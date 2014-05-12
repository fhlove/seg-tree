/*************************************************************************
    > File Name: lightoj_1135.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月07日 星期六 22时27分08秒
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
int cover[N<<2];
int mod_0[N<<2],mod_1[N<<2],mod_2[N<<2];
void push_up(int rt)
{
	mod_0[rt]=mod_0[rt<<1]+mod_0[rt<<1|1];
	mod_1[rt]=mod_1[rt<<1]+mod_1[rt<<1|1];
	mod_2[rt]=mod_2[rt<<1]+mod_2[rt<<1|1];
}
void build(int l,int r,int rt)
{
	cover[rt]=0;
	if(l==r)
	{	
		mod_0[rt]=1;
		mod_1[rt]=mod_2[rt]=0;
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	push_up(rt);
}
void deal(int rt)
{
	int temp=mod_0[rt];
	mod_0[rt]=mod_2[rt];
	mod_2[rt]=mod_1[rt];
	mod_1[rt]=temp;
}
void push_down(int rt)
{
	if(cover[rt]!=0)
	{
		cover[rt<<1]+=cover[rt];
		cover[rt<<1|1]+=cover[rt];
		for(int i=0;i<cover[rt]%3;i++)
		{
			deal(rt<<1);
			deal(rt<<1|1);
		}
		cover[rt]=0;
	}
}

void update(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		cover[rt]+=1;
		deal(rt);
		return;
	}
	push_down(rt);
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R);
	if(m<R) update(rson,L,R);
	push_up(rt);
}
int query(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		return mod_0[rt];
	}
	push_down(rt);
	int m=(l+r)>>1;
	int res=0;
	if(m>=L) res+=query(lson,L,R);
	if(m<R) res+=query(rson,L,R);
	return res;
}
int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int c=1;
	int n,m;
	int op,x,y;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		build(0,n-1,1);
		printf("Case %d:\n",c++);
		while(m--)
		{
			scanf("%d%d%d",&op,&x,&y);
			if(op==0)
			{
				update(0,n-1,1,x,y);
			}else {
				int res=query(0,n-1,1,x,y);
				printf("%d\n",res);
			}
		}
	}
	return 0;
}
