import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        FileReader fr = null;
        try{
            fr = new FileReader("dane.txt");
        }
        catch (FileNotFoundException e)
        {
            System.out.println("Nie znaleziono takiego pliku.");
        }
        BufferedReader br = new BufferedReader(fr);
        String z, dane = "";
        while((z = br.readLine()) != null)
        {
            dane += z;
        }
        fr.close();
        Huffman.DrzewoHuffmana(dane);
    }
}
