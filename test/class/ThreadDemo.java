public class ThreadDemo {

    public static void test1() {
        Object c = null;
        c.getClass();
    }

    public static void test() {
        System.out.println("test");
        test1();
    }

    public static void main(String[] args) throws InterruptedException {
    System.out.println("Hello");
            Thread t1 = new Thread(new Runnable() {
                            @Override
                            public void run() {
                                System.out.println(111);
                            }
                        });
                        Thread t2 = new Thread(new Runnable() {
                            @Override
                            public void run() {
                                System.out.println(222);
                            }
                        });
                        Thread t3 = new Thread(new Runnable() {
                            @Override
                            public void run() {
                                test1();
                            }
                        });
                        t1.start();
                        t2.start();
                        t3.start();
                        t1.join();
                        t2.join();
                        t3.join();
        }
}
