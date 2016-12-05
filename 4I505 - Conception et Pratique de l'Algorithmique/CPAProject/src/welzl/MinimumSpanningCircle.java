package welzl;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

public class MinimumSpanningCircle {
	
	private MinimumSpanningCircle() {}
	
	public static <T extends Point2D> Circle.Double welzl(Collection<T> P) {
		if (P instanceof List<?>) {
			return minidisk((List<T>) P);
		}
		else if(P instanceof Set<?>) {
			return minidisk((Set<T>) P);
		}
		else {
			List<T> Pcopy = new ArrayList<T>(P);
			return minidisk(Pcopy);
		}
	}
	
	public static <T extends Point2D> welzl.Circle.Double algoNaif(Collection<T> points) {
		/***************************************
		 * ALGORITHME NAIF AVEC CERCLE MINIMUM *
		 ***************************************/
		//Avec un peu de chance, on est en O(n3)...
		welzl.Circle.Double c = null; 
		for(T p : points) {
			for(T q : points) {
				Point2D.Double center = new Point2D.Double((p.getX()+q.getX())/2, (p.getY()+q.getY())/2);
				c = new welzl.Circle.Double(center, center.distance(q));
				if(c.containsAll(points)) 
					return c;
			}
		}
		//System.out.println("Pas trouvé en O(n3) :-(");
		//Sinon pas de chance ! O(n4) !
		
		welzl.Circle.Double cMin = null; double minRadius = -1;
		for(T p : points) {
			for(T q : points) {
				for(T r : points) {	
					c = Math.cercleCirconscrit(p, q, r);
					if(c.containsAll(points)) 
						if(c.getRadius() < minRadius || minRadius==-1) {
							cMin = c;
							minRadius = cMin.getRadius();
						}
				}
			}
		}
		if(cMin==null) System.out.println("step should never happened");
		return cMin;
	}

	private static <T extends Point2D> Circle.Double minidisk(List<T> P) {
		if(P.isEmpty() || P.size()==1)
			return new Circle.Double();
		
		Iterator<T> ite = P.iterator();
		T p = ite.next();
		List<T> points = new ArrayList<T>(P);
		points.remove(p);
		Circle.Double D = minidisk(points);

		if(!D.contains(p)) {
			List<T> R = new ArrayList<T>();
			R.add(p);
			D = b_minidisk(points,R);
		}
		return D;
	}
	
	private static <T extends Point2D> Circle.Double b_minidisk(List<T> P, List<T> R) {
		if(P.size()==0 || R.size()==3) {
			return computeCircle(R);
		}

		int pos = (int) (java.lang.Math.random()*P.size());
		T p = P.get(pos);

		List<T> Pcopy = new ArrayList<T>(P); //To avoid modifying the set in a recursion
		Pcopy.remove(p);
		Circle.Double c = b_minidisk(Pcopy, R);
		if(!c.contains(p)) {
			List<T> Rcopy = new ArrayList<T>(R);
			Rcopy.add(p);
			c = b_minidisk(Pcopy,Rcopy);
		}
		return c;
	}
	
	private static <T extends Point2D> Circle.Double minidisk(Set<T> P) {
		if(P.isEmpty() || P.size()==1)
			return new Circle.Double();
		
		Iterator<T> ite = P.iterator();
		T p = ite.next();
		Set<T> points = new HashSet<T>(P);
		points.remove(p);
		Circle.Double D = minidisk(points);

		if(!D.contains(p)) {
			Set<T> R = new HashSet<T>();
			R.add(p);
			D = b_minidisk(points,R);
		}
		return D;
	}
	private static <T extends Point2D> Circle.Double b_minidisk(Set<T> P, Set<T> R) {
		if(P.size()==0 || R.size()==3) {
			return computeCircle(R);
		}
		Iterator<T> ite = P.iterator();
		T p = ite.next();
		Set<T> Pcopy = new HashSet<T>(P); //To avoid modifying the set in a recursion
		Pcopy.remove(p);
		Circle.Double c = b_minidisk(Pcopy, R);
		if(!c.contains(p)) {
			Set<T> Rcopy = new HashSet<T>(R);
			Rcopy.add(p);
			c = b_minidisk(Pcopy,Rcopy);
		}
		return c;
	}

	
	private static <T extends Point2D> Circle.Double computeCircle(Collection<T> R) {
		
		T p1;
		T p2;
		T p3;
		
		Iterator<T> ite = R.iterator();
		Circle.Double c;
		switch(R.size()) {		
			case 2 : 
				p1 = ite.next();
				p2 = ite.next();
				c = new Circle.Double(Math.middlePointOf(p1, p2), p1.distance(p2)/2.0);
				break;
			case 3 : 
				p1 = ite.next();
				p2 = ite.next();
				p3 = ite.next();
				c = Math.cercleCirconscrit(p1, p2, p3);
				break;
			default : 
				c = new Circle.Double();
				break;
		}
		return c;
	}
	
	
	////////////////////////////////////////////////////////////////////////:
	public static <T extends Point2D> Circle.Double MTFminidisk(List<T> P) {
		if(P.isEmpty() || P.size()==1)
			return new Circle.Double();
		
		Iterator<T> ite = P.iterator();
		T p = ite.next();
		List<T> points = new ArrayList<T>(P);
		points.remove(p);
		Circle.Double D = MTFminidisk(points);

		if(!D.contains(p)) {
			List<T> R = new ArrayList<T>();
			R.add(p);
			D = b_MTFminidisk(points,R);
		}
		return D;
	}
	
	private static <T extends Point2D> Circle.Double b_MTFminidisk(List<T> P, List<T> R) {
		if(P.size()==0 || R.size()==3) {
			return computeCircle(R);
		}

		T p = P.get(0);
		permuteLastAndFirst(P);

		List<T> Pcopy = new ArrayList<T>(P); //To avoid modifying the set in a recursion
		Pcopy.remove(p);
		Circle.Double c = b_MTFminidisk(Pcopy, R);
		if(!c.contains(p)) {
			List<T> Rcopy = new ArrayList<T>(R);
			Rcopy.add(p);
			c = b_MTFminidisk(Pcopy,Rcopy);
		}
		return c;
	}
	
	private static <T> void permuteLastAndFirst(List<T> P) {
		if(P==null || P.isEmpty())
			return;
		int last = P.size()-1;
		int first = 0;
		
		T tmp = P.get(first);
		P.set(first, P.get(last));
		P.set(last, tmp);
	}
	

}
