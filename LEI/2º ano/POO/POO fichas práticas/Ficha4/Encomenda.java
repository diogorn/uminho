import java.lang.reflect.Array;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Iterator;


public class Encomenda {
    private String nomeCliente;
    private int NIF;
    private String morada;
    private int numEncomenda;
    private LocalDate dataEncomenda;
    private ArrayList<LinhaEncomenda> linhas;

    public Encomenda() {
        this.nomeCliente = "";
        this.NIF = 0;
        this.morada = "";
        this.numEncomenda = 0;
        this.dataEncomenda = LocalDate.now();
        this.linhas = new ArrayList<LinhaEncomenda>();
    }
    public Encomenda(String nomeCliente, int NIF, String morada, int numEncomenda, LocalDate dataEncomenda, ArrayList<LinhaEncomenda> linhas) {
        this.nomeCliente = nomeCliente;
        this.NIF = NIF;
        this.morada = morada;
        this.numEncomenda = numEncomenda;
        this.dataEncomenda = dataEncomenda;
        this.linhas = new ArrayList<LinhaEncomenda>();
        for(LinhaEncomenda l : linhas){
            this.linhas.add(l.clone());
        }
    }
    public Encomenda(Encomenda encomenda) {
        this.nomeCliente = encomenda.getNomeCliente();
        this.NIF = encomenda.getNIF();
        this.morada = encomenda.getMorada();
        this.numEncomenda = encomenda.getNumEncomenda();
        this.dataEncomenda = encomenda.getDataEncomenda();
        this.linhas = new ArrayList<LinhaEncomenda>();
        for(LinhaEncomenda l : encomenda.getLinhas()){
            this.linhas.add(l.clone());
        }
    }

    // getters
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

    public ArrayList<LinhaEncomenda> getLinhas() {
        ArrayList<LinhaEncomenda> copia = new ArrayList<LinhaEncomenda>();
        for(LinhaEncomenda l : this.linhas){
            copia.add(l.clone());
        }
        return copia;
    }
    // setters
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
    public void setLinhas(ArrayList<LinhaEncomenda> linhas) {
        this.linhas = new ArrayList<LinhaEncomenda>();
        for(LinhaEncomenda l : linhas){
            this.linhas.add(l.clone());
        }
    }

    public double calculaValorTotal(){
        double total=0;
        for(LinhaEncomenda l : this.linhas){
            total += l.calculaValorLinhaEnc();
        }
        return total;
    }
    public double calculaValorDesconto(){
        double desconto=0;
        for(LinhaEncomenda l : this.linhas){
            desconto += l.calculaValorDesconto();
        }
        return desconto;
    }

    public int numeroTotalProdutos(){
        return this.linhas.size();
    }

    public boolean existeProdutoEncomenda(String refProduto){
       boolean encontrado=false; 
       Iterator<LinhaEncomenda> it = this.linhas.iterator();
         while(it.hasNext() && !encontrado){
              LinhaEncomenda l = it.next();
              if(l.getReferencia().equals(refProduto)){
                encontrado = true;
              }
         }
         return encontrado;   
    }
    public void adicionaLinha(LinhaEncomenda linha){
        this.linhas.add(linha.clone());
    }
    
    public void removeProduto(String codProd){
        boolean encontrado=false; 
        Iterator<LinhaEncomenda> it = this.linhas.iterator();
        while(it.hasNext() && !encontrado){
            LinhaEncomenda l = it.next();
            if(l.getReferencia().equals(codProd)){
                it.remove();
                encontrado = true;
            }
        }
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nEncomenda: ");
        sb.append(this.numEncomenda);
        sb.append("\nData: ");
        sb.append(this.dataEncomenda);
        sb.append("\nCliente: ");
        sb.append(this.nomeCliente);
        sb.append("\nNIF: ");
        sb.append(this.NIF);
        sb.append("\nMorada: ");
        sb.append(this.morada);
        sb.append("\nLinhas: ");
        for(LinhaEncomenda l : this.linhas){
            sb.append(l.toString());
        }
        return sb.toString();
    }    
}
