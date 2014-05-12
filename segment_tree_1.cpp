/*************************************************************************
    > File Name: segment_tree_1.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com
    > Created Time: 2013年12月02日 星期一 20时23分22秒
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
int sum[N<<2];
int mark[N<<2];
void push_up(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void push_down(int rt,int len)
{
	if(mark[rt]!=0)
	{
		mark[rt<<1]=mark[rt<<1|1]=mark[rt];
		sum[rt<<1]=(len-len/2)*mark[rt];
		sum[rt<<1|1]=(len/2)*mark[rt];
		mark[rt]=0;
	}
}
void build(int l,int r,int rt)
{
	mark[rt]=0;
	if(l==r)
	{
		sum[rt]=1;
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	push_up(rt);
}
void update(int l,int r,int rt,int L,int R,int sr)
{
	if(l>=L&&R>=r)
	{
		mark[rt]=sr;
		sum[rt]=(r-l+1)*sr;
		return;
	}
	push_down(rt,r-l+1);
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R,sr);
	if(m<R) update(rson,L,R,sr);
	push_up(rt);
}
int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int n,Q;
	int x,y,z;
	scanf("%d",&t);
	for(int ca=1;ca<=t;ca++)
	{
		scanf("%d%d",&n,&Q);
		build(1,n,1);
		while(Q--)
		{
			scanf("%d%d%d",&x,&y,&z);
			update(1,n,1,x,y,z);
		}
		printf("Case %d: The total value of the hook is %d.\n",ca,sum[1]);
	}
	return 0;
}
