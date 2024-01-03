#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<pair<long,long>> p;
long n;
stack<pair<long,long>>frst, frdr;

bool sortare(pair<long,long>a, pair<long,long> b)
{
    if (a.first > b.first)
        return true;
    if (a.first==b.first && a.second>b.second)
        return true;
    return false;

}

int determinant(pair<long,long>x, pair<long,long>y, pair<long,long>z)
{
    long long rez = (y.first*z.second)+(x.first*y.second)+(z.first*x.second)-(x.second*y.first)-(y.second*z.first)-(x.first*z.second);
    if (rez < 0)
        return -1;
    if (rez == 0)
        return 0;

    return 1;
}

int virajstanga()
{
    pair<long,long> a ,b,c;
    a= frst.top();
    frst.pop();
    b= frst.top();
    frst.pop();
    c=frst.top();
    frst.pop();
    int rez = determinant(a,b,c);
    frst.push(c);
    frst.push(b);
    frst.push(a);
    if (rez != 1)
        return 0;
    return 1;
}

int virajdreapta()
{
    pair<long,long> a ,b,c;
    a= frdr.top();
    frdr.pop();
    b= frdr.top();
    frdr.pop();
    c=frdr.top();
    frdr.pop();
    int rez = determinant(a,b,c);
    frdr.push(c);
    frdr.push(b);
    frdr.push(a);
    if (rez !=1)
        return 0;
    return 1;
}

void Graham()
{
    frst.push(p[0]);
    frst.push(p[1]);

    for(long i=2;i< n ;i++)
    {
        frst.push(p[i]);

        while(frst.size()>2 && virajstanga()==0)
        {
            pair<long,long> a = frst.top();
            frst.pop();
            frst.pop();
            frst.push(a);
        }
    }

    frdr.push(p[n-1]);
    frdr.push(p[n-2]);
    for(long i=n-3;i>=0;i--)
    {
        frdr.push(p[i]);

        while(frdr.size()>2 && virajdreapta()==0)
        {
            pair<long,long> a = frdr.top();
            frdr.pop();
            frdr.pop();
            frdr.push(a);
        }
    }
}

int main() {

    cin>>n;
    p.resize(n);

    for(long i=0;i<n;i++)
        cin>>p[i].first>>p[i].second;
    sort(p.begin(),p.end(),sortare);

    Graham();

    cout<<frst.size()+frdr.size()-2<<endl;
    while(!frdr.empty())
    {
        pair<long,long> a;
        a=frdr.top();
        cout<<a.first<<" "<<a.second<<endl;
        frdr.pop();
    }

    unsigned long long x = frst.size();

    frst.pop();

    for (unsigned long long i = 2; i < x; i++)
    {
        pair<long, long> a;
        a = frst.top();
        cout << a.first << " " << a.second << endl;
        frst.pop();
    }

    return 0;
}
