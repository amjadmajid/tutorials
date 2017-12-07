import java.io.*;
public class RWChar {

        public static void main(String[] args) throws IOException  {
            
    		BufferedReader reader = null;
    		PrintWriter out = null;
    		try {
    			reader =  new BufferedReader (new FileReader("text.txt"));
    			out =  new PrintWriter ( new BufferedWriter(new FileWriter("newText.txt")));
    			
    			String str;
    			while((str = reader.readLine()) != null){
    				
    			out.println(str);
    			}
    			
    		} finally {
    			if(reader !=null)
    				reader.close();
    			if(out !=null)
    				out.close();
    		}
    	}
}