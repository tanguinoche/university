package cds;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collection;

import algorithms.Tools;

public class SMISFiltreLOCALSEARCH implements ICDS {

	@Override
	public Collection<Point> process(Collection<Point> set, int edgeThreshold) {
		
		ArrayList<Point> hitpoints = new SMIS().process(set, edgeThreshold);
		ArrayList<Point> hitpointsOpti = new ArrayList<>(hitpoints);
		for(Point p : hitpoints) {
			hitpointsOpti.remove(p);
			if(Tools.checkConnexe(set, hitpointsOpti, edgeThreshold))
				continue;
			else hitpointsOpti.add(p);
		}

		
		return Tools.localSearch(set, hitpointsOpti, edgeThreshold, 2);
	}


}
