// Practising Dijkstra
//28 July 2018
// hopefully completed on same day
#include<iostream>
#include<vector>
using namespace std;

struct Node{
  int v; //vertex
  int w; //weight
  struct Node* next;
};

Node* createNode(int v, int w){
  Node* root = (Node*)calloc(1,sizeof(Node));
  root->v = v;
  root->w = w;
  return root;
}
Node* insertNode(Node*root, int v, int w){
  Node* tmp=createNode(v,w);
  tmp->next=root;
  return tmp;
  // if(root == NULL){
  //   root = createNode(v,w);
  //   return root;
  // }
  // while(root->next != NULL){
  //   root=root->next;
  // }
  // root->next = createNode(v,w);
  // return root;

}

int deletemin(vector<int> d){
  int V = d.size();
  int i=0;
  int min=0;
  for(i=0;i<V;i++){
    if(d[i] < d[min]){
      min = i;
    }
  }
  return min;
}

Node* del(Node* root, int s){
  Node* tmp = root;
  if(root->v == s){
    Node*x = root->next;
    free(root);
    return x;
  }
  while(root->next!=NULL){
    if(root->next->v == s){
      Node* x = root->next;
      root->next = root->next->next;
      free(x);
      return tmp;
    }
    root=root->next;
  }
}

int main(){
  int i;
  int v1,v2,w;
  int V,E;
  int inf = 99999;
  cin>>V>>E; //V= #cities, E=#roads

  vector<Node*> adj(V,NULL);

  for(i=0;i<E;i++){
    cin>>v1>>v2>>w;
    adj[v1] = insertNode(adj[v1], v2, w);
    adj[v2] = insertNode(adj[v2], v1, w);
  }

  for(i=0;i<V;i++){
    Node*t = adj[i];
    cout<<i<<" :    ";
    while(t!=NULL){
      cout<<t->v<<" ";
      t=t->next;
    }
    cout<<endl;

  }
  int s=0;
  vector<int> D(V,inf);
  vector<int> d(V,inf);
  D[s]=0;
  d[s]=0;

  int count=0;
  while(count != V){
    int s = deletemin(d);
    d[s] = inf+1;
    count++;
    cout<<count<<endl;

    Node*tmp = adj[s];
    while(tmp != NULL){
      int ver = tmp->v;
      int weight = tmp->w;
      if(D[ver] > D[s]+weight){
        D[ver] = D[s]+weight;
        d[ver] = D[s]+weight;
      }

      cout<<"deleting "<<s<<" from adj list of "<<ver<<endl;
      adj[ver] = del(adj[ver], s);
      tmp=tmp->next;
    }
  }

  for(i=0;i<V;i++){
    cout<<" vertex "<<i<<" shortest path= "<<D[i]<<endl;
  }


  return 0;
}
