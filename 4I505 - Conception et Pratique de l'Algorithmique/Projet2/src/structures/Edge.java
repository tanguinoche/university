package structures;

import java.util.ArrayList;

public class Edge implements Comparable<Edge> {
	
	private int etiquette;
	private double weight;
	Point p, q;

	public Edge(Point p, Point q) {
		this.p = p;
		this.q = q;
		this.weight = p.distanceSq(q);
	}
	
	public Edge(Point p, Point q, int etiquette) {
		this.p = p;
		this.q = q;
		this.etiquette = etiquette;
		this.weight = p.distanceSq(q);
	}
	
	public Edge(Point p, Point q, double d, int etiquette) {
		this.p = p;
		this.q = q;
		this.weight = d;
		this.etiquette = etiquette;
	}

	@Override
	public int compareTo(Edge e) {
		return (int) (this.weight-e.weight);
	}
	
	public double getDistance(){ return this.weight; }
	public int getEtiquette(){ return this.etiquette; }
	
	public void setEtiquette(int i){ this.etiquette = i; }
	public void setDistance(double d){ this.weight = d; }
	
	public String toString(){
		return "P: " + getP() + " Q: " + getQ() + " distance: " + weight + " etiquette : "+ etiquette;
	}
	
	public Point getP(){ return this.p; }
	public Point getQ(){ return this.q; }
	
	public boolean equals(Edge e){
		return (this.getP().equals(e.getP()) && this.getQ().equals(e.getQ()));
	}
	
	public static ArrayList<Edge> createEdges(ArrayList<Point> vertices) {
		ArrayList<Edge> edges = new ArrayList<>();

		for(int i = 0; i<vertices.size() ; i++) {
			for(int j=i+1; j<vertices.size(); j++)
				if(!vertices.get(i).equals(vertices.get(j)))
					edges.add(new Edge(vertices.get(i), vertices.get(j)));
		}
		return edges;
	}

	public boolean adjacentTo(Edge e2) {
		return ( (p==e2.getP() && q!=e2.getQ()) || (p!=e2.getP() && q==e2.getQ()) || (q==e2.getP() && p!=e2.getQ()) || (q!=e2.getP() && p==e2.getQ()) );
	}
	
	public Point getCommonPointTo(Edge e2) {
		if(this.adjacentTo(e2) == false) { return null; }
		if(this.p.x==e2.getP().x && this.p.y==e2.getP().y) 
			return e2.getP();
		else
			return e2.getQ();
	}
	
	public Point getUncommonPointTo(Edge e2) {
		if(this.adjacentTo(e2) == false) { return null; }
		if(this.p.x==e2.getP().x && this.p.y==e2.getP().y) 
			return e2.getQ();
		else 
			return e2.getP();
	}
	
	public int scalaire(Point a, Point b, Point c) {//c le point en commun
		return scalaire(c, a, c, b);
	}
	
	
	private int scalaire(Point a, Point b, Point c, Point d) {
		int x_ab = b.x - a.x;
		int y_ab = b.y - a.y;
		int x_cd = d.x - c.x;
		int y_cd = d.y - c.y;
		return x_ab*x_cd + y_ab*y_cd;
	}

	public double getAngleWith(Edge e2) {
		if(this.adjacentTo(e2) == false) return 0;
		
		Point A = getUncommonPointTo(e2);
		Point B = e2.getUncommonPointTo(this);
		Point C = this.getCommonPointTo(e2);
		
		double AC = A.distance(C);
		double BC = B.distance(C);
		
		int scal = scalaire(A, B, C);
		
		return Math.acos(scal / (AC * BC));
	}

	public boolean isAcuteAngledWith(Edge e2) {
		if(this.adjacentTo(e2) == false) { return false; }

		return this.getAngleWith(e2)<90;
	}
	
	public boolean isTriangleAcute(Edge e2) { 
		if(this.adjacentTo(e2) == false) return false;
		Point A = getUncommonPointTo(e2);
		Point B = e2.getUncommonPointTo(this);
		
		Edge e3 = new Edge(A, B);
		if(( isAcuteAngledWith(e2) && isAcuteAngledWith(e3) && e2.isAcuteAngledWith(e3))) {
			System.out.println("[");
			System.out.println("Edges "+this.toString()+" and "+e2.toString());
			System.out.println("P1 : "+A.toString());
			System.out.println("P2 : "+B.toString());
			System.out.println("P3 : "+this.getCommonPointTo(e2).toString());
		}

		return ( isAcuteAngledWith(e2) && isAcuteAngledWith(e3) && e2.isAcuteAngledWith(e3));
	}

	public boolean is120MaxAngledWith(Edge e2) {
		if(this.adjacentTo(e2) == false) { return false; }

		return this.getAngleWith(e2)<120;
	}
	
	public boolean isTriangleFermat(Edge e2) { 
		if(this.adjacentTo(e2) == false) return false;
		Point A = getUncommonPointTo(e2);
		Point B = e2.getUncommonPointTo(this);
		Edge e3 = new Edge(A, B);
		return ( is120MaxAngledWith(e2) && is120MaxAngledWith(e3) && e2.is120MaxAngledWith(e3));
	}
	
	public double getLengthSq() {
		return p.distanceSq(q);
	}
}
