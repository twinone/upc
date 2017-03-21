package xyz.twinone;

public class Main {

    public static void main(String[] args) {
        long start = System.currentTimeMillis();

        State s = new State(100, 100, (int) System.currentTimeMillis());
        s.generateInitialSolution();


        long time = System.currentTimeMillis() - start;
        System.out.println("Execution took " +time / 1000 + "s" + time%1000 + "ms");
    }

}
