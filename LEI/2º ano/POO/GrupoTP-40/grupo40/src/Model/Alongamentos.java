package Model;

import java.time.LocalDateTime;

import Model.InterfacesAtividades.Repeticoes;

/*
 * Alongamentos é um tipo de Atividade que, para além de caracteristicas próprias, herda as caracteristicas de uma Atividade e implementa métodos da interface Repeticoes
 */

public class Alongamentos extends Atividade implements Repeticoes{
    private int repeticoes;
    private int series;
    private BodyPart parteCorpo;

    /*
    * Construtor vazio
    */
    public Alongamentos(){
        super();
        this.repeticoes = 0;
        this.series = 0;
        this.parteCorpo = BodyPart.OUTRO;
    }
    /*
     * Construtor com argumentos
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param user - utilizador que realizou a atividade
     * @param repeticoes - numero de repetições 
     * @param series - numero de series
     * @param parteCorpo - parte do corpo que foi exercitada
     */
    public Alongamentos(String nome, LocalDateTime dataRealização, long duracao, Utilizador user, int repeticoes, int series, BodyPart parteCorpo) {
        super(nome, dataRealização, duracao, user);
        this.repeticoes = repeticoes;
        this.series = series;
        this.parteCorpo = parteCorpo;
    }

    /*
     * Construtor com argumentos - sem utilizador associado, usado para atividades genéricas, deste tipo
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param repeticoes - numero de repetições 
     * @param series - numero de series
     * @param parteCorpo - parte do corpo que foi exercitada
     */
    public Alongamentos(String nome, LocalDateTime dataRealização, long duracao, int repeticoes, int series, BodyPart parteCorpo) {
        super(nome, dataRealização, duracao);
        this.repeticoes = repeticoes;
        this.series = series;
        this.parteCorpo = parteCorpo;
    }
    /*
     * Construtor de cópia
     * @param alongamentos - objeto do tipo Alongamentos
     */
    public Alongamentos(Alongamentos alongamentos){
        super(alongamentos);
        this.repeticoes = alongamentos.getNRepeticoes();
        this.series = alongamentos.getNSeries();
        this.parteCorpo = alongamentos.getParteCorpo();
    }

    /*
     * Getter número de repetições
     * @return número de repetições
     */
    public int getNRepeticoes() {
        return repeticoes;
    }
    /*
     * Getter número de series
     * @return número de series
     */
    public int getNSeries() {
        return series;
    }
    /*
     * Getter parte do corpo
     * @return parte do corpo
     */
    public BodyPart getParteCorpo() {
        return parteCorpo;
    }
    /*
     * Setter número de repetições
     * @param repeticoes - número de repetições
     */
    public void setNRepeticoes(int repeticoes) {
        this.repeticoes = repeticoes;
    }
    /*
     * Setter número de series
     * @param series - número de series
     */
    public void setNSeries(int series) {
        this.series = series;
    }
    /*
     * Setter parte do corpo
     * @param parteCorpo - parte do corpo
     */
    public void setParteCorpo(BodyPart parteCorpo) {
        this.parteCorpo = parteCorpo;
    }
    /*
     * Clone de Alongamentos
     * @return cópia do objeto do tipo Alongamentos 
     */
    public Alongamentos clone(){
        return new Alongamentos(this);
    }
    /*
     * toString de Alongamentos
     * @return String com informações sobre a atividade Alongamentos
     */
    public String toString() {
        return "Alongamentos{" +
                super.toString() +
                "repeticoes=" + getNRepeticoes() +
                ", series=" + getNSeries() +
                ", parteCorpo=" + getParteCorpo() +
                ", caloriasGastas=" + calcularCaloriasGastas(getUtilizador()) +
                ", frequanciaCardiacaMedia=" + calcularfrequanciaCardiacaMediaAtividade() +
                "}";
    }
    /*
     * equals de Alongamentos
     * @param o - objeto
     * @return true se o objeto for igual ao objeto do tipo Alongamentos, false se o objeto for diferente do objeto do tipo Alongamentos
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Alongamentos)) return false;
        if (!super.equals(o)) return false;
        Alongamentos a = (Alongamentos) o;
        return  super.equals(a) &&
                this.repeticoes == a.getNRepeticoes() &&
                this.series == a.getNSeries() &&
                this.parteCorpo == a.getParteCorpo();
    }
    /*
     * Método que calcula as calorias gastas numa atividade do tipo Alongamentos
     * @param utilizador - utilizador que realizou a atividade
     * @return calorias gastas
     */
    @Override
    public double calcularCaloriasGastas(Utilizador utilizador) {
        if (utilizador == null) return 0;

        double mediaCGporPessoa = (getNRepeticoes() * getNSeries() * 0.5) * (utilizador.getPeso() / 70.0) * (utilizador.idade() / 30.0);

        double caloriasGastas = mediaCGporPessoa * utilizador.getfatorMultiplicativoCalorias();
        if(utilizador.getGenero()==Genero.Masculino) caloriasGastas *= 1.1;
        switch (getParteCorpo()) {
            case SUPERIORES:
                caloriasGastas *= 0.9;
                break;
            case INFERIORES:
                caloriasGastas *= 1.1;
                break;
            case TRONCO:
                caloriasGastas *= 1.0;
                break;
            default:
                break;
        }
        return caloriasGastas;
    }
    /*
     * Método que calcula a frequência cardíaca média numa atividade do tipo Alongamentos
     * @return frequência cardíaca média do utilizador durante a atividade
     */
    @Override
    public double calcularfrequanciaCardiacaMediaAtividade() {
        if (getUtilizador() == null) return 0;
        double maxFQ = 220 - getUtilizador().idade();
        return ((maxFQ - getUtilizador().calcularfrequanciaCardiacaMediaRepouso()) * 0.7) + getUtilizador().calcularfrequanciaCardiacaMediaRepouso();
    }
   
}
