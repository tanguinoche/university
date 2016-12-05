package cds;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;

import algorithms.Tools;

public class GreedyCDS implements ICDS {
		int edgeThreshold;
		Collection<Point> blacks = new HashSet<>();
		Collection<Point> greys = new HashSet<>();
		Collection<Point> grey_neighbors = new HashSet<>();
		Collection<Point> whites; //Contains every whites, active or not

		@Override
		public ArrayList<Point> process(Collection<Point> points, int edgeThreshold) {
			this.edgeThreshold = edgeThreshold;
			whites = new HashSet<>(points);
			
			Point focus = Tools.maxNeighbors(whites, edgeThreshold);
			do {
				turnBlackAndUpdate(focus);
				if(grey_neighbors.isEmpty()) break;
				focus = pickNextActive();
			}while(true);
			
			return new ArrayList<Point>(blacks);
		}

		private void turnBlackAndUpdate(Point focus) {
			//Add black
			blacks.add(focus); whites.remove(focus); grey_neighbors.remove(focus);
			//Add greys
			Collection<Point> neighbors = Tools.neighbors(focus, whites, edgeThreshold);
			greys.addAll(neighbors); whites.removeAll(neighbors); grey_neighbors.removeAll(neighbors);
			//Add actives
			HashSet<Point> neighborsTwoHops = new HashSet<>();
			neighbors.stream().forEach(neighbor -> neighborsTwoHops.addAll(Tools.neighbors(neighbor, whites, edgeThreshold)));
			neighborsTwoHops.removeAll(neighbors); neighborsTwoHops.remove(focus);
			grey_neighbors.addAll(neighborsTwoHops);
		}

		private Point pickNextActive() {
			return Tools.maxNeighbors(greys, grey_neighbors, edgeThreshold); // Gris qui a le plus de voisins parmi les actifs
		}

	}

