package algorithms;

import java.util.ArrayList;

import structures.Edge;
import structures.Point;
import utils.Utils;

public class Steiner {

	public static final int EDGETHRESHOLD = 55;

	public static ArrayList<Edge> steinerTree(ArrayList<Point> points, int edgeThreshold, ArrayList<Point> hitPoints) {
		int[][] paths = FloydWarshall.compute(points, edgeThreshold);

		ArrayList<Edge> edgesBetweenHitPoints = Kruskal.compute(hitPoints);
		ArrayList<Point> path = new ArrayList<Point>();

		for(Edge e : edgesBetweenHitPoints){
			int i = points.indexOf(e.getP());
			int j = points.indexOf(e.getQ());
			for(Integer k : getPathPointsIndex(i, j, paths)){
				path.add(points.get(k));
			}
		}
		return Kruskal.compute(path);
	}
	
	public static Tree2D getHeuristic(ArrayList<Point> points, int edgeThreshold, ArrayList<Point> hitPoints){
		int[][] paths = FloydWarshall.compute(points, edgeThreshold);

		ArrayList<Edge> edgesBetweenHitPoints = Kruskal.compute(hitPoints);
		ArrayList<Point> path = new ArrayList<Point>();

		for(Edge e : edgesBetweenHitPoints){
			int i = points.indexOf(e.getP());
			int j = points.indexOf(e.getQ());
			for(Integer k : getPathPointsIndex(i, j, paths)){
				path.add(points.get(k));
			}
		}

		Tree2D res = Kruskal.EdgeToTree(Kruskal.compute(path));
		return res;	
	}

	public static ArrayList<Edge> withoutRestriction(ArrayList<Point> points, ArrayList<Edge> l_edges, ArrayList<Point> hitPoints){
		ArrayList<Edge> l_edges_clone = new ArrayList<Edge>(l_edges);

		double score = 0;
		double scoreCentroid = 0;
		double scoreFermat = 0;
		Point centroid = null;
		Point A = null, B = null,  C = null, I = null, J = null;

		for (int i = 0; i < l_edges.size(); i++){
			for (int j = i + 1 ; j < l_edges.size(); j++){
				Edge e1 = l_edges.get(i);
				Edge e2 = l_edges.get(j);

				if(e1.getP().equals(e2.getP())){
					A = e1.getQ();
					B = e1.getP();
					C = e2.getQ();
				}else if(e1.getP().equals(e2.getQ())){
					A = e1.getQ();
					B = e1.getP();
					C = e2.getP();
				}else if( e2.getP().equals(e1.getQ())){
					A = e1.getP();
					B = e1.getQ();
					C = e2.getQ();
				}else if(e1.getQ().equals(e2.getQ())){
					A = e1.getP();
					B = e1.getQ();
					C = e2.getP();
				} else continue;

				centroid = Geom.getCentroid(A,B,C);
				Point fermat = Geom.torricelliFermat(e1, e2);

				I = centroid.nearestPoint(points);
				J = fermat.nearestPoint(points);

				score = A.distance(B) + B.distance(C);
				scoreCentroid = A.distance(I) + B.distance(I) + C.distance(I);
				scoreFermat = A.distance(J) + B.distance(J) + C.distance(J);
				
				Point bestPoint;
				double bestScore = Double.MAX_VALUE;
				if(scoreCentroid<=scoreFermat) {
					bestPoint = I;
					bestScore = scoreCentroid;
					System.out.print("centroid has been better than fermat");
				}else{
					bestPoint = J;
					bestScore = scoreFermat;
					System.out.print("Fermat has been better than centroid");
				}
				
				if(bestScore < score){
					System.out.println(" and better than current score");
					l_edges_clone.add(new Edge(A, bestPoint));
					l_edges_clone.add(new Edge(B, bestPoint));
					l_edges_clone.add(new Edge(C, bestPoint));
					l_edges_clone.remove(e1);
					l_edges_clone.remove(e2);
					hitPoints.add(bestPoint);
				}
				System.out.println();
			}
		}
		return Convertion.treeToEdges(getHeuristic(points, EDGETHRESHOLD, hitPoints));
	}
	
	public static Tree2D withRestriction(int budget, ArrayList<Point> points, ArrayList<Point> hitPoints){
		ArrayList<Point> newHitPoints = new ArrayList<Point>();
		
		//le point 0 de hitPoint est notre point de depart/maison mere
		newHitPoints.add(hitPoints.get(0));
		//on retire de la liste des hitPoints le point qu'on vient de rajouter
		//pour eviter de retomber dessus quand on relance la fonction de distance min
		hitPoints.remove(0);		
		
		//premier ajout de points
		//on cherche a chaque fois le point qui minimize la distance
		//par rapport au dernier point ajouté a la liste newHitPoints
		for(int i=0 ; i<18; i++){
			newHitPoints.add(hitPoints.get(Utils.pointAtMinDistance(newHitPoints.get(i), hitPoints)));
			hitPoints.remove(Utils.pointAtMinDistance(newHitPoints.get(i), hitPoints));
		}
		
		//Deuxieme ajout de points
		//une fois qu'on obtient un 1er arbre qui respecte le budget
		//on cherche pour tout les points de newHitPoints 
		//si on peut trouver un autre point de distance min et on le rajoute
		for(int i=0 ; i<3; i++){
			newHitPoints.add(hitPoints.get(Utils.pointAtMinDistance(newHitPoints, hitPoints)));
			hitPoints.remove(Utils.pointAtMinDistance(newHitPoints, hitPoints));
		}
		
		Tree2D tree = getHeuristic(points, 55, newHitPoints);
		ArrayList<Edge> edges = Convertion.treeToEdges(tree);
		ArrayList<Edge> edgesBis = withoutRestriction(points, edges, newHitPoints);
		
		
		System.out.println(newHitPoints.size());

		return Convertion.EdgesToTree(edgesBis);
	}


	
	public static ArrayList<Point> getListPoints(ArrayList<Point> points, int edgeThreshold, ArrayList<Point> hitPoints){
		int[][] paths = FloydWarshall.compute(points, edgeThreshold);

		ArrayList<Edge> edgesBetweenHitPoints = Kruskal.compute(hitPoints);
		ArrayList<Point> path = new ArrayList<Point>();

		for(Edge e : edgesBetweenHitPoints){
			int i = points.indexOf(e.getP());
			int j = points.indexOf(e.getQ());
			for(Integer k : getPathPointsIndex(i, j, paths)){
				path.add(points.get(k));
			}
		}

		return path;		
	}	



	public static ArrayList<Integer> getPathPointsIndex(int i, int j, int[][] paths){
		ArrayList<Integer> path = new ArrayList<Integer>();
		path.add(i);
		while(paths[i][j] != j){
			path.add(paths[i][j]);
			i = paths[i][j];
		}
		path.add(j);
		return path;
	}

	public static Edge neighbourEdge(Edge e1, ArrayList<Edge> edges){
		for(Edge e2 : edges ){
			if(e1.getP().equals(e2.getP()) || e1.getP().equals(e2.getQ()) || e2.getP().equals(e1.getQ()) || e1.getQ().equals(e2.getQ()))
				return e2;
		}
		return null;
	}
}
