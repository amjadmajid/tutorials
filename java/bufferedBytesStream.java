import java.io.*;

public class RWChar {

    public static void main(String[] args) throws IOException {

		BufferedInputStream reader = null;
		BufferedOutputStream out = null;
		try {
			reader = new BufferedInputStream( new FileInputStream("text.txt"));
			out = new BufferedOutputStream( new FileOutputStream("newText.txt"));

			while ( reader.available() != 0) {
				out.write(reader.read());
			}

		} finally {
			if (reader != null)
				reader.close();
			if (out != null)
				out.close();
		}
	}
}  