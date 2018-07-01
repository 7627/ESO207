#include<iostream>
#include<vector>
using namespace std;

vector<string> v;

int min(int s1,int s2){
  return v[s1]<v[s2]? s1:s2;
}
void swap(int ind1,int ind2){
  string x=v[ind1];
  v[ind1]=v[ind2];
  v[ind2]=x;
}

void learn(string str){
  int i=v.size();
  int parent=i/2;
  v.push_back(str);
  while(i!=0){
    if(v[i]<v[parent]){
      swap(i,parent);
      i=parent;
      parent=i/2;
    }
    else return;
  }
}
void print(){
  int i;
  for(i=0;i<v.size();i++){
    cout<<v[i]<<"\t";
  }
}

void deleteMin(){
  // cout<<"v.size()= "<<v.size()<<endl;
  int i=v.size()-1;
  if(i==0){
    // cout<<"No element present"<<endl;
    return;
  }
  if(i==1){
    cout<<v[1]<<endl;
    v.erase(v.end());
    // cout<<"Empty now"<<endl;
    return;
  }
  cout<<v[1]<<endl;

  v[1]=v[i];
  v.erase(v.end());
  i=1;
  int c1=2*i;
  int c2=2*i+1; c2<v.size()? c2=c2:c2=c1; //in case node have only one child, the second child is same as first
  // cout<<"v[i]="<<v[i]<<"\ti="<<i<<"c2="<<c2<<"\tc1="<<c1<<endl;
  while(c2<v.size()){
    if(v[i]<=v[min(c1,c2)]){
      return;
    }
    else{
      int j=min(c1,c2);
      swap(i,min(c1,c2));
      i=j;
      c1=2*i;
      c2=2*i+1; c2<v.size()? c2=c2:c2=c1;
      // cout<<"v[i]="<<v[i]<<"\ti="<<i<<"c2="<<c2<<"\tc1="<<c1<<endl;
    }
  }
}

void reportSmallest(){
  if(v.size()>=2){
    cout<<v[1]<<endl;
  }
  return;
}

int main(){
  int t,i;
  scanf("%d",&t);
  // cout<<"t= "<<t<<endl;
  v.push_back("-1");
  string cmd,word;
  for(i=0;i<t;i++){
    // cout<<"v= ";print();
    cin>>cmd;
    if(cmd=="learn"){
      // cout<<"learning\t";
      cin>>word;
      learn(word);
    }
    if(cmd=="reportsmallest"){
      reportSmallest();
    }
    if(cmd=="forgetsmallest"){
      deleteMin();
    }
    // cout<<"v=";print();
  }

}
