package algorithms;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collections;

public class Kruskal {
	
	public static ArrayList<Edge> process(ArrayList<Point> points) {
        ArrayList<Edge> candidatesEdges = candidatesEdges(points);
        Collections.sort(candidatesEdges);

        ArrayList<Edge> rslt = new ArrayList<Edge>();

        Edge voisin1 = null;
        Edge voisin2 = null;

        for (Edge current : candidatesEdges) {
            voisin1 = null;
            voisin2 = null;
            for (Edge cycleEdge : rslt) {
                if (current.getP() == cycleEdge.getP()) voisin1 = cycleEdge;
                else if (current.getP() == cycleEdge.getQ()) voisin1 = cycleEdge;
                else if (current.getQ() == cycleEdge.getQ()) voisin2 = cycleEdge;
                else if (current.getQ() == cycleEdge.getP()) voisin2 = cycleEdge;
                
                if(voisin1!=null && voisin2!=null) break;
            }

            // Si les deux voisins sont null alors on a un edge isole, donc on l'ajoute a la liste rslt
            if (voisin1 == null && voisin2 == null) {
                rslt.add(current);
            } else {
                // si il n'y a que un seul edge null, alors l'autre est un voisin de l'edge courant
                if (voisin1 == null && voisin2 != null) {
                    current.setEtiquette(voisin2.getEtiquette());
                    rslt.add(current);
                } else if (voisin2 == null && voisin1 != null) {
                    current.setEtiquette(voisin1.getEtiquette());
                    rslt.add(current);
                }
                // sinon, il y a deux edges voisins de l'edge courant
                // on change arbitrairement l'etiquette de l'edge courant avec celui d'un voisin, et on propage cette etiquette
                // sur tous les edges de l'autre voisin
                else {
                    int etiquetteVoisin1 = voisin1.getEtiquette();
                    int etiquetteVoisin2 = voisin2.getEtiquette();
                    if (etiquetteVoisin1 == etiquetteVoisin2)
                        continue;
                    else {
                        current.setEtiquette(etiquetteVoisin1);
                        rslt.add(current);
                        for (Edge other : rslt) {
                            if (other.getEtiquette() == etiquetteVoisin2) {
                                other.setEtiquette(etiquetteVoisin1);
                            }
                        }
                    }
                }
            }
            if (rslt.size() == points.size() - 1)
                break;
        }
        return rslt;
    }
	
    public static ArrayList<Edge> candidatesEdges(ArrayList<Point> points) {
        ArrayList<Edge> edges = new ArrayList<Edge>();
        int cptEtiquette = 0;

        for (int i = 0; i < points.size(); i++) {
            for (int j = i; j < points.size(); j++) {
                Point p1 = points.get(i);
                Point p2 = points.get(j);
                if (p1 != p2) {
                    edges.add(new Edge(p1, p2, cptEtiquette));
                }
            }
            cptEtiquette++;
        }

        return edges;
    }

}
