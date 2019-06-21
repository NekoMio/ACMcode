#include<cstdio>
#include<cstring>
namespace WorkSpace{
    class function{
    public:
        double pow(double a,int k){
            double ans=1;
            while(k){
                if(k&1) ans*=a;
                k>>=1;
                a*=a;
            }
            return ans;
        }
    }F;
    struct InPut{
        int K,W,H;
    }Read;
    double Probability[1005][1005];
    class Main{
    public:
        Main(){
            scanf("%d%d%d",&Read.K,&Read.W,&Read.H);
            int All=Read.W*Read.H;
            double ans=0;
            for(int i=1;i<=Read.W;i++){
                for(int j=1;j<=Read.H;j++){
                    Probability[i][j]+=
                        (double)2*((j-1)*(i-1)/All)*(double)(Read.H-j)*(Read.W-i)/All+
                        (double)2*((j-1)*(Read.W-i)/All)*(double)((Read.H-j)*(i-1))/All+
                        (double)2*(j-1)/All*(double)(Read.H-j)/All+
                        (double)2*(i-1)/All*(double)(Read.W-i)/All+
                        (double)1/All;
                    ans+=(double)1-F.pow((1-Probability[i][j]),Read.K);
                }
            }
            printf("%.0lf",ans);
        }
    }Run;
}
int main(){;}