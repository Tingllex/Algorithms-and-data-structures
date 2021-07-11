public class dlugosc {
    public static void len(String a, String b, int[][] tab) {
        for (int i = 1; i < a.length() + 1; i++)
        {
            for (int j = 1; j < b.length() + 1; j++)
            {
                if (a.charAt(i - 1) == b.charAt(j - 1))
                {
                    tab[i][j] = tab[i - 1][j - 1] + 1;
                }
                else
                {
                    if(tab[i - 1][j] > tab[i][j - 1])
                    {
                        tab[i][j] = tab[i - 1][j];
                    }
                    else
                    {
                        tab[i][j] = tab[i][j - 1];
                    }
                }
            }
        }
    }
}
