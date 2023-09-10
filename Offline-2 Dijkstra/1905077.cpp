
#include <bits/stdc++.h>
using namespace std;

struct node
{
    int u;
    int v;
    int wt;
    node(int first, int second, int weight)
    {
        u = first;
        v = second;
        wt = weight;
    }
};
void BellmanFord(int src, int dest, int N, vector<node> edges)
{

    vector<int> distTo(N);
    for (int i = 0; i < N; i++)
    {
        distTo[i] = INT_MAX;
    }
    vector<int> parent(N);
    distTo[src] = 0;
    parent[src] = src;
    stack<int> st;

    for (int i = 1; i <= N - 1; i++)
    {
        for (auto it : edges)
        {
            if (distTo[it.u] + it.wt < distTo[it.v] && distTo[it.u] != INT_MAX)
            {
                distTo[it.v] = distTo[it.u] + it.wt;
                parent[it.v] = it.u;
            }
        }
    }

    int flag = 0;
    for (auto it : edges)
    {
        if (distTo[it.u] + it.wt < distTo[it.v])
        {
            cout << "The graph contains a negative cycle";
            flag = 1;
            break;
        }
    }

    if (!flag)
    {

        cout << "The graph doesn't contain a negative cycle" << endl;

        cout << "Shortest path cost :" << distTo[dest] << endl;
        int a = dest;
        while (true)
        {
            st.push(a);
            a = parent[a];
            if (a == src)
            {
                st.push(a);
                break;
            }
        }
        while (st.size() > 1)
        {
            cout << st.top() << "->";
            st.pop();
        }
        cout << st.top();
    }
}

void Dijkstra(int source, int n, vector<pair<int, int>> adj[], int dest)
{

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distTo(n);
    for (int i = 0; i < n; i++)
    {
        distTo[i] = INT_MAX;
    }

    distTo[source] = 0;
    vector<int> parent(n);
    parent[source] = source;
    pq.push({0, source});
    stack<int> st;

    while (!pq.empty())
    {

        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        vector<pair<int, int>>::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); it++)
        {
            int v = it->first;
            int nxtDist = it->second;
            if (distTo[v] > distTo[u] + nxtDist)
            {

                distTo[v] = distTo[u] + nxtDist;
                pq.push({distTo[v], v});
                parent[v] = u;
            }
        }
    }
    cout << "Shortest path cost :" << distTo[dest] << endl;

    int a = dest;
    while (true)
    {
        st.push(a);
        a = parent[a];
        if (a == source)
        {
            st.push(a);
            break;
        }
    }
    // cout<<st.size()<<endl;
    while (st.size() > 1)
    {
        cout << st.top() << "->";
        st.pop();
    }
    cout << st.top();
}

int main()
{
    freopen("mst.txt", "r", stdin);
    int n, m, flag = 0;
    int i, u, v, w, src, dest;
    ifstream fin("mst.txt");
    fin >> n >> m;
    vector<pair<int, int>> adj[n];
    vector<node> edges;

    for (i = 1; i <= n; i++)
        adj[i].clear();

    for (i = 1; i <= m; i++)
    {
        fin >> u >> v >> w;
        if (w < 0)
        {
            flag = 1;
        }
        adj[u].push_back(make_pair(v, w));
        edges.push_back(node(u, v, w));
    }
    fin >> src >> dest;
    if (!flag)
    {
        Dijkstra(src, n, adj, dest);
    }
    else
    {
        BellmanFord(src, dest, n, edges);
    }

    fin.close();

    return 0;
}
