#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

size_t max(string A[], int n){ //maksymalna wartosc
    size_t k = A[0].size();
    for (int i = 1; i < n; i++){
        if (A[i].size()>k)
            k = A[i].size();
    }
    return k;
}

void countSort(string A[], int n, size_t k){ 
    string *B = NULL; 
	int *C = NULL;
    B = new string[n];
    C = new int[256]; //max wartosc w ascii to 256

    for (int i = 0; i <= 256; i++){
        C[i] = 0;
    }
    for (int j = 0; j <n; j++){   
        C[k < A[j].size() ? (int)(unsigned char)A[j][k] + 1 : 0]++; //C[i] == ilosc wartosci rownych "i" w tablicy A
    }

    for (int i = 1; i <256; i++){
        C[i] += C[i - 1]; //C[i] == ilosc wartosci mniejszych lub rownych "i" w A
    }

    for (int j = n - 1; j >= 0; j--){
        B[C[k < A[j].size() ? (int)(unsigned char)A[j][k] + 1 : 0] - 1] = A[j]; //B[C[A[j]]]=A[j]
        C[k < A[j].size() ? (int)(unsigned char)A[j][k] + 1 : 0]--; //C[A[j]]=C[A[j]]-1
    }

    for (int i = 0; i < n; i++){
        A[i] = B[i];
    }

    //zwalnianie pamieci
    delete[] B;
    delete[] C;
}


void radixSort(string A[], int n){
    size_t k = max(A, n);
    for (size_t cyfra = k; cyfra > 0; cyfra--){
        countSort(A, n, cyfra - 1);
    }
}

int main() {
	
    string tablica[] = {"4123","123","321","12312","4412","1111","111"};
    string tablica2[] = {"abb","abbb","accaca","casdads","casca","acacs","aaaaa"};
    
	cout<<"tablica:"<<endl;
	cout<<"Przed sortowaniem:"<<endl;
    for (size_t i = 0; i < sizeof(tablica) / sizeof(tablica[0]); i++) {
        printf("%s\n", tablica[i].c_str());
    }
    radixSort(tablica, (int)(sizeof(tablica) / sizeof(tablica[0])));
    
    cout<<endl<<"Po sortowaniu:"<<endl;
    for (size_t i = 0; i < sizeof(tablica) / sizeof(tablica[0]); i++) {
        printf("%s\n", tablica[i].c_str());
    }
    cout<<endl<<"tablica2:"<<endl;
    cout<<"Przed sortowaniem:"<<endl;
    for (size_t i = 0; i < sizeof(tablica2) / sizeof(tablica2[0]); i++) {
        printf("%s\n", tablica2[i].c_str());
    }
    radixSort(tablica2, (int)(sizeof(tablica2) / sizeof(tablica2[0])));
    
    cout<<endl<<"Po sortowaniu:"<<endl;
    for (size_t i = 0; i < sizeof(tablica2) / sizeof(tablica2[0]); i++) {
        printf("%s\n", tablica2[i].c_str());
    }
    return 0;
}
