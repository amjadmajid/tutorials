    import java.io.*;
        public class RWChar {
        
            public static void main(String[] args) throws IOException {
        
        		FileInputStream reader = null;
        		FileOutputStream out = null;
        		try {
        			reader = new FileInputStream("text.txt");
        			out = new FileOutputStream("newText.txt");
        
        			int c;
        			while ((c = reader.read()) != -1) {
        
        				out.write(c);
        			}
        
        		} finally {
        			if (reader != null)
        				reader.close();
        			if (out != null)
        				out.close();
        		}
        	}
        }  