package xyz.twinone;

import IA.Red.Centro;
import IA.Red.Sensor;

import java.security.InvalidParameterException;

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

    public static String objectToString(Object o) {
        if (o instanceof Sensor) return sensorToString((Sensor)o);
        if (o instanceof Centro) return centerToString((Centro)o);
        throw new InvalidParameterException("Must be Centro or Sensor");
    }

    public static String sensorToString(Sensor s) {
        return "Sensor (" + s.getCoordX() + "," + s.getCoordY() + "): " + s.getCapacidad();
    }

    public static String centerToString(Centro s) {
        return "Centro (" + s.getCoordX() + "," + s.getCoordY() + ")";
    }

}
