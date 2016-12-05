package algorithms;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collections;

public class GreedyApproach {
	
	public static ArrayList<ArrayList<Point>> firstSol(Point maison, double budget, ArrayList<Point> points) {
	    ArrayList<Point> alice = new ArrayList<Point>(); alice.add(maison);
	    ArrayList<Point> bob = new ArrayList<Point>(); bob.add(maison);
	    ArrayList<Point> cindy = new ArrayList<Point>(); cindy.add(maison);
	    ArrayList<Point> dave = new ArrayList<Point>(); dave.add(maison);
	    ArrayList<Point> eddy = new ArrayList<Point>(); eddy.add(maison);

	    ArrayList<Point> clone = (ArrayList<Point>) points.clone();
	    clone.remove(maison);
	    
	    alice = Tools.partDePizza(maison, 72*0, 72*1, clone);
	    System.out.println("Alice nb points : "+alice.size());
	    bob = Tools.partDePizza(maison, 72*1, 72*2, clone);
	    System.out.println("Bob nb points : "+bob.size());
	    cindy = Tools.partDePizza(maison, 72*2, 72*3, clone);
	    System.out.println("Cindy nb points : "+cindy.size());
	    dave = Tools.partDePizza(maison, 72*3, 72*4, clone);
	    System.out.println("Dave nb points : "+dave.size());
	    eddy = Tools.partDePizza(maison, 72*4, 72*5, clone);
	    System.out.println("Eddy nb points : "+eddy.size());
	    

	    alice = GreedyApproach.greedyTSPWithBudget(alice, maison, budget);
	    bob = GreedyApproach.greedyTSPWithBudget(bob, maison, budget);
	    cindy = GreedyApproach.greedyTSPWithBudget(cindy, maison, budget);
	    dave = GreedyApproach.greedyTSPWithBudget(dave, maison, budget);
	    eddy = GreedyApproach.greedyTSPWithBudget(eddy, maison, budget);
	    
	    ArrayList<ArrayList<Point>> result = new ArrayList<ArrayList<Point>>();
	    result.add(alice);
	    result.add(bob);
	    result.add(cindy);
	    result.add(dave);
	    result.add(eddy);

	    return result;
	}
	
	public static ArrayList<Point> greedyTSP(ArrayList<Point> points) {
		ArrayList<Point> solution = new ArrayList<>();
		ArrayList<Point> aParcourir = new ArrayList<>(points);
		
		solution.add(aParcourir.get(0));
		while(!aParcourir.isEmpty()) {
			solution.add(Tools.nearest(solution.get(solution.size()-1), aParcourir));
		}
		
		return solution;
	}
	
	public static ArrayList<Point> greedyTSPWithBudget(ArrayList<Point> points, Point maison, double budget) {
		ArrayList<Point> solution = new ArrayList<>();
		ArrayList<Point> aParcourir = new ArrayList<>(points);
		double leftBudget = budget;
		solution.add(maison);
		
		Point focus = maison;
		while(!aParcourir.isEmpty()) {
			Point nearest = Tools.nearest(focus, aParcourir);
			
			double distanceWithNearest = focus.distance(nearest);
			
			double distanceToGoBack = nearest.distance(maison);
			if(leftBudget-(distanceToGoBack+distanceWithNearest) < 0) {
					return solution;
			}
			solution.add(nearest);
			focus = nearest;
			leftBudget -= distanceWithNearest;
		}
		return solution;
	}

	private static ArrayList<Point> greedyTSPWithBudgetBiase(ArrayList<Point> points, Point maison, double budget,
			int i) {
		ArrayList<Point> solution = new ArrayList<>();
		ArrayList<Point> aParcourir = new ArrayList<>(points);
		double leftBudget = budget;
		solution.add(maison);
		
		Point focus = maison;
		while(!aParcourir.isEmpty()) {
			i--;
			Point nearest;
			if(i==0)
				nearest = Tools.nearestDown(focus, aParcourir);
			else
				nearest = Tools.nearest(focus, aParcourir);
			
			double distanceWithNearest = focus.distance(nearest);
			
			double distanceToGoBack = nearest.distance(maison);
			if(leftBudget-(distanceToGoBack+distanceWithNearest) < 0) {
					return solution;
			}
			solution.add(nearest);
			focus = nearest;
			leftBudget -= distanceWithNearest;
		}
		return solution;
	}
	
