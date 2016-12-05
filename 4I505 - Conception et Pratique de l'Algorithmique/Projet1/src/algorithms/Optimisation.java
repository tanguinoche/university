package algorithms;

import java.awt.Point;
import java.util.ArrayList;

public class Optimisation {

	public static ArrayList<Point> opt2v1(ArrayList<Point> points) {
		int size = points.size();
		for(int i = 0; i<size; i++)
			for(int j = i+2; j<size; j++) {
				// On considère les deux segments [i, i+1], [j, j+1]
				// On regarde les distances des couples segment ([i,i+1],[j,j+1]) et ([i,j],[i+1, j+1])
				double a = points.get(i).distance(points.get((i+1)%size));
				double b = points.get(j%size).distance(points.get((j+1)%size));
				double c = points.get(i).distance(points.get(j%size));
				double d = points.get((i+1)%size).distance(points.get((j+1)%size));
				
				//Si le couple ([i,j],[i+1, j+1]) est meilleur que le couple ([i,i+1],[j,j+1]) que nous avons actuellement
				if(c+d < a+b) {
					ArrayList<Point> solution = new ArrayList<>();
					for(int k=0;k<=i;k++) solution.add(points.get(k));
					for(int k=j;k>i;k--) solution.add(points.get(k));
					for(int k=j+1;k<size;k++) solution.add(points.get(k));
					return solution;
				}
			}
		return points;
	}
	
	public static ArrayList<Point> opt2v2(ArrayList<Point> points) {
		ArrayList<Point> solution = new ArrayList<>(points);
		int size = solution.size();
		for(int i = 0; i<size; i++)
			for(int j = i+2; j<size; j++) {
				// On considère les deux segments [i, i+1], [j, j+1]
				// On regarde les distances des couples segment ([i,i+1],[j,j+1]) et ([i,j],[i+1, j+1])
				double a = solution.get(i%size).distance(solution.get((i+1)%size));
				double b = solution.get(j%size).distance(solution.get((j+1)%size));
				double c = solution.get(i%size).distance(solution.get(j%size));
				double d = solution.get((i+1)%size).distance(solution.get((j+1)%size));
				
				//Si le couple ([i,j],[i+1, j+1]) est meilleur que le couple ([i,i+1],[j,j+1]) que nous avons actuellement
				if(c+d < a+b) {
					ArrayList<Point> new_solution = new ArrayList<>();
					for(int k=0;k<=i;k++) new_solution.add(solution.get(k));
					for(int k=j;k>i;k--) new_solution.add(solution.get(k));
					for(int k=j+1;k<size;k++) new_solution.add(solution.get(k));
					solution = new_solution;
				}
			}
		return solution;
	}

}
