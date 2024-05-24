import java.io.FileInputStream;

import java.io.FileOutputStream;


public class Aluno {
    
    public Map<String, Aluno> getAlunos() {
        Map<String, Aluno> res = new HashMap<>();

        for(Aluno a: this.alunos.values()) {
            res.put(a.getNumero(), a);
        }
        return res;
    }
/* 
    public Map<String, Aluno> getAlunos2() {
        Map<String, Aluno> res = new HashMap<>();

        for(String getNumero: this.alunos.keySet()) {
            res.put(e.put(getKey(), e.getValue()));
        }
        return res;
    }
*/ // -- errado/incompleto 

    public String toString() {
       return 0;
    }
    // guardar
    public void escreveEmFicheiro(String nomeFicheiro) throws IOException{
        
        PrintWriter ficheiro = new PrintWriter(nomeFicheiro);
        ficheiro.println(this.toString());
        ficheiro.flush();
        ficheiro.close();
        


    }

    public void guardaEstado(String nomeFicheiro) throws FileNotFoundException, IOException{
        FileOutputStream fos = new FileOutputStream(nomeFicheiro);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this); //se a classe implementar Serializable

        oos.flush();
        oos.close();
    }
    // carregar
    public static TurmaMap carregaEstado(String nomeFicheiro) throws FileNotFoundException, IOException {
        FileInputStream fis = new FileInputStream(nomeFicheiro);
        ObjectInputStream ois = new ObjectInputStream(fis);

        TurmaMap novaTurma = (TurmaMap) ois.readObject();
        ois.close();
        return novaTurma;
    }


}
