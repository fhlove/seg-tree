/*************************************************************************
    > File Name: segment_tree_2.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月02日 星期一 19时40分37秒
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
typedef long long LL;
const int N=100005;
LL t[N<<2];
LL mark[N<<2];
LL num[N];
void push_up(int rt)
{
	t[rt]=t[rt<<1]+t[rt<<1|1];
}
void push_down(int rt,int len)
{
	if(mark[rt]!=0)
	{
		mark[rt<<1]+=mark[rt];
		mark[rt<<1|1]+=mark[rt];

		t[rt<<1]+=mark[rt]*(len-len/2);
		t[rt<<1|1]+=mark[rt]*(len/2);
		mark[rt]=0;
	}
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		t[rt]=num[l];
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
		mark[rt]+=sr;
		t[rt]+=(r-l+1)*sr;
		return;
	}
	push_down(rt,r-l+1);
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R,sr);
	if(m<R) update(rson,L,R,sr);
	push_up(rt);
}
LL query(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		return t[rt];
	}
	push_down(rt,r-l+1);
	LL sum=0;
	int m=(l+r)>>1;
	if(m>=L) sum+=query(lson,L,R);
	if(m<R) sum+=query(rson,L,R);
	return sum;
}
int main()
{
	freopen("input.txt","r",stdin);
	int n,m;
	char op[3];
	int x,y,z;
	while(~scanf("%d%d",&n,&m))
	{
		memset(mark,0,sizeof(mark));
		for(int i=1;i<=n;i++)
			scanf("%lld",&num[i]);
		build(1,n,1);
		while(m--)
		{
			scanf("%s",op);
			if(op[0]=='Q')
			{
				scanf("%d%d",&x,&y);
				LL ans=query(1,n,1,x,y);
				printf("%lld\n",ans);
			}else {
				scanf("%d%d%d",&x,&y,&z);
				update(1,n,1,x,y,z);
			}
		}
	}
	return 0;
}
