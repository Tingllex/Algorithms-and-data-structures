public class Algorytm {
    public static void KMP(String tekst, String wzorzec, int[] pozycje) {
        int q = 0, p = 0, x = 0;
        int[] prefixy = new int[wzorzec.length()];
        prefix(wzorzec, prefixy);

        while(tekst.length() > q) {
            if(tekst.charAt(q) == wzorzec.charAt(p) || tekst.charAt(q) == '?') {
                q++; p++;
            }
            if(p == wzorzec.length()) {
                pozycje[x] = q - p + 1;
                x++;
                p = prefixy[p-1];
            }
            else if(q < tekst.length() && tekst.charAt(q) != wzorzec.charAt(p) && tekst.charAt(q) != '?') {
                if(p != 0)
                    p = prefixy[p-1];
                else
                    q++;
            }
        }
        for(int i = 0; i < x; i++) {
            System.out.println("wzorzec wystepuje w tekscie na pozycji: " + pozycje[i]);
        }
    }

    public static void prefix(String wzorzec, int[] pi){
        pi[0] = 0;
        int length = 0;
        for(int q = 1; q < wzorzec.length(); q++) {
            while(length >= 0 && wzorzec.charAt(length) != wzorzec.charAt(q))
            {
                if(length - 1 >= 0){
                    length = pi[length - 1];
                }
                else {
                    length--;
                }
            }
            length++;
            pi[q] = length;
        }
    }
}
