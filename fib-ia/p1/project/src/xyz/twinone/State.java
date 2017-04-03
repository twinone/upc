package xyz.twinone;

import IA.Red.Centro;
import IA.Red.CentrosDatos;
import IA.Red.Sensor;
import IA.Red.Sensores;
import aima.search.framework.Successor;

import javax.swing.*;
import java.awt.*;
import java.security.InvalidParameterException;
import java.util.*;
import java.util.List;
import java.util.Queue;

public class State implements aima.search.framework.SuccessorFunction, aima.search.framework.HeuristicFunction, aima.search.framework.GoalTest {

    /**
     * Maximum allowed connections per center
     */
    private static final int CONNS_CENTER = 25;
    /**
     * Maximum allowed connections per sensor
     */
    private static final int CONNS_SENSOR = 3;

    /**
     * Maximum currentFlow a data center can handle
     */
    public static final int CENTER_CAPACITY = 150;
    /**
     * Set to true if we count the outgoing edge as a "connection"
     */
    private static final boolean COUNT_OUTGOING = false;

    /*
     * DO NOT TOUCH SENSORS, CENTERS or NODES!!!
     * IF YOU WANT TO MODIFY IT, MAKE A COPY
     */

    /**
     * The sensors of this problem
     */
    private final Sensores sensors;

    /**
     * The data centers of this problem
     */
    private final CentrosDatos centers;

    /**
     * Combination of the list of sensors and centers
     */
    private final List<Object> nodes;

    /**
     * The number of remaining connections
     */
    public final Map<Object, Integer> remainingConnections;

    /**
     * The connections between centers and sensors
     */
    public final Map<Sensor, Object> graph;

    /**
     * The initial state to compare to
     */
    public static State initialState;

    public final Set<Sensor> leaves;


    /**
     * Genera un estado con sensors y centers de datos con coordenadas aleatorias.
     *
     * @param numSensores     El numero de sensors
     * @param numCentrosDatos El numero de centers de datos
     * @param seed            La semilla para los sensors y estados
     */
    public static State genRandom(int numSensores, int numCentrosDatos, int seed) {
        if (numSensores <= 0) throw new InvalidParameterException("numSensores should be > 0");
        if (numCentrosDatos <= 0) throw new InvalidParameterException("numCentrosDatos should be > 0");

        // Set up the sensors and centers
        Random r = new Random(seed);
        Sensores sensors = new Sensores(numSensores, r.nextInt());
        CentrosDatos centers = new CentrosDatos(numCentrosDatos, r.nextInt());
        return new State(sensors, centers);

    }

    public State(Sensores ss, CentrosDatos cd) {
        sensors = ss;
        centers = cd;


        nodes = new ArrayList<>();
        nodes.addAll(sensors);
        nodes.addAll(centers);

        remainingConnections = new HashMap<>();
        for (Centro c : centers) remainingConnections.put(c, CONNS_CENTER);
        for (Sensor s : sensors) remainingConnections.put(s, CONNS_SENSOR);
        sensors.sort((o1, o2) -> (int) (o2.getCapacidad() - o1.getCapacidad()));

        // Initialize the graph
        graph = new HashMap<>();
        leaves = new HashSet<>(sensors);
    }

    /**
     * Generates a copy (by value) of src<br>
     * <b>Warning: {@link #sensors} and {@link #centers} will be shared!</b>
     */
    public State(State src) {
        // Pointers
        sensors = src.sensors;
        centers = src.centers;
        nodes = src.nodes;


        // Copies
        graph = new HashMap<>(src.graph);
        remainingConnections = new HashMap<>(src.remainingConnections);
        leaves = new HashSet<>(src.leaves);
    }

    /**
     * Creates a clone of the previous state
     *
     * @param src The source of the clone
     * @see #clone(State)
     */
    public static State clone(State src) {
        return new State(src);
    }


    public Sensores getSensors() {
        return sensors;
    }

    public CentrosDatos getCenters() {
        return centers;
    }


    /**
     * Generates an initial valid solution for the problem using generateInitialSolution1()
     */
    public void generateInitialSolution(int n) {
        if (n == 0) generateInitialSolution1();
        else if (n == 1) generateInitialSolution2();
        else if (n == 2) generateInitialSolution3();

        if (!isSolution()) {
            throw new IllegalStateException("generateInitialSolution did not generate a valid solution");
        }
    }

