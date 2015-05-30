#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#define width 1000
#define siz 100//Square of width
using namespace std;
class Node
{
 public:
  int edge;
  int cellno;
  int j;
  int k;
  int visit;
  Node *next;
  Node *up;
  Node *down;
  Node *left;
  Node *right;
  char chd,chl,chr;
  Node()
  {
  }
  Node(int i)
  {
      up=NULL;
      down=NULL;
      left=NULL;
      right=NULL;
      next=NULL;
      visit=0;
      j=i/width;
      k=i%width;
      cellno=i;
      if(k==0)
      left=NULL;
      if(k==(width-1))
       right=NULL;
      if(j==0)
       up=NULL;
      if(j==(width-1))
         down=NULL;
         if(j==0||j==(width-1))
        {
            if(k==0||k==(width-1))
                edge=2;
            else
                edge=1;
        }
        else if(k==0||k==(width-1))
        {
            if(j==0||j==(width-1))
                edge=2;
            else
                edge=1;
        }
        else
            edge=0;
    chl=' ';
    chd=' ';
    chr=' ';
  }
  void represent()
  {

        if(left==NULL)
            chl='|';
        if(down==NULL)
            chd='_';
        if(right==NULL)
            chr='|';
  }

};
Node *getneighbours(int n,Node *&start,int & s,Node *gr,Node *nbrs);
Node *makelist(Node *st,int i);
Node *connect(Node *grid,Node *nod);
void display(Node *start);
void solve(Node *start);
Node *Prim(Node *st);
int Present(Node *lst,int data);
Node *srch(Node *&st,int i);
Node *addlist(Node *lst, Node *nod);
void print(Node *st);//Not using, to be removed
void showlist(Node *st);
Node *sorting1(Node *&head);
int main()
{
  Node *start=NULL;
  for(int i=0;i<siz;i++)
  start=makelist(start,i);
  //cout<<"Generating a "<<width<<"X"<<width<<" maze\n";
  start=Prim(start);
  start=sorting1(start);
  Node *n=start;
  while(n!=NULL)
  {
      n->represent();
      n=n->next;
  }
   display(start);
  char c;
  //cout<<"\nEnter any character to solve:";
  c=getchar();
  //cout<<"Entering Maze at 0,0\nExit at "<<width<<","<<width<<"\nPath:"<<endl;

  solve(start);

}
int Present(Node *lst,int data)//Checks if the passed data is present in the passed list
{
    Node *n=lst;
    while(n!=NULL)
    {
        if(n->cellno==data)
            return 1;
         n=n->next;
    }
    return 0;
}
Node *makelist(Node *st,int i)//Makes a singly linked list
{
    Node *n,*p;
    n=new Node(i);
    p=st;
    if(st==NULL)
      st=n;
     else
   {
     while(p->next!=NULL)
      p=p->next;
     p->next=n;
   }
    return st;
}
void display(Node *start)//Uses special characters to represent the maze graphically
{
    Node *x=start;
    cout<<endl;
    for(int i=0;i<=width*2;i++)
        cout<<"_";
    cout<<endl<<"|";
    while(x!=NULL)
    {
      cout<<x->chd<<x->chr;
      if((x->cellno+1)%width==0)
        cout<<endl<<"|";
      x=x->next;
    }
}
Node *srch(Node *&st,int i)//Looks for the passed data in the list and returns extracts that node from the list
{
   if(!Present(st,i))
        return NULL;
    Node *p,*q;
    p=st;
    while(p->cellno!=i)
     {
         q=p;
         p=p->next;
     }
     if(st==p)
       st=st->next;
     else
        q->next=p->next;
     p->next=NULL;
    return p;
}
int getcell(Node *st,int n)//Returns the data at position 'n' in the list
{
    Node *p=st;
    for(int i=0;i<n;i++)
       p=p->next;
    return p->cellno;
}
Node *Prim(Node *st)//Runs Prim's algorithm to generate the maze
{
    Node *graph,*neighbours=NULL,*gr;
    srand(time(0));
    int n,i=0,s=0;
    n=rand()%siz;
    graph=srch(st,n);//Random starting point
    //cout<<"Starting point of maze generation is:"<<graph->j<<","<<graph->k<<endl;
    neighbours=getneighbours(n,st,s,graph,neighbours);//Getting a list of the selected node's neighbours
    //cout<<"size "<<s<<endl;
   // showlist(neighbours);
    //cout<<endl<<s;
    do
    {
      n=rand()%s;
      n=getcell(neighbours,n);
      gr=srch(neighbours,n);//selecting a node from list of neighbours
      s--;
       //cout<<endl<<gr->cellno;
      //cout<<"Before nbrs:\n";
    //showlist(neighbours); //working
      neighbours=getneighbours(n,st,s,gr,neighbours);//working
      //cout<<"After nbrs:\n";
      //showlist(neighbours); //working
      graph=connect(graph,gr);//adding selected node to the maze
      graph=addlist(graph,gr);
      i++;//Keeping a count of the iterations of the loop
      //cout<<"Graph:";
      //cout<<endl<<"Showlist"<<endl;
      //showlist(graph);//working
      //cout<<endl<<"//////"<<i<<"??????????"<<endl;
    }while(neighbours!=NULL);
    //cout<<"No of iterations of do-while loop"<<i;
    //cout<<graph->cellno;
    return graph;
}
Node *connect(Node *grid,Node *nod)//Connects selected nodes to the maze grid
{
  //cout<<"/ "<<nod->cellno<<" ";
  Node *nr[4],*g;
  int i=0,cn;
  cn=nod->cellno;
  g=grid;
  //cout<<" "<<cn<<" ";
  if(Present(grid,(cn-width)))//Checking if upper neighbour is present in maze
  {
    while(g!=NULL)
    {
      if(g->cellno==(cn-width))
       {
          // cout<<" |"<<g->cellno<<"| ";
           nr[i]=g;
           i++;
           break;
       }
       g=g->next;
    }
  }
  g=grid;
  if(Present(grid,(cn+width)))
  {
    while(g!=NULL)
    {
      if(g->cellno==(cn+width))//Checking if lower neighbour is present in maze
       {
          // cout<<" |"<<g->cellno<<"| ";
           nr[i]=g;
           i++;
           break;
       }
       g=g->next;
    }
  }
  g=grid;
  if(cn%width!=0)
   if(Present(grid,(cn-1)))//Checking if left neighbour is present in maze
   {
     while(g!=NULL)
     {
       if(g->cellno==(cn-1))
       {
           //cout<<" |"<<g->cellno<<"| ";
           nr[i]=g;
           i++;
           break;
       }
       g=g->next;
     }
   }
  g=grid;
  if((cn+1)%width!=0)
  if(Present(grid,(cn+1)))////Checking if right neighbour is present in maze
  {
    while(g!=NULL)
    {
      if(g->cellno==(cn+1))
       {
           //cout<<" |"<<g->cellno<<"| ";
           nr[i]=g;
           i++;
           break;
       }
       g=g->next;
    }
  }
 // for(int j=0;j<i;j++)
   // cout<<"//"<<nr[j]->cellno<<"//";
  int n;
  //if(i>1)
   n=rand() % i;
  //else
    //n=0;
  if(nr[n]->cellno==(cn-width))
  {
      nod->up=nr[n];
      nr[n]->down=nod;
      //nr[n]=NULL;
      nod->next=NULL;
      //cout<<"Connected "<<nr[n]->j<<","<<nr[n]->k<<" node with "<<nod->j<<","<<nod->k<<" node(selected)\n";
      return grid;
  }
  else if(nr[n]->cellno==(cn+width))
  {
      nod->down=nr[n];
      nr[n]->up=nod;
      //nr[n]=NULL;
      nod->next=NULL;
      //cout<<"Connected "<<nr[n]->j<<","<<nr[n]->k<<" node with "<<nod->j<<","<<nod->k<<" node(selected)\n";
      return grid;
  }
  else if(nr[n]->cellno==(cn-1))
  {
      nod->left=nr[n];
      nr[n]->right=nod;
      //nr[n]=NULL;
      nod->next=NULL;
      //cout<<"Connected "<<nr[n]->j<<","<<nr[n]->k<<" node with "<<nod->j<<","<<nod->k<<" node(selected)\n";
      return grid;
  }
  else if(nr[n]->cellno==(cn+1))
  {
      nod->right=nr[n];
      nr[n]->left=nod;
      //nr[n]=NULL;
      nod->next=NULL;
      //cout<<"Connected "<<nr[n]->j<<","<<nr[n]->k<<" node with "<<nod->j<<","<<nod->k<<" node(selected)\n";
      return grid;
  }
}
void showlist(Node *st)//Displays the node no.s of the list
{
    cout<<endl;
    while(st!=NULL)
    {
        //cout<<st->cellno<<" ";
        st=st->next;
    }
}
Node *addlist(Node *lst,Node *nod)//Adds a node to the singly linked list
{
    Node *n;
    n=lst;
    if(n!=NULL)
    {
        while(n->next!=NULL)
          n=n->next;
         n->next=nod;
    }
    else
    {
      n=nod;
      n->next=NULL;
      lst=n;
    }
    return lst;
}
Node *getneighbours(int n,Node *&st,int &s,Node *gr,Node *nbrs)//Gets the adjacent nodes of a given node and puts them in a list
{
    Node *p;
    Node *nbr;
    p=gr;
    //cout<<"\nGetting neighbours for "<<p->cellno<<" ";
    //showlist(nbrs);
    if(p->j>0)
    {
        nbr=srch(st,(n-width));
        if(nbr!=NULL)
          if(!Present(gr,(nbr->cellno))&&!Present(nbrs,(nbr->cellno)))
          {
             nbrs=addlist(nbrs,nbr);
             s++;
          }
    }
    if(p->j<(width-1))
    {
        nbr=srch(st,n+width);
        if(nbr!=NULL)
          if(!Present(gr,(nbr->cellno))&&!Present(nbrs,(nbr->cellno)))
          {
             nbrs=addlist(nbrs,nbr);
             s++;
          }
    }
    if(p->k>0)
    {
        nbr=srch(st,n-1);
        if(nbr!=NULL)
          if(!Present(gr,(nbr->cellno))&&!Present(nbrs,(nbr->cellno)))
          {
             nbrs=addlist(nbrs,nbr);
             s++;
          }
    }
    if(p->k<width-1)
    {
        nbr=srch(st,n+1);
        if(nbr!=NULL)
          if(!Present(gr,nbr->cellno)&&!Present(nbrs,nbr->cellno))
          {
             nbrs=addlist(nbrs,nbr);
             s++;
          }
    }
   return nbrs;
}
void solve(Node *start)//Traverses the maze using dfs and finds a path to escape
{
    //cout<<"\nto node"<<start->j<<","<<start->k;
    start->visit=1;
    if(start->cellno==siz-1)
    {
      // cout<<"\n****Escaped the maze!!****";
       getchar();
       exit(0);
    }
    Node *nr[4];
    int i=0,x=0,q;
    if(start->up!=NULL&&!(start->up->visit))
    {
       nr[i]=start->up;
       i++;
    }
    if(start->down!=NULL&& !(start->down->visit))
    {
       nr[i]=start->down;
       i++;
     }
     if(start->left!=NULL&& !(start->left->visit))
     {
        nr[i]=start->left;
        i++;
      }
      if(start->right!=NULL&& !(start->right->visit))
      {
         nr[i]=start->right;
         i++;
       }
       if(nr[0]==NULL)
        {
        //  cout<<"\nReturning from"<<start->cellno;
          return;
        }
    for(x=0;x<i;x++)
    {
      if(nr[x]->visit==0)
       solve(nr[x]);
    }
    //cout<<"\nReturning from "<<start->j<<","<<start->k<<"\n";
    return;
}
Node *sorting1(Node *&head)//Sorts a singly linked list
{  int x,swapped;
    Node *current=head;
    Node *n;
    Node *prev;
    for(int i=0;i<siz;i++)
    {
      while(current->next!=NULL)
      {
        n=current->next;
       if(current->cellno>n->cellno)
       {
           swapped=1;
           current->next=n->next;
           n->next=current;
           if(prev!=NULL)
              prev->next=n;
           prev=n;
           if(head==current)
              head=n;
       }
        else
        {
           prev=current;
           current=current->next;
        }
     }
       if(swapped==0)
        break;
       else
       {
           prev=NULL;
           current=head;
           swapped=0;
       }
   }
return head;
}
