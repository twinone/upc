package xyz.twinone;

import IA.Red.Centro;
import IA.Red.CentrosDatos;
import IA.Red.Sensor;
import IA.Red.Sensores;

import java.security.InvalidParameterException;
import java.util.List;
import java.util.Map;

public class Util {

    /**
     * @return The euclidean distance from a to b
     */
    public static double distance(Object a, Object b) {
        Coords ca = Coords.get(a);
        Coords cb = Coords.get(b);
        int dx = ca.x - cb.x;
        int dy = ca.y - cb.y;
        return Math.sqrt(dx * dx + dy * dy);
    }

    public static String objectToString(Object o, State st) {
        if (o instanceof Sensor) return sensorToString((Sensor) o, st);
        if (o instanceof Centro) return centerToString((Centro) o, st);
        throw new InvalidParameterException("Must be Centro or Sensor");
    }

    public static String sensorToString(Sensor s, State st) {
        return "Sensor (" + s.getCoordX() + "," + s.getCoordY() + ":cap=" +(int)s.getCapacidad()+"flow=" + st.flowLeft.get(s) + ",conn="+st.remainingConnections.get(s) +")";
    }

    public static String centerToString(Centro s, State st) {
        return "Centro (" + s.getCoordX() + "," + s.getCoordY() + ":flow=" + st.flowLeft.get(s) + ",conn="+st.remainingConnections.get(s) +")";
    }


    public static CentrosDatos genCentrosDatos(List<Coords> list) {
        CentrosDatos cd = new CentrosDatos(0, 0);
        for (Coords c : list) {
            cd.add(new Centro(c.x, c.y));
        }
        return cd;
    }

    public static Sensores genSensores(Map<Coords, Integer> map) {
        Sensores ss = new Sensores(0, 0);
        for (Map.Entry<Coords, Integer> ci : map.entrySet()) {
            Coords c = ci.getKey();
            Integer i = ci.getValue();
            ss.add(new Sensor(i, c.x, c.y));
        }

        return ss;
    }

    /**
     * Checks whether o is a sensor or a center
     * @param o the object to check
     */
    public static void check(Object o) throws InvalidParameterException {
        if (!(o instanceof Sensor) && !(o instanceof Centro))
            throw new InvalidParameterException("Should be Sensor or Centro" + ", was " + o);
    }


}
