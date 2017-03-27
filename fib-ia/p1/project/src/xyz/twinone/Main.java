package xyz.twinone;

import aima.search.framework.Problem;
import aima.search.framework.Search;
import aima.search.framework.SearchAgent;
import aima.search.informed.HillClimbingSearch;
import aima.search.informed.SimulatedAnnealingSearch;

import java.util.*;

public class Main {


    private static final boolean SIMULATED_ANNEALING = false;
    private static final int INITIAL_SOLUTION = 0;


    static double totalCost = 0.0;
    static double totalFlow = 0.0;
    static double totalIterations = 0;
    static double totalMillis;

    public static void main(String[] args) throws Exception {
        Random r = new Random();

        int numTests = 15;
        for (int i = 0; i < numTests; i++) {
            //System.out.println("----------------");
            runExperiment(i, r.nextInt(), i == numTests-1);
        }
        //System.out.println("----------------");

        totalCost /= numTests;
        totalFlow /= numTests;
        totalIterations /= numTests;
        totalMillis /= numTests;

        System.out.println("Averages: t="+totalMillis + ", iter="+totalIterations + ", cost="+totalCost + ", flow="+totalFlow);
    }

    public static void runExperiment(int num, int seed, boolean draw) throws Exception {


        //State orig = State.genRandom(100, 4, (int) System.currentTimeMillis());
        State orig = State.genRandom(100, 4, seed);


        State s = new State(orig);
        s.setInitial();
        s.generateInitialSolution(INITIAL_SOLUTION);

        long start = System.currentTimeMillis();

        Problem p = new Problem(s, s, s, s);
        Search search;
        if (SIMULATED_ANNEALING) {
            search = new SimulatedAnnealingSearch();
            s.setSearchMode(State.SearchMode.SIMULATED_ANNEALING);
        } else {
            search = new HillClimbingSearch();
            s.setSearchMode(State.SearchMode.HILL_CLIMBING);
        }
        SearchAgent ag = new SearchAgent(p, search);
        //printActions(ag.getActions());




        long dt = System.currentTimeMillis() - start;
        long time = dt;
        System.out.print("Simulation #"+num + ": ");
        System.out.print(" t=" + time + "ms, ");
        List<State> l = search.getPathStates();
        System.out.print("iter=" + l.size() + ", ");
        if (l.size() >= 1) {
            State x = l.get(l.size() - 1);
            x.getHeuristic();
            x.debugState();
            if (draw)  x.drawState();

            totalIterations += l.size();
            totalMillis += dt;
            totalFlow += x.totalFlow;
            totalCost += x.totalCost;
        } else {
            throw new IllegalStateException("Execution " +num +  "has no actions");
        }
    }

}
