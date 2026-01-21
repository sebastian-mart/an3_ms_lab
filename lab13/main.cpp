#include<math.h>
#include<iostream>
using namespace std;

double genExp(double lambda)
{
    double u, x;
    u = (double)rand() / RAND_MAX;
    x = (-1) / lambda * log(1 - u);
    return x;
}
int lambda=9;
int miu1=10,miu2=miu1,miu3=miu1;
//7 tranz
//8 procese
static double D[7]={0,-1,-1,-1,-1,-1,-1};
int C=300;
static int M[8]={C,0,0,0,0,1,1,1};

static int I[8][7]={
    1,0,0,0,0,0,0,
    0,1,1,1,0,0,0,
    0,0,0,0,1,0,0,
    0,0,0,0,0,1,0,
    0,0,0,0,0,0,1,
    0,1,0,0,0,0,0,
    0,0,1,0,0,0,0,
    0,0,0,1,0,0,0
};
static int O[7][8]={
    0,1,0,0,0,0,0,0,
    0,0,1,0,0,0,0,0,
    0,0,0,1,0,0,0,0,
    0,0,0,0,1,0,0,0,
    1,0,0,0,0,1,0,0,
    1,0,0,0,0,0,1,0,
    1,0,0,0,0,0,0,1
};
static double pas=0;

int np=8;
int nt=7;
static double STS = 0; 
static double CT=0;
static double Q[300] = {0};
static double ceas=0;

void ExecutaTranzitie(int te)
{
    int t,p,ex,i;
    //actualizare marcaj
    for(p=0;p<np;p++){
        M[p]=M[p]-I[p][te]+O[te][p];
    }
    //actualizare D
    for(t=0;t<nt;t++){
        //verif daca tr e exec in noua stare M
        ex=1;
        for(p=0;p<np;p++){if(M[p]<I[p][t]){ex=0; break;}}
        //act D[t]
        if(ex==0) D[t]=-1;
        else if(D[t]==-1 || t==te){
            if(t>=1 && t<=3) D[t]=0;
            else{
                switch(t){
                    case 0:D[t]=genExp(lambda);
                        break;
                    case 4:D[t]=genExp(miu1);
                        break;
                    case 5:D[t]=genExp(miu2);
                        break;
                    case 6:D[t]=genExp(miu3);
                    break;
                }
            }
        }else{ 
            D[t]=D[t]-pas;
            if(D[t] < 0) D[t] = -1;
        }//actualizare durata d[t]
    }
    if(te==0){
        if(M[1] < 300)
            Q[M[1]] = ceas;
    }else if(te>=1 && te<=3){
        STS=STS+ceas-Q[1]+D[te+3];
        for(int i=0;i<M[1]-1;i++){
            Q[i]=Q[i+1];
        }
    }
    else if(te>=4 && te<=6){
        CT++;
    }
}

int main(){
    miu1=miu2=miu3=10;
    for(lambda=15;lambda<=29;lambda+=2){
        ceas=0;
        STS=0;
        for(int i=0;i<300;i++)
            Q[i]=0;
        for(int i=0;i<nt;i++)
            D[i] = -1;
        D[0] = 0;
        M[0]=C; M[1]=0; M[2]=0; M[3]=0;
        M[4]=0; M[5]=1; M[6]=1; M[7]=1;


        CT=0;
        double DS=1000000/(double)lambda;
        do{
            int te=0;
            pas=100000000;
            for(int i=0;i<nt;i++){
                if(D[i]>=0){
                    if(D[i]<pas){
                        te=i;
                        pas=D[i];
                    }
                }
            }
            ceas+=pas;
            ExecutaTranzitie(te);
        }while(ceas<DS);
        cout<<"lambda="<<lambda<<";TSm="<<STS/CT<<"\n";
    }
    
}

