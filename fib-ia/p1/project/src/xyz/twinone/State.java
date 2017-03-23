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
     * The current currentFlow through the object.
     * For a sensor, this is the sum of the incoming currentFlow (the data it receives
     * from it's children) plus it's own capacity
     */
    public final Map<Object, Integer> currentFlow;

    /**
     * The connections between centers and sensors
     */
    public final Map<Sensor, Object> graph;

    /**
     * The initial state to compare to
     */
    public static State initialState;


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

        currentFlow = new HashMap<>();
        for (Object o : nodes) currentFlow.put(o, 0);
    }

    /**
     * Generates a copy (by value) of src<br>
     * <b>Warning: {@link #sensors} and {@link #centers} will be shared!</b>
     */
    public State(State src) {
        // Pointers
        this.sensors = src.sensors;
        this.centers = src.centers;
        this.nodes = src.nodes;


        // Copies
        this.graph = new HashMap<>(src.graph);
        this.remainingConnections = new HashMap<>(src.remainingConnections);
        this.currentFlow = new HashMap<>(src.currentFlow);
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
        if (n == 0) {
            generateInitialSolution1();
            System.out.println("Cost:" + getCost());
        } else if (n == 1) {
            generateInitialSolution2();
            System.out.println("Cost:" + getCost());
        }
        if (!isSolution()) {
            throw new IllegalStateException("generateInitialSolution did not generate a valid solution");
        }
        // Print state
        //printState();
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
            Object best = connectable.get(0);


            connectable.sort(new Comparator<Object>() {
                @Override
                public int compare(Object o1, Object o2) {
                    return (int) (Util.distance(s, o2) - Util.distance(s, o1));
                }
            });


            for (Object o : connectable) {
                if (Util.distance(s, o) < Util.distance(s, best)
                        && checkEdge(s, o)) {

                    best = o;
                }
            }
            addEdge(s, best);
            connectable.add(s);
            // don't overconnect!
            if (remainingConnections.get(best) == 0) connectable.remove(best);
        }
    }


    private int currentFlow(Object o) {
        return currentFlow.get(o);
    }

    /**
     * @return The maximum possible currentFlow through this object
     */
    private int maxFlow(Object o) {
        if (o instanceof Centro) return CENTER_CAPACITY;
        return (int) ((Sensor) o).getCapacidad() * 3;
    }

    private int flowRemaining(Object o) {
        return maxFlow(o) - currentFlow(o);
    }


    public void debugState() {

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

        printState();
    }

    public void printState() {

        System.out.println("Cost     : " + getCost());
        System.out.println("Flow     : " + getTotalFlowAtCenters());
        System.out.println("Max Flow : " + getMaxFlow());
        System.out.println("Flow %   : " + getFlowRatio() * 100);
        System.out.println("Centers: " + centers.size() + ", Sensors: " + sensors.size());
        drawState();
    }

    public void drawState() {

        JFrame frame = new JFrame("Test");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());
        frame.add(new JScrollPane(new StateDraw(sensors, centers, graph, currentFlow)));
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
     * Adds currentFlow to the given node
     * Returns false if the new flow is negative or beyond it's capacity
     */
    private boolean addFlow(Object o, int flow) {
        int newFlow = currentFlow(o) + flow;
        if (newFlow > maxFlow(o)) return false;
        if (newFlow < 0) return false;

        currentFlow.put(o, newFlow);
        return true;
    }

    @SuppressWarnings("SuspiciousMethodCalls")
    private boolean addFlowRecursive(Object o, int flow) {
        if (flowRemaining(o) < flow) return false;

        if (!addFlow(o, flow)) return false;

        if (graph.get(o) == null) return true;

        boolean ok = addFlowRecursive(graph.get(o), flow);
        if (!ok) addFlow(o, -flow);
        return ok;
    }


    /**
     * @return true if the edge was successfully added
     */
    public boolean addEdge(Sensor s, Object o) {
        if (graph.get(s) != null) throw new IllegalStateException("Edge already exists");
        if (s == o) return false;
        if (remainingConnections.get(o) == 0) return false;

        // Since we are currently not connected to anything
        // we need to compute our own capacity

        if (!addFlow(s, (int) s.getCapacidad())) return false;
        // here we've already added the flow to ourselves,
        // now we're only missing the rest of the nodes


        boolean ok = addFlowRecursive(o, currentFlow(s));
        if (ok) {
            graph.put(s, o);
            remainingConnections.put(o, remainingConnections.get(o) - 1);
        } else addFlow(s, -(int) s.getCapacidad());
        return ok;
    }

    public void removeEdge(Sensor s) {
        if (graph.get(s) == null) throw new IllegalStateException("Edge does not exists");
        int flow = currentFlow(s);
        // remove it's own capacity since it's not connected anymore
        addFlow(s, -(int) s.getCapacidad());

        addFlowRecursive(graph.get(s), -flow);
        Object o = graph.get(s);
        graph.remove(s);
        remainingConnections.put(o, remainingConnections.get(o) + 1);
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
        return s.getCost();
    }

    private double getCost() {
        double cost = 0;
        for (Map.Entry<Sensor, Object> e : graph.entrySet()) {
            Sensor s = e.getKey();
            Object v = e.getValue();
            double dst = Util.distance(s, v);
            double flow = currentFlow(s);
            if (flow < 0) {
                throw new IllegalStateException("currentFlow < 0:" + (s.getCapacidad() * 3) + " " + flowRemaining(s));
            }
            cost += dst * dst * flow;
        }
        return cost;
    }

    private double getFlowRatio() {
        return getTotalFlowAtCenters() / (double) getMaxFlow();
    }

    private int getMaxFlow() {
        int sum = 0;
        for (Sensor s : sensors) sum += s.getCapacidad();
        return Math.min(sum, centers.size() * CENTER_CAPACITY);
    }

    /**
     * Gets the current currentFlow that is arriving at all centers
     */
    private int getTotalFlowAtCenters() {
        int sum = 0;
        for (Centro c : centers) sum += currentFlow(c);
        return sum;
    }


    @Override
    public List getSuccessors(Object o) {
        if (!(o instanceof State)) throw new InvalidParameterException("Should be state");
        State state = (State) o;

        if (!state.isSolution()) throw new IllegalStateException("State is not a solution");

        List<Successor> res = new ArrayList<>();

        double initialCost = initialState.getCost();
        double myCost = state.getCost();
        for (final Sensor sensor : state.sensors) {
            for (final Object target : state.nodes) {
                if (sensor == target) continue;

                // TODO optimize
                String action = "Action: " +
                        Util.sensorToString(sensor, this) +
                        " -> " +
                        Util.objectToString(target, this)
                        + " cost:" + myCost + " " + initialCost + "(-" + (100 - (myCost / initialCost) * 100) + "%)"
                        + " currentFlow: " + getTotalFlowAtCenters() + "/" + getMaxFlow() + " (" + getFlowRatio() * 100 + "%)";
                //System.out.println("--- START ----" + sensor.hashCode());
                State newState = new State(state);
                newState.removeEdge(sensor);
                boolean added = newState.addEdge(sensor, target);
                if (!added) continue;

                //System.out.println("--- END   ----");

                Successor succ = new Successor(action, newState);
                res.add(succ);
            }
        }

        //System.out.println("Generated " + res.size() + " successors");
        return res;
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
