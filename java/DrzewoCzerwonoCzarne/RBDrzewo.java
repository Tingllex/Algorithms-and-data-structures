public class RBDrzewo {
    private Wezel korzen;
    private final Wezel TNULL;

    //przechodzenie drzewa
    // Preorder traversal
    private void Preorder(Wezel wezel) {
        if (wezel != TNULL) {
            System.out.print(wezel.liczba + " ");
            Preorder(wezel.lewy);
            Preorder(wezel.prawy);
        }
    }
    public void preorder() {
        Preorder(this.korzen);
    }

    // Inorder traversal
    private void Inorder(Wezel wezel) {
        if (wezel != TNULL) {
            Inorder(wezel.lewy);
            System.out.print(wezel.liczba + " ");
            Inorder(wezel.prawy);
        }
    }
    public void inorder() {
        Inorder(this.korzen);
    }

    // Postorder traversal
    private void Postorder(Wezel wezel) {
        if (wezel != TNULL) {
            Postorder(wezel.lewy);
            Postorder(wezel.prawy);
            System.out.print(wezel.liczba + " ");
        }
    }
    public void postorder() {
        Postorder(this.korzen);
    }

    private Wezel Szukanie(Wezel x, int key) {
        if (key == x.liczba || x == TNULL) {
            return x;
        }

        if (key < x.liczba) {
            return Szukanie(x.lewy, key);
        }
        return Szukanie(x.prawy, key);
    }
    public Wezel Search(int key) {
        return Szukanie(this.korzen, key);
    }

    //naprawienie wezla po usunieciu elementu
    private void Naprawa(Wezel x) {
        Wezel y;
        while (x != korzen && x.kolor == 0) {
            if (x == x.rodzic.lewy) {
                y = x.rodzic.prawy;
                if (y.kolor == 1) {
                    y.kolor = 0;
                    x.rodzic.kolor = 1;
                    lewyObrot(x.rodzic);
                    y = x.rodzic.prawy;
                }

                if (y.lewy.kolor == 0 && y.prawy.kolor == 0) {
                    y.kolor = 1;
                    x = x.rodzic;
                } else {
                    if (y.prawy.kolor == 0) {
                        y.lewy.kolor = 0;
                        y.kolor = 1;
                        prawyObrot(y);
                        y = x.rodzic.prawy;
                    }

                    y.kolor = x.rodzic.kolor;
                    x.rodzic.kolor = 0;
                    y.prawy.kolor = 0;
                    lewyObrot(x.rodzic);
                    x = korzen;
                }
            } else {
                y = x.rodzic.lewy;
                if (y.kolor == 1) {
                    y.kolor = 0;
                    x.rodzic.kolor = 1;
                    prawyObrot(x.rodzic);
                    y = x.rodzic.lewy;
                }

                if (y.prawy.kolor == 0) {
                    y.kolor = 1;
                    x = x.rodzic;
                } else {
                    if (y.lewy.kolor == 0) {
                        y.prawy.kolor = 0;
                        y.kolor = 1;
                        lewyObrot(y);
                        y = x.rodzic.lewy;
                    }

                    y.kolor = x.rodzic.kolor;
                    x.rodzic.kolor = 0;
                    y.lewy.kolor = 0;
                    prawyObrot(x.rodzic);
                    x = korzen;
                }
            }
        }
        x.kolor = 0;
    }

    //naprawa wezla po wstawieniu
    private void NaprawaPoWstawieniu(Wezel x) {
        Wezel y;
        while (x.rodzic.kolor == 1) {
            if (x.rodzic == x.rodzic.rodzic.prawy) {
                y = x.rodzic.rodzic.lewy;
                if (y.kolor == 1) {
                    y.kolor = 0;
                    x.rodzic.kolor = 0;
                    x.rodzic.rodzic.kolor = 1;
                    x = x.rodzic.rodzic;
                } else {
                    if (x == x.rodzic.lewy) {
                        x = x.rodzic;
                        prawyObrot(x);
                    }
                    x.rodzic.kolor = 0;
                    x.rodzic.rodzic.kolor = 1;
                    lewyObrot(x.rodzic.rodzic);
                }
            } else {
                y = x.rodzic.rodzic.prawy;
                if (y.kolor == 1) {
                    y.kolor = 0;
                    x.rodzic.kolor = 0;
                    x.rodzic.rodzic.kolor = 1;
                    x = x.rodzic.rodzic;
                } else {
                    if (x == x.rodzic.prawy) {
                        x = x.rodzic;
                        lewyObrot(x);
                    }
                    x.rodzic.kolor = 0;
                    x.rodzic.rodzic.kolor = 1;
                    prawyObrot(x.rodzic.rodzic);
                }
            }
            if (x == korzen) {
                break;
            }
        }
        korzen.kolor = 0;
    }

    private void Transplant(Wezel x, Wezel y) {
        if (x.rodzic == null) {
            korzen = y;
        } else if (x == x.rodzic.lewy) {
            x.rodzic.lewy = y;
        } else {
            x.rodzic.prawy = y;
        }
        y.rodzic = x.rodzic;
    }

    private void UsunWezel(Wezel wezel, int key) {
        Wezel z = TNULL;
        Wezel x, y;
        while (wezel != TNULL) {
            if (wezel.liczba == key) {
                z = wezel;
            }
            if (wezel.liczba <= key) {
                wezel = wezel.prawy;
            } else {
                wezel = wezel.lewy;
            }
        }
        if (z == TNULL) {
            System.out.println("Nie znaleziono " + key + " w drzewie\n");
            return;
        }
        y = z;
        int Poczatkowykolor = y.kolor;
        if (z.lewy == TNULL) {
            x = z.prawy;
            Transplant(z, z.prawy);
        } else if (z.prawy == TNULL) {
            x = z.lewy;
            Transplant(z, z.lewy);
        } else {
            y = min(z.prawy);
            Poczatkowykolor = y.kolor;
            x = y.prawy;
            if (y.rodzic == z) {
                x.rodzic = y;
            } else {
                Transplant(y, y.prawy);
                y.prawy = z.prawy;
                y.prawy.rodzic = y;
            }
            Transplant(z, y);
            y.lewy = z.lewy;
            y.lewy.rodzic = y;
            y.kolor = z.kolor;
        }
        if (Poczatkowykolor == 0) {
            Naprawa(x);
        }
    }

    private void DrukujDrzewo(Wezel korzen, String akapit, boolean ostatni) {
        if (korzen != TNULL) {
            System.out.print(akapit);
            if (ostatni) {
                System.out.print("prawy - - ");
                akapit += "   ";
            } else {
                System.out.print("lewy - - ");
                akapit += "|  ";
            }
            String RczyB = korzen.kolor == 1 ? "R" : "B";
            System.out.println(RczyB + " " + korzen.liczba);
            DrukujDrzewo(korzen.lewy, akapit, false);
            DrukujDrzewo(korzen.prawy, akapit, true);
        }
    }

    public RBDrzewo() {
        TNULL = new Wezel();
        TNULL.kolor = 0;
        TNULL.lewy = null;
        TNULL.prawy = null;
        korzen = TNULL;
    }









    public Wezel min(Wezel x) {
        while (x.lewy != TNULL) {
            x = x.lewy;
        }
        return x;
    }

    public void lewyObrot(Wezel x) {
        Wezel y = x.prawy;
        x.prawy = y.lewy;
        if (y.lewy != TNULL) {
            y.lewy.rodzic = x;
        }
        y.rodzic = x.rodzic;
        if (x.rodzic == null) {
            this.korzen = y;
        } else if (x == x.rodzic.lewy) {
            x.rodzic.lewy = y;
        } else {
            x.rodzic.prawy = y;
        }
        y.lewy = x;
        x.rodzic = y;
    }

    public void prawyObrot(Wezel x) {
        Wezel y = x.lewy;
        x.lewy = y.prawy;
        if (y.prawy != TNULL) {
            y.prawy.rodzic = x;
        }
        y.rodzic = x.rodzic;
        if (x.rodzic == null) {
            this.korzen = y;
        } else if (x == x.rodzic.prawy) {
            x.rodzic.prawy = y;
        } else {
            x.rodzic.lewy = y;
        }
        y.prawy = x;
        x.rodzic = y;
    }

    public Wezel getKorzen() {
        return this.korzen;
    }

    public void Wstaw(int key) {
        Wezel wezel = new Wezel();
        wezel.rodzic = null;
        wezel.liczba = key;
        wezel.lewy = TNULL;
        wezel.prawy = TNULL;
        wezel.kolor = 1;

        Wezel y = null;
        Wezel x = this.korzen;

        while (x != TNULL) {
            y = x;
            if (wezel.liczba < x.liczba) {
                x = x.lewy;
            } else {
                x = x.prawy;
            }
        }

        wezel.rodzic = y;
        if (y == null) {
            korzen = wezel;
        } else if (wezel.liczba < y.liczba) {
            y.lewy = wezel;
        } else {
            y.prawy = wezel;
        }
        if (wezel.rodzic == null) {
            wezel.kolor = 0;
            return;
        }
        if (wezel.rodzic.rodzic == null) {
            return;
        }
        NaprawaPoWstawieniu(wezel);
    }

    public void Usun(int key) {
        UsunWezel(this.korzen, key);
    }

    public void Drukuj() {
        DrukujDrzewo(this.korzen, "", true);
        System.out.println();
    }
}
