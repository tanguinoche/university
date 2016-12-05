import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class Compute {

	public static void main(String[] args) {
//		FileWriter fw;
//		try {
//			fw = new FileWriter(new File("1664"));
//			fw.write("");
//			fw.close();
//
//		} catch (IOException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		
//		for(int i = 1; i<= 1664; i++) {
//			String toWrite = i+", ";
//			try {
//				Files.write(Paths.get("1664"), toWrite.getBytes(), StandardOpenOption.APPEND);
//			} catch (IOException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
//		}
		String[] files = {
//				"4-Naif-Set-Double", "8-Naif-Set-Double", "16-Naif-Set-Double", "32-Naif-Set-Double",
//				"64-Naif-Set-Double","128-Naif-Set-Double", "256-Naif-Set-Double",
//				"4-Welzl-Set-Double", "8-Welzl-Set-Double", "16-Welzl-Set-Double", "32-Welzl-Set-Double",
//				"64-Welzl-Set-Double","128-Welzl-Set-Double", "256-Welzl-Set-Double",
//				"4-Naif-List-Double", "8-Naif-List-Double", "16-Naif-List-Double", "32-Naif-List-Double",
//				"64-Naif-List-Double","128-Naif-List-Double", "256-Naif-List-Double",
//				"4-Welzl-List-Double", "8-Welzl-List-Double", "16-Welzl-List-Double", "32-Welzl-List-Double",
//				"64-Welzl-List-Double","128-Welzl-List-Double", "256-Welzl-List-Double"
				"4-MTF-Double", "8-MTF-Double", "16-MTF-Double", "32-MTF-Double",
				"64-MTF-Double","128-MTF-Double", "256-MTF-Double"		
		};
		for(String f : files) {
			File file = new File(f);
			try {
				BufferedReader br = null;
				Reader in = null;
				try {
					in = new FileReader(file);
					br = new BufferedReader(in);
					String content;
					int cptPoints=0;
					double sum = 0;
					while((content = br.readLine()) != null) {
						cptPoints++;
						String[] str = content.split(" ");
						if(str.length < 1) { 
							System.out.println("error occured, bad file syntax");
							throw new NumberFormatException();
						}
						sum += Double.parseDouble(str[0]);
					}
					String toWrite = file.getName()+" : "+(sum/cptPoints)+"\n";
					Files.write(Paths.get("Moyennes"), toWrite.getBytes(), StandardOpenOption.APPEND);
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
