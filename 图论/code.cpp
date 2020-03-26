#include<bits/stdc++.h>
using namespace std;
//二分
int erfen(int l,int r,int v)
{
    int mid=(l+r)>>1;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(a[mid]==v) return mid;
        else if(a[mid]>v) return erfen(l,mid+1,v);
        else return erfen(mid+1,r,v);
    }
    return -1;
}
//01背包
for(int i=1;i<=n;++i)
  for(int j=m;j>=w[i];j--)
  {
      dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
      maxx=max(dp[j],maxx);
  }
//LIS   使用二分优化
int LIS(int *a,int n)
{
    int dp[n+50];
    int ans=1;
    dp[ans]=a[1];
    for(int i=2;i<=n;++i)
    {
        if(dp[ans]<a[i]) dp[++ans]=a[i];
        else *(lower_bound(dp+1,dp+1+ans,a[i]))=a[i];
    }
}

//LCS
int lena,lenb;
int dp[MAXN][MAXN],flag[maxn][maxn];
void Print(int i,int j)
{
    if(i==0||j==0) return;
    if(!flag[i][j]) 
    {
        Print(i-1,j-1);
        printf("%c",a[i-1]);
    }
    else if(flag[i][j]==-1) Print(i,j-1);
    else Print(i-1,j);
}
int LCS(int a[],int b[])
{
    mem(dp,0);
    for(int i=1;i<=lena;++i)
      for(int j=1;j<=lenb;++j)
      {
          if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1]+1,flag[i][j]=0;
          else if(dp[i-1][j]>dp[i][j-1]) dp[i][j]=dp[i-1][j],flag[i][j]=1;
          else dp[i][j]=dp[i][j-1],flag[i][j]=-1;
      }
    return dp[lena][lenb];
}