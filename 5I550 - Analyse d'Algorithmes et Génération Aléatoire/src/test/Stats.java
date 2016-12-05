package test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

public class Stats {

	/*
	 * 
	 * Pour utiliser : Décompressez les dossiers XXXRESULT à la racine du projet !
	 */
	public static void main(String[] args) {

		//Pour chaque dossier de résultat
		for(int i = 100; i <= 1000; i+=100) {
			int scoreMoyen = 0;
			boolean allsuceed = true;
			double temps = 0.0;
			//Pour chaque fichier
			int j;
			for(j = 0; j < 100; j+=1) {
				File f = new File(i+"result"+File.separator+i+"input"+j+".result");
				//Pour chaque ligne
				String line;
				String data[];
				try {
					BufferedReader input = new BufferedReader(
							new InputStreamReader(new FileInputStream(f))
							);
					try {
						while ((line=input.readLine())!=null) {
							data=line.split(",");
							scoreMoyen += Integer.parseInt(data[1]);
							allsuceed = allsuceed && Boolean.parseBoolean(data[2]);
							temps += Double.parseDouble(data[3]);
						}
					} catch (IOException e) {
						System.err.println("Exception: interrupted I/O.");
					} finally {
						try {
							input.close();
						} catch (IOException e) {
							System.err.println("I/O exception: unable to close "+f.getName());
						}
					}
				} catch (FileNotFoundException e) {
					System.err.println("Input file not found : "+i+"result"+File.separator+i+"input"+j+".result");
				}	
					
			}
			
			System.out.println("Pour les instances de "+i+"points : ");
			System.out.println("Score moyen : "+(scoreMoyen/j));
			System.out.println("Tout a réussi : " + allsuceed);
			System.out.println("Temps total : " + (temps/j) +  "secondes = " + (temps/j/60) + "minutes = " + (temps/j/3600) + " heures");
		}
		System.out.println("FINI");
	}
}
