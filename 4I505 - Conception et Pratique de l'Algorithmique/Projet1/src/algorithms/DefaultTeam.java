package algorithms;

import java.awt.Point;
import java.util.ArrayList;

public class DefaultTeam {

  public ArrayList<Point> calculTSP(ArrayList<Point> points) {
    if (points.size()<4) {
      return points;
    }

    int nbIte = 0;
	ArrayList<Point> computingSet = GreedyApproach.greedyTSP(points);
	double score = Double.MAX_VALUE;
	while(Tools.score(computingSet) < score) {
		nbIte++;
		score = Tools.score(computingSet);
		computingSet = Optimisation.opt2v2(computingSet);
	}
	System.out.println("Nombre d'itérations : "+nbIte);
	return computingSet;
  }

  public ArrayList<ArrayList<Point>> calculCinqVoyageursAvecBudget(Point maison, ArrayList<Point> points) {
	double budget = 1664;
	//return GreedyApproach.firstSol(maison, budget, points); //396
	//return GreedyApproach.secondSol(maison, budget, points); //394
	return GreedyApproach.fourthSol(maison, budget, points); //418
	//return GreedyApproach.eigthSol(maison, budget, points); //418
  }
}
