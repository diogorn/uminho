import java.util.ArrayList;
import java.util.Iterator;


public class Stack {
    private ArrayList<String> elementos;

    public Stack() {
        this.elementos = new ArrayList<String>();
    }
    public Stack(Stack stackArgumento){
        ArrayList<String> copia = new ArrayList<String>();
        for(String elem : this.elementos){
            copia.add(elem); //nao usamos clone pois String é imutavel  
        }
    }

    public String top(){
        String top=null;
        Iterator<String> it = this.elementos.iterator();
        while(it.hasNext()){
            top = it.next();
        }
        return top;
    }
    public void push(String s){
        this.elementos.add(s);
    }
    public void pop(){
        this.elementos.remove(elementos.size()-1);
    }

    public boolean empty(){
        return this.elementos.isEmpty();
    }
    public int length(){
        return this.elementos.size();
    }

}
