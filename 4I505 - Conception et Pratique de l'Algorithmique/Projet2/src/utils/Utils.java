package utils;

import java.util.ArrayList;

import algorithms.Tree2D;
import structures.Edge;
import structures.Point;

public class Utils {

	static double SQRT32=0.866025403784439;
	
	public static double score(Tree2D tree){
		double d = tree.distanceRootToSubTrees();
		for (int i = 0; i < tree.getSubTrees().size(); i++) {
			d += score(tree.getSubTrees().get(i));
		}
		return d;
	}
	
	public static int scoreBis(ArrayList<Edge> edges){
		int score = 0;
		for (Edge e: edges){
			score += e.getDistance();
	}
		return score;
		
	}

	public static double prodScalaire(Point A, Point B, Point C){
		return (B.getX()-A.getX())*(C.getX()-A.getX())+(B.getY()-A.getY())*(C.getY()-A.getY());
	}

	public static double angle(Point A, Point B, Point C){
		return prodScalaire(A, B, C)/(B.distance(A)*C.distance(A));
	}
	public static int pointAtMinDistance(Point p,ArrayList<Point> points){
		double dist = Double.MAX_VALUE;
		int res = 0;

		for(int i=0; i<points.size(); i++){
			if(p.distance(points.get(i))<dist && !p.equals(points.get(i))){
				dist = p.distance(points.get(i));
				res = i;
			}
		}
		return res;
	}
	
	
	public static int pointAtMinDistance(ArrayList<Point> hitPoints,ArrayList<Point> points){
		double dist = Double.MAX_VALUE;		
		double distBis = Double.MAX_VALUE;
		int res = 0, i_min = 0;
		for(int i=0; i<hitPoints.size(); i++){
			Point p = hitPoints.get(i);	
			
			for(int j=0; j<points.size(); j++){
				if(p.distance(points.get(j))<dist && !p.equals(points.get(j))){
					dist = p.distance(points.get(j));
					i_min = j;
				}
			}
			if(p.distance(points.get(i_min))<distBis){
				distBis = p.distance(points.get(i_min));
				res = i_min;
			}
		}
		return res;
	}
	
	
	
}
