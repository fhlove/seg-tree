/*************************************************************************
    > File Name: ligthoj_1097.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月07日 星期六 15时48分13秒
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
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int N=1500000;
int sum[N<<2];
void push_up(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		if(l%2==0) sum[rt]=0;
		else sum[rt]=1;
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	push_up(rt);
}
void update(int l,int r,int rt,int sr)
{
	if(l==r)
	{
		sum[rt]=0;
		return;
	}
	int m=(l+r)>>1;
	if(sum[rt<<1]>=sr) update(lson,sr);
	else update(rson,sr-sum[rt<<1]);
	push_up(rt);
}
int query(int l,int r,int rt,int sr)
{
	if(l==r) return l;
	int m=(l+r)>>1;
	int res=-1;
	if(sum[rt<<1]>=sr) res=query(lson,sr);
	else res=query(rson,sr-sum[rt<<1]);
	return res;
}
void solve()
{
	memset(sum,0,sizeof(sum));
	build(1,N,1);
	for(int i=2;i<N;i++)
	{
		int x=query(1,N,1,i);
		if(x==-1) break;
		for(int j=sum[1]/(x);j>=1;j--)
		{
			update(1,N,1,j*(x));
		}
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int n;
	solve();
	scanf("%d",&t);
	for(int c=1;c<=t;c++)
	{
		scanf("%d",&n);
		int ans=query(1,N,1,n);
		printf("Case %d: %d\n",c,ans);
	}
	return 0;
}
