#include<iostream>
#include<math.h>
using namespace std;


double genGauss(double medie, double sigma)
{
    double s = 0;
    int i;
    for (i = 1; i <= 12; i++)
        s += (double)rand() / RAND_MAX;
    return medie + sigma * (s - 6);
}

double genExp(double lambda)
{
    double u, x;
    u = (double)rand() / RAND_MAX;
    x = (-1) / lambda * log(1 - u);
    return x;
}


int main(){
    double lambda,miu1=10,miu2=10,NS=1000000,sigma=0.05;
    for(lambda=4;lambda<=9;lambda++){
        double STR=0;
        int i=1;
        double Ta=0;
        double Tp1,Tp2;
        double Dis;
        double Tp;
        do{
            Tp1=genExp(miu1);
            Tp2=genExp(miu2);
            // Tp1=genGauss(1/miu1,sigma);
            // Tp2=genGauss(1/miu2,sigma);

            if(Tp1>Tp2){
                Tp=Tp1;
            }else Tp=Tp2;
            
            STR+=Ta+Tp;
            Dis=genExp(lambda);
            
            if(Dis>Ta+Tp){
                Ta=0;
            }else{
                Ta=Ta+Tp-Dis;
            }
            i++;
        }while(i<=NS);
    cout<<"\nlambda="<<lambda<<endl;
    cout<<"TRm="<<(STR/NS)<<endl;
    }
    return 0;
}