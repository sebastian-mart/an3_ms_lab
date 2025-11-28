#include <iostream>
#include<random>
#include<math.h>
#include <cfloat>
using namespace std;
#define L 0
#define O 1
double genExp(double lambda)
{
    double u, x;
    u = (double)rand() / RAND_MAX;
    x = (-1) / lambda * log(1 - u);
    return x;
}

int main()
{
    int S = 3;
    double miu = 10;
    double STp[4], CT[4], ST[4];
    double Q[300];
    double Tp[4];
    for (int lambda = 15; lambda <= 29; lambda = lambda + 2)
    {
        double STa = 0;
        if (lambda == 29)
            lambda--;
        double DS = 1000000 / (double)lambda;
        int m = 0, s = 0;
        double Sq = 0;
        for (int j = 1; j <= S; j++)
        {
            STp[j] = 0;
            CT[j] = 0;
            ST[j] = L;
        }
        double ceas = 0;
        int q = 0;
        double Tsu = genExp(lambda);
        do
        {
            if (ST[1] == L && ST[2] == L && ST[3] == L)
            {
                ceas += Tsu;
                m = rand() % 3 + 1;
                ST[m] = O;
                Tp[m] = genExp(miu);
                STp[m] += Tp[m];
                Tsu = genExp(lambda);
            }
            else if (Tsu < Tp[s])
            {
                ceas += Tsu;
                for (int j = 1; j <= S; j++)
                {
                    if (ST[j] == O)
                        Tp[j] -= Tsu;
                }
                if (ST[1] == L || ST[2] == L || ST[3] == L)
                {
                    if (ST[1] == L)
                        m = 1;
                    else if (ST[2] == L)
                        m = 2;
                    else if (ST[3] == L)
                        m = 3;
                    ST[m] = O;
                    Tp[m] = genExp(miu);
                    STp[m] += Tp[m];
                }
                else
                {
                    Sq += q;
                    q++;
                    Q[q] = ceas;
                }
                Tsu = genExp(lambda);
            }
            else if (Tp[s] <= Tsu)
            {
                ceas += Tp[s];
                Tsu -= Tp[s];
                for (int j = 1; j <= S; j++)
                    if (ST[j] == O && j != s)
                        Tp[j] -= Tp[s];
                Tp[s] = 0;
                CT[s]++;
                if (q == 0)
                    ST[s] = L;
                else if (q > 0)
                {
                    STa += ceas - Q[1];
                    Tp[s] = genExp(miu);
                    STp[s] += Tp[s];
                    q--;
                    for (int i = 1; i <= q; i++)
                        Q[i] = Q[i + 1];
                }
            }
            double min = DBL_MAX;
            for (int j = 1; j <= S; j++)
            {
                if (ST[j] == O && Tp[j] < min)
                {
                    min = Tp[j];
                    s = j;
                }
            }
            Tp[s] = min;
        } while (ceas < DS);
        double sumSTp = 0, sumCT = 0,Osm=0;
        double Oc[4]{0};
        cout << "\nlambda: " << lambda << ";";
        for (int j = 1; j <= S; j++)
        {
            sumSTp += STp[j];
            sumCT += CT[j];
            Oc[j]=STp[j]/DS;
        }
        double Tsm = (double)(STa + sumSTp) / sumCT;
        double qm = (double)Sq / (DS * lambda);
        cout << "Tsm: " << Tsm << ";";
        cout << "qm: " << qm << ";";
        for (int j = 1; j <= S; j++)
        {
            std::cout<<"Oc["<<j<<"]:"<<Oc[j]<<';';
        }
    }

    return 0;
}