#include<iostream>
#include<vector>
using namespace std;

void function(vector<int>*v,int* a){
  vector<int>V=(*v);
  int A=*a;
  A=15;
  (V)[0]=2;
}

int main(){
  vector<int>v;
  int a=12;
  v.push_back(1);
  printf("Initially:%d %d\n",v[0],a);
  function(&v,&a);
  printf("finally:%d %d\n",v[0],a);
}
