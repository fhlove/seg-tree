/*************************************************************************
    > File Name: debug_segment_tree_H.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com 
    > Created Time: 2013年12月06日 星期五 22时27分00秒
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
#define root 0,n-1,1
const int N=100005;
int sum[N<<2],max_sum[N<<2],min_sum[N<<2],cover[N<<2];
char str[N];
void push_up(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
	max_sum[rt]=max(max_sum[rt<<1],sum[rt<<1]+max_sum[rt<<1|1]);
	min_sum[rt]=min(min_sum[rt<<1],sum[rt<<1]+min_sum[rt<<1|1])'
}
void push_down(int rt,int l,int r)
{
	int dis=r-l+1;
	if(cover[rt]==0)
	{
		cover[rt<<1]=cover[rt<<1|1]=cover[rt];
		sum[rt<<1]=-sum[rt<<1];
		sum[rt<<1|1]=-sum[rt<<1|1];

		int temp=max_sum[rt<<1];
		max_sum[rt<<1]=-min_sum[rt<<1];
		min_sum[rt<<1]=-temp;

		temp=max_sum[rt<<1|1];
		max_sum[rt<<1|1]=-min_sum[rt<<1|1];
		min_sum[rt<<1|1]=-temp;
		cover[rt]=-1;
	}else if(cover[rt]==1)
	{
		cover[rt<<1]=cover[rt<<1|1]=cover[rt];
		sum[rt<<1]=-(dis-dis/2);
		sum[rt<<1|1]=-dis/2;

		max_sum[rt<<1]=max(-1,sum[rt<<1]);
		min_sum[rt<<1]=min(-1,sum[rt<<1]);

		max_sum[rt<<1|1]=max(-1,sum[rt<<1|1]);
		min_sum[rt<<1|1]=min(-1,sum[rt<<1|1]);
		cover[rt]=-1;
	}else if()
}
int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int n,m;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		scanf("%s",str);
		build(root);
	}
	return 0;
}
