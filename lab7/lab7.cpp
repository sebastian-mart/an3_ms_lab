#include <iostream>
#include <math.h>
using namespace std;

struct s
{
    double MS, Tp;
};
double m1 = 0.5, s1 = 0.05, m2 = 2, m3 = 5;
double lambda1 = 0.5, lambda2 = 0.1, lambda3 = 0.03;

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
    u = (double)random() / RAND_MAX;
    x = -1 / lambda * log(1 - u);
    return x;
}
double genTp(double p[])
{
    double u = (double)rand() / RAND_MAX;
    int k=1;
    if (u < p[1])
        k = 1;
    else if (u < (p[1] + p[2]))
        k = 2;
    else
        k = 3;
    switch (k)
    {
    case 1:
        return genGauss(m1, s1);
        break;
    case 2:
        return genExp(1 / m2);
        break;
    default:
        return genExp(1 / m3);
        break;
    }
}

int main()
{
    
    double C;
    double Coptim,TrmOptim=100000;
    for(C=0.2;C<=2;C+=0.1)
    {
        double NS = 1000000;
        double lambda =(double) lambda1 + lambda2 + lambda3;
        double DS = (double)NS / lambda;
        double STR = 0, CT = 0, ceas = 0;
        double p[4];
        
        p[1] = lambda1 / lambda;
        p[2] = lambda2 / lambda;
        p[3] = lambda3 / lambda;
        int n = 1;
        s Q[300] = {0};
        Q[1].MS = ceas;
        Q[1].Tp = genTp(p);
        double Tsu = genExp(lambda);
        double ca;
        // alocare cuanta ca
        if (Q[1].Tp < C)
        {
            ca = Q[1].Tp;
        }
        else
        {
            ca = C;
        }
        Q[1].Tp -= ca;
        /////
        do
        {
            if (n == 0)
            {
                ceas += Tsu;
                n = 1;
                Q[n].MS = ceas;
                Q[n].Tp = genTp(p);
                ///
                if (Q[1].Tp < C)
                {
                    ca = Q[1].Tp;
                }
                else
                {
                    ca = C;
                }
                Q[1].Tp -= ca;
                ///
                Tsu=genExp(lambda);
            }
            else if (Tsu < ca && n>0)
            {
                ceas += Tsu;
                ca -= Tsu;
                n++;
                Q[n].MS = ceas;
                Q[n].Tp = genTp(p);
                Tsu = genExp(lambda);
            }
            else if (Tsu >= ca && n>0)
            {
                ceas += ca;
                Tsu -= ca;
                if (Q[1].Tp > 0)
                {
                    Q[n + 1] = Q[1];
                }
                else if (Q[1].Tp == 0)
                {
                    n--;
                    CT++;
                    STR += ceas - Q[1].MS;
                }
                if (n>0)
                {
                    for (int i = 1; i <= n; i++)
                    {
                        Q[i] = Q[i + 1];
                    }
                    //alocare cuanta
                    if (Q[1].Tp < C)
                    {
                        ca = Q[1].Tp;
                    }
                    else
                    {
                        ca = C;
                    }
                    Q[1].Tp -= ca;
                    ////
                }
            }

        } while (ceas < DS);
        double TRm=(double)STR/CT;
        std::cout<<"C="<<C<<",TRm="<<TRm<<endl;
        if(TRm<TrmOptim){
            Coptim=C;
            TrmOptim=TRm;
        }
    }
    cout<<Coptim<<endl<<TrmOptim<<endl;
    
    
    return 0;
}