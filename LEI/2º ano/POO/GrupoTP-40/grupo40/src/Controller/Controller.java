package Controller;


import static java.lang.System.out;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.time.LocalDate;
import java.time.LocalDateTime;

import Model.*;

public class Controller {
    
    private Fitness fitness;

    /*
     * Construtor parametrizado
     * @param f - objeto do tipo Fitness
     */
    public Controller(Fitness f) {
        this.fitness = f;
    }

    /*
     * getter do objeto Fitness
     * @return objeto do tipo Fitness
     */
    public Fitness getFitness() {
        return this.fitness;
    }

    /*
     * setter do objeto Fitness
     * @param f - objeto do tipo Fitness
     */
    public void setFitness(Fitness f) {
        this.fitness = f;
    }

    /*
     * Método que verifica se um utilizador existe, e caso não exista, cria um novo utilizador no map de utilizadores do Fitness
     * @param email - email do utilizador
     * @param password - password do utilizador
     * @param nome - nome do utilizador
     * @param genero - genero do utilizador
     * @param altura - altura do utilizador
     * @param peso - peso do utilizador
     * @param dataNascimento - data de nascimento do utilizador
     * @param utype - tipo de utilizador de acordo com o enum UserType
     * @return true se o utilizador já existir, false se o utilizador não existir
     */
    public boolean addUser(String email, String password, String nome, String genero, double altura, double peso, LocalDate dataNascimento, int utype) {
        boolean existe = this.fitness.userExists(email, password);
        if (!existe) {
            Genero gen;
            switch (genero) {
                case "M":
                    gen = Genero.Masculino;
                    break;
                case "F":
                    gen = Genero.Feminino;
                    break;
                default:
                    gen = Genero.Outro;
                    break;
            }
            UserType userType = UserType.values()[utype-1];
            this.fitness.criarUtilizadorNoMap(userType, email, password, nome, gen, altura, peso, dataNascimento);
        }
        return existe;
    }
    // simulação

    /*
     * Setter da data de simulação
     * @param data - data de simulação
     */
    public void setDataSimulacao(LocalDateTime data){
        this.fitness.setDataGin(data);
    }
    /*
     * Getter da data de simulação
     * @return data de simulação
     */
    public LocalDateTime getDataSimulacao(){
        return this.fitness.getDataGin();
    }
    /*
     * Método que chama o método updateDatas do objeto Fitness para atualizar as datas das atividades realizadas nos planos de treino - conveniencia de nomes apenas
     */
    public void updateSimulacao(){
        this.fitness.updateDatas();
    }
    // detalhes simulacao
    /*
     * Método que retorna uma string com os detalhes da simulação
     * @return string com os detalhes da simulação
     */
    public String detalhesSimulacao() {
        StringBuilder sb = new StringBuilder();
        sb.append("Data de simulação: ").append(this.fitness.getDataGin()).append("\n");
        sb.append("Número de utilizadores: ").append(this.fitness.getUtilizadoresMap().size()).append("\n");
        sb.append("Número de planos de treino: ").append(this.fitness.getPlanosTreino().size()).append("\n");
        return sb.toString();
    }

    // utilizadores
    /*
     * Método que inicia sessão de um utilizador caso este exista
     * @param email - email do utilizador
     * @param password - password do utilizador
     * @return true se o utilizador existe, false se o utilizador não existe
     */
    public boolean iniciarSessao(String email, String password) {
        return this.fitness.userExists(email, password);
    }
    /*
     * Método que retorna o id de um utilizador para efeitos de pedidos no sistema
     * @param email - email do utilizador
     * @return id do utilizador
     */
    public String getViewRequestsID(String email) {
        return this.fitness.searchUserId(email);
    }
    /*
     * Método que retorna o perfil de um utilizador
     * @param id - id do utilizador
     * @return string com o perfil do utilizador
     */
    public String perfilUser (String id) {
        return this.fitness.perfilUser(id);
    }
    /*
     * Método que retorna as atividades de um utilizador
     * @param id - id do utilizador
     * @return string com as atividades do utilizador
     */
    public String verAtividadesUser (String id) {
        return this.fitness.atividadesUser(id);
    }
    /*
     * Método que retorna os planos de treino de um utilizador
     * @param id - id do utilizador
     * @return string com os planos de treino do utilizador
     */
    public String verPlanosUser (String id) {
        return this.fitness.planosUser(id);
    }

