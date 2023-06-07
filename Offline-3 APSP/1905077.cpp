#include<bits/stdc++.h>
using namespace std;

//int N;
int n;

vector<vector<int>> ExtendShortestPath(vector<vector<int>> &l, vector<vector<int>> &adj ){
      vector<vector<int>>res(n,vector<int> (n, -1));
       for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                res[i][j]=INT_MAX;
        }
    }
     for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                    if((adj[k][j] != INT_MAX && l[i][k] != INT_MAX)){
                    res[i][j]=min(res[i][j], l[i][k]+adj[k][j]);
                    }

            }
        }
    }
    return res;

}

void SlowAPSP(vector<vector<int>> &adj){
  vector<vector<int>>l(n,vector<int> (n, -1));
  for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            l[i][j]=adj[i][j];
        }
    }
    for(int i=2;i<=n-1;i++){

        l=ExtendShortestPath(l,adj);
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(l[i][j]==INT_MAX){
                   cout<<"INF"<<" ";
                   }
                   else{
            cout<<l[i][j]<<"   ";
                   }
        }
        cout<<endl;
    }



}
void FastAPSP(vector<vector<int>> &adj){
  vector<vector<int>>l(n,vector<int> (n, -1));
  for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            l[i][j]=adj[i][j];
        }
    }
    for(int i=1;i<n-1;i*=2){

        l=ExtendShortestPath(l,adj);

    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(l[i][j]==INT_MAX){
                   cout<<"INF"<<" ";
                   }
                   else{
            cout<<l[i][j]<<"   ";
                   }
        }
        cout<<endl;
    }



}

void FloydWarshall(vector<vector<int>> &adj){
    vector<vector<int>>res(n,vector<int> (n, -1));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res[i][j]=adj[i][j];
        }
    }


    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if((res[k][j] != INT_MAX && res[i][k] != INT_MAX)){
                    res[i][j]=min(res[i][j],res[i][k]+res[k][j]);
                }
            }
        }
     }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
                if(res[i][j]==INT_MAX){
                   cout<<"INF"<<" ";
                   }
                   else{
            cout<<res[i][j]<<"   ";
                   }
        }
        cout<<endl;
    }


}

int main(){
    freopen("mst.txt", "r", stdin);
    ifstream fin("mst.txt");

    int m;
    fin>>n>>m;
    int u,v,w;
    vector<vector<int>>adj(n,vector<int> (n, INT_MAX));


    //cout<<n;
     for (int i = 0; i < n; i++)
    {

        adj[i][i]=0;

    }

     for (int i = 0; i < m; i++)
    {

        fin>>u>>v>>w;
        adj[u-1][v-1]= w;
    }
    cout<<"Floyd-Warshall"<<endl;
    FloydWarshall(adj);
    cout<<"Matrix-Multiplication"<<endl;
    FastAPSP(adj);

    fin.close();


}

