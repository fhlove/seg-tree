/*************************************************************************
    > File Name: hdu-4578.cpp
    > Author: mengshangqi
    > Mail: mengshangqi@gmail.com
    > Created Time: 2014年05月13日 星期二 20时16分58秒
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
#include<sstream>
#include<queue>
#include<stack>
#include<cmath>
using namespace std;
const int N=100005;
const int mod=10007;
#define lson rt<<1
#define rson rt<<1|1
int sss=0;
int p2(int x)
{
    return x*x%mod;
}
int p3(int x)
{
    return p2(x)*x%mod;
}
struct node
{
    int l,r;
    int sum[4];
    int add,mul;
    void init()
    {
        memset(sum,0,sizeof(sum));
        add=0;
        mul=1;
    }

    int mid()
    {
        return (l+r)>>1;
    }
    int length()
    {
        return r-l+1;
    }
    void muls(int m){
        (sum[1] *= m) %= mod;
        (sum[2] *= p2(m)) %= mod;
        (sum[3] *= p3(m)) %= mod;

        (mul *= m) %= mod;
        (add *= m) %= mod;
    }
    void adds(int a){
    sss++;
        (sum[3] += p3(a) * length()) %= mod;
        (sum[3] += 3 *    a    * sum[2]) %= mod;
       // cout<<sum[3]<<endl;
        (sum[3] += 3 * p2(a) * sum[1]) %= mod;
        //printf("%d  %d  %d\n",sum[3],sum[2],sum[1]);
        (sum[2] += p2(a) * length()) %= mod;
        (sum[2] += 2 * a  * sum[1]) %= mod;

        (sum[1] += a * length()) %= mod;

        (add += a) %= mod;
        //cout<<sum[3]<<endl;
    }

};
node t[N<<2];
void build(int rt,int l,int r)
{
    t[rt].l=l;
    t[rt].r=r;
    t[rt].init();
    if(l==r) return;
    int m=t[rt].mid();
    build(lson,l,m);
    build(rson,m+1,r);
}
void push_down(int rt)
{
    t[lson].muls(t[rt].mul);
    t[rson].muls(t[rt].mul);

    t[lson].adds(t[rt].add);
    t[rson].adds(t[rt].add);

    t[rt].mul=1;
    t[rt].add=0;
}
void push_up(int rt)
{
    for(int i=1;i<=3;i++)
        t[rt].sum[i]=(t[lson].sum[i]+t[rson].sum[i])%mod;
}
void update(int rt,int l,int r,int add,int mul)
{
    if(l==t[rt].l&&r==t[rt].r)
    {
        t[rt].muls(mul);
        t[rt].adds(add);
        return;
    }
    push_down(rt);
    int m=t[rt].mid();
    if(m>=r) update(lson,l,r,add,mul);
    else if(m<l) update(rson,l,r,add,mul);
    else {
        update(lson,l,m,add,mul);
        update(rson,m+1,r,add,mul);
    }
    push_up(rt);
}
int q;
int query(int rt,int l,int r)
{
    if(l==t[rt].l&&r==t[rt].r)
    {
        return t[rt].sum[q];
    }
    push_down(rt);
    int m=t[rt].mid();
    if(m>=r) return query(lson,l,r);
    else if(m<l) return query(rson,l,r);
    else return (query(lson,l,m)+query(rson,m+1,r))%mod;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    int n,m;
    while(scanf("%d%d",&n,&m)&&(n||m))
    {
        build(1,1,n);
        int op;
        int l,r,x;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&op,&l,&r);
            if(op==1)
            {
                scanf("%d",&x);
                update(1,l,r,x,1);
            }else if(op==2)
            {
                scanf("%d",&x);
                update(1,l,r,0,x);
            }else if(op==3)
            {
                scanf("%d",&x);
                update(1,l,r,x,0);
            }else {
                scanf("%d",&q);
                int res=query(1,l,r);
                printf("%d\n",res);
            }
        }
    }
    return 0;
}
