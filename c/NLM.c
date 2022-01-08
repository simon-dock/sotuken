#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//座標用構造体
typedef struct{
    double x;
    double y;
}POINT;

//ｘの偏微分
double xdifferen(double (*func)(double,double),double x,double y,double h){
    
    double fx;

    fx=(func(x+h,y)-func(x,y))/h;

    return fx;
}


//ｙの偏微分
double ydifferen(double (*func)(double,double),double x,double y,double h){
    
    double fy;

    fy=(func(x,y+h)-func(x,y))/h;

    return fy;
}

//目的関数
double function(double x,double y){
    
    double f;

    f=pow((x-1),4)+pow((y-2),2);
    
    return f;
}

//最急降下法
POINT extreme(POINT p0){

    POINT p;
    double x,y,h,a,fx,fy,err,esp;
    int n=0,m=1000000;

    a=0.04;
    h=0.000000001;
    esp=1.e-5;
    x=p0.x;
    y=p0.y;

    do
    {
        n++;
        fx=xdifferen(function,x,y,h);
        fy=ydifferen(function,x,y,h);
        x-=a*fx;
        y-=a*fy;
        if(x<-2)x=-2;
        if(x>2)x=2;
        if(y<-2)y=-2;
        if(y>2)y=2;
        err=fabs(fx)+fabs(fy);
        printf("%d\n",n);
        if(n>m)break;
    } while (err>esp);
    
    p.x=x;
    p.y=y;

    return p;
}


int main(){

    POINT p0,p;

    p0.x=0.0;
    p0.y=0.0;
/*
    p=extreme(p0);

    printf("x  = %.1f\n",p.x);
    printf("y  = %.1f\n",p.y);
*/
    double a,b;

    a = xdifferen(function,p0.x,p0.y,0.000000001);
    b = xdifferen(function,p0.x,p0.y,0.000000001);

    printf("%.10lf %.10lf\n",a,b);
    return 0;
    
}