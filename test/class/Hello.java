public class Hello {

//     private static long x = 16000001;
//     private static Object f = new Object();
//     private static String a = "aaa";
//     private static String b = "aaa";
//     private long aa = 1;
// 	public static void main(String[] args) {
// 	    long x = 181902333;
// 	    System.out.println(a == b);
// 		String str = new String("abc");
//         int sum = 0;
// 		for (int i = 1; i <= 100; i++) {
//             sum += i;
//         }
// 	}

// 	public static void main(String[] args) {
// 	    int sum = 0;
// 		for (int i = 0; i < 2; i++) {
//             sum += i;
//         }
//         System.out.println(sum);
// 	}

//     public static void main(String[] args) {
// 	    System.out.println(new Object().getClass() == new Object().getClass());
// 	}


    public static void test1() {
        Object c = null;
        c.getClass();
        System.out.println(1 / 0);
    }

    public static void test() {
        System.out.println("test0");
        test1();
    }

    public static void main(String[] args) {
        int a = 0;
        int b = 2;
        Object object = new Object();
        System.out.println(object.getClass());
        for (int i = 0; i < 100; i++) {
            test();
            System.out.println("Hello:");
            System.out.println(a + b + i);
            b = a;
            a = i;
//             System.out.println("Hello" + i);
//             System.out.println("Hello World");
        }

//         int a = 100;
//         int b = 300;
//         System.out.println(a + b);
//         System.out.println("Hello World!");
	}
}
