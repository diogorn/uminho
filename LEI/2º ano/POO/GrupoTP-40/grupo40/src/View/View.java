package View;

import java.io.IOException;
import java.time.DateTimeException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.InputMismatchException;
import java.util.Scanner;
import Controller.Controller;

import static java.lang.System.out;
// view nao tem throws, so exceptions
public class View {
    private Controller c;
    private Scanner scanner;

    /*
     * Construtor parametrizado
     * @param c - objeto do tipo Controller
     * @param scanner - objeto do tipo Scanner
     */
    public View(Controller c, Scanner scanner) {
        this.c = c;
        this.scanner = scanner;
    }

    /*
     * Método run que inicia a aplicação
     */
    public void run() {
        clearConsole();
        try {
            menuSimulacao();
        } catch (Exception e) {out.println("Failed loading simulation: " + e.getMessage());
        }
    }

    /*
     * Método que limpa a consola
     */
    public void clearConsole() {
        try {
             if (System.getProperty("os.name").contains("Windows")) {
                 new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
 
             }
             else {
                 out.println("\033\143");
             }
         } catch (IOException | InterruptedException ex) { out.println(ex.getMessage());}
    }

    /*
     * Método que imprime o menu de simulação
     */
     public void menuSimulacao() throws IOException, ClassNotFoundException{
        //clearConsole();
        out.println("=== Bem-vindo ao UM-Sports ===\n");
        out.println("1 - Iniciar nova simulação");
        out.println("2 - Carregar simulação");
        out.println("3 - Fechar programa\n");
        out.println("Opção: ");
        try {
            int opcao = scanner.nextInt();
            switch(opcao){
                case 1:
                    defineDataSimulacao();
                    simulacaoAtual();
                    break;
                case 2:
                    carregarSimulacao();
                    detalhesSimulacao();
                    simulacaoAtual();
                    break;
                case 3:
                    System.exit(0);
                    break;
            }
        } catch (Exception e) {
            out.println("Opção inválida");
            out.println(e.getMessage());
        }
        menuSimulacao();
     }
    


     /*
      * Método que imprime o menu de simulação atual
      */
      public void simulacaoAtual() {
        try {
            out.println("== Menu Inicial ==");
            out.println("Data de simulação: " + c.getDataSimulacao() + "\n");
            out.println("1 - Criar novo utilizador");
            out.println("2 - Iniciar sessão");
            out.println("3 - Menu admin");
            out.println("4 - Menu Simulação");
            out.println("Opção: ");
    
            int opcao = scanner.nextInt();
            switch (opcao) {
                case 1:
                    criarNovoUtilizador();
                    break;
                case 2:
                    iniciarSessao();
                    break;
                case 3:
                    menuAdmin();
                    break;
                case 4:
                    menuSimulacao();
                    break;
                default:
                    out.println("Opção inválida");
                    break;
            }
        } catch (InputMismatchException e) {
            out.println("Opção inválida. Por favor, insira um número.");
            scanner.nextLine(); 
            simulacaoAtual(); 
        } catch (IOException | ClassNotFoundException e) {
            out.println("Erro ao executar a opção: " + e.getMessage());
            scanner.nextLine(); 
            simulacaoAtual(); 
        }
        simulacaoAtual(); 
    }
    

    /*
     * Método que define a data de simulação
     */
    public void defineDataSimulacao() {
    try {
        clearConsole();
        out.println("1 - Utilizar data atual");
        out.println("2 - Definir data de simulação");
        out.println("Opção: ");
        int opcao = scanner.nextInt();
        switch (opcao) {
            case 1:
                c.setDataSimulacao(LocalDateTime.now());
                break;
            case 2:
                c.setDataSimulacao(scanDataHora());
                break;
            default:
                out.println("Opção inválida. Por favor, escolha 1 ou 2.");
                defineDataSimulacao(); 
                return; 
        }
        c.updateSimulacao();
        clearConsole();
    } catch (InputMismatchException e) {
        out.println("Opção inválida. Por favor, insira um número.");
        scanner.nextLine();
        defineDataSimulacao(); 
    } catch (DateTimeException e) {
        out.println("Data inválida. Por favor, insira uma data válida.");
        scanner.nextLine(); 
        defineDataSimulacao();
    }
}

