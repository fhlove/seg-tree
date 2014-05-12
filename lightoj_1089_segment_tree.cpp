/*************************************************************************
    > File Name: lightoj_1089_segment_tree.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年11月28日 星期四 20时57分59秒
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
const int N=2000105;
int sum[N];
struct node
{
	int l,r;
};
node xx[500050];
int cc[5000000];
int qu[500050];
void push_down(int rt)
{
	if(sum[rt]!=0)
	{
		sum[rt<<1]+=sum[rt];
		sum[rt<<1|1]+=sum[rt];
		sum[rt]=0;
	}
}
void build(int l,int r,int rt)
{
	sum[rt]=0;
	if(l==r) return;
	int m=(l+r)>>1;
	build(lson);
	build(rson);
}
void update(int l,int r,int rt,int L,int R,int sr)
{
	if(L<=l&&R>=r)
	{
		sum[rt]++;
		return;
	}
	push_down(rt);
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R,sr);
	if(m<R) update(rson,L,R,sr);
}
int query(int l,int r,int rt,int L,int R)
{
	if(L<=l&&R>=r)
	{
		return sum[rt];
	}
	push_down(rt);
	int res=0;
	int m=(l+r)>>1;
	if(m>=L) res+=query(lson,L,R);
	if(m<R) res+=query(rson,L,R);
	return res;
}
int main()
{
	freopen("input.txt","r",stdin);
	int n,m;
	int t;
	int index;
	scanf("%d",&t);
	for(int c=1;c<=t;c++)
	{
		index=0;
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
		{
			scanf("%d%d",&xx[i].l,&xx[i].r);
			cc[index++]=xx[i].l;
			cc[index++]=xx[i].r;
		}
		for(int i=0;i<m;i++)
		{
			scanf("%d",&qu[i]);
			cc[index++]=qu[i];
		}
		sort(cc,cc+index);
		int size=unique(cc,cc+index)-cc;
		build(1,500002,1);
		for(int i=0;i<n;i++)
		{
			int l=lower_bound(cc,cc+size,xx[i].l)-cc+1;
			int r=lower_bound(cc,cc+size,xx[i].r)-cc+1;
			update(1,500002,1,l,r,1);
		}
		printf("Case %d:\n",c);
		for(int i=0;i<m;i++)
		{
			int q=lower_bound(cc,cc+size,qu[i])-cc+1;
			int res=query(1,500002,1,q,q);
			printf("%d\n",res);
		}
	}
	return 0;
}
