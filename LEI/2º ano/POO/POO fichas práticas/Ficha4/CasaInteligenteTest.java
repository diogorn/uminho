import java.util.ArrayList;

public class CasaInteligenteTest {
    public static void main(String [] args){
        Lampada l1 = new Lampada();
        Lampada l2 = new Lampada(Lampada.Modo.ECO, 1, 2, 0, 0);
        Lampada l3 = new Lampada(Lampada.Modo.ON, 2, 4, 0, 0);
        Lampada l4 = new Lampada(Lampada.Modo.ON, 1, 2, 0, 0);
        Lampada l5 = new Lampada(Lampada.Modo.OFF, 1, 4, 0, 0);
        ArrayList<Lampada> ls = new ArrayList<Lampada>();
        ls.add(l1);
        ls.add(l2);
        ls.add(l3);
        ls.add(l4);
        CasaInteligente c = new CasaInteligente(ls);
        c.addLampada(l5);
        c.ligaLampadaNormal(0);
        c.ligaLampadaEco(0);
       // System.out.println(c.qtEmEco());
        c.removeLampada(4);
        c.ligaTodasEco();
        c.ligaTodasMax();
        System.out.println(c.consumoTotal());
       // System.out.println(c.maisGastadora());
       // System.out.println(c.lampadasEmModoEco());
       // c.reset();
        //System.out.println(c);
       // System.out.println(c.podiumEconomia());
        //System.out.println(c);




    }
}
