package structures;

import java.util.ArrayList;

public class Point extends java.awt.Point {
	private static final long serialVersionUID = 8561320844424096772L;
	public int tag;
	
	public Point(int x, int y) {
		super(x,y);
	}
	
	public Point nearestPoint(ArrayList<Point> list){
		double distance = java.lang.Double.MAX_VALUE;
		Point res = null;
		for(Point p : list ){
			if(distance(p)<distance){
				distance = distance(p);
				res = p;
			}
		}
		return res; 
	}
	
	/***********************
	 * POINTS TO VERTICES  *
	 **********************/
	
	public static ArrayList<Point> pointsToVertices(ArrayList<java.awt.Point> points) {
		//Create vertices
		ArrayList<Point> vertices = new ArrayList<>();
		for(java.awt.Point p : points)
			vertices.add(new Point(p.x, p.y));
		
		return vertices;
	}
	
	public String toString() {
		return "[x="+x+",y="+y+"]";
	}

	public static ArrayList<Point> pointsFromEdges(ArrayList<Edge> edges) {
		ArrayList<Point> points = new ArrayList<>();
		for(Edge e : edges) {
			if(!points.contains(e.getP()))
				points.add(e.getP());
			if(!points.contains(e.getQ()))
				points.add(e.getQ());
		}
		return points;
	}

}