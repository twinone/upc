package xyz.twinone;

import aima.search.framework.Problem;
import aima.search.framework.Search;
import aima.search.framework.SearchAgent;
import aima.search.informed.HillClimbingSearch;

import java.util.*;

public class Main {


    public static void main(String[] args) throws Exception {


        //State orig = State.genRandom(100, 4, (int) System.currentTimeMillis());

        // DONT REMOVE, we are working on this seed:
        //State orig = State.genRandom(300, 6, 30002947);


        // EXTRA POINT EXPERIMENT 8
        State orig = State.genRandom(100, 4, 1234);

        //State orig = Test.getCurrent();

       /*
        State o = Test.getCurrent();
        o.generateInitialSolution(1);

        o.debugState();

        o.removeEdge(o.getSensors().get(2));
        System.out.println("---------------");

        o.debugState();
*/

        //if (true) return;
        for (int i = 0; i < 1; i++) {
            State s = new State(orig);
            s.setInitial();
            s.generateInitialSolution(1);


            //s.debugState();
            //if (true)return;
            long start = System.currentTimeMillis();

            Problem p = new Problem(s, s, s, s);
            Search search = new HillClimbingSearch();

            SearchAgent ag = new SearchAgent(p, search);
            printActions(ag.getActions());

            List<State> l = search.getPathStates();
            l.get(l.size() - 1).getHeuristic();
            l.get(l.size() - 1).getHeuristic();

            l.get(l.size() - 1).debugState();



            long time = System.currentTimeMillis() - start;
            System.out.println("State " + i + ": Execution took " + time / 1000 + "s" + time % 1000 + "ms");

        }
    }


    private static void printActions(List actions) {
        for (int i = 0; i < actions.size(); i++) {
            String action = (String) actions.get(i);
            System.out.println(action);
        }
    }

    private static void printInstrumentation(Properties properties) {
        Iterator keys = properties.keySet().iterator();
        while (keys.hasNext()) {
            String key = (String) keys.next();
            String property = properties.getProperty(key);
            System.out.println(key + " : " + property);
        }

    }

}
