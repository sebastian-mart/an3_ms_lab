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
    u = (double)random() / RAND_MAX;
    x = -1 / lambda * log(1 - u);
    return x;
}

int main()
{
    double m1 = 0.5, s1 = 0.05, m2 = 2, m3 = 5;
    double lambda1 = 0.5, lambda2 = 0.1, lambda3 = 0.03, NS = 1000000;
    double STR[4]{0}, CT[4]{0}, Dis[4]{0};
    int i = 1;
    double Ta = 0, dis;
    int k;
    double lambda = lambda1 + lambda2 + lambda3;
    int x;
    double Tp;
    cout << "1:fifo, 2:1-3";
    cin >> x;



    //verificare pentru fiecare tip
    switch (x)
    {
    case 1:
        k = 1;
        break;
    case 2:
        dis = genExp(lambda); // durata între 2 cereri, indiferent de tipul lor
        double u = (double)rand() / RAND_MAX;
        double p[4]{};
        p[1] = lambda1 / lambda;
        p[2] = lambda2 / lambda;
        p[3] = lambda3 / lambda;
        if (u < p[1])
            k = 1;
        else if (u < (p[1] + p[2]))
            k = 2;
        else
            k = 3; // aflarea tipului cererii, ţinând cont de faptul că
                   // Pj este probabilitatea ca cererea să fie de tip j;
        break;
    }



    for (int j = 1; j <= 3; j++)
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

    do
    {
        switch (k)
        {
        case 1:
            Tp = genGauss(m1, s1);
            break;
        case 2:
            Tp = genExp(1 / m2);
            break;
        case 3:
            Tp = genExp(1 / m3);
            break;
        }
        STR[k] += Ta + Tp;
        CT[k]++;






        //verificare pentru fiecare tip
        switch (x)
        {
        case 1:
            for (int j = 1; j <= 3; j++)
            {
                if (Dis[k] > Dis[j])
                {
                    k = j;
                }
            }

            dis = Dis[k];

            for (int j = 1; j <= 3; j++)
            {
                Dis[j] -= dis;
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
            break;
        case 2:
            dis = genExp(lambda); // durata între 2 cereri, indiferent de tipul lor
            double u = (double)rand() / RAND_MAX;
            double p[4]{};
            p[1] = lambda1 / lambda;
            p[2] = lambda2 / lambda;
            p[3] = lambda3 / lambda;
            if (u < p[1])
                k = 1;
            else if (u < (p[1] + p[2]))
                k = 2;
            else
                k = 3; // aflarea tipului cererii, ţinând cont de faptul că
                       // Pj este probabilitatea ca cererea să fie de tip j;
            break;
        }





        if (dis < Ta + Tp)
        {
            Ta = Ta + Tp - dis;
        }
        else
        {
            Ta = 0;
        }
        i++;
    } while (i <= NS);

    double TR[4], TRm, sumaux = 0;
    for (int j = 1; j <= 3; j++)
    {
        TR[j] = STR[j] / CT[j];
        cout << "TR[" << j << "]:" << TR[j] << ",";
        sumaux += STR[j];
    }
    TRm = sumaux / NS;
    cout << "TRm:" << TRm << endl;

    return 0;
}
