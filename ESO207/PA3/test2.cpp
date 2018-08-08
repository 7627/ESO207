#include<iostream>
#include<vector>
using namespace std;

void function_vector(vector<int>v, int n){
  v[1]=n;
}

void function_array(int a[3], int n){
  a[1]=n;
}

int main(){
  vector<int>v;
  v.push_back(1);
  v.push_back(2);
  int i;
  for(i=0;i<v.size();i++){
    cout<<v[i]<<endl;
  }

  function_vector(v,3);

  for(i=0;i<v.size();i++){
    cout<<v[i]<<endl;
  }

  cout<<endl<<endl;



  int a[3];
  a[0]=1;
  a[1]=2;
  // int i;
  for(i=0;i<2;i++){
    cout<<a[i]<<endl;
  }

  function_array(a,3);

  for(i=0;i<2;i++){
    cout<<a[i]<<endl;
  }
}
