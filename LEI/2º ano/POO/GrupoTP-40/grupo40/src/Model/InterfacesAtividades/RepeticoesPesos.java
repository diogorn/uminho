package Model.InterfacesAtividades;

/*
 * Interface que define os métodos a implementar por um objeto do tipo Atividade com caracteristicas de desporto com repetições e pesos
 */
public interface RepeticoesPesos {
    double getPeso();
    void setPeso(double peso);
    int getSeries();
    void setSeries(int series);
    int getRepeticoes();
    void setRepeticoes(int repeticoes);

}
