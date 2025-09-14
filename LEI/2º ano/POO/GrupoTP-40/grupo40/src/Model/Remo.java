package Model;

import java.time.LocalDateTime;

import Model.InterfacesAtividades.Distancia;

public class Remo extends Atividade implements Distancia {
    private double distancia;
    private TipoTerreno tipoTerreno;

    // construtores
    /*
     * Construtor vazio
     * Inicializa as variáveis de instância com valores por defeito
     */
    public Remo(){
        super();
        this.distancia = 0;
        this.tipoTerreno = TipoTerreno.PISTA;
    }
    /*
     * Construtor parametrizado
     * @param nome - nome da atividade
     * @param dataRealização - data de realizacao da atividade
     * @param duracao - duracao da atividade em minutos
     * @param user - utilizador que realizou a atividade
     * @param distancia - distancia percorrida
     */
    public Remo(String nome, LocalDateTime dataRealização, long duracao, Utilizador user, double distancia) {
        super(nome, dataRealização, duracao, user);
        this.distancia = distancia;
        this.tipoTerreno = TipoTerreno.PISTA;

    }
    /*
     * Construtor parametrizado - sem utilizador associado, usado para atividades genéricas, deste tipo
     * @param nome - nome da atividade
     * @param dataRealização - data de realizacao da atividade
     * @param duracao - duracao da atividade em minutos
     * @param distancia - distancia percorrida
     */
    public Remo(String nome, LocalDateTime dataRealização, long duracao, double distancia) {
        super(nome, dataRealização, duracao);
        this.distancia = distancia;
        this.tipoTerreno = TipoTerreno.PISTA;

    }
    /*
     * Construtor de cópia
     * @param remo - objeto do tipo Remo
     */
    public Remo(Remo remo){
        super(remo);
        this.distancia = remo.getDistancia();
        this.tipoTerreno = remo.getTipoTerreno();
    }

    // getters
    /*
     * Getter da distancia percorrida pelo utilizador na atividade
     * @return distancia percorrida em metros
     */
    public double getDistancia() {
        return distancia;
    }
    /*
     * Getter do tipo de terreno onde a atividade foi realizada de acordo com o enum TipoTerreno
     * @return tipo de terreno
     */
    public TipoTerreno getTipoTerreno() {
        return tipoTerreno;
    }
    // setters
    /*
     * Setter da distancia percorrida pelo utilizador na atividade
     * @param distancia - distancia percorrida em metros
     */
    public void setDistancia(double distancia) {
        this.distancia = distancia;
    }
    /*
     * Setter do tipo de terreno onde a atividade foi realizada de acordo com o enum TipoTerreno
     * @param tipoTerreno - tipo de terreno
     */
    public void setTipoTerreno(TipoTerreno tipoTerreno) {
        this.tipoTerreno = tipoTerreno;
    }
    /*
     * Clone de Remo
     * @return objeto copiado do tipo Remo
     */
    public Remo clone(){
        return new Remo(this);
    }
    /*
     * Método que verifica se dois objetos são iguais
     * @param o - objeto a comparar
     * @return true se forem iguais, false se não forem
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        Remo remo = (Remo) o;
        return super.equals(remo) &&
                this.distancia == remo.getDistancia() &&
                this.tipoTerreno == remo.getTipoTerreno();
    }
    /*
     * Método que devolve a representação em String de um objeto do tipo Remo
     * @return representação em String de um objeto do tipo Remo
     */
    public String toString() {
        return "Remo{" +
                super.toString() +
                "distancia=" + distancia +
                ", tipoTerreno=" + tipoTerreno +
                ", caloriasGastas=" + calcularCaloriasGastas(getUtilizador()) +
                ", frequanciaCardiacaMedia=" + calcularfrequanciaCardiacaMediaAtividade() +
                "}";
    }

    /*
     * Método que calcula as calorias gastas numa atividade do tipo Remo
     * @param u - utilizador que realizou a atividade
     * @return calorias gastas 
     */
    @Override
    public double calcularCaloriasGastas(Utilizador u) {
        if (u == null) return 0;
        double caloriasGastas = 0;
        double mediaCGporPessoa = getduracaoMin()/60 * 754 * u.getPeso()/84;
        if(u.getGenero()==Genero.Masculino) mediaCGporPessoa *= 1.1;
        caloriasGastas = mediaCGporPessoa*u.getfatorMultiplicativoCalorias();
        caloriasGastas += getDistancia() * 0.1;
        return caloriasGastas;
    }
    /*
     * Método que calcula a frequência cardíaca média durante a atividade do tipo Remo
     * @return frequência cardíaca média do utilizador durante a atividade
     */
    @Override
    public double calcularfrequanciaCardiacaMediaAtividade() {
        if (getUtilizador() == null) return 0;
        double maxFQ = 220 - getUtilizador().idade();
        return ((maxFQ - getUtilizador().calcularfrequanciaCardiacaMediaRepouso()) * 0.6) + getUtilizador().calcularfrequanciaCardiacaMediaRepouso();
    }
	
    
}
