import java.time.LocalDate;

public class TesteEncomenda {   
    public static void main(String[] args) {
        LinhaEncomenda l1= new LinhaEncomenda();
        LinhaEncomenda l2= new LinhaEncomenda("0195949052606", "AirPods Pro", 203.25,1,23,0);
        LinhaEncomenda l3= new LinhaEncomenda(l2);

        LinhaEncomenda[] linhas = new LinhaEncomenda[10];
        linhas[0] = l1;
        linhas[1] = l2;
        linhas[2] = l3;

        l1.setEAN("0195949052606");
        l1.setDescrição("MX Master 3");
        l1.setPreçoSIva(100.0);
        l1.setQuantidade(2);
        l1.setIva(23);
        l1.setDesconto(10);

        Encomenda e1= new Encomenda();
        Encomenda e2= new Encomenda("Diogo",240262492, "Barcelos", 12, LocalDate.now(), linhas);
        
        System.out.println("Encomenda e1:\n"+e1.toString());
        System.out.println("Encomenda e2:\n"+e2.toString());
        System.out.println("Valor total da encomenda e2: "+e2.calculaValorTotal());
        System.out.println("Valor total dos descontos da encomenda e2: "+e2.calculaValorDesconto());
        System.out.println("Numero de produtos: "+e2.numeroTotalProdutos());
        System.out.println("Existe produto na encomenda e2: "+e2.existeProdutoEncomenda("0195949052606"));
        
        LinhaEncomenda e3= new LinhaEncomenda("123", "Teste", 50,1,23,0);
        e2.adicionaLinha(e3);
        System.out.println("Encomenda e2:\n"+e2.toString());
        e2.removeProduto("0195949052606");
        System.out.println("Encomenda e2:\n"+e2.toString());
    }
}
