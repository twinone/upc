package xyz.twinone;

public class Main {

    public static void main(String[] args) {

        State s = new State(100, 100, (int) System.currentTimeMillis());
        s.generateInitialSolution();

    }

}
