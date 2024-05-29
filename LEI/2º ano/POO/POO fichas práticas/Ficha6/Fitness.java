import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.stream.Collector
;
import java.util.stream.Collectors;
import java.util.HashMap;
import java.util.Set;

public class Fitness implements Serializable{
    private String nomeGinasio;
    private Map<String, Utilizador> utilizadoresMap;

    public Fitness(){
        this.nomeGinasio = "";
        this.utilizadoresMap = new HashMap<>();
    }

    public Fitness(String nomeGinasio, Map<String, Utilizador> utilizadoresMap) {
        this.nomeGinasio = nomeGinasio;
        this.utilizadoresMap = utilizadoresMap.entrySet().stream().collect(Collectors.toMap(k->k.getKey(), v->v.getValue().clone()));
    }

    // a
    public boolean existeUtilizador(String email){
        return this.utilizadoresMap.containsKey(email);
        
    }
    // b
    public int quantos(){
        return this.utilizadoresMap.size();
    }
    // c
// string fornecida corresponde ao nome da dlasse
    public int quantos(String atividade, String email) throws UtilizadorNaoExisteException{
        if(this.utilizadoresMap.containsKey(email)){
            return (int) this.utilizadoresMap.get(email).getAtividades().values().stream().
                                              filter(a -> a.getClass().getSimpleName().equals(atividade)).
                                              count();
        }
        else{
            //throw new UtilizadorNaoExisteException(email);
        }
        return 0;
    }
    // d
    public Utilizador getUtilizador(String email){
        return this.utilizadoresMap.get(email).clone(); // composição
    }
    // e
    public void adiciona(String email, Atividade act){
       Utilizador u = getUtilizador(email);
       u.addAtividade(act);        
    }
    // g
    public void adiciona(String email, Set<Atividade> activs){
        Utilizador u = getUtilizador(email);
        for(Atividade a : activs){
            u.addAtividade(a);
        }
    }

    // h
    public int tempoTotalUtilizador(String email){
        return getUtilizador(email).getAtividades().values().stream().mapToInt(Atividade::getDuracao).sum();
    }
    // f
    public List<Atividade> getAllAtividades(){
        List<Atividade> todas = new ArrayList<>();
        for(Utilizador u : this.utilizadoresMap.values()){
            Map<String,Atividade> la = u.getAtividades();
            for(Atividade a: la.values()){
                todas.add(a.clone());
            }
        }
        return todas;
    } 
    
    // i
    public Atividade AtividadeMaisExigente(){
        Comparator<Atividade> atividadeMaisCalorias =(a1,a2) -> (int) (a1.calorias()-a2.calorias()); // crescente
        return getAllAtividades().stream().sorted(atividadeMaisCalorias).findFirst().orElse(null);

    }


    // j
    // Obter o utilizador com maior dispêndio de calorias
    public Utilizador utilizadorMaisActivo() {
        Comparator<Utilizador> maisAtivo = Comparator.comparingDouble(u -> u.getAtividades().values().stream().mapToDouble(Atividade::calorias).sum());
        return this.utilizadoresMap.values().stream().max(maisAtivo).orElse(null);
    }

    // 
    public void actualizaDesportoFav(){
        for(Utilizador u : this.utilizadoresMap.values()){
            String desportoFAV = u.getAtividades().values().stream().collect(Collectors.groupingBy(Atividade::getDescricao, Collectors.counting()))
            .entrySet().stream()
            .max(Map.Entry.comparingByValue())
            .map(Map.Entry::getKey)
            .orElse("");
            u.setDesporto_favorito(desportoFAV);
        }

    }
     // fase 2 
    // a
    public Utilizador utilizadorComMaisRegistos()throws UtilizadorNaoExisteException {
        Comparator <Utilizador> maisRegistos = (u1,u2) -> {if((u1.getAtividades().size() - u2.getAtividades().size()) == 0 )
        return u2.getData_nascimento().compareTo(u1.getData_nascimento());
        else return u1.getAtividades().size() - u2.getAtividades().size();};
        
        return this.utilizadoresMap.values().stream().map(Utilizador::clone).sorted(maisRegistos).findFirst().orElse(null);
    }

    private static Map<String, Comparator<Atividade>> comparadores = new HashMap<>();
    public static void addComparator(String nome, Comparator<Atividade> c){
        comparadores.put(nome,c);
    }

    // fase 3
    // escrever csv
    public void escreverCSVAtividades(String email, String Ficheiro)throws IOException, UtilizadorNaoExisteException{
        if (!this.utilizadoresMap.containsKey(email)) {
            throw new UtilizadorNaoExisteException(email);
        }else {
            PrintWriter pw = new PrintWriter(Ficheiro);
            Utilizador u = this.utilizadoresMap.get(email);
            for(Atividade a : u.getAtividades().values()){
                pw.println(a.toString());
                pw.println(";");
            }
            pw.flush();
            pw.close();
        }
    }
    public void guardaEstado(String nomeFicheiro) throws FileNotFoundException, IOException{
        FileOutputStream fos = new FileOutputStream(nomeFicheiro);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this);
        oos.flush();
        oos.close();
    }


 
    
    
    
}
