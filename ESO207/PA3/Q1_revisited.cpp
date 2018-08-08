// August 04, 2018
// Practicing all ESO207 assignment questions for internship
// Done : Using OOP(lil bit)

#include<iostream>
#include<vector>
using namespace std;

class Heap{
  vector<string> v;
public:
  Heap(){
    v.push_back("-1");
  }

  void learn(string word){
    v.push_back(word);
    int i;
    for(i=v.size()-1; i/2>0;){
      if(v[i] < v[i/2]){
        swap(v[i], v[i/2]);
        i=i/2;
      }
      else{
        return;
      }
    }
  }

  void reportSmallest(){
    cout<<v[1]<<endl;
    // cout<<"hello"<<endl;
  }

  void forgetSmallest(){
      v[1] = v[v.size()-1];
      v.erase(v.end());
      if(v.size() < 2) return;
      int i;
      int min_index;
      for(i=1; 2*i<v.size(); ){
        int c1,c2;
        c1=2*i;
        c2=(2*i+1 < v.size())? 2*i+1:2*i;
        min_index = (v[c1] > v[c2])? c2:c1;
        if(v[i] > v[min_index]){
          swap(v[i], v[min_index]);
          i = min_index;
        }
        else return;
      }
  }

  void print(){
    int i;
    for(i=0;i<v.size();i++){
      cout<<i<<" "<<v[i]<<endl;
    }
  }


};





int main(){
  int i,n;
  cin>>n;
  string cmd,word;
  Heap h;
  for(i=0;i<n;i++){
    cin>>cmd;
    // cout<<"cmd = "<<cmd<<" word = "<<word<<endl;
    if(cmd=="l"){
      cin>>word;
      h.learn(word);
    }
    if(cmd=="r"){
      h.reportSmallest();
    }
    if(cmd=="f"){
      h.forgetSmallest();
    }
    cout<<endl;
    h.print();
  }
  h.reportSmallest();
  h.print();
}
