package welzl;

import java.awt.geom.Point2D;

public class Math {
	private Math() {}
	
	
	public static <T extends Point2D> Point2D.Double middlePointOf(T p1, T p2) {
		return new Point2D.Double((p1.getX()+p2.getX())/2, (p1.getY()+p2.getY())/2);
	}
	
	/**
	 * solve equation of type :
	 * ax + by = c
	 * dx + ey = f
	 * return the point (x,y)
	 */
	public static Point2D.Double solveEquation(double a, double b, double c, double d, double e, double f){
		if((a*e-d*b)==0) return new Point2D.Double();
		double x = (c*e-f*b)/(a*e-d*b);
		double y = (a*f-d*c)/(a*e-d*b);
		return new Point2D.Double(x, y);
		
	}
	
	public static <T extends Point2D> Circle.Double cercleCirconscrit(T A, T B, T C){
		
		double Ix = (A.getX()+B.getX())/2.0;
		double Iy = (A.getY()+B.getY())/2.0;
		double Jx = (B.getX()+C.getX())/2.0;
		double Jy = (B.getY()+C.getY())/2.0;
		Point2D.Double center = solveEquation(B.getX()-A.getX(), 
										B.getY()-A.getY(), 
										Ix*B.getX() - Ix*A.getX() + Iy*B.getY() - Iy*A.getY(), 
										C.getX()-B.getX(),
										C.getY()-B.getY(),
										Jx*C.getX() - Jx*B.getX() + Jy*C.getY() - Jy*B.getY());
		double radius = center.distance(C);		
		return new Circle.Double(center, java.lang.Math.ceil(radius));
		
	}

}
