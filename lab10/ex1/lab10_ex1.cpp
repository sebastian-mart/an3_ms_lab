#include <iostream>
#include <random>
#include <math.h>
#include <cstdlib>
#include <cfloat>
using namespace std;

int alegeremprobab(double p[4])
{
    int m = 3;
    double u = (double)rand() / RAND_MAX;
    if (u < p[1])
        m = 1;
    else if (u < p[1] + p[2])
        m = 2;
    else
        m = 3;
    return m;
}

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


int alegeMDet(int n[4], int miu[4])
{
    int min = n[1];
    int index = 1;
    for (int i = 2; i <= 3; i++)
        if (min > n[i])
        {
            min = n[i];
            index = i;
        }
    int max = miu[1];

    for (int i = 2; i <= 3; i++)
        if (miu[i] > max && n[i] == min)
        {
            max = miu[i];
            index = i;
        }

    return index;
}

int main()
{
    int alegere =0;
    int lambda = 25;
    double sigma=0.02;
    int miu[4] = {};
    int NS = pow(10, 6);
    int S = 3;
    double STS[4], STp[4], CT[4];
    int n[4];
    double Q[4][512];
    for (int i = 1; i <= S; i++)
    {
        STS[i] = 0;
        STp[i] = 0;
        CT[i] = 0;
        n[i] = 0;
        miu[i] = i + 8;
    }
    double ceas = 0;
    int m = alegeMDet(n, miu);
    // int m=rand()%3+1;


    // double p[4]{0};
    // double sumMiu = miu[1] + miu[2] + miu[3];
    // p[1] =  miu[1] / sumMiu;
    // p[2] =  miu[2]/ sumMiu;
    // p[3] =  miu[3] / sumMiu;
    // int m= alegeremprobab(p);
    // while(alegere<2)

    n[m] = 1;
    Q[m][1] = 0;
    int s = m;
    double Tp[4];
    Tp[m] = genExp(miu[m]);
    STp[m] += Tp[m];
    double Tsu = genExp(lambda);
    do
    {
        if ((n[1] == 0 && n[2] == 0 && n[3] == 0) || Tsu < Tp[s])
        {
            ceas += Tsu;
            for (int i = 1; i <= S; i++)
                if (n[i] > 0)
                    Tp[i] -= Tsu;
            m = alegeMDet(n, miu);
            // m=rand()%3+1;
            // m= alegeremprobab(p);

            n[m]++;
            Q[m][n[m]] = ceas;
            if (n[m] == 1)
            {
                Tp[m] = genExp(miu[m]);
                STp[m] += Tp[m];
            }
            Tsu = genExp(lambda);
        }
        else if (Tp[s] <= Tsu)
        {
            ceas += Tp[s];
            Tsu -= Tp[s];
            for (int i = 1; i <= S; i++)
                if (n[i] > 0 && i != s)
                    Tp[i] -= Tp[s];
            Tp[s] = 0;
            n[s]--;
            STS[s] += ceas - Q[s][1];
            CT[s]++;
            if (n[s] > 0)
            {
                for (int i = 1; i <= n[s]; i++)
                    Q[s][i] = Q[s][i + 1];
                Tp[s] = genExp(miu[s]);
                STp[s] += Tp[s];
            }
        }
        double min = 999999;
        for (int i = 1; i <= S; i++)
            if (n[i] > 0 && Tp[i] < min)
            {
                s = i;
                min = Tp[i];
            }
    } while (ceas < NS);
    double sumSTS = 0, sumCT = 0;
    
    for (int i = 1; i <= S; i++)
    {
        sumSTS += STS[i];
        sumCT += CT[i];
    }
    double TSmg = (double)sumSTS / sumCT;
    cout << "TSmg: " << TSmg << "\n";
    double O[4], Og = 0;
    for (int i = 1; i <= S; i++)
    {
        O[i] = (double)STp[i] / NS * 100;
        Og += O[i];
        cout << "O[" << i << "]: " << O[i] << "\n";
    }
    Og = (double)Og / 3;
    cout << "Og: " << Og;

    return 0;
}
















// #include <iostream>
// #include <math.h>
// #include <random>
// using namespace std;

// double genGauss(double medie, double sigma)
// {
//     double s = 0;
//     int i;
//     for (i = 1; i <= 12; i++)
//         s += (double)rand() / RAND_MAX;
//     return medie + sigma * (s - 6);
// }

// double genExp(double lambda)
// {
//     double u, x;
//     u = (double)rand() / RAND_MAX;
//     x = (-1) / lambda * log(1 - u);
//     return x;
// }

// int alegeremprobab(double p[4])
// {
//     int m = 3;
//     double u = (double)rand() / RAND_MAX;
//     if (u < p[1])
//         m = 1;
//     else if (u < p[1] + p[2])
//         m = 2;
//     else
//         m = 3;
//     return m;
// }

// int verif(int n[4])
// {
//     for (int i = 1; i <= 3; i++)
//     {
//         if (n[i] != 0)
//         {
//             return 0;
//         }
//     }
//     return 1;
// }

