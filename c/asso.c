#include<stdio.h>
#include <stdlib.h>

int main(void){

    double sum=0,s=0;
    int n=200,m=80,t=20;
    int original[200][80];
    int data[20][80];
    double weight[200][200];
    double direction[20];
    int i,j,k,a;

    
    //記憶パターンを生成
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            original[i][j]=rand()%2;
            if(original[i][j]==0){
                original[i][j]=-1;
            }
        //printf("%2d",original[i][j]);
        }
    }
    //printf("\n");

      //ウェイトの計算
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            if(i==j){
                weight[i][j]=0;
            }else{
                for(k=0;k<m;k++){
                    s=original[m][i]*original[m][j];
                    sum=sum+s;
                }
                weight[i][j]=sum/n;
            }
        }
    }

    //生成したパターンの０番目にノイズをかける
    a=25;
    for(i=0;i<a;i++){
        original[0][i]=original[0][i]*-1;
        //printf("%2d",input_data[i]);
    }
    for(j=i;j<m;j++){
        original[0][j]=original[0][j];
        //printf("%2d",input_data[j]);
    }
    //printf("\n");


    //想起の動き
    sum=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            sum=sum+weight[i][j]*original[0][j];
        }
        if(sum<0){
            data[1][i]=-1;
        }else{
            data[1][i]=1;
        }
    }

    sum=0;


    //オリジナルとの差異（direction cosine）
    for(i=0;i<m;i++){
        sum=sum+original[0][i]*data[1][i];
    }
    direction[0]=sum/m;

    printf("%1.4lf\n",direction[0]);


    return 0;
}