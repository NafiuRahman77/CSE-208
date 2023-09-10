#include <bits/stdc++.h>
using namespace std;

void Dijkstra(int source, int n, vector<pair<int, double>> g[], int dest)
{

	priority_queue<pair<double, int>> pq;
	vector<double> distTo(n, INT_MIN);
	distTo[source] = 1;
	vector<int> parent(n);
	parent[source] = source;
	pq.push(make_pair(1, source));
	stack<int> st;

	while (!pq.empty())
	{

		double dist = pq.top().first;
		int prev = pq.top().second;
		pq.pop();

		for (auto it : g[prev])
		{
			int next = it.first;
			double nextDist = it.second;
			if (distTo[next] < distTo[prev] * nextDist)
			{

				distTo[next] = distTo[prev] * nextDist;
				pq.push(make_pair(distTo[next], next));
				parent[next] = prev;
			}
		}
	}
	cout << "The most reliable cost is :" << distTo[dest] << endl;

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
	// freopen("mst.txt", "r", stdin);
	int n, m;
	int i, u, v, src, dest;
	double w;
	// ifstream fin("mst.txt");
	cin >> n >> m;
	vector<pair<int, double>> adj[n];
	//    vector<node> edges;

	for (i = 1; i <= n; i++)
		adj[i].clear();

	for (i = 1; i <= m; i++)
	{
		cin >> u >> v >> w;
		adj[u].push_back(make_pair(v, w));
	}
	cin >> src >> dest;
	Dijkstra(src, n, adj, dest);

	// fin.close();

	return 0;
}
