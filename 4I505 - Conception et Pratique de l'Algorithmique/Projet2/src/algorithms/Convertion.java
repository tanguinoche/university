package algorithms;

import java.util.ArrayList;

import structures.Edge;
import structures.Point;

public class Convertion {

	/** EDGES TO TREE **/
	public static Tree2D EdgesToTree(ArrayList<Edge> solution) {
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
	
	
	private static Edge getEdge(Point point1, Point point2, ArrayList<Edge> solution2) {
		for(Edge tmp : solution2) {
			if(tmp.getP().equals(point1) && tmp.getQ().equals(point2))
				return tmp;
			if(tmp.getP().equals(point2) && tmp.getQ().equals(point1))
				return tmp;
		}
		return null;
	}
	
	/** TREE TO EDGES **/
	public static ArrayList<Edge> treeToEdges(Tree2D tree){
		ArrayList<Edge> res = new ArrayList<Edge>();
		res = getEdgesFromTreeRec(tree,res);
		return res;
	}

	private static ArrayList<Edge> getEdgesFromTreeRec(Tree2D tree,ArrayList<Edge> res){
		for(int i=0;i<tree.getSubTrees().size();i++){
			Edge a = new Edge(tree.getRootPoint(),tree.getSubTrees().get(i).getRootPoint());
			res.add(a);
			getEdgesFromTreeRec(tree.getSubTrees().get(i),res);
		}
		return res;
	}
}
