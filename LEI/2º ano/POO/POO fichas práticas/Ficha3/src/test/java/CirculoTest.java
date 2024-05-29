import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import Circulo;

public class CirculoTest {
    /*
    public static void main(String [] args){
        x
        Circulo c1,c2,c3,c4;
        c1 = new Circulo(1,1,10);
        c2 = new Circulo(2,6,8);
        c3 = new Circulo(5);
        c4 = new Circulo(6,6,2);

        System.out.println(c1); // o .toString() é chamado automaticamente
        System.out.println(c2);
        System.out.println(c3);
        System.out.println(c4);

        System.out.println("Area do c1: " + c1.calculaArea());
        System.out.println("Perimetro do c4: " + c4.calculaPerimetro());


    }
    */
    @Test
    public void testGetX(){
        Circulo c = new Circulo(2,4,10);
        double x = c.getX();
        assertEquals(2,x);
    }
    @Test
    public void testGetY(){
        Circulo c = new Circulo(2,4,10);
        double y = c.getY();
        assertEquals(4,y);
    }
    @Test
    public void testGetRaio(){
        Circulo c = new Circulo(1,4,10);
        double raio = c.getRaio();
        assertEquals(10,raio);
    }
}
