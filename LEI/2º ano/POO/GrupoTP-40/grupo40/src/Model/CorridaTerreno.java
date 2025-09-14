package Model;

import java.time.LocalDateTime;

import Model.InterfacesAtividades.DistanciaAltimetria;

public class CorridaTerreno extends Atividade implements DistanciaAltimetria{

    private double distancia;
    private double altimetria;
    private TipoTerreno tipoTerreno;

    /*
     * Construtor vazio
     */
    public CorridaTerreno(){
        super();
        this.distancia = 0;
        this.altimetria = 0;
        this.tipoTerreno = TipoTerreno.OUTRO;
    }

    /*
     * Construtor parametrizado
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param user - utilizador que realizou a atividade
     * @param distancia - distancia percorrida
     * @param altimetria - altimetria acumulada
     * @param tipoTerreno - tipo de terreno
     */
    public CorridaTerreno(String nome, LocalDateTime dataRealização, long duracao, Utilizador user, double distancia, double altimetria, TipoTerreno tipoTerreno) {
        super(nome, dataRealização, duracao, user);
        this.distancia = distancia;
        this.altimetria = altimetria;
        this.tipoTerreno = tipoTerreno;
    }
    /*
     * Construtor parametrizado - sem utilizador associado, usado para atividades genéricas, deste tipo
     * @param nome - nome da atividade
     * @param dataRealização - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param distancia - distancia percorrida
     * @param altimetria - altimetria acumulada
     * @param tipoTerreno - tipo de terreno
     */
    public CorridaTerreno(String nome, LocalDateTime dataRealização, long duracao, double distancia, double altimetria, TipoTerreno tipoTerreno) {
        super(nome, dataRealização, duracao);
        this.distancia = distancia;
        this.altimetria = altimetria;
        this.tipoTerreno = tipoTerreno;
    }
    
    /*
     * Construtor de cópia
     * @param corrida - objeto do tipo CorridaTerreno
     */
    public CorridaTerreno(CorridaTerreno corrida){
        super(corrida);
        this.distancia = corrida.getDistancia();
        this.altimetria = corrida.getAltimetria();
        this.tipoTerreno = corrida.getTipoTerreno();
    }

    /*
     * Getter Distancia
     * @return distancia percorrida em metros
     */
    public double getDistancia() {
        return distancia;
    }
    /*
     * Getter Altimetria
     * @return altimetria acumulada em metros
     */
    public double getAltimetria() {
        return altimetria;
    }
    /*
     * Getter Tipo de Terreno
     * @return tipo de terreno onde a atividade foi realizada de acordo com a enumeração TipoTerreno
     */
    public TipoTerreno getTipoTerreno() {
        return tipoTerreno;
    }
    
    /*
     * Setter Distancia
     * @param distancia - distancia percorrida em metros
     */
    public void setDistancia(double distancia) {
        this.distancia = distancia;
    }
    /*
     * Setter Altimetria
     * @param altimetria - altimetria acumulada em metros
     */
    public void setAltimetria(double altimetria) {
        this.altimetria = altimetria;
    }
    /*
     * Setter Tipo de Terreno
     * @param tipoTerreno - tipo de terreno onde a atividade foi realizada de acordo com a enumeração TipoTerreno
     */
    public void setTipoTerreno(TipoTerreno tipoTerreno) {
        this.tipoTerreno = tipoTerreno;
    }
    
    /*
     * Clone de CorridaTerreno
     * @return cópia do objeto do tipo CorridaTerreno
     */
    public Atividade clone(){
        return new CorridaTerreno(this);
    }
    /*
     * toString de CorridaTerreno
     * @return String com informações sobre a atividade CorridaTerreno
     */
    public String toString(){
        return "CorridaTerreno{"+
                super.toString() + 
                ", Distancia=" + getDistancia() + 
                ", Altimetria=" + getAltimetria() + 
                ", Tipo de Terreno=" + getTipoTerreno() +
                ", Calorias gastas=" + calcularCaloriasGastas(getUtilizador()) +
                ", Frequencia Cardiaca Media=" + calcularfrequanciaCardiacaMediaAtividade() +
            "}";

    }
    
    /*
     * equals de CorridaTerreno
     * @param o - objeto
     * @return true se forem iguais, false caso contrário
     */
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || this.getClass() != o.getClass()) return false;
        CorridaTerreno corrida = (CorridaTerreno) o;
        return super.equals(corrida) &&
                this.distancia == corrida.getDistancia() &&
                this.altimetria == corrida.getAltimetria() &&
                this.tipoTerreno.equals(corrida.getTipoTerreno());
    }
   
    /*
     * Método que calcula as calorias gastas numa atividade do tipo CorridaTerreno
     * @param u - utilizador que realizou a atividade
     * @return calorias gastas pelo utilizador na atividade
     */
    @Override
    public double calcularCaloriasGastas(Utilizador u) {
        if (u == null) return 0;
        double caloriasGastas = 0;
        double mediaCGporPessoa = (getDistancia() / 1000.0) * 100 * u.getPeso() / 70.0;
        if(u.getGenero()==Genero.Masculino) mediaCGporPessoa *= 1.1;
        caloriasGastas = mediaCGporPessoa * u.getfatorMultiplicativoCalorias();
        caloriasGastas += getDistancia() * 0.1 + getAltimetria() * 0.13;
        switch (getTipoTerreno()) {
            case PISTA:
                caloriasGastas *= 1;
                break;
            case ESTRADA:
                caloriasGastas *= 1.01;
                break;
            case TRILHO:
                caloriasGastas *= 1.1;
                break;
            case MONTE:
                caloriasGastas *= 1.2;
                break;
            default:
                caloriasGastas *= 1;
                break;
        }
        return caloriasGastas/2;
    }

    /*
     * Método que calcula a frequência cardíaca média numa atividade do tipo CorridaTerreno
     * @return frequência cardíaca média do utilizador durante a atividade
     */
    @Override
    public double calcularfrequanciaCardiacaMediaAtividade() {
        if (getUtilizador() == null) return 0;
        double maxFQ = 220 - getUtilizador().idade();
        return ((maxFQ - getUtilizador().calcularfrequanciaCardiacaMediaRepouso()) * 0.5) + getUtilizador().calcularfrequanciaCardiacaMediaRepouso();
    }
    

    
}