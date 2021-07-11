import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception{
        String file = "graf.txt";
        Scanner scanner = new Scanner(new File(file));
        int N = scanner.nextInt();
        int[][] macierz = new int[N][N];
        System.out.println("\nmacierz sasiedztwa grafu:");
        System.out.println("Rozmiar: "+ N + "x" + N);
        for(int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                macierz[i][j] = scanner.nextInt();
                System.out.print(macierz[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();

        wierzcholek[] v = new wierzcholek[N];
        for(int i = 0 ; i < N ; i++){
            v[i] = new wierzcholek();
            v[i].visited = false;
            v[i].p = 0;
        }
        System.out.println("v.p:  v:");
        DFS.DFS(0,v,macierz,N);
    }
}