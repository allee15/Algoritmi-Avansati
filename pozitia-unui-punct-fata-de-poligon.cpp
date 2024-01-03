#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//returneaza cel mai departe punct
pair<long, long> getFarthestPoint (const vector<pair<long,long>>& P){
    pair<long,long> farthest = P[0];
    for(const auto&p :P){
        if(p.first >farthest.first)
            farthest = p;
        else{
            if(p.first == farthest.first && p.second> farthest.second)
                farthest = p;
        }
    }
    farthest.first +=1000000;
    farthest.second +=1000000;
    return farthest;
}

int countIntersection(long n,const pair<long,long>&a, const pair<long,long>&b, const vector<pair<long,long>>& P){
    int count =0;

    for(long i=0;i<n;i++){
        long j=(i+1)%n;
        if(a.first == P[i].first && a.second==P[i].second){
            //a este punct al polig si alegem alt punct departat
            pair<long,long> farthest = getFarthestPoint(P);
            if(farthest == a) farthest = {farthest.first + 1, farthest.second + 1}; // evitare buclă infinită
            return countIntersection(n,a,farthest,P);
        }
        if(a.first == P[j].first && a.second == P[j].second){
            //a e punct al polig, alegem alt punct
            pair<long,long> farthest = getFarthestPoint(P);
            if(farthest == a) farthest = {farthest.first + 1, farthest.second + 1}; // evitare buclă infinită
            return countIntersection(n,a,farthest,P);
        }

        if(b.first == P[i].first && b.second==P[i].second){
            //b este punct al polig si alegem alt punct departat
            pair<long,long> farthest = getFarthestPoint(P);
            if(farthest == b) farthest = {farthest.first + 1, farthest.second + 1}; // evitare buclă infinită
            return countIntersection(n,b,farthest,P);
        }
        if(b.first == P[j].first && b.second == P[j].second){
            //b e punct al polig, alegem alt punct
            pair<long,long> farthest = getFarthestPoint(P);
            if(farthest == b) farthest = {farthest.first + 1, farthest.second + 1}; // evitare buclă infinită
            return countIntersection(n,b,farthest,P);
        }


        if((a.second > P[i].second) != (b.second>P[i].second) && (b.first-a.first)*(P[i].second-a.second) < (P[i].first-a.first)*(b.second-a.second))
            count++;
    }
    return count; //nr de intersectii dintre sg format de punct si cel mai departat punct din poligon si laturile polig
}//dc count este impar=> punctul e inside
//dc count este par=> punctul e outside
//dc count ==0 => punctul e boundary

//verif daca punctul este in interiorul polig
int isInside(long n, const pair<long,long>&p, const vector<pair<long,long>>&P){
    pair<long,long> farthest = getFarthestPoint(P);
    int count = countIntersection(n,p,farthest,P);
    if(count%2==1) return 1; //inside
    else {
        if(count==0) return 0; //boundary
        else return 2; //outside
    }
}

int main() {
    vector<pair<long,long>>P,Q;
    long n,m;
    cin>>n;
    P.resize(n);
    for(long i=0;i<n;i++)
        cin>>P[i].first>>P[i].second;
    cin>>m;
    Q.resize(m);
    for(long i=0;i<m;i++)
        cin>>Q[i].first>>Q[i].second;

    for(long i=0;i<m;i++) {
        int k= isInside(n,Q[i], P);
        if ( k== 0) cout << "BOUNDARY" << endl;
        else {
            if (k==1) cout<<"INSIDE"<<endl;
            else cout<<"OUTSIDE"<<endl;
        }
    }

    return 0;
}