    /*
     * Método que permite saltar no tempo
     */
    public void saltoNoTempo(){
        clearConsole();
        out.println("== Menu mudança de data ==");
        out.println("Data atual: " + c.getDataSimulacao());
        c.setDataSimulacao(scanDataHora());
        c.updateSimulacao();
    }
    /*
     * Método que permite criar um novo utilizador
     */
    public void criarNovoUtilizador() {
        clearConsole();
        out.println("== Menu de registo de utilizador ==");
        try {
            out.println("Email: ");
            String email = scanner.next();
            out.println("Password: ");
            String password = scanner.next();
            out.println("Nome: ");
            String nome = scanner.next();
            out.println("Género (M/F/O): ");
            String genero = scanner.next().toUpperCase();
            out.println("Altura: ");
            double altura = scanner.nextDouble();
            out.println("Peso: ");
            double peso = scanner.nextDouble();
            out.println("Data de nascimento: ");
            LocalDate dataNascimento = scanData();
            out.println("Tipo de utilizador:");
            out.println("1 - Profissional");
            out.println("2 - Ocasional");
            out.println("3 - Amador");
            out.println("Opção: ");
            int utype = scanner.nextInt();
           
            if (!c.addUser(email, password, nome, genero, altura, peso, dataNascimento, utype)) {
                out.println("Utilizador criado com sucesso");
            } else {
                out.println("Utilizador já existe");
            }
        } catch (InputMismatchException e) {
            out.println("Entrada inválida. insira o tipo de dados correto.");
            scanner.nextLine(); 
            criarNovoUtilizador(); 
        }
    }
    

    /*
     * Método que permite iniciar sessão
     */
    public void iniciarSessao() {
        clearConsole();
        out.println("== Menu de login ==\n");
        try {
            out.println("Email: ");
            String email = scanner.next();
            out.println("Password: ");
            String password = scanner.next();
            if (c.iniciarSessao(email, password)) {
                clearConsole();
                out.println("Login efetuado com sucesso");
                String id = c.getViewRequestsID(email);
                perfilUser(id);
            } else {
                out.println("Email ou password incorretos");
            }
        } catch (InputMismatchException e) {
            out.println("Dados de login inválidos");
            scanner.nextLine(); 
            iniciarSessao(); 
        }

    }
    

    /*
     * Método que imprime opções de utilizador registado
     */
    public void perfilUser(String id) {
        out.println("== Perfil de utilizador ==\n");
        out.println("1 - Ver dados pessoais");
        out.println("2 - Ver atividades realizadas");
        out.println("3 - Ver planos de treino\n");
        out.println("4 - Adicionar Atividade Realizada");
        out.println("5 - Adicionar Plano de Treino");
        out.println("6 - Estatísticas da simulação");
        out.println("7 - Menu Inicial");
        out.println("Opção: ");
        try {
            int opcao = scanner.nextInt();
            switch (opcao) {
                case 1:
                    verDadosPessoais(id);
                    break;
                case 2:
                    verAtividadesUser(id);
                    break;
                case 3:
                    verPlanosTreino(id);
                    break;
                case 4:
                    addAtividadeRealizada(id);
                    break;
                case 5:
                    addPlanoTreinoRealizado(id);
                    break;
                case 6:
                    estatisticasSimulação(id);
                    break;
                case 7:
                    simulacaoAtual();
                    break;
                default:
                    out.println("Opção inválida");
                    break;
            }
            perfilUser(id); 
        } catch (InputMismatchException e) {
            out.println("Opção inválida. Por favor, insira um número.");
            scanner.nextLine(); 
            perfilUser(id); 
        } 
    }
    
    /*
     * Método que imprime os dados pessoais de um utilizador
     * @param id - id do utilizador
     */
    public void verDadosPessoais(String id){
        clearConsole();
        out.println("== Dados pessoais ==");
        out.println(c.perfilUser(id));
    }

