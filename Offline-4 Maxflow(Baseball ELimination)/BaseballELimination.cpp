// C++ program for implementation of Ford Fulkerson
// algorithm
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include<bits/stdc++.h>
using namespace std;


bool bfs(vector<vector<int>> &res, int s, int t, vector<int> &parent, int ver)

{

    vector<bool> visited(ver,false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;


    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < ver; v++) {
            if (visited[v] == false && res[u][v] > 0) {

                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}
void dfs(vector<vector<int>> rGraph, int s, bool visited[], int ver)
{
    visited[s] = true;
    for (int i = 0; i < ver; i++)
       if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited, ver);
}


void minCut(vector<vector<int>> graph, int s, int t,int ver)
{
    int u, v;


    vector<vector<int>> rGraph(ver,vector<int> (ver, 0)); // rGraph[i][j] indicates residual capacity of edge i-j
    for (u = 0; u < ver; u++)
        for (v = 0; v < ver; v++)
             rGraph[u][v] = graph[u][v];

    vector<int> parent(ver);
    while (bfs(rGraph, s, t, parent, ver))
    {
       int path_flow = INT_MAX;
        v=t;
        while(v!=s)
        {
            //augmentedPath.push_back(v);
             u = parent[v];
              path_flow = min(path_flow, rGraph[u][v]);
            v=u;
        }


       v=t;
        while(v!=s)
        {
             u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
            v=u;
        }
    }
    bool visited[ver];
    memset(visited, false, sizeof(visited));
    dfs(rGraph, s, visited, ver);

    return;
}

int fordFulkerson(vector<vector<int>> & g, int s, int t, int ver)
{
    int u, v;

    vector<vector<int>> rG(ver,vector<int> (ver, 0));


    for(int i=0;i<ver;i++){
        for(int j=0;j<ver;j++){
            rG [i][j]= g[i][j];
        }
    }

    vector<int> parent(ver);

    int max_flow = 0;
    while (bfs(rG, s, t, parent, ver)==true) {
          // cout<<"bop";

        int path_flow = INT_MAX;
        v=t;
        while(v!=s)
        {
            //augmentedPath.push_back(v);
             u = parent[v];
              path_flow = min(path_flow, rG[u][v]);
            v=u;
        }


       v=t;
        while(v!=s)
        {
             u = parent[v];
            rG[u][v] -= path_flow;
            rG[v][u] += path_flow;
            v=u;
        }


        max_flow += path_flow;
    }

    return max_flow;
}

vector<vector<int>> flowNetwork(int n,int V, int x, vector<int> nodeTeam, vector<int> w, vector<int> rem, vector<vector<int>> nodeMatch, vector<vector<int>> game){

    vector<vector<int>> g(n,vector<int> (n, 0));
    for(int i=0;i<V;i++)
        {
            if(i==x)
                continue;
            g[nodeTeam[i]][n-1] = max(0,w[x]+rem[x]-w[i]);

            for(int j=i;j<V;j++)
            {

                if(j==i || j==x)
                    continue;
                g[0][nodeMatch[i][j]] = game[i][j];
                g[nodeMatch[i][j]][nodeTeam[i]] = INT_MAX;
                g[nodeMatch[i][j]][nodeTeam[j]] = INT_MAX;
            }
        }

   return g;
}

int main(){

    int V;
    cin >> V;

    vector<string> clubs(V);

    vector<int> w(V);
    vector<int> l(V);
    vector<int> rem(V);
    vector<int> nodeTeam(V);
    vector<vector<int>> game(V,vector<int> (V, 0));
    vector<vector<int>> nodeMatch(V,vector<int> (V, 0));


    int matchNo = 1;


    for(int i=0;i<V;i++) //taking individual team inputs
    {
        cin >> clubs[i] >> w[i] >> l[i] >> rem[i];
        for(int j=0;j<V;j++)
        {
            cin>>game[i][j];
            if(j>=i)
            {
                nodeMatch[i][j] = matchNo++;
            }
        }
    }

    int n = V + V*(V+1)/2+2;

    for(int x=0;x<V;x++)
    {

        int maxflow = 0;

        for(int i=0;i<V;i++)
        {
            if(i==x)
                continue;
            for(int j=i;j<V;j++)
            {

                if(j==i || j==x)
                    continue;
                maxflow += game[i][j];
            }
        }

        vector<vector<int>> g=flowNetwork(n, V, x, nodeTeam,w,rem,nodeMatch,game);

        int res = fordFulkerson( g, 0, n-1,n);
        if(maxflow>res)
        {
            cout << clubs[x] << " is eliminated" << endl;
            cout << "They can win at most " << w[x] << " + " << rem[x] << " = " << w[x]+rem[x] << " games" << endl;
        } else continue;

    }


}
