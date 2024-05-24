import sd23.JobFunction;
import sd23.JobFunctionException;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.LinkedList;
import java.util.concurrent.*;

public class Servidor {

    private static final int MAX_MEMORY = 1000;
    private static int currentMemory = 0;
    private static BlockingQueue<Frame> taskQueue = new LinkedBlockingQueue<>();
    private static int currentIndex = 0; // Index for round robin algorithm

    public static void main(String[] args) throws Exception {
        ServerSocket ss = new ServerSocket(12345);

        final Accounts accounts = new Accounts();

        while (true) {
            Socket s = ss.accept();
            Connection c = new Connection(s);

            Runnable worker = () -> {
                try (c) {
                    while (true) {
                        Frame frame = c.receive();

                        if (frame.tag == 0) {
                            System.out.println("User log-in attempt.");
                            String email = frame.username;
                            String password = new String(frame.data);
                            String stored_password;
                            accounts.l.readLock().lock();
                            try {
                                stored_password = accounts.getPassword(email);
                            } finally {
                                accounts.l.readLock().unlock();
                            }
                            if (stored_password != null) {
                                if (stored_password.equals(password)) {
                                    c.send(0, "", "Sessão iniciada com sucesso!".getBytes());
                                } else
                                    c.send(0, "", "Erro - palavra-passe errada.".getBytes());
                            } else
                                c.send(0, "", "Erro - conta não existe.".getBytes());
                        } else if (frame.tag == 1) {
                            System.out.println("User registration attempt.");
                            String email = frame.username;
                            String password = new String(frame.data);
                            accounts.l.writeLock().lock();
                            try {
                                if (accounts.accountExists(email))
                                    c.send(1, "", "Erro - endereço de email já pertence a uma conta.".getBytes());
                                else {
                                    accounts.addAccount(email, password);
                                    c.send(frame.tag, "", "Registo efetuado com sucesso!".getBytes());
                                }
                            } finally {
                                accounts.l.writeLock().unlock();
                            }
                        } else if (frame.tag == 2) {
                            int requiredMemory = getRequiredMemory(frame.data);
                            byte[] job = getJob(frame.data);

                            if (requiredMemory <= MAX_MEMORY - currentMemory) {
                                currentMemory += requiredMemory;
                                byte[] result = JobFunction.execute(frame.data);
                                c.send(2, frame.username, result);
                                currentMemory -= requiredMemory;
                            } else {
                                taskQueue.add(frame);
                            }

                            // Round Robin implementation
                            if (!taskQueue.isEmpty() && currentIndex >= taskQueue.size()) {
                                currentIndex = 0;
                            }
                            if (!taskQueue.isEmpty()) {
                                Frame nextTask = taskQueue.peek(); // espreita o próximo elemento sem removê-lo.
                                int nextTaskMemory = getRequiredMemory(nextTask.data);
                                if (nextTaskMemory <= MAX_MEMORY - currentMemory) {
                                    taskQueue.remove(); // Remove o elemento da cabeça da fila.
                                    currentMemory += nextTaskMemory;
                                    byte[] result = JobFunction.execute(nextTask.data);
                                    c.send(2, nextTask.username, result);
                                    currentMemory -= nextTaskMemory;
                                }
                                currentIndex++;
                            }
                        } else if (frame.tag == 3) {
                            // Handle service status request
                            String status = "Memory available: " + (MAX_MEMORY - currentMemory) +
                                    "\nTasks in queue: " + taskQueue.size();
                            c.send(3, "", status.getBytes());
                        }
                    }
                } catch (IOException | JobFunctionException ignored) {

                }
            };

            new Thread(worker).start();
        }
    }

    private static int getRequiredMemory(byte[] taskData) {
        String dataString = new String(taskData);
        String[] parts = dataString.split(":");

        // Assuming the second part of the split string is the required memory for the task
        return Integer.parseInt(parts[1]);
    }

    private static byte[] getJob(byte[] taskData) {
        String dataString = new String(taskData);
        String[] parts = dataString.split(":");

        // Assuming the second part of the split string is the required memory for the task
        return parts[0].getBytes();
    }

    public static int getMemoryAvailable() {
        return (MAX_MEMORY - currentMemory);
    }
}