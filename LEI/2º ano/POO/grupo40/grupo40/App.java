import java.util.Scanner;

import Controller.Controller;
import Model.Fitness;
import View.*;

public class App {
    public static void main(String[] args) throws Exception {
        Fitness fitness = new Fitness();
        Controller controller = new Controller(fitness);
        Scanner scanner = new Scanner(System.in);
        View view = new View(controller, scanner);
        view.run();
        scanner.close();

    }
}
