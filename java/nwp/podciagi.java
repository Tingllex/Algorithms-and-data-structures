import java.util.*;

public class podciagi {
    public static List<String> NWP(String a, String b, int x, int y, int[][] tab)
    {
        if(x == 0 || y == 0)
        {
            //return pusty ciag
            return new ArrayList<>(Collections.nCopies(1, ""));
        }
        if(a.charAt(x - 1) == b.charAt(y - 1)) {
            List<String> nwp = NWP(a, b, x - 1, y - 1, tab);
            for (int i = 0; i < nwp.size(); i++) {
                nwp.set(i, nwp.get(i) + (a.charAt(x - 1)));
            }
            return nwp;
        }
        if(tab[x - 1][y] < tab[x][y - 1])
        {
            return NWP(a,b,x,y - 1,tab);
        }
        if(tab[x][y - 1] < tab[x - 1][y])
        {
            return NWP(a,b,x - 1, y, tab);
        }
        List<String> lewo = NWP(a,b, x,y - 1, tab);
        List<String> gora = NWP(a,b,x - 1, y, tab);
        lewo.addAll(gora);
        return lewo;
    }
}
