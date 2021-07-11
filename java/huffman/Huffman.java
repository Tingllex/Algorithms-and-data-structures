import java.util.*;
public class Huffman
{
    public static boolean lisc(Wezel korzen) {
        return korzen.lewy == null && korzen.prawy == null;
    }

    public static void kodowanie(Wezel korzen, String string, Map <Character,String> huffman)
    {
        if (korzen == null) {
            return;
        }

        if (lisc(korzen)) {
            if(string.length() > 0)
            {
                huffman.put(korzen.z, string);
            }
            else{
                huffman.put(korzen.z, "1");
            }
        }
        kodowanie(korzen.lewy, string + '0', huffman);
        kodowanie(korzen.prawy, string + '1', huffman);
    }

    public static void DrzewoHuffmana(String string)
    {
        if (string.length() == 0) {
            return;
        }
        Map<Character, Integer> czestosc = new HashMap<>();
        int[] licznik = new int[256];
        for(int i = 0; i < string.length(); i++)
        {
            licznik[string.charAt(i)]++;
        }
        char[] znak = new char[string.length()];
        for (int i = 0; i < string.length(); i++)
        {
            znak[i] = string.charAt(i);
            int czyjest = 0;
            for(int j = 0; j <= i; j++)
            {
                if (string.charAt(i)==znak[j])
                    czyjest++;
            }
            if (czyjest == 1)
            {
                //System.out.println(string.charAt(i) + " " + licznik[string.charAt(i)]);
                czestosc.put(string.charAt(i), licznik[string.charAt(i)]);
            }
        }
        PriorityQueue<Wezel> pq;
        pq = new PriorityQueue<>(Comparator.comparingInt(x -> x.czestosc));

        for (var x: czestosc.entrySet()) {
            pq.add(new Wezel(x.getKey(), x.getValue()));
        }
        while (pq.size() != 1)
        {
            Wezel lewy = pq.poll();
            Wezel prawy = pq.poll();
            int suma = lewy.czestosc + prawy.czestosc;
            pq.add(new Wezel(null, suma, lewy, prawy));
        }
        Wezel korzen = pq.peek();

        Map<Character, String> zakodowane = new HashMap<>();
        kodowanie(korzen, "", zakodowane);

        System.out.println("Tekst z pliku: " + string);

        for (char i: zakodowane.keySet()) {
            System.out.println(i + " " + licznik[i]+ " " + zakodowane.get(i));
        }
        StringBuilder sb = new StringBuilder();
        for (char c: string.toCharArray()) {
            sb.append(zakodowane.get(c));
        }
        System.out.println("Zakodowany tekst: " + sb);
    }
}