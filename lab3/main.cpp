#include<iostream>
#include<random>
#include<math.h>
using namespace std;
double genGauss(double medie,double sigma){
    double s=0;int i;
    for(i=1;i<=12;i++)
        s+=(double)rand()/RAND_MAX;
    return medie+sigma*(s-6);
}
double genExp(double lambda){
    double u,x;
    u=(double) random()/RAND_MAX;
    x=-1/lambda*log(1-u);
    return x;
}

int main(){
    int k;
    cout<<"k=(0:genExp,1:genGauss)";
    cin>>k;
    double miu=10,NS=1000000;
    double sigma=0.01;
    double lambda;
    double STP,STS,STL;
    for(lambda=4;lambda<=9;lambda++){
        STS=0;STP=0;STL=0;
        double Ta=0,Tp;
        for(int i=1;i<=NS;i++){
            if(k==0)
                Tp=genExp(miu);
            else
                Tp=genGauss(1/miu,sigma);
            STP+=Tp;
            STS+=Ta+Tp;
            double Dis=genExp(lambda);
            if(Dis>Ta+Tp){
                STL+=Dis-(Ta+Tp);
                Ta=0;
            }
            else{
                Ta=Ta+Tp-Dis;
            }
        }
        double TSm=STS/NS,O=STP/(STP+STL)*100;
        cout<<"pentru lambda="<<lambda<<":TSm="<<TSm<<"\tO%="<<O<<"\n";
    }


    return 0;
}