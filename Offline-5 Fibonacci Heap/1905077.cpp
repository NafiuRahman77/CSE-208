
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <malloc.h>

#include <bits/stdc++.h>
#include <chrono>

using namespace std::chrono;

using namespace std;

// Creating a structure to represent a node in the heap
struct node
{
	node *parent;		   // Parent pointer
	node *child;		   // Child pointer
	node *left;			   // Pointer to the node on the left
	node *right;		   // Pointer to the node on the right
	pair<double, int> key; // Value of the node
	int degree;			   // Degree of the node
	bool mark;			   // Black or white mark of the node
};

class FibonacciHeap
{
private:
	node *mini;
	int no_of_nodes;
	void swapp(node *x, node *y)
	{
		node *temp;
		temp = x;
		x = y;
		y = temp;
	}
	// Consolidating the heap
	void Consolidate(int rootSize)
	{
		int temp1, d;
		int max_degree = static_cast<int>(floor(log(static_cast<double>(no_of_nodes)) / log(static_cast<double>(1 + sqrt(static_cast<double>(5))) / 2)));
		node *A[max_degree + 2];
		node *rootList[rootSize];
		for (int i = 0; i < max_degree + 2; i++)
			A[i] = NULL;
		node *ptr1 = mini;
		node *ptr2;
		node *temp;
		node *ptr4 = ptr1;
		node *next, *w, *x, *y;
		w = mini;
		next = w;

		// rootList=new node*[rootSize] ;

		for (int i = 0; i < rootSize; i++)
		{
			rootList[i] = next;
			next = next->right;
		}
		for (int i = 0; i < rootSize; i++)
		{
			w = rootList[i];
			x = w;
			d = x->degree;
			while (A[d] != NULL)
			{

				y = A[d];

				if ((x->key).first > (y->key).first)
				{
					// swap
					swap(x, y);
				}

				Fibonnaci_link(y, x);

				A[d] = NULL;

				d++;
			}

			A[d] = x;
		}
		// delete [] rootList;
		mini = NULL;
		for (int j = 0; j < max_degree + 2; j++)
		{
			if (A[j] != NULL)
			{
				A[j]->left = A[j];
				A[j]->right = A[j];
				if (mini != NULL)
				{
					(mini->left)->right = A[j];
					A[j]->right = mini;
					A[j]->left = mini->left;
					mini->left = A[j];
					if ((A[j]->key).first < (mini->key).first)
						mini = A[j];
				}
				else
				{
					mini = A[j]->left = A[j]->right = A[j];
				}
			}
		}
	}

	void Fibonnaci_link(node *ptr2, node *ptr1)
	{
		(ptr2->left)->right = ptr2->right;
		(ptr2->right)->left = ptr2->left;
		if (ptr1->right == ptr1)
			mini = ptr1;
		ptr2->left = ptr2;
		ptr2->right = ptr2;
		ptr2->parent = ptr1;
		if (ptr1->child == NULL)
			ptr1->child = ptr2;
		ptr2->right = ptr1->child;
		ptr2->left = (ptr1->child)->left;
		((ptr1->child)->left)->right = ptr2;
		(ptr1->child)->left = ptr2;
		if ((ptr2->key).first < ((ptr1->child)->key).first)
			ptr1->child = ptr2;
		ptr1->degree++;
	}

public:
	FibonacciHeap()
	{
		mini = NULL;
		no_of_nodes = 0;
	}

	int getno_of_nodes()
	{
		return no_of_nodes;
	}
	// Function to insert a node in heap
	void insertion(pair<double, int> val)
	{
		node *new_node = new node();
		new_node->parent = NULL;
		new_node->child = NULL;
		new_node->left = new_node;
		new_node->right = new_node;
		new_node->key = val;
		new_node->degree = 0;
		new_node->mark = false;

		if (mini == NULL)
		{
			//	mini = new_node;
			mini = new_node->left = new_node->right = new_node;
		}
		else
		{

			(mini->left)->right = new_node;
			new_node->right = mini;
			new_node->left = mini->left;
			mini->left = new_node;
			if ((new_node->key).first < (mini->key).first)
				mini = new_node;
		}
		no_of_nodes++;
	}

	pair<double, int> Extract_min()

