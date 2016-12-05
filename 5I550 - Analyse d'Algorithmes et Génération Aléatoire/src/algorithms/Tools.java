package algorithms;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Tools {

	static private int max = 0;
	static private ArrayList<Point> explored = new ArrayList<>();

	public static <T extends Collection<K>, K extends Point> Collection<K> neighbors(K p, T points, int edgeThreshold) {
		List<K> res = new ArrayList<>();
		points.stream().filter(p2 -> p.distance(p2) < edgeThreshold && !p.equals(p2)).forEach(res::add);
		return res;
	}

	public static <T extends Collection<K>, K extends Point> int nbNeighbors(K p, T points, int edgeThreshold) {
		return Tools.neighbors(p, points, edgeThreshold).size();
	}
	
	public static <T extends Collection<K>, K extends Point> K maxNeighbors(T points, int edgeThreshold) {
		return points.stream().max(new Comparator<K>() {
			@Override public int compare(K p1, K p2) {
				return nbNeighbors(p1, points, edgeThreshold) - nbNeighbors(p2, points, edgeThreshold);
			}
		}).get();
	}
	
	//Le point dans le set qui a le plus de voisins dans le cloud
	public static <T extends Collection<K>, K extends Point> K maxNeighbors(T set, T cloud, int edgeThreshold) {
		return set.stream().max(new Comparator<K>() {
			@Override public int compare(K p1, K p2) {
				return nbNeighbors(p1, cloud, edgeThreshold) - nbNeighbors(p2, cloud, edgeThreshold);
			}
		}).get();
	}
	
	static <T extends Collection<K>, K extends Point> Collection<K> glouton(T points, int edgeThreshold) {
		List<K> pointsCp = new ArrayList<>(points);
		Collection<K> solution = new ArrayList<>();
		while (!checkValid(points, solution, edgeThreshold)) {
			int[] nb = new int[pointsCp.size()];
			for (int i = 0; i < pointsCp.size(); i++)
				nb[i] = neighbors(pointsCp.get(i), pointsCp, edgeThreshold).size();
			int index = get_max(nb);
			K p = pointsCp.get(index);
			Collection<K> neighbors = neighbors(p, pointsCp, edgeThreshold);
			solution.add(p);
			pointsCp.removeAll(neighbors);
			pointsCp.remove(p);
		}
		//System.out.println("Sol " + solution.size());
		return localSearch(points, solution, edgeThreshold, 1);
		//return solution;
	}

	public static <T extends Collection<K>, K extends Point> Collection<K> localSearch(T points, T sol, int edgeThreshold, int type){
		List<K> solCp = new ArrayList<>(sol);
		//System.out.println();
		while(true){
			//Collections.shuffle(pointsCp);
			Collections.shuffle(solCp);
			List<K> next = optimisation(points, solCp, edgeThreshold, type);
			if(next != null){
				solCp.add(next.get(0));
				solCp.remove(next.get(1));
				solCp.remove(next.get(2));
			}
			else break;
		}
		max = 0;
		return solCp;
	}

	private static <T extends Collection<K>, K extends Point> List<K> optimisation(T points, List<K> solCp, int thresh, int type){
		int seuil = (2 * thresh) * (2 * thresh);
		Collection<K> solutionCp = new ArrayList<>(solCp);
		Collection<K> diff = new ArrayList<>(points);
		diff.removeAll(solCp);
		for(int i = 0; i < solCp.size(); i++){
			if (i > max) {
				max = i;
				//System.out.println("Local search: " + (max * 100) / solCp.size() + "%");
			}
			K p = solCp.get(i);
			for(int j = i + 1; j < solCp.size(); j++){
				K q = solCp.get(j);
				if(p.distance(q) <= seuil){
					for(K n : diff){
						if (p.distanceSq(n) <= seuil && q.distanceSq(n) <= seuil) {
							solutionCp.remove(q);
							solutionCp.remove(p);
							solutionCp.add(n);
							if ((type == 1 && checkValid(points, solutionCp, thresh)) ||
									(type == 2 && checkConnexe(points, solutionCp, thresh))) {
								List<K> pt = new ArrayList<>();
								pt.add(n);
								pt.add(p);
								pt.add(q);
								return pt;
							}
							solutionCp.add(p);
							solutionCp.add(q);
							solutionCp.remove(n);
						}
					}
				}
			}
		}
		return null;
	}

	private static <T extends Collection<K>, K extends Point> boolean checkValid(T points, T sol, int edgeThreshold){
		List<K> cpy = new ArrayList<>(points);
		for(K p : sol){
			Collection<K> neighbors = neighbors(p, points, edgeThreshold);
			for(K q : neighbors){
				if(sol.contains(q)) return false;
			}
		}
		for(K p : sol){
			Collection<K> neighbors = neighbors(p, points, edgeThreshold);
			cpy.removeAll(neighbors);
			cpy.remove(p);
		}
		return cpy.size() == 0;
	}

	public static <T extends Collection<K>, K extends Point> boolean checkConnexe(T points, T sol, int edgeThreshold){
		explored.clear();
		explore(points, sol, sol.iterator().next(), edgeThreshold);
		for(K p : sol) if(!explored.contains(p)) return false;
		explored.clear();

		List<K> cpy = new ArrayList<>(points);
		for(K p : sol){
			Collection<K> neighbors = neighbors(p, points, edgeThreshold);
			cpy.removeAll(neighbors);
			cpy.remove(p);
		}
		return cpy.size() == 0;
	}

	private static <T extends Collection<K>, K extends Point> void explore(T points, T sol, K p, int edgeThreshold){
		explored.add(p);
		Collection<K> neigh = neighbors(p, points, edgeThreshold);
		neigh.stream()
		.filter(q -> sol.contains(q) && !explored.contains(q))
		.forEach(q -> explore(points, sol, q, edgeThreshold));
	}

	private static int get_max(int[] tab){
		int max = 0;
		int index = -1;
		for(int i = 0; i < tab.length; i++){
			if(tab[i] >= max){
				max = tab[i];
				index = i;
			}
		}
		return index;
	}
	
	public <T extends Collection<K>, K extends Point> List<K> improve(T set, T hitpoints, int edgeThreshold) {
		List<K> hitpointsOpti = new ArrayList<>(hitpoints);
		for(K p : hitpoints) {
			hitpointsOpti.remove(p);
			if(Tools.checkConnexe(set, hitpointsOpti, edgeThreshold))
				continue;
			else hitpointsOpti.add(p);
		}
		return hitpointsOpti;
	}
}