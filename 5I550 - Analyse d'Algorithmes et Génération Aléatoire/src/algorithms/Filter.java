package algorithms;

import java.awt.Point;
import java.util.ArrayList;

public class Filter {
	
	public static ArrayList<Point> getNeighborLess(ArrayList<Point> points, int edgeThreshold) {
		ArrayList<Point> res = new ArrayList<>();
		points.stream().filter(p-> Tools.nbNeighbors(p, points, edgeThreshold) == 0).forEach(res::add);
		return res;
	}
	
	public static ArrayList<Point> getNeighborOnlyOne(ArrayList<Point> points, int edgeThreshold) {
		ArrayList<Point> res = new ArrayList<>();
		//Tous ceux qui ont un voisin
		points.stream().filter(p-> Tools.nbNeighbors(p, points, edgeThreshold) == 1).forEach(p -> res.addAll(Tools.neighbors(p, points, edgeThreshold))); 
		//On enlève ceux qui sont voisins entre eux
		for(int i = 0; i<res.size(); i++)
			for(int j = 0; j<res.size(); j++) {
				ArrayList<Point> l = new ArrayList<>(Tools.neighbors(res.get(i), res, edgeThreshold));
				if(!l.isEmpty())
					if(l.get(0).equals(res.get(j))) {
						res.remove(res.get(j));
						j--;
					}
			}
		
		return res;
	}

}
