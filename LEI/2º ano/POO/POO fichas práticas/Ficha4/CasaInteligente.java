import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Set;
import java.util.HashSet;

public class CasaInteligente {
    private ArrayList<Lampada> lampadas; // agregação

    public CasaInteligente(){
        this.lampadas = new ArrayList<Lampada>();
    }
    public CasaInteligente(ArrayList<Lampada> lampadasArgumento){
        this.lampadas = new ArrayList<Lampada>(); 
        for(Lampada l : lampadasArgumento){
            lampadas.add(l);
        }
    }

    public CasaInteligente(CasaInteligente casa){
        this.lampadas = new ArrayList<Lampada>(); 
        for(Lampada l : casa.lampadas){
            this.lampadas.add(l); // ????
        }
    }

    public ArrayList<Lampada> getLampadas(){
        ArrayList<Lampada> copia = new ArrayList<Lampada>();
        for(Lampada l : this.lampadas){
            copia.add(l);
        }
        return copia;
    }

    public void addLampada(Lampada l){
        this.lampadas.add(l);
    }

    public void ligaLampadaNormal(int index){
        this.lampadas.get(index).lampON();
    }
    public void ligaLampadaEco(int index){
        this.lampadas.get(index).lampECO();
    }

    public int qtEmEco(){
        int count = 0;
        for(Lampada l : this.lampadas){
            if(l.getModo() == Lampada.Modo.ECO){
                count++;
            }
        }
        return count;
    }

    public void removeLampada(int index){
        this.lampadas.remove(index);
    }

    public void ligaTodasEco(){
        /*
        for(Lampada l : this.lampadas){
            l.lampECO();
        }
        */
        this.lampadas.forEach(l -> l.lampECO());
    }
    public void ligaTodasMax(){
        /*
        for(Lampada l : this.lampadas){
            l.lampON();
        }
        */
        this.lampadas.forEach(l -> l.lampON());
    }

    public double consumoTotal(){
        /*
        double consumoTotalCasa =0;
        for(Lampada l : this.lampadas){
            consumoTotalCasa += l.getConsumoTotal();
        }
        return consumoTotalCasa;
        */
        return this.lampadas.stream().mapToDouble(Lampada::getConsumoTotal).sum();
        // (double) ??
    }

    public Lampada maisGastadora(){
        /*
        Lampada maisGastadora = new Lampada();
        double maxGasto=0;
        for(Lampada l : this.lampadas){
            if(l.getConsumoTotal()>=maxGasto){
                maxGasto = l.getConsumoTotal();
                maisGastadora = l;
            }
        }
        return maisGastadora;
        */
        Comparator<Lampada> comp = (l1,l2) -> Double.compare(l2.getConsumoTotal(),l1.getConsumoTotal());
        return this.lampadas.stream()
            .sorter(comp)
            .findFirst() // stream acaba aqui
            .get()
            .clone();

    }

    public Set<Lampada> lampadasEmModoEco(){
        /*
        Set<Lampada> lampadasEco = new HashSet<Lampada>();
        for(Lampada l : this.lampadas){
            if(l.getModo() == Lampada.Modo.ECO){
                lampadasEco.add(l);
            }
        }
        return lampadasEco;
        */
        return this.lampadas.stream()
            .filter(l -> l.getModo() == Lampada.Modo.ECO)
            .map(Lampada::clone)
            .collect(Collectors.toSet()); //????
    }
    public void reset(){
        /*
        for(Lampada l : this.lampadas){
            l.setConsumoPeriodo(0);
        }
        */
        this.lampadas.forEach(l -> l.setConsumoPeriodo(0));
    }
    public Set<Lampada> podiumEconomia(){
        return this.lampadas.stream()
            .sorted((l1,l2) -> Double.compare(l1.periodoConsumo(),l2.periodoConsumo()))
            .limit(3)
            .map(Lampada::clone)
            .collect(Collectors.toSet());
    }
    

    public String toString(){
        return "\nCasaInteligente:" +
                "\nlampadas: " + lampadas.toString();
    }

}
