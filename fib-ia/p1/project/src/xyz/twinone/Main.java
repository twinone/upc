package xyz.twinone;

import aima.search.framework.Problem;
import aima.search.framework.Search;
import aima.search.framework.SearchAgent;
import aima.search.informed.HillClimbingSearch;
import aima.search.informed.SimulatedAnnealingSearch;

import java.util.*;

public class Main {


    private static final boolean SIMULATED_ANNEALING = false;

    public static void main(String[] args) throws Exception {


        State orig = State.genRandom(100, 4, (int) System.currentTimeMillis());


        State s = new State(orig);
        s.setInitial();
        s.generateInitialSolution(1);

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

        List<State> l = search.getPathStates();
        System.out.println("Iterations: " + l.size());
        if (l.size() >= 1) {
            l.get(l.size() - 1).getHeuristic();
            l.get(l.size() - 1).debugState();
        }


        long time = System.currentTimeMillis() - start;
        System.out.println("Execution took " + time / 1000 + "s" + time % 1000 + "ms");
    }

}
