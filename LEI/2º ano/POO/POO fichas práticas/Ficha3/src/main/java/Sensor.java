public class Sensor {
    double pressao;

    public Sensor() {
        this.pressao = 0;
    }

    public Sensor(double valor){
        this.pressao = valor >= 0 ? valor : 0;
        
    }

    public Sensor(Sensor sensor){
        this.pressao = sensor.getPressao();
    }

    public double getPressao() {
        return this.pressao;
    }

    public boolean setPressao(double valor) {
        if (this.getPressao() + valor>=0) {
            this.pressao = valor + this.getPressao();
            return true;
        } else {
            return false;
        }
    }

    
}
