package Model;

import java.time.LocalDate;

public class UserAmador extends Utilizador{

    /*
     * Construtor vazio
     * Inicializa as variáveis de instância com valores por defeito
     */
    public UserAmador() {
        super();
    }
    /*
     * Construtor com argumentos
     * @param email - email do utilizador
     * @param password - password do utilizador
     * @param nome - nome do utilizador
     * @param genero - genero do utilizador
     * @param altura - altura do utilizador
     * @param peso - peso do utilizador
     * @param dataNascimento - data de nascimento do utilizador
     */
    public UserAmador(String email, String password, String nome, Genero genero, double altura, double peso, LocalDate dataNascimento) {
        super(email, password, nome, genero, altura, peso, dataNascimento);
    }
    /*
     * Construtor de cópia
     * @param u - objeto do tipo Utilizador
     */
    public UserAmador(Utilizador u) {
        super(u);
    }

    /* 
     * toString do objeto UserAmador
     * @return String com as informações do objeto
     */
    public String toString() {
        return super.toString();
    }

    /* 
     * equals do objeto UserAmador
     * @param o - objeto a comparar
     * @return true se forem iguais, false se forem diferentes
     */
    public boolean equals(Object o) {
        return super.equals(o);
    }
    
    /*
     * Clone de UserAmador
     * @return cópia do objeto do tipo UserAmador
     */
    @Override
    public UserAmador clone() {
        return new UserAmador(this);
    }

    /*
     * Método que calcula o fator de calorias de um utilizador amador com uma fórmula específica. Este fator é utilizado para calcular as calorias gastas numa atividade
     * @return fator de calorias
     */
    @Override
    public double calculaFatorCalorias(){
        // max: 0.9
        // min: 0.6
        double fator = 0.3; // default para amadores
        fator += (this.getGenero() == Genero.Masculino) ? 0.4 : 0.2;
        fator += (this.getPeso() > 95) ? 0.2 : 0.1;
        fator += (this.getPeso() < 70) ? 0 : 0.1;
        return fator;
    }

    /*
     * Método que calcula a frequência cardíaca média de um utilizador amador em repouso
     * @return frequência cardíaca média em repouso
     */
    @Override
    public double calcularfrequanciaCardiacaMediaRepouso() {
        double FCMR;
        if (getGenero().equals(Genero.Masculino)) {
            FCMR = 210 - (0.5 * idade()) + (0.11 * getPeso()) - (5.6 * getAltura());
        } else {
            FCMR = 210 - (0.5 * idade()) + (0.11 * getPeso()) - (5.6 * getAltura()) - 20;
        }
        return FCMR * 0.38; 
    }
    
    
}
