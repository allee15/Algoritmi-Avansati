#include <iostream>
#include <algorithm>
#include <vector>
#define INF 999999999

using namespace std;

struct semiplan{
    long ax,by,c;
};

struct inecuatii{
    long x,y;
    bool eMaximX, eMaximY;
};

vector<inecuatii>inec;
vector<semiplan> v;
long n;

void citire(){
    cin>>n;
    v.resize(n);
    inec.resize(n);
    for(long i=0;i<n;i++) {
        cin >> v[i].ax >> v[i].by >> v[i].c;
        inec[i].x = 0;
        inec[i].y= 0;
    }

}

void calculInecuatie(semiplan s, long i){
    if (s.by == 0) {
        inec[i].y = 0;
        inec[i].eMaximY = false;
        if (s.ax == 0) {
            inec[i].x = INF;
        } else {
            inec[i].x = - s.c / s.ax;
            if (s.ax < 0) {
                inec[i].eMaximX = false;
            } else {
                inec[i].eMaximX = true;
            }
        }
    } else {
        inec[i].x = 0;
        inec[i].eMaximX = false;
        if (s.by == 0) {
            inec[i].y = INF;
        } else {
            inec[i].y = - s.c / s.by;
            if (s.by < 0) {
                inec[i].eMaximY = false;
            } else {
                inec[i].eMaximY = true;
            }
        }
    }
}

void cautareMaximMinim(long& Xmaxim, long&Xminim, long& Ymaxim, long& Yminim) {

    for (long i = 0; i < n; i++) {
        if (v[i].by == 0) {
            if (inec[i].eMaximX) {
                if (Xmaxim < inec[i].x)
                    Xmaxim = inec[i].x;
            } else {
                if (Xminim > inec[i].x)
                    Xminim = inec[i].x;
            }
        } else {
            if (inec[i].eMaximY) {
                if (Ymaxim < inec[i].y)
                    Ymaxim = inec[i].y;
            } else {
                if (Yminim > inec[i].y)
                    Yminim = inec[i].y;
            }
        }
    }
}

int main(){

    citire();

    long Xmaxim = -INF;
    long Xminim = INF;

    long Ymaxim = -INF;
    long Yminim = INF;

    for(long i=0;i<n;i++)
        calculInecuatie(v[i],i);

    cautareMaximMinim(Xmaxim,Xminim,Ymaxim,Yminim);

    if(Xmaxim == -INF) Xmaxim = INF;
    if(Xminim == INF) Xminim = -INF;
    if(Ymaxim == -INF) Ymaxim = INF;
    if(Yminim == INF) Yminim = -INF;


    if (Xminim < Xmaxim && Yminim < Ymaxim) {
        if (Xmaxim == INF || Xminim == -INF || Ymaxim == INF || Yminim == -INF)
            cout<<"UNBOUNDED";
        else
            cout << "BOUNDED";
    } else {
        if(Xminim < Xmaxim || Yminim < Ymaxim) {
            cout << "VOID";
        }
    }

    return 0;
}