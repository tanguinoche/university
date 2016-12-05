package algorithms;

import java.awt.Point;

public class Edge implements Comparable<Edge> {

    private int etiquette;
    private double distance;
	private Point p;
    private Point q;

    public Edge(Point p, Point q, int etiquette) {
        this.p = p;
        this.q = q;
        this.etiquette = etiquette;
        this.distance = p.distanceSq(q);
    }

    @Override
    public int compareTo(Edge e) {
    	return Double.compare(this.distance, e.getDistance());
    }

    public double getDistance() {
        return this.distance;
    }

    public int getEtiquette() {
        return this.etiquette;
    }

    public void setEtiquette(int i) {
        this.etiquette = i;
    }

    public String toString() {
    	StringBuilder str = new StringBuilder();
    	str.append("[").append(p.toString()).append(',').append(q.toString()).append("]");
        return str.toString();
    }

    public Point getP(){
        return this.p;
    }

    public  Point getQ(){
        return this.q;
    }

}
