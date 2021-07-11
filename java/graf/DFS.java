public class DFS {
    public static void DFS(int i, wierzcholek[] v, int[][] macierz, int N){
        if(v[i].p == 0 && i == 0){ }
        else{
            System.out.print(" " + v[i].p + "    ");
            System.out.println(i);
        }
        v[i].visited = true;
        for(int j = 0; j < N; j++){
            if(!v[j].visited && macierz[i][j]==1){
                v[j].p = i;
                DFS(j,v,macierz,N);
            }
        }
    }
}