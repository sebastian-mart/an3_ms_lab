#include <iostream>
#include <math.h>
#include <assert.h>

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
    u = (double)random() / RAND_MAX;
    x = -1 / lambda * log(1 - u);
    return x;
}

int main()
{
    int C = 300;
    double lambda, miu = 10, DS, sigma = 0.01;
    int nmax = 0;
    int sumn = 0, el = 0;
    int nmediu;
    int x;
    std::cout << "0:Exp1(exp)\torice altceva:Exp2(normala):";
    cin >> x;
    for (lambda = 4; lambda <= 9; lambda++)
    {
        DS = 1000000 / lambda;
        double STS = 0, ceas = 0;
        double CT = 0, CR = 0;
        int n = 1;
        nmediu = 0;
        double Q[C + 1];
        Q[1] = ceas;
        double Tp, Tsu;
        if (x == 0)
        {
            // schimbi la 2 gentp
            Tp = genExp(miu);
            //-------------
            // si aici gendis
            Tsu = genExp(lambda);
        }
        else
        {
            Tsu = genExp(lambda);
            Tp = genGauss(1 / miu, sigma);
        }
        //
        do
        {
            if (n == 0)
            {
                ceas += Tsu;
                n = 1;
                Q[1] = ceas;
                // gentp
                if (x == 0)
                    Tp = genExp(miu);
                else
                    Tp = genGauss(1 / miu, sigma);
            }
            else if (n > 0)
            {
                if (Tsu < Tp)
                {
                    ceas += Tsu;
                    Tp -= Tsu;
                    if (n == C)
                    {
                        CR++;
                    }
                    else if (n < C)
                    {
                        n++;
                        Q[n] = ceas;
                    }
                    // gendis
                    Tsu = genExp(lambda);
                }
                else if (Tp <= Tsu)
                {
                    ceas += Tp;
                    Tsu -= Tp;
                    STS += ceas - Q[1];
                    CT++;
                    if (n > 0)
                    {
                        for (int i = 2; i < n; i++)
                        {
                            Q[i - 1] = Q[i];
                        }
                        // gentp
                        if (x == 0)
                            Tp = genExp(miu);
                        else
                            Tp = genGauss(1 / miu, sigma);
                    }
                    n--;
                }
            }
            else
                assert(1 == 0);
            if (nmax < n)
            {
                nmax = n;
            }
            sumn += n;
            el++;

        } while (ceas < DS);
        double Tsm = STS / CT, Pcr = (CR / (CT + CR + n)) * 100;
        nmediu = sumn / el;
        std::cout << "\nlambda=" << lambda << ";TSm=" << Tsm << ";Pcr=" << Pcr << ";nmax:" << nmax << ";nmediu:" << nmediu << endl;
    }
}