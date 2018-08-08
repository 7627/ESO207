#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

int count1=0;

typedef struct node{
  int v; //vertex
  struct node* next;
} Node;

Node* insertNode(Node* head,int v){
  Node*tmp=(Node*)calloc(1,sizeof(Node));
  tmp->v=v;
  tmp->next=head;
  return tmp;
}

void DFS_visit(vector<Node*>*adj, vector<int>* visited, vector<int>*parent, vector<int>*dtime, vector<int>*low_time, vector<int>*art_p, int flag, int v){
  (*visited)[v]=1;
  // cout<<"Visiting "<<v<<endl;
  int i=0;
  // for(i=0;i<(*dtime).size();i++){
  //   cout<<i<<" dtime: "<<(*dtime)[i];
  //   cout<<" low_time: "<<(*low_time)[i]<<endl;
  // }
  int nos=0; //counts the number of DFS visit recursions done by root
  Node* l=(*adj)[v];

  while(l!=NULL){
    int u= l->v;
    // cout<<"u= "<<u<<endl;
    if((*visited)[u]==1 && u!=(*parent)[v]){
      if((*low_time)[v] > (*dtime)[u]){
        (*low_time)[v] = (*dtime)[u];
        // cout<<"updating low_time of "<<v<<" : "<<(*low_time)[v]<<endl;
      }
    }
    if((*visited)[u]==0){// i.e unvisited
      (*parent)[u]=v;
      (*dtime)[u]=++count1;
      (*low_time)[u]=count1; //initially dtime and low_time are same
      nos++;
      DFS_visit(adj, visited, parent, dtime, low_time, art_p, 0, u);

      if((*low_time)[v] > (*low_time)[u]){
        (*low_time)[v] = (*low_time)[u];
        // cout<<"updating low_time of "<<v<<" : "<<(*low_time)[v]<<endl;
      }
      if((*dtime)[v] <= (*low_time)[u] && flag!=1){
        (*art_p)[v]=1;
      }
    }
    l=l->next;
  }
  if(nos>1 && flag==1){
    // cout<<v<<" is root and ar_p point "<<endl;
    (*art_p)[v]=1;
    return;
  }
  // if(flag==1) return;
  // cout<<" nos= "<<nos<<endl;

  ///////////////////////////////////////////////////////////////
  // Node* x=(*adj)[v];
  // while(x!=NULL){
  //   int w=x->v;
  //   if(w!=(*parent)[v]){
  //     cout<<"dtime of "<<v<<" : "<<(*dtime)[v]<<" low_time : "<<(*low_time)[v]<<endl;
  //     cout<<"dtime of "<<w<<" : "<<(*dtime)[w]<<" low_time : "<<(*low_time)[w]<<endl;
  //     if((*dtime)[v] <= (*low_time)[w]){
  //       if(art_p.size()==0){
  //         cout<<v<<" is a ar_p point "<<endl;
  //         art_p.push_back(v);
  //       }
  //       else if(v!=art_p.back()){ //if not already pushed
  //         art_p.push_back(v); //v is a articulation point
  //         cout<<v<<" is a ar_p point "<<endl;
  //       }
  //     }
  //     if((*low_time)[v] > (*low_time)[w]){
  //       (*low_time)[v] = (*low_time)[w];
  //       cout<<"updating low_time of "<<v<<" : "<<(*low_time)[v]<<endl;
  //     }
  //   }
  //   x=x->next;
  // }
  /////////////////////////////////////////////////////////////
  // cout<<v<<" done "<<endl<<endl;
}


//////////////Find articulation points//////////////
int main(){
  int n,m,v1,v2,i;
  cin>>n>>m; //n= #vertices, m=#edges
  vector<Node*>adj(n,NULL); //adjacency list with elementa neighbours of vertex
  for(i=0;i<m;i++){
    cin>>v1>>v2;
    adj[v1]=insertNode(adj[v1],v2);
    adj[v2]=insertNode(adj[v2],v1);
  }
  // for(i=0;i<n;i++){ //print the adjacency list
  //   Node*tmp;
  //   tmp=adj[i];
  //   while(tmp!=NULL){
  //     cout<<tmp->v<<" ";
  //     tmp=tmp->next;
  //   }
  //   cout<<endl;
  // }



  ///////////Initialiation for DFS/////////////
  vector<int>visited(n,0);
  vector<int>parent(n,-1);
  vector<int>dtime(n,-1);
  vector<int>low_time(n,-1);
  vector<int>art_p(n,0);

  int s=0;
  dtime[s]=count1;
  low_time[s]=count1;
  DFS_visit(&adj, &visited, &parent, &dtime, &low_time, &art_p, 1, s); //1 is a flag which tells it that root is special

  // for(i=0;i<n;i++){
  //   cout<<i<<" dtime: "<<dtime[i];
  //   cout<<" low_time: "<<low_time[i]<<endl;
  // }
  // sort(art_p.begin(),art_p.end());
  for(i=0;i<n;i++){
    if(art_p[i]==1)
    cout<<i<<endl;
  }


  return 0;
}
