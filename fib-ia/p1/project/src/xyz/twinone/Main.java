package xyz.twinone;

import aima.search.framework.Problem;
import aima.search.framework.Search;
import aima.search.framework.SearchAgent;
import aima.search.informed.HillClimbingSearch;
import aima.search.informed.SimulatedAnnealingSearch;

import java.util.*;

public class Main {


    private static final boolean SIMULATED_ANNEALING = true;
    private static final int INITIAL_SOLUTION = 1;
    private static final int NUM_TESTS = 10;
    private static final boolean INCREMENT_VALUES = true;


    static long totalCost = 0;
    static long totalFlow = 0;
    static long totalIterations = 0;
    static long totalMillis;

    public static void main(String[] args) throws Exception {
        Random r = new Random();

        for (int i = 0; i < NUM_TESTS; i++) {
            //System.out.println("----------------");
            runExperiment(i, r.nextInt(), i == NUM_TESTS-1);
        }
        //System.out.println("----------------");

        totalCost /= NUM_TESTS;
        totalFlow /= NUM_TESTS;
        totalIterations /= NUM_TESTS;
        totalMillis /= NUM_TESTS;

        System.out.println("Averages: t="+totalMillis + ", iter="+totalIterations + ", cost="+totalCost + ", flow="+totalFlow);
    }

    public static void runExperiment(int num, int seed, boolean draw) throws Exception {
        int xx;
        int y;
        if (INCREMENT_VALUES) {
            xx = 100+50*num;
            y = 4 + num*2;
        }
        else {
            xx = 100;
            y = 4;
        }
        //State orig = State.genRandom(100, 4, (int) System.currentTimeMillis());
        State orig = State.genRandom(xx,y, seed);


        State s = new State(orig);
        s.setInitial();
        s.generateInitialSolution(INITIAL_SOLUTION);

        long start = System.currentTimeMillis();

        Problem p = new Problem(s, s, s, s);
        Search search;
        if (SIMULATED_ANNEALING) {
            int steps = 10000 * 100; int stiter = 100; int k = 20; double lambda = 0.005D;
            search = new SimulatedAnnealingSearch(steps, stiter, k, lambda);
            s.setSearchMode(State.SearchMode.SIMULATED_ANNEALING);
        } else {
            search = new HillClimbingSearch();
            s.setSearchMode(State.SearchMode.HILL_CLIMBING);
        }
        SearchAgent ag = new SearchAgent(p, search);
        //printActions(ag.getActions());




        long dt = System.currentTimeMillis() - start;
        long time = dt;
        System.out.print("Simulation #"+num + " ("+xx + " sensors,"+y+" centers): ");
        System.out.print(" t=" + time + "ms, ");
        List<State> l = search.getPathStates();
        System.out.print("iter=" + l.size() + ", ");
        State x = s;
        if (l.size() >= 1) {
            x = l.get(l.size() - 1);
        }

        x.getHeuristic();
        x.debugState();
        if (draw)  x.drawState();
        totalIterations += l.size();
        totalMillis += dt;
        totalFlow += x.totalFlow;
        totalCost += x.totalCost;
    }

}
