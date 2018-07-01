#include<iostream>
#include<vector>
using namespace std;

typedef struct node{
  int v;
  struct node* next;
} Node;

typedef struct sort{
  int v;
  Node* head;
  struct sort* next;
} sort;

typedef struct Stack{
  int v;
  struct Stack* next;
} Stack;

Stack* stack= NULL;
int mini; //stores minimum value of label in a SCC
// vector<Node*>adj(n,NULL);

Stack* push(Stack* head, int v){
  Stack* tmp= (Stack*)calloc(1,sizeof(Stack));
  tmp->v=v;
  tmp->next=head;
  return tmp;
}

Node* insertNode(Node* head, int v){
  Node* tmp=(Node*)calloc(1,sizeof(Node));
  tmp->v=v;
  tmp->next=head;
  return tmp;
}

sort* insertSort(sort* sorted, int mini, Node* k){
  sort* head=sorted;
  sort*tmp=(sort*)calloc(1,sizeof(sort));
  tmp->v=mini;
  tmp->head=k;
  if(sorted==NULL || sorted->v > mini){
    tmp->next=sorted;
    return tmp;
  }
  while(sorted->next!=NULL){
    if(sorted->next->v > mini){
      tmp->next=sorted->next;
      sorted->next=tmp;
      return head;
    }
    sorted=sorted->next;
  }
  sorted->next=tmp;
  return head;
}

void DFS_visit(vector<Node*>*adj, vector<int>*visited, vector<int>*parent, int v){ //recursively visit the graph starting from
  (*visited)[v]=1;
  // cout<<"Visiting "<<v<<endl;

  Node* l=(*adj)[v];
  while(l!=NULL){
    int u= l->v;
    // cout<<"u= "<<u<<endl;
    if((*visited)[u]==0){// i.e unvisited
      (*parent)[u]=v;
      DFS_visit(adj, visited, parent, u);
      stack= push(stack,u);
    }
    l=l->next;
  }
}


Node* DFS_visit_T(vector<Node*>*adj, vector<int>*visited, vector<int>*x, Node* k, vector<int>*y, int v){ //recursively visit the graph starting from
  (*visited)[v]=1;
  // cout<<"Visiting "<<v<<endl;

  Node* l=(*adj)[v];
  while(l!=NULL){
    int u= l->v;
    // cout<<"u= "<<u<<endl;
    if((*visited)[u]==1 && (*y)[u]!=-1){
      //edge to another already visited SCCs
      k=insertNode(k,(*y)[u]); //insert the SCC number
    }
    if((*visited)[u]==0){// i.e unvisited
      if(u<mini) mini=u;
      (*x).push_back(u); //store all the visiting vertices in a array
      k=DFS_visit_T(adj, visited, x, k, y, u);
    }
    l=l->next;
  }

  return k;
}



int main(){
  int n,v,i;
  cin>>n; //number of vertices
  vector<Node*>adj(n,NULL); //Adjacency list
  vector<Node*>adj_T(n,NULL); //Transpose of Adjacency list
  for(i=0;i<n;i++){ //reading the adjacencylist input
    cin>>v;
    while(v!=-1){
      adj[i]=insertNode(adj[i],v);
      adj_T[v]=insertNode(adj_T[v],i);
      cin>>v;
    }
  }

  // for(i=0;i<n;i++){
  //   Node* tmp=adj[i];
  //   while(tmp!=NULL){
  //     cout<<tmp->v<<" ";
  //     tmp=tmp->next;
  //   }
  //   cout<<endl;
  // }

  ///////////Initialize////////
  vector<int>visited(n,0);
  vector<int>parent(n,-1);

  ////////////Initially run on adjacency list and make a stack according to finishing time
  for(i=0;i<n;i++){
    if(visited[i]==0){
      // cout<<"Running DFS_visit on "<<i<<endl;
      DFS_visit(&adj, &visited, &parent, i);
      stack=push(stack,i);
    }
  }

  // Stack* z=stack;
  // cout<<endl<<"Stack: "<<endl;
  // while(stack!=NULL){
  //   cout<<stack->v<<" "<<endl;
  //   stack=stack->next;
  // }
  // stack=z;

  /////////////////////Now run DFS on Transpose of Adj/////////////////////
  for(i=0;i<n;i++)
    visited[i]=0;

vector<int>x; //stores the vertices visited by a DFS_visit_T
vector<int>y(n,-1);//stores the SCC number of all vertices
Node* k=NULL; //stores the other SCCs visited during a DFS_visit_T
sort* sorted=NULL; //stores the sorted mini values
vector<Node*>adj_new; //will store the new graph by resulting SCCs
int count=0; //counts the number of SCC
  while(stack!=NULL){
    int u=stack->v;
    if(visited[u]==0){
      count++;
      mini=u;
      x.push_back(u);
      k=NULL;
      k=DFS_visit_T(&adj_T,&visited,&x,k,&y,u);//parent is not needed, but still
      // cout<<"mini in SCC= "<<mini<<endl;

      int j=0; //store the SCC of visited vertices
      for(j=0;j<x.size();j++){
        y[x[j]]=mini;
      }
      x.clear(); //makes the empty, ready for use again

      //////////////storing the sorted min values/////////////////////
      sorted=insertSort(sorted,mini,k);
  //     sort* fuck=sorted;
  //     cout<<endl<<"Fuck: "<<endl;
  //     while(fuck!=NULL){
  //       cout<<endl<<" Fuck is "<<fuck->v<<endl;
  //       Node* yoyo=fuck->head;
  //       while(yoyo!=NULL){
  //         cout<<"  "<<yoyo->v;
  //         yoyo=yoyo->next;
  //       }
  //       fuck=fuck->next;
  //     }
    }
    stack=stack->next;
  }
  cout<<count<<endl;

  // for(i=0;i<n;i++){
  //   cout<<"SCC of "<<i<<" is : "<<y[i]<<endl;
  // }


  //////////////yahan tak sorted ban gya///////ab dekho kya karna hai//////////
  i=0;
  int j=0,u;
  sort* start=sorted;
  sort*tmp=sorted;
  while(start!=NULL){
    u=start->v;
    tmp=sorted;
    j=0;
    while(tmp!=NULL){
      Node*head= tmp->head;
      while(head!=NULL){
        if(head->v==u){
          cout<<j<<" ";
          break;
        }
        head=head->next;
      }
      j++;
      tmp=tmp->next;
    }
    cout<<"-1"<<endl;
    start=start->next;

  }





  // example graph
  // 9
  // 1 -1
  // 4 3 2 -1
  // 5 -1
  // -1
  // 0 -1
  // 6 -1
  // 7 -1
  // 8 -1
  // 2 -1



  return 0;
}
