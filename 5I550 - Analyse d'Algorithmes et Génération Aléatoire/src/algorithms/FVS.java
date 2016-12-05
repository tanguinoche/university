package algorithms;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Random;

public class FVS {

    private HashSet<Point> coupables;
    private int[] nbVoisins;
    int max = 0;

    public FVS(ArrayList<Point> ensemble, int threshold){
        coupables = new HashSet<>();
        nbVoisins = new int[ensemble.size()];
        ensemble.forEach(p -> nbVoisins[ensemble.indexOf(p)] = neighbor(ensemble, p, threshold).size());
    }

    public ArrayList<Point> glouton(ArrayList<Point> ensemble, int threshold){
        System.out.println("Start glouton");
        ArrayList<Point> solution = add_alone(ensemble, threshold);
        coupables.addAll(solution);
        ArrayList<Point> ensemble_red = remove_all(ensemble, solution, threshold);
        while(!check_valid(ensemble, solution, threshold)){
            int[] nb = new int[ensemble_red.size()];
            for(int i = 0; i < ensemble_red.size(); i++) nb[i] = neighbor(ensemble_red, ensemble_red.get(i), threshold).size();
            int index = get_max(nb);
            solution.add(ensemble_red.get(index));
            ensemble_red = remove_all(ensemble_red, solution, threshold);
        }
        return filter(ensemble, solution, threshold);
    }

    public ArrayList<Point> gloutonV2(ArrayList<Point> ensemble, int threshold){
        ArrayList<Point> solution = add_alone(ensemble, threshold);
        ArrayList<Point> ensemble_red = remove_all(ensemble, solution, threshold);
        while(!check_valid(ensemble, solution, threshold)){
            int[] nb = new int[ensemble_red.size()];
            for(int i = 0; i < ensemble_red.size(); i++) nb[i] = neighbor(ensemble_red, ensemble_red.get(i), threshold).size();
            int next = get_max(nb);
            while(true) {
                ArrayList<Point> nbList = neighbor(ensemble_red, ensemble_red.get(next), threshold);
                ArrayList<Point> candidates = new ArrayList<>();
                for (Point p : nbList) {
                    candidates.addAll(neighbor(ensemble_red, p, threshold));
                }
                candidates.removeAll(nbList);
                candidates.remove(ensemble_red.get(next));
                if(candidates.size() == 0) break;
                int[] tmp = new int[candidates.size()];
                for (int i = 0; i < candidates.size(); i++)
                    nb[i] = neighbor(ensemble, candidates.get(i), threshold).size();
                solution.add(ensemble_red.get(next));
                ensemble_red = remove_all(ensemble, solution, threshold);
                next = ensemble_red.indexOf(candidates.get(get_max(tmp)));
            }
        }
        return filter(ensemble,solution, threshold);
    }

    public ArrayList<Point> localSearch(ArrayList<Point> ensemble, ArrayList<Point> solution, int threshold, int type) {
        ArrayList<Point> new_sol = new ArrayList<>(solution);
        ArrayList<Point> diff = new ArrayList<>(ensemble);
        diff.removeAll(new_sol);
        while(true){
            if(type == 3){
                Collections.shuffle(new_sol);
                Collections.shuffle(ensemble);
            }
            ArrayList<Point> next = opt(ensemble, diff, new_sol, threshold, 2);
            if(next != null){
                new_sol.add(next.get(0));
                new_sol.remove(next.get(1));
                new_sol.remove(next.get(2));
                //if(type == 3) new_sol.remove(next.get(3));
                //System.out.println("Opt found(" +  nb_opt + ") size: " + new_sol.size() );
                diff.removeAll(new_sol);
            }
            else{
                break;
            }
        }
        max = 0;
        return new_sol;
    }

