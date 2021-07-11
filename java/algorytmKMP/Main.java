public class Main {
    public static void main(String[] args) {
        String tekst  = "ac?c?acbaa?baacb";
        String wzorzec = "cb";
        int[] pozycje = new int[tekst.length()];
        Algorytm.KMP(tekst, wzorzec, pozycje);
    }
}
