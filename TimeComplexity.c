//analiza zlozonosci czasowej
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MLD 1000000000.0
/////////////////////////////////////////////
//   PROCEDURY POMOCNICZE                  //
/////////////////////////////////////////////
void utworz_MACIERZ(int n, int ***M){
// alokuje pami�?�? na tablic�? rozmiaru nxn
// i wpisuje losowe warto�?ci 0/1 
int i,j;
    (*M) = (int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++){
        (*M)[i]=(int *)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            (*M)[i][j]=rand()% 2;
            }
    }
}
/////////////////////////////////////////////
void utworz_MACIERZ_x(int n, int ***M, int x){
// alokuje pami na tablic�? rozmiaru nxn
// i wpisuje wszdzie warto�?ci x
int i,j;
    (*M) = (int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++){
        (*M)[i]=(int *)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            (*M)[i][j]=x;
            }
    }
}
/////////////////////////////////////////////
void wypisz_MACIERZ(int n, int **M){
// wypisuje warto�?ci tablicy
int i,j;

for(i=0;i<n;i++){
    for(j=0;j<n;j++)
        printf("%d",M[i][j]);
    printf("\n");
    }
}
/////////////////////////////////////////////
void zwolnij_MACIERZ(int n, int **M){
// zwalania pami�?�? zarezerwowan�? dla macierzy
int i;
    for(i=0;i<n;i++)
    {
    free(M[i]);
    }
    free(M);
}
/////////////////////////////////////////////
//   ALGORYTM PIERWSZY                     //
/////////////////////////////////////////////
int ALGO_NAIWNY(int n, int **M){
int x1,y1,x2,y2,x,y;
int max=0;
int local_max=0;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++)
        for(x2=n-1;x2>x1-1;x2--)
            for(y2=n-1;y2>y1-1;y2--){
                local_max=0;
                for(x=x1;x<x2+1;x++)
                    for(y=y1;y<y2+1;y++)
                        local_max+=M[x][y];
                if ((local_max==(x2-x1+1)*(y2-y1+1)) && (local_max>max)) max=local_max;
                }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM DRUGI                        //
/////////////////////////////////////////////
int REKURENCJA(int **M,int x1, int y1, int x2, int y2){
if ((x2==x1)&&(y2==y1)) return M[x1][y1];
    else if ((x2-x1)>(y2-y1))
        return REKURENCJA(M,x1,y1,(int)(x1+x2)/2,y2)*REKURENCJA(M,(int)(x1+x2+1)/2,y1,x2,y2);
            else return REKURENCJA(M,x1,y1,x2,(int)(y1+y2)/2)*REKURENCJA(M,x1,(int)(y1+y2+1)/2,x2,y2);
}
/////////////////////////////////////////////
int ALGO_REKURENCYJNY(int n, int **M){
int x1,y1,x2,y2;
int max=0;
int local_max;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++)
        for(x2=x1;x2<n;x2++)
            for(y2=y1;y2<n;y2++){
                local_max=REKURENCJA(M,x1,y1,x2,y2)*(x2-x1+1)*(y2-y1+1);
                if (local_max>max) max=local_max;
            }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM TRZECI                       //
