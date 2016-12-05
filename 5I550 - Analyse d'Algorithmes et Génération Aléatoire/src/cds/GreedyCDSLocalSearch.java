package cds;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collection;

import algorithms.Tools;

public class GreedyCDSLocalSearch  implements ICDS {

	@Override
	public Collection<Point> process(Collection<Point> set, int edgeThreshold) {
		ArrayList<Point> hitpoints = new GreedyCDS().process(set, edgeThreshold);
		
		return Tools.localSearch(set, hitpoints, edgeThreshold, 2);
	}

}
