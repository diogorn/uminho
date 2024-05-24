public class TesteLinhaEncomenda {
    public static void main(String[] args) {
        LinhaEncomenda l1= new LinhaEncomenda();
        LinhaEncomenda l2= new LinhaEncomenda("0195949052606", "AirPods Pro", 203.25,1,23,0);
        LinhaEncomenda l3= new LinhaEncomenda(l2);

        System.out.println("l1\n"+l1.toString());
        System.out.println("l2\n"+l2.toString());
        System.out.println("l3\n"+l3.toString());

        l1.setEAN("0195949052606");
        l1.setDescrição("MX Master 3");
        l1.setPreçoSIva(100.0);
        l1.setQuantidade(2);
        l1.setIva(23);
        l1.setDesconto(10);

        System.out.println("Faturas");
        System.out.println("l1\n"+l1.toString());
        System.out.println("valor linha encomenda l1: "+l1.calculaValorLinhaEnc());
        System.out.println("Valor desconto l1: "+l1.calculaValorDesconto());
        System.out.println("l2\n"+l2.toString());
        System.out.println("valor linha encomenda l2: "+l2.calculaValorLinhaEnc());
        System.out.println("Valor desconto l2: "+l2.calculaValorDesconto());
        System.out.println("l3\n"+l3.toString());
        System.out.println("valor linha encomenda l3: "+l3.calculaValorLinhaEnc());
        System.out.println("Valor desconto l3: "+l3.calculaValorDesconto());
        


    }
}
