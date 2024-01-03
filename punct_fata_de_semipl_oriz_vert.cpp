#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#define INF 999999999

using namespace std;

struct semiplan{
    double ax,by,c;
};

struct inecuatii{
    double x,y;
};

vector<inecuatii>inec;
vector<semiplan> v;
vector<double> xMaximi, xMinimi, yMaximi, yMinimi;
vector<pair<double,double>>Q;
long n,m;

void citire(){
    cin>>n;
    v.resize(n);
    inec.resize(n);
    for(long i=0;i<n;i++) {
        cin >> v[i].ax >> v[i].by >> v[i].c;
        inec[i].x = 0;
        inec[i].y= 0;
    }
    cin>>m;
    Q.resize(m);
    for(long i=0;i<m;i++)
        cin>>Q[i].first>>Q[i].second;

}

void calculInecuatie(semiplan s, long i){
    if (s.by == 0) {
        inec[i].y = 0;
        inec[i].x = - s.c / s.ax;
        if (s.ax < 0) {
            xMinimi.push_back(inec[i].x);
        } else {
            xMaximi.push_back(inec[i].x);
        }
    } else {
        inec[i].x = 0;
        inec[i].y = - s.c / s.by;
        if (s.by < 0) {
            yMinimi.push_back(inec[i].y);
        } else {
            yMaximi.push_back(inec[i].y);
        }
    }
}

double isInsideIntersection(pair<double,double> p) {
    long indice_x_max=0, indice_y_max=0, indice_x_min=0, indice_y_min=0;
    long xmax = xMaximi.size(), xmin = xMinimi.size(), ymax = yMaximi.size(), ymin = yMinimi.size();
    if(!xmax || !xmin || !ymax || !ymin) return 0;
    while (p.first >= xMaximi[indice_x_max] && indice_x_max <= xmax) indice_x_max++;
    while( p.second >= yMaximi[indice_y_max] && indice_y_max <= ymax) indice_y_max++;
    while( p.first <= xMinimi[indice_x_min] && indice_x_min <= xmin) indice_x_min++;
    while( p.second <= yMinimi[indice_y_min] && indice_y_min <= ymin) indice_y_min++;

    if(indice_x_max >= xmax|| indice_y_max >= ymax || indice_x_min >= xmin || indice_y_min >= ymin)
        return 0;
    else {
        return ((xMaximi[indice_x_max] - xMinimi[indice_x_min]) * (yMaximi[indice_y_max] - yMinimi[indice_y_min]));
    }
}


int main(){

    citire();

    for(long i=0;i<n;i++)
        calculInecuatie(v[i],i);

    sort(xMaximi.begin(),xMaximi.end());
    sort(yMaximi.begin(),yMaximi.end());

    sort(xMinimi.begin(),xMinimi.end(),greater<>());
    sort(yMinimi.begin(),yMinimi.end(),greater<>());

    //aria = xmaxim-xminim * ymaxim-yminim
    for(long i=0;i<m;i++) {
        double rez = isInsideIntersection(Q[i]);
        if (rez!= 0)
            cout << "YES" << endl << fixed<< setprecision(6)<<rez << endl;
        else cout << "NO" << endl;
    }

    return 0;
}