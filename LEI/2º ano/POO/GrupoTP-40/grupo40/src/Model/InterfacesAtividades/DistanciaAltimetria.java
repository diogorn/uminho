package Model.InterfacesAtividades;

import Model.TipoTerreno;

/*
 * Interface que define o comportamento de um objeto do tipo Atividade com caracteristicas de desporto com distancia e altimetria
 */

public interface DistanciaAltimetria {
    double getDistancia();
    double getAltimetria();
    TipoTerreno getTipoTerreno();
    void setDistancia(double distancia);
    void setAltimetria(double altimetria);
    void setTipoTerreno(TipoTerreno tipoTerreno);
    

}