	private static ArrayList<Point> greedyTSPWithBudgetBiaseAndDistMax(ArrayList<Point> points, Point maison, double budget,
			int i, int max) {
		ArrayList<Point> solution = new ArrayList<>();
		ArrayList<Point> aParcourir = new ArrayList<>(points);
		double leftBudget = budget;
		solution.add(maison);
		
		Point focus = maison;
		while(!aParcourir.isEmpty()) {
			i--;
			Point nearest;
			if(i==0)
				nearest = Tools.nearestDownMax(focus, aParcourir, max, maison);
			else
				nearest = Tools.nearestMax(focus, aParcourir, max, maison);
			
			double distanceWithNearest = focus.distance(nearest);
			
			double distanceToGoBack = nearest.distance(maison);
			if(leftBudget-(distanceToGoBack+distanceWithNearest) < 0) {
					return solution;
			}
			solution.add(nearest);
			focus = nearest;
			leftBudget -= distanceWithNearest;
		}
		return solution;
	}

	private static ArrayList<Point> greedyTSPWithBudgetDistMax(ArrayList<Point> points, Point maison, double budget, int max) {
		ArrayList<Point> solution = new ArrayList<>();
		ArrayList<Point> aParcourir = new ArrayList<>(points);
		double leftBudget = budget;
		solution.add(maison);
		
		Point focus = maison;
		while(!aParcourir.isEmpty()) {
			Point nearest;
			nearest = Tools.nearest(focus, aParcourir);
			if(nearest.distance(maison)>max) continue;
			
			double distanceWithNearest = focus.distance(nearest);
			
			double distanceToGoBack = nearest.distance(maison);
			if(leftBudget-(distanceToGoBack+distanceWithNearest) < 0) {
					return solution;
			}
			solution.add(nearest);
			focus = nearest;
			leftBudget -= distanceWithNearest;
		}
		return solution;
	}
	
	private static ArrayList<Point> greedyTSPWithBudgetDoublePath(ArrayList<Point> points, Point maison, double budget ) {
		ArrayList<Point> solution = new ArrayList<>();
		ArrayList<Point> solutionBack = new ArrayList<>();
		ArrayList<Point> aParcourir = new ArrayList<>(points);
		
		solution.add(maison);
		solutionBack.add(maison);
		
		Point focus = maison;
		Point focus2 = maison;
		
		while(aParcourir.size() >=2) {
			Point nearest;
			nearest = Tools.nearest(focus, aParcourir);
			Point nearest2;
			nearest2 = Tools.nearest(focus2, aParcourir);
			
			double distanceWithNearest = focus.distance(nearest);
			double distanceWithNearest2 = focus2.distance(nearest2);
			
			double distanceBetweenNearest = nearest.distance(nearest2);
			
			double distanceToGoFocus = Tools.score(solution);
			double distanceToGoFocus2 = Tools.score(solutionBack);
			if(distanceToGoFocus + distanceToGoFocus2 + distanceWithNearest + distanceWithNearest2 + distanceBetweenNearest < budget) {
				solution.add(nearest);
				focus=nearest;
				//solution = Optimisation.opt2v2(solution);
				
				solutionBack.add(nearest2);
				focus2=nearest2;
				//solutionBack = Optimisation.opt2v2(solutionBack);
			}

		}
		Collections.reverse(solutionBack);
		solution.addAll(solutionBack);
		solution.remove(solution.size()-1);
		
		return solution;
	}
	
	
	
