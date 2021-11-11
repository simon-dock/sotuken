#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>


void helix_3(double p[30][3]){

    int i,j;

    for(i=0;i<30;i++){
        p[i][2]=(sqrt(2)/2)*i;
        p[i][0]=cos(p[i][2]);
        p[i][1]=sin(p[i][2]);   
    }

    return ;
}

int main(){
    
    int i,j;
    double p[30][3];
    FILE *fp;

    fp = fopen("test5.dat","w");

    helix_3(p);

    for(i=0;i<30;i++){
        for(j=0;j<3;j++){
            printf("%18.15lf,",p[i][j]);
            fprintf(fp,"%.4lf ",p[i][j]);
        }
        printf("\n");
    }

    fclose(fp);

    return 0;
}