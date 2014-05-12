/*************************************************************************
    > File Name: segment_G_2.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com
    > Created Time: 2013年12月05日 星期四 18时52分31秒
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
int add[N<<2],lsum[N<<2],rsum[N<<2],sum[N<<2],l_n[N<<2],r_n[N<<2];
void push_up(int rt,int l,int r)
{
	l_n[rt]=l_n[rt<<1];
	r_n[rt]=r_n[rt<<1|1];

	lsum[rt]=lsum[rt<<1];
	rsum[rt]=rsum[rt<<1|1];

	sum[rt]=max(sum[rt<<1],sum[rt<<1|1]);
	int dis=r-l+1;
	if(l_n[rt<<1|1]>r_n[rt<<1])
	{
		if(lsum[rt]==(dis-dis/2)) lsum[rt]+=lsum[rt<<1|1];
		if(rsum[rt]==dis/2) rsum[rt]+=rsum[rt<<1];
		sum[rt]=max(sum[rt],lsum[rt<<1|1]+rsum[rt<<1]);
	}
}
void push_down(int rt)
{
	if(add[rt])
	{
		add[rt<<1]+=add[rt];
		add[rt<<1|1]+=add[rt];

		l_n[rt<<1]+=add[rt];
		l_n[rt<<1|1]+=add[rt];

		r_n[rt<<1]+=add[rt];
		r_n[rt<<1|1]+=add[rt];
		add[rt]=0;
	}
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		scanf("%d",&l_n[rt]);
		r_n[rt]=l_n[rt];
		lsum[rt]=rsum[rt]=sum[rt]=1;
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	push_up(rt,l,r);
}
void update(int l,int r,int rt,int L,int R,int sr)
{
	if(l>=L&&R>=r)
	{
		add[rt]+=sr;
		l_n[rt]+=sr;
		r_n[rt]+=sr;
		return;
	}
	push_down(rt);
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R,sr);
	if(m<R) update(rson,L,R,sr);
	push_up(rt,l,r);
}
int query(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		return sum[rt];
	}
	push_down(rt);
	int m=(l+r)>>1;
	int ans=0;
	if(m>=L) ans=max(ans,query(lson,L,R));
	if(m<R) ans=max(ans,query(rson,L,R));
	if(l_n[rt<<1|1]>r_n[rt<<1]&&m>=L&&R>m)
	{
		int temp=min(lsum[rt<<1|1],R-m)+min(rsum[rt<<1],m-L+1);
		ans=max(temp,ans);
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	int n,t,m;
	int x,y,z;
	char op[3];
	scanf("%d",&t);
	for(int c=1;c<=t;c++)
	{
        memset(add,0,sizeof(add));
		scanf("%d%d",&n,&m);
		build(1,n,1);
		printf("Case #%d:\n",c);
		while(m--)
		{
			scanf("%s",op);
			if(op[0]=='a')
			{
				scanf("%d%d%d",&x,&y,&z);
				update(1,n,1,x,y,z);
			}else {
				scanf("%d%d",&x,&y);
				int ans=query(1,n,1,x,y);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
