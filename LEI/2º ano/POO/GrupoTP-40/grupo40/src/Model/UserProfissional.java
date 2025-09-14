package Model;

import java.time.LocalDate;
public class UserProfissional extends Utilizador {

    /*
     * Construtor vazio
     * Inicializa as variáveis de instância com valores por defeito
     */
    public UserProfissional() {
        super();
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
    public UserProfissional(String email, String password, String nome, Genero genero, double altura, double peso, LocalDate dataNascimento) {
        super(email, password, nome, genero, altura, peso, dataNascimento);
    }

    /*
     * Construtor de cópia
     * @param u - objeto do tipo Utilizador
     */
    public UserProfissional(Utilizador u) {
        super(u);
    }

    /* 
     * toString do objeto UserProfissional
     * @return String com as informações do objeto
     */
    public String toString() {
        return super.toString();
    }

    /* 
     * equals do objeto UserProfissional
     * @param o - objeto a comparar
     * @return true se forem iguais, false se forem diferentes
     */
    public boolean equals(Object o) {
        return super.equals(o);
    }

    // metodos super
    /*
     * Clone de UserProfissional
     * @return cópia do objeto do tipo UserProfissional
     */
    @Override
    public UserProfissional clone() {
        return new UserProfissional(this);
    }
    /*
     * Método que calcula o fator de calorias para um utilizador profissional com uma fórmula específica. Este fator é utilizado para calcular as calorias gastas numa atividade
     * @return fator de calorias
     */
    @Override
    public double calculaFatorCalorias(){
        // max: 1.3
        // min: 0.9
        double fator = 0.5; // default para profissionais
        fator += (this.getGenero() == Genero.Masculino) ? 0.6 : 0.4;
        fator += (this.getPeso() > 80) ? 0.2 : 0.1;
        fator += (this.getPeso() < 70) ? 0 : 0.1;
        return fator;
    }

    /*
     * Método que calcula a frequência cardíaca média de um utilizador profissional em repouso
     * @return frequência cardíaca média do utilizador em repouso
     */
    public double calcularfrequanciaCardiacaMediaRepouso() {
        double FCMR;
        if (getGenero().equals(Genero.Masculino)) {
            FCMR = 210 - (0.5 * idade()) + (0.11 * getPeso()) - (5.6 * getAltura());
        } else {
            FCMR = 210 - (0.5 * idade()) + (0.11 * getPeso()) - (5.6 * getAltura()) - 20;
        }
        return FCMR * 0.35;
    }
    
    
    

    
}
