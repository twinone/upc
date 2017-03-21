package xyz.twinone;

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

}
