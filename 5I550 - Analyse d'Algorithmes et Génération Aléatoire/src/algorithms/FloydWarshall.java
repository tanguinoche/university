package algorithms;

import java.awt.Point;
import java.util.ArrayList;

public class FloydWarshall {
	
    public static int[][] process(ArrayList<Point> points, int edgeThreshold) {
        int[][] paths = new int[points.size()][points.size()];
        for (int i = 0; i < paths.length; i++) for (int j = 0; j < paths.length; j++) paths[i][j] = j;
        paths = FloydWarshall.aux(points, edgeThreshold, paths);
        return paths;
    }

	public static int[][] aux(ArrayList<Point> points, int threshold, int[][] paths) {
		int taille = points.size();
		double[][] distances = new double[taille][taille];
		for (int i = 0; i < taille; i++) {
			for (int j = 0; j < taille; j++) {
				distances[i][j] = points.get(i).distance(points.get(j));
				if (distances[i][j] >= threshold) distances[i][j] = Double.MAX_VALUE;
			}
		}
		for (int k = 0; k < taille; k++) {
			for (int i = 0; i < taille; i++) {
				for (int j = 0; j < taille; j++) {
					if (distances[i][j] > distances[i][k] + distances[k][j]) {
						paths[i][j] = paths[i][k];
					}
					distances[i][j] = Math.min(distances[i][j], distances[i][k] + distances[k][j]);
				}
			}
		}
		return paths;
	}
}
