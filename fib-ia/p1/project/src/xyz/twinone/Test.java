package xyz.twinone;

import java.util.*;

public class Test {

    public static class Static {
        Map<Coords, Integer> sensors = new LinkedHashMap<>();
        List<Coords> centers = new ArrayList<>();

        Static addCenter(int x, int y) {
            centers.add(new Coords(x, y));
            return this;
        }

        Static addSensor(int x, int y, int cap) {
            sensors.put(new Coords(x, y), cap);
            return this;
        }

        void addTo(List<Static> l) {
            l.add(this);
        }


    }

    static Static t1 = new Static();
    static Static t2 = new Static();
    static Static t3 = new Static();
    static Static t4 = new Static();
    static Static t5 = new Static();

    static List<Static> LIST = new ArrayList<>();


    static {
        new Static()
                .addSensor(0, 1, 2)
                .addSensor(1, 0, 5)
                .addCenter(1, 2)
                .addTo(LIST);

        new Static()
                .addSensor(0, 3, 2)
                .addCenter(1, 3)
                .addSensor(0, 2, 5)
                .addSensor(1, 2, 5)
                .addSensor(0, 1, 2)
                .addSensor(1, 1, 1)
                .addSensor(0, 0, 1)
                .addSensor(1, 0, 5)
                .addTo(LIST);


        new Static()
                .addCenter(0, 0)
                .addSensor(10, 10, 5)
                .addSensor(10, 20, 5)
                .addSensor(10, 30, 2)
                .addSensor(10, 40, 1)
                .addTo(LIST);
    }

    static Static CURRENT = LIST.get(LIST.size() - 1);

    static State getCurrent() {
        return new State(Util.genSensores(Test.CURRENT.sensors), Util.genCentrosDatos(Test.CURRENT.centers));
    }

    static List<State> getAll() {
        List<State> res = new ArrayList<>();
        for (Static s : LIST) {
            State ss = new State(Util.genSensores(Test.CURRENT.sensors), Util.genCentrosDatos(Test.CURRENT.centers));
            res.add(ss);
        }
        return res;
    }

}
