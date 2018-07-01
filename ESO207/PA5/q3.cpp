#include<iostream>
#include<vector>
using namespace std;

int INF=1000000;
int V,E; //number of vertices and edges

typedef struct node{
  int v; //vertex
  int w; //weight of the edge
  struct node* next;
} Node;

int deletemin(vector<int>*q){
  int i=0;
  // vector<int>Q=(*q);
  int index=0;
  for(i=0;i<V;i++){
    if((*q)[i]<(*q)[index]){
      index=i;
    }
  }
  (*q)[index]=INF+1;
  return index;
}

// void Relax(vector<node*>*x,int u,int v){
//   vector<Node*>Q=(*x);
//   if()
// }


Node* insertNode(Node* head,int v, int w){
  Node*tmp=(Node*)calloc(1,sizeof(Node));
  tmp->v=v;
  tmp->w=w;
  tmp->next=head;
  return tmp;
}



int main(){
  int i,v1,v2,w;
  cin>>V>>E;
  vector <Node*> adj(V,NULL); //adjacency list with elementa neighbours of vertex

  for(i=0;i<E;i++){
    cin>>v1>>v2>>w;
    adj[v1]=insertNode(adj[v1],v2,w);
    adj[v2]=insertNode(adj[v2],v1,w);
  }
  // for(i=0;i<V;i++){ //print the adjacency list
  //   Node*tmp;
  //   tmp=adj[i];
  //   while(tmp!=NULL){
  //     cout<<tmp->v<<" "<<tmp->w<<"   ";
  //     tmp=tmp->next;
  //   }
  //   cout<<endl;
  // }

  //initialize some arrays to store parents, distances etc
  vector<int> d(V,INF); // Size=V, Initialize with  INF;
  vector<int> pi(V,-1);//stores parents of nodes
  vector<int> S; //used to store vertices we are done with;
  vector<int>Q(V,INF); // Q is like set of all vertices;
  int s=0;//starting vertex
  int t=V-1;//target vertex
  d[s]=0;//initialize distance of source as zero
  Q[s]=0;
  int u=s; //present vertex
  int count=0;
  int cost=0;
  /////////////////////////Prim's///////////////////////////////////
  while(count!=V){
    u=deletemin(&Q);
    count++;
    if(count!=1){//dont do this step for 1st iteration
      // cout<<"parent of "<<u<<" is ="<<pi[u]<<endl;
      Node* x=adj[pi[u]];
      while(x->v!=u) x=x->next;
      cost=cost+x->w;
      // cout<<"cost after "<<count<<" ="<<cost<<endl;
    }
    // for(i=0;i<V;i++){
    //   cout<<"d["<<i<<"]="<<d[i]<<endl;
    // }
    // cout<<endl;
    // for(i=0;i<V;i++){
    //   cout<<"Q["<<i<<"]="<<Q[i]<<endl;
    // }
    // cout<<"extract_min="<<u<<endl;
    Node* l=adj[u];
    while(l!=NULL){
      int v=l->v;
      int w=l->w;
      // cout<<"v,w="<<v<<", "<<w<<endl;
      if(d[v]>w){
        // cout<<"changing distance"<<endl;
        d[v]=w;
        Q[v]=w;
        // cout<<"d["<<v<<"]="<<d[v];
        // cout<<" Q["<<v<<"]="<<Q[v]<<endl<<endl;
        pi[v]=u;
      }
      // cout<<"d["<<v<<"]="<<d[v]<<endl;
      Node*f=adj[v]; //delete u from graph
      if(f->v==u){
        adj[v]=f->next;
        // cout<<"deleting "<<f->v<<endl;
        free(f);
      }
      else{
        while(f->next->v!=u){
          f=f->next;
        }
        Node*temp=f->next;
        f->next=f->next->next;
        // cout<<"deleting "<<temp->v<<endl;
        free(temp);
      }

      l=l->next;
    }
    // for(i=0;i<V;i++){
    //   cout<<"d["<<i<<"]="<<d[i]<<endl;
    // }
    // cout<<endl;
    // for(i=0;i<V;i++){
    //   cout<<"Q["<<i<<"]="<<Q[i]<<endl;
    // }
  }
  // for(i=0;i<V;i++){
  //   cout<<"d["<<i<<"]="<<d[i]<<endl;
  // }
  // cout<<endl;
  // for(i=0;i<V;i++){
  //   cout<<"Q["<<i<<"]="<<Q[i]<<endl;
  // }
  cout<<cost<<endl;













  return 0;

}
