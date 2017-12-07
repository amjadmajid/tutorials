
import java.io.*;
public class RWChar {

    public static void main(String[] args) throws IOException  {
		
		BufferedReader reader = null;
		BufferedWriter out = null;
		try {
			reader = new BufferedReader (new FileReader("text.txt"));
			out =  new BufferedWriter (new FileWriter("newText.txt"));
			
			String str;
			while((str = reader.readLine()) != null){
				
			out.write(str+"\n");
			}
			
		} finally {
			if(reader !=null)
				reader.close();
			if(out !=null)
				out.close();
		}
	}
}