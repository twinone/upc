package xyz.twinone;

/**
 * Created by Davigo on 22/03/2017.
 */
/* Simple graph drawing class
Bert Huang
COMS 3137 Data Structures and Algorithms, Spring 2009

This class is really elementary, but lets you draw
reasonably nice graphs/trees/diagrams. Feel free to
improve upon it!
 */

import IA.Red.Centro;
import IA.Red.CentrosDatos;
import IA.Red.Sensor;
import IA.Red.Sensores;

import java.awt.geom.AffineTransform;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.util.List;
import java.util.concurrent.Semaphore;
import javax.swing.*;

public class StateDraw extends JPanel implements Scrollable {

    private static int SEP_SCALE = 1;
    private static int SCALE = 1;
    private static final int AUM_DIST = 7 * SEP_SCALE;
    private static final int MARGIN = 10 * SEP_SCALE;
    public static final Color COLOR_1 = Color.decode("#FFF176");
    public static final Color COLOR_2 = Color.decode("#FF9800");
    public static final Color COLOR_5 = Color.decode("#C62828");
    public static final Color COLOR_CENTER = Color.blue;
    private final int ARR_SIZE = 1 * SCALE;


    int centerSize;
    int sensorSize;
    int minWidth;
    int minHeight;

    Sensores s;
    CentrosDatos cd;
    Map<Sensor, Object> gg;
    Map<Object, Integer> flow;

    public StateDraw(Sensores s, CentrosDatos cd, Map<Sensor, Object> gg, Map<Object, Integer> fl) {

        centerSize = 15 * SCALE;
        sensorSize = 10 * SCALE;
        this.s = s;
        this.cd = cd;
        this.gg = gg;
        this.flow = fl;

        minHeight = 0;
        minWidth = 0;

        for (Sensor ss : this.s) {
            if (ss.getCoordX() > minWidth) minWidth = ss.getCoordX();
            if (ss.getCoordY() > minHeight) minHeight = ss.getCoordY();
        }
        for (Centro ccd : this.cd) {
            if (ccd.getCoordX() > minWidth) minWidth = ccd.getCoordX();
            if (ccd.getCoordY() > minHeight) minHeight = ccd.getCoordY();
        }
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension((minWidth * AUM_DIST) + MARGIN * 2, (minHeight * AUM_DIST) + MARGIN * 2);
    }

    @Override
    public Dimension getMinimumSize() {
        return new Dimension((minWidth * AUM_DIST) + MARGIN * 2, (minHeight * AUM_DIST) + MARGIN * 2);
    }

    @Override
    public Dimension getPreferredScrollableViewportSize() {
        return new Dimension(1000, 1000);
    }

    @Override
    public int getScrollableUnitIncrement(Rectangle visibleRect, int orientation, int direction) {
        return 128;
    }

    @Override
    public int getScrollableBlockIncrement(Rectangle visibleRect, int orientation, int direction) {
        return 128;
    }

    @Override
    public boolean getScrollableTracksViewportWidth() {
        return getPreferredSize().width
                <= getParent().getSize().width;
    }

    @Override
    public boolean getScrollableTracksViewportHeight() {
        return getPreferredSize().height
                <= getParent().getSize().height;
    }


    void drawArrow(Graphics g1, int x1, int y1, int x2, int y2) {
        Graphics2D g = (Graphics2D) g1.create();

        double dx = x2 - x1, dy = y2 - y1;
        double angle = Math.atan2(dy, dx);
        int len = (int) Math.sqrt(dx * dx + dy * dy);
        AffineTransform at = AffineTransform.getTranslateInstance(x1, y1);
        at.concatenate(AffineTransform.getRotateInstance(angle));
        g.transform(at);

        // Draw horizontal arrow starting in (0, 0)
        g.drawLine(0, 0, len, 0);
        g.fillPolygon(new int[]{len, len - ARR_SIZE, len - ARR_SIZE, len},
                new int[]{0, -ARR_SIZE, ARR_SIZE, 0}, 4);
    }

    @Override
    public void paintComponent(Graphics g) { // draw the nodes and edges
        super.paintComponent(g);

        g.setColor(Color.black);

        int dist = (int) (sensorSize / (Math.sqrt(2) * 2));

        for (Sensor ss : s) {

            g.setColor(Color.black);
            int coordX = (ss.getCoordX() * AUM_DIST) + MARGIN;
            int coordY = (ss.getCoordY() * AUM_DIST) + MARGIN;

            switch ((int) ss.getCapacidad()) {
                case 1:
                    g.setColor(COLOR_1);
                    break;
                case 2:
                    g.setColor(COLOR_2);
                    break;
                case 5:
                    g.setColor(COLOR_5);
                    break;
            }
            g.fillOval(coordX, coordY,
                    sensorSize, sensorSize);
            g.setColor(Color.black);
            g.drawOval(coordX, coordY,
                    sensorSize, sensorSize);
            String cap = flow.get(ss).toString();
            String coord = "(" + ss.getCoordX() + ","  + ss.getCoordY() + ")";
            g.drawString(cap + " " + coord, coordX+10,
                    coordY + 20);
        }

        for (Centro ccd : cd) {
            g.setColor(COLOR_CENTER);
            int x = (ccd.getCoordX() * AUM_DIST) - (centerSize / 2) + MARGIN;
            int y = (ccd.getCoordY() * AUM_DIST) - (centerSize / 2) + MARGIN;
            g.fillOval(x, y,
                    centerSize, centerSize);
            g.setColor(Color.black);
            g.drawOval(x,y,
                    centerSize, centerSize);
            g.drawString(""+flow.get(ccd), x+10,
                    y + 35);

        }

        for (Sensor ss : s) {
            if (gg.get(ss) == null) continue;

            g.setColor(Color.black);
            int coordX = (ss.getCoordX() * AUM_DIST) + MARGIN;
            int coordY = (ss.getCoordY() * AUM_DIST) + MARGIN;

            Object o = gg.get(ss);
            int oCoordX = o instanceof Sensor ? (((Sensor) o).getCoordX() * AUM_DIST + MARGIN) + dist :
                    (((Centro) o).getCoordX() * AUM_DIST + MARGIN);
            int oCoordY = o instanceof Sensor ? (((Sensor) o).getCoordY() * AUM_DIST + MARGIN) + dist :
                    (((Centro) o).getCoordY() * AUM_DIST + MARGIN);
            drawArrow(g, coordX + dist, coordY + dist,
                    oCoordX, oCoordY);

        }

        /*for (Edge e : edges) {
            drawArrow(g, nodes.get(e.i).x, nodes.get(e.i).y,
                    nodes.get(e.j).x-dist, nodes.get(e.j).y-dist);
        }*/

        /*for (Node n : nodes) {
            int nodeWidth = nodeHeight;
            //int nodeWidth = Math.max(width, f.stringWidth(n.name)+width/2);
            g.setColor(Color.white);
            g.fillOval(n.x-nodeWidth/2, n.y-nodeHeight/2,
                    nodeWidth, nodeHeight);
            g.setColor(Color.black);
            g.drawOval(n.x-nodeWidth/2, n.y-nodeHeight/2,
                    nodeWidth, nodeHeight);

            g.drawString(n.name, n.x-f.stringWidth(n.name)/2,
                    n.y+f.getHeight()/2);
        }*/
    }
}

