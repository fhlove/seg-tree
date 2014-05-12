/*************************************************************************
    > File Name: segment_tree_H.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com
    > Created Time: 2013年12月05日 星期四 18时43分50秒
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
#define tree 0,n-1,1
const int N=100005;
int sum[N<<2],max_sum[N<<2],min_sum[N<<2],cover[N<<2],Xor[N<<2];
char str[N];
void fxor(int rt)
{
	if(cover[rt]!=0) cover[rt]=-cover[rt];
	else Xor[rt]=Xor[rt]^1;
}
void push_up(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
	max_sum[rt]=max(max_sum[rt<<1],sum[rt<<1]+max_sum[rt<<1|1]);

	min_sum[rt]=min(min_sum[rt<<1],sum[rt<<1]+min_sum[rt<<1|1]);
}
void push_down(int rt,int l,int r)
{
	int dis=r-l+1;
	if(cover[rt]!=0)
	{
		cover[rt<<1]=cover[rt<<1|1]=cover[rt];

		sum[rt<<1]=cover[rt]*(dis-dis/2);
		sum[rt<<1|1]=cover[rt]*dis/2;

		max_sum[rt<<1]=max(cover[rt],sum[rt<<1]);
		min_sum[rt<<1]=min(cover[rt],sum[rt<<1]);

		max_sum[rt<<1|1]=max(cover[rt],sum[rt<<1|1]);
		min_sum[rt<<1|1]=min(cover[rt],sum[rt<<1|1]);

		Xor[rt<<1]=Xor[rt<<1|1]=0;
		cover[rt]=0;
	}
	if(Xor[rt]!=0)
	{
		fxor(rt<<1);
		fxor(rt<<1|1);

		sum[rt<<1]=-sum[rt<<1];
		sum[rt<<1|1]=-sum[rt<<1|1];

		int temp=max_sum[rt<<1];
		max_sum[rt<<1]=-min_sum[rt<<1];
		min_sum[rt<<1]=-temp;

		temp=max_sum[rt<<1|1];
		max_sum[rt<<1|1]=-min_sum[rt<<1|1];
		min_sum[rt<<1|1]=-temp;

		Xor[rt]=0;
	}
}
void build(int l,int r,int rt)
{
	cover[rt]=0;
	Xor[rt]=0;
	if(l==r)
	{
		if(str[l]=='(') sum[rt]=max_sum[rt]=min_sum[rt]=-1;
		else sum[rt]=max_sum[rt]=min_sum[rt]=1;
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
		if(sr==0)
		{
			fxor(rt);
			sum[rt]=-sum[rt];
			int temp=max_sum[rt];
			max_sum[rt]=-min_sum[rt];
			min_sum[rt]=-temp;
		}else if(sr==1)
		{
			cover[rt]=-1;
			sum[rt]=-(r-l+1);
			max_sum[rt]=-1;
			min_sum[rt]=sum[rt];
			Xor[rt]=0;
		}else if(sr==2)
		{
			cover[rt]=1;
			sum[rt]=r-l+1;
			max_sum[rt]=sum[rt];
			min_sum[rt]=1;
			Xor[rt]=0;
		}
		return;
	}
	push_down(rt,l,r);
	int m=(l+r)>>1;
	if(m>=L) update(lson,L,R,sr);
	if(m<R) update(rson,L,R,sr);
	push_up(rt);
}
int query(int l,int r,int rt,int L,int R)
{
	if(l>=L&&R>=r)
	{
		return sum[rt];
	}
	push_down(rt,l,r);
	int m=(l+r)>>1;
	int res=0;
	if(m>=L) res+=query(lson,L,R);
	if(m<R) res+=query(rson,L,R);
	return res;
}

int get_max(int l,int r,int rt,int L,int R)
{
	//printf("------------\n");
	//printf("%d  %d  %d  %d\n",l,r,L,R);
	if(l>=L&&R>=r)
	{
		return max_sum[rt];
	}
	//printf("--------------------\n");
	push_down(rt,l,r);
	int m=(l+r)>>1;
	int res=0;
	if(m>=R) res=get_max(lson,L,R);//,puts("&");
	else if(m<L) res=get_max(rson,L,R);//,puts("%");
	else {
        //puts("^^");
		res=max(get_max(lson,L,R),query(lson,L,R)+get_max(rson,L,R));
	}
	return res;
}
int main()
{
	freopen("input.txt","r",stdin);
	int t,n,m;
	char op[10];
	int x,y;
	char ch[3];
	int c=1;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		scanf("%s",str);
		build(tree);
		scanf("%d",&m);
		printf("Case %d:\n",c++);
		while(m--)
		{
			scanf("%s %d%d",op,&x,&y);
			if(op[0]=='q')
			{
				int s1=query(tree,x,y);
				int s2=get_max(tree,x,y);
				//printf("%d   %d\n",s1,s2);
				if(s1==0&&s2<=0) printf("YES\n");
				else printf("NO\n");
			}else if(op[0]=='r') {
				update(tree,x,y,0);
			}else {
				scanf("%s",ch);
				if(ch[0]=='(') update(tree,x,y,1);
				else update(tree,x,y,2);
			}
		}
		puts("");
	}
	return 0;
}
