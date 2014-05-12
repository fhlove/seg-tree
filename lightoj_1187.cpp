/*************************************************************************
    > File Name: lightoj_1183.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月10日 星期二 21时52分55秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<set>
#include<map>
#include<algorithm>
#include<vector>
#include<cstring>
#include<string>
#include<bitset>
using namespace std;
typedef long long ll;
#define lson l,m,rt<<1
#define rosn m+1,r,rt<<1|1
const int N=100005;
int h[N];
int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int n,m;
	int c=1;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&h[i]);
		int ans=1;
		for(int i=n;i>=1;i--)
		{
			if(h[i]==i-1)
			{
				ans=i;
				break;
			}
		}
		printf("Case %d: %d\n",c++,ans);
	}
	return 0;
}
