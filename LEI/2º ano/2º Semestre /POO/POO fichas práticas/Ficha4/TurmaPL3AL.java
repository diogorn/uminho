import java.sql.Array;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import javax.swing.text.html.HTMLDocument.Iterator;

public class TurmaPL3AL { // turma é uma composição de alunos
    private String designação;
    private List<Aluno> alunos;

    public TurmaPL3AL() {
        this.designação = "";
        this.alunos = new ArrayList<Aluno>();
    }
    
    public TurmaPL3AL(String designação, List<Aluno> alunosInscritos){
        this.designação = designação;
        // this.alunos = alunosInscritos; -- nem a estrutura de dados é da Turma
        // this.alunos = alunosInscritos.clone(); -- não existe metodo clone em List 
        // this.alunos = new ArrayList<Alunos>(alunosInscritos); -- nao faz o clone dos conteudos
        this.alunos = new ArrayList<Aluno>();
        // this.alunos.addAll(alunosInscritos); -- addAll nao faz clone, logo nao serve 
        for(Aluno a : alunosInscritos){
            this.alunos.add(a.clone());
        }
            
    }


    // construtor de copia 
    /*
    public List<Aluno> getAlunos(){
        List<Aluno> copia = new ArrayList<Aluno>();
        for(Aluno a : this.alunos){
            copia.add(a.clone());
        }
        return copia;
    } */
    public List<Aluno> getAlunos(){
        return this.alunos.stream.map(Aluno::clone).collect(Collectors.toList());
    }

    public String getDesignação(){
        return this.designação;
    }

    public void addAluno(Aluno umAluno){
        this.alunos.add(umAluno.clone());
    }
    public boolean existeAluno(Aluno umAluno){
        return this.alunos.contains(umAluno);
    }

    public boolean existeAlunoComNumero(String num){
        boolean encontrado = false;
        for(int i=0; i<this.alunos.size() && !encontrado;i++){
            if(this.alunos.get(i).getNumero().equals(num)){
                encontrado = true;
            }
        }
        return encontrado;
    }
     // nao podemos remover com for 
     // iterator é implementado pela estrututa logo gere a remoção
    public boolean existeAlunoComNumero2(String num){ // percorrer coleção e parar a meio
        boolean encontrado = false;
        Iterator<Aluno> it =  this.alunos.iterator();

        while(it.hasNext() && !encontrado){
            Aluno a = it.next();
            if(a.getNumero().equals(num)){
                encontrado = true;
            }
        }
        return encontrado;
    }

    public int posAluno(String numero){
        int pos =-1;
        boolean encontrado = false;
        Iterator<Aluno> it = this.alunos.iterator();
        while(it.hasNext() && !encontrado){
            Aluno a = it.next();
            pos++;
            if(a.getNumero().equals(numero)){
                encontrado = true;
            }


        } 
        return encontrado ? pos : -1;

    }


    public void removeAluno(String num){
       int pos = posAluno(num);
         if(pos != -1){
              this.alunos.remove(pos);
         }
    }

    public List<Aluno> listaAlunosPassam(){
        return this.alunos.stream().filter(a -> a.getNota()>=10)
        .map(Aluno::clone) // map(a -> a.clone())
        .collect(Collectors.toList());
    }
    // obter ordenação dos alunos por ordem alfabetica do nome
    public List<Aluno> listaAlunosOrdemAlfabetica(){
        return this.alunos.stream().map(Aluno::clone).sorted().collect(Collectors.toSet());
    }
// metodo que ordena pela classificação (crescente)
public List<Aluno> ordemCrescenteNota(){
    Comparator<Aluno> comp = (a1,a2) -> a2.getNota() - a1.getNota(); 
    return this.alunos.stream()
                        .map(Aluno::clone)
                        .sorted(comp)
                        .collect(Collectors.toList());
} 

public List<Aluno> ordemCrescenteNotaV2(){
    Comparator<Aluno> comp = (a1,a2) -> a2.getNota() - a1.getNota(); 

    TreeSet<Aluno> res = new TreeSet(comp);
    for(Aluno a : this.alunos){
        res.add(a.clone());
    }
    return res;
}
