#include<iostream>
#include<vector>
using namespace std ;

int main (){
    vector<int>::iterator i ;
    vector<int> :: reverse_iterator it;
    vector<int> vec = {4,5,1,2};
    // for(i= vec.begin() ; i!=vec.end();i++){
    //     cout<<*(i)<<endl;
    // }
    for(it =vec.rend() ; it!= vec.rbegin() ;it--){
        cout<<*(it)<<endl;
    }
    return 0 ;
}