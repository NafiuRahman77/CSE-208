#include<bits/stdc++.h>
using namespace std;

void remove(std::vector<int> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }

    v.erase(end, v.end());
}

struct node {
    int u;
    int v;
    double wt;
    node(int first, int second, double weight) {
        u = first;
        v = second;
        wt = weight;
    }
};

bool comp(node a, node b) {
    return a.wt < b.wt;
}
int findParent(int u, vector<int> &parent) {
    if(u == parent[u]) return u;
    return parent[u] = findParent(parent[u], parent); //Path compression
}

void unionn(int u, int v, vector<int> &parent, vector<int> &rank) {
    u = findParent(u, parent);
    v = findParent(v, parent);
    if(rank[u] < rank[v]) {
    	parent[u] = v;
    }
    else if(rank[v] < rank[u]) {
    	parent[v] = u;
    }
    else {
    	parent[v] = u;
    	rank[u]++;
    }
}


void Kruskal(vector<node> edges, int N){

    sort(edges.begin(), edges.end(), comp);

	vector<int> parent(N);
	for(int i = 0;i<N;i++)
	    parent[i] = i;

	vector<int> rank(N, 0);

	double cost = 0;
	vector<pair<int,int>> mst;
	for(auto it : edges) {
	    if(findParent(it.v, parent) != findParent(it.u, parent)) {
	        cost += it.wt;
	        mst.push_back({it.u, it.v});
	        unionn(it.u, it.v, parent, rank);
	    }
	}
	//cout << "Cost of the minimum spanning tree : "<< cost << endl;
    cout<<"List of edges selected by Kruskal's: {";
	for(int i=0;i<=mst.size()-2;i++) cout <<"("<< mst[i].first << "," << mst[i].second <<"),";
    cout <<"("<< mst[mst.size()-1].first << "," << mst[mst.size()-1].second <<")";

    cout<<"}";

}

void Prim(vector<pair<int,double> > adj[], int N){

    int parent[N];
    double key[N];
    bool mstSet[N];
    //vector <int> mst;

    for (int i = 0; i < N; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    priority_queue< pair<double,int>, vector <pair<double,int>> , greater<pair<double,int>> > pq;

    key[0] = 0;
    parent[0] = -1;
    pq.push({0, 0});
    double cost=0;
    int count=0;

    vector<int> mst;


    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();


        mstSet[u] = true;

        if(u!=0){
            mst.push_back(u);
        }
       // mst.push_back(u);

        for (auto it : adj[u]) {
            int v = it.first;
            double weight = it.second;

            if (mstSet[v] == false && weight < key[v]) {
                parent[v] = u;
		        key[v] = weight;
                pq.push({key[v], v});


            }

        }

    }

    for (int i = 0; i < N; i++) {
        cost+=key[i];

    }


    remove(mst);

    cout<<"Cost of the minimum spanning tree : "<<cost<<endl;
    cout<<"List of edges selected by Prim's : {";
    for (int i = 0; i < mst.size()-1; i++) {
        cout << "("<< mst[i]<< "," << parent[mst[i]]<<"),";

     }
    cout <<"("<<  mst[mst.size()-1]<<  "," <<  parent[mst[mst.size()-1]] <<")";
    cout<<"}";
    cout<<endl;


}

int main(){
    freopen("mst.txt", "r", stdin);
	int n,m;
	int i, u, v;
    double w;
    ifstream fin("mst.txt");
    fin >> n >> m ;
    vector<pair<int,double> > adj[n];
    vector<node> edges;


    for (i = 1; i <= m; i++){
        fin >> u >> v >> w;
      //  cout<<w<<endl;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
        edges.push_back(node(u,v,w));
        edges.push_back(node(v,u,w));
    }

    fin.close();



    Prim(adj, n);
    Kruskal(edges, n);

	return 0;
}
