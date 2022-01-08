#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//d空間座標用構造体
typedef struct{
    double y1;
    double y2;
}Y_POINT;

//L空間座標用構造体
typedef struct{
    double x1;
    double x2;
    double x3;
}X_POINT;

//y11の偏微分
double y11_diff(double (*func)(X_POINT*,Y_POINT*),X_POINT *px,Y_POINT *py){
    
    double fx;
    double h=0.00001;
    Y_POINT* pyh;
    pyh=(Y_POINT*)malloc(sizeof(Y_POINT)*3);

    pyh[0].y1=py[0].y1+h;
    pyh[0].y2=py[0].y2;
    pyh[1].y1=py[1].y1;
    pyh[1].y2=py[1].y2;
    pyh[2].y1=py[2].y1;
    pyh[2].y2=py[2].y2;

    fx=(func(px,pyh)-func(px,py))/h;

    return fx;
}

//y12の偏微分
double y12_diff(double (*func)(X_POINT*,Y_POINT*),X_POINT *px,Y_POINT *py){
    
    double fx;
    double h=0.000000001;
    Y_POINT* pyh;

    pyh=(Y_POINT*)malloc(sizeof(Y_POINT)*3);

    pyh[0].y1=py[0].y1;
    pyh[0].y2=py[0].y2+h;
    pyh[1].y1=py[1].y1;
    pyh[1].y2=py[1].y2;
    pyh[2].y1=py[2].y1;
    pyh[2].y2=py[2].y2;

    fx=(func(px,pyh)-func(px,py))/h;

    return fx;
}

//y21の偏微分
double y21_diff(double (*func)(X_POINT*,Y_POINT*),X_POINT *px,Y_POINT *py){
    
    double fx;
    double h=0.000000001;
    Y_POINT* pyh;

    pyh=(Y_POINT*)malloc(sizeof(Y_POINT)*3);
    pyh[0].y1=py[0].y1;
    pyh[0].y2=py[0].y2;
    pyh[1].y1=py[1].y1+h;
    pyh[1].y2=py[1].y2;
    pyh[2].y1=py[2].y1;
    pyh[2].y2=py[2].y2;

    fx=(func(px,pyh)-func(px,py))/h;

    return fx;
}

//y22の偏微分
double y22_diff(double (*func)(X_POINT*,Y_POINT*),X_POINT *px,Y_POINT *py){
    
    double fx;
    double h=0.000000001;
    Y_POINT* pyh;

    pyh=(Y_POINT*)malloc(sizeof(Y_POINT)*3);
    pyh[0].y1=py[0].y1;
    pyh[0].y2=py[0].y2;
    pyh[1].y1=py[1].y1;
    pyh[1].y2=py[1].y2+h;
    pyh[2].y1=py[2].y1;
    pyh[2].y2=py[2].y2;

    fx=(func(px,pyh)-func(px,py))/h;

    return fx;
}

//y31の偏微分
double y31_diff(double (*func)(X_POINT*,Y_POINT*),X_POINT *px,Y_POINT *py){
    
    double fx;
    double h=0.000000001;
    Y_POINT* pyh;

    pyh=(Y_POINT*)malloc(sizeof(Y_POINT)*3);

    pyh[0].y1=py[0].y1;
    pyh[0].y2=py[0].y2;
    pyh[1].y1=py[1].y1;
    pyh[1].y2=py[1].y2;
    pyh[2].y1=py[2].y1+h;
    pyh[2].y2=py[2].y2;

    fx=(func(px,pyh)-func(px,py))/h;

    return fx;
}

//y32の偏微分
double y32_diff(double (*func)(X_POINT*,Y_POINT*),X_POINT *px,Y_POINT *py){
    
    double fx;
    double h=0.000000001;
    Y_POINT* pyh;

    pyh=(Y_POINT*)malloc(sizeof(Y_POINT)*3);

    pyh[0].y1=py[0].y1;
    pyh[0].y2=py[0].y2;
    pyh[1].y1=py[1].y1;
    pyh[1].y2=py[1].y2;
    pyh[2].y1=py[2].y1;
    pyh[2].y2=py[2].y2+h;

    fx=(func(px,pyh)-func(px,py))/h;

    return fx;
}

//d空間ユークリッド距離dist
double dist_d(Y_POINT p0,Y_POINT p1){

    double d;

    d=sqrt(pow(p0.y1-p1.y1,2)+pow(p0.y2-p1.y2,2));

    return d;
}

