#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;


typedef pair<int, int> iPair;
  

class Graph
{
    
    int V, E;
    list<int> *adj; 
    vector< pair<int, iPair> > edges;

  
public:
    Graph(int V,int E);
    void addEdge(int u, int v, int w);
    vector<int> BFS(int s); 
    vector<vector<vector<int>>> conectedGraph(vector<vector<int>> dados);
    
    int kruskalMST();
    int finalfunction(vector<vector<int>> dados);

};

Graph::Graph(int V, int E)
{
    this->V = V;
    this->E = E;
    adj = new list<int>[V];
}
void Graph::addEdge(int u, int v, int w)
    {
        adj[u].push_back(v); 
        adj[v].push_back(u); 
        edges.push_back({w, {u, v}});
    }


vector<int> Graph::BFS(int s)
{

    vector<bool> visited;
    visited.resize(V, false);
 
   
    list<int> queue;
 

    visited[s] = true;
    queue.push_back(s);
    vector<int> lista;
    while (!queue.empty()) {
     
        s = queue.front();
       
        lista.push_back(s);
        queue.pop_front();
 
        for (auto adjecent : adj[s]) {
            if (!visited[adjecent]) {
                visited[adjecent] = true;
                queue.push_back(adjecent);
            }
        }
    }
    return lista;
}

 vector<vector<vector<int>>> Graph::conectedGraph(vector<vector<int>> dados){
    int V = dados[0][0];
    int E = dados[0][1];
    Graph g(V,E);
    vector<int> lista;
    for (int i =1; i<dados.size();i++){
        g.addEdge(dados[i][0],dados[i][1],dados[i][2]);
    }
    list<int> to_visit;
    for (int j=0; j<V ; j++){
        to_visit.push_back(j);
    }

    vector<vector<vector<int>>> grafos;
   
    while(to_visit.size()!=0){
        vector<int> tamanho;
        
        lista=g.BFS(to_visit.front());
        tamanho.push_back(lista.size());
    
        vector<int>::iterator it;
        
        vector<vector<int>> grafo= {};
        grafo.push_back(tamanho);
        for (int j = 1; j<dados.size();j++){
            it=find(lista.begin(),lista.end(),dados[j][0]);
            if (it!=lista.end()){ //se encontraste
                grafo.push_back(dados[j]);
            }
        }
        grafos.push_back(grafo);
        
        for (int i=0; i<lista.size();i++){   
            to_visit.remove(lista[i]);
        }    
    }
    return grafos;
}

struct DisjointSets
{
    int *parent, *rnk;
    int n;
  

    DisjointSets(int n)
    {
       
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
  
   
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
  
            parent[i] = i;
        }
    }
  

    int find(int u)
    {

        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
  
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else 
            parent[x] = y;
  
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
  

  
int Graph::kruskalMST()
{
    int mst_wt = 0;
  

    sort(edges.rbegin(), edges.rend());
  
 
    DisjointSets ds(V);
  

    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
  
        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {

            mst_wt += it->first;
  
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
  
    return mst_wt;
}


int Graph::finalfunction(vector<vector<int>> dados){
    vector<vector<vector<int>>> lista = conectedGraph(dados);
    int res=0;
    for (int i= 0; i<lista.size();i++){
        int V = dados[0][0];
        int E = lista[i].size() - 1;
        Graph g(V,E);
        for (int j=1; j<lista[i].size();j++){
            g.addEdge(lista[i][j][0],lista[i][j][1],lista[i][j][2]);  
        }
        res+=g.kruskalMST();
    }

    return res;
}



int main(){
    

    vector<vector<int>> dados;
    vector<int> numero_nos;


    int nos;
    scanf("%d", &nos);
    numero_nos.push_back(nos);

    int arcos;
    scanf("%d",&arcos);
    numero_nos.push_back(arcos);


    int counter=0;
    dados.push_back(numero_nos);

    while (counter != arcos){

        vector<int> conjunto = {};
        
        
        char valor[10];
        scanf (" %[^\n]%*c", valor);


        int n1 = valor[0] - '0';
        int n2 = valor[2] - '0';
        int n3 = valor[4] - '0';

        int n11 = n1 -1;
        int n22 = n2-1;

        conjunto.push_back(n11);
        conjunto.push_back(n22);
        conjunto.push_back(n3);

        
        dados.push_back(conjunto);
        counter++;
    }

    Graph g(1,1);
    printf("%d\n", g.finalfunction(dados));

    return 0;
}