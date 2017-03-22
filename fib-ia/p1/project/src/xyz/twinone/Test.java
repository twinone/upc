package xyz.twinone;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by twinone on 22/03/2017.
 */
public class Test {


    public static class Static {
        public Map<Coords, Integer> sensors = new HashMap<>();
        public List<Coords> centers = new ArrayList<>();

        public void addCenter(int x, int y) {
            centers.add(new Coords(x, y));
        }

        public void addSensor(int x, int y, int cap) {
            sensors.put(new Coords(x, y), cap);
        }
    }

    public static Static t1 = new Static();
    public static Static t2 = new Static();
    public static Static t3 = new Static();
    public static Static t4 = new Static();
    public static Static t5 = new Static();


    public static Static CURRENT = t2;

    static {

        t1.addSensor(0, 1, 2);
        t1.addSensor(1, 0, 5);
        t1.addCenter(1, 2);

        //////////////////////////////////
        t2.addSensor(0, 3, 2);
        t2.addCenter(1, 3);

        t2.addSensor(0, 2, 5);
        t2.addSensor(1, 2, 5);

        t2.addSensor(0, 1, 2);
        t2.addSensor(1, 1, 1);

        t2.addSensor(0, 0, 1);
        t2.addSensor(1, 0, 5);

    }

    public static State getCurrent() {
        return new State(Util.genSensores(Test.CURRENT.sensors), Util.genCentrosDatos(Test.CURRENT.centers));
    }

}
