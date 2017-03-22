package xyz.twinone;

import aima.search.framework.Problem;
import aima.search.framework.Search;
import aima.search.framework.SearchAgent;
import aima.search.informed.HillClimbingSearch;
import sun.management.Sensor;

import java.util.*;

public class Main {


    public static void main(String[] args) throws Exception {



        State orig = State.genRandom(100, 8, (int) System.currentTimeMillis());
        //State s = Test.getCurrent();



        for (int i = 0; i < 2; i++) {
            State s = new State(orig);
            s.setInitial();
            s.generateInitialSolution(i);

            long start = System.currentTimeMillis();

            Problem p = new Problem(s, s, s, s);
            Search search = new HillClimbingSearch();

            SearchAgent ag = new SearchAgent(p, search);
            //printActions(ag.getActions());
            System.out.println("Last action: " + ag.getActions().get(ag.getActions().size()-1));
            //printInstrumentation(ag.getInstrumentation());


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
