package welzl;
import java.awt.Color;
import java.awt.Point;
import java.awt.geom.Point2D;
import java.util.Collection;

public abstract class Circle {

	protected Color color;
	
	
	public static class Double extends Circle {
		private Point2D.Double center;
		private double radius;
		
		public Double() { //"EMPTY" CIRCLE
			center = new Point2D.Double();
			radius = 0.0;
			color = Color.RED;
		}
		public Double(Point2D.Double center, double radius) { 
			this.center = center;
			this.radius = radius;
			color = Color.RED;
		}

		public Point2D.Double getCenter() {
			return center;
		}

		public double getRadius() {
			return radius;
		}
	}
	
	public static class Float extends Circle {
		private Point2D.Float center;
		private float radius;
		
		public Float() { //"EMPTY" CIRCLE
			center = new Point2D.Float();
			radius = 0f;
			color = Color.RED;
		}
		public Float(Point2D.Float center, float radius) { 
			this.center = center;
			this.radius = radius;
			color = Color.RED;
		}

		public Point2D.Float getCenter() {
			return center;
		}

		public double getRadius() {
			return (double)radius;
		}
	}

	public static class Integer extends Circle {
		private Point center;
		private int radius;
		
		public Integer() { //"EMPTY" CIRCLE
			center = new Point();
			radius = 0;
			color = Color.RED;
		}
		public Integer(Point center, int radius) { 
			this.center = center;
			this.radius = radius;
			color = Color.RED;
		}

		public Point getCenter() {
			return center;
		}

		public double getRadius() {
			return (double)radius;
		}

		
	}
	
    public boolean contains(Point2D p) {
    	
    	if( ((getCenter().getX()-p.getX())*(getCenter().getX()-p.getX())+(getCenter().getY()-p.getY())*(getCenter().getY()-p.getY())) >= (getRadius()*getRadius()) )
			return false;
    	else
    		return true;
    }
    
	public <T extends Point2D> boolean containsAll(Collection<T> points) {
		if(points!=null)
			for(T p : points) {
				if( ((getCenter().getX()-p.getX())*(getCenter().getX()-p.getX())+(getCenter().getY()-p.getY())*(getCenter().getY()-p.getY())) >= (getRadius()*getRadius()) )
					return false;
			}
		return true;
	}

	public Color getColor() {
		return color;
	}
	
	protected abstract double getRadius();
	
	protected abstract Point2D getCenter();
	
}
