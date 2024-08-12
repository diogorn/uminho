package Model;


import java.io.Serializable;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;
import java.util.stream.Collectors;

public abstract class Utilizador implements Serializable {

    // login
    private String id;
    private String email;
    private String password;

    // dados pessoais
    private String nome;
    private Genero genero;
    private double altura;
    private double peso;
    private LocalDate dataNascimento;

    private double frequanciaCardiacaMediaRepouso; 


    private double fatorMultiplicativoCalorias; // calculado a partir do genero, idade, peso, altura, frequencia cardiaca media
    private Map<String, Atividade> atividades; // atividades realizadas pelo utilizador
    private Map<String, PlanoTreino> planodeTreino; // planos de treino do utilizador 

    
    /*
     * Construtor vazio
     * Inicializa as variáveis de instância com valores por defeito
     */
    public Utilizador() {
        this.id = geraId();
        this.email = "";
        this.password = "";
        this.nome = "";
        this.genero = Genero.Outro;
        this.altura = 0;
        this.peso = 0;
        this.dataNascimento = LocalDate.now();
        this.frequanciaCardiacaMediaRepouso = 0.0;
        this.fatorMultiplicativoCalorias=0.0;
        this.atividades = new HashMap<>();
        this.planodeTreino = new HashMap<>();
    }
    /*
     * Construtor parametrizado
     * @param email - email do utilizador
     * @param password - password do utilizador
     * @param nome - nome do utilizador
     * @param genero - genero do utilizador
     * @param altura - altura do utilizador
     * @param peso - peso do utilizador
     * @param dataNascimento - data de nascimento do utilizador
     */
    public Utilizador(String email, String password, String nome, Genero genero, double altura, double peso, LocalDate dataNascimento) {
        this.id = geraId();
        this.email = email;
        this.password = password;
        this.nome = nome;
        this.genero = genero;
        this.altura = altura;
        this.peso = peso;
        this.dataNascimento = dataNascimento;
        this.frequanciaCardiacaMediaRepouso = calcularfrequanciaCardiacaMediaRepouso();
        this.fatorMultiplicativoCalorias= calculaFatorCalorias();
        this.atividades = new HashMap<>();
        this.planodeTreino = new HashMap<>();

    }
    /*
     * Construtor de cópia
     * @param utilizador - objeto do tipo Utilizador
     */
    public Utilizador(Utilizador utilizador) {
        this.id = utilizador.getId();
        this.email = utilizador.getEmail();
        this.password = utilizador.getPassword();
        this.nome = utilizador.getNome();
        this.genero = utilizador.getGenero();
        this.altura = utilizador.getAltura();
        this.peso = utilizador.getPeso();
        this.dataNascimento = utilizador.getDataNascimento();
        this.frequanciaCardiacaMediaRepouso = calcularfrequanciaCardiacaMediaRepouso();
        this.fatorMultiplicativoCalorias= calculaFatorCalorias(); 
        this.atividades = utilizador.getAtividades();
        this.planodeTreino = utilizador.getPlanodeTreino();
    }

    /*
     * Método que gera um id para o utilizador
     * @return id gerado
     */
    public String geraId(){
        return UUID.randomUUID().toString();
    }
    /*
     * Getter do id do utilizador
     * @return id do utilizador
     */
    public String getId() {
        return id;
    }
    /*
     * Getter do email do utilizador
     * @return email do utilizador
     */
    public String getEmail() {
        return email;
    }
    /*
     * Getter da password do utilizador
     * @return password do utilizador
     */
    public String getPassword() {
        return password;
    }
    /*
     * Getter do nome do utilizador
     * @return nome do utilizador
     */

    public String getNome() {
        return nome;
    }
    /*
     * Getter do genero do utilizador
     * @return genero do utilizador de acordo com o Enum Genero
     */
    public Genero getGenero() {
        return genero;
    }

    /*
     * Getter da altura do utilizador
     * @return altura do utilizador em metros
     */
    public double getAltura() {
        return altura;
    }

