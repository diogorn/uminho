
import java.io.Serializable;
import java.time.LocalDate;


public abstract class Atividade implements Serializable{
    private String codigo;
    private String descricao;
    private LocalDate data;
    private int duracao;
    private Utilizador user;

    public Atividade() {
        this.codigo = "";
        this.descricao = "";
        this.data = LocalDate.EPOCH;
        this.duracao = 0;
        this.user = new Utilizador();
    }

    public Atividade(String codigo, String descricao, LocalDate data, int duracao) {
        this.codigo = codigo;
        this.descricao = descricao;
        this.data = data;
        this.duracao = duracao;
    }

    public Atividade(Atividade outro){
        this.codigo = outro.getCodigo();
        this.descricao = outro.getDescricao();
        this.data = outro.getData();
        this.duracao = outro.getDuracao();
        this.user = outro.getUser();
    }
    
    // Getters
    public String getCodigo() {
        return codigo;
    }
    public String getDescricao() {
        return descricao;
    }
    public LocalDate getData() {
        return data;
    }
    public int getDuracao() {
        return duracao;
    }
    public Utilizador getUser() {
        return user;
    }
    // Setters
    public void setCodigo(String codigo) {
        this.codigo = codigo;
    }
    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }
    public void setData(LocalDate data) {
        this.data = data;
    }
    public void setDuracao(int duracao) {
        this.duracao = duracao;
    }
    public void setUser(Utilizador user) {
        this.user = user;
    }

    

    @Override
    public String toString() {
        return "Atividade{" +
                "codigo='" + codigo + '\'' +
                ", descricao='" + descricao + '\'' +
                ", data=" + data +
                ", duracao=" + duracao +
                '}';
    }




    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Atividade atividade = (Atividade) o;
        return this.duracao == atividade.getDuracao()
                && this.codigo.equals(atividade.getCodigo())
                && this.descricao.equals(atividade.getDescricao())
                && this.data.equals(atividade.getData());
    }


    public abstract double calorias();
    public  abstract  Atividade clone();


}