
package Model;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

import Model.InterfacesAtividades.*;

import java.util.UUID;

public class PlanoTreino implements Serializable{

    private String id;
    private LocalDate realizacao;
    private Map<String, Atividade> atividades;
    private PeriodicidadePlano periodicidade;

    /*
     * Construtor vazio
     * Inicializa as variáveis de instância com valores por defeito
     */
    public PlanoTreino() {  
        this.id = geraId();
        this.realizacao = LocalDate.now();
        this.atividades = new HashMap<>();
        this.periodicidade = PeriodicidadePlano.Outro;
    }
    /*
     * Construtor com argumentos
     * @param realizacao - data de realização do plano de treino
     * @param periodicidade - periodicidade do plano de treino
     */
    public PlanoTreino(LocalDate realizacao, PeriodicidadePlano periodicidade) {
        this.id = geraId();
        this.realizacao = realizacao;
        this.atividades = new HashMap<>();
        this.periodicidade = periodicidade;
    }
    /*
     * Construtor com argumentos
     * @param realizacao - data de realização do plano de treino
     * @param atividades - atividades do plano de treino
     * @param periodicidade - periodicidade do plano de treino
     */
    public PlanoTreino(LocalDate realizacao, Map<String, Atividade> atividades, PeriodicidadePlano periodicidade) {
        this.id = geraId();
        this.realizacao = realizacao;
        this.atividades = atividades.entrySet().stream().collect(Collectors.toMap(k->k.getKey(), v-> v.getValue().clone()));
        this.periodicidade = periodicidade;
    }

    /*
     * Construtor de cópia
     * @param planoTreino - objeto do tipo PlanoTreino
     */
    public PlanoTreino(PlanoTreino planoTreino) {
        this.id = geraId();
        this.realizacao = planoTreino.getRealizacao();
        this.atividades = planoTreino.getAtividades();
        this.periodicidade = planoTreino.getPeriodicidade();
    }

    // getters
    /*
     * Método que gera um id para o plano de treino
     * @return id gerado
     */
    public String geraId(){
        return UUID.randomUUID().toString();
    }
    /*
     * Método que devolve o id do plano de treino 
     * @return id do plano de treino
     */
    public String getId() {
        return id;
    }
    /*
     * Método que devolve a data de realização do plano de treino
     * @return data de realização do plano de treino
     */
    public LocalDate getRealizacao() {
        return realizacao;
    }
    /*
     * Método que devolve as atividades do plano de treino
     * @return clone atividades do plano de treino
     */
    public Map<String, Atividade> getAtividades() {
        return atividades.entrySet().stream().collect(Collectors.toMap(k->k.getKey(), v-> v.getValue().clone()));
    }
    /*
     * Método que devolve a periodicidade do plano de treino
     * @return periodicidade do plano de treino
     */
    public PeriodicidadePlano getPeriodicidade() {
        return periodicidade;
    }

    // setters
    /*
     * Setter da data de realização do plano de treino
     * @param realizacao - data de realização do plano de treino
     */
    public void setRealizacao(LocalDate realizacao) {
        this.realizacao = realizacao;
    }
    /*
     * Setter das atividades do plano de treino
     * @param atividades - map atividades do plano de treino
     */
    public void setAtividades(Map<String, Atividade> atividades) {
        this.atividades = atividades.entrySet().stream().collect(Collectors.toMap(k->k.getKey(), v-> v.getValue().clone()));
    }
    /*
     * Setter da periodicidade do plano de treino
     * @param periodicidade - periodicidade do plano de treino
     */
    public void setPeriodicidade(PeriodicidadePlano periodicidade) {
        this.periodicidade = periodicidade;
    }

    /*
     * Clone de um plano de treino
     * @return cópia do plano de treino
     */
    public PlanoTreino clone() {
        return new PlanoTreino(this);
    }

    /*
     * Método que devolve a representação em String de um plano de treino
     * @return representação em String de um plano de treino
     */
    public String toString() {
       return "PlanoTreino{" +
               "id=" + getId() +
               ", realizacao=" + getRealizacao() +
               ", atividades=" + getAtividades() +
                ", periodicidade=" + getPeriodicidade() +
               '}';
    }


    /*
     * Método que verifica se um objeto é igual a um plano de treino
     * @param o - objeto a ser comparado
     * @return true se forem iguais, false se não forem
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        PlanoTreino planoTreino = (PlanoTreino) o;
        return this.id.equals(planoTreino.getId()) &&
                this.realizacao.equals(planoTreino.getRealizacao()) &&
                this.atividades.equals(planoTreino.getAtividades()) &&
                this.periodicidade.equals(planoTreino.getPeriodicidade());
    }

    // metodos maps atividades 
    /*
     * Método que adiciona uma atividade (clonada) ao plano de treino
     * @param atividade - atividade a ser adicionada
     */
    public void addAtividade(Atividade atividade){
        this.atividades.put(atividade.getId(), atividade.clone());
    }
    /*
     * Método que remove uma atividade do plano de treino
     * @param atividade - atividade a ser removida
     */
    public void removeAtividade(Atividade atividade){
        this.atividades.remove(atividade.getId());
    }
    /*
     * Método que verifica se um plano de treino tem atividades do tipo Hard
     * @return true se tiver atividades do tipo Hard, false se não tiver
     */
    public Boolean planoTemHards (){
        return this.atividades.values().stream().anyMatch(a -> a instanceof Hard);
    }




}