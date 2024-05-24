import java.time.LocalDate;

public class Encomenda {    
    private String nomeCliente;
    private int NIF;
    private String morada;
    private int numEncomenda;
    private LocalDate dataEncomenda;
    private int ocupaçãoLinhas;
    private LinhaEncomenda[] linhas;

    public Encomenda(){
        this.nomeCliente="N/A";
        this.NIF=0;
        this.morada="N/A";
        this.numEncomenda=0;
        this.dataEncomenda=LocalDate.now();
        this.ocupaçãoLinhas=0;
        this.linhas=new LinhaEncomenda[10];
    }
    public Encomenda(String nomeCliente, int NIF, String morada, int numEncomenda, LocalDate dataEncomenda, int ocupaçãoLinhas){
        this.nomeCliente=nomeCliente;
        this.NIF=NIF;
        this.morada=morada;
        this.numEncomenda=numEncomenda;
        this.dataEncomenda=dataEncomenda;
        this.ocupaçãoLinhas=ocupaçãoLinhas;
        this.linhas=new LinhaEncomenda[10];
    }

    public Encomenda(String nomeCliente, int NIF, String morada, int numEncomenda, LocalDate dataEncomenda, int ocupaçãoLinhas,LinhaEncomenda[] linhas){
        this.nomeCliente=nomeCliente;
        this.NIF=NIF;
        this.morada=morada;
        this.numEncomenda=numEncomenda;
        this.dataEncomenda=dataEncomenda;
        this.ocupaçãoLinhas=ocupaçãoLinhas;
        for(int i=0;i<linhas.length;i++){
            this.linhas[i]=linhas[i];
        }
    }

    public Encomenda(Encomenda e){
        this.nomeCliente=e.getNomeCliente();
        this.NIF=e.getNIF();
        this.morada=e.getMorada();
        this.numEncomenda=e.getNumEncomenda();
        this.dataEncomenda=e.getDataEncomenda();
        this.ocupaçãoLinhas=e.getOcupaçãoLinhas();
        this.linhas=e.getLinhas();
    }
    //getters
    public String getNomeCliente() {
        return nomeCliente;
    }
    public int getNIF() {
        return NIF;
    }
    public String getMorada() {
        return morada;
    }
    public int getNumEncomenda() {
        return numEncomenda;
    }
    public LocalDate getDataEncomenda() {
        return dataEncomenda;
    }
    public int getOcupaçãoLinhas() {
        return ocupaçãoLinhas;
    }
    // agregação
    public LinhaEncomenda[] getLinhas() {
        LinhaEncomenda[] res = new LinhaEncomenda[this.linhas.length];
        for(int i=0;i<this.linhas.length;i++){
            res[i]=this.linhas[i];
        }
        return res;

    }
    // composição 
    /*
    public LinhaEncomenda[] getLinhas(){
        LinhaEncomenda[] res = new LinhaEncomenda[this.linhas.length];
        for(int i=0;i<this.linhas.length;i++){
            res[i]=this.linhas[i].clone();
        }
        return res;

    */

    //setters
    public void setNomeCliente(String nomeCliente) {
        this.nomeCliente = nomeCliente;
    }
    public void setNIF(int NIF) {
        this.NIF = NIF;
    }
    public void setMorada(String morada) {
        this.morada = morada;
    }
    public void setNumEncomenda(int numEncomenda) {
        this.numEncomenda = numEncomenda;
    }
    public void setDataEncomenda(LocalDate dataEncomenda) {
        this.dataEncomenda = dataEncomenda;
    }
    public void setOcupaçãoLinhas(int ocupaçãoLinhas) {
        this.ocupaçãoLinhas = ocupaçãoLinhas;
    }
    public void setLinhas(LinhaEncomenda[] linhas) {
        LinhaEncomenda[] res = new LinhaEncomenda[linhas.length];
        for(int i=0;i<linhas.length;i++){
            res[i]=linhas[i];
        }

    }
    //metodos

    public double calculaValorTotal(){
        double total=0;
        for(LinhaEncomenda le : getLinhas()){
            if (le != null) {
                total += le.calculaValorLinhaEnc();
            }
    
        }
        return total;
    }

    public double calculaValorDesconto(){
        double totalDesconto=0;
        for(LinhaEncomenda le: getLinhas()){
            if (le != null) {
                totalDesconto+=le.calculaValorDesconto();
            }
        }
        return totalDesconto;
    }
    public int numeroTotalProdutos(){
        int totalProdutos=0;
        for(LinhaEncomenda le: this.getLinhas()){
            if(le!=null){
                totalProdutos+=1;
            }
        }
        return totalProdutos;
    }

    public boolean existeProdutoEncomenda(String refProduto){
        // return dentro de ciclo não é boa prática porem .strem e .anyMatch ainda nao foi dado
        for(LinhaEncomenda le: this.getLinhas()){
            if(le!=null){
                if(le.getEAN().equals(refProduto)){
                    return true;
                }
            }
        }
        return false;
    }

    public void adicionaLinha(LinhaEncomenda linha){
        if(this.ocupaçãoLinhas<this.linhas.length){
            this.linhas[this.ocupaçãoLinhas+1]=linha;
            this.ocupaçãoLinhas++;
        }
    }
    public void removeProduto(String codProd){
        for(int i=0; i<this.ocupaçãoLinhas;i++){
            if(this.linhas[i].getEAN().equals(codProd)){
                for(int j=i;j<this.ocupaçãoLinhas;j++){ // tudo o que esta depois do ocupaçãoLinhas nao vai ser definido como null mas estará la como "lixo" pois nunca sera lido (à partida)
                    this.linhas[j]=this.linhas[j+1];
                }
                this.ocupaçãoLinhas--;
            }
        }
    }
    // equals
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        Encomenda e = (Encomenda) o;
        return this.nomeCliente.equals(e.getNomeCliente()) &&
                this.NIF == e.getNIF() &&
                this.morada.equals(e.getMorada()) &&
                this.numEncomenda == e.getNumEncomenda() &&
                this.dataEncomenda.equals(e.getDataEncomenda()) &&
                this.linhas.equals(e.getLinhas());
    }
    //toString
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("nomeCliente:'").append(nomeCliente).append("\n");
        sb.append("NIF:").append(NIF).append("\n");
        sb.append("morada:'").append(morada).append("\n");
        sb.append("numEncomenda:").append(numEncomenda).append("\n");
        sb.append("dataEncomenda_").append(dataEncomenda).append("\n");
        sb.append("linhas:\n");
        for (LinhaEncomenda le : this.linhas) {
            if(le!=null){
                sb.append(le.toString());
            }
        }
        return sb.toString();
       
    }
}
