#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct D { ll sm,v,smd,lzd,lzv; };
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    ll n,m,q; cin>>n>>m>>q;
    vector<ll> X(m);
    for(ll i=0;i<m;i++) cin>>X[i];
    vector<ll> V(m);
    for(ll i=0; i<m;i++) cin>>V[i];
    set<pair<ll,ll>> h;
    for(ll i=0;i<m;i++) h.insert({X[i],V[i]});
    vector<D> segt(4*n);
    vector<ll> iniu(n+1);
    vector<ll> inid(n+1);
    auto c=h.begin();
    for(ll i = 1; i <= n; i++) {
        while((*c).first<i) c++;
        if((*c).first==i) inid[i]=0,iniu[i]=0;
        else inid[i]=((*c).first-i),iniu[i]=(*prev(c)).second;
    }
    auto pull = [&] (ll s) {
        segt[s].sm=segt[2*s].sm+segt[2*s+1].sm;
        segt[s].smd=segt[2*s].smd+segt[2*s+1].smd;
        segt[s].v=segt[2*s].v;
    };
    auto push = [&] (ll s, ll lb, ll rb) {
        if(segt[s].lzv==0&&segt[s].lzd==0) return;
        ll m = (lb + rb) / 2;
        segt[2*s].sm+=segt[2*s].smd*segt[s].lzv;
        segt[2*s].v+=segt[s].lzv;
        segt[2*s+1].sm+=segt[2*s+1].smd*segt[s].lzv;
        segt[2*s+1].v+=segt[s].lzv;
        segt[2*s].sm+=segt[2*s].v*(m-lb+1)*segt[s].lzd;
        segt[2*s].smd+=(m-lb+1)*segt[s].lzd;
        segt[2*s+1].sm+=segt[2*s+1].v*(rb-m)*segt[s].lzd;
        segt[2*s+1].smd+=(rb-m)*segt[s].lzd;
        segt[2*s].lzd+=segt[s].lzd;
        segt[2*s+1].lzd+=segt[s].lzd;
        segt[2*s].lzv+=segt[s].lzv;
        segt[2*s+1].lzv+=segt[s].lzv;
        segt[s].lzv=0;
        segt[s].lzd=0;
    };
    function<void(ll, ll, ll)> build = [&] (ll s, ll lb, ll rb) {
        segt[s].lzd=segt[s].lzv=0;
        if(lb==rb){
            segt[s].v=iniu[lb];
            segt[s].smd=inid[lb];
            segt[s].sm=segt[s].v*segt[s].smd;
            return;
        }
        ll m=(lb+rb)/2;
        build(2*s,lb,m);
        build(2*s+1,m+1,rb);
        pull(s);
    };
    function<void(ll, ll, ll, ll, ll, ll)> updv = [&] (ll v, ll l, ll r, ll s, ll lb, ll rb) {
        l=max(l,lb);
        r=min(r,rb);
        if(r<l) return;
        if(lb==l&&rb==r){
            segt[s].sm+=v*segt[s].smd;
            segt[s].lzv+=v;
            segt[s].v+=v;
            return;
        }
        ll m=(lb+rb)/2;
        push(s, lb, rb);
        updv(v,l,r,2*s,lb,m);
        updv(v,l,r,2*s+1,m+1,rb);
        pull(s);
    };
    function<void(ll, ll, ll, ll, ll, ll)> updd = [&] (ll d, ll l, ll r, ll s, ll lb, ll rb) {
        l=max(l,lb);
        r=min(r,rb);
        if(r<l) return;
        if(lb==l&&rb==r){
            segt[s].sm+=segt[s].v*(rb-lb+1)*d;
            segt[s].lzd+=d;
            segt[s].smd+=(ll)(rb-lb+1)*d;
            return;
        }
        ll m=(lb+rb)/2;
        push(s, lb, rb);
        updd(d,l,r,2*s,lb,m);
        updd(d,l,r,2*s+1,m+1,rb);
        pull(s);
    };
    function<ll(ll, ll, ll, ll, ll)> query = [&] (ll l, ll r, ll s, ll lb, ll rb) {
        l=max(l,lb);
        r=min(r,rb);
        if(r<l) return 0ll;
        if(lb==l&&rb==r){
            return segt[s].sm;
        }
        ll m=(lb+rb)/2;
        push(s, lb, rb);
        return query(l,r,2*s,lb,m)+query(l,r,2*s+1,m+1,rb);
    };
    build(1,1,n);
    for(ll i = 0; i < q; i++) {
        ll t; cin>>t;
        if(t == 1) {
            ll x,v; cin>>x>>v;
            auto [p,_]=h.insert({x,v});
            updv(v-(*prev(p)).second,x+1,(*next(p)).first-1,1,1,n);
            updd(x-(*next(p)).first,(*prev(p)).first+1,x,1,1,n);
        } else {
            ll l,r; cin>>l>>r;
            cout<<query(l,r,1,1,n)<<'\n';
        }
    }
 
}