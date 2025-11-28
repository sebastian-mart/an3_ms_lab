#include <iostream>
#include <math.h>
#include <random>

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
int minimDis(double Dis[])
{
    int k=1;
    for (int j = 1; j <= 3; j++)
    {
        if (Dis[k] > Dis[j])
        {
            k = j;
        }
    }

    return k;
}

int main()
{
    double m1 = 0.5, s1 = 0.05, m2 = 2, m3 = 5;
    double lambda1 = 0.5, lambda2 = 0.1, lambda3 = 0.03, DS = 1000000 / (lambda1 + lambda2 + lambda3);
    double STR[4]{0}, CT[4]{0}, Dis[4]{0}, Tp[4]{0}, Tsu;
    int  n[4]{0}, c = 0, k;
    double ceas = 0,Q[4][512]{0};
    for (int j = 1; j < 4; j++)
    {
        switch (j)
        {
        case 1:
            Dis[j] = genExp(lambda1);
            break;
        case 2:
            Dis[j] = genExp(lambda2);
            break;
        case 3:
            Dis[j] = genExp(lambda3);
            break;
        }
    }
    k = minimDis(Dis);
    Tsu = Dis[k];

    for (int j = 1; j <= 3; j++)
    {
        Dis[j] -= Tsu;
    }
    do
    {
        if (c)
        {
            if (Tsu < Tp[c])
            {
                ceas += Tsu;
                Tp[c] -= Tsu;
                n[k]++;
                Q[k][n[k]] = ceas;
                //parte specifica varianta 3
                if(k>c){
                    c=k;
                    switch (c)
                    {
                    case 1:
                        Tp[c] = genGauss(m1, s1);
                        break;
                    case 2:
                        Tp[c] = genExp(1 / m2);
                        break;
                    case 3:
                        Tp[c] = genExp(1 / m3);
                        break;
                    }
                }

                //end
                switch (k)
                {
                case 1:
                    Dis[k] = genExp(lambda1);
                    break;
                case 2:
                    Dis[k] = genExp(lambda2);
                    break;
                case 3:
                    Dis[k] = genExp(lambda3);
                    break;
                }
                k = minimDis(Dis);
                Tsu = Dis[k];

                for (int j = 1; j <= 3; j++)
                {
                    Dis[j] -= Tsu;
                }
            }
            else if (Tp[c] <= Tsu)
            {
                ceas += Tp[c];
                Tsu -= Tp[c];
                STR[c] += ceas - Q[c][1];
                CT[c]++;
                Tp[c]=0;
                if (n[c] > 0)
                    for (int i = 1; i <= n[c] - 1; i++)
                    {
                        Q[c][i] = Q[c][i + 1];
                    }
                n[c]--;
                c = 0;
                if (n[3] > 0)
                {
                    c = 3;
                }
                else if (n[2] > 0)
                {
                    c = 2;
                }
                else if (n[1] > 0)
                {
                    c = 1;
                }
                if (c > 0 && Tp[c] == 0)
                {
                    switch (c)
                    {
                    case 1:
                        Tp[c] = genGauss(m1, s1);
                        break;
                    case 2:
                        Tp[c] = genExp(1 / m2);
                        break;
                    case 3:
                        Tp[c] = genExp(1 / m3);
                        break;
                    }
                }
            }
        }
        else if(c==0)
        {
            ceas += Tsu;
            n[k] = 1;
            Q[k][1] = ceas;
            c = k;
            switch (c)
            {
            case 1:
                Tp[c] = genGauss(m1, s1);
                break;
            case 2:
                Tp[c] = genExp(1 / m2);
                break;
            case 3:
                Tp[c] = genExp(1 / m3);
                break;
            }
            switch (k)
            {
            case 1:
                Dis[k] = genExp(lambda1);
                break;
            case 2:
                Dis[k] = genExp(lambda2);
                break;
            case 3:
                Dis[k] = genExp(lambda3);
                break;
            }
            k = minimDis(Dis);
            Tsu = Dis[k];

            for (int j = 1; j <= 3; j++)
            {
                Dis[j] -= Tsu;
            }
        }

    } while (ceas < DS);
    double TR[4],TRm,sumSTR=0,sumCT=0;
    for(int j=1;j<=3;j++){
        TR[j]=STR[j]/CT[j];
        cout<<"TR["<<j<<"]:"<<TR[j]<<"\n";
        sumCT+=CT[j];
        sumSTR+=STR[j];
    }
    TRm=sumSTR/sumCT;
    cout<<"TRm:"<<TRm<<endl;
    
}