    /*
     * Getter do peso do utilizador
     * @return peso do utilizador em kg
     */
    public double getPeso() {
        return peso;
    }

    /*
     * Getter da data de nascimento do utilizador
     * @return data de nascimento do utilizador
     */
    public LocalDate getDataNascimento() {
        return dataNascimento;
    }

    /*
     * Getter da frequencia cardiaca media em repouso
     * @return frequencia cardiaca media em repouso do utilizador
     */
    public double getfrequanciaCardiacaMediaRepouso(){
        return this.frequanciaCardiacaMediaRepouso;
    }

    /*
     * Getter do fator multiplicativo de calorias
     * @return fator multiplicativo de calorias do utilizador
     */
    public double getfatorMultiplicativoCalorias(){
        return this.fatorMultiplicativoCalorias;
    }

    /*
     * Getter das atividades realizadas pelo utilizador
     * @return clone do map com as atividades realizadas pelo utilizador
     */
    public Map<String, Atividade> getAtividades() {
        return atividades.entrySet().stream().collect(Collectors.toMap(k->k.getKey(), v-> v.getValue().clone()));
    }

    /*
     * Getter dos planos de treino do utilizador
     * @return clone do map com os planos de treino do utilizador
     */

    public Map<String, PlanoTreino> getPlanodeTreino() {
        return planodeTreino.entrySet().stream().collect(Collectors.toMap(k->k.getKey(), v-> v.getValue().clone()));
    }

    // setters

    /*
     * Setter do email do utilizador
     * @param email - email do utilizador
     */
    public void setEmail(String email) {
        this.email = email;
    }
    /*
     * Setter da password do utilizador
     * @param password - password do utilizador
     */
    public void setPassword(String password) {
        this.password = password;
    }
    /*
     * Setter do nome do utilizador
     * @param nome - nome do utilizador
     */
    public void setNome(String nome) {
        this.nome = nome;
    }
    /*
     * Setter do genero do utilizador
     * @param genero - genero do utilizador
     */
    public void setGenero(Genero genero) {
        this.genero = genero;
    }
    /*
     * Setter da altura do utilizador
     * @param altura - altura do utilizador
     */
    public void setAltura(double altura) {
        this.altura = altura;
    }
    /*
     * Setter do peso do utilizador
     * @param peso - peso do utilizador
     */
    public void setPeso(double peso) {
        this.peso = peso;
    }
    /*
     * Setter da data de nascimento do utilizador
     * @param dataNascimento - data de nascimento do utilizador
     */
    public void setDataNascimento(LocalDate dataNascimento) {
        this.dataNascimento = dataNascimento;
    }
    /*
     * Setter da frequencia cardiaca media em repouso
     * @param frequanciaCardiacaMediaRepouso - frequencia cardiaca media em repouso do utilizador
     */
    public double SetfrequanciaCardiacaMediaRepouso(double frequanciaCardiacaMediaRepouso){
        return this.frequanciaCardiacaMediaRepouso = frequanciaCardiacaMediaRepouso;
    }
    /*
     * Setter do fator multiplicativo de calorias
     * @param fatorMultiplicativoCalorias - fator multiplicativo de calorias do utilizador
     */
    public double SetfatorMultiplicativoCalorias(double fatorMultiplicativoCalorias){
        return this.fatorMultiplicativoCalorias = fatorMultiplicativoCalorias;
    }
    /*
     * Setter das atividades realizadas pelo utilizador - deep copy
     * @param atividades - map com as atividades realizadas pelo utilizador
     */
    public void setAtividades(Map<String, Atividade> atividades) {
        this.atividades =  atividades.entrySet().stream().collect(Collectors.toMap(k->k.getKey(), v-> v.getValue().clone()));
    }