    // ficheiros
    /*
     * Método que guarda o estado do Fitness num ficheiro binário e num ficheiro CSV
     * @param filename - nome do ficheiro binário
     * @param filename2 - nome do ficheiro CSV
     * @throws FileNotFoundException
     */
    public void guardarEstado(String filename, String filename2) throws FileNotFoundException, IOException {
        this.fitness.guardaEstadoBin(filename);
    }
    /*
     * Método que carrega o estado do Fitness de um ficheiro binário
     * @param filename - nome do ficheiro binário
     * @throws ClassNotFoundException
     */
    public void carregarEstado(String filename) throws ClassNotFoundException, IOException {
        setFitness(fitness.carregaEstadoBin(filename));
        
    }
    /*
     * Método que guarda o estado dos maps de atividades e planos de treino PRÉ-DEFINIDOS num ficheiro binário
     */
    public void guardaEstadoATePT() throws IOException {
        this.fitness.guardaAtividades("Atividades.dat");
        this.fitness.guardaPlanosTreino("Planos.dat");
        this.fitness.escreverCSVAtividades("Atividades.csv");
        this.fitness.escreverCSVPlanosTreino("Planos.csv");

    }
    /*
     * Método que carrega o estado dos maps de atividades e planos de treino PRÉ-DEFINIDOS de um ficheiro binário
     * @throws ClassNotFoundException
     */
    public void carregaEstadoATePT() throws IOException, ClassNotFoundException {
        this.fitness.loadAtividades("Atividades.dat");
        this.fitness.loadPlanosTreino("Planos.dat");
    }
    /*
     * Método que guarda o estado dos utilizadores num ficheiro binário
     */
    public void guardaEstadoUser() throws IOException {
        this.fitness.guardaUtilizadores("Utilizadores.dat");
        this.fitness.escreverCSVUtilizadores("Utilizadores.csv");
    }

    /*
     * Método que carrega o estado dos utilizadores de um ficheiro binário
     */
    public void carregaEstadoUser() throws IOException, ClassNotFoundException {
        this.fitness.loadUtilizadores("Utilizadores.dat");
    }
    // atividades
    /*
     * Método que cria uma atividade de corrida em terreno, caso o utilizador exista, associa a atividade ao utilizador, caso contrário, cria a atividade sem utilizador associado e adiciona-a ao List de atividades pré-definidas
     * @param nome - nome da atividade
     * @param duracao - duração da atividade em minutos
     * @param distancia - distância percorrida
     * @param dataRealizacao - data de realização da atividade
     * @param id - id do utilizador
     */
    public void criarAtividadeCorridaTerreno(String nome, long duracao, double distancia, double altimetria, int tipo, LocalDateTime dataRealizacao, String id) {
    
        if (id == "0") {
            CorridaTerreno ct = new CorridaTerreno(nome, dataRealizacao, duracao, distancia, altimetria, TipoTerreno.values()[tipo-1]);
            this.fitness.addAtividade(ct);
        } else {
            CorridaTerreno ct = new CorridaTerreno(nome, dataRealizacao, duracao, this.fitness.getUtilizadoresMap().get(id), distancia, altimetria, TipoTerreno.values()[tipo-1]);
            this.fitness.addAtividadeUser(id, ct);
        }
        
    }
    /*
     * Método que cria uma atividade de remo, caso o utilizador exista, associa a atividade ao utilizador, caso contrário, cria a atividade sem utilizador associado e adiciona-a ao List de atividades pré-definidas
     * @param nome - nome da atividade
     * @param duracao - duração da atividade em minutos
     * @param distancia - distância percorrida
     * @param dataRealizacao - data de realização da atividade
     * @param id - id do utilizador
     */
    public void criarAtividadeRemo (String nome, long duracao, double distancia, LocalDateTime dataRealizacao, String id) {
        if (id == "0") {
            Remo r = new Remo(nome, dataRealizacao, duracao, distancia);
            this.fitness.addAtividade(r);
        } else {
            Remo r = new Remo(nome, dataRealizacao, duracao, this.fitness.getUtilizadoresMap().get(id), distancia);
            this.fitness.addAtividadeUser(id, r);
        }
    }
    /*
     * Método que cria uma atividade de alongamentos, caso o utilizador exista, associa a atividade ao utilizador, caso contrário, cria a atividade sem utilizador associado e adiciona-a ao List de atividades pré-definidas
     * @param nome - nome da atividade
     * @param dataRealizacao - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param pc - parte do corpo que foi exercitada
     * @param repeticoes - numero de repetições
     * @param series - numero de series 
     * @param id - id do utilizador
     */
    public void criarAtividadeAlongamentos (String nome, LocalDateTime dataRealizacao, long duracao, int pc, int repeticoes, int series, String id) {

        if (id == "0"){
            Alongamentos a = new Alongamentos(nome, dataRealizacao, duracao, repeticoes, series, BodyPart.values()[pc-1]);
            this.fitness.addAtividade(a);
        } else {
            Alongamentos a = new Alongamentos(nome, dataRealizacao, duracao, this.fitness.getUtilizadoresMap().get(id), repeticoes, series, BodyPart.values()[pc-1]);
            this.fitness.addAtividadeUser(id, a);
        }
    }
    /*
     * Método que cria uma atividade de levantamento de pesos, caso o utilizador exista, associa a atividade ao utilizador, caso contrário, cria a atividade sem utilizador associado e adiciona-a ao List de atividades pré-definidas
     * @param nome - nome da atividade
     * @param dataRealizacao - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param repeticoes - numero de repetições
     * @param series - numero de series
     * @param peso - peso levantado
     * @param id - id do utilizador
     */
    public void criarAtividadeLevantamentoPeso (String nome, LocalDateTime dataRealizacao, long duracao, int repeticoes, int series, double peso, String id) {
        Pesos lp = new Pesos (nome, dataRealizacao, duracao, this.fitness.getUtilizadoresMap().get(id), peso, repeticoes, series);
        if (id == "0") {
            this.fitness.addAtividade(lp);
        } else {
            this.fitness.addAtividadeUser(id, lp);
        }
    }

