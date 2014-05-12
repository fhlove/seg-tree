/*************************************************************************
    > File Name: segment_G.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com
    > Created Time: 2013年12月03日 星期二 19时09分58秒
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
int r_len[N<<2],len[N<<2],l_len[N<<2];
int num[N];
void push_up(int rt,int l,int r)
{
	l_len[rt]=l_len[rt<<1];
	r_len[rt]=r_len[rt<<1|1];
	len[rt]=max(len[rt<<1],len[rt<<1|1]);
	int m=(l+r)>>1;
	int dis=r-l+1;
	if(num[m+1]>num[m])
	{
		if(l_len[rt]==(dis-dis/2)) l_len[rt]+=l_len[rt<<1|1];
		if(r_len[rt]==dis/2) r_len[rt]+=r_len[rt<<1];
		len[rt]=max(len[rt],l_len[rt<<1|1]+r_len[rt<<1]);
	}
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		len[rt]=l_len[rt]=r_len[rt]=1;
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	push_up(rt,l,r);
}
void update(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r) return;
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R);
	if(m<R) update(rson,L,R);
	push_up(rt,l,r);
}
int query(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		return len[rt];
	}
	int ans=0;
	//push_up(rt,l,r);
	int m=(l+r)>>1;
	if(m>=R) ans=query(lson,L,R);
	else if(m<L) ans=query(rson,L,R);
	else {
		int s1=query(lson,L,R);
		int s2=query(rson,L,R);
		ans=max(s1,s2);
		if(num[m+1]>num[m])
		{
			int temp=min(r_len[rt<<1],m-L+1)+min(l_len[rt<<1|1],R-m);
			ans=max(ans,temp);
		}
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	int t;
	int n,m;
	char op[3];
	int x,y,z;
	int ca=1;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",&num[i]);
		build(1,n,1);
		printf("Case #%d:\n",ca);
		while(m--)
		{
			scanf("%s",op);
			if(op[0]=='a')
			{
				scanf("%d%d%d",&x,&y,&z);
				for(int i=x;i<=y;i++)
					num[i]+=z;
				update(1,n,1,x,y);
			}else if(op[0]=='q'){
				scanf("%d%d",&x,&y);
				int ans=query(1,n,1,x,y);
				printf("%d\n",ans);
			}
		}
		ca++;
	}
	return 0;
}
