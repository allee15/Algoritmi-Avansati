#include <iostream>
using namespace std;

int main() {
    int n;
    int a,b,x=-1,y=-1,c,d,contor=0;
    cin>>a>>b>>n;
    int v[n];
    for(int i=1;i<=n;i++)
    {
        cin>>c>>d;
        if (c<=a && ( d>=a && d<=b))
        {
            if(y<d && x>c)
            {
                contor++;
                v[i]++;
                x=c; y=d;
            }
        }
    }
    cout<<contor<<endl;
    for(int i=1;i<=n;i++)
        if(v[i]>0) cout<<i<<" ";
    return 0;
}
