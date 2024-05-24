

public class Circulo {
    private double x;
    private double y;
    private double raio;

    public Circulo(){
        this.x=0;
        this.y=0;
        this.raio=1;
    }

    public Circulo(double px, double py, double r){
        this.x=px;
        this.y=py; 
        this.raio=r; // e se o raio for negativo?
    }
    public Circulo(double r){
        this.x=0;
        this.y=0;
        this.raio=r;
    }

    public Circulo(Circulo circlo){
        this.x=circlo.getX();
        this.y=circlo.getY();
        this.raio=circlo.getRaio();
    }

    //getters

    public double getX() {
        return this.x;
    }

    public double getY() {
        return this.y;
    }

    public double getRaio() {
        return this.raio;
    }

    //setters
    public void setX(double px) {
        this.x=px;
    }
    public void setY(double py) {
        this.y=py;
    }
    public void setRaio(double r) {
        this.raio=r;
    }
//
    public void alteraCentro(double x, double y){
        setX(x);
        setY(y);
    }

    public double calculaArea(){
        double area = Math.PI * Math.pow(raio, 2);
        return area;
    }

    public double calculaPerimetro(){
        double perimetro = 2*Math.PI*raio;
        return perimetro;
    }

    public Circulo clone(){
        return new Circulo(this);
    }

    public String toString(){
        return "Circulo de centro (" + this.x + "," + this.y + ") e raio " + this.raio;
    }
    // equals
    public boolean equals(Object o){
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        Circulo c = (Circulo) o;
        return this.x == c.getX() && this.y == c.getY() && this.raio == c.getRaio();
    }


}