    /*
     * Método que imprime as atividades realizadas por um utilizador
     * @param id - id do utilizador
     */
    public void verAtividadesUser(String id){
        clearConsole();
        out.println("== Atividades do utilizador ==");
        out.println(c.verAtividadesUser(id));
    }

    /*
     * Método que imprime os planos de treino de um utilizador
     * @param id - id do utilizador
     */
    public void verPlanosTreino(String id){
        clearConsole();
        out.println("== Planos de treino ==");
        out.println(c.verPlanosUser(id));
    }

    /*
     * Método que guarda a simulação inteira ou apenas as atividades e planos de treino
     */

    public void guardarSimulacao() {
        clearConsole();
        out.println("== Guardar simulação ==");
        out.println("1 - Guardar simulação atual");
        out.println("2 - Guardar Atividades e Planos de Treino");
        out.println("3 - Guardar Utilizadores");
        out.println("4 - Menu Simulação\n");
        out.println("Opção: ");
        try {
            int opcao = scanner.nextInt();
            switch (opcao) {
                case 1:
                    out.println("Nome do ficheiro: ");
                    String filename = scanner.next();
                    filename += ".dat";
                    try {
                        c.guardarEstado(filename, "users.csv");
                    } catch (IOException e) {
                        out.println("Erro ao guardar a simulação: " + e.getMessage());
                    }
                    break;
                case 2:
                    c.guardaEstadoATePT();
                    break;
                case 3:
                    c.guardaEstadoUser();
                    break;
                case 4:
                    menuSimulacao();
                    break;
                default:
                    out.println("Opção inválida");
                    break;
            }
        } catch (InputMismatchException e) {
            out.println("Opção inválida. Por favor, insira um número.");
            scanner.nextLine(); 
            guardarSimulacao();
        } catch (IOException | ClassNotFoundException e) {
            out.println("Erro ao executar a opção: " + e.getMessage());
            scanner.nextLine(); 
            guardarSimulacao();
        }
        guardarSimulacao();
    }
    
    /*
     * Método que carrega a simulação inteira ou apenas as atividades e planos de treino
     */

    public void carregarSimulacao() {
        clearConsole();
        out.println("== Carregar simulação ==");
                    out.println("Nome do ficheiro: ");
                    String filename = scanner.next();
                    filename += ".dat";
                    try {
                        c.carregarEstado(filename);
                    } catch (IOException | ClassNotFoundException e) {
                        out.println("Erro ao carregar a simulação: " + e.getMessage());
                    }

    }
    
    
    /*
     * Método que imprime os detalhes da simulação atual
     */
    public void detalhesSimulacao(){
       // clearConsole();
        out.println("== Detalhes da simulação atual ==");
        out.println(c.detalhesSimulacao());
        
    }
    
    /*
     * metodo que mostra o menu de atividades a criar
     */
    public void criarAtividade(String id) {
        try {
            clearConsole();
            out.println("== Criar atividade ==");
            out.println("Tipo de atividade: ");
            out.println("1 - Corrida Terreno");
            out.println("2 - Remo");
            out.println("3 - Alongamentos");
            out.println("4 - Levantamento de peso");
            out.println("5 - Btt");
            int tipo = scanner.nextInt();
            out.println("Nome:");
            String nome = scanner.next();
            LocalDateTime drP = null;
            if (!id.equals("0")) {
                out.println("Data de realização: ");
                drP = scanDataHora();
            }
            out.println("Tempo de duração (minutos): ");
            long duracao = scanner.nextInt();
            switch (tipo) {
                case 1:
                    criarAtividadeCorridaTerreno(nome, duracao, drP, id);
                    break;
                case 2:
                    criarAtividadeRemo(nome, duracao, drP, id);
                    break;
                case 3:
                    criarAtividadeAlongamentos(nome, duracao, drP, id);
                    break;
                case 4:
                    criarAtividadeLevantamentoPeso(nome, duracao, drP, id);
                    break;
                case 5:
                    criarAtividadeBtt(nome, duracao, drP, id);
                    break;
                default:
                    out.println("Opção inválida");
                    break;
            }
        } catch (InputMismatchException e) {
            out.println("Opção inválida. Por favor, insira um número.");
            scanner.nextLine(); 
            criarAtividade(id); 
        }
    }
    

