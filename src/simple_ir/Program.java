package simple_ir;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Program {

	public static void main(String[] args) {
		for(int i = 1; i < 100; i++)
		{
			String fileName = "Reuters\\" + i + ".html";
			System.out.println(fileName);
			FileReader reader;
			BufferedReader breader;
			try {
				reader = new FileReader(fileName);
				breader = new BufferedReader(reader); 
				String line = breader.readLine();
				String[] tokens = Tokenizer.Tokennize(line);
				System.out.println(tokens[0]);
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
