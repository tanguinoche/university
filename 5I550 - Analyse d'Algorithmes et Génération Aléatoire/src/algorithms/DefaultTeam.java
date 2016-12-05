package algorithms;

import java.awt.Point;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import cds.GreedyCDS;
import cds.GreedyCDSFiltre;
import cds.GreedyCDSLocalSearch;
import cds.ICDS;
import cds.SMIS;
import cds.SMISFiltre;

public class DefaultTeam {

	private class Job implements Callable<ArrayList<Point>> {
		private ArrayList<Point> set;
		private int edgeThreshold;
		private ICDS job;
		
		public Job(ArrayList<Point> points, int edgeThreshold, ICDS job) {
			set = new ArrayList<>(points);
			this.edgeThreshold = edgeThreshold;
			this.job = job;
		}

		@Override
		public ArrayList<Point> call() throws Exception {
			return new ArrayList<>(job.process(set, edgeThreshold));
		}
		
	}

	public ArrayList<Point> calculConnectedDominatingSet(ArrayList<Point> points, int edgeThreshold) {
		ArrayList<Point> bestScore = null;
		ExecutorService pool = Executors.newFixedThreadPool(3);
		ArrayList<Future<ArrayList<Point>>> futures = new ArrayList<Future<ArrayList<Point>>>(); 
	    Callable<ArrayList<Point>> callable;
	    callable = new Job(points, edgeThreshold, new GreedyCDSFiltre());
	    futures.add(pool.submit(callable));
	    ArrayList<Point> hitpoints;
	    bestScore = points;
		    for (Future<ArrayList<Point>> future : futures) {
		    	try {
		    		if((hitpoints = future.get()).size() < bestScore.size()) bestScore = hitpoints;
		    	} catch (Exception e) { e.printStackTrace(); }
		    }
		return bestScore;

	}


	//FILE PRINTER
	@SuppressWarnings("unused")
	private void saveToFile(String filename,ArrayList<Point> result){
		int index=0;
		try {
			while(true){
				BufferedReader input = new BufferedReader(new InputStreamReader(new FileInputStream(filename+Integer.toString(index)+".points")));
				try {
					input.close();
				} catch (IOException e) {
					System.err.println("I/O exception: unable to close "+filename+Integer.toString(index)+".points");
				}
				index++;
			}
		} catch (FileNotFoundException e) {
			printToFile(filename+Integer.toString(index)+".points",result);
		}
	}
	private void printToFile(String filename,ArrayList<Point> points){
		try {
			PrintStream output = new PrintStream(new FileOutputStream(filename));
			for (Point p:points) output.println(Integer.toString((int)p.getX())+" "+Integer.toString((int)p.getY()));
			output.close();
		} catch (FileNotFoundException e) {
			System.err.println("I/O exception: unable to create "+filename);
		}
	}

	//FILE LOADER
	@SuppressWarnings("unused")
	private ArrayList<Point> readFromFile(String filename) {
		String line;
		String[] coordinates;
		ArrayList<Point> points=new ArrayList<Point>();
		try {
			BufferedReader input = new BufferedReader(
					new InputStreamReader(new FileInputStream(filename))
					);
			try {
				while ((line=input.readLine())!=null) {
					coordinates=line.split("\\s+");
					points.add(new Point(Integer.parseInt(coordinates[0]),
							Integer.parseInt(coordinates[1])));
				}
			} catch (IOException e) {
				System.err.println("Exception: interrupted I/O.");
			} finally {
				try {
					input.close();
				} catch (IOException e) {
					System.err.println("I/O exception: unable to close "+filename);
				}
			}
		} catch (FileNotFoundException e) {
			System.err.println("Input file not found.");
		}
		return points;
	}
}