	private static ArrayList<Point> greedyTSPWithBudgetDoublePathAngled(ArrayList<Point> points, Point maison, double budget,double min, double max) {
		ArrayList<Point> solution = new ArrayList<>();
		ArrayList<Point> solutionBack = new ArrayList<>();
		ArrayList<Point> aParcourir = Tools.partDePizza(maison, min, max, points);
		
		solution.add(maison);
		solutionBack.add(maison);
		
		Point focus = maison;
		Point focus2 = maison;
		
		while(aParcourir.size() >=2) {
			Point nearest;
			nearest = Tools.nearest(focus, aParcourir);
			Point nearest2;
			nearest2 = Tools.nearest(focus2, aParcourir);
			
			double distanceWithNearest = focus.distance(nearest);
			double distanceWithNearest2 = focus2.distance(nearest2);
			
			double distanceBetweenNearest = nearest.distance(nearest2);
			
			double distanceToGoFocus = Tools.score(solution);
			double distanceToGoFocus2 = Tools.score(solutionBack);
			if(distanceToGoFocus + distanceToGoFocus2 + distanceWithNearest + distanceWithNearest2 + distanceBetweenNearest < budget) {
				solution.add(nearest);
				focus=nearest;
				solution = Optimisation.opt2v2(solution);
				//solution = Optimisation.opt2v2(solution);
				
				solutionBack.add(nearest2);
				focus2=nearest2;
				solutionBack = Optimisation.opt2v2(solutionBack);
				//solutionBack = Optimisation.opt2v2(solutionBack);
			}

		}
		Collections.reverse(solutionBack);
		solution.addAll(solutionBack);
		solution.remove(solution.size()-1);
		
		return solution;
	}
	public static ArrayList<ArrayList<Point>> secondSol(Point maison, double budget, ArrayList<Point> points) {
	    ArrayList<Point> alice = new ArrayList<Point>(); alice.add(maison);
	    ArrayList<Point> bob = new ArrayList<Point>(); bob.add(maison);
	    ArrayList<Point> cindy = new ArrayList<Point>(); cindy.add(maison);
	    ArrayList<Point> dave = new ArrayList<Point>(); dave.add(maison);
	    ArrayList<Point> eddy = new ArrayList<Point>(); eddy.add(maison);

	    ArrayList<Point> clone = (ArrayList<Point>) points.clone();
	    clone.remove(maison);
	    
	    alice = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(alice);
	    bob = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(bob);
	    bob = Optimisation.opt2v2(bob);
	    cindy = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(cindy);
	    cindy = Optimisation.opt2v2(cindy);
	    dave = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(dave);
	    dave = Optimisation.opt2v2(dave);
	    eddy = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(eddy);
	    eddy = Optimisation.opt2v2(eddy);
	    
	    ArrayList<ArrayList<Point>> result = new ArrayList<ArrayList<Point>>();
	    result.add(alice);
	    result.add(bob);
	    result.add(cindy);
	    result.add(dave);
	    result.add(eddy);

	    return result;
	}
	
