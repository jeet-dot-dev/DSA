#include <iostream>
#include<vector>
using namespace std;
int main()
{
    pair<int, int> p = {1, 2};
    pair<string, char> p1 = {"jeet", 'j'};
    pair<int, pair<int, int>> p3 = {1, {2, 3}};
    vector <pair<int,int>> v = {{1,2},{2,3},{4,5}};
    for(auto p : v){
        cout<<"{"<<p.first<<","<<p.second<<"}"<<endl;
    }
    v.emplace_back(5,6);
    for(auto p : v){
        cout<<"{"<<p.first<<","<<p.second<<"}"<<endl;
    }
    cout << p3.first;
    cout << p3.second.first;

    return 0;
}
