package algorithms;

import structures.Edge;
import structures.Point;

public class Geom {
	
	/**
	 * 
	 * CENTROID
	 * 
	 */

	public static Point getCentroid(Point ...points) {
		int x = 0;
		int y = 0;
		for(Point p : points) {
			x += p.x;
			y += p.y;
		}
		x/=points.length;
		y/=points.length;
		return new Point((int)x, (int)y);
	}
	
	
	
	/**
	 * 
	 * FERMAT
	 * 
	 */
	public static Point torricelliFermat(Edge AB, Edge BC){
		if(!AB.adjacentTo(BC)) return null;
		
		Point A = AB.getUncommonPointTo(BC);
		Point B = AB.getCommonPointTo(BC);
		Point C = BC.getUncommonPointTo(AB);
		Edge AC = new Edge(A, C);

		//Obvious points
		if(Math.abs(AB.getAngleWith(BC)) >= 120)
			return B;
		else if(Math.abs(AB.getAngleWith(AC)) >= 120)
			return A;	
		else if(Math.abs(BC.getAngleWith(AC)) >= 120)
			return C;
		
		//D, E, F		
		Point T = null, R = null;
		int vectABx = B.x - A.x;
		int vectABy = B.y - A.y;
		int vectACx = C.x - A.x;
		int vectACy = C.y - A.y;
		
		double rotGcos = Math.cos(Math.PI/3);
		double rotDcos = Math.cos(-Math.PI/3);
		double rotGsin = Math.sin(Math.PI/3);
		double rotDsin = Math.sin(-Math.PI/3);
		if ((vectABx*vectACy - vectABy*vectACx) > 0){
			T = new Point ((int) Math.round(A.x + vectACx*rotGcos - vectACy*rotGsin), (int) Math.round(A.y + vectACy*rotGcos + (C.x - A.x)*rotGsin));
			R = new Point ((int) Math.round(A.x + vectABx*rotDcos - vectABy*rotDsin), (int) Math.round(A.y + vectABy*rotDcos + (B.x - A.x)*rotDsin));
		}else{
			T = new Point ((int) Math.round(A.x + vectACx*rotDcos - vectACy*rotDsin), (int) Math.round(A.y + vectACy*rotDcos + (C.x - A.x)*rotDsin));
			R = new Point ((int) Math.round(A.x + vectABx*rotGcos - vectABy*rotGsin), (int) Math.round(A.y + vectABy*rotGcos + (B.x - A.x)*rotGsin));
		}
		
		
		// Eq. de droites
		double A1, B1, C1;
		A1 = C.y - R.y;
		B1 = R.x - C.x;
		C1 = A1*R.x + B1*R.y;

		double A2,B2, C2;
		A2 = B.y - T.y;
		B2 = T.x - B.x;
		C2 = A2*T.x + B2*T.y;
		
		double det = A1*B2 - A2*B1;
		double x, y;
		if(det==0) {
			//Paralell
			return A; //or B, or C, whatever
		} else {
			x = (B2*C1 - B1*C2)/det;
			y = (A1*C2 - A2*C1)/det;
		}
		Point fermat = new Point((int)x, (int)y);
		return fermat;
		
	}
}
