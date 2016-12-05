package algorithms;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

import structures.Edge;
import structures.Point;

public class Kruskal {

	public static ArrayList<Edge> compute(ArrayList<Point> vertices) {
		ArrayList<Edge> candidates = Edge.createEdges(vertices);
		Collections.sort(candidates);

		ArrayList<Edge> solution = new ArrayList<>();

		for(int i=0; i<vertices.size(); i++) {
			vertices.get(i).tag = i;
		}

		UnionFind uf = new UnionFind(vertices.size());
		
		for(Edge edge : candidates) {
			//Si on ne crée pas de cycle
			if(!uf.isConnected(edge.getP().tag, edge.getQ().tag)) {
				solution.add(edge);
				uf.union(edge.getP().tag, edge.getQ().tag);
			}
		}
		return solution;
	}


	@SuppressWarnings("unused")
	private static void reetiqueter(int x, int y, HashMap<Point, Integer> myHash) {
		for(Point p : myHash.keySet()) {
			if(x == myHash.get(p))
				myHash.replace(p, y);
		}
	}

	@SuppressWarnings("unused")
	private static HashMap<Point, Integer> getHash(ArrayList<Point> points) {
		HashMap<Point, Integer> res = new HashMap<Point, Integer>();
		int cpt = 0;
		for(Point tmp : points) 
			res.put(tmp, cpt++);
		return res;
	}

	public static Tree2D EdgeToTree(ArrayList<Edge> solution) {
		return EdgeToTreeRec(solution.get(0).getP(), solution);
	}

	@SuppressWarnings("unchecked")
	private static Tree2D EdgeToTreeRec(Point myPoint, ArrayList<Edge> solution) {
		ArrayList<Edge> solution2; 
		Point cur = myPoint;
		ArrayList<Point> fils = getAllExtre(cur, solution);
		Tree2D cur2D = new Tree2D(cur, new ArrayList<Tree2D>());

		if(fils.isEmpty())
			return cur2D;

		for(Point tmp : fils) {
			solution2 = (ArrayList<Edge>) solution.clone();
			Edge branche = getEdge(myPoint, tmp, solution2);
			solution2.remove(branche);

			Tree2D fils2D = EdgeToTreeRec(tmp, solution2);
			cur2D.getSubTrees().add(fils2D);
		}
		
		return cur2D;
	}
	
	private static Edge getEdge(Point point1, Point point2, ArrayList<Edge> solution2) {
		for(Edge tmp : solution2) {
			if(tmp.getP().equals(point1) && tmp.getQ().equals(point2))
				return tmp;
			if(tmp.getP().equals(point2) && tmp.getQ().equals(point1))
				return tmp;
		}
		return null;
	}

	private static ArrayList<Point> getAllExtre(Point cur, ArrayList<Edge> solution) {
		ArrayList<Point> res = new ArrayList<Point>();

		for(Edge a : solution) {
			if(a.getP().equals(cur)) 
				res.add(a.getQ());
			else if(a.getQ().equals(cur))
				res.add(a.getP());
		}
		return res;
	}

	public static ArrayList<Edge> getAllEdges(ArrayList<Point> points) {
		ArrayList<Edge> Edges = new ArrayList<Edge>();
		for(int i=0 ; i<points.size() ; i++) {
			for(int j = i+1 ; j<points.size() ; j++) {
				Point p1 = points.get(i);
				Point p2 = points.get(j);
				if(p1.equals(p2)) continue;
				Edges.add(new Edge(p1, p2));
			}
		}
		return Edges;
	}

}
