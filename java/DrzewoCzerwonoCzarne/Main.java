public class Main {
    public static void main(String[] args) {
        RBDrzewo drzewo = new RBDrzewo();

        drzewo.Wstaw(4);
        drzewo.Wstaw(21);
        drzewo.Wstaw(42);
        drzewo.Wstaw(8);
        drzewo.Wstaw(20);
        drzewo.Wstaw(5);
        drzewo.Wstaw(10);
        //drzewo.Drukuj();

        drzewo.Usun(12);
        drzewo.Usun(8);

        //drzewo.Drukuj();

        drzewo.Usun(10);
        //drzewo.Usun(21);
        drzewo.Drukuj();
    }
}
