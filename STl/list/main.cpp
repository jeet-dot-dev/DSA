#include<iostream>
#include<list>
using namespace std ;

int main(){
    list<int> l;
    l.push_back(5);
    l.push_front(1);
    for(int val : l){
        cout<<val;
    }
}
