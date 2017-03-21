package xyz.twinone;

import IA.Red.Centro;
import IA.Red.CentrosDatos;
import IA.Red.Sensor;
import IA.Red.Sensores;

import java.security.InvalidParameterException;
import java.util.*;

public class State {

    /**
     * Maximum allowed connections per center
     */
    private static final int CONNS_CENTER = 25;
    /**
     * Maximum allowed connections per sensor
     */
    private static final int CONNS_SENSOR = 3;

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
     * The connections between centers and sensors
     */
    private final Map<Object, List<Sensor>> graph;


    /**
     * Genera un estado con sensors y centers de datos con coordenadas aleatorias.
     *
     * @param numSensores     El numero de sensors
     * @param numCentrosDatos El numero de centers de datos
     * @param seed            La semilla para los sensors y estados
     */
    public State(int numSensores, int numCentrosDatos, int seed) {
        if (numSensores <= 0) throw new InvalidParameterException("numSensores should be > 0");
        if (numCentrosDatos <= 0) throw new InvalidParameterException("numCentrosDatos should be > 0");

        // Set up the sensors and centers
        sensors = new Sensores(numSensores, seed);
        centers = new CentrosDatos(numCentrosDatos, seed);

        nodes = new ArrayList<>();
        nodes.addAll(sensors);
        nodes.addAll(centers);

        remainingConnections = new HashMap<>();
        for (Centro c : centers) remainingConnections.put(c, CONNS_CENTER);
        for (Sensor s : sensors) remainingConnections.put(s, CONNS_SENSOR);

        // Initialize the graph
        graph = new HashMap<>();
        for (Sensor s : sensors) graph.put(s, new ArrayList<>());
        for (Centro c : centers) graph.put(c, new ArrayList<>());
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
        this.graph = new HashMap<>();


        // Copies
        for (Map.Entry<Object, List<Sensor>> e: graph.entrySet()) {
            this.graph.put(e.getKey(), new ArrayList<>(e.getValue()));
        }
        this.remainingConnections = new HashMap<>(src.remainingConnections);
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
    }

    /**
     * Generates a naive valid solution for the problem
     *
     * Basically it adds each sensor to a free node. We begin with
     * the centers as free nodes. When we add a sensor to it, we make this
     * sensor a free node too as it can still hold 2 more sensors attached to it
     *
     * This will finish correctly because all sensor can be connected no matter
     * how many
     */
    private void generateInitialSolutionSimple() {
        // For each data center, connect up to 25 sensors to it
        Queue<Sensor> pending = new LinkedList<>(sensors);
        Queue<Object> connectable = new LinkedList<>(centers);

        while (!pending.isEmpty()) {
            Sensor s = pending.poll();
            Object parent = connectable.peek();

            // Add the edge from the parent to the sensor
            addEdge(parent, s);

            // Add the sensor to the queue of connectable devices
            // When adding a new sensor to the queue,
            // it has exactly 2 connections left
            connectable.add(s);

            // don't overconnect!
            if (remainingConnections.get(parent) == 0) connectable.remove();
        }
    }

    private void addEdge(Object parent, Sensor s) {
        graph.get(parent).add(s);
        remainingConnections.put(parent, remainingConnections.get(parent) - 1);
        remainingConnections.put(s, remainingConnections.get(s) - 1);
    }

    private void removeEdge(Object parent, Sensor s) {
        graph.get(parent).remove(s);
        remainingConnections.put(parent, remainingConnections.get(parent) + 1);
        remainingConnections.put(s, remainingConnections.get(s) + 1);
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
        List<Object> x = new ArrayList<>(nodes);
        for (Object o : nodes) {
            if (remainingConnections.get(o) < 0) {
                throw new IllegalStateException("A node has negative remaining connections");
            }
        }

        for (Map.Entry<Object, List<Sensor>> e: graph.entrySet()) {
            if (e.getValue().size() >= 1 || e.getKey() instanceof Centro)
                x.remove(e.getKey());

            // Remove all nodes from x
            x.removeAll(e.getValue());
        }
        if (!x.isEmpty()) throw new IllegalStateException("The graph is not connected");

        return true;
    }


    private List<State> generateNextStates() {
        // TODO
        throw new RuntimeException("Stub!");
    }

}