    /*
     * Setter dos planos de treino do utilizador - deep copy
     * @param planodeTreino - map com os planos de treino do utilizador
     */
    public void setPlanodeTreino(Map<String, PlanoTreino> planodeTreino) {
        this.planodeTreino = planodeTreino.entrySet().stream().collect(Collectors.toMap(k->k.getKey(), v-> v.getValue().clone()));
    }

    
    /*
     * Método que verifica se um objeto é igual a uma instância da classe Utilizador
     * @param obj - objeto a comparar
     * @return true se o objeto for igual ao objeto do tipo Utilizador, false se o objeto for diferente do objeto do tipo Utilizador
     */
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || this.getClass() != obj.getClass()) return false;
        Utilizador u = (Utilizador) obj;
        return  this.id.equals(u.getId()) &&
                this.email.equals(u.getEmail()) &&
                this.password.equals(u.getPassword()) &&
                this.nome.equals(u.getNome()) &&
                this.genero == u.getGenero() &&
                this.altura == u.getAltura() &&
                this.peso == u.getPeso() &&
                this.dataNascimento.equals(u.getDataNascimento()) &&
                this.frequanciaCardiacaMediaRepouso == u.getfrequanciaCardiacaMediaRepouso() &&
                this.fatorMultiplicativoCalorias == u.getfatorMultiplicativoCalorias() &&
                this.atividades.equals(u.getAtividades()) &&
                this.planodeTreino.equals(u.getPlanodeTreino());
                // == para tipos primitivos, .equals para objetos
    }

    /*
     * Método que converte um objeto do tipo Utilizador para uma String
     * @return String com informações sobre o utilizador
     */
    public String toString() {
        return "Utilizador{" +
                "id=" + getId() + 
                ", email='" + getEmail() + '\'' +
                ", password='" + getPassword() + '\'' +
                ", nome='" + getNome() + '\'' +
                ", genero=" + getGenero() +
                ", altura=" + getAltura() +
                ", peso=" + getPeso() +
                ", dataNascimento=" + getDataNascimento() +
                ", frequanciaCardiacaMediaRepouso=" + getfrequanciaCardiacaMediaRepouso() +
                ", fatorMultiplicativoCalorias=" + getfatorMultiplicativoCalorias() +
                '}';
    }
    // metodos super
    /*
     * Método que calcula a idade de um utilizador
     * @param data - data da simulação
     * @return idade do utilizador
     */
    public int idade(LocalDate data){
        return data.getYear() - getDataNascimento().getYear();
    }
    // metodos maps atividades e planos de treino

    /*
     * Método que adiciona uma atividade REALIZADA ao map de atividades do utilizador
        * @param a - atividade realizada
     */
    public void addAtividade(Atividade a){
        this.atividades.put(a.getId(), a.clone());

    }

    /*
     * Método que remove uma atividade REALIZADA do map de atividades do utilizador
     * @param a - atividade realizada
     */
    public void removeAtividade(Atividade a){
        this.atividades.remove(a.getId());
    }

    /*
     * Método que adiciona um plano de treino ao map de planos de treino do utilizador
     * @param p - plano de treino
     */
    public void addPlanoTreino(PlanoTreino p){
        this.planodeTreino.put(p.getId(), p.clone());
    }

    /*
     * Método que remove um plano de treino do map de planos de treino do utilizador
     * @param p - plano de treino
     */
    public void removePlanoTreino(PlanoTreino p){
        this.planodeTreino.remove(p.getId());
    }

    // metodos
    /*
     * Método que calcula a idade de um utilizador
     * @return idade do utilizador
     */
    public int idade(){
        return getDataNascimento().until(LocalDate.now()).getYears();
    }
    
    // metodos abstratos
    /*
     * Clone de Utilizador
     * @return cópia do objeto do tipo Utilizador
     */
    public abstract Utilizador clone();
      /*
     * Método que calcula o fator de calorias de um utilizador. A fórmula utilizada é específica para cada tipo de utilizador e o valor calculado é utilizado para calcular as calorias gastas numa atividade
     */
    public abstract double calculaFatorCalorias();
    /*
     * Método que calcula a frequencia cardiaca media em repouso de um utilizador
     * @return frequencia cardiaca media em repouso do utilizador
     */

    public abstract double calcularfrequanciaCardiacaMediaRepouso();
}
