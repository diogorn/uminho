package Model;

import java.time.LocalDateTime;

import Model.InterfacesAtividades.*;

public class Btt extends Atividade implements DistanciaAltimetria, Hard {

    private boolean hard;
    private int dificuldade; // 1-5
    private double distancia;
    private double altimetria;
    private TipoTerreno tipoTerreno;

    /*
     * Construtor vazio
     */
    public Btt(){
        super();
        this.hard = true;
        this.dificuldade = 0;
        this.distancia = 0;
        this.altimetria = 0;
        this.tipoTerreno = TipoTerreno.OUTRO;
    }

    /*
     * Construtor com argumentos
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param user - utilizador que realizou a atividade
     * @param distancia - distancia percorrida
     * @param altimetria - altimetria acumulada
     * @param tipoTerreno - tipo de terreno
     * @param dificuldade - dificuldade da atividade
     */
    public Btt(String nome, LocalDateTime dataRealização, long duracao, Utilizador user, double distancia, double altimetria, TipoTerreno tipoTerreno, int dificuldade) {
        super(nome, dataRealização, duracao, user);
        this.hard = true;
        this.dificuldade = dificuldade;
        this.distancia = distancia;
        this.altimetria = altimetria;
        this.tipoTerreno = tipoTerreno;
    }

    /*
     * Construtor com argumentos - sem utilizador associado, usado para atividades genéricas, deste tipo
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param distancia - distancia percorrida
     * @param altimetria - altimetria acumulada
     * @param tipoTerreno - tipo de terreno
     * @param dificuldade - dificuldade da atividade
     */
    public Btt(String nome, LocalDateTime dataRealização, long duracao, double distancia, double altimetria, TipoTerreno tipoTerreno, int dificuldade) {
        super(nome, dataRealização, duracao);
        this.hard = true;
        this.dificuldade = dificuldade;
        this.distancia = distancia;
        this.altimetria = altimetria;
        this.tipoTerreno = tipoTerreno;
    }

    /*
     * Construtor de cópia
     * @param btt - objeto do tipo Btt
     */
    public Btt(Btt btt){
        super(btt);
        this.hard = btt.isHard();
        this.dificuldade = btt.getDificuldade();
        this.distancia = btt.getDistancia();
        this.altimetria = btt.getAltimetria();
        this.tipoTerreno = btt.getTipoTerreno();
    }
    
    /*
     * Getter hard
     * @return hard - true se a atividade for hard, false caso contrário
     */
    public boolean isHard() {
        return hard;
    }
    /*
     * Getter dificuldade
     * @return dificuldade - dificuldade da atividade (1-5)
     */
    public int getDificuldade() {
        return dificuldade;
    }
    /*
     * Getter distancia
     * @return distancia - distancia percorrida
     */
    public double getDistancia() {
        return distancia;
    }
    /*
     * Getter altimetria
     * @return altimetria - altimetria acumulada
     */
    public double getAltimetria() {
        return altimetria;
    }
    /*
     * Getter tipo de terreno
     * @return tipoTerreno - tipo de terreno onde a atividade foi realizada, de acordo com a enumeração TipoTerreno
     */
    public TipoTerreno getTipoTerreno() {
        return tipoTerreno;
    }
    /*
     * Setter hard
     * @param hard - true se a atividade for hard, false caso contrário
     */
    public void setHard(boolean hard) {
        this.hard = hard;
    }
    /*
     * Setter dificuldade
     * @param dificuldade - dificuldade da atividade (1-5)
     */
    public void setDificuldade(int dificuldade) {
        this.dificuldade = dificuldade;
    }
    /*
     * Setter distancia
     * @param distancia - distancia percorrida na atividade em metros
     */
    public void setDistancia(double distancia) {
        this.distancia = distancia;
    }
    /*
     * Setter altimetria
     * @param altimetria - altimetria acumulada na atividade em metros
     */
    public void setAltimetria(double altimetria) {
        this.altimetria = altimetria;
    }
    /*
     * Setter tipo de terreno
     * @param tipoTerreno - tipo de terreno onde a atividade foi realizada, de acordo com a enumeração TipoTerreno
     */
    public void setTipoTerreno(TipoTerreno tipoTerreno) {
        this.tipoTerreno = tipoTerreno;
    }
    
    /*
     * Clone de Btt
     * @return cópia do objeto do tipo Btt
     */
    public Btt clone(){
        return new Btt(this);
    }

    /*
     * toString de Btt
     * @return String com informações sobre a atividade Btt
     */
    public String toString() {
        return "Btt{" +
                super.toString() +
                "hard=" + isHard() +
                ", dificuldade=" + getDificuldade() +
                ", distancia=" + getDistancia() +
                ", altimetria=" + getAltimetria() +
                ", tipoTerreno=" + getTipoTerreno() +
                '}';
    }

    /*
     * equals de Btt
     * @param o - objeto
     * @return true se o objeto for igual ao objeto do tipo Btt, false se o objeto for diferente do objeto do tipo Btt
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Btt)) return false;
        if (!super.equals(o)) return false;
        Btt btt = (Btt) o;
        return isHard() == btt.isHard() &&
                getDificuldade() == btt.getDificuldade() &&
                Double.compare(btt.getDistancia(), getDistancia()) == 0 &&
                Double.compare(btt.getAltimetria(), getAltimetria()) == 0 &&
                getTipoTerreno() == btt.getTipoTerreno();
    }

    /*
     * Método que calcula as calorias gastas numa atividade de BTT
     * @param utilizador - utilizador que realizou a atividade
     * @return calorias gastas na atividade pelo utilizador
     */
    @Override
    public double calcularCaloriasGastas(Utilizador utilizador) {
        if (utilizador == null) return 0;
        final double MET = 8.0; // Taxa metabólica específica para BTT
        return MET * utilizador.getPeso() * this.getduracaoMin() * (getDificuldade()/10);
       

    }

    /*
     * Método que calcula a frequência cardíaca média numa atividade de BTT
     * @return frequência cardíaca média do utilizador durante a atividade
     */
    @Override
    public double calcularfrequanciaCardiacaMediaAtividade() {
        if (this.getUtilizador() == null) return 0;
        double maxFQ = 220 - getUtilizador().idade();
        return ((maxFQ - getUtilizador().calcularfrequanciaCardiacaMediaRepouso()) * 0.5) + getUtilizador().calcularfrequanciaCardiacaMediaRepouso();
    }

       




    
}
