package Model;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.UUID;

public abstract class Atividade implements Serializable {

    private String id; 
    private String nome;

    private LocalDateTime dataRealização;
    private long duracaoMin;
    private double frequanciaCardiacaMedia;

    private Utilizador utilizador;
    


    /*
     * Construtor vazio
     */
    public Atividade(){
        this.id = geraID();
        this.nome = "";
        this.dataRealização = LocalDateTime.now();
        this.frequanciaCardiacaMedia = 0;
        this.duracaoMin = 0;
    }

    /*
     * Construtor com argumentos
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracaoMin - duração da atividade em minutos
     * @param utilizador - utilizador que realizou a atividade
     */
    public Atividade(String nome, LocalDateTime dataRealização, long duracaoMin, Utilizador utilizador) {
        this.id = geraID();
        this.nome = nome;
        this.dataRealização = dataRealização;
        this.duracaoMin = duracaoMin;
        this.frequanciaCardiacaMedia = calcularfrequanciaCardiacaMediaAtividade();
        this.utilizador = utilizador.clone();
    }
    
    /*
     * Construtor com argumentos - sem utilizador associado, usado para atividades genéricas, deste tipo
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracaoMin - duração da atividade em minutos
     */
    public Atividade(String nome, LocalDateTime dataRealização, long duracaoMin) {
        this.id = geraID();
        this.nome = nome;
        this.dataRealização = dataRealização;
        this.duracaoMin = duracaoMin;
        this.frequanciaCardiacaMedia = calcularfrequanciaCardiacaMediaAtividade();
    }

    /*
     * Construtor de cópia
     * @param atividade - objeto do tipo Atividade
     */
    public Atividade(Atividade atividade){
        this.id = geraID();
        this.nome = atividade.getNome();
        this.dataRealização = atividade.getDataRealização();
        this.duracaoMin = atividade.getduracaoMin();
        this.frequanciaCardiacaMedia = atividade.getFrequanciaCardiacaMedia();
        this.utilizador = atividade.getUtilizador() == null ? null : atividade.getUtilizador().clone();
    }

    /*
     * Getter id
     * @return id da atividade
     */ 
    public String getId() {
        return id;
    }
    /*
     * Getter nome
     * @return nome da atividade
     */
    public String getNome() {
        return nome;
    }
    /*
     * Getter data de realização da atividade
     * @return data de realização da atividade
     */
    public LocalDateTime getDataRealização() {
        return dataRealização;
    }
    /*
     * Getter duração da atividade
     * @return duração da atividade em minutos
     */
    public long getduracaoMin() {
        return duracaoMin;
    }
    /*
     * Getter frequência cardíaca 
     * @return frequência cardíaca média durante a atividade
     */
    public double getFrequanciaCardiacaMedia() {
        return frequanciaCardiacaMedia;
    }
    /*
     * Getter utilizador 
     * @return utilizador que realizou a atividade
     */
    public Utilizador getUtilizador() {
        return utilizador;
    }

    /*
     * Setter id
     * @param id - id da atividade
     */
    public void setId(String id) {
        this.id = id;
    }
    /*
     * Setter nome
     * @param nome - nome da atividade
     */
    public void setNome(String nome) {
        this.nome = nome;
    }
    /*
     * Setter data de realização da atividade
     * @param dataRealização - data de realização da atividade
     */
    public void setDataRealização(LocalDateTime dataRealização) {
        this.dataRealização = dataRealização;
    }
    /*
     * Setter duração da atividade
     * @param duracaoMin - duração da atividade em minutos
     */
    public void setduracaoMin(long duracaoMin) {
        this.duracaoMin = duracaoMin;
    }
    /*
     * Setter frequência cardíaca 
     * @param frequanciaCardiacaMedia - frequência cardíaca média durante a atividade
     */
    public void setFrequanciaCardiacaMedia(double frequanciaCardiacaMedia) {
        this.frequanciaCardiacaMedia = frequanciaCardiacaMedia;
    }
    /*
     * Setter utilizador 
     * @param utilizador - utilizador que realizou a atividade
     */
    public void setUtilizador(Utilizador utilizador) {
        this.utilizador = utilizador.clone();
    }
    /*
     * Método que gera um id único para a atividade
     * @return id único
     */
    public String geraID(){
        return UUID.randomUUID().toString();
    }
    
    /*
     * Método equals que verifica se a atividade é igual a um determinado objeto
     * @param o - objeto a comparar
     * @return true se o objeto for igual à atividade, false se o objeto for diferente da atividade
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Atividade atividade = (Atividade) o;
        return this.id == atividade.getId()
                && this.getNome().equals(atividade.getNome())
                && this.getDataRealização().equals(atividade.getDataRealização())
                && this.getduracaoMin() == atividade.getduracaoMin()
                && this.getFrequanciaCardiacaMedia() == atividade.getFrequanciaCardiacaMedia();
    }

    /*
     * Método que transforma a atividade numa string
     * @return string com a informação da atividade
     */
    @Override
    public String toString(){
        return "Atividade{" +
                "id="+ getId() +
                ", nome='" + getNome() + '\'' +
                ", dataRealização=" + getDataRealização() +
                ", duracaoMin=" + getduracaoMin() +
                ", frequanciaCardiacaMedia=" + getFrequanciaCardiacaMedia() +
                '}';
    }
    
    
    /*
     * Método abstrato de clone da atividade
     */
    public abstract Atividade clone();
    /*
     * Método abstrato de cálculo de calorias gastas
     * @param utilizador - utilizador que realizou a atividade
     * @return calorias gastas
     */
    public abstract double calcularCaloriasGastas(Utilizador utilizador);
    /*
     * Método abstrato de cálculo de frequência cardíaca média
     * @return frequência cardíaca média do utilizador durante a atividade
     */
    public abstract double calcularfrequanciaCardiacaMediaAtividade();

 

    

}