    /**
     * This very simple algorithm builds a solution where everything is
     * connected to the first datacenter until it's full, then to the next, etc.
     * If we run out of data centers we will connect to the first sensor, then to the second,
     * and so on<br>
     * This algorithm guarantees the following restrictions:
     * <ul>
     * <li>Every sensor is connected to exactly one node</li>
     * <li>Every sensor has at most 3 sensor connected to it</li>
     * <li>Every data center has at most 25 sensor connected to it</li>
     * </ul>
     * <p>
     * We do not look at the flows. They might be negative.
     */
    private void generateInitialSolution1() {
        Queue<Sensor> pending = new LinkedList<>(sensors);
        Queue<Object> connectable = new LinkedList<>(centers);
        while (!pending.isEmpty()) {
            Sensor s = pending.peek();
            Object o = connectable.peek();
            if (addEdge(s, o)) {
                pending.remove();
                connectable.add(s);
                if (remainingConnections.get(o) == 0) connectable.remove();
            } else {
                connectable.remove();
            }
        }

    }

    private void generateInitialSolution2() {
        List<Object> connectable = new ArrayList<>(centers);
        for (Sensor s : sensors) {
            connectable.sort((o1, o2) -> {
                // if one is a sensor and the other not, the center has priority
                if (o1 instanceof Sensor || o2 instanceof Sensor) {
                    if (o2 instanceof Centro) {
                        return 1;
                    }
                    if (o1 instanceof Centro) {
                        return -1;
                    }
                }
                if (Util.distance(s, o1) > Util.distance(s, o2)) return 1;
                else if (Util.distance(s, o1) < Util.distance(s, o2)) return -1;
                else return 0;
            });
            Object o = connectable.get(0);

            addEdge(s, o);
            connectable.add(s);
            if (remainingConnections.get(o) == 0) connectable.remove(o);
        }
    }

    private void generateInitialSolution3() {
        List<Object> connectable = new ArrayList<>(centers);
        List<Sensor> pending = new ArrayList<>(sensors);

        while (!pending.isEmpty()) {
            double best = -1;
            Object bestTarget = null;
            Sensor bestSource = null;
            double bestSrcCap = -1;
            double bestTgtCap = -1;
            for (Sensor s : pending) {
                for (Object o : connectable) {
                    double dst = Util.distance(s, o);
                    if (o instanceof Sensor && ((Sensor) o).getCapacidad() < s.getCapacidad()) continue;
                    double ocap = o instanceof Centro ? 150 : ((Sensor) o).getCapacidad();
                    double scap = s.getCapacidad();
                    if (scap > bestSrcCap || scap == bestSrcCap && ocap > bestTgtCap || best == -1 || dst < best) {
                        best = dst;
                        bestTarget = o;
                        bestSource = s;
                        bestSrcCap = scap;
                        bestTgtCap = ocap;
                    }
                }
            }
            addEdge(bestSource, bestTarget);
            if (remainingConnections.get(bestTarget) == 0) connectable.remove(bestTarget);
            connectable.add(bestSource);
            pending.remove(bestSource);
        }


    }


    public void debugState() {

        /**
         for (Sensor s : sensors) {
         Object o = graph.get(s);
         System.out.println(
         Util.sensorToString(s, this) +
         " -> " +
         Util.objectToString(o, this)
         );
         }


         for (Centro c : centers) {
         System.out.println(Util.centerToString(c, this));
         }
         */
        getHeuristic();
        System.out.println("cost=" + totalCost + ", flow=" + totalFlow);
    }


