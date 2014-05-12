/*************************************************************************
    > File Name: lightoj_1339.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月18日 星期三 21时44分46秒
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
const int N=100005;
int sum[N<<2];
int num[N];
int x[N<<1];
struct node
{
	int l,r,u;
	int id;
};
node qu[N];
bool cmp(node p,node q)
{
	if(p.l!=q.l) return p.l<q.l;
	return p.r<q.r;
}
int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int t;
	int n,m;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		int index;
		for(int i=0;i<n;i++)
		{
			scanf("%d",&num[i]);
			x[i]=num[i];
		}
		sort(x,x+n);
		int size=unique(x,x+n)-x;
		for(int i=0;i<m;i++)
			scanf("%d%d%d",&qu[i].l,&qu[i].r,&qu[i].u),qu[i].id=i;
		sort(qu,qu+m,cmp);

	}
	return 0;
}
