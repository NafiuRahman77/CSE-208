#include<bits/stdc++.h>

using namespace std;

int shortestPath (int V, vector<int> adj[], int src){

    vector<int> vis(V,0);
     vector<int> dist(V);
    for(int i=0;i<V;i++){
        dist[i]=INT_MAX;
    }
    dist[src]=0;
            queue<int> q;
            q.push(src);
            vis[src]=1;
            while(!q.empty()){
                int node=q.front();
                q.pop();

                for(auto it: adj[node]){

                    if(dist[node]+1< dist[it]){
                        dist[it]=dist[node]+1;
                        q.push(it);
                        vis[it]=1;
                    }
                }
            }

    return dist[V-1];

}

int main(){
    string s;
    cin>>s;
    int vertices=s.length();
    vector<int> adj[vertices]; //adjacency list
    for(int i=0;i<vertices;i++){

        if(i==0){
            adj[i].push_back(i+1);
            adj[i+1].push_back(i);
        }
        else if(i=vertices-1){
            adj[i].push_back(i-1);
            adj[i-1].push_back(i);
        }
        else{
            adj[i].push_back(i+1);
            adj[i].push_back(i-1);
            adj[i+1].push_back(i);
            adj[i-1].push_back(i);
        }
        for(int j=0; j<vertices;j++){
            if(j!=i){
                if(s[i]==s[j]){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

    }

    cout<<shortestPath ( vertices,adj, 0);

}
