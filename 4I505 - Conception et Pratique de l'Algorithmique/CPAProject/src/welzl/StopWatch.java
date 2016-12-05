package welzl;

//Robert Sedgewick

public class StopWatch {

	private final long start;
	
	public StopWatch() {
		start = System.nanoTime();
	}
	
	//Result is milliseconds
	public double elapsedTime() {
		long now = System.nanoTime();
		return (now - start) / 1000000.0;
	}
}
