package xyz.twinone;

import aima.search.framework.Problem;
import aima.search.framework.Search;
import aima.search.framework.SearchAgent;
import aima.search.informed.HillClimbingSearch;

import java.util.*;

public class Main {

    public static final Map<Coords, Integer> TEST_SS = new HashMap<>();
    public static final List<Coords> TEST_CD = new ArrayList<>();

    static {
        TEST_SS.put(new Coords(0,1), 2);
        TEST_SS.put(new Coords(1,0), 5);


        TEST_CD.add(new Coords(1, 2));
    }


    public static void main(String[] args) throws Exception {
        long start = System.currentTimeMillis();


        //State s = State.genRandom(100, 100, (int) System.currentTimeMillis());
        State s = new State(Util.genSensores(TEST_SS), Util.genCentrosDatos(TEST_CD));
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
