#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

#define N 9

void straightline_9(double p[9][9]){

    int i,j;
    int v[9];

    srand((unsigned int)time(NULL));
    
    for(i=0;i<9;i++){
        p[0][i]=rand()%10+(rand()%1000+1.0)/1000.0000;;
    }

    srand((unsigned int)time(NULL));

    for(i=0;i<9;i++){
        v[i]=rand()%2;
        if(v[i]==0)v[i]=-1;
    }

    for(i=1;i<9;i++){
        for(j=0;j<9;j++){
            p[i][j]=p[i-1][j]+v[j];
        }
    }

    return ;
}

int main(){
    
    int i,j;
    double p[9][9];
    FILE *fp;

    fp = fopen("test1.dat","w");

    straightline_9(p);

    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            printf("%4.5f,",p[i][j]);
            fprintf(fp,"%.4lf ",p[i][j]);
        }
        if(i!=0){
                printf("   %.5lf",sqrt(pow(p[i][0]-p[i-1][0],2)+pow(p[i][1]-p[i-1][1],2)+pow(p[i][2]-p[i-1][2],2)+
                                    pow(p[i][3]-p[i-1][3],2)+pow(p[i][4]-p[i-1][4],2)+pow(p[i][5]-p[i-1][5],2)+
                                    pow(p[i][6]-p[i-1][6],2)+pow(p[i][7]-p[i-1][7],2)+pow(p[i][8]-p[i-1][8],2)));
            }
        printf("\n");
    }

    fclose(fp);

    return 0;
}