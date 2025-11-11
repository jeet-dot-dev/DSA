#include<iostream>
#include<vector>
using namespace std ;
int main(){
    vector <int> vec ; //size & capacity = 0
    vec.push_back(5); //size =1 capacity = 1
    vec.push_back(6); // size =2 capacity = 2
    vec.push_back(9) ; // size =3 capacity = 4
    cout<<vec.size()<<endl;
    cout<<vec.capacity()<<endl;
    for(int val : vec){
        cout << val << " ";
    }
    cout<<endl;
    return 0;
}