	public static ArrayList<ArrayList<Point>> thirdSol(Point maison, double budget, ArrayList<Point> points) {
	    ArrayList<Point> alice = new ArrayList<Point>(); alice.add(maison);
	    ArrayList<Point> bob = new ArrayList<Point>(); bob.add(maison);
	    ArrayList<Point> cindy = new ArrayList<Point>(); cindy.add(maison);
	    ArrayList<Point> dave = new ArrayList<Point>(); dave.add(maison);
	    ArrayList<Point> eddy = new ArrayList<Point>(); eddy.add(maison);

	    ArrayList<Point> clone = (ArrayList<Point>) points.clone();
	    clone.remove(maison);
	    
	    alice = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    alice = Optimisation.opt2v2(alice); //On optimise
	    //On recherche le plus près dans points des points d'alice
	    //Si on l'ajoute à la bonne place, et que ça reste < au budget, on continue
	    while(true) {
		    Point p = Tools.nearestPointOfPath(alice, points);
		    if(p==null) break;
		    ArrayList<Point> tmp = addPointPath(p, alice);
		    if(Tools.score(tmp) < 1664 && alice.size() < tmp.size()) {
		    	alice = tmp;
		    } else break;
	    }
	    clone.removeAll(alice);
	    
	    
	    bob = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    bob = Optimisation.opt2v2(bob);
	    while(true) {
		    Point p = Tools.nearestPointOfPath(bob, points);
		    if(p==null) break;
		    ArrayList<Point> tmp = addPointPath(p, bob);
		    if(Tools.score(tmp) < 1664 && bob.size() < tmp.size()) {
		    	bob = tmp;
		    } else break;
	    }
	    clone.removeAll(bob);
	    
	    
	    
	    cindy = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    cindy = Optimisation.opt2v2(cindy);
	    while(true) {
		    Point p = Tools.nearestPointOfPath(cindy, points);
		    if(p==null) break;
		    ArrayList<Point> tmp = addPointPath(p, cindy);
		    if(Tools.score(tmp) < 1664 && cindy.size() < tmp.size()) {
		    	cindy = tmp;
		    } else break;
	    }
	    clone.removeAll(cindy);
	    
	    
	    
	    
	    dave = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    dave = Optimisation.opt2v2(dave);
	    while(true) {
		    Point p = Tools.nearestPointOfPath(dave, points);
		    if(p==null) break;
		    ArrayList<Point> tmp = addPointPath(p, dave);
		    System.out.println(tmp.size()+ " "+Tools.score(tmp));
		    System.out.println(dave.size()+ " "+Tools.score(dave));
		    if(Tools.score(tmp) < 1664 && dave.size() < tmp.size()) {
		    	dave = tmp;
		    } else break;
	    }
	    clone.removeAll(dave);
	    
	    
	    
	    
	    eddy = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    eddy = Optimisation.opt2v2(eddy);
	    while(true) {
		    Point p = Tools.nearestPointOfPath(eddy, points);
		    if(p==null) break;
		    ArrayList<Point> tmp = addPointPath(p, eddy);
		    if(Tools.score(tmp) < 1664 && eddy.size() < tmp.size()) {
		    	eddy = tmp;
		    } else break;
	    }
	    clone.removeAll(eddy);
	    
	    
	    ArrayList<ArrayList<Point>> result = new ArrayList<ArrayList<Point>>();
	    result.add(alice);
	    result.add(bob);
	    result.add(cindy);
	    result.add(dave);
	    result.add(eddy);

	    return result;
	}
	
	public static ArrayList<ArrayList<Point>> fourthSol(Point maison, double budget, ArrayList<Point> points) {
	    ArrayList<Point> alice = new ArrayList<Point>(); alice.add(maison);
	    ArrayList<Point> bob = new ArrayList<Point>(); bob.add(maison);
	    ArrayList<Point> cindy = new ArrayList<Point>(); cindy.add(maison);
	    ArrayList<Point> dave = new ArrayList<Point>(); dave.add(maison);
	    ArrayList<Point> eddy = new ArrayList<Point>(); eddy.add(maison);

	    ArrayList<Point> clone = (ArrayList<Point>) points.clone();
	    clone.remove(maison);
	    
	    alice = GreedyApproach.greedyTSPWithBudgetBiase(clone, maison, budget, 9);
	    alice = Optimisation.opt2v2(alice); //On optimise
	    clone.removeAll(alice);
	    bob = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(bob);
	    bob = Optimisation.opt2v2(bob);
	    cindy = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(cindy);
	    cindy = Optimisation.opt2v2(cindy);
	    dave = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(dave);
	    dave = Optimisation.opt2v2(dave);
	    eddy = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(eddy);
	    eddy = Optimisation.opt2v2(eddy);
	    
	    
	    ArrayList<ArrayList<Point>> result = new ArrayList<ArrayList<Point>>();
	    result.add(alice);
	    result.add(bob);
	    result.add(cindy);
	    result.add(dave);
	    result.add(eddy);

	    return result;
	}
	
