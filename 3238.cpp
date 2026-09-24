#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define sz(x) (int)(x).size()
#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC target ("avx,avx2,fma")
#define endl '\n'

struct segtree {
    int n,sz;
    vector<int>tree;
    segtree(int n):n(n){
        sz=1;
        while(sz<n)sz<<=1;
        tree.assign(2*sz,LLONG_MIN);
    }
    
    void build(vector<int>&arr){
        for(int i=0;i<n;i++)tree[sz+i]=arr[i];
        for(int i=sz-1;i>0;i--)tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }

    int query(int l,int r){
        int res=LLONG_MIN;
        for(l+=sz-1,r+=sz-1;l<=r;l>>=1,r>>=1){
            if(l&1)res=max(res,tree[l++]);
            if(!(r&1))res=max(res,tree[r--]);
        }
        return res;
    }

    void update(int k,int val){
        int pos=sz+k-1;
        tree[pos]=val;
        for(pos>>=1;pos>0;pos>>=1)tree[pos]=max(tree[pos<<1],tree[pos<<1|1]);
    }

    void erase(int idx){
        int pos=sz+idx-1;
        if(tree[pos]==LLONG_MIN)return;
        tree[pos]=LLONG_MIN;
        for(pos>>=1;pos>0;pos>>=1)tree[pos]=max(tree[pos<<1],tree[pos<<1|1]);
    }
};

int n,q,cmd,i,j;

void solve() {
    cin>>n>>q;
    segtree seg(n);
    while(q--){
        cin>>cmd;
        if (cmd==1){
            cin>>i>>j;
            seg.update(i,j);
        } else if (cmd==2){
            cin>>i>>j;
            int res=seg.query(i,j);
            if(res!=LLONG_MIN)cout<<res<<endl;
        } else {
            cin>>i;
            seg.erase(i);
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}