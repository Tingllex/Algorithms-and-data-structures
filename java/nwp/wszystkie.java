import java.util.*;

public class wszystkie {
    public static Set<String> NWP(String a, String b, int[][] tab)
    {
        dlugosc.len(a, b, tab);
        List<String> nwp = podciagi.NWP(a, b, a.length(), b.length(), tab);
        return new HashSet<>(nwp);
    }
}
