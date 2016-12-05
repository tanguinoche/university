package welzl;
import java.awt.geom.Point2D;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class Main {

	public static void main(String[] args) {
		
		Collection<Point2D> points;
		welzl.Circle.Double minidisk;
		StopWatch watch;
		double elapsedTime;
		double naifRadius;
		double welzlRadius;
		String toWrite;
		String content;
		File path = new File("samples");
		
		int nbPointsMax = 256;
		int cptPoints = 0;
		
		//Création/Flush des fichiers
//		String[] files = {nbPointsMax+"-Naif-Set-Double", nbPointsMax+"-Welzl-Set-Double",
//				nbPointsMax+"-Assert-Set-Double" ,nbPointsMax+"-Naif-List-Double", 
//				nbPointsMax+"-Welzl-List-Double", nbPointsMax+"-Assert-List-Double",
//				nbPointsMax+"-Naif-Set-Float", nbPointsMax+"-Welzl-Set-Float",
//				nbPointsMax+"-Assert-Set-Float", nbPointsMax+"-Naif-List-Float", 
//				nbPointsMax+"-Welzl-List-Float", nbPointsMax+"-Assert-List-Float",
//				nbPointsMax+"-Naif-Set-Integer", nbPointsMax+"-Welzl-Set-Integer", 
//				nbPointsMax+"-Assert-Set-Integer", nbPointsMax+"-Naif-List-Integer", 
//				nbPointsMax+"-Welzl-List-Integer", nbPointsMax+"-Assert-List-Integer"};
		String[] files = {nbPointsMax+"-MTF-Double" };
		for(String file : files) {
			try {
				FileWriter fw = new FileWriter(new File(file));
				fw.write("");
				fw.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		
		int i = 0;
		int nbFiles = path.listFiles().length;
		for(File file : path.listFiles()) {
			i++;
			System.out.println("Fichier "+i+"/"+nbFiles+" ("+file.getName()+")");
			try {
				BufferedReader br = null;
				Reader in = null;
				try {
					/****************
					 *  SET/DOUBLE  *
					 ****************/
//					in = new FileReader(file);
//					br = new BufferedReader(in);
//					points = new HashSet<>();
//					cptPoints=0;
//					while((content = br.readLine()) != null && cptPoints != nbPointsMax) {
//						cptPoints++;
//						String[] coords = content.split(" ");
//						if(coords.length < 2) { 
//							System.out.println("error occured, bad file syntax");
//							throw new NumberFormatException();
//						}
//						points.add(new Point2D.Double(Double.parseDouble(coords[0]), Double.parseDouble(coords[1])));
//					}
//					//System.out.println("points chargés dans la HashSet ("+points.size()+"points).");
//					
//					//Résolution du problème
//					//Naive / Set / Double precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.algoNaif(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Naif-Set-Double"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Naif/Set/Double terminé.");
//					
//					naifRadius = minidisk.getRadius();
//					System.gc(); //Nettoyage mémoire
//					
//					
//					//Welzl / Set / Double precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.welzl(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Welzl-Set-Double"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Welzl/Set/Double terminé.");
//					welzlRadius = minidisk.getRadius();
//					
//					//(Naive<->Welzl) / Set / Double precision 
//					toWrite = file.getName()+" "+(java.lang.Math.abs(naifRadius-welzlRadius)<1)+" "+naifRadius+" "+welzlRadius+", ";
//					Files.write(Paths.get(nbPointsMax+"-Assert-Set-Double"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					in.close();
//					br.close();
//					points = null;
//					System.gc(); //Nettoyage mémoire
					
					
					/****************
					 *  MTF DOUBLE  *
					 ****************/
					in = new FileReader(file);
					br = new BufferedReader(in);
					points = new ArrayList<>();
					cptPoints=0;
					while((content = br.readLine()) != null && cptPoints != nbPointsMax) {
						cptPoints++;
						String[] coords = content.split(" ");
						if(coords.length < 2) { 
							System.out.println("error occured, bad file syntax");
							throw new NumberFormatException();
						}
						points.add(new Point2D.Double(Double.parseDouble(coords[0]), Double.parseDouble(coords[1])));
					}
					//System.out.println("points chargés dans la HashSet ("+points.size()+"points).");
					
					//Résolution du problème
					//Naive / Set / Double precision
					watch = new StopWatch();
					minidisk = MinimumSpanningCircle.MTFminidisk((List<Point2D>) points);
					elapsedTime = watch.elapsedTime();
					toWrite = elapsedTime+"\n";
					Files.write(Paths.get(nbPointsMax+"-MTF-Double"), toWrite.getBytes(), StandardOpenOption.APPEND);

					in.close();
					br.close();
					points = null;
					System.gc(); //Nettoyage mémoire
					
					/*****************
					 *  LIST/DOUBLE  *
					 *****************/
//					in = new FileReader(file);
//					br = new BufferedReader(in);
//					points = new ArrayList<>();
//					cptPoints=0;
//					while((content = br.readLine()) != null && cptPoints != nbPointsMax) {
//						cptPoints++;
//						String[] coords = content.split(" ");
//						if(coords.length < 2) { 
//							System.out.println("error occured, bad file syntax");
//							throw new NumberFormatException();
//						}
//						points.add(new Point2D.Double(Double.parseDouble(coords[0]), Double.parseDouble(coords[1])));
//					}
//					//System.out.println("points chargés dans l'ArrayList ("+points.size()+"points).");
//					
//					//Résolution du problème
//					//Naive / List / Double precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.algoNaif(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Naif-List-Double"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Naif/List/Double terminé.");
//					
//					naifRadius = minidisk.getRadius();
//					System.gc(); //Nettoyage mémoire
//					
//					
//					//Welzl / List / Double precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.welzl(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Welzl-List-Double"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Welzl/List/Double terminé.");
//					welzlRadius = minidisk.getRadius();
//					
//					//(Naive<->Welzl) / List / Double precision 
//					toWrite = file.getName()+" "+(java.lang.Math.abs(naifRadius-welzlRadius)<1)+" "+naifRadius+" "+welzlRadius+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Assert-List-Double"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					
//					in.close();
//					br.close();
//					points = null;
//					System.gc(); //Nettoyage mémoire
					
					
					/****************
					 *  SET/FLOAT  *
					 ****************/
//					in = new FileReader(file);
//					br = new BufferedReader(in);
//					points = new HashSet<>();
//					cptPoints=0;
//					while((content = br.readLine()) != null && cptPoints != nbPointsMax) {
//						cptPoints++;
//						String[] coords = content.split(" ");
//						if(coords.length < 2) { 
//							System.out.println("error occured, bad file syntax");
//							throw new NumberFormatException();
//						}
//						points.add(new Point2D.Float(Float.parseFloat(coords[0]), Float.parseFloat(coords[1])));
//					}
//					//System.out.println("points chargés dans la HashSet ("+points.size()+"points).");
//					
//					//Résolution du problème
//					//Naive / Set / Simple precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.algoNaif(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Naif-Set-Float"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Naif/Set/Float terminé.");
//					
//					naifRadius = minidisk.getRadius();
//					System.gc(); //Nettoyage mémoire
//					
//					
//					//Welzl / Set / Simple precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.welzl(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Welzl-Set-Float"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Welzl/Set/Float terminé.");
//					welzlRadius = minidisk.getRadius();
//					
//					//(Naive<->Welzl) / Set / Double precision 
//					toWrite = file.getName()+" "+(java.lang.Math.abs(naifRadius-welzlRadius)<1)+" "+naifRadius+" "+welzlRadius+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Assert-Set-Float"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					in.close();
//					br.close();
//					points = null;
//					System.gc(); //Nettoyage mémoire
					
					
					/*****************
					 *  LIST/FLOAT  *
					 *****************/
//					in = new FileReader(file);
//					br = new BufferedReader(in);
//					points = new ArrayList<>();
//					cptPoints=0;
//					while((content = br.readLine()) != null && cptPoints != nbPointsMax) {
//						cptPoints++;
//						String[] coords = content.split(" ");
//						if(coords.length < 2) { 
//							System.out.println("error occured, bad file syntax");
//							throw new NumberFormatException();
//						}
//						points.add(new Point2D.Float(Float.parseFloat(coords[0]), Float.parseFloat(coords[1])));
//					}
//					//System.out.println("points chargés dans l'ArrayList ("+points.size()+"points).");
//					
//					//Résolution du problème
//					//Naive / List / Double precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.algoNaif(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Naif-List-Float"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Naif/List/Float terminé.");
//					
//					naifRadius = minidisk.getRadius();
//					System.gc(); //Nettoyage mémoire
//					
//					
//					//Welzl / List / Simple precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.welzl(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Welzl-List-Float"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Welzl/List/Float terminé.");
//					welzlRadius = minidisk.getRadius();
//					
//					//(Naive<->Welzl) / List / Simple precision 
//					toWrite = file.getName()+" "+(java.lang.Math.abs(naifRadius-welzlRadius)<1)+" "+naifRadius+" "+welzlRadius+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Assert-List-Float"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					
//					in.close();
//					br.close();
//					points = null;
//					System.gc(); //Nettoyage mémoire
					
					
					/****************
					 *  SET/INTEGER  *
					 ****************/
//					in = new FileReader(file);
//					br = new BufferedReader(in);
//					points = new HashSet<>();
//					cptPoints=0;
//					while((content = br.readLine()) != null && cptPoints != nbPointsMax) {
//						cptPoints++;
//						String[] coords = content.split(" ");
//						if(coords.length < 2) { 
//							System.out.println("error occured, bad file syntax");
//							throw new NumberFormatException();
//						}
//						points.add(new Point(Integer.parseInt(coords[0]), Integer.parseInt(coords[1])));
//					}
//					//System.out.println("points chargés dans la HashSet ("+points.size()+"points).");
//					
//					//Résolution du problème
//					//Naive / Set / int precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.algoNaif(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Naif-Set-Integer"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Naif/Set/Integer terminé.");
//					
//					naifRadius = minidisk.getRadius();
//					System.gc(); //Nettoyage mémoire
//					
//					
//					//Welzl / Set / Integer precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.welzl(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Welzl-Set-Integer"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Welzl/Set/Integer terminé.");
//					welzlRadius = minidisk.getRadius();
//					
//					//(Naive<->Welzl) / Set / Integer precision 
//					toWrite = file.getName()+" "+(java.lang.Math.abs(naifRadius-welzlRadius)<1)+" "+naifRadius+" "+welzlRadius+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Assert-Set-Integer"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					in.close();
//					br.close();
//					points = null;
//					System.gc(); //Nettoyage mémoire
					
					
					/*****************
					 *  LIST/INTEGER  *
					 *****************/
//					in = new FileReader(file);
//					br = new BufferedReader(in);
//					points = new ArrayList<>();
//					cptPoints=0;
//					while((content = br.readLine()) != null && cptPoints != nbPointsMax) {
//						cptPoints++;
//						String[] coords = content.split(" ");
//						if(coords.length < 2) { 
//							System.out.println("error occured, bad file syntax");
//							throw new NumberFormatException();
//						}
//						points.add(new Point(Integer.parseInt(coords[0]), Integer.parseInt(coords[1])));
//					}
//					//System.out.println("points chargés dans l'ArrayList ("+points.size()+"points).");
//					
//					//Résolution du problème
//					//Naive / List / Integer precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.algoNaif(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Naif-List-Integer"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Naif/List/Integer terminé.");
//					
//					naifRadius = minidisk.getRadius();
//					System.gc(); //Nettoyage mémoire
//					
//					
//					//Welzl / List / Double precision
//					watch = new StopWatch();
//					minidisk = MinimumSpanningCircle.welzl(points);
//					elapsedTime = watch.elapsedTime();
//					toWrite = elapsedTime+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Welzl-List-Integer"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					//System.out.println(nbPointsMax+"-Welzl/List/Integer terminé.");
//					welzlRadius = minidisk.getRadius();
//					
//					//(Naive<->Welzl) / List / Double precision 
//					toWrite = file.getName()+" "+(java.lang.Math.abs(naifRadius-welzlRadius)<1)+" "+naifRadius+" "+welzlRadius+"\n";
//					Files.write(Paths.get(nbPointsMax+"-Assert-List-Integer"), toWrite.getBytes(), StandardOpenOption.APPEND);
//					
//					in.close();
//					br.close();
//					points = null;
//					System.gc(); //Nettoyage mémoire
					
				} catch (FileNotFoundException e) {
					System.err.println("The file XXX hasn't been found.");
					e.printStackTrace();
				} finally {
					in.close();
					if(br!=null) {
						br.close();
					}
				}
			} catch (NumberFormatException e) {
				System.err.println("The syntax of file XXX isn't well-defined.");
				e.printStackTrace();
			} catch (IOException e) {
				System.err.println("Error I/O on file XXX.");
				e.printStackTrace();
			}
		}
	}
	
}

