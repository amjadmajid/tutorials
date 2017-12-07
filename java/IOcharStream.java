import java.io.*;
    public class RWChar {
    
        public static void main(String[] args) throws IOException  {
    		
    		FileReader reader = null;
    		FileWriter out = null;
    		try {
    			reader = new FileReader("text.txt");
    			out =  new FileWriter("newText.txt") ;
    			
    			int c;
    			while((c = reader.read()) != -1){
    				
    			out.write(c);
    			}
    			
    		} finally {
    			if(reader !=null)
    				reader.close();
    			if(out !=null)
    				out.close();
    		}
    	}
    }                   
       