/////////////////////////////////////////////
int ALGO_DYNAMICZNY(int n, int **M){
int x1,x2,y;
int max=0;
int iloczyn;
int **MM;

utworz_MACIERZ_x(n,&MM,0);

for(y=0;y<n;y++)
    for(x1=0;x1<n;x1++){
        iloczyn=1;
        for(x2=x1;x2<n;x2++){
            iloczyn*=M[x2][y];
            MM[x1][x2]=iloczyn*(x2-x1+1+MM[x1][x2]);
            if (MM[x1][x2]>max) max=MM[x1][x2];
        }
    }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM CZWARTY                      //
/////////////////////////////////////////////
int ALGO_CZULY(int n, int **M){
int x1,y1,x2,y2,ymax;
int max=0;
int local_max=0;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++){
        local_max=0;
        x2=x1;
        ymax=n-1;
        while ((x2<n)&&(M[x2][y1]==1)){
            y2=y1;
            while((y2<ymax+1)&&(M[x2][y2]==1)){
                y2++;
            }
            ymax=y2-1;
            local_max=(x2-x1+1)*(ymax-y1+1);
            if (local_max>max) max=local_max;
            x2++;
        }
    }
return max;
}
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
int main()
{
	int **Macierz;
	struct timespec tp0, tp1;
	double Tn,Fn;
	long int n;
	srand(time(NULL));
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	printf("\n\t\t\tALGORYTM PIERWSZY\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=70;n+=10)
	{
		utworz_MACIERZ(n,&Macierz);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm pierwszy= %d \n", ALGO_NAIWNY(n,Macierz));
		
		Fn=pow(n,6);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////	
	printf("\n\t\t\tALGORYTM PIERWSZY\n");
	printf("\t\t\tMacierz z samych zer\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=70;n+=10)
	{
		utworz_MACIERZ_x(n,&Macierz,0);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm pierwszy= %d \n", ALGO_NAIWNY(n,Macierz));
		
		Fn=pow(n,6);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	printf("\n\t\t\tALGORYTM PIERWSZY\n");
	printf("\t\t\tMacierz z samych jedynek\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=70;n+=10)
	{
		utworz_MACIERZ_x(n,&Macierz,1);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm pierwszy= %d \n", ALGO_NAIWNY(n,Macierz));
		
		Fn=pow(n,6);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	printf("\n\t\t\tALGORYTM DRUGI\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=45;n+=5)
	{
		utworz_MACIERZ(n,&Macierz);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm drugi= %d \n", ALGO_REKURENCYJNY(n,Macierz));
		
		Fn=pow(n,6);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////	
	printf("\n\t\t\tALGORYTM DRUGI\n");
	printf("\t\t\tMacierz z samych zer\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=45;n+=5)
	{
		utworz_MACIERZ_x(n,&Macierz,0);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm drugi= %d \n", ALGO_REKURENCYJNY(n,Macierz));
		
		Fn=pow(n,6);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	printf("\n\t\t\tALGORYTM DRUGI\n");
	printf("\t\t\tMacierz z samych jedynek\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=45;n+=5)
	{
		utworz_MACIERZ_x(n,&Macierz,1);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm drugi= %d \n",ALGO_REKURENCYJNY(n,Macierz));
		
		Fn=pow(n,6);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	printf("\n\t\t\tALGORYTM TRZECI\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=1200;n+=200)
	{
		utworz_MACIERZ(n,&Macierz);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm trzeci= %d \n",ALGO_DYNAMICZNY(n,Macierz));
		
		Fn=pow(n,3);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////	
	printf("\n\t\t\tALGORYTM TRZECI\n");
	printf("\t\t\tMacierz z samych zer\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=1200;n+=200)
	{
		utworz_MACIERZ_x(n,&Macierz,0);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm trzeci= %d \n",ALGO_DYNAMICZNY(n,Macierz));
		
		Fn=pow(n,3);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	printf("\n\t\t\tALGORYTM TRZECI\n");
	printf("\t\t\tMacierz z samych jedynek\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=1200;n+=200)
	{
		utworz_MACIERZ_x(n,&Macierz,1);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm trzeci= %d \n",ALGO_DYNAMICZNY(n,Macierz));
		
		Fn=pow(n,3);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	printf("\n\t\t\tALGORYTM CZWARTY\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=10000;n+=1000)
	{
		utworz_MACIERZ(n,&Macierz);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm czwarty= %d \n",ALGO_CZULY(n,Macierz));
		
		Fn=pow(n,2);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////	
	printf("\n\t\t\tALGORYTM CZWARTY\n");
	printf("\t\t\tMacierz z samych zer\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=15000;n+=1000)
	{
		utworz_MACIERZ_x(n,&Macierz,0);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm czwarty= %d \n",ALGO_CZULY(n,Macierz));
		
		Fn=pow(n,2);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	printf("\n\t\t\tALGORYTM CZWARTY\n");
	printf("\t\t\tMacierz z samych jedynek\n");
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	for(n=1;n<=300;n+=30)
	{
		utworz_MACIERZ_x(n,&Macierz,1);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
		
		printf("Algorytm czwarty= %d \n",ALGO_CZULY(n,Macierz));
		
		Fn=pow(n,4);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
		Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
		
		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
		
		zwolnij_MACIERZ(n,Macierz);
	}
	return 1;
}

