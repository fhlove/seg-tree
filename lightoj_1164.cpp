/*************************************************************************
    > File Name: lightoj_1164.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com
    > Created Time: 2013年12月10日 星期二 19时43分39秒
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
typedef long long ll;
ll sum[N<<2],add[N<<2];
void push_up(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void push_down(int rt,int l,int r)
{
	if(add[rt])
	{
		int dis=r-l+1;

		add[rt<<1]+=add[rt];
		
		add[rt<<1|1]+=add[rt];
		
		sum[rt<<1]+=(dis-dis/2)*add[rt];

		sum[rt<<1|1]+=dis/2*add[rt];

		add[rt]=0;
	}
}
void build(int l,int r,int rt)
{
	sum[rt]=add[rt]=0;
	if(l==r) return;
	int m=(l+r)>>1;
	build(lson);
	build(rson);
}
void update(int l,int r,int rt,int L,int R,int sr)
{
	if(l>=L&&R>=r)
	{
		add[rt]+=sr;

		sum[rt]+=sr*(r-l+1);
		return;
	}
	push_down(rt,l,r);
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R,sr);
	if(m<R) update(rson,L,R,sr);
	push_up(rt);
}

ll query(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		return sum[rt];
	}
	push_down(rt,l,r);
	ll res=0;
	int m=(l+r)>>1;
	if(m>=L) res+=query(lson,L,R);
	if(m<R) res+=query(rson,L,R);
	return res;
}

int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int n,m;
	int op,x,y,z;
	int c=1;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		build(1,n,1);
		printf("Case %d:\n",c++);
		while(m--)
		{
			scanf("%d",&op);
			if(op==0)
			{
				scanf("%d%d%d",&x,&y,&z);
				x++;
				y++;
				update(1,n,1,x,y,z);
			}else {
				scanf("%d%d",&x,&y);
				x++;
				y++;
				ll ans=query(1,n,1,x,y);
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
