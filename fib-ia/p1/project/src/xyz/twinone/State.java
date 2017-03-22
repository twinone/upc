package xyz.twinone;

import IA.Red.Centro;
import IA.Red.CentrosDatos;
import IA.Red.Sensor;
import IA.Red.Sensores;
import aima.search.framework.Successor;

import java.security.InvalidParameterException;
import java.util.*;

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
     * Maximum flow a data center can handle
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
    private final Map<Object, Integer> remainingConnections;


    /**
     * The remaining incoming flow for each object
     * For example a Sensor of capacity 5 can handle a flow of 15
     * If we connect it to a data center it will have 10 incoming flow
     * remaining.
     */
    private final Map<Object, Integer> flowLeft;

    /**
     * The connections between centers and sensors
     */
    private final Map<Sensor, Object> graph;


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

        flowLeft = new HashMap<>();
        for (Centro c : centers) flowLeft.put(c, CENTER_CAPACITY);
        for (Sensor s : sensors) flowLeft.put(s, (int) s.getCapacidad() * 3);

    }

    /**
     * Generates a copy (by value) of src<br>
     * <b>Warning: {@link #sensors} and {@link #centers} will be shared!</b>
     */
    private State(State src) {
        // Pointers
        this.sensors = src.sensors;
        this.centers = src.centers;
        this.nodes = src.nodes;


        // Copies
        this.graph = new HashMap<>(src.graph);
        this.remainingConnections = new HashMap<>(src.remainingConnections);
        this.flowLeft = new HashMap<>(src.flowLeft);
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
     * Generates an initial valid solution for the problem using generateInitialSolutionSimple()
     *
     * @see State#generateInitialSolution()
     */
    public void generateInitialSolution() {
        generateInitialSolutionSimple();
        if (!isSolution()) {
            throw new IllegalStateException("generateInitialSolution did not generate a valid solution");
        }
        // Print state
        printState();
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
    private void generateInitialSolutionSimple() {
        List<Object> connectable = new ArrayList<>(centers);
        for (Sensor s : sensors) {
            Object best = connectable.get(0);
            addEdge(s, best);
            connectable.add(s);
            if (remainingConnections.get(best) == 0) connectable.remove(best);
        }

    }

    private void generateInitialSolution2() {
        List<Object> connectable = new ArrayList<>(centers);
        for (Sensor s : sensors) {
            Object best = connectable.get(0);

            for (Object o : connectable) {
                if (Util.distance(o, s) < Util.distance(best, s)) {
                    best = o;
                }
            }
            addEdge(s, best);
            connectable.add(s);
            // don't overconnect!
            if (remainingConnections.get(best) == 0) connectable.remove(best);
        }
    }

    /**
     * Updates the flow of a sensor and all the sensors (or datacenter)
     * it's connected to, recursively
     *
     * @param s
     * @param connect true if we add the edge, false otherwise
     */
    private boolean updateFlows(Sensor s, boolean connect) {
        if (connect) return updateFlowsRecursive(s, (int) s.getCapacidad());
        // TODO test
        return updateFlowsRecursive(s, (int) -s.getCapacidad());
    }

    /**
     * Adds flow to the flow of o
     */
    private boolean addFlow(Object o, int flow) {
        int res = flowLeft.get(o) + flow;
        if (res < 0) return false;
        flowLeft.put(o, res);
        return true;
    }

    private boolean updateFlowsRecursive(Object o, int flow) {
        Util.check(o);

        boolean ok = addFlow(o, -flow);
        if (!ok) return false;


        if (o instanceof Centro) return true;

        // If we get to this point, the flow of this node
        // is already decreased
        boolean next = updateFlowsRecursive(graph.get(o), flow);
        // if any of the next nodes fail, we have to reset out count
        if (!next) addFlow(o, flow);

        return next;
    }

    private void printState() {
        for (Sensor s : sensors) {
            Object o = graph.get(s);
            System.out.println(
                    Util.sensorToString(s, flowLeft.get(s)) +
                            " -> " +
                            Util.objectToString(o, flowLeft.get(o))
            );
        }

        for (Centro c : centers) {
            System.out.println(Util.centerToString(c, flowLeft.get(c)));
        }
        System.out.println("Cost     : " + getCost());
        System.out.println("Flow     : " + getTotalFlow());
        System.out.println("Max Flow : " + getMaxFlow());
        System.out.println("Flow %   : " + getFlowRatio() * 100);
        System.out.println("Centers: " + centers.size() + ", Sensors: " + sensors.size());
    }

    private void addEdge(Sensor s, Object o) {
        if (graph.get(s) != null) throw new InvalidParameterException("Source node is already in graph");

        graph.put(s, o);
        remainingConnections.put(o, remainingConnections.get(o) - 1);
        if (COUNT_OUTGOING) remainingConnections.put(s, remainingConnections.get(s) - 1);
        updateFlows(s, true);
    }

    private void removeEdge(Object parent, Sensor s) {
        if (graph.get(s) != parent) throw new InvalidParameterException("Edge is not in graph");

        graph.remove(s);
        remainingConnections.put(parent, remainingConnections.get(parent) + 1);
        if (COUNT_OUTGOING) remainingConnections.put(s, remainingConnections.get(s) + 1);
        updateFlows(s, false);
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

        if (!x.isEmpty()) throw new IllegalStateException("The graph is not connected");


        return true;
    }


    /*
     * AIMA stuff
     */

    @Override
    public double getHeuristicValue(Object o) {
        if (!(o instanceof State)) throw new InvalidParameterException("Should be state");
        State s = (State) o;
        // TODO take flow into account here
        return s.getCost();
    }

    private double getCost() {
        double cost = 0;
        for (Map.Entry<Sensor, Object> e : graph.entrySet()) {
            Sensor s = e.getKey();
            Object v = e.getValue();
            double dst = Util.distance(s, v);
            double cap = s.getCapacidad();
            cost += dst * dst * cap;
        }
        return cost;
    }

    private double getFlowRatio() {
        return getTotalFlow() / (double) getMaxFlow();
    }

    private int getMaxFlow() {
        int sum = 0;
        for (Sensor s : sensors) sum += s.getCapacidad();
        return Math.min(sum, centers.size() * CENTER_CAPACITY);
    }

    private int getTotalFlow() {
        int sum = 0;
        for (Centro c : centers) sum += CENTER_CAPACITY - flowLeft.get(c);
        return sum;
    }


    @Override
    public List getSuccessors(Object o) {
        if (!(o instanceof State)) throw new InvalidParameterException("Should be state");
        State s = (State) o;

        List<Successor> res = new ArrayList<>();

        // TODO

        return res;
    }

    @Override
    public boolean isGoalState(Object o) {
        if (!(o instanceof State)) throw new InvalidParameterException("Should be state");
        State s = (State) o;

        return false;
    }

    private boolean isConnected(Sensor s) {
        return graph.get(s) != null;
    }
}
