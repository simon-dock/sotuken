#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>


void nonlinear_5(double p[29][5]){

    int i;

    for(i=0;i<29;i++){
        p[i][4]=(sqrt(2)/2)*i;
        p[i][0]=cos(p[i][4]);
        p[i][1]=sin(p[i][4]);
        p[i][2]=0.5*cos(2*(p[i][4]));
        p[i][3]=0.5*sin(2*(p[i][4]));
    }

    return ;
}

int main(){
    
    int i,j;
    double p[29][5];
    FILE *fp;

    fp = fopen("test6.dat","w");

    nonlinear_5(p);

    for(i=0;i<29;i++){
        for(j=0;j<5;j++){
            printf("%18.15lf,",p[i][j]);
            fprintf(fp,"%.4lf ",p[i][j]);
        }
        printf("\n");
    }
    

    fclose(fp);

    return 0;
}