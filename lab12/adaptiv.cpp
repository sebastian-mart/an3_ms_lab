#include <iostream>
#include <math.h>
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
struct a
{
    double MS, Tp1, Tp2;
};

int evUrmator(int n1, int n2, double Dis, a Q1[], a Q2[])
{
    if (n1 == 0 && n2 == 0)
        return 1;
    if (n2 == 0)
    {
        if (Dis <= Q1[1].Tp1)
            return 1;
        if (Q1[1].Tp2 == 0)
            return 2;
        return 4;
    }
    if (n1 == 0)
    {
        if (Dis <= Q2[1].Tp2)
            return 1;
        if (Q1[1].Tp1 == 0)
            return 3;
        return 5;
    }
    if (Dis < Q1[1].Tp1 && Dis < Q2[1].Tp2)
        return 1;
    if (Q1[1].Tp1 < Q2[1].Tp2)
    {
        if (Q1[1].Tp2 == 0)
            return 2;
        return 4;
    }
    // if(Q2[1].Tp2<=Q1[1].Tp1)
    else
    {
        if (Q2[1].Tp1 == 0)
            return 3;
        return 5;
    }
    return 0;
}

int main()
{
    double lambda, miu1 = 10, miu2 = 10, miu = 10, sigma = 0.05;
    int NS = 1000000;
    for (lambda = 4; lambda <= 9; lambda++)
    {
        int DS = NS / lambda;
        double STR = 0, CT = 0, ceas = 0;
        int n1 = 0, n2 = 0;
        double Tp[2];
        Tp[1] = genExp(miu), Tp[2] = genExp(miu);
        // Tp[1] = genGauss(1/miu,sigma), Tp[2] = genGauss(1/miu,sigma);
        a Q1[200], Q2[200];
        Q1[1].Tp1 = Tp[1];
        Q1[1].Tp2 = Tp[2];
        Q1[1].MS = ceas;
        double Dis = genExp(lambda);
        do
        {
            int decizie = evUrmator(n1, n2, Dis, Q1, Q2);
            if (decizie == 1)
            {
                ceas+=Dis;
                if(n1>0){
                    Q1[1].Tp1-=Dis;
                    // Q1[1].Tp2-=Dis;
                }
                if(n2>0){
                    Q2[1].Tp2-=Dis;
                    // Q2[1].Tp1-=Dis;
                }
                Tp[1] = genExp(miu), Tp[2] = genExp(miu);
                // Tp[1] = genGauss(1/miu,sigma), Tp[2] = genGauss(1/miu,sigma);
                if(n1<=n2){
                    n1++;
                    Q1[n1].MS=ceas;
                    Q1[n1].Tp1=Tp[1];
                    Q1[n1].Tp2=Tp[2];
                }else
                {
                    n2++;
                    Q2[n2].MS=ceas;
                    Q2[n2].Tp1=Tp[1];
                    Q2[n2].Tp2=Tp[2];
                }
                Dis=genExp(lambda);
            }
            else if (decizie == 2)
            {
                //
                ceas+=Q1[1].Tp1;
                Q2[1].Tp2-=Q1[1].Tp1;
                Dis-=Q1[1].Tp1;
                //

                STR+=ceas-Q1[1].MS;
                CT++;
                
                //
                n1--;
                if(n1!=0){
                    for(int i=1;i<=n1;i++){
                        Q1[i]=Q1[i+1];
                    }
                }
                //
            }
            else if (decizie == 3)
            {
                //
                ceas+=Q2[1].Tp2;
                Q1[1].Tp1-=Q2[1].Tp2;
                Dis-=Q2[1].Tp2;
                //

                STR+=ceas-Q2[1].MS;
                CT++;

                //
                n2--;
                if(n2!=0){
                    for(int i=1;i<=n2;i++){
                        Q2[i]=Q2[i+1];
                    }
                }
                //                
            }
            else if (decizie == 4)
            {
                //
                ceas+=Q1[1].Tp1;
                Q2[1].Tp2-=Q1[1].Tp1;
                Dis-=Q1[1].Tp1;
                //
                Q1[1].Tp1=0;
                n2++;
                Q2[n2]=Q1[1];

                //
                n1--;
                if(n1!=0){
                    for(int i=1;i<=n1;i++){
                        Q1[i]=Q1[i+1];
                    }
                }
                //
            }
            else if (decizie == 5)
            {
                ceas+=Q2[1].Tp2;
                Q1[1].Tp1-=Q2[1].Tp2;
                Dis-=Q2[1].Tp2;

                Q2[1].Tp2=0;
                n1++;
                Q1[n1]=Q2[1];

                
                //
                n2--;
                if(n2!=0){
                    for(int i=1;i<=n2;i++){
                        Q2[i]=Q2[i+1];
                    }
                }
                //
            }
            else
            {
                //
            }
        } while (ceas < DS);
        cout<<"lambda:"<<lambda<<",TRm="<<STR/NS<<endl;
    }

    return 0;
}