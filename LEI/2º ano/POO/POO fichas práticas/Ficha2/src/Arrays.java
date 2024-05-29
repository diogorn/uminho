
public class Arrays {
    public int minArray(int[] a){
        int min=a[0];
        for(int elem: a){
            if(min>elem) min=elem;
        }
        return min;
    }

    public int[] indiceArrays(int a, int b){
        //nao funciona para b<a
        int [] array = new int[b-a-1];
        for(int i=0; a<b-1; i++){
            a++;
            array[i]=a;
        }
        return array;
    }

    public int[] arrayCompare(int[] a, int[] b){
        int[] array= new int[Math.max(a.length, b.length)];
        int i=0;
        for(int as:a){
            for(int bs:b){
                if (as==bs){
                    array[i] = as;
                    i++;
                }
            }
        }
        int[] arrayCopy=new int[i];
        for(int j=0; j<i;j++ ){
            arrayCopy[j]=array[j];
        }
        return arrayCopy;
    }


}
