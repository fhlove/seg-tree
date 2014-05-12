/*************************************************************************
    > File Name: lightoj_1207.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月18日 星期三 21时13分06秒
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
int cover[N<<4];
bool visit[N];
int ans=0;
void push_down(int rt)
{
	if(cover[rt]!=-1)
	{
		cover[rt<<1]=cover[rt<<1|1]=cover[rt];
		cover[rt]=-1;
	}
}
void update(int l,int r,int rt,int L,int R,int sr)
{
	if(l>=L&&R>=r)
	{
		cover[rt]=sr;
		return;
	}
	push_down(rt);
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R,sr);
	if(m<R) update(rson,L,R,sr);
}
void query(int l,int r,int rt)
{
	if(cover[rt]!=-1)
	{
		if(!visit[cover[rt]])
		{
			ans++;
			visit[cover[rt]]=1;
		}
		return;
	}
	if(l==r) return;
	push_down(rt);
	int m=(l+r)>>1;
	query(lson);
	query(rson);
}
int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int n;
	int c=1;
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		scanf("%d",&n);
		memset(cover,-1,sizeof(cover));
		memset(visit,0,sizeof(visit));
		int x,y;
		int m=n*2;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&x,&y);
			update(1,m,1,x,y,i);
		}
		query(1,m,1);
		printf("Case %d: %d\n",c++,ans);
	}
	return 0;
}