    private ArrayList<Point> opt(ArrayList<Point> ensemble, ArrayList<Point> diff, ArrayList<Point> solution, int thresh, int type) {
        int seuil = (3 * thresh) * (3 * thresh);
        ArrayList<Point> solution_cp = new ArrayList<>(solution);
        for (int i = 0; i < solution.size(); i++) {
            Point p = solution.get(i);
            if (i > max) {
                max = i;
                System.out.println("Local search: " + (max * 100) / solution.size() + "%");
            }
            if (coupables.contains(p)) continue;
            for (int j = i + 1; j < solution.size(); j++) {
                Point q = solution.get(j);
                if (coupables.contains(q)) continue;
                if (p.distanceSq(q) <= seuil) {
                    if (type == 2) {
                        for (Point n : diff) {
                            if (p.distanceSq(n) < seuil && q.distanceSq(n) <= seuil) {
                                solution_cp.remove(q);
                                solution_cp.remove(p);
                                solution_cp.add(n);
                                if (check_valid(ensemble, solution_cp, thresh)) {
                                    ArrayList<Point> pt = new ArrayList<>();
                                    pt.add(n);
                                    pt.add(p);
                                    pt.add(q);
                                    return pt;
                                }
                                solution_cp.add(p);
                                solution_cp.add(q);
                                solution_cp.remove(n);
                            }
                        }
                    } else {
                        for(int k = j + 1; k < solution.size(); k++) {
                            Point r = solution.get(k);
                            if (coupables.contains(r)) continue;
                            if (r.distanceSq(q) <= seuil && r.distanceSq(p) <= seuil) {
                                for (Point n : diff) {
                                    if (p.distanceSq(n) < seuil && q.distanceSq(n) <= seuil &&
                                            r.distanceSq(n) <= seuil) {
                                        solution_cp.remove(r);
                                        solution_cp.remove(q);
                                        solution_cp.remove(p);
                                        solution_cp.add(n);
                                    }
                                    if (check_valid(ensemble, solution_cp, thresh)) {
                                        ArrayList<Point> pt = new ArrayList<>();
                                        pt.add(n);
                                        pt.add(p);
                                        pt.add(q);
                                        pt.add(r);
                                        return pt;
                                    }
                                    solution_cp.remove(n);
                                    solution_cp.add(p);
                                    solution_cp.add(q);
                                    solution_cp.add(r);
                                }
                            }
                        }
                    }
                }
            }
        }
        return null;
    }

    public ArrayList<Point> alg_subgraph(ArrayList<Point> ensemble, int threshold, double epsilon){
        ArrayList<Point> result = new ArrayList<>();
        ArrayList<Point> rest = new ArrayList<>(ensemble);
        ArrayList<ArrayList<Point>> ss = new ArrayList<>();
        double rho = 1 + epsilon;
        while(rest.size() > 0){
            System.out.println("Remaining: " + rest.size());
            int[] nb = new int[rest.size()];
            for(int i = 0; i < rest.size(); i++) nb[i] = neighbor(rest, rest.get(i), threshold).size();
            Point p = rest.get(get_max(nb));
            ArrayList<ArrayList<Point>> si = get_si(rest, p, threshold, rho);
            rest.removeAll(si.get(0));
            ss.add(si.get(1));
        }
        ss.forEach(result::addAll);
        ArrayList<Point> res = filter(ensemble, new ArrayList<>(new HashSet<>(result)), threshold);
        return res;
    }

    private ArrayList<ArrayList<Point>> get_si(ArrayList<Point> set, Point p, int threshold, double rho){
        int r = 0;
        ArrayList<ArrayList<Point>> res = new ArrayList<>();
        ArrayList<Point> nr = get_neighborhood(set, p, threshold, r);
        ArrayList<Point> nr1 = get_neighborhood(set, p, threshold, r + 1);
        //ArrayList<Point> nr2 = get_neighborhood(set, p, threshold, r + 2);
        ArrayList<Point> dnr = dom_set(nr, threshold);
        ArrayList<Point> dnr1 = dom_set(nr1, threshold);
        //ArrayList<Point> dnr2 = dom_set(nr2, threshold);
        while(dnr1.size() > dnr.size() * rho){
            r++;
            nr = nr1;
            //nr1 = nr2;
            nr1 = get_neighborhood(set, p, threshold, r + 1);
            //nr2 = get_neighborhood(set, p, threshold, r + 2);
            dnr = dnr1;
            //dnr1 = dnr2;
            dnr1 = dom_set(nr1, threshold);
            //dnr2 = dom_set(nr2, threshold);
        }
        res.add(nr1);
        res.add(dnr1);
        if(r > 0)System.out.println("R = " + r);
        return res;
    }

