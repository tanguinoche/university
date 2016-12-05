package algorithms;

import java.util.ArrayList;

import structures.Point;

public class FloydWarshall {

	// calcul shortest paths between pairs
	public static int[][] compute(ArrayList<Point> points, int edgeThreshold) {
		int[][] paths=new int[points.size()][points.size()];
		for (int i=0;i<paths.length;i++) for (int j=0;j<paths.length;j++) paths[i][j]=j;

		double[][] D = new double[points.size()][points.size()];
		for(int i = 0; i<D.length; i++){
			for(int j= 0; j<D.length; j++){
				if(i==j)paths[i][j]=0;
				else if(points.get(i).distance(points.get(j))<edgeThreshold){
					D[i][j] = points.get(i).distance(points.get(j));
				}
				else 
					D[i][j] = Double.MAX_VALUE;
			}
		}

		for(int k=0; k<points.size(); k++){
			for(int i=0; i<points.size(); i++){
				for(int j=0; j<points.size(); j++){
					if(D[i][k]+D[k][j]<D[i][j]){
						D[i][j]= D[i][k]+D[k][j];
						paths[i][j] = paths[i][k];
					}
				}
			}
		}
		return paths;
	}
	
}
