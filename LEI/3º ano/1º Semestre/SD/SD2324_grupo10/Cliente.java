import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.io.FileWriter;

public class Cliente {
    public static void main(String[] args) throws Exception {
        Socket s = new Socket("localhost", 12345);
        Demultiplexer m = new Demultiplexer(new Connection(s));

        HashSet<Thread> alarms = new HashSet<>();
        ConcurrentHashMap<Integer, String> responses = new ConcurrentHashMap<>();

        m.start();

        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        Boolean logado = false;
        String username = null;
        int requestID = 0; // Adicionado para rastrear pedidos

        while (username == null) {
            System.out.print("***JOB'S***\n"
                    + "\n"
                    + "O que pretende fazer?\n"
                    + "1) Iniciar sessão.\n"
                    + "2) Registar nova conta.\n"
                    + "\n"
                    + "Insira o valor corresponde à operação desejada: ");
            String option = stdin.readLine();
            if (option.equals("1")) {
                System.out.print("***INICIAR SESSÃO***\n"
                        + "\n"
                        + "Introduza o seu endereço de email: ");
                String email = stdin.readLine();
                System.out.print("Introduza a sua palavra-passe: ");
                String password = stdin.readLine();
                m.send(0, email, password.getBytes());
                String response = new String(m.receive(0));
                if (!response.startsWith("Erro")) {
                    username = email;
                    logado = true;
                }
                System.out.println("\n" + response + "\n");
            } else if (option.equals("2")) {
                System.out.print("***REGISTAR NOVA CONTA***\n"
                        + "\n"
                        + "Introduza o seu endereço de email: ");
                String email = stdin.readLine();
                System.out.print("Introduza a sua palavra-passe: ");
                String password = stdin.readLine();
                m.send(1, email, password.getBytes());
                String response = new String(m.receive(1));
                if (!response.startsWith("Erro")) {
                    username = email;
                    logado = true;
                }
                System.out.println("\n" + response + "\n");
            }
        }
        while (logado) {
            System.out.print("\n***JOB'S***\n"
                    + "\n"
                    + "O que pretende fazer?\n"
                    + "1) Enviar uma tarefa para execução.\n"
                    + "2) Verificar o status do servidor.\n"
                    + "3) Carregar tarefas de ficheiro.\n"
                    + "4) Sair.\n"
                    + "\n"
                    + "Insira o valor corresponde à operação desejada: ");
            String option = stdin.readLine();
            switch (option) {
                case "1":
                    String code = "";
                    boolean validCode = false; // Flag para verificar se o código da tarefa é válido

                    while (!validCode) {
                        System.out.print("Insira o código da tarefa: ");
                        code = stdin.readLine();

                        if (code == null || code.trim().isEmpty()) {
                            System.out.println("Por favor, insira um código de tarefa válido.");
                        } else {
                            try {
                                int codeValue = Integer.parseInt(code.trim());
                                validCode = true; // Código é um inteiro válido, sai do loop
                            } catch (NumberFormatException e) {
                                System.out.println("Por favor, insira um número inteiro válido.");
                            }
                        }
                    }

                    int memory = 0; // Inicializa a variável memory
                    boolean validMemory = false; // Flag para verificar se a memória inserida é válida
                    while (!validMemory) {
                        try {
                            System.out.print("Insira a quantidade de memória necessária: ");
                            memory = Integer.parseInt(stdin.readLine());
                            if (memory <= 0) {
                                System.out.println("Por favor, insira um valor de memória positivo.");
                            } else if (memory > Servidor.getMemoryAvailable()) {
                                System.out.println("Tarefa excede o limite de memória.");
                            } else {
                                validMemory = true; // Memória válida, sai do loop
                            }
                        } catch (NumberFormatException e) {
                            System.out.println("Por favor, insira um número válido para a quantidade de memória.");
                        }
                    }

                    m.send(2, username, (code + ":" + memory).getBytes());
                    final int taskID = requestID++;
                    new Thread(() -> {
                        try {
                            byte[] bytes = m.receive(2);
                            String response = new String(bytes, StandardCharsets.UTF_8);
                            responses.put(taskID, response);
                            System.out.println("\nResposta para o pedido " + taskID + ": \u001B[32m" + response+"\u001B[0m");

                            // Automaticamente depositar os resultados no arquivo
                            String resultFilePath = "result_" + taskID + ".txt";
                            writeResultsToFile(resultFilePath, Collections.singletonList(response));
                            System.out.println("Resultado depositado em " + resultFilePath);

                        } catch (IOException | InterruptedException e) {
                            e.printStackTrace();
                        }
                    }).start();
                    System.out.println("\nPedido enviado com ID: \u001B[32m" + taskID + "\u001B[0m");
                    break;
                case "2":
                    // Enviar um pedido para verificar o estado atual de ocupação do serviço
                    m.send(3, username, "".getBytes());
                    final int statusID = requestID++;
                    new Thread(() -> {
                        try {
                            byte[] bytes = m.receive(3);
                            String response2 = new String(bytes, StandardCharsets.UTF_8);
                            responses.put(statusID, response2);
                            System.out.println("\nResposta para o pedido " + statusID + ": \u001B[32m" + response2+"\u001B[0m");

                        } catch (IOException | InterruptedException e) {
                            e.printStackTrace();
                        }
                    }).start();
                    System.out.println("\nPedido enviado com ID: \u001B[32m" + statusID+"\u001B[0m");
                    break;
                case "3":
                    System.out.print("Insira o caminho do arquivo contendo as tarefas: ");
                    String filePath = stdin.readLine();
                    List<AbstractMap.SimpleEntry<Integer, Integer>> tasksFromFile = readTasksFromFile(filePath);
                    System.out.print("String " + tasksFromFile);
                    // C:\Users\Asus\Desktop\tarefas.txt
                    for (AbstractMap.SimpleEntry<Integer, Integer> taskEntry : tasksFromFile) {
                        int Tcode = taskEntry.getKey();
                        int Tmemory = taskEntry.getValue();

                        // Envie cada tarefa para o servidor
                        m.send(2, username, (Tcode + ":" + Tmemory).getBytes());
                        new Thread(() -> {
                            try {
                                byte[] bytes = m.receive(2);
                                String response = new String(bytes, StandardCharsets.UTF_8);
                                responses.put(Tcode, response);
                                System.out.println("Resposta para o pedido " + Tcode + ": " + response);

                                // Automaticamente depositar os resultados no arquivo
                                String resultFilePath = "result_" + Tcode + ".txt";
                                writeResultsToFile(resultFilePath, Collections.singletonList(response));
                                System.out.println("Resultado depositado em " + resultFilePath);

                            } catch (IOException | InterruptedException e) {
                                e.printStackTrace();
                            }
                        }).start();
                    }
                break;
                case "4":
                    System.out.println("\nSaindo...");
                    logado = false;
                    try {
                        m.close(); // Se Demultiplexer tiver um método close, fechará o socket e outras conexões
                        s.close(); // Fechar o socket
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    System.exit(0); // Encerra o programa
                    break;

                default:
                    System.out.println("\nOpção inválida. Tente novamente.");

            }
        }
    }

    private static List<AbstractMap.SimpleEntry<Integer, Integer>> readTasksFromFile(String filePath) {
        List<AbstractMap.SimpleEntry<Integer, Integer>> tasks = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(";");
                if (parts.length == 2) {
                    int code = Integer.parseInt(parts[0].trim());
                    int memory = Integer.parseInt(parts[1].trim());
                    tasks.add(new AbstractMap.SimpleEntry<>(code, memory));
                } else {
                    System.out.println("Ignorando linha inválida: " + line);
                }
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo de tarefas: " + e.getMessage());
        }
        return tasks;
    }


    private static void writeResultsToFile(String filePath, List<String> results) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            for (String result : results) {
                writer.write(result);
                writer.newLine(); // Adiciona uma nova linha após cada resultado
            }
        } catch (IOException e) {
            System.out.println("Erro ao escrever os resultados no arquivo: " + e.getMessage());
        }
    }
}