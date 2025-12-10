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
        int i=1;
        double Ta1=0,Ta2=0;
        double Tp1,Tp2;
        double Dis;
        double STR=0;
        do{
            Tp1=genExp(miu1);
            Tp2=genExp(miu2);
            // Tp1=genGauss(1/miu1,sigma);
            // Tp2=genGauss(1/miu2,sigma);
            if(Ta1+Tp1>Ta2+Tp2){
                STR+=Ta1+Tp1;
            }else STR+=Ta2+Tp2;
            Dis=genExp(lambda);
            if(Dis>Ta1+Tp1){
                Ta1=0;
            }else{
                Ta1=Ta1+Tp1-Dis;
            }
            if(Dis>Ta2+Tp2){
                Ta2=0;
            }else{
                Ta2=Ta2+Tp2-Dis;
            }
            
            i++;



        }while(i<=NS);
    cout<<"\nlambda="<<lambda<<endl;
    cout<<"TRm="<<STR/NS<<endl;
    }

}