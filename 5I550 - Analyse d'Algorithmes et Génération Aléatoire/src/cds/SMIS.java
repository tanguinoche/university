package cds;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashSet;

import algorithms.Tools;

public class SMIS implements ICDS{

	@Override
	public ArrayList<Point> process(Collection<Point> points, int edgeThreshold) {

		ArrayList<Point> set = new ArrayList<>(points);
		ArrayList<Point> black = new ArrayList<>(new mis.MIS2hopsActiveSelection().process(set, edgeThreshold));
		ArrayList<Point> grey = new ArrayList<>(set); grey.removeAll(black);
		ArrayList<Point> blue = new ArrayList<>();

		ArrayList<ArrayList<Point>> forests = new ArrayList<>();
		for(Point p : black) {
			ArrayList<Point> forest = new ArrayList<>();
			forest.add(p);
			forests.add(forest);
		}

		for(int i = 5; i > 1; i--) {
			while(true)
			{
				Point candidate = findCandidate(i, grey, forests, set, edgeThreshold);
				if(candidate==null) break;
				blue.add(candidate);
				grey.remove(candidate);
			}
		}
		//System.out.println("black : "+black.size());
		//System.out.println("grey : "+grey.size());
		//System.out.println("blue : "+blue.size());
		blue.addAll(black);
		return blue;
	}

	private static Point findCandidate(int i, ArrayList<Point> grey, ArrayList<ArrayList<Point>> forests, ArrayList<Point> set, int edgeThreshold) {

		for(Point candidate : grey) {
			ArrayList<Point> neighbors = new ArrayList<>(Tools.neighbors(candidate, set, edgeThreshold));
			if(neighbors.size() >= i) {
				int[] indexes = getComponentsIndex(neighbors, forests);
				Arrays.sort(indexes);
				if(indexes.length >= i) {
					union(forests, indexes);
					forests.get(indexes[0]).add(candidate);
					//System.out.println("indexes : "+indexes.length);
					//System.out.println("nombre de forets : "+forests.size());
					return candidate;
				}
			}
		}
		return null;
	}



	private static void union(ArrayList<ArrayList<Point>> forests, int[] indexes) {
		for(int i = indexes.length-1 ; i > 0 ; i--)
			forests.get(indexes[0]).addAll(forests.remove(indexes[i]));
	}



	private static int[] getComponentsIndex(ArrayList<Point> neighbors, ArrayList<ArrayList<Point>> forests) {
		HashSet<Integer> components = new HashSet<>();
		for(int i = 0; i < forests.size() ; i ++) {
			for( int j = 0 ; j < neighbors.size() ; j++) {
				Point p = neighbors.get(j);
				if(forests.get(i).contains(p)){
					neighbors.remove(p);
					components.add(new Integer(i));
				}
			}
		}

		int[] tab = new int[components.size()];
		int i = 0;
		for(Integer k : components) {
			tab[i] = k.intValue();
			i++;
		}
		return tab;
	}

}