	public static ArrayList<ArrayList<Point>> fifthSol(Point maison, double budget, ArrayList<Point> points) {
	    ArrayList<Point> alice = new ArrayList<Point>(); alice.add(maison);
	    ArrayList<Point> bob = new ArrayList<Point>(); bob.add(maison);
	    ArrayList<Point> cindy = new ArrayList<Point>(); cindy.add(maison);
	    ArrayList<Point> dave = new ArrayList<Point>(); dave.add(maison);
	    ArrayList<Point> eddy = new ArrayList<Point>(); eddy.add(maison);

	    ArrayList<Point> clone = (ArrayList<Point>) points.clone();
	    clone.remove(maison);
	    
	    alice = GreedyApproach.greedyTSPWithBudgetBiaseAndDistMax(clone, maison, budget, 9, 400);
	    alice = Optimisation.opt2v2(alice); //On optimise
	    clone.removeAll(alice);
	    bob = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(bob);
	    bob = Optimisation.opt2v2(bob);
	    cindy = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(cindy);
	    cindy = Optimisation.opt2v2(cindy);
	    dave = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(dave);
	    dave = Optimisation.opt2v2(dave);
	    eddy = GreedyApproach.greedyTSPWithBudget(clone, maison, budget);
	    clone.removeAll(eddy);
	    eddy = Optimisation.opt2v2(eddy);
	    
	    
	    ArrayList<ArrayList<Point>> result = new ArrayList<ArrayList<Point>>();
	    result.add(alice);
	    result.add(bob);
	    result.add(cindy);
	    result.add(dave);
	    result.add(eddy);

	    return result;
	}
	
	public static ArrayList<ArrayList<Point>> sixthSol(Point maison, double budget, ArrayList<Point> points) {
	    ArrayList<Point> alice = new ArrayList<Point>(); alice.add(maison);
	    ArrayList<Point> bob = new ArrayList<Point>(); bob.add(maison);
	    ArrayList<Point> cindy = new ArrayList<Point>(); cindy.add(maison);
	    ArrayList<Point> dave = new ArrayList<Point>(); dave.add(maison);
	    ArrayList<Point> eddy = new ArrayList<Point>(); eddy.add(maison);

	    ArrayList<Point> clone = (ArrayList<Point>) points.clone();
	    clone.remove(maison);
	    int max = 400;
	    alice = GreedyApproach.greedyTSPWithBudgetDistMax(clone, maison, budget, max);
//	    alice = Optimisation.opt2v2(alice); //On optimise
	    clone.removeAll(alice);
	    bob = GreedyApproach.greedyTSPWithBudgetDistMax(clone, maison, budget, max);
	    clone.removeAll(bob);
//	    bob = Optimisation.opt2v2(bob);
	    cindy = GreedyApproach.greedyTSPWithBudgetDistMax(clone, maison, budget, max);
	    clone.removeAll(cindy);
//	    cindy = Optimisation.opt2v2(cindy);
	    dave = GreedyApproach.greedyTSPWithBudgetDistMax(clone, maison, budget, max);
	    clone.removeAll(dave);
//	    dave = Optimisation.opt2v2(dave);
	    eddy = GreedyApproach.greedyTSPWithBudgetDistMax(clone, maison, budget, max);
	    clone.removeAll(eddy);
//	    eddy = Optimisation.opt2v2(eddy);
	    
	    
	    ArrayList<ArrayList<Point>> result = new ArrayList<ArrayList<Point>>();
	    result.add(alice);
	    result.add(bob);
	    result.add(cindy);
	    result.add(dave);
	    result.add(eddy);

	    return result;
	}

	public static ArrayList<ArrayList<Point>> seventhSol(Point maison, double budget, ArrayList<Point> points) {
	    ArrayList<Point> alice = new ArrayList<Point>(); alice.add(maison);
	    ArrayList<Point> bob = new ArrayList<Point>(); bob.add(maison);
	    ArrayList<Point> cindy = new ArrayList<Point>(); cindy.add(maison);
	    ArrayList<Point> dave = new ArrayList<Point>(); dave.add(maison);
	    ArrayList<Point> eddy = new ArrayList<Point>(); eddy.add(maison);

	    ArrayList<Point> clone = (ArrayList<Point>) points.clone();
	    clone.remove(maison);
	    
	    alice = GreedyApproach.greedyTSPWithBudgetDoublePath(clone, maison, budget);
	    alice = Optimisation.opt2v2(alice); //On optimise
	    clone.removeAll(alice);
	    bob = GreedyApproach.greedyTSPWithBudgetDoublePath(clone, maison, budget);
	    clone.removeAll(bob);
	    bob = Optimisation.opt2v2(bob);
	    cindy = GreedyApproach.greedyTSPWithBudgetDoublePath(clone, maison, budget);
	    clone.removeAll(cindy);
	    cindy = Optimisation.opt2v2(cindy);
	    dave = GreedyApproach.greedyTSPWithBudgetDoublePath(clone, maison, budget);
	    clone.removeAll(dave);
	    dave = Optimisation.opt2v2(dave);
	    eddy = GreedyApproach.greedyTSPWithBudgetDoublePath(clone, maison, budget);
	    clone.removeAll(eddy);
	    eddy = Optimisation.opt2v2(eddy);
	    
	    
	    ArrayList<ArrayList<Point>> result = new ArrayList<ArrayList<Point>>();
	    result.add(alice);
	    result.add(bob);
	    result.add(cindy);
	    result.add(dave);
	    result.add(eddy);

	    return result;
	}
	
	
	public static ArrayList<ArrayList<Point>> eigthSol(Point maison, double budget, ArrayList<Point> points) {
	    ArrayList<Point> alice = new ArrayList<Point>(); alice.add(maison);
	    ArrayList<Point> bob = new ArrayList<Point>(); bob.add(maison);
	    ArrayList<Point> cindy = new ArrayList<Point>(); cindy.add(maison);
	    ArrayList<Point> dave = new ArrayList<Point>(); dave.add(maison);
	    ArrayList<Point> eddy = new ArrayList<Point>(); eddy.add(maison);

	    ArrayList<Point> clone = (ArrayList<Point>) points.clone();
	    clone.remove(maison);
	    
	    alice = GreedyApproach.greedyTSPWithBudgetDoublePathAngled(clone, maison, budget, 0, 72);
	    alice = Optimisation.opt2v2(alice); //On optimise
	    clone.removeAll(alice);
	    bob = GreedyApproach.greedyTSPWithBudgetDoublePathAngled(clone, maison, budget, 72, 72*2);
	    clone.removeAll(bob);
	    bob = Optimisation.opt2v2(bob);
	    cindy = GreedyApproach.greedyTSPWithBudgetDoublePathAngled(clone, maison, budget, 72*2, 72*3);
	    clone.removeAll(cindy);
	    cindy = Optimisation.opt2v2(cindy);
	    dave = GreedyApproach.greedyTSPWithBudgetDoublePathAngled(clone, maison, budget, 72*3, 72*4);
	    clone.removeAll(dave);
	    dave = Optimisation.opt2v2(dave);
	    eddy = GreedyApproach.greedyTSPWithBudgetDoublePathAngled(clone, maison, budget, 72*4, 72*5);
	    clone.removeAll(eddy);
	    eddy = Optimisation.opt2v2(eddy);
	    
	    
	    ArrayList<ArrayList<Point>> result = new ArrayList<ArrayList<Point>>();
	    result.add(alice);
	    result.add(bob);
	    result.add(cindy);
	    result.add(dave);
	    result.add(eddy);

	    return result;
	}
	

	private static ArrayList<Point> addPointPath(Point p, ArrayList<Point> alice) {
		ArrayList<Point> solution = new ArrayList<>(alice);
		solution.add(p);
		double score = Double.MAX_VALUE;
		while(Tools.score(solution) < score) {
			score = Tools.score(solution);
			solution = Optimisation.opt2v2(solution);
		}
		return solution;
	}



}
