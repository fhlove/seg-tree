/*************************************************************************
    > File Name: lightoj_1188.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com
    > Created Time: 2013年12月18日 星期三 19时53分59秒
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
int num[N];
bool visit[N];
int head[N],next[N];
int ans[N];
struct node
{
	int id;
	int l,r;
};
node q[N];
bool cmp(node a,node b)
{
	if(a.l!=b.l) return a.l<b.l;
	return a.r<b.r;
}
void push_up(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void update(int l,int r,int rt,int sr,int e)
{
	if(l==r)
	{
		sum[rt]=e;
		return;
	}
	int m=(l+r)>>1;
	if(m>=sr) update(lson,sr,e);
	else update(rson,sr,e);
	push_up(rt);
}
int query(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		return sum[rt];
	}
	int res=0;
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
	int c=1;
	scanf("%d",&t);
	while(t--)
	{
		memset(sum,0,sizeof(sum));
		memset(visit,0,sizeof(visit));
		memset(head,-1,sizeof(head));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",&num[i]);
		for(int i=n;i>0;i--)
		{
			if(head[num[i]]==-1)
			{
				head[num[i]]=i;
				next[i]=-1;
			}else {
				next[i]=head[num[i]];
				head[num[i]]=i;
			}
		}

		for(int i=1;i<=n;i++)
		{
			if(!visit[num[i]])
			{
				update(1,n,1,i,1);
				visit[num[i]]=1;
			}
		}

		for(int i=0;i<m;i++)
		{
			scanf("%d%d",&q[i].l,&q[i].r);
			q[i].id=i;
		}

		sort(q,q+m,cmp);
		int index=0;

		for(int i=1;i<=n;i++)
		{
			while(index<m&&q[index].l==i)
			{
				ans[q[index].id]=query(1,n,1,q[index].l,q[index].r);
				index++;
			}

			update(1,n,1,i,0);
			if(next[i]!=-1) update(1,n,1,next[i],1);
		}

		printf("Case %d:\n",c++);
		for(int i=0;i<m;i++)
			printf("%d\n",ans[i]);
	}
	return 0;
}
