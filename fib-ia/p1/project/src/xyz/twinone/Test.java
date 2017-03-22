package xyz.twinone;

import java.util.*;

public class Test {


    public static class Static {
        Map<Coords, Integer> sensors = new LinkedHashMap<>();
        List<Coords> centers = new ArrayList<>();

        void addCenter(int x, int y) {
            centers.add(new Coords(x, y));
        }

        void addSensor(int x, int y, int cap) {
            sensors.put(new Coords(x, y), cap);
        }
    }

    static Static t1 = new Static();
    static Static t2 = new Static();
    static Static t3 = new Static();
    static Static t4 = new Static();
    static Static t5 = new Static();


    static Static CURRENT = t3;

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


        t3.addCenter(-1, 0);
        t3.addSensor(0, 0, 5);
        t3.addSensor(1, 0, 5);
        t3.addSensor(2, 0, 5);
        t3.addSensor(3, 0, 5);

    }

    static State getCurrent() {
        return new State(Util.genSensores(Test.CURRENT.sensors), Util.genCentrosDatos(Test.CURRENT.centers));
    }

}