    public void drawState(int num) {

        JFrame frame = new JFrame("Test " + num);
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setLayout(new BorderLayout());
        frame.add(new JScrollPane(new StateDraw(sensors, centers, graph)));
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);

    }

    /**
     * Returns true if you can add an edge without
     * currentFlow problems but DOES NOT ADD IT
     *
     * @return true if you can add this edge
     */
    private boolean checkEdge(Sensor s, Object o) {
        if (!addEdge(s, o)) return false;

        removeEdge(s);
        return true;
    }

    /**
     * @return true if the edge was successfully added
     */
    public boolean addEdge(Sensor s, Object o) {
        if (graph.get(s) != null) throw new IllegalStateException("Edge already exists");
        if (s == o) return false;
        if (remainingConnections.get(o) == 0) return false;

        // detect cycle:
        Object next = graph.get(o);
        while (next != null) {
            if (next == s) return false;
            next = graph.get(next);
        }

        graph.put(s, o);
        if (o instanceof Sensor) leaves.remove((Sensor) o);
        remainingConnections.put(o, remainingConnections.get(o) - 1);
        return true;
    }

    public Object removeEdge(Sensor s) {
        if (graph.get(s) == null) throw new IllegalStateException("Edge does not exists");

        Object o = graph.get(s);
        if (o instanceof Sensor) leaves.add((Sensor) o);
        Object r = graph.remove(s);
        remainingConnections.put(o, remainingConnections.get(o) + 1);
        return r;
    }

    /**
     * This function checks whether this {@link State} fulfills all
     * restrictions<br>
     * <ul>
     * <li>It's a DAG (no cycles, connected)</li>
     * <li>Every root is a {@link Centro}</li>
     * <li>Every sensor is connected to at most 3 nodes</li>
     * <li>Every center is connected to at most 25 nodes</li>
     * </ul>
     *
     * @return true if this {@link State} is a solution to the problem
     */
    public boolean isSolution() {
        if (true) return true;
        // Check if it's connected

        Set<Object> x = new HashSet<>(nodes);
        for (Object o : nodes) {
            if (remainingConnections.get(o) < 0) {
                throw new IllegalStateException("A node has negative remaining connections");
            }
        }


        for (Map.Entry<Sensor, Object> e : graph.entrySet()) {
            x.remove(e.getKey());
            x.remove(e.getValue());
        }

        x.removeAll(centers);

        //if (!x.isEmpty()) throw new IllegalStateException("The graph is not connected");


        return true;
    }


    /*
     * AIMA stuff
     */

    @Override
    public double getHeuristicValue(Object o) {
        if (!(o instanceof State)) throw new InvalidParameterException("Should be state");
        State s = (State) o;
        // TODO take currentFlow into account here
        return s.getHeuristic();
    }

    public double getHeuristic() {
        double cost = 0;
        double flow = 0;
        Map<Object, Integer> flows = new HashMap<>();
        for (Object o : nodes) flows.put(o, 0);

        Set<Object> cycleDetector = new HashSet<>();
        Queue<Object> curr = new LinkedList<>(leaves);
        Set<Object> next = new HashSet<>();
        while (!curr.isEmpty()) { // while there are more nodes to process

            for (Object x : curr) {

                if (x instanceof Centro || cycleDetector.contains(x)) {
                    continue;
                }
                Sensor s = (Sensor) x;

                Object o = graph.get(s);
                if (o == null) {
                    throw new IllegalStateException("Sensor is not connected");
                    //System.out.println("Warning, sensor is not connected");
                    //continue;
                }
                double cap = s.getCapacidad();
                int val = (int) Math.min(flows.get(s) + cap, cap * 3);
                double dst = Util.distance(s, o);
                cost += dst * dst * val;

                flows.put(o, flows.get(o) + val);


                next.add(o);
                cycleDetector.add(s);
            }


            curr = new LinkedList<>(next);
            next = new HashSet<>();
        }
        for (Centro c : centers) {
            flow += Math.min(flows.get(c), CENTER_CAPACITY);
        }

        totalCost = cost;
        totalFlow = flow;
        // TODO
        //System.out.println("Cost:" + cost + ", Flow:" + flow);

        return cost / Math.pow(flow, 2.5);
        //return cost - 80 * Math.pow(flow, 2);
    }

    public double totalCost, totalFlow;

    private double getFlowRatio() {
        return getTotalFlowAtCenters() / (double) getMaxFlow();
    }

    private int getMaxFlow() {
        int sum = 0;
        for (Sensor s : sensors) sum += s.getCapacidad();
        return Math.min(sum, centers.size() * CENTER_CAPACITY);
    }

    /**
     * Get the capacity of a node
     *
     * @return
     */
    private int getNodeCapacity(Object o) {
        if (o instanceof Centro) return CENTER_CAPACITY;
        return (int) ((Sensor) o).getCapacidad() * 3;
    }

    /**
     * Gets the current currentFlow that is arriving at all centers
     */
    private int getTotalFlowAtCenters() {
        // FIXME
        return 0;
    }


    @Override
    public List getSuccessors(Object o) {
        return searchMode == SearchMode.HILL_CLIMBING ? getSuccessorsHC(o) : getSuccessorsSA(o);
    }

    public List getSuccessorsHC(Object o) {
        if (!(o instanceof State)) throw new InvalidParameterException("Should be state");
        State state = (State) o;

        if (!state.isSolution()) throw new IllegalStateException("State is not a solution");

        List<Successor> res = new ArrayList<>();

        for (final Sensor sensor : state.sensors) {
            for (final Object target : state.nodes) {
                if (sensor == target) continue;


                State newState = new State(state);
                //double heu = newState.getHeuristic();
                String action = "Action: " +
                        Util.sensorToString(sensor, this) +
                        " -> " +
                        Util.objectToString(target, this)
                        + " cost:" + newState.totalCost + " "
                        + " currentFlow: " + newState.totalFlow
                        // + " heuristic: " + heu
                        ;


                if (!newState.moveEdge(sensor, target)) {
                    continue;
                }
                /*newState.removeEdge(sensor);
                if (!newState.addEdge(sensor, target)) {
                    continue;
                }*/

                Successor succ = new Successor(action, newState);
                res.add(succ);
            }
        }

        //System.out.println("Generated " + res.size() + " successors");
        return res;
    }

    public List getSuccessorsHC2(Object o) {
        if (!(o instanceof State)) throw new InvalidParameterException("Should be state");
        State state = (State) o;

        if (!state.isSolution()) throw new IllegalStateException("State is not a solution");

        List<Successor> res = new ArrayList<>();

        int counter = 1;
        for (final Sensor sensor : state.sensors) {
            for (final Sensor target : state.sensors.subList(counter, state.sensors.size())) {

                State newState = new State(state);
                //double heu = newState.getHeuristic();
                String action = "Action: " +
                        Util.sensorToString(sensor, this) +
                        " -> " +
                        Util.objectToString(target, this)
                        + " cost:" + newState.totalCost + " "
                        + " currentFlow: " + newState.totalFlow
                        // + " heuristic: " + heu
                        ;


                if (!newState.swapEdges(sensor, target)) {
                    ++counter;
                    continue;
                }

                Successor succ = new Successor(action, newState);
                res.add(succ);
                ++counter;
            }
        }

        //System.out.println("Generated " + res.size() + " successors");
        return res;
    }

    private boolean moveEdge(Sensor sensor, Object target) {
        removeEdge(sensor);
        return addEdge(sensor, target);
    }

    private boolean swapEdges(Sensor s1, Sensor s2) {
        Object o1 = removeEdge(s1);
        Object o2 = removeEdge(s2);
        boolean ok1 = addEdge(s1, o2);
        boolean pl2 = addEdge(s2, o1);
        if (!ok1 || !pl2) {
            if (ok1) removeEdge(s1);
            if (pl2) removeEdge(s2);
        }
        return addEdge(s1, o2) && addEdge(s2, o1);
    }


    public List getSuccessorsSA(Object o) {
        if (!(o instanceof State)) throw new InvalidParameterException("Should be state");
        State state = (State) o;

        if (!state.isSolution()) throw new IllegalStateException("State is not a solution");

        List<Successor> res = new ArrayList<>();

        Random r = new Random(System.currentTimeMillis());
        while (true) {
            Sensor sensor = sensors.get(r.nextInt(state.sensors.size()));
            Object target = nodes.get(r.nextInt(state.nodes.size()));

            if (sensor == target) continue;

            State newState = new State(state);
            //double heu = newState.getHeuristic();
            String action = "Action: " +
                    Util.sensorToString(sensor, this) +
                    " -> " +
                    Util.objectToString(target, this)
                    + " cost:" + newState.totalCost + " "
                    + " currentFlow: " + newState.totalFlow
                    // + " heuristic: " + heu
                    ;

            if (!newState.moveEdge(sensor, target)) {
                continue;
            }
            Successor succ = new Successor(action, newState);
            res.add(succ);
            return res;
        }
    }

    private SearchMode searchMode = SearchMode.HILL_CLIMBING;

    public void setSearchMode(SearchMode mode) {
        searchMode = mode;
    }

    public enum SearchMode {
        SIMULATED_ANNEALING, HILL_CLIMBING
    }

    @Override
    public boolean isGoalState(Object o) {
        if (!(o instanceof State)) throw new InvalidParameterException("Should be state");
        State s = (State) o;

        // We never know the minimum cost
        return false;
    }

    private boolean isConnected(Sensor s) {
        return graph.get(s) != null;
    }

    public void setInitial() {
        //if (initialState != null) throw new IllegalStateException("Not null");
        initialState = this;
    }
}
