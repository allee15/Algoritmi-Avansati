#include <iostream>

using namespace std;

long determinant(pair<long,long>x, pair<long,long>y, pair<long,long>z)
{
    return (y.first*z.second)+(x.first*y.second)+(z.first*x.second)-(x.second*y.first)-(y.second*z.first)-(x.first*z.second);
}

int main() {
    long n; cin>>n;
    long st=0,dr=0,in=0;
    pair<long,long>x,y,z,a,b;
    cin>>x.first>>x.second>>y.first>>y.second;
    a=x; b=y;
    for(long i=3;i<=n;i++)
    {
        cin>>z.first>>z.second;
        if(determinant(x,y,z) == 0) in++;
        else {
            if (determinant(x,y,z) >0) st++;
            else dr++;}
        x=y;
        y=z;
    }
    if(determinant(x,y,a) == 0) in++;
    else {
        if (determinant(x,y,a) >0) st++;
        else dr++;}

    cout<<st<<" "<<dr<<" "<<in;
    return 0;
}
