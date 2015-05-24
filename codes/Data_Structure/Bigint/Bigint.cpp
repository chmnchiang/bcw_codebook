#include<bits/stdc++.h>
using namespace std;

const int bL = 1000;
const int bM = 10000;

struct Bigint{
    int v[bL],l,s;
    Bigint() : l(0), s(1) {
        memset(v, 0, sizeof(v)); 
    }


    void n(){
        for(;l;l--) if(v[l-1]) return;
    }

    Bigint(long long a){
        s = 1;
        if(a<0) {
            s = -1; a = -a;
        }
        for(l=0;a;v[l++]=a%bM,a/=bM);
    }
    Bigint(const char *a){
        l=0; s=1;
        int t=0,i=strlen(a),q=1;
        int ls=0;
        if(a[0] == '-') {
            ls = 1; s = -1;
        }
        while(i>ls){
            t+=(a[--i]-'0')*q;
            if((q*=10)>=bM) {
                v[l++]=t; t=0; q=1;
            }
        }
        if(t) v[l++]=t; 
    }

    void print() const {
        if(l==0){ putchar('0');return; }
        if(s==-1) putchar('-');
        printf("%d",v[l-1]);
        for(int i=l-2;i>=0;i--) printf("%.4d",v[i]);
    }

    int cp3(const Bigint &b)const {
        if(l!=b.l) return l>b.l?1:-1;
        for(int i=l-1;i>=0;i--)
            if(v[i]!=b.v[i])
                return v[i]>b.v[i]?1:-1;
        return 0;
    }

    bool operator < (const Bigint &b)const{ return cp3(b)==-1; }
    bool operator == (const Bigint &b)const{ return cp3(b)==0; }
    bool operator > (const Bigint &b)const{ return cp3(b)==1; }

    Bigint operator - () const {
        Bigint r = (*this);
        r.s = -r.s;
        return r;
    }

    Bigint operator + (const Bigint &b) const {
        if(s == -1) return -(-(*this)+(-b));
        if(b.s == -1) return (*this)-(-b);
        Bigint r;
        r.l=max(l,b.l);
        for(int i=0;i<r.l;i++) {
            r.v[i]+=v[i]+b.v[i];
            if(r.v[i]>=bM) {
                r.v[i+1]+=r.v[i]/bM;
                r.v[i]%=bM;
            }
        }
        if(r.v[r.l]) r.l++;
        return r;
    }

    Bigint operator - (const Bigint &b) const {
        if(s == -1) return -(-(*this)-(-b));
        if(b.s == -1) return (*this)+(-b);
        if((*this)<b) return -(b-(*this));
        Bigint r;
        r.l=l;
        for(int i=0;i<l;i++) {
            r.v[i]+=v[i];
            if(i<b.l) r.v[i]-=b.v[i];
            if(r.v[i]<0) {
                r.v[i]+=bM;
                r.v[i+1]--;
            }
        }
        r.n();
        return r;
    }

    Bigint operator * (const Bigint &b) {
        Bigint r;
        r.l=l+b.l;
        r.s = s * b.s;
        for(int i=0;i<l;i++) {
            for(int j=0;j<b.l;j++) {
                r.v[i+j]+=v[i]*b.v[j];
                if(r.v[i+j]>=bM) {
                    r.v[i+j+1]+=r.v[i+j]/bM;
                    r.v[i+j]%=bM;
                }
            }
        }
        r.n();
        return r;
    }

    Bigint operator / (const Bigint &b) {
        Bigint r;
        r.l=max(1,l-b.l+1);
        r.s = s * b.s;
        for(int i=r.l-1;i>=0;i--) {
            int d=0,u=bM-1,m;
            while(d<u) {
                m=(d+u+1)>>1;
                r.v[i]=m;
                if((r*b)>(*this)) u=m-1;
                else d=m;
            }
            r.v[i]=d;
        }
        r.n();
        return r;
    }

    Bigint operator % (const Bigint &b) {
        return (*this)-(*this)/b*b;
    }
};