// int main()
// {
//     // int alegere;
//     // cout << "Alegere m:1->determinist,2->aleator,3->probabilitati:";
//     // std::cin >> alegere;
//     // std::cout<<alegere;
//     int minQ;
//     double maxMiu;
//     int alegere = 1;
//     double miu1 = 9, miu2 = 10, miu3 = 11, lambda = 25, DS = 1000000 / lambda;
//     // caz probabilitati
//     double p[4]{0};
//     double sumMiu = miu1 + miu2 + miu3;
//     p[1] = miu1 / sumMiu;
//     p[2] = miu2 / sumMiu;
//     p[3] = miu3 / sumMiu;
//     ///
//     int S = 3;
//     double miu[S + 1]{0, miu1, miu2, miu3};
//     double STS[S + 1]{0}, STp[S + 1]{0}, Tp[S + 1]{0}, CT[S + 1]{0};
//     double Q[S + 1][3000]{0};
//     int m=1;
//     int n[S + 1]{0};
//     for(int i=0;i<=4;i++){
//         n[i]=0;
//     }
//     double ceas = 0, Tsu;
//     int s;
//     // alegere m
//     switch (alegere)
//     {
//     case 1:
//         cout<<n[3];
//         minQ = 1;
//         maxMiu = miu1;
//         for (int i = 2; i <= 3; i++)
//         {
//             if (n[minQ] > n[i])
//             {
//                 minQ = i;
//                 maxMiu = miu[i];
//             }
//             else if (n[minQ] == n[i])
//             {
//                 if (maxMiu < miu[i])
//                 {
//                     minQ = i;
//                     maxMiu = miu[i];
//                 }
//             }
//         }
//         m = minQ;
//         cout << "caz1";
//         break;
//     case 2:
//         m = (rand() % 3) + 1;
//         break;
//     case 3:
//         m = alegeremprobab(p);
//         break;
//     default:
//         break;
//     }

//     Q[m][1] = 0;
//     n[m] = 1;
//     s = m;
//     Tp[m] = genExp(miu[m]);
//     STp[m] += Tp[m];
//     Tsu = genExp(lambda);
//     do
//     {
//         if (verif(n) || Tsu < Tp[s])
//         {
//             ceas += Tsu;
//             for (int i = 1; i <= S; i++)
//             {
//                 if (n[i] > 0)
//                 {
//                     Tp[i] = std::max(0.0, Tp[i] - Tsu);
//                 }
//             }
//             // alegere m
//             switch (alegere)
//             {
//                 case 1:
//                     minQ = 1;
//                     maxMiu = miu1;
//                     for (int i = 2; i <= 3; i++)
//                     {
//                         if (n[minQ] > n[i])
//                         {
//                             minQ = i;
//                             maxMiu = miu[i];
//                         }
//                         else if (n[minQ] == n[i])
//                         {
//                             if (maxMiu < miu[i])
//                             {
//                                 minQ = i;
//                                 maxMiu = miu[i];
//                             }
//                         }
//                     }
//                     m = minQ;
//                     break;
//                 case 2:
//                     m = (rand() % 3) + 1;
//                     break;
//                 case 3:
//                     m = alegeremprobab(p);
//                     break;
//                 default:
//                     break;
//             }

//             n[m]++;
//             Q[m][n[m]] = ceas;
//             if (n[m] == 1)
//             {
//                 Tp[m] = genExp(miu[m]);
//                 STp[m] += Tp[m];
//             }
//             Tsu = genExp(lambda);
//         }
//         else if (Tp[s] <= Tsu)
//         {
//             ceas += Tp[s];
//             Tsu -= Tp[s];
//             for (int i = 1; i <= S; i++)
//             {
//                 if (n[i] > 0 && i != s)
//                 {
//                     Tp[i] = std::max(0.0, Tp[i] - Tp[s]);
//                 }
//             }
//             Tp[s] = 0;
//             n[s]--;
//             STS[s] += ceas - Q[s][1];
//             CT[s]++;
//             if (n[s] > 0)
//             {
//                 for (int i = 1; i <= n[s]; i++)
//                 {
//                     Q[s][i] = Q[s][i + 1];
//                 }
//                 Tp[s] = genExp(miu[s]);
//                 STp[s] += Tp[s];
//             }
//         }
//         s = 0;
//         int min = -1;
//         for (int i = 1; i <= S; i++)
//         {
//             if (n[i] > 0)
//             {
//                 if (min == -1)
//                 {
//                     s = i;
//                 }
//                 else if (Tp[i] < Tp[s])
//                 {
//                     s = i;
//                 }
//             }
//         }

//     } while (ceas < DS);
//     double TSm = 0, sumSTS = 0, sumCT = 0, O[S + 1]{0};
//     for (int i = 1; i <= S; i++)
//     {
//         sumSTS += STS[i];
//         sumCT += CT[i];
//         O[i] = (STp[i] / DS) * 100;
//         std::cout << "O[" << i << "]:" << O[i] << ";";
//     }
//     TSm = sumSTS / sumCT;
//     std::cout << "Tsm:" << TSm << endl;

//     return 0;
// }