    /*
     * Método que mostra o menu uma atividade de corrida terreno a criar
     * @param nome - nome da atividade
     * @param duracao - duração da atividade em minutos
     * @param dr - data de realização da atividade
     * @param id - id do utilizador
     */
    public void criarAtividadeCorridaTerreno(String nome, long duracao, LocalDateTime dr, String id){
        try {
            out.println("Distância: ");
            double distancia = scanner.nextDouble();
            out.println("Altimetria: ");
            double altimetria = scanner.nextDouble();
            out.println("Tipo de terreno: ");
            out.println("1 - Estrada");
            out.println("2 - Trilho");
            out.println("3 - Monte");
            out.println("4 - Pista");
            int tipo = scanner.nextInt();
            c.criarAtividadeCorridaTerreno(nome, duracao, distancia, altimetria, tipo, dr, id);
        } catch (InputMismatchException e) {
            out.println("Tipo de dados inválidos");
            scanner.nextLine(); 
            criarAtividadeCorridaTerreno(nome, duracao, dr, id); 
        }
    }

    /*
     * Método que mostra o menu uma atividade de remo a criar
     * @param nome - nome da atividade
     * @param duracao - duração da atividade em minutos
     * @param dr - data de realização da atividade
     * @param id - id do utilizador
     */
    public void criarAtividadeRemo(String nome, long duracao, LocalDateTime dr, String id){
        try {
            out.println("Distância: ");
            double distancia = scanner.nextDouble();
            c.criarAtividadeRemo(nome, duracao, distancia, dr, id);
        } catch (InputMismatchException e) {
            out.println("Tipo de dados inválidos");
            scanner.nextLine(); 
            criarAtividadeRemo(nome, duracao, dr, id); 
        }
    }
    
    /*
     * Método que mostra o menu uma atividade de alongamentos a criar
     * @param nome - nome da atividade
     * @param duracao - duração da atividade em minutos
     * @param dr - data de realização da atividade
     * @param id - id do utilizador
     */
    public void criarAtividadeAlongamentos(String nome, long duracao, LocalDateTime dr, String id){

        try {
            out.println("Repeticões: ");
            int repeticoes = scanner.nextInt();
            out.println("Séries: ");
            int series = scanner.nextInt();
            out.println("Parte do corpo: ");
            out.println("1 - Superiores");
            out.println("2 - Inferiores");
            out.println("3 - Tronco");
            out.println("4 - Outro");
            int parteCorpo = scanner.nextInt();
            c.criarAtividadeAlongamentos(nome, dr, duracao, parteCorpo, repeticoes, series, id);
        } catch (InputMismatchException e) {
            out.println("Tipo de dados inválidos");
            scanner.nextLine(); 
            criarAtividadeAlongamentos(nome, duracao, dr, id); 
        }

    }

    /*
     * Método que mostra o menu uma atividade de levantamento de peso a criar
     * @param nome - nome da atividade
     * @param duracao - duração da atividade em minutos
     * @param dr - data de realização da atividade
     * @param id - id do utilizador
     */
    public void criarAtividadeLevantamentoPeso(String nome, long duracao, LocalDateTime dr, String id){
        try {
            out.println("Peso: ");
            double peso = scanner.nextDouble();
            out.println("Repetições: ");
            int repeticoes = scanner.nextInt();
            out.println("Séries: ");
            int series = scanner.nextInt();
            c.criarAtividadeLevantamentoPeso(nome, dr, duracao, repeticoes, series, peso,id);
        } catch (InputMismatchException e) {
            out.println("Tipo de dados inválidos");
            scanner.nextLine();
            criarAtividadeLevantamentoPeso(nome, duracao, dr, id); 
        }
    }

