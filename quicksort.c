//gcc quicksort.c -lrt -lm
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MLD 1000000000.0

//##########podpunkt 1############
//partition(A,p,r)
    int partition(int A[], int p, int r) {
        int x=A[r]; //element wyznaczajacy podzial
        int i=p-1;
        int temp;
        for(int j=p; j<r; j++) {
            if(A[j]<=x)
            {
                i=i+1;
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
            }
        }
        temp=A[i+1];
        A[i+1]=A[r];
        A[r]=temp;
        return i+1;
    }

//quickSort(A,p,r)
    void quickSort1(int A[], int p, int r) {
        if(p<r)
        {
            int q = partition(A,p,r);
            quickSort1(A,p,q-1);
            quickSort1(A,q+1,r);
        }
    }
//##########podpunkt 2############
     void quickSort(int A[], int p, int r) {
        int c=5; //stala c>=1
        if(r-p+1<c)
        {
            //brak wykonania procedury Partition
        }
        else if(p<r) {
            int q = partition(A,p,r);
            quickSort(A,p,q-1);
            quickSort(A,q+1,r);
        }
    }
//Sortowanie przez wstawianie (Insertion-sort)
    void insertionSort(int arr[], int n) 
    { 
    int i, j, current;
    for (i = 1; i < n; i++) { 
        current = arr[i]; 
        j = i - 1; 
  
        while (j >= 0 && arr[j] > current) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = current; 
        } 
    } 


    int main() {
    	double Tn1, Tn2, x;
        struct timespec tp0, tp1, tp2, tp3;
        long int n; 
        printf("\t\t\tPorownanie czasow dzialania algorytmow\n");
        printf("#################################################################");
        printf("\nRodzaj danych:\tDane losowe \n");
        for(long int n=10000;n<=150000;n+=20000) { //rozmiar tablicy
        	int A[n];
        	int B[n];
       		for(int i=0;i<n;i++)
        	{
            	A[i]= rand() % 100;
            	B[i]= A[i];
      		}
        	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        	
        	quickSort(A, 0, (sizeof(A) / sizeof(A[0]))-1);
        	insertionSort(A, (sizeof(A) / sizeof(A[0])));
        
        	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
        
        	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp2);
        	
        	quickSort1(B, 0, (sizeof(B) / sizeof(B[0]))-1);
        	
        	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp3);

        	Tn1=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
        	Tn2=(tp3.tv_sec+tp3.tv_nsec/MLD)-(tp2.tv_sec+tp2.tv_nsec/MLD);
        
        	printf("Rozmiar tablicy: %6ld\nczas quickSort z insertionSort: %3.10lf \tczas quickSort1: %3.10lf\n\n",n,Tn1, Tn2);
        }
        printf("#################################################################");
        printf("\nRodzaj danych:\tDane skrajnie niekorzystne (ciag malejacy) \n");
        for(long int n=10000;n<=50000;n+=10000) { //rozmiar tablicy
        	int A[n];
        	int B[n];
        	for(int i=0;i<n;i++)
        	{
        	    A[i]= n-1;
        	    B[i]= A[i];
        	}
        	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        	
        	quickSort(A, 0, (sizeof(A) / sizeof(A[0]))-1);
        	insertionSort(A, (sizeof(A) / sizeof(A[0])));
        	
        	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
        	
        	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp2);
        	
        	quickSort1(B, 0, (sizeof(B) / sizeof(B[0]))-1);
        	
        	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp3);
        	
        	Tn1=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
        	Tn2=(tp3.tv_sec+tp3.tv_nsec/MLD)-(tp2.tv_sec+tp2.tv_nsec/MLD);
        
        	printf("Rozmiar tablicy: %6ld\nczas quickSort z insertionSort: %3.10lf \tczas quickSort1: %3.10lf\n\n",n,Tn1, Tn2);
        }
    }
