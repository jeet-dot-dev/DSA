#include<iostream>
#include<stack> // last in first out
using namespace std ;
int main(){
    stack <int> s ;
    s.push(1);
    s.push(2);
   // cout<<s.top();
    while(!s.empty()){
        cout<<s.top()<<endl;
        s.pop();
    }
    return 0;
}