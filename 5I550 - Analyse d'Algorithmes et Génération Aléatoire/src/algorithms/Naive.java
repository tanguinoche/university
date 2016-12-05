package algorithms;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collection;


public class Naive {
	ArrayList<Point> innocents = new ArrayList<>(); //Les points qu'on veut garder
	ArrayList<Point> guilties = new ArrayList<>(); // Les points qu'on veut tuer

	public ArrayList<Point> process(ArrayList<Point> points, int edgeThreshold) {
		ArrayList<Point> nodes = new ArrayList<>(points);
		
		guilties.addAll(Filter.getNeighborLess(nodes, edgeThreshold));
		//guilties.addAll(Filter.getNeighborOnlyOne(nodes, edgeThreshold));
		
		nodes.removeAll(guilties);
		
		
		while(!Tools.checkConnexe(guilties, points, edgeThreshold) && !nodes.isEmpty()) {
			//calculer celui qui a le plus de voisins
			Point p = Tools.maxNeighbors(nodes, edgeThreshold);
			//ses voisins sont innocents
			Collection<Point> neighborsOfP = Tools.neighbors(p, nodes, edgeThreshold);
			innocents.addAll(neighborsOfP);
			nodes.removeAll(neighborsOfP);
			//le mettre en presumed_guilty
			guilties.add(p);
			nodes.remove(p);
		}
		
		return guilties;
	}
}
