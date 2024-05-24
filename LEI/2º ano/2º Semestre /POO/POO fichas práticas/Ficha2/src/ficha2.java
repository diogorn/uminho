import java.util.Scanner;

public class ficha2 {
    public static void main(String[] args) {

        Arrays arr = new Arrays();
        Scanner sc = new Scanner(System.in);
        System.out.print("Exercicio: ");
        int n = sc.nextInt();
        switch (n){
            case 1:
                System.out.print("alinea: ");
                n = sc.nextInt();
                switch (n){
                    case 1:
                        System.out.print("Número de inteiros a ler?: ");
                        n = sc.nextInt();

                        int[] valores = new int[n];
                        for(int i = 0; i < n; i++) {
                            int valor = sc.nextInt();
                            valores[i] = valor;
                        }
                        System.out.print("minimo: "+arr.minArray(valores));
                    case 2:
                        System.out.print("Indice 1: ");
                        int a = sc.nextInt();
                        System.out.print("Indice 2: ");
                        int b = sc.nextInt();
                        System.out.print("Array: ");
                        for (int num : arr.indiceArrays(a,b)) {
                            System.out.print(num + " ");
                        }
                    case 3:
                        System.out.print("Número de inteiros a ler?: ");
                        n = sc.nextInt();
                        int[] array1 = new int[n];
                        for(int i = 0; i < n; i++) {
                            int valor = sc.nextInt();
                            array1[i] = valor;
                        }
                        System.out.print("Número de inteiros a ler?: ");
                        n = sc.nextInt();
                        int[] array2 = new int[n];
                        for(int i = 0; i < n; i++) {
                            int valor = sc.nextInt();
                            array2[i] = valor;
                        }
                        int[]array = arr.arrayCompare(array1,array2);
                        System.out.print("Array: ");
                        for(int elem: array) System.out.print(elem+" ");

                }
        }

    }
}