    /*
     * Método que cria uma atividade de BTT, caso o utilizador exista, associa a atividade ao utilizador, caso contrário, cria a atividade sem utilizador associado e adiciona-a ao List de atividades pré-definidas
     * @param nome - nome da atividade
     * @param dataRealizacao - data de realização da atividade
     * @param duracao - duração da atividade em minutos
     * @param distancia - distância percorrida
     * @param altimetria - metros de altimetria
     * @param tipo - tipo de terreno
     * @param dificuldade - dificuldade da atividade
     * @param id - id do utilizador
     */
    public void criarAtividadeBtt(String nome, LocalDateTime dataRealizacao, long duracao, double distancia, double altimetria, int tipo, int dificuldade, String id) {
        if (id == "0") {
            Btt b = new Btt(nome, dataRealizacao, duracao, distancia, altimetria, TipoTerreno.values()[tipo-1], dificuldade);
            this.fitness.addAtividade(b);
        } else {
            Btt b = new Btt(nome, dataRealizacao, duracao, this.fitness.getUtilizadoresMap().get(id), distancia, altimetria, TipoTerreno.values()[tipo-1], dificuldade);
            this.fitness.addAtividadeUser(id, b);
        }
    }
    // PRE DEFINIDAS    
        // atividades
    /*
     * Método que retorna uma atividade pré-definida
     * @param i - indice da atividade
     * @return string com a atividade pré-definida
     */
    public String getAtividades(int i) {
        return this.fitness.getAtividades().get(i).toString();
    }
    /*
     * metodo que retorna a lista de atividades pré-definidas em forma de string
     * @return string com as atividades pré-definidas
     */
    public String verAtividadesPRE() {
        return this.fitness.atividadesPreDefinidas();
    }
    /*
     * Método que retorna o tamanho da lista de atividades pré-definidas
     * @return tamanho da lista de atividades pré-definidas
     */
    public int getAtividadesSize() {
        return this.fitness.getAtividades().size();
    }
        // planos
    /*
        * Método que retorna um plano de treino pré-definido
        * @param i - indice do plano de treino
        * @return string com o plano de treino pré-definido
    */
    public PlanoTreino getPlanos(int i) {
        return this.fitness.getPlanosTreino().get(i);
    }
    /*
     * Método que retorna a lista de planos de treino pré-definidos em forma de string
     * @return string com os planos de treino pré-definidos
     */
    public String verPlanoPre(){
        return this.fitness.planosTreinoPreDefinidos();
    }
    /*
     * Método que retorna o tamanho da lista de planos de treino pré-definidos
     * @return tamanho da lista de planos de treino pré-definidos
     */
    public int getPlanosSize() {
        return this.fitness.getPlanosTreino().size();
    }
    /*
     * Método que regista uma atividade pré-definida para um utilizador
     * @param id - id do utilizador
     * @param i - indice da atividade 
     * @param dataRealizacao - data de realização da atividade por parte do utilizador
     */
    public void registaAtividadePre (String id, int i, LocalDateTime dataRealizacao) {
        Atividade a = this.fitness.getAtividades().get(i);
        a.setDataRealização(dataRealizacao);
        a.setUtilizador(this.fitness.getUtilizadoresMap().get(id));
        this.fitness.addAtividadeUser(id, a);
    }

