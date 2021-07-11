import java.util.*;
class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Podaj pierwszy ciag:\n");
        String S1 = sc.nextLine();
        System.out.print("Podaj drugi ciag:\n");
        String S2 = sc.nextLine();

        int[][] tab = new int[S1.length()+1][S2.length()+1];
        Set<String> nwp = wszystkie.NWP(S1, S2, tab);
        System.out.println(nwp);
    }
}