    public ArrayList<Point> get_random_sol(ArrayList<Point> ensemble, int thresh){
        ArrayList<Point> res = new ArrayList<>();
        ArrayList<Point> ens_red = new ArrayList<>(ensemble);
        Random ran = new Random();
        while(!check_valid(ensemble, res, thresh)){
            int[] nb = new int[ens_red.size()];
            for(int i = 0; i < ens_red.size(); i++) nb[i] = neighbor(ensemble, ens_red.get(i), thresh).size();
            while(true){
                int ch = ran.nextInt(100);
                int max = get_max(nb);
                if(ch <= 30 + (0.5 * nb[max])){
                    res.add(ens_red.get(max));
                    break;
                }
                nb[max] = 0;
            }
            ens_red.removeAll(res);
        }
        System.out.println("Random gen done");
        return localSearch(ensemble, filter(ensemble, res, thresh), thresh, 3);
    }

    public ArrayList<Point> get_neighborhood(ArrayList<Point> set, Point p, int threshold, int n){
        ArrayList<Point> neighborhood = new ArrayList<>();
        neighborhood(neighborhood, new ArrayList<>(set), p, n, threshold);
        return neighborhood;
    }

    private void neighborhood(ArrayList<Point> nbhd, ArrayList<Point> g, Point v, int r, int thresh){
        g.remove(v);
        if(!nbhd.contains(v)){
            nbhd.add(v);
        }
        if(r == 0) return;
        ArrayList<Point> neibhbors = neighbor(g, v, thresh);
        g.removeAll(neibhbors);
        for(Point neighbor : neibhbors){
            neighborhood(nbhd, g, neighbor, r-1, thresh);
        }
    }

    private ArrayList<Point> dom_set(ArrayList<Point> list, int thresh) {
        ArrayList<Point> res = null;
        int i = 1;
        int an;
        while (res == null) {
            Point[] r = new Point[i];
            an = combinations2(list, i, 0, r, thresh);
            if (an == 1) {
                res = new ArrayList<>(Arrays.asList(r));
            }
            i++;
        }
        return res;
    }

    private int combinations2(ArrayList<Point> arr, int len, int startPosition, Point[] result, int thresh){
        if (len == 0){
            if(check_valid2(arr, result, thresh)) return 1;
            return 0;
        }
        for (int i = startPosition; i <= arr.size()-len; i++){
            result[result.length - len] = arr.get(i);
            if(combinations2(arr, len-1, i+1, result, thresh) == 1) return 1;
        }
        return 0;
    }


    public ArrayList<Point> add_alone(ArrayList<Point> ensemble, int threshold){
        ArrayList<Point> solution = new ArrayList<>();
        ensemble.stream().filter(p -> neighbor(ensemble, p, threshold).size() == 0).forEach(solution::add);
        System.out.println("Point sans voisins: " + solution.size());
        return solution;
    }

    public ArrayList<Point> filter(ArrayList<Point> ensemble, ArrayList<Point> solution, int threshold) {
        ArrayList<Point> new_sol = new ArrayList<>(solution);
        for (Point p : solution) {
            new_sol.remove(p);
            if (!check_valid(ensemble, new_sol, threshold)) new_sol.add(p);
        }
        return new_sol;
    }

    public boolean check_valid(ArrayList<Point> ensemble, ArrayList<Point> solution, int threshold){
        ArrayList<Point> rest = new ArrayList<>(ensemble);
        for(Point p : solution){
            ArrayList<Point> neighbor = neighbor(ensemble, p, threshold);
            rest.removeAll(neighbor);
            rest.remove(p);
        }
        return rest.isEmpty();
    }

    public boolean check_valid2(ArrayList<Point> ensemble, Point[] solution, int threshold){
        ArrayList<Point> rest = new ArrayList<>(ensemble);
        for(Point p : solution){
            ArrayList<Point> neighbor = neighbor(ensemble, p, threshold);
            rest.removeAll(neighbor);
            rest.remove(p);
        }
        return rest.isEmpty();
    }

    private ArrayList<Point> neighbor(ArrayList<Point> ensemble, Point pt, int threshold){
        ArrayList<Point> result = new ArrayList<>();
        ensemble.stream().filter(p -> p.distance(pt) <= threshold && !p.equals(pt)).forEach(result::add);
        //for (Point point:vertices) if (point.distance(p)<edgeThreshold && !point.equals(p)) result.add((Point)point.clone());
        return result;
    }

    private ArrayList<Point> remove_all(ArrayList<Point> ensemble, ArrayList<Point> solution, int threshold){
        ArrayList<Point> res = new ArrayList<>(ensemble);
        for(Point p : solution) {
            ArrayList<Point> nei = neighbor(ensemble, p, threshold);
            res.removeAll(nei);
            res.remove(p);
        }
        return res;
    }

    private int get_max(int[] tab){
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
}
