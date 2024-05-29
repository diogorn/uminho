import java.io.IOException;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) throws IOException, UtilizadorNaoExisteException {
        
        Corrida c1 = new Corrida("c1", "Corrida na praia", LocalDate.now(), 60, 10, 100, "Praia");
        Corrida c2 = new Corrida("c2", "Corrida na cidade", LocalDate.now(), 60, 10, 100, "Cidade");
        Map<String, Atividade> atividades = new HashMap<>();
        atividades.put(c1.getCodigo(), c1);
        atividades.put(c2.getCodigo(), c2);
        Utilizador u1 = new Utilizador("u1", "1234", "Joao", Genero.Masculino, 1.80, 80, LocalDate.now(), "Corrida", atividades);
        Utilizador u2 = new Utilizador("u2", "1234", "Maria", Genero.Feminino, 1.60, 60, LocalDate.now(),null);
        Map<String, Utilizador> utilizadores = new HashMap<>();
        utilizadores.put(u1.getEmail(), u1);
        utilizadores.put(u2.getEmail(), u2);
        Fitness f1 = new Fitness("Ginasio", utilizadores);
        Fitness f2 = new Fitness("Ginasio", utilizadores);
/*
        try {
             System.out.println(f2.utilizadorComMaisRegistos());
        } catch (UtilizadorNaoExisteException e) {
            System.out.println(e.getMessage());
        }
        */

        f1.escreverCSVAtividades("u1", "atividades.csv");
        f1.guardaEstado("estado.dat");
        System.out.println(f1.toString());
    }
}
