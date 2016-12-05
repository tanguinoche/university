package cds;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collection;

public interface ICDS {
	
	public Collection<Point> process(Collection<Point> set, int edgeThreshold);

}
