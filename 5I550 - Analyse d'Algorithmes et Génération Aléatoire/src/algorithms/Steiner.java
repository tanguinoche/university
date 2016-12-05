package algorithms;

import java.awt.Point;
import java.util.ArrayList;

/**
 * Created by tassos on 3/9/16.
 * in {$PWD}
 */
public class Steiner {
    public static ArrayList<Point> result;
    public static int[][] pathList;
    public static ArrayList<Edge> firstKrusk = null;


    public static ArrayList<Edge> calculSteiner(ArrayList<Point> points, int edgeThreshold, ArrayList<Point> hitPoints) {
        System.out.println("================ Calcul de la matrice des chemins les plus courts ================");
        int[][] paths = FloydWarshall.process(points, edgeThreshold);
        pathList = paths;
        System.out.println("Terminé");
        ArrayList<Edge> krusk = Kruskal.process(hitPoints);
        firstKrusk = krusk;
        ArrayList<Point> res = getPoints(krusk, points, paths);
        res.addAll(hitPoints);
        result = res;
        System.out.println("Taille ensemble : "+points.size() + " points speciaux : " + hitPoints.size() + " points dans path : " + res.size());
        System.out.println("================ Kruskal ================");
        ArrayList<Edge> t0 = Kruskal.process(res);
        System.out.println("Terminé size : " + t0.size());
        return t0;
    }
    static public ArrayList<Point> getPoints(ArrayList<Edge> edges, ArrayList<Point> points, int[][] pathList){
        ArrayList<Point> res = new ArrayList<>();
        for(Edge e : edges){
            int i = points.indexOf(e.getP());
            int j = points.indexOf(e.getQ());
            ArrayList<Integer> list = getListePointPath(i, j, pathList);
            for(Integer in : list) {
                if (!res.contains(points.get(in))) {
                    res.add(points.get(in));
                }
            }
        }
        return res;
    }




    public static ArrayList<Integer> getListePointPath(int i, int j, int[][] paths){
        ArrayList<Integer> res = new ArrayList<>();
        while(paths[i][j] != j){
            res.add(paths[i][j]);
            i = paths[i][j];
        }
        return res;
    }

    


    public static boolean isCommonPoints(Edge e1, Edge e2) {
        return e1.getP() == e2.getP()
                || e1.getP() == e2.getQ()
                || e1.getQ() == e2.getP()
                || e1.getQ() == e2.getQ()
            ? true : false;
    }

}
