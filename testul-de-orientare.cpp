#include <iostream>

using namespace std;

long determinant(pair<long,long>x, pair<long,long>y, pair<long,long>z)
{
    return (y.first*z.second)+(x.first*y.second)+(z.first*x.second)-(x.second*y.first)-(y.second*z.first)-(x.first*z.second);
}

int main() {

    long t; cin>>t;
    pair<long,long> x;
    pair<long,long>y;
    pair<long,long>z;
    for(long i=0;i<t;i++)
    {
        cin>>x.first>>x.second>>y.first>>y.second>>z.first>>z.second;
        if(determinant(x,y,z) == 0) cout<<"TOUCH"<<endl;
        else {
            if (determinant(x,y,z) >0) cout<<"LEFT"<<endl;
            else cout<<"RIGHT"<<endl;}
    }
    return 0;
}
