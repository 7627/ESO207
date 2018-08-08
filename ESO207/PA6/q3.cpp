#include<iostream>
#include<vector>
#include<string.h>
using namespace std;

int main(){
  vector<string>table(63,"");
  vector<string>backup;
  int i,size,rem;
  double code;
  string str, symbol,result;
  char c='A';

  for(i=0;i<63;i++){
    table[i]=c;
    if(c=='Z') c='a';
    else if(c=='z') c='0';
    else if(c=='9') c=' ';
    else c++;
    // cout<<table[i]<<" "<<i<<endl;
  }
  table.push_back("clear");
  backup=table;


  cin>>code;
  // cout<<code<<endl;
  while(code!=-1){
    ///////////////////
    size=table.size()-1;
    // rem=code%1;


    if(code>size || code<-1 || code!=(int)code){
      // cout<<code<<endl;
      cout<<"Archive is corrupted!"<<endl;
      return 0;
    }
    if(code==63){
      table=backup;
      cin>>code;
      continue;
    }
    if(code==-1) break;


    ////////////////////////////////////////////////////
    str=table[code];
    // cout<<str;
    result=result+str;
    cin>>code;



    size=table.size()-1;
    // rem=(code%1);
    if(code > size || code<-1 || code!=(int)code){
      cout<<"Archive is corrupted!"<<endl;
      // cout<<(code > (table.size()-1))<<endl;
      // cout<<code<<" "<<(table.size()-1)<<" "<<size<<endl;
      return 0;
    }
    if(code==63){
      table=backup;
      cin>>code;
      continue;
    }
    if(code==-1) break;



    symbol=table[code];
    // cout<<symbol<<endl;
    str=str+symbol[0];
    table.push_back(str);
  }

  cout<<result<<endl;


  // for(i=62;i<table.size();i++){
  //   cout<<i<<" "<<table[i]<<endl;
  // }
}
