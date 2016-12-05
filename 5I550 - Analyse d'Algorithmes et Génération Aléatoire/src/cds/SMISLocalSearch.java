package cds;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collection;

import algorithms.Tools;

public class SMISLocalSearch implements ICDS {

	@Override
	public Collection<Point> process(Collection<Point> set, int edgeThreshold) {
		ArrayList<Point> result = new SMIS().process(set, edgeThreshold);
		return Tools.localSearch(set, result, edgeThreshold, 2);
	}

	
}
