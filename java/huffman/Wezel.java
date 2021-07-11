class Wezel
{
    Wezel lewy = null;
    Wezel prawy = null;
    Character z;
    Integer czestosc;
    public Wezel(Character z, Integer czestosc, Wezel lewy, Wezel prawy)
    {
        this.z = z;
        this.czestosc = czestosc;
        this.lewy = lewy;
        this.prawy = prawy;
    }
    public Wezel(Character z, Integer czestosc)
    {
        this.z = z;
        this.czestosc = czestosc;
    }
}