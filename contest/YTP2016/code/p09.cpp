// by 張凱傑
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
struct Bigint{
    static const int LEN=60;
    static const int BIGMOD = 10000;
    int s;
    int vl,v[LEN];
    Bigint(): s(1){vl=0;}
    Bigint(long long a){
        s=1;vl=0;
        if(a<0){s=-1;a=-a;}
        while(a){
            push_back(a%BIGMOD);
            a/=BIGMOD;
        }
    }
    Bigint(string str){
        s=1;vl=0;
        int stPos=0,num=0;
        if(!str.empty()&&str[0]=='-'){
            stPos=1;
            s=-1;
        }
        for(int i=str.size()-1,q=1;i>=stPos;i--){
            num+=(str[i]-'0')*q;
            if((q*=10)>=BIGMOD){
                push_back(num);
                num=0;q=1;
            }
        }
        if(num)push_back(num);
    }
    int len() const{return vl;}
    bool empty()const{return len()==0;}
    void push_back(int x){v[vl++]=x;}
    void pop_back(){vl--;}
    int back() const {return v[vl-1];}
    void n(){ while(!empty()&&!back())pop_back();}
    void resize(int nl){
        vl=nl;fill(v,v+vl,0);
    }
    void print()const{
        if(empty()){putchar('0');return;}
        if(s==-1)putchar('-');
        printf("%d",back());
        for(int i=len()-2;i>=0;i--)printf("%.4d",v[i]);
    }
    int cp3(const Bigint &b)const{
        if(s!=b.s)return s>b.s? 1:-1;
        if(s==-1)return -(-*this).cp3(-b);
        if(len()!=b.len())return len()>b.len()?1:-1;
        for(int i=len()-1;i>=0;i--)
            if(v[i]!=b.v[i])return v[i]>b.v[i]?1:-1;
        return 0;
    }
    bool operator < (const Bigint &b)const{return cp3(b)==-1;}
    bool operator <= (const Bigint &b)const{return cp3(b)<=0;}
    bool operator >= (const Bigint &b)const{return cp3(b)>=0;}
    bool operator == (const Bigint &b)const{return cp3(b)==0;}
    bool operator != (const Bigint &b)const{return cp3(b)!=0;}
    bool operator > (const Bigint &b)const{return cp3(b)==1;}
    Bigint  operator - () const{
        Bigint r=(*this);
        r.s=-r.s;
        return r;
    }

    Bigint operator + (const Bigint &b) const{
        if(s==-1)return -(-(*this)+(-b));
        if(b.s==-1)return (*this)-(-b);
        Bigint r;
        int nl =max(len(),b.len());
        r.resize(nl+1);
        for(int i=0;i<nl;i++){
            if(i<len())r.v[i]+=v[i];
            if(i<b.len())r.v[i]+=b.v[i];
            if(r.v[i]>=BIGMOD){
                r.v[i+1]+=r.v[i]/BIGMOD;
                r.v[i]%=BIGMOD;
            }

        }
        r.n();
        return r;
    }
    Bigint operator -(const Bigint &b) const{
        if(s==-1)return -(-(*this)-(-b));
        if(b.s==-1)return (*this)+(-b);
        if((*this)<b)return -(b-(*this));
        Bigint r;
        r.resize(len());
        for(int i=0;i<len();i++){
            r.v[i]+=v[i];
            if(i<b.len())r.v[i]-=b.v[i];
            if(r.v[i]<0){
                r.v[i]+=BIGMOD;
                r.v[i+1]--;
            }
        }
        r.n();
        return r;
    }

};
int main(){
    string strA,strB;
    cin>>strA>>strB;
    Bigint A=(strA);
    Bigint B=(strB);
    Bigint C=A+B;
    Bigint D=A-B;
    C.print();puts("");
    D.print();puts("");
}
