package algorithms;

public class UnionFind {

	private int[] id; // Each id[i] is the id of the parent of the i-th vertex. 
	private int[] size; //Size of each component
	private int nbComponents;
	
	public UnionFind(int nbVertices) {
		nbComponents = nbVertices;

		id = new int[nbVertices];
		size = new int[nbVertices];
		for(int i = 0; i < nbVertices ; i++) {
			id[i] = i;
			size[i] = 1;
		}
	}
	
	public int getNbComponents() {
		return nbComponents;
	}
	
	public boolean isConnected(int p, int q) {
		return ( find(p) == find(q) );
	}
	
	//Follow the path until root found
	public int find(int p) {
		while(p!=id[p])
			p = id[p];
		return p;
	}


	public void union(int p, int q)
	{
		int i = find(p);
		int j = find(q);
		if(i==j) return; //Already in the same component
		
		//Smaller component becomes parent of the other
		// => possibly minimise next find operation
		if(size[i] < size[j]) {
			id[i] = j;          //Update root
			size[j] += size[i]; //Update size
		} else {
			id[j] = i;
			size[i] += size[j]; 
		}
		nbComponents--;
	}
}