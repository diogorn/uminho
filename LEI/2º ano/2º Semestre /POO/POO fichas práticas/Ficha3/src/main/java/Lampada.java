import java.time.LocalDateTime; 
public class Lampada {
    public static final int OFF = 0;
    public static final int ON = 1;
    public static final int ECO = 2;

    private int modo; // 0 - desligada, 1 - ligada, 2 - eco
    private double consumoNormal; // por milissegundo
    private double consumoEco; // por milissegundo
    private double consumoTotal; // acumulador
    private long ultimaAlreração; // stamp em milissegundos desde 1/1/1970

    public Lampada(){
        this.modo = Lampada.OFF;
        this.consumoNormal = 1;
        this.consumoEco = 0.5;
        this.consumoTotal = 0;
    }

    public Lampada(double consumoNormal, double consumoEco){
        this.modo = Lampada.OFF;
        this.consumoNormal = consumoNormal;
        this.consumoEco = consumoEco;
        this.consumoTotal = 0;
    }

    public void lampadaOn(){
        if(this.modo != Lampada.ON){
            if (this.modo == Lampada.OFF) {
                this.modo = Lampada.ON;
                this.ultimaAlreração = System.currentTimeMillis();
            } else {
                this.modo = Lampada.ON;
                long agora = System.currentTimeMillis();
                long tempoDecorrido = agora - this.ultimaAlreração;
                this.consumoTotal += tempoDecorrido * this.consumoEco;
                this.ultimaAlreração = agora;
               
            }
        }
    }

    public void lampECO(){
        if(this.modo != Lampada.ECO){
            if (this.modo == Lampada.OFF) {
                this.modo = Lampada.ECO;
                this.ultimaAlreração = System.currentTimeMillis();
            } else {
                this.modo = Lampada.ECO;
                long agora = System.currentTimeMillis();
                long tempoDecorrido = agora - this.ultimaAlreração;
                this.consumoTotal += tempoDecorrido * this.consumoNormal;
                this.ultimaAlreração = agora;
            }
        }
    }
    

    
   
    
    
}