    /*
     * Método que mostra o menu uma atividade de Btt a criar
     * @param nome - nome da atividade
     * @param duracao - duração da atividade em minutos
     * @param dr - data de realização da atividade
     * @param id - id do utilizador
     */
    public void criarAtividadeBtt(String nome, long duracao, LocalDateTime dr, String id){
        try{
            out.println("Distância: ");
            double distancia = scanner.nextDouble();
            out.println("Altimetria: ");
            double altimetria = scanner.nextDouble();
            out.println("Tipo de terreno: ");
            out.println("1 - Estrada");
            out.println("2 - Trilho");
            out.println("3 - Monte");
            out.println("4 - Pista");
            int tipo = scanner.nextInt();
            out.println("Dificuldade: (1-5)");
            int dificuldade = scanner.nextInt();
            c.criarAtividadeBtt(nome, dr, duracao, distancia, altimetria, tipo, dificuldade, id);
        } catch (InputMismatchException e) {
            out.println("Tipo de dados inválidos");
            scanner.nextLine();
            criarAtividadeBtt(nome, duracao, dr, id);
        }
        
    }

    /*
     * Método que lê uma data
     * @return data
     */
    public LocalDate scanData(){
        try {
            out.println("Ano: ");
            int ano = scanner.nextInt();
            out.println("Mês: ");
            int mes = scanner.nextInt();
            out.println("Dia: ");
            int dia = scanner.nextInt();
            return LocalDate.of(ano, mes, dia);
        } catch (Exception e) {
            out.println("Data inválida");
            return scanData();
        }
    }

    /*
     * Método que lê uma data e hora
     * @return data e hora
     */
    public LocalDateTime scanDataHora(){
        try {
            out.println("Ano: ");
            int ano = scanner.nextInt();
            out.println("Mês: ");
            int mes = scanner.nextInt();
            out.println("Dia: ");
            int dia = scanner.nextInt();
            out.println("Hora: ");
            int hora = scanner.nextInt();
            out.println("Minutos: ");
            int minutos = scanner.nextInt();
            return LocalDateTime.of(ano, mes, dia, hora, minutos);
        } catch (Exception e) {
            out.println("Data inválida");
            return scanDataHora();
        }
    }

    /*
     * Método que imprime o menu de admin
     */
    public void menuAdmin() throws IOException, ClassNotFoundException{
        out.println("== Menu Admin ==\n");
        out.println("1 - Criar atividade pré-definida");
        out.println("2 - Criar plano de treino pré-definido");
        out.println("3 - Saltar no tempo");
        out.println("4 - Guardar simulação");
        out.println("5 - Carregar atividades e planos de treino pré-definidos");
        out.println("6 - Carregar utilizadores");
        out.println("7 - Menu Simulação\n");
        out.println("Opção: ");
        try {
            int out = scanner.nextInt();
            switch (out) {
                case 1:
                    criarAtividadeAdmin();
                    break;     
                case 2:
                    criarPlanoTreinoAdmin();
                    break;
                case 3:
                    saltoNoTempo();
                    break;
                case 4:
                    guardarSimulacao();
                    break;
                case 5:
                    c.carregaEstadoATePT();
                    detalhesSimulacao();
                    simulacaoAtual();
                    break;
                case 6:
                    c.carregaEstadoUser();
                    detalhesSimulacao();    
                    simulacaoAtual();
                    break;
                case 7:
                    simulacaoAtual();
                    break;
            }
        } catch (InputMismatchException e) {
            out.println("Opção inválida. Por favor, insira um número.");
            scanner.nextLine(); 
            menuAdmin(); 
        }
        menuAdmin();
    }

    /*
     * Método que imprime o menu de atividades pré-definidas a criar
     */
    public void criarAtividadeAdmin(){
        clearConsole();
        out.println("== Criar atividade pré-definida ==");
        criarAtividade("0");
    }

