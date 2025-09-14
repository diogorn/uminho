package Model.InterfacesAtividades;

import Model.TipoTerreno;
/*
 * Interface que define o comportamento de um objeto do tipo Atividade com caracteristicas de desporto com distancia
 */
public interface Distancia {
    // getters
    double getDistancia();
    TipoTerreno getTipoTerreno();
    
    // setters
    void setDistancia(double distancia);
    void setTipoTerreno(TipoTerreno tipoTerreno);

}
