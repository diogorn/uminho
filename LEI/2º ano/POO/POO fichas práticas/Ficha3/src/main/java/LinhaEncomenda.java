public class LinhaEncomenda {
    private String EAN;
    private String descrição;
    private double preçoSIva;
    private double quantidade;
    private double iva; // %
    private double desconto; // %

    private static double PORCENTO = 100;

    //construtores
    public LinhaEncomenda (){
        this.EAN="N/A";
        this.descrição="N/A";
        this.preçoSIva=0;
        this.quantidade=0;
        this.iva=0;
        this.desconto=0;
    }
    public LinhaEncomenda(String Ean, String descriçao, double preçoSIva, double quantidade, double iva, double desconto){
        this.EAN=Ean;
        this.descrição=descriçao;
        this.preçoSIva=preçoSIva;
        this.quantidade=quantidade;
        this.iva=iva;
        this.desconto=desconto;
    }
    public LinhaEncomenda(LinhaEncomenda le){
        this.EAN=le.getEAN();
        this.descrição=le.getDescrição();
        this.preçoSIva=le.getPreçoSIva();
        this.quantidade=le.getQuantidade();
        this.iva=le.getIva();
        this.desconto=le.getDesconto();
    }

    //guetters
    public String getEAN() {
        return this.EAN;
    }
    public String getDescrição() {
        return this.descrição;
    }
    public double getPreçoSIva() {
        return this.preçoSIva;
    }
    public double getQuantidade() {
        return this.quantidade;
    }
    public double getIva() {
        return this.iva;
    }
    public double getDesconto() {
        return this.desconto;
    }
    //setters
    public void setEAN(String EAN) {
        this.EAN = EAN;
    }
    public void setDescrição(String descrição) {
        this.descrição = descrição;
    }
    public void setPreçoSIva(double preçoSIva) {
        this.preçoSIva = preçoSIva;
    }
    public void setQuantidade(double quantidade) {
        this.quantidade = quantidade;
    }
    public void setIva(double iva) {
        this.iva = iva;
    }
    public void setDesconto(double desconto) {
        this.desconto = desconto;
    }

    //metodos
    public double calculaValorLinhaEnc(){
        if (this.getPreçoSIva()==0) return 0;

        double subtotal = getPreçoSIva()*getQuantidade();
        double desconto = subtotal*(getDesconto()/PORCENTO);
        //double desonto = calculaValorDesconto();
        double total = (subtotal - desconto)*(1+(getIva()/PORCENTO));        
        
        return total;
    }
    public double calculaValorDesconto(){
        double subtotal = getPreçoSIva()*getQuantidade();
        double desconto = subtotal*(getDesconto()/PORCENTO);
        return desconto;
    }
    // equals
    
    // toString
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("EAN: ").append(this.EAN).append("\n");
        sb.append("Descrição: ").append(this.descrição).append("\n");
        sb.append("Preço s/ IVA: ").append(this.preçoSIva).append("\n");
        sb.append("Quantidade: ").append(this.quantidade).append("\n");
        sb.append("IVA: ").append(this.iva).append("\n");
        sb.append("Desconto: ").append(this.desconto).append("\n");
        return sb.toString();
    }

}