	{
		if (mini == NULL)
			cout << "The heap is empty" << endl;

		node *z, *x, *next, *w;
		int rootSize = 0;
		node **childList;
		w = mini;
		z = mini;
		next = w;
		x = z->child;
		if (x != NULL)

		{
			int d = z->degree;
			childList = new node *[d];
			next = x;
			for (int i = 0; i < (int)z->degree; i++)
			{
				childList[i] = next;
				next = next->right;
			}
			for (int i = 0; i < (int)z->degree; i++)
			{

				x = childList[i];
				mini->left->right = x;
				x->left = mini->left;
				mini->left = x;
				x->right = mini;
				x->parent = NULL;
			}
			delete[] childList;
		}

		z->left->right = z->right;
		z->right->left = z->left;
		if (z == z->right)
		{

			mini = NULL;
		}
		else
		{

			mini = z->right;
			w = mini;
			next = w;
			do
			{
				rootSize++;
				next = next->right;
			} while (next != w);

			Consolidate(rootSize);
		}

		no_of_nodes--;

		return z->key;
	}
};

pair<double, int> DijkstraFheap(int source, int n, vector<pair<int, double>> adj[], int dest)
{

	// priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int>>> pq;
	FibonacciHeap f;
	vector<double> distTo(n);
	for (int i = 0; i < n; i++)
	{
		distTo[i] = INT_MAX;
	}

	distTo[source] = 0;
	vector<int> parent(n);
	parent[source] = source;
	f.insertion({0, source});
	stack<int> st;

	while (f.getno_of_nodes() != 0)
	{

		pair<int, int> pa = f.Extract_min();

		int dist = pa.first;
		int u = pa.second;

		vector<pair<int, double>>::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++)
		{
			int v = it->first;
			double nxtDist = it->second;
			if (distTo[v] > distTo[u] + nxtDist)
			{

				distTo[v] = distTo[u] + nxtDist;
				f.insertion({distTo[v], v});
				parent[v] = u;
			}
		}
	}
	// cout<<"Shortest path cost :"<<distTo[dest]<<endl;

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
	pair<double, int> p = {distTo[dest], st.size() - 1};
	return p;
}
pair<double, int> DijkstraBheap(int source, int n, vector<pair<int, double>> adj[], int dest)
{

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
	vector<double> distTo(n);
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

		vector<pair<int, double>>::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++)
		{
			int v = it->first;
			double nxtDist = it->second;
			if (distTo[v] > distTo[u] + nxtDist)
			{

				distTo[v] = distTo[u] + nxtDist;
				pq.push({distTo[v], v});
				parent[v] = u;
			}
		}
	}
	// cout<<"Shortest path cost :"<<distTo[dest]<<endl;

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
	pair<double, int> p = {distTo[dest], st.size() - 1};
	return p;
}

int main()
{
	freopen("heap1.txt", "r", stdin);
	int n, m, flag = 0;
	int i, u, v, w, src, dest;
	ifstream fin("heap1.txt");
	fin >> n >> m;
	vector<pair<int, double>> adj[n];
	// vector<node> edges;

	for (i = 1; i <= n; i++)
		adj[i].clear();

	for (i = 1; i <= m; i++)
	{
		fin >> u >> v >> w;
		adj[u].push_back(make_pair(v, w));
		adj[v].push_back(make_pair(u, w));
		// edges.push_back(node(u,v,w));
	}
	// fin>>src>>dest;

	fin.close();
	// DijkstraFheap(src,n,adj,dest);
	freopen("heap2.txt", "r", stdin);
	ifstream fin1("heap2.txt");
	freopen("out.txt", "w", stdout);
	ofstream fout("out.txt");
	int k;
	fin1 >> k;
	while (k--)
	{
		fin1 >> src >> dest;
		// Start
		auto start = high_resolution_clock::now();
		pair<double, int> p = DijkstraBheap(src, n, adj, dest);
		auto stop = high_resolution_clock::now();
		auto duration1 = duration_cast<milliseconds>(stop - start);
		// Cout << duration.count();
		auto start1 = high_resolution_clock::now();
		pair<double, int> a = DijkstraFheap(src, n, adj, dest);
		auto stop1 = high_resolution_clock::now();
		auto duration2 = duration_cast<milliseconds>(stop1 - start1);
		fout << a.second << " " << a.first << " " << duration1.count() << " " << duration2.count() << endl;
	}

	return 0;
}
