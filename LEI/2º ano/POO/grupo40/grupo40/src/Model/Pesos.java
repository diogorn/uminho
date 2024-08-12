package Model;

import java.time.LocalDateTime;

import Model.InterfacesAtividades.RepeticoesPesos;

public class Pesos extends Atividade implements RepeticoesPesos {
    private double peso;
    private int repeticoes;
    private int series;

    /*
     * Construtor vazio
     * Inicializa as variáveis de instância com valores por defeito
     */
    public Pesos(){
        super();
        this.peso = 0;
        this.repeticoes = 0;
        this.series = 0;
    }
    /*
     * Construtor com argumentos
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param user - utilizador que realizou a atividade
     * @param peso - peso levantado em kg
     * @param repeticoes - numero de repetições
     * @param series - numero de series

     */
    public Pesos(String nome, LocalDateTime dataRealização, long duracao, Utilizador user, double peso, int repeticoes, int series) {
        super(nome, dataRealização, duracao, user);
        this.peso = peso;
        this.repeticoes = repeticoes;
        this.series = series;
    }
    /*
     * Construtor com argumentos - sem utilizador associado, usado para atividades genéricas, deste tipo
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param peso - peso levantado em kg
     * @param repeticoes - numero de repetições
     * @param series - numero de series
     */
    public Pesos(String nome, LocalDateTime dataRealização, long duracao, double peso, int repeticoes, int series) {
        super(nome, dataRealização, duracao);
        this.peso = peso;
        this.repeticoes = repeticoes;
        this.series = series;
    }
    /*
     * Construtor de cópia
     * @param pesos - objeto do tipo Pesos
     */
    public Pesos(Pesos pesos){
        super(pesos);
        this.peso = pesos.getPeso();
        this.repeticoes = pesos.getRepeticoes();
        this.series = pesos.getSeries();
    }

    /*
     * Método que devolve o peso levantado
     * @return peso levantado em kg
     */
    public double getPeso() {
        return peso;
    }
    /*
     * Método que devolve o número de repetições
     * @return número de repetições
     */
    public int getRepeticoes() {
        return repeticoes;
    }
    /*
     * Método que devolve o número de series
     * @return número de series
     */
    public int getSeries() {
        return series;
    }
    /*
     * Método que define o peso levantado
     * @param peso - peso levantado em kg
     */
    public void setPeso(double peso) {
        this.peso = peso;
    }
    /*
     * Método que define o número de repetições
     * @param repeticoes - número de repetições
     */
    public void setRepeticoes(int repeticoes) {
        this.repeticoes = repeticoes;
    }
    /*
     * Método que define o número de series
     * @param series - número de series
     */
    public void setSeries(int series) {
        this.series = series;
    }
    /*
     * Método que devolve uma cópia da atividade do tipo Pesos
     * @return cópia da atividade
     */
    public Pesos clone(){
        return new Pesos(this);
    }
    /*
     * toString de Pesos
     * @return String com informações sobre a atividade Pesos
     */
    public String toString() {
        return "Pesos{" +
                super.toString() +
                "peso=" + peso +
                ", repeticoes=" + repeticoes +
                ", series=" + series +
                ", caloriasGastas=" + calcularCaloriasGastas(getUtilizador()) +
                ", frequanciaCardiacaMedia=" + calcularfrequanciaCardiacaMediaAtividade() +
                "}";
    }
    /*
     * equals de Pesos
     * @param o - objeto
     * @return true se forem iguais, false se forem diferentes
     */
    public boolean equals(Object o){
        if (this == o) return true;
        if (!(o instanceof Pesos)) return false;
        if (!super.equals(o)) return false;
        Pesos p = (Pesos) o;
        return super.equals(p) &&
                this.peso == p.getPeso() &&
                this.repeticoes == p.getRepeticoes() &&
                this.series == p.getSeries();
    }

    /*
     * Método que calcula as calorias gastas numa atividade do tipo Pesos
     * @param u - utilizador que realizou a atividade
     * @return calorias gastas durante o levantamento de pesos pelo utilizador
     */
    @Override 
    public double calcularCaloriasGastas(Utilizador u) {
        if (u == null) return 0;
        double caloriasGastas = 0;
        double mediaCGporPessoa = getPeso() + (getPeso() * getRepeticoes())*getSeries() / 300.0; 
        caloriasGastas = mediaCGporPessoa * u.getfatorMultiplicativoCalorias();
        return caloriasGastas; 
    }
    /*
     * Método que calcula a frequência cardíaca média durante a atividade do tipo Pesos
     * @return frequência cardíaca média do utilizador durante a atividade
     */
    public double calcularfrequanciaCardiacaMediaAtividade() {
        if (getUtilizador() == null) return 0;
        double maxFQ = 220 - getUtilizador().idade();
        return ((maxFQ - getUtilizador().calcularfrequanciaCardiacaMediaRepouso()) * 0.5) + getUtilizador().calcularfrequanciaCardiacaMediaRepouso();
    }
    
 
}