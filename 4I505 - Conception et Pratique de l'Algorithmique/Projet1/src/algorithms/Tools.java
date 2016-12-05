package algorithms;

import java.awt.Point;
import java.util.ArrayList;

public class Tools {
	public static double score(ArrayList<Point> points) {
		double score=0;
		int size = points.size();
		for(int i=0; i<size; i++)
				score += points.get(i).distance(points.get((i+1)%size));
		
		return score;
	}

	
	public static Point nearest(Point point, ArrayList<Point> points) {
		int iMin=0;
		for(int i=0; i<points.size(); i++) {
			if(point.distanceSq(points.get(i)) < point.distanceSq(points.get(iMin)))
				iMin = i;
		}
		return points.remove(iMin);
	}
	public static Point nearestDown(Point point, ArrayList<Point> points) {
		int iMin=0;
		for(int i=0; i<points.size(); i++) {
			if(point.distanceSq(points.get(i)) < point.distanceSq(points.get(iMin)) && points.get(i).y > point.y)
				iMin = i;
		}
		return points.remove(iMin);
	}
	public static Point nearestWest(Point point, ArrayList<Point> points) {
		int iMin=0;
		for(int i=0; i<points.size(); i++) {
			if(point.distanceSq(points.get(i)) < point.distanceSq(points.get(iMin)) && points.get(i).x < point.x)
				iMin = i;
		}
		return points.remove(iMin);
	}
	public static Point nearestEast(Point point, ArrayList<Point> points) {
		int iMin=0;
		for(int i=0; i<points.size(); i++) {
			if(point.distanceSq(points.get(i)) < point.distanceSq(points.get(iMin)) && points.get(i).x > point.x)
				iMin = i;
		}
		return points.remove(iMin);
	}
	
	public static Point nearestPointOfPath(ArrayList<Point> path, ArrayList<Point> points) {
		ArrayList<Point> set = new ArrayList<>(points);
		set.removeAll(path);
		int jMin=0;
		for(int i=0; i<path.size(); i++)
			for(int j=0; j<set.size(); j++) {
				if(path.get(i).distanceSq(set.get(j)) < path.get(i).distanceSq(set.get(jMin))) {
					jMin = j;
				}
			}
		
		System.out.println(points.get(jMin));
		return set.get(jMin);
	}
	
	//On considère angleMin = 0 l'axe nord du point origin
	public static ArrayList<Point> partDePizza(Point origin, double angleMin, double angleMax, ArrayList<Point> points) {
		Point ordonee = new Point(origin.x, origin.y-50); //Juste pour avoir un point de référence, au dessus de origin
		ArrayList<Point> solution = new ArrayList<>(points);
		solution.remove(origin); //Le point ne devrait pas être dans la liste, au cas où quand même
		
		for(Point point : points) {
			double angle = getAngleWith(origin, ordonee, point);
			System.out.println("angle : "+angle);
			if(angle < angleMin || angle > angleMax) {
				solution.remove(point);
			}
		}
		
		return solution;
		
	}
	
	
	public static double getAngleWith(Point origin, Point a, Point b) {
		
		double OA = a.distance(origin);
		double OB = b.distance(origin);
		
		int scal = scalaire(a, b, origin);
		
		return Math.toDegrees(2*Math.acos(scal / (OA * OB)));
	}
	private static int scalaire(Point a, Point b, Point c) {//c le point en commun
		return scalaire(c, a, c, b);
	}
	private static int scalaire(Point a, Point b, Point c, Point d) {
		int x_ab = b.x - a.x;
		int y_ab = b.y - a.y;
		int x_cd = d.x - c.x;
		int y_cd = d.y - c.y;
		return x_ab*x_cd + y_ab*y_cd;
	}


	public static Point nearestDownMax(Point point, ArrayList<Point> points, int max, Point maison) {
		int iMin=0;
		for(int i=0; i<points.size(); i++) {
			if(point.distanceSq(points.get(i)) < point.distanceSq(points.get(iMin)) && points.get(i).y > point.y && point.distance(maison)<max)
				iMin = i;
		}
		return points.remove(iMin);
	}
	
	public static Point nearestMax(Point point, ArrayList<Point> points, int max, Point maison) {
		int iMin=0;
		for(int i=0; i<points.size(); i++) {
			if(point.distanceSq(points.get(i)) < point.distanceSq(points.get(iMin)) && point.distance(maison)<max)
				iMin = i;
		}
		return points.remove(iMin);
	}
}
