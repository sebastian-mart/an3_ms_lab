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
        double STp1=0,STp2=0,STS=0,STL1=0,STL2=0;
        int i=1;
        double Ta1=0,Ta2=0;
        double Tp1=genExp(miu1),Tp2;
        //double Tp1=genGauss(1/miu1,sigma),Tp2;
            
        STp1+=Tp1;
        double Dis1,Dis2,TL1,TL2;
        do{
            STS+=Ta1+Tp1;
            Dis1=genExp(lambda);
            if(Dis1>Ta1+Tp1){
                TL1=Dis1-(Ta1+Tp1);
                Ta1=0;
            }else{
                Ta1=Ta1+Tp1-Dis1;
                TL1=0;
            }
            STL1+=TL1;
            
            // Tp2=genGauss(1/miu2,sigma);
            Tp2=genExp(miu2);
            STS+=Ta2+Tp2;
            STp2+=Tp2;

            // Tp1=genGauss(1/miu1,sigma);
            Tp1=genExp(miu1);
            STp1+=Tp1;
            Dis2=TL1+Tp1;

            if(Dis2>Ta2+Tp2){
                TL2=Dis2-(Ta2+Tp2);
                Ta2=0;
            }else{
                Ta2=Ta2+Tp2-Dis2;
                TL2=0;
            }
            
            STL2+=TL2;
            
            i++;



        }while(i<=NS);
    cout<<"lambda="<<lambda<<endl;
    cout<<"TSm="<<STS/NS<<";O1="<<STp1/(STp1+STL1);
    cout<<";O2="<<STp2/(STp2+STL2);
    }

}