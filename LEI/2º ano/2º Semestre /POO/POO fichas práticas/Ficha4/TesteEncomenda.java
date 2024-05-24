import java.time.LocalDate;
import java.util.ArrayList;

public class TesteEncomenda {
    public static void main(String [] args){
        LinhaEncomenda l1 = new LinhaEncomenda("1","Computador", 1000, 2, 0.23, 0.10);
        LinhaEncomenda l2 = new LinhaEncomenda("2","Rato", 10, 10, 0.23, 0.10);
        LinhaEncomenda l3 = new LinhaEncomenda("3","Teclado", 20, 5, 0.23,0.10);
        ArrayList<LinhaEncomenda> linhas = new ArrayList<LinhaEncomenda>();
        linhas.add(l1);
        linhas.add(l2);
        linhas.add(l3);
        Encomenda e = new Encomenda("João", 123456789, "Rua do João", 1, LocalDate.now(), linhas);
        System.out.println(e.toString());
        System.out.println("\nValor total: " + e.calculaValorTotal());
        System.out.println("\nValor desconto: "+e.calculaValorDesconto());
        System.out.println("\nNumero produtos: "+ e.numeroTotalProdutos());
        System.out.println("\nExiste: "+e.existeProdutoEncomenda("1"));
        LinhaEncomenda l4 = new LinhaEncomenda("4","Monitor", 200, 1,0.23, 0.10);
        e.adicionaLinha(l4);
        System.out.println(e.toString());
        e.removeProduto("4");
        System.out.println(e.toString());



    
    }
 
}
