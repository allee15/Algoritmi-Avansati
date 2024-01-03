#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<long,long>>P;
long n;

long cmp(long start, long stop){
    if(start<stop)
        return stop;
    return stop+n;
}

long cmp2(long start, long stop){
    if(start<stop)
        return start+n;
    return start;
}

int monotonie(bool Ox){

    long start=0, stop=0;
    if(Ox){
        for(long i=0;i<P.size();++i) {
            if (P[i].first < P[start].first)
                start = i;
            if(P[i].first > P[stop].first)
                stop = i;
        }

        long size= cmp(start,stop);
        for(long i= start; i<size; ++i)
            if(P[i%n].first > P[(i+1)%n].first) return 0;

        size= cmp2(start,stop);
        for(long i = size; i>stop; --i)
            if(P[i%n].first > P[(i-1)%n].first) return 0;

    }
    else{
        for(long i=0;i<P.size();++i) {
            if (P[i].second < P[start].second)
                start = i;
            if(P[i].second > P[stop].second)
                stop = i;
        }

        long size= cmp(start,stop);
        for(long i= start; i<size; ++i)
            if(P[i%n].second > P[(i+1)%n].second) return 0;

        size= cmp2(start,stop);
        for(long i = size; i>stop; --i)
            if(P[i%n].second > P[(i-1)%n].second) return 0;
    }

    return 1;

}

void citire(){
    cin>>n;
    P.resize(n);
    for(int i=0;i<n;i++)
        cin>>P[i].first>>P[i].second;
}

int main() {
    citire();

    int rezultat = monotonie(true);
    if(rezultat==1)
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    rezultat = monotonie(false);
    if (rezultat==1)
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    return 0;
}
