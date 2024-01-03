#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void citire(vector<pair<long,long>>&T, long& m, vector<pair<long,long>>&P){
    T.resize(3);
    for(int i=0;i<3;i++)
        cin>>T[i].first>>T[i].second;

    cin>>m;
    P.resize(m);
    for(int i=0;i<m;i++)
        cin>>P[i].first>>P[i].second;
}

double determinant(double x11, double x12, double x13, double x21, double x22, double x23, double x31, double x32, double x33){
    return x11*x22*x33 + x21*x32*x13 + x31*x12*x23 - x13*x22*x31 - x23*x32*x11 - x33*x12*x21;
}

double pozitie(pair<long,long>a, pair<long,long>b, pair<long,long>c, pair<long,long>d){
    //daca det > 0 => d e inside
    //daca det == 0 => d e boundary
    //daca det < 0 => d e outside
    double a1 = a.first*a.first+a.second*a.second;
    double b1 = b.first*b.first+b.second*b.second;
    double c1 = c.first*c.first + c.second*c.second;
    double d1 = d.first*d.first + d.second*d.second;

    double det1 = a.first * determinant(b.second, b1,1,c.second,c1,1,d.second,d1,1);
    double det2 = (-1) * a.second * determinant(b.first,b1,1,c.first,c1,1,d.first,d1,1);
    double det3 = a1 * determinant(b.first, b.second,1,c.first,c.second,1,d.first,d.second,1);
    double det4 = (-1) * determinant(b.first, b.second,b1,c.first,c.second,c1,d.first,d.second,d1);

    if (abs(det1)==0.0)
        det1=0.0;
    if (abs(det2)==0.0)
        det2=0.0;
    if (abs(det3)==0.0)
        det3=0.0;
    if (abs(det4)==0.0)
        det4=0.0;

    double rez = det1+det2+det3+det4;
    return rez;
}

int main() {

    vector<pair<long,long>>T,P;
    long m;
    citire(T,m,P);

    for(int i=0;i<m;i++){
        if(pozitie(T[0],T[1],T[2],P[i]) > 0)
            cout<<"INSIDE"<<endl;
        else {
            if(pozitie(T[0],T[1],T[2],P[i]) < 0)
                cout<<"OUTSIDE"<<endl;
            else cout<<"BOUNDARY"<<endl;
        }
    }
    return 0;
}
