import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;



public class FitnessTest {

    public static void main(String[] args) {
        Utilizador u = new Utilizador("diogo@mail.com", "passWord", "Diogo", Genero.Masculino, 1.85, 74, LocalDate.of(2002, 2, 12), "");
        Corrida c1 = new Corrida("c1", "Corrida", LocalDate.of(2024, 4, 16), 60, 5, 100, "Bom Jesus");
        Corrida c2 = new Corrida("c2", "Corrida", LocalDate.of(2024, 4, 17), 60, 5, 100, "Bom Jesus");
        Corrida c3 = new Corrida("c3", "Corrida", LocalDate.of(2024, 4, 18), 60, 5, 100, "Bom Jesus");
        u.addAtividade(c1);
        u.addAtividade(c2);
        u.addAtividade(c3);

        Map<String, Utilizador> utilizadoresMap = new HashMap<>();
        utilizadoresMap.put(u.getEmail(), u);

        Fitness f = new Fitness("Ginasio", utilizadoresMap);

        // Teste do método adiciona
        System.out.println("Atividades do Diogo: " + f.getUtilizador("diogo@mail.com").getAtividades());

        // Teste do método utilizadorMaisActiv
        Utilizador utilizadorMaisAtivo = f.utilizadorMaisActivo();
        System.out.println("Utilizador mais ativo: " + utilizadorMaisAtivo);

        // Teste do método actualizaDesportoFav
        f.actualizaDesportoFav();
        System.out.println("Desporto favorito do Diogo: " + f.getUtilizador("diogo@mail.com").getDesporto_favorito());
    }
}