    /*
     * Método que regista um plano de treino pré-definido para um utilizador
     * @param id - id do utilizador
     * @param i - indice do plano de treino
     */
    public void registaPlanoPre (String id, int i) {
        PlanoTreino p = this.fitness.getPlanosTreino().get(i);
        this.fitness.addPlanoTreinoUser(id, p);
    }

    // estatisticas
    /*
     * Método que retorna as estatísticas de uma simulação
     * @param id - id do utilizador
     * @param opcao - opção de estatística definida no enunciado
     * @param opcaoData - opção de data - 1 - desde sempre, 2 - entre datas
     * @param datain - data inicial
     * @param datafim - data final
     * @return string com as estatísticas
     */
   public String estatisticasSimulacao(String id, int opcao, int opcaoData, LocalDate datain, LocalDate datafim) {
        this.fitness.adicionarComparators();
        switch (opcao) {
            case 1:
                    if(opcaoData == 1){
                        return this.fitness.statsUsers(opcao).toString();
                    } else {
                        return this.fitness.statsUsers(opcao, datain, datafim).toString();
                    }
            case 2:
                    if(opcaoData == 1){
                        return this.fitness.statsUsers(opcao).toString();
                    } else {
                        return this.fitness.statsUsers(opcao, datain, datafim).toString();
                    }
            case 3:
                    return this.fitness.tipoAtividadeMaisRealizada().toString();
            case 4:
                    if(opcaoData == 1){
                        return String.valueOf(this.fitness.kmsUtilizador(id));
                    } else {
                        return String.valueOf(this.fitness.kmsUtilizador(id, datain, datafim));
                    }
            case 5:
                    if(opcaoData == 1){
                        return String.valueOf(this.fitness.metrosAltimetriaUtilizador(id));
                    } else {
                        return String.valueOf(this.fitness.metrosAltimetriaUtilizador(id, datain, datafim));
                    }
            case 6:
                    return this.fitness.planoMaisExigente().toString();
            case 7:
                    return this.fitness.atividadesUtilizador(id).toString();
            default:
                break;
        }
       
        return "";
   }

   /*
    * Método que regista um plano de treino para um utilizador
    * @param id - id do utilizador
    * @param p - plano de treino
    */
   public void registaPlanoUser(String id, PlanoTreino p){
         this.fitness.addPlanoTreinoUser(id, p);
   }

    /*
     * Método que regista atividades para um plano de treino
     * @param dataR - data de realização das atividades
     * @param periodicidade - periodicidade do plano de treino
     * @param idAtvs - array com os ids das atividades a adicionar ao plano de treino
     * @param id - id do utilizador
     */
   public void registaAtividadesParaPlano(LocalDate dataR, int periodicidade, int idAtvs [], String id) {
         PlanoTreino p = new PlanoTreino();
            p.setRealizacao(dataR);
            p.setPeriodicidade(PeriodicidadePlano.values()[periodicidade]);
            for (int s : idAtvs) {
                if(!p.planoTemHards()){
                    p.addAtividade(this.fitness.getAtividades().get(s));
                }
            }
            registaPlanoUser(id, p);
   }

    /*
     * Método que regista um plano de treino pré-definido para um utilizador
     * @param data - data de realização do plano de treino
     * @param Periodo - periodicidade do plano de treino
     * @param idAtvs - array com os ids das atividades a adicionar ao plano de treino
     */
   public void registaPlanoPre(LocalDate data, int Periodo, int idAtvs []) {
        PlanoTreino p = new PlanoTreino(data, PeriodicidadePlano.values()[Periodo]);
        for (int s : idAtvs) {
            p.addAtividade(this.fitness.getAtividades().get(s));
        }
        this.fitness.addPlanoTreino(p);
    }
    


}
