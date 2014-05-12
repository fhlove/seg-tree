/*************************************************************************
    > File Name: lightoj_1103.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月07日 星期六 21时13分01秒
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
const int N=200005;
struct node
{
	int x,y;
};
node p[N];
int sum[N<<2];
bool cmp(node a,node b)
{
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}
void push_up(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void update(int l,int r,int rt,int sr)
{
	if(l==r)
	{
		sum[rt]++;
		return;
	}
	int m=(l+r)>>1;
	if(m>=sr) update(lson,sr);
	else update(rson,sr);
	push_up(rt);
}
int query(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		return sum[rt];
	}
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
	int n,m;
	int c=1;
	scanf("%d",&t);
	while(t--)
	{
		memset(sum,0,sizeof(sum));	
		scanf("%d%d",&n,&m);
		for(int i=0;i<n+m;i++)
			scanf("%d%d",&p[i].x,&p[i].y);
		sort(p,p+m+n,cmp);
		long long ans=0;
		for(int i=0;i<m+n;i++)
		{
			ans=ans+query(1,m+n,1,p[i].y,m+n);
			update(1,n+m,1,p[i].y);
		}
		printf("Case %d: %lld\n",c++,ans);
	}
	return 0;
}
