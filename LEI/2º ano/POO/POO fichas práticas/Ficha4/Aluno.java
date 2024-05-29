
public class Aluno implements Comparable<Aluno>{
    private String nome;
    private String numero;
    private int idade;
    private String curso;

    // Construtor
    public Aluno() {
        this.nome = "";
        this.numero = "";
        this.idade = 0;
        this.curso = "";
    }
    public Aluno(String nome,String numero, int idade, String curso) {
        this.nome = nome;
        this.numero = numero;
        this.idade = idade;
        this.curso = curso;
    }
    public Aluno(Aluno aluno) {
        this.nome = aluno.getNome();
        this.numero = aluno.getNumero();
        this.idade = aluno.getIdade();
        this.curso = aluno.getCurso();
    }

    // Método para obter o nome do aluno
    public String getNome() {
        return nome;
    }

    // Método para definir o nome do aluno
    public void setNome(String nome) {
        this.nome = nome;
    }

    // Método para obter o número do aluno
    public String getNumero() {
        return numero;
    }

    // Método para definir o número do aluno
    public void setNumero(String numero) {
        this.numero = numero;
    }

    // Método para obter a idade do aluno
    public int getIdade() {
        return idade;
    }

    // Método para definir a idade do aluno
    public void setIdade(int idade) {
        this.idade = idade;
    }

    // Método para obter o curso do aluno
    public String getCurso() {
        return curso;
    }

    // Método para definir o curso do aluno
    public void setCurso(String curso) {
        this.curso = curso;
    }

    public toString() {
        return this.nome + " " + this.numero + " " + this.idade + " " + this.curso;
    }

    public equals (Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        Aluno a = (Aluno) o;
        return this.nome.equals(a.getNome()) && this.numero.equals(a.getNumero()) && this.idade == a.getIdade() && this.curso.equals(a.getCurso());
    }

    public Aluno clone() {
        return new Aluno(this);
    }

    public int compareTo(Aluno a) {
        return this.nome.compareTo(a.getNome());
    }

}