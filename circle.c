#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

#define PI 3.14159265358979323846


void circular_2(double p[9][2]){

    srand((unsigned int)time(NULL));

    p[8][0]=rand()%10+(rand()%1000+1.0)/1000.0000;
    p[8][1]=rand()%10+(rand()%1000+1.0)/1000.0000;

    p[0][0]=p[8][0]+2.5;
    p[0][1]=p[8][1];

    p[1][0]=p[8][0]+cos(PI/4)*2.5;
    p[1][1]=p[8][1]+sin(PI/4)*2.5;

    p[2][0]=p[8][0];
    p[2][1]=p[8][1]+2.5;

    p[3][0]=p[8][0]-cos(PI/4)*2.5;
    p[3][1]=p[8][1]+sin(PI/4)*2.5;

    p[4][0]=p[8][0]-2.5;
    p[4][1]=p[8][1];

    p[5][0]=p[8][0]-cos(PI/4)*2.5;
    p[5][1]=p[8][1]-sin(PI/4)*2.5;

    p[6][0]=p[8][0];
    p[6][1]=p[8][1]-2.5;

    p[7][0]=p[8][0]+cos(PI/4)*2.5;
    p[7][1]=p[8][1]-sin(PI/4)*2.5;

    return ;
}

int main(){
    
    int i,j;
    double p[9][2];
    FILE *fp;

    fp = fopen("test2.dat","w");

    circular_2(p);

    for(i=0;i<9;i++){
        for(j=0;j<2;j++){
            printf("%18.15lf,",p[i][j]);
            fprintf(fp,"%.4lf ",p[i][j]);
        }
        printf("\n");
        fprintf(fp,"\n");
    }

     fclose(fp);

    return 0;
}