//L空間ユークリッド距離dist
double dist_L(X_POINT p0,X_POINT p1){

    double d;

    d=sqrt(pow(p0.x1-p1.x1,2)+pow(p0.x2-p1.x2,2)+pow(p0.x3-p1.x3,2));

    return d;
}

//目的関数
double function(X_POINT *px,Y_POINT *py){
    
    double f,a,b;

    a=1/(dist_L(px[0],px[1])+dist_L(px[0],px[2])+dist_L(px[1],px[2]));
    b=pow(dist_L(px[0],px[1])-dist_d(py[0],py[1]),2)/dist_L(px[0],px[1])+
      pow(dist_L(px[0],px[2])-dist_d(py[0],py[2]),2)/dist_L(px[0],px[2])+
      pow(dist_L(px[1],px[2])-dist_d(py[1],py[2]),2)/dist_L(px[1],px[2]);

    f=a*b;
    
    return f;
}

//最急降下法
Y_POINT* extreme(X_POINT *px,Y_POINT *py){

    Y_POINT* p;
    double y11,y12,y21,y22,y31,y32,a,fy11,fy12,fy21,fy22,fy31,fy32,err,esp;
    int n=0,m=10000;

    p=(Y_POINT*)malloc(sizeof(Y_POINT)*3);

    a=0.03;
    esp=1e-3;
    y11=py[0].y1;
    y12=py[0].y2;
    y21=py[1].y1;
    y22=py[1].y2;
    y31=py[2].y1;
    y32=py[2].y2;

    printf("strat\n");

    do
    {
        n++;
        fy11=y11_diff(function,px,py);
        fy12=y12_diff(function,px,py);
        fy21=y21_diff(function,px,py);
        fy22=y22_diff(function,px,py);
        fy31=y31_diff(function,px,py);
        fy32=y32_diff(function,px,py);

        y11-=a*fy11;
        y12-=a*fy12;
        y21-=a*fy21;
        y22-=a*fy22;
        y31-=a*fy31;
        y32-=a*fy32;

        p[0].y1=y11;
        p[0].y2=y12;
        p[1].y1=y21;
        p[1].y2=y22;
        p[2].y1=y31;
        p[2].y2=y32;
/*
        if(p[0].y1<-5)p[0].y1=-5;
        if(p[0].y1>5)p[0].y1=5;
        if(p[0].y2<-5)p[0].y2=-5;
        if(p[0].y2>5)p[0].y2=5;

        if(p[1].y1<-5)p[1].y1=-5;
        if(p[1].y1>5)p[1].y1=5;
        if(p[1].y2<-5)p[1].y2=-5;
        if(p[1].y2>5)p[1].y2=5;

        if(p[2].y1<-5)p[2].y1=-5;
        if(p[2].y1>5)p[2].y1=5;
        if(p[2].y2<-5)p[2].y2=-5;
        if(p[2].y2>5)p[2].y2=5;
*/
        err=function(px,p);
        printf("%d\n",n);
        if(n>m)break;
    } while (err>esp);

    return p;
}


//
int main(){

    X_POINT* px;
    Y_POINT* py;
    Y_POINT* p;

    px=(X_POINT*)malloc(sizeof(X_POINT)*3);
    py=(Y_POINT*)malloc(sizeof(Y_POINT)*3);
    p=(Y_POINT*)malloc(sizeof(Y_POINT)*3);

    //double d1,d2,d3,d4,d5,d6,y11;

    px[0].x1=1.0;
    px[0].x2=1.0;
    px[0].x3=1.0;

    px[1].x1=2.0;
    px[1].x2=2.0;
    px[1].x3=2.0;

    px[2].x1=3.0;
    px[2].x2=3.0;
    px[2].x3=3.0;

    py[0].y1=2.0;
    py[0].y2=1.0;

    py[1].y1=3.0;
    py[1].y2=0.0;

    py[2].y1=5.0;
    py[2].y2=4.0;
/*
    y11=y21_diff(function,px,py);

    printf("%1f\n",y11);

*/   
    p=extreme(px,py);

    printf("y1(%18.15lf,%18.15lf)\n",p[0].y1,p[0].y2);
    printf("y2(%18.15lf,%18.15lf)\n",p[1].y1,p[1].y2);
    printf("y3(%18.15lf,%18.15lf)\n",p[2].y1,p[2].y2);

    /*p=extreme(p0);

    printf("x  = %.1f\n",p.x);
    printf("y  = %.1f\n",p.y);
    */

   free(p);
   free(px);
   free(py);
    
    return 0;
    
}