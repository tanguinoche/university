package algorithms;

import java.util.ArrayList;

import structures.Edge;
import structures.Point;
import utils.Utils;

public class DefaultTeam {
	public Tree2D calculSteiner(ArrayList<java.awt.Point> points, int edgeThreshold, ArrayList<java.awt.Point> hitPoints) {
		//Juste convertir les points d'entrée en nos points, pour qu'il contiennent un tag.
		ArrayList<structures.Point> hitPoints2 = Point.pointsToVertices(hitPoints);
		ArrayList<structures.Point> points2 = Point.pointsToVertices(points);

		Tree2D tree = Steiner.getHeuristic(points2, edgeThreshold, hitPoints2);
		ArrayList<Edge> edges = Convertion.treeToEdges(tree);
		ArrayList<Edge> edgesBis = Steiner.withoutRestriction(points2, edges, hitPoints2);
		Tree2D tree2 = Convertion.EdgesToTree(edgesBis);

		double oldScore = Utils.score(tree);
		double newScore = Utils.score(tree2);

		while(oldScore > newScore){

			edges = Convertion.treeToEdges(tree2);
			edgesBis = Steiner.withoutRestriction(points2, edges, hitPoints2);
			tree2 = Convertion.EdgesToTree(edgesBis);
			oldScore = newScore;
			newScore = Utils.score(tree2);
		}
		ArrayList<Edge> res = Kruskal.compute(Point.pointsFromEdges(edgesBis));
		tree2 = Convertion.EdgesToTree(res);
		return tree2;
	}


	public Tree2D calculSteinerBudget(ArrayList<java.awt.Point> points, int edgeThreshold, ArrayList<java.awt.Point> hitPoints) {
		ArrayList<structures.Point> hitPoints2 = Point.pointsToVertices(hitPoints);
		ArrayList<structures.Point> points2 = Point.pointsToVertices(points);
		
	    return Steiner.withRestriction(1664, points2, hitPoints2);
	}


}
