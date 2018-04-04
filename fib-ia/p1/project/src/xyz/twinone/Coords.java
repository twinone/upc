package xyz.twinone;

import IA.Red.Centro;
import IA.Red.Sensor;

import java.security.InvalidParameterException;

public class Coords {
    public final int x;
    public final int y;

    public Coords(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public static Coords get(Object o) {
        if (o instanceof Centro) {
            Centro c = (Centro)o;
            return new Coords(c.getCoordX(), c.getCoordY());
        } else if (o instanceof Sensor) {
            Sensor s = (Sensor)o;
            return new Coords(s.getCoordX(), s.getCoordY());
        }
        throw new InvalidParameterException("Should be Centro or Sensor");
    }
}
