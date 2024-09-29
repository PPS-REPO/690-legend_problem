#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <random>
#define ll long long
#define vl vector<ll>
#define vpl vector<pair<ll,ll>>
#define tl pair<ll,pair<ll,ll>>
using namespace std;
ll Arr[15]={2,3,5,7,11,13,17,19,23,29,31};
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ll> dis(0,999999999);
ll pow(ll a,ll b,ll c){
    if(b==0){
        return 1;
    }
    ll d=pow(a,b/2,c);
    d*=d;
    d%=c;
    if(b%2==1){
        d*=a;
        d%=c;
    }
    return d;
}
ll gcd_uclid(ll x,ll y){
    if(x<y){
        swap(x,y);
    }
    ll z=1;
    while(y!=0){
        z=x%y;
        x=y;
        y=z;
    }
    return x;
}
tl gcd_ex(ll r1,ll r2){
    ll q,r,s,t;
    ll s1=1,s2=0;
    ll t1=0,t2=1;
    while(r2>0){
        q=r1/r2;
        r=r1-q*r2;
        s=s1-q*s2;
        t=t1-q*t2;
        r1=r2;
        r2=r;
        s1=s2;
        s2=s;
        t1=t2;
        t2=t;
    }
    return {r1,{s1,t1}};
}
ll mod_inv(ll a,ll mod){
    ll x=gcd_ex(mod,a).second.second;
    while(x<0){
        x+=mod*100000;
    }
    return x%mod;
}
ll miler(ll N,ll a){
    ll d=N-1,r=0;
    while(d%2==0){
        d/=2;
        r++;
    }
    ll i;
    if(pow(a,d,N)==1){
        return 1;
    }
    for(i=0;i<=r;i++){
        if(pow(a,d,N)==N-1){
            return 1;
        }
        d*=2;
    }
    return 0;
}
ll prime(ll N){
    if(N<3){
        return N-1;
    }
    ll i;
    ll b=lower_bound(Arr,Arr+3,N)-Arr;
    for(i=0;i<b;i++){
        if(miler(N,Arr[i])==0){
            return 0;
        }
    }
    return 1;
}
ll f(ll x,ll c,ll N){
    return (pow(x,2,N)+c%N)%N;
}
///폴라드 로 핵심 함수
ll pollard(ll N){
    if(N%2==0){
        return 2;
    }
    if(prime(N)==1){
        return N;
    }
    ll x=dis(gen)%(N-2)+2;
    ll y=x;
    ll c=dis(gen)%10+1;
    ll g=1;
    while(g==1){
        x=f(x,c,N);
        y=f(f(y,c,N),c,N);
        g=gcd_uclid(max(x,y)-min(x,y),N);
        if(g==N){
            return pollard(N);
        }
    }
    if(prime(g)==1){
        return g;
    }
    return pollard(g);
}
///폴라드 로
vl polvec(ll N){
    vl divend;
    ll d;
    while(N>1){
        d=pollard(N);
        N/=d;
        divend.push_back(d);
    }
    sort(divend.begin(),divend.end());
    return divend;
}
///인수들의 벡터
vpl comp_polvec(ll N){
    vl v=polvec(N);
    vpl x;
    if(prime(N)){
        x.push_back({N,1});
        return x;
    }
    ll sz=v.size(),i;
    ll heret=0;
    for(i=1;i<sz;i++){
        heret++;
        if(v[i]!=v[i-1]){
            x.push_back({v[i-1],heret});
            heret=0;
        }
    }
    x.push_back({v[sz-1],heret+1});
    return x;
}
ll fac_mod[2005]={0};
ll fac_pows(ll n,ll p,ll mod){
    if(n==0){
        return 1;
    }
    return pow(fac_mod[mod],n/mod,mod)*fac_mod[n%mod]%mod*fac_pows(n/p,p,mod)%mod;
}
ll countps(ll n,ll p){
    ll cnt=0;
    while(n>0){
        n/=p;
        cnt+=n;
    }
    return cnt;
}
ll C_powers(ll n,ll k,ll p,ll mod){
    ll i;
    for(i=1;i<=mod;i++){
        fac_mod[i]=fac_mod[i-1];
        if(i%p!=0){
            fac_mod[i]*=i;
            fac_mod[i]%=mod;
        }
    }
    return fac_pows(n,p,mod)*mod_inv(fac_pows(k,p,mod)*fac_pows(n-k,p,mod)%mod,mod)%mod*pow(p,countps(n,p)-countps(k,p)-countps(n-k,p),mod)%mod;
}
ll dp[2005][2005];
ll Lucas(ll n,ll k,ll m){
    ll i,j;
    for(i=1;i<=m;i++){
        dp[i][0]=1;
        dp[i][i]=1;
        for(j=1;j<i;j++){
            dp[i][j]=(dp[i-1][j]+dp[i-1][j-1])%m;
        }
    }
    ll p=1;
    while(n>0){
        p*=dp[n%m][k%m];
        n/=m;k/=m;
    }
    return p;
}
ll CRT(ll a1,ll a2,ll m1,ll m2){
    tl alp=gcd_ex(m1,m2);
    ll x=alp.second.first,y=alp.second.second;
    ll lcm=m1*m2;
    return ((a1*m2%(lcm*y)%lcm)+(a2*m1%lcm*x%lcm)+lcm)%lcm;
}///x ≡ a1 (mod m1) and x ≡ a2 (mod m2) (gcd(m1,m2)=1)
ll C(ll n,ll k,ll m){
    vpl v=comp_polvec(m);
    ll sz=v.size(),i,j,modulo=0,prod=1,modulo_here,x;
    for(i=0;i<sz;i++){
        x=1;
        for(j=0;j<v[i].second;j++){
            x*=v[i].first;
        }
        if(v[i].second==1){
            modulo_here=Lucas(n,k,v[i].first);
        }
        else{
            modulo_here=C_powers(n,k,v[i].first,x);
        }
        modulo=CRT(modulo,modulo_here,prod,x);
        prod*=x;
    }
    return modulo;
}
int main(){
    fac_mod[0]=1;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll x,y,m;
    cin>>x>>y>>m;
    cout<<C(x,y,m);
}