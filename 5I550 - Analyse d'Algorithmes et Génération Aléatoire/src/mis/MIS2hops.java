package mis;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;

import algorithms.Tools;

public class MIS2hops {
	int edgeThreshold;
	Collection<Point> blacks = new HashSet<>();
	Collection<Point> grays = new HashSet<>();
	Collection<Point> actives = new HashSet<>();
	Collection<Point> whites; //Contains every whites, active or not

	public ArrayList<Point> process(Collection<Point> points, int edgeThreshold) {
		this.edgeThreshold = edgeThreshold;
		whites = new HashSet<>(points);
		
		//Prendre un point au hasard, il devient noir, ses voisins gris, les voisins de ses voisins actifs.
		
		//Tant qu'il reste des blancs :
		// prendre l'actif qui a le plus de voisins blancs
		// Il devient noir, ses voisins blancs gris, ses voisins de ses voisins blancs actifs
		
		actives.add(Tools.maxNeighbors(whites, edgeThreshold));
		Point focus;
		while (!actives.isEmpty()) {
			focus = pickNextActive();
			turnBlackAndUpdate(focus);
		}
		
		return new ArrayList<Point>(blacks);
	}

	private void turnBlackAndUpdate(Point focus) {
		//focus becomes black, update the whole structure
		//Add black
		blacks.add(focus); whites.remove(focus); actives.remove(focus);
		//Add grays
		Collection<Point> neighbors = Tools.neighbors(focus, whites, edgeThreshold);
		grays.addAll(neighbors); whites.removeAll(neighbors); actives.removeAll(neighbors);
		//Add actives
		HashSet<Point> neighborsTwoHops = new HashSet<>();
		neighbors.stream().forEach(neighbor -> neighborsTwoHops.addAll(Tools.neighbors(neighbor, whites, edgeThreshold)));
		neighborsTwoHops.removeAll(neighbors); neighborsTwoHops.remove(focus);
		actives.addAll(neighborsTwoHops);
	}

	private Point pickNextActive() {
		//Pick the active with the most white neighbors (actives or not)
		return Tools.maxNeighbors(actives, whites, edgeThreshold); //Prendre l'actif qui a le plus plus de voisins parmi les actifs
	}

}
