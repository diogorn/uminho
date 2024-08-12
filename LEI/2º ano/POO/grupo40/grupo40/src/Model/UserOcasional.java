package Model;

import java.time.LocalDate;

public class UserOcasional extends Utilizador{

    /*
     * Construtor vazio
     * Inicializa as variáveis de instância com valores por defeito
     */
    public UserOcasional() {
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
    public UserOcasional(String email, String password, String nome, Genero genero, double altura, double peso, LocalDate dataNascimento) {
        super(email, password, nome, genero, altura, peso, dataNascimento);
    }
    /*
     * Construtor de cópia
     * @param u - objeto do tipo Utilizador
     */
    public UserOcasional(Utilizador u) {
        super(u);
    }
    
    /* 
     * toString do objeto UserOcasional
     * @return String com as informações do objeto
     */
    public String toString() {
        return super.toString();
    }
    /* 
     * equals do objeto UserOcasional
     * @param o - objeto a comparar
     * @return true se forem iguais, false se forem diferentes
     */
    public boolean equals(Object o) {
        return super.equals(o);
    }

    /*
     * Clone de UserOcasional
     * @return cópia do objeto do tipo UserOcasional
     */
    @Override
    public UserOcasional clone() {
        return new UserOcasional(this);
    }

    /*
     * Método que calcula o fator de calorias de um utilizador ocasional. A fórmula utilizada é específica para este tipo de utilizador e o valor calculado é utilizado para calcular as calorias gastas numa atividade
     * @return fator de calorias
     */
    @Override
    public double calculaFatorCalorias(){
        // max: 0.5
        // min: 0.2
        double fator = 0.1; // default para ocasionais
        fator += (this.getGenero() == Genero.Masculino) ? 0.2 : 0.1;
        fator += (this.getPeso() > 89) ? 0.2 : 0.1;
        fator += (this.getPeso() < 60) ? 0 : 0.1;
        return fator;
    }

    /*
     * Método que calcula a frequência cardíaca média de um utilizador ocasional durante uma atividade
     * @return frequência cardíaca média
     */
    public double calcularfrequanciaCardiacaMediaRepouso() {
        double FCMR;
        if (getGenero().equals(Genero.Masculino)) {
            FCMR = 210 - (0.5 * idade()) + (0.11 * getPeso()) - (5.6 * getAltura());
        } else {
            FCMR = 210 - (0.5 * idade()) + (0.11 * getPeso()) - (5.6 * getAltura()) - 20;
        }
        return FCMR * 0.42; 
    }
}
