public class TestaSensor {
    public static void main(String[] args) {
        Sensor s1 = new Sensor();
        Sensor s2 = new Sensor(10);
        Sensor s3 = new Sensor(s2);
        System.out.println("Pressao sensor 1 " + s1.getPressao());
        System.out.println("Pressao sensor 2 " + s2.getPressao());
        System.out.println("Pressao sensor 3 " + s3.getPressao());
        System.out.println(s1.setPressao(5));
        System.out.println(s2.setPressao(-50));
        System.out.println(s3.setPressao(15));
        System.out.println("Pressao sensor 1 " + s1.getPressao());
        System.out.println("Pressao sensor 2 " + s2.getPressao());
        System.out.println("Pressao sensor 3 " + s3.getPressao());
    }
}
