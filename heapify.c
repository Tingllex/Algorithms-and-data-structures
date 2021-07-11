#include <stdio.h>
#include <stdlib.h>

void zamien(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
void heapify(int tab[], int n, int i) { //kopcowanie
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && tab[l] > tab[max])
        max = l;

    if (r < n && tab[r] > tab[max])
        max = r;

    if (max != i) {
        zamien(&tab[i], &tab[max]);
        heapify(tab, n, max);
    }
}
void heapSort(int tab[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) //budowanie kopca (buildheap)
        heapify(tab, n, i);

    for (int i = n - 1; i >= 0; i--) { //sortowanie kopcowe (heapsort)
        zamien(&tab[0], &tab[i]);
        heapify(tab, i, 0);
    }
}

void wypis(int tab[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", tab[i]);
    printf("\n");
}

void rozmiar(int* tablica, int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &tablica[i]);
    }
}

int main() {
    FILE* plik;
    plik = fopen("posortowana_tablica.txt", "w");
    int x;
    printf("\t\tSortowanie przez kopcowanie: \n");
    printf("Podaj rozmiar tablicy: \n");
    scanf("%d", &x);
    int* arr = malloc(sizeof(int) * x);
    printf("Podaj zawartosc tablicy: \n");
    rozmiar(arr, x);
    printf("Podana tablica:\n");
    wypis(arr, x);
    heapSort(arr, x);
    printf("Posortowana tablica w pliku tekstowym.\n");
    //wypis(arr, x);    //wypis posortowanej tablicy do konsoli
    for (int i = 0; i < x; ++i) {
        fprintf(plik, "%d \n", arr[i]);
    }
    fclose(plik);
}
