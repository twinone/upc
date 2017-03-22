package xyz.twinone;

import aima.search.framework.Problem;
import aima.search.framework.Search;
import aima.search.framework.SearchAgent;
import aima.search.informed.HillClimbingSearch;
import sun.management.Sensor;

import java.util.*;

public class Main {



    public static void main(String[] args) throws Exception {
        long start = System.currentTimeMillis();



        //State s = State.genRandom(100, 100, (int) System.currentTimeMillis());
        State s = Test.getCurrent();
        s.generateInitialSolution();

        Problem p = new Problem(s, s, s, s);
        Search search = new HillClimbingSearch();

        SearchAgent ag = new SearchAgent(p, search);
        printActions(ag.getActions());
        printInstrumentation(ag.getInstrumentation());


        long time = System.currentTimeMillis() - start;
        System.out.println("Execution took " + time / 1000 + "s" + time % 1000 + "ms");
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