    /*
     * Método que imprime o menu de estatísticas da simulação
     * @param id - id do utilizador
     */
    public void estatisticasSimulação(String id) {
        out.println("== Estatísticas da simulação ==");
        out.println("1 - Utilizador que mais dispendeu calorias");
        out.println("2 - Utilizador com mais atividades realizadas");
        out.println("3 - Tipo de atividade mais realizada");
        out.println("4 - Kms totais percorridos por utilizador");
        out.println("5 - Metros de altimetria totais por utilizador");
        out.println("6 - Plano de treino mais exigente");
        out.println("7 - Listar atividades de um utilizador");
        out.println("8 - Menu Inicial");
        out.println("Opção: ");
        try {
            int opcaoEst = scanner.nextInt();
            int opcaoData = 0;
            LocalDate datain = null, datafim = null;
            if (opcaoEst == 1 || opcaoEst == 2 || opcaoEst == 4 || opcaoEst == 5) {
                out.println("1 - Desde sempre");
                out.println("2 - Periodo");
                out.println("Opção: ");
                opcaoData = scanner.nextInt();
                if (opcaoData == 2) {
                    out.println("Data de início: ");
                    datain = scanData();
                    out.println("Data de fim: ");
                    datafim = scanData();
                }
            }
            out.println(c.estatisticasSimulacao(id, opcaoEst, opcaoData, datain, datafim));
            if (opcaoEst == 8) {
                perfilUser(id);
            }
            estatisticasSimulação(id); 
        } catch (InputMismatchException e) {
            out.println("Opção inválida. Por favor, insira tipo de dados correto.");
            scanner.nextLine(); 
            estatisticasSimulação(id); 
        }
    }
    
    
    /*
     * Método que imprime o menu de adicionar atividades realizadas
     * @param id - id do utilizador
     */
    public void addAtividadeRealizada(String id) {
        clearConsole();
        out.println("== Adicionar atividade realizada ==");
        out.println("1 - Criar nova atividade");
        out.println("2 - Adicionar atividade pré-definida");
        out.println("3 - Menu utilizador");
        out.println("Opção: ");
        try {
            int opcao = scanner.nextInt();
            switch (opcao) {
                case 1:
                    criarAtividade(id);
                    break;
                case 2:
                    for (int i = 0; i < c.getAtividadesSize(); i++) {
                        out.println(i + " - " + c.getAtividades(i));
                    }
                    out.println("Opção: ");
                    int idAtv = scanner.nextInt();
                    out.println("Data de realização: ");
                    LocalDateTime drP = scanDataHora();
                    c.registaAtividadePre(id, idAtv, drP);
                    break;
                case 3:
                    perfilUser(id);
                    break;
                default:
                    out.println("Opção inválida");
                    break;
            }
        } catch (InputMismatchException e) {
            out.println("Opção inválida. Por favor, insira um número.");
            scanner.nextLine();
            addAtividadeRealizada(id); 
        }
    }
    

    /*
     * Método que imprime o menu de adicionar plano de treino
     * @param id - id do utilizador
     */
    public void addPlanoTreinoRealizado(String id){
        clearConsole();
        out.println("== Adicionar plano de treino ==");
        for (int i = 0; i < c.getPlanosSize(); i++) {
            out.println(i + " - " + c.getPlanos(i));
        }
        out.println("Opção: ");
        int idPlano = scanner.nextInt();
        c.registaPlanoPre(id, idPlano);
    }

    /*
     * Método que imprime o menu de criar plano de treino pré-definido
     */
    public void criarPlanoTreinoAdmin() {
        clearConsole();
        out.println("== Criar plano de treino pré-definido ==");
        out.println("Data de realização: ");
        LocalDate drP = scanData();
        out.println("Periodicidade: ");
        out.println("1 - Diário");
        out.println("2 - 2 em 2 dias");
        out.println("3 - 3 em 3 dias");
        out.println("4 - Semanal");
        out.println("5 - Mensal");
        out.println("6 - Outro");
        int periodicidade = scanner.nextInt();
        out.println("Atividades: ");
        out.println("0 - Concluído");
        int opcao = -1;
        int[] idAtvs = new int[c.getAtividadesSize()];
        while (opcao != 0) {
            for (int i = 1; i <= c.getAtividadesSize(); i++) {
                out.println(i + " - " + c.getAtividades(i - 1));
            }
            out.println("Opção: ");
            opcao = scanner.nextInt();
            if (opcao != 0) {
                idAtvs[opcao - 1] = opcao - 1;
            }
        }
        c.registaPlanoPre(drP, periodicidade, idAtvs);
    }
    
}


