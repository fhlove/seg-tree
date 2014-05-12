/*************************************************************************
    > File Name: segment_tree_E.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月03日 星期二 18时33分25秒
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
const int N=8005;
struct node
{
	int y1,y2;
	int x;
};
vector<int> link[N];
node a[N];
int tree[N<<4];
int mark[N];
bool cmp(node u,node v)
{
	return u.x<v.x;
}
void push_down(int rt)
{
	if(tree[rt]!=-1)
	{
		tree[rt<<1]=tree[rt<<1|1]=tree[rt];
		tree[rt]=-1;
	}
}
void update(int l,int r,int rt,int L,int R,int sr)
{
	if(l>=L&&R>=r)
	{
		tree[rt]=sr;
		return;
	}
	push_down(rt);
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R,sr);
	if(m<R) update(rson,L,R,sr);
}
void query(int l,int r,int rt,int L,int R,int sr)
{
	if(tree[rt]!=-1)
	{
		if(mark[tree[rt]]!=sr)
		{
			mark[tree[rt]]=sr;
			link[sr].push_back(tree[rt]);
		}
		return;
	}
	if(l==r) return;
	push_down(rt);
	int m=(l+r)>>1;
	if(m>=L) query(lson,L,R,sr);
	if(m<R) query(rson,L,R,sr);
}
int main()
{
	freopen("input.txt","r",stdin);
	int ts;
	int n;
	int x,y1,y2;
	scanf("%d",&ts);
	while(ts--)
	{
		memset(tree,-1,sizeof(tree));
		memset(mark,-1,sizeof(mark));
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d%d%d",&y1,&y2,&x);
			link[i].clear();
			a[i].y1=y1*2;
			a[i].y2=y2*2;
			a[i].x=x;
		}
		sort(a,a+n,cmp);
		int r=N*2;
		for(int i=0;i<n;i++)
		{
			query(0,r,1,a[i].y1,a[i].y2,i);
			update(0,r,1,a[i].y1,a[i].y2,i);
		}
		int ans=0;
		for(int i=0;i<n;i++)
		{
			int size=link[i].size();
			for(int j=0;j<size;j++)
			{
				int temp=link[i][j];
				for(int u=0;u<size;u++)
					for(int v=0;v<link[temp].size();v++)
			
						if(link[i][u]==link[temp][v]) ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
