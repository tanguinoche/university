package test;

import java.awt.Point;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;

import algorithms.DefaultTeam;
import algorithms.Tools;

public class TestBed {
	int nbTests = 10;
	int threshold = 80;
	RC3G generator;

	public TestBed() {
		generator = new RC3G();
	}

	public TestBed(int nbTests) {
		this.nbTests = nbTests;
		generator = new RC3G();
	}

	public TestBed(int nbTests, int nbPoints, int graphwidth, int graphheight, int threshold) {
		this.nbTests = nbTests;
		this.threshold = threshold;
		generator = new RC3G(nbPoints, graphwidth, graphheight, threshold);
	}

	public void genTestBeds(String prefix) {
		// On cr�e nb Tests dans le folder PREFIXtest/inputNUMTEST.points
		for(int i = 0; i<nbTests; i++) {
			String file = prefix+"test" + File.separator + "input" + i + ".points"; 
			ArrayList<Point> points = generator.generate();
			printGraphToFile(file, points);
		}
	}

	public void runTestBeds(String prefix) {
		// On rangera dans le fichier PREFIXresult/PREFIX.total l'ensemble des r�sultats
		FileWriter fw;
		BufferedWriter bw = null;
		try {
			fw = new FileWriter(prefix+"result" + File.separator + prefix + ".total", true);
			bw = new BufferedWriter(fw);
			bw.write("nbPoints,score,valid,time,fichier");
			bw.newLine();
		} catch (IOException e1) {
			e1.printStackTrace();
		}

		// On ouvre PREFIXtest/ et pour chaque fichier test dedans :
		final File testfolder = new File(prefix+"test");
		for(final File testfile : testfolder.listFiles()) {
			ArrayList<Point> points = readFromFile(testfile);
			Stopwatch watch = new Stopwatch();
			ArrayList<Point> result = new DefaultTeam().calculConnectedDominatingSet(points, threshold); //On fait le run
			double time = watch.elapsedTime();
			//On met le r�sultat dans PREFIXresult/PREFIXFICHIERTEST.result
			System.err.println("test completed : "+testfile.getAbsolutePath());
			String resultFilename = prefix+"result" + File.separator + prefix + testfile.getName().split("\\.(?=[^\\.]+$)")[0] + ".result";
			printResultToFile(resultFilename, points, result, time);
			//On met aussi le r�sultat � la fin de PREFIXresult/PREFIX.total
			try {
				bw.write(points.size() + "," + result.size() + "," + Tools.checkConnexe(points, result, threshold) + "," + time + "," + resultFilename);
				bw.newLine();
				bw.flush();
			} catch (Exception e) {
				e.printStackTrace();
			} 
		}
		if (bw != null) {
			try {
				bw.close();
			} catch (IOException e) {
				// just ignore it
			}
		}
	}


	private void printResultToFile(String filename, ArrayList<Point> points, ArrayList<Point> result, double time){
		try {
			PrintStream output = new PrintStream(new FileOutputStream(filename));
			output.println(points.size() + "," + result.size() + "," + Tools.checkConnexe(points, result, threshold) + "," + time);
			output.close();
			System.err.println("wrote result : " + filename);
		} catch (FileNotFoundException e) {
			System.err.println("I/O exception: unable to create "+filename);
		}
	}

	private void printGraphToFile(String filename, ArrayList<Point> points){
		try {
			PrintStream output = new PrintStream(new FileOutputStream(filename));
			for (Point p:points) output.println(Integer.toString((int)p.getX())+" "+Integer.toString((int)p.getY()));
			output.close();
			System.err.println("wrote test : " + filename);
		} catch (FileNotFoundException e) {
			System.err.println("I/O exception: unable to create "+filename);
		}
	}

	private ArrayList<Point> readFromFile(File file) {
		String line;
		String[] coordinates;
		ArrayList<Point> points=new ArrayList<Point>();
		try {
			BufferedReader input = new BufferedReader(
					new InputStreamReader(new FileInputStream(file))
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
					System.err.println("I/O exception: unable to close "+file.getName());
				}
			}
		} catch (FileNotFoundException e) {
			System.err.println("Input file not found.");
		}
		return points;
	}

	public static void main(String[] args) {

		for(int i = 100; i <= 1000; i+=100) {
			String prefix = ""+i;
			
			//final File testfolder = new File(prefix+"test"); //On cr�e un folder nbPointstest
			//testfolder.mkdir();

			final File resfolder = new File(prefix+"result"); //On cr�e un folder nbPointsresult
			resfolder.mkdir();


			TestBed tests = new TestBed(100, i, 1400, 900, 80);
			//tests.genTestBeds(prefix);
			tests.runTestBeds(prefix);
		}
		System.out.println("FINI");
		


	}
}
