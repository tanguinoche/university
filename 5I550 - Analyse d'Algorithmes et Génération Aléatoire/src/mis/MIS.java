package mis;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Random;

import algorithms.Tools;

public class MIS {
	
	public static ArrayList<Point> process(ArrayList<Point> set, int edgeThreshold) {
		Random rd = new Random(2016);
		
		ArrayList<Point> dominators = new ArrayList<>();
		ArrayList<Point> dominatees = new ArrayList<>(set);
		
		while(!dominatees.isEmpty()) {
			Point theChosenOne = dominatees.get(rd.nextInt(dominatees.size()));
			Collection<Point> neighbors = Tools.neighbors(theChosenOne, dominatees, edgeThreshold);
			dominatees.remove(theChosenOne); dominatees.removeAll(neighbors);
			dominators.add(theChosenOne);
		}
		
		return dominators;
	}

}
