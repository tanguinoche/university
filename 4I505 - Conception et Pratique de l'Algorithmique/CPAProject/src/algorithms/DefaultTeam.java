package algorithms;

import java.awt.Point;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Collection;

import supportGUI.Circle;
import welzl.MinimumSpanningCircle;

public class DefaultTeam {

	// calculDiametre: ArrayList<Point> --> Line
	//   renvoie une pair de points de la liste, de distance maximum.
	public supportGUI.Line calculDiametre(ArrayList<Point> points) {
		return new supportGUI.Line(points.get(0), points.get(1));
	}
	
	// calculCercleMin: ArrayList<Point> --> Circle
	//   renvoie un cercle couvrant tout point de la liste, de rayon minimum.
	public supportGUI.Circle calculCercleMin(ArrayList<Point> points) {
		
		Collection<Point2D.Double> pointsDouble = new ArrayList<>();
		//Collection<Point2D.Double> pointsDouble = new HashSet<>();
		for(Point p : points) {
			pointsDouble.add(new Point2D.Double(p.x, p.y));
		}
		System.out.println("collection copiée");
		
		welzl.Circle.Double minidisk = MinimumSpanningCircle.algoNaif(pointsDouble);


		Circle c = new Circle(new Point((int)minidisk.getCenter().getX(), (int)minidisk.getCenter().getY()), (int)minidisk.getRadius());
		System.out.println("centre : "+c.getCenter().toString());
		System.out.println("rayon : "+c.getRadius());
		return c;
	}
	
	
	
	
}
