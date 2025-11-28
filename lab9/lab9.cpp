#include <iostream>
#include<random>
#include<math.h>
#include <cfloat>
using namespace std;

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
    
    double Q[300];
    double Tp;
    for (int lambda = 15; lambda <= 31; lambda = lambda + 2)
    {
        double STp[4]{0},MT[4]{0};
        int i=1;
        double STa = 0;
        if (lambda == 29)
            lambda--;
        else if(lambda == 30){
            lambda--;
        }
        
        double NS = 1000000;
        double DS = NS / (double)lambda;
        
        int s = 0;
        double MS=0;
        for (i = 1; i <= S; i++)
        {
            Tp=genExp(miu);
            STp[i]+=Tp;
            MT[i]=MS+Tp;
            MS+=genExp(lambda);
        }
        // double Tsu = genExp(lambda);
        do
        {
            //MTmin
            double min=MT[1];
            s=1;
            for (int j = 2; j <= S; j++)
            {
                if (MT[j] < min)
                {
                    min = MT[j];
                    s = j;
                }
            }
            
            if(MS<MT[s])
            {
                STa+=MT[s]-MS;
            }
            else
            {
                MT[s]=MS;
            }
            Tp=genExp(miu);
            STp[s]+=Tp;
            MT[s]+=Tp;
            MS+=genExp(lambda);
            i++;
        } while (i <= NS);



        double sumSTp = 0, Osm=0;
        double Oc[4]{0};
        std::cout << "\nlambda: " << lambda << ";";
        for (int j = 1; j <= S; j++)
        {
            sumSTp += STp[j];
            Oc[j]=(STp[j]/NS)*lambda;
        }

        double Tsm = (double)(STa + sumSTp) / NS;
        
        // double qm = (double)Sq / (DS * lambda);
        std::cout << "Tsm: " << Tsm << ";";
        // std::cout << "qm: " << qm << ";";
        for (int j = 1; j <= S; j++)
        {
            // std::cout<<"Oc["<<j<<"]:"<<Oc[j]<<';';
            Osm+=Oc[j];
        }
        double Oam=(lambda/(miu*3))*100;
        std::cout<<"Oam:"<<Oam<<";";
        std::cout<<"Osm:"<<(Osm/S)*100;
        double ro=lambda/miu;
        double ro_=ro/S;
        double sumron;
        for (int n = 1; n <= S-1; n++)
        {
            double factorial=1;
            for(int j=2;j<=n;j++)
            {
                factorial*=j;
            }
            sumron+=pow(ro,n)/factorial;
        }
        double factorial2=1;
        for(int j=2;j<=S;j++)
        {
            factorial2*=j;
        }
        double p0=pow((1+sumron+(pow(ro,S)/factorial2)*(S/(S-ro))),-1);
        double qma=p0*(pow(S,S)/factorial2)*(pow(ro_,S+1)/pow(1-ro_,2));
        double TSma = (qma/lambda)+(1/miu);
        cout<<";qma"<<qma<<";";
        cout<<";TSma:"<<TSma;

        if(lambda==29)
            break;
        
    }

    return 0;
}