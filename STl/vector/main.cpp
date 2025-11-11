#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> vec;
    vec.push_back(5); // cap -> 1
    vec.push_back(6); // cap -> 2
    vec.push_back(9); // cap -> 4
    vec.push_back(5); // cap -> 4
    vec.push_back(56); // cap -> 8
   // cout<<vec.capacity()<<endl;
    // for(int i = 0 ; i<vec.capacity() ; i++){
    //     cout<<vec[i]<<endl;
    // }

    // front & back 
   // cout<<vec.front()<<endl;
   // cout<<vec.back()<<endl;

    // intializing a vector 
    vector<int> vec2 = {2,3,5};
    vector <int> vec3(9,10); 
    // for(int val : vec3){
    //     cout<<val<<endl;
    // }
    vector <int> vec4(vec2);

    // erase insert 
    vec.erase(vec.begin());
    vec.insert(vec.begin()+2,8);
     for(int val : vec){
        cout<<val<<endl;
    }
    return 0;
}