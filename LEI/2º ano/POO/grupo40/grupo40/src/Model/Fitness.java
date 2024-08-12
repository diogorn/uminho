package Model;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import Model.InterfacesAtividades.Distancia;
import Model.InterfacesAtividades.DistanciaAltimetria;

public class Fitness implements Serializable{

    private String nomeGinasio;
    private LocalDateTime data; 

    private Map<String, Utilizador> utilizadoresMap; // id -> utilizador
    
    private List<Atividade> atividades;  // atividades pré-definidas no ginásio
    private List<PlanoTreino> planosTreino; // planos de treino pré-definidos no ginásio

    private List<Comparator<Utilizador>> comparatorsEstatisticasUser;

    /*
     * Construtor vazio
     */
    public Fitness() {
        this.nomeGinasio = "Ginasio";
        this.data = LocalDateTime.now();
        this.utilizadoresMap = new HashMap<>();
        this.atividades = new ArrayList<>();
        this.planosTreino = new ArrayList<>();
        this.comparatorsEstatisticasUser = new ArrayList<>();
    }
    
    /*
     * Construtor parametrizado
     * @param nomeGinasio - nome do ginásio
     * @param data - data de criação do ginásio
     * @param utilizadoresMap - mapa de utilizadores registados no ginásio
     * @param atividades - lista de atividades pré-definidas no ginásio
     * @param planosTreino - lista de planos de treino pré-definidos no ginásio
     */
    public Fitness(String nomeGinasio,LocalDateTime data, Map<String, Utilizador> utilizadoresMap, List<Atividade> atividades, List<PlanoTreino> planosTreino) {
        this.nomeGinasio = nomeGinasio;
        this.data = data;
        this.utilizadoresMap = utilizadoresMap.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().clone()));
        this.atividades = atividades.stream().map(Atividade::clone).collect(Collectors.toList());
        this.planosTreino = planosTreino.stream().map(PlanoTreino::clone).collect(Collectors.toList());
        this.comparatorsEstatisticasUser = new ArrayList<>();
    }

    /*
     * Construtor de cópia
     * @param f - objeto do tipo Fitness
     */
    public Fitness(Fitness f) {
        this.nomeGinasio = f.getNomeGinasio();
        this.data = f.getDataGin();
        this.utilizadoresMap = f.getUtilizadoresMap().entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().clone()));
        this.atividades = f.getAtividades().stream().map(Atividade::clone).collect(Collectors.toList());
        this.planosTreino = f.getPlanosTreino().stream().map(PlanoTreino::clone).collect(Collectors.toList());
        this.comparatorsEstatisticasUser = new ArrayList<>();
    }

    /*
     * Getter do nome do ginásio
     * @return nome do ginásio
     */
    public String getNomeGinasio() {
        return this.nomeGinasio;
    }
    /*
     * Getter da data da simulação 
     * @return data da simulação
     */
    public LocalDateTime getDataGin() {
        return this.data;
    }
    /*
     * Getter do mapa de utilizadores
     * @return de clome do mapa de utilizadores registados no ginásio 
     */
    public Map<String, Utilizador> getUtilizadoresMap() {
        return this.utilizadoresMap.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().clone()));
    }
    /*
     * Getter das atividades pré-definidas
     * @return lista de atividades pré-definidas no ginásio
     */
    public List<Atividade> getAtividades() {
        return this.atividades.stream().map(Atividade::clone).collect(Collectors.toList());
    }
    /*
     * Getter dos planos de treino pré-definidos
     * @return lista de planos de treino pré-definidos no ginásio
     */
    public List<PlanoTreino> getPlanosTreino() {
        return this.planosTreino.stream().map(PlanoTreino::clone).collect(Collectors.toList());
    }

    /*
     * Setter do nome do ginásio
     * @param nomeGinasio - nome do ginásio
     */
    public void setNomeGinasio(String nomeGinasio) {
        this.nomeGinasio = nomeGinasio;
    }
    /*
     * Setter da data da simulação
     * @param data - data da simulação
     */
    public void setDataGin(LocalDateTime data) {
        this.data = data;
    }
    /*
     * Setter do mapa de utilizadores
     * @param utilizadoresMap - mapa de utilizadores registados no ginásio
     */
    public void setUtilizadoresMap(Map<String, Utilizador> utilizadoresMap) {
        this.utilizadoresMap = utilizadoresMap.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().clone()));
    }
    /*
     * Setter das atividades pré-definidas
     * @param atividades - lista de atividades pré-definidas no ginásio
     */
    public void setAtividades(List<Atividade> atividades) {
        this.atividades = atividades.stream().map(Atividade::clone).collect(Collectors.toList());
    }
    /*
     * Setter dos planos de treino pré-definidos
     * @param planosTreino - lista de planos de treino pré-definidos no ginásio
     */
    public void setPlanosTreino(List<PlanoTreino> planosTreino) {
        this.planosTreino = planosTreino.stream().map(PlanoTreino::clone).collect(Collectors.toList());
    }

    /*
     * Método de cópia
     * @return cópia do objeto Fitness
     */
    public Fitness clone() {
        return new Fitness(this);
    }

    /*
     * Método equals
     * @param o - objeto a ser comparado
     * @return true se os objetos forem iguais, false caso contrário
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        Fitness fitness = (Fitness) o;
        return this.nomeGinasio.equals(fitness.getNomeGinasio()) &&
                this.data.equals(fitness.getDataGin()) &&
                this.utilizadoresMap.equals(fitness.getUtilizadoresMap()) &&
                this.atividades.equals(fitness.getAtividades()) &&
                this.planosTreino.equals(fitness.getPlanosTreino());
    }

    /*
     * Método toString
     * @return String com informações sobre o objeto Fitness
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("Fitness{");
        sb.append("nomeGinasio='").append(nomeGinasio).append('\'');
        sb.append(", data=").append(data);
        sb.append(", utilizadoresMap=").append(utilizadoresMap);
        sb.append(", atividades pré-definidas=").append(atividades);
        sb.append(", planosTreino pré-definidas=").append(planosTreino);
        sb.append('}');
        return sb.toString();
    }

    /*
     * Método para adicionar um utilizador ao mapa de utilizadores
     * @param ut - tipo de utilizador a ser adicionado
     * @param email - email do utilizador
     * @param password - password do utilizador
     * @param nome - nome do utilizador
     * @param genero - género do utilizador de acordo com a enumeração Genero
     * @param altura - altura do utilizador
     * @param peso - peso do utilizador
     * @param dataNascimento - data de nascimento do utilizador
     */
    public void criarUtilizadorNoMap(UserType ut, String email, String password, String nome, Genero genero, double altura, double peso, LocalDate dataNascimento) {
        switch (ut) {
            case PROFISSIONAL:
                UserProfissional up = new UserProfissional(email, password, nome, genero, altura, peso, dataNascimento);
                this.utilizadoresMap.put(up.getId(), up.clone());
                break;
            case OCASIONAL:
                UserOcasional uo = new UserOcasional(email, password, nome, genero, altura, peso, dataNascimento);
                this.utilizadoresMap.put(uo.getId(), uo.clone());
                break;
            default:
                UserAmador ua = new UserAmador(email, password, nome, genero, altura, peso, dataNascimento);
                this.utilizadoresMap.put(ua.getId(), ua.clone());
                break;
        }
    }
    public void adduser (Utilizador u){
        this.utilizadoresMap.put(u.getId(), u.clone());
    }

    /*
     * Metodo para verificar se um utilizador existe no mapa de utilizadores
     * @param email - email do utilizador
     * @param password - password do utilizador
     * @return true se o utilizador existir, false caso contrário
     */
    public boolean userExists (String email, String password) {
        return this.utilizadoresMap.containsKey(searchUserId(email)) && this.utilizadoresMap.get(searchUserId(email)).getPassword().equals(password);
    }
    /*
     * Metodo para procurar o id de um utilizador
     * @param email - email do utilizador
     * @return id do utilizador
     */
    public String searchUserId(String email){
       return this.utilizadoresMap.values().stream().filter(u -> u.getEmail().equals(email)).map(Utilizador::getId).findFirst().orElse("");
    }
    /*
     * Metodo que elimina um utilizador do mapa de utilizadores
     */
    public void deleteUser(String email){
        this.utilizadoresMap.remove(email);
    }
    /*
     * Metodo que adiciona uma atividade a um utilizador
     * @param id - id do utilizador
     * @param atividade - atividade a ser adicionada
     */
    public void addAtividadeUser(String id, Atividade atividade){
        this.utilizadoresMap.get(id).addAtividade(atividade);
    }
    /*
     * Metodo que remove uma atividade de um utilizador
     * @param id - id do utilizador
     * @param atividade - atividade a ser removida
     */
    public void removeAtividadeUser(String id, Atividade atividade){
        this.utilizadoresMap.get(id).removeAtividade(atividade);
    }
    /*
     * Metodo que adiciona um plano de treino a um utilizador
     * @param id - id do utilizador
     * @param planoTreino - plano de treino a ser adicionado
     */
    public void addPlanoTreinoUser(String id, PlanoTreino planoTreino){
        this.utilizadoresMap.get(id).addPlanoTreino(planoTreino);
    }
    /*
     * Metodo que remove um plano de treino de um utilizador
     * @param id - id do utilizador
     * @param planoTreino - plano de treino a ser removido
     */
    public void removePlanoTreinoUser(String id, PlanoTreino planoTreino){
        this.utilizadoresMap.get(id).removePlanoTreino(planoTreino);
    }
    /*
     * Metodo que devolve o perfil de um utilizador
     * @param id - id do utilizador
     * @return perfil do utilizador em formato de String
     */
    public String perfilUser(String id){
        return this.utilizadoresMap.get(id).toString();
    }
    /*
     * Metodo que devolve as atividades de um utilizador
     * @param id - id do utilizador
     * @return atividades do utilizador em formato de String
     */
    public String atividadesUser(String id){
        return this.utilizadoresMap.get(id).getAtividades().values().toString();
    }
    /*
     * Metodo que devolve os planos de treino de um utilizador
     * @param id - id do utilizador
     * @return planos de treino do utilizador em formato de String
     */
    public String planosUser(String id){
        return this.utilizadoresMap.get(id).getPlanodeTreino().values().toString();
    } 


    // metodos para List de atividades/planos-treino pre-definidas

    /*
     * Metodo que adiciona uma atividade ao List de atividades pre-definidas
     * @param a - atividade a ser adicionada
     */
    public void addAtividade(Atividade a){
        this.atividades.add(a.clone());
    }
    /*
     * Metodo que remove uma atividade do List de atividades pre-definidas
     * @param a - atividade a ser removida
     */
    public void removeAtividade(Atividade a){
        this.atividades.remove(a.clone());
    }
    /*
     * Metodo que adiciona um plano de treino ao List de planos de treino pre-definidos
     * @param p - plano de treino a ser adicionado
     */
    public void addPlanoTreino(PlanoTreino p){
        this.planosTreino.add(p.clone());
    }
    /*
     * Metodo que remove um plano de treino do List de planos de treino pre-definidos
     * @param p - plano de treino a ser removido
     */
    public void removePlanoTreino(PlanoTreino p){
        this.planosTreino.remove(p.clone());
    }
    /*
     * Metodo que devolve as atividades pre-definidas em formato de String
     * @return atividades pre-definidas em formato de String
     */
    public String atividadesPreDefinidas(){
        return this.atividades.toString();
    }

    /*
     * Metodo que devolve os planos de treino pre-definidos em formato de String
     * @return planos de treino pre-definidos em formato de String
     */
    public String planosTreinoPreDefinidos(){
        return this.planosTreino.toString();
    }
    /*
     * Metodo que devolve comparadores para estatisticas pré-definidas do utilizador
     * @param i - indice do comparador ou número da estatistica do enunciado (1-2)
     * @return comparador para estatisticas do utilizador
     */
    public Comparator<Utilizador> getComparatorEstatisticasUser(int i){
        return this.comparatorsEstatisticasUser.get(i);
    }

    /*
     * Metodo que adiciona comparadores para estatisticas pré-definidas do utilizador e define comparadores pré-definidos
     * @param c - comparador para estatisticas do utilizador
     */
    public void adicionarComparators(){
        comparatorsEstatisticasUser.add(Comparator.comparingDouble(u -> u.getAtividades().values().stream()
                .mapToDouble(a -> a.calcularCaloriasGastas(u)).sum())); // q1
        comparatorsEstatisticasUser.add(Comparator.comparingInt(u -> u.getAtividades().size())); // q2

    }
    
    // ESTATISTICAS ENUNCIADO
   

    // 3.2 - estatisticas sobre o estado do programa
    /* 
     * Metodo que devolve o utilizador dependendo do tipo de estatistica evocada
     * @param idStat - número da estatistica do enunciado (1-2)
     * @return utilizador com a estatistica evocada
    */
    public Utilizador statsUsers(int idStat){
        return this.utilizadoresMap.values().stream().max(this.comparatorsEstatisticasUser.get(idStat)).orElse(null);
    }
    /*
     * Metodo que devolve o utilizador dependendo do tipo de estatistica evocada e do período de tempo
     * @param idStat - número da estatistica do enunciado (1-2)
     * @param din - data de início do período de tempo
     * @param dfim - data de fim do período de tempo
     * @return utilizador com a estatistica evocada no período de tempo
     */
    public Utilizador statsUsers(int idStat, LocalDate din, LocalDate dfim){
        return this.utilizadoresMap.values().stream().filter(u -> u.getAtividades().values().stream().anyMatch(a -> a.getDataRealização().toLocalDate().isAfter(din) && a.getDataRealização().toLocalDate().isBefore(dfim))).max(this.comparatorsEstatisticasUser.get(idStat)).orElse(null);
    }

    /*
     * Metodo que devolve o tipo de atividade mais realizada - Q3 do enunciado
     * @return tipo de atividade mais realizada
     */
    public String tipoAtividadeMaisRealizada() {
        Comparator<String> atividadeMRealizada = Comparator.comparing(atividade -> this.utilizadoresMap.values().stream().mapToInt(u -> (int) u.getAtividades().values().stream().filter(a -> a.getClass().getSimpleName().equals(atividade)).count()).sum());
        List<String> atividades = Arrays.asList("CorridaTerreno", "Pesos", "Alongamentos", "Remo", "Btt");
    return atividades.stream().max(atividadeMRealizada).orElse("");
    }
    /*
     * Metodo que devolve os quilómetros totalizados por um utilizador desde sempre - Q4 do enunciado
     * @param id - id do utilizador
     * @return quilómetros totalizados pelo utilizador
     */
    public double kmsUtilizador (String id){
        return this.utilizadoresMap.get(id).getAtividades().values().stream().mapToDouble(a -> a instanceof Distancia ? ((Distancia) a).getDistancia() : 0).sum();
    }
    /*
     * Metodo que devolve os quilómetros totalizados por um utilizador num período de tempo - Q4 do enunciado
     * @param id - id do utilizador
     * @param din - data de início do período de tempo
     * @param dfim - data de fim do período de tempo
     * @return quilómetros totalizados pelo utilizador no período de tempo
     */
    public double kmsUtilizador(String id, LocalDate din, LocalDate dfim){
        return this.utilizadoresMap.get(id).getAtividades().values().stream().filter(a -> a.getDataRealização().toLocalDate().isAfter(din) && a.getDataRealização().toLocalDate().isBefore(dfim)).mapToDouble(a -> a instanceof Distancia || a instanceof DistanciaAltimetria ? ((Distancia) a).getDistancia() : 0).sum();
    }
    /*
     * Metodo que devolve os metros de altimetria totalizados por um utilizador desde sempre - Q5 do enunciado
     * @param id - id do utilizador
     * @return metros de altimetria totalizados pelo utilizador
     */
    public double metrosAltimetriaUtilizador(String id){
        return this.utilizadoresMap.get(id).getAtividades().values().stream().mapToDouble(a -> a instanceof DistanciaAltimetria ? ((DistanciaAltimetria) a).getAltimetria() : 0).sum();
    }
    /*
     * Metodo que devolve os metros de altimetria totalizados por um utilizador num período de tempo - Q5 do enunciado
     * @param id - id do utilizador
     * @param din - data de início do período de tempo
     * @param dfim - data de fim do período de tempo
     * @return metros de altimetria totalizados pelo utilizador no período de tempo
     */
    public double metrosAltimetriaUtilizador(String id, LocalDate din, LocalDate dfim){
        return this.utilizadoresMap.get(id).getAtividades().values().stream().filter(a -> a.getDataRealização().toLocalDate().isAfter(din) && a.getDataRealização().toLocalDate().isBefore(dfim)).mapToDouble(a -> a instanceof DistanciaAltimetria ? ((DistanciaAltimetria) a).getAltimetria() : 0).sum();
    }
    /*
     * Metodo que devolve o plano de treino mais exigente em função do dispêndio de calorias proposto - Q6 do enunciado
     * @return plano de treino mais exigente
     */
    public PlanoTreino planoMaisExigente(){
        Comparator<PlanoTreino> maisExigente = Comparator.comparingDouble(p -> p.getAtividades().values().stream().mapToDouble(a -> a.calcularCaloriasGastas(a.getUtilizador())).sum());
        return this.utilizadoresMap.values().stream().map(Utilizador::getPlanodeTreino)
                .flatMap(p -> p.values().stream()) // getPlanodeTreino() devolve um Map<String,PlanoTreino> e queremos os objetos pois o comparador é para PlanoTreino
                .max(maisExigente).orElse(null);
    }

    /*
     * Metodo que devolve as atividades realizadas por um utilizador - Q7 do enunciado
     * @param id - id do utilizador
     * @return atividades realizadas pelo utilizador
     */
    public String atividadesUtilizador(String id){
        return this.utilizadoresMap.get(id).getAtividades().values().toString();
    }

    // RECORDES DE ATIVIDADES


    // ficheiros - guardar e carregar estado
    /*
     * Metodo que guarda o estado do programa num ficheiro binário
     * @param nomeFicheiro - nome do ficheiro
     * @throws FileNotFoundException
     * @throws IOException
     */
    public void guardaEstadoBin(String nomeFicheiro) throws FileNotFoundException, IOException{
        try {
            FileOutputStream fos = new FileOutputStream(nomeFicheiro);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(this);
            oos.flush();
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    /*
     * Metodo que carrega o estado do programa de um ficheiro binário
     * @param nomeFicheiro - nome do ficheiro
     * @return estado do programa
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public Fitness carregaEstadoBin(String nomeFicheiro) throws IOException, ClassNotFoundException{
        FileInputStream fis = new FileInputStream(nomeFicheiro);
        ObjectInputStream oos = new ObjectInputStream(fis);
        Fitness fit =(Fitness) oos.readObject();
        oos.close();
        return fit;
    }
    /*
        * Metodo que guarda o estado do programa num ficheiro CSV
        * @param nomeFicheiro - nome do ficheiro
        * @throws IOException
        */
        public void guardaEstadoCSV(String nomeFicheiro) throws IOException{
            PrintWriter pw = new PrintWriter(nomeFicheiro);
            pw.println(this.toString());
            pw.flush();
            pw.close();
        }
        /*
         * Metodo que carrega o estado do programa de um ficheiro binário
         * @param nomeFicheiro - nome do ficheiro
         * @return estado do programa
         * @throws FileNotFoundException
         */
        public void loadUtilizadores(String filename) throws FileNotFoundException {
            try {
                FileInputStream fis = new FileInputStream(filename);
                ObjectInputStream ois = new ObjectInputStream(fis);
                setUtilizadoresMap((Map<String, Utilizador>) ois.readObject());
                ois.close();
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
        /*
         * Metodo que guarda os utilizadores num ficheiro binário
         * @param filename - nome do ficheiro
         * @throws FileNotFoundException
         * @throws IOException
         */
        public void guardaUtilizadores(String filename) throws FileNotFoundException, IOException{
            try {
                FileOutputStream fos = new FileOutputStream(filename);
                ObjectOutputStream oos = new ObjectOutputStream(fos);
                oos.writeObject(this.utilizadoresMap);
                oos.flush();
                oos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
       


        // load set atividades e planos pre-definidos -- meio inutil pois o carregaEstadoBin já faz isso porem pode usar-se para simulações novas
        /*
         * Metodo que carrega as atividades de um ficheiro binário
         * @param filename - nome do ficheiro
         * @throws FileNotFoundException
         */
        public void loadAtividades(String filename) throws FileNotFoundException {
            try {
                FileInputStream fis = new FileInputStream(filename);
                ObjectInputStream ois = new ObjectInputStream(fis);
                setAtividades((List<Atividade>) ois.readObject());
                ois.close();
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
        /*
         * Metodo que guarda as atividades num ficheiro binário
         * @param filename - nome do ficheiro
         * @throws FileNotFoundException
         * @throws IOException
         */
        public void guardaAtividades(String filename) throws FileNotFoundException, IOException{
            try {
                FileOutputStream fos = new FileOutputStream(filename);
                ObjectOutputStream oos = new ObjectOutputStream(fos);
                oos.writeObject(this.atividades);
                oos.flush();
                oos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        /*
         * Metodo que carrega os planos de treino de um ficheiro binário
         * @param filename - nome do ficheiro
         * @throws FileNotFoundException
         */
        public void loadPlanosTreino(String filename) throws FileNotFoundException {
            try {
                FileInputStream fis = new FileInputStream(filename);
                ObjectInputStream ois = new ObjectInputStream(fis);
                setPlanosTreino((List<PlanoTreino>) ois.readObject());
                ois.close();
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
        /*
         * Metodo que guarda os planos de treino num ficheiro binário
         * @param filename - nome do ficheiro
         * @throws FileNotFoundException
         * @throws IOException
         */
        public void guardaPlanosTreino(String filename) throws FileNotFoundException, IOException{
            try {
                FileOutputStream fos = new FileOutputStream(filename);
                ObjectOutputStream oos = new ObjectOutputStream(fos);
                oos.writeObject(this.planosTreino);
                oos.flush();
                oos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        
        /*
         * Metodo que guarda os utilizadores num ficheiro CSV
         * @param Ficheiro - nome do ficheiro
         * @throws IOException
         */

        public void escreverCSVUtilizadores(String Ficheiro) throws IOException{
            PrintWriter pw = new PrintWriter(Ficheiro);
            for(Utilizador u : this.utilizadoresMap.values()){
                pw.println(u.toString());
                pw.println(";");
            }
            pw.flush();
            pw.close();
        }
        /*
         * Metodo que guarda as atividades num ficheiro CSV
         * @param Ficheiro - nome do ficheiro
         * @throws IOException
         */
        public void escreverCSVAtividades(String Ficheiro) throws IOException{
            PrintWriter pw = new PrintWriter(Ficheiro);
            for(Atividade a : this.atividades){
                pw.println(a.toString());
                pw.println(";");
            }
            pw.flush();
            pw.close();
        }
        /* 
         * Metodo que guarda os planos de treino num ficheiro CSV
         * @param Ficheiro - nome do ficheiro
         * @throws IOException
         */
        public void escreverCSVPlanosTreino(String Ficheiro) throws IOException{
            PrintWriter pw = new PrintWriter(Ficheiro);
            for(PlanoTreino p : this.planosTreino){
                pw.println(p.toString());
                pw.println(";");
            }
            pw.flush();
            pw.close();
        }
        /* 
         * Metodo que dá update das atividades realizadas em planos de treino pelos utilizadores no mapa de atividades quando a data da simulação é atulizada 
         */
        public void updateDatas(){
            // ir aos planos de treino e adicionar as atividades ao mapa de atividades realizadas
            for(Utilizador u : this.utilizadoresMap.values()){
                for(PlanoTreino p : u.getPlanodeTreino().values()){
                    for(Atividade a : p.getAtividades().values()){
                        if (a.getDataRealização().isBefore(getDataGin())) u.addAtividade(a);
                    }
                }
                
            }
        }

        


}
