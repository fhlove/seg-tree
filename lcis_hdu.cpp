/*************************************************************************
    > File Name: lcis_hdu.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月03日 星期二 21时45分18秒
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
const int N=100005;
int lsum[N<<2],rsum[N<<2],sum[N];
int num[N];
void push_up(int rt,int l,int r)
{
	lsum[rt]=lsum[rt<<1];
	rsum[rt]=rsum[rt<<1|1];
	sum[rt]=max(sum[rt<<1],sum[rt<<1|1]);
	int m=(l+r)>>1;
	int dis=r-l+1;
	if(num[m+1]>num[m])
	{
		if(lsum[rt]==(dis-dis/2)) lsum[rt]+=lsum[rt<<1|1];
		if(rsum[rt]==dis/2) rsum[rt]+=rsum[rt<<1];
		sum[rt]=max(sum[rt],lsum[rt<<1|1]+rsum[rt<<1]);
	}
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		lsum[rt]=rsum[rt]=sum[rt]=1;
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	push_up(rt,l,r);
}
void update(int l,int r,int rt,int id,int sr)
{
	if(l==r)
	{
		num[l]=sr;
		return;
	}
	int m=(l+r)>>1;
	if(m>=id) update(lson,id,sr);
	else if(m<id) update(rson,id,sr);
	push_up(rt,l,r);
}
int query(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		return sum[rt];
	}
	int ans=0;
	int m=(l+r)>>1;
	if(m>=R) ans=query(lson,L,R);
	else if(m<L) ans=query(rson,L,R);
	else {
		ans=max(ans,query(lson,L,R));
		ans=max(ans,query(rson,L,R));
		if(num[m+1]>num[m])
		{
			int temp=min(lsum[rt<<1|1],R-m)+min(rsum[rt<<1],m-L+1);
			ans=max(ans,temp);
		}
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int n,m;
	char op[5];
	int x,y;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",&num[i]);
		build(1,n,1);
		while(m--)
		{
			scanf("%s%d%d",op,&x,&y);
			if(op[0]=='U') update(1,n,1,x,y);
			else {
				int ans=query(1,n,1,x,y);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
