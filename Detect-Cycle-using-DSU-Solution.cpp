*****************************************************************************************  Question  *************************************************************************************************
Given an undirected graph with no self loops with V (from 0 to V-1) nodes and E edges, the task is to check if there is any cycle in the undirected graph.

Note: Solve the problem using disjoint set union (DSU).

Example 1:

Input: 

Output: 1
Explanation: There is a cycle between 0->2->4->0
Example 2:

Input: 

Output: 0
Explanation: The graph doesn't contain any cycle
Your Task:
You don't need to read or print anyhting. Your task is to complete the function detectCycle() which takes number of vertices in the graph denoting as V and adjacency list adj and returns 1 if graph contains any cycle otherwise returns 0.

Expected Time Complexity: O(V + E)
Expected Space Complexity: O(V)

Constraints:
2 ≤ V ≤ 104
1 ≤ E ≤ 104





******************************************************************************************  Solution  ************************************************************************************************

  //{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
    public:
     int find_set(int v, vector<int> &parent)
    {
        if (v != parent[v])
        {
            v = find_set(parent[v], parent);
        }
        return v;
    }

    void union_sets(int x, int y, vector<int> &parent, vector<int> &rank)
    {
        x = find_set(x, parent);
        y = find_set(y, parent);
        if (rank[x] < rank[y])
        {
            swap(x, y);
        }
        parent[y] = x;
        rank[x] += rank[y];
    }

    int detectCycle(int V, vector<int> adj[])
    {
        vector<int> parent(V);
        vector<int> rank(V, 1);
        unordered_set<pair<int, int>, PairHash> s;

        for (int i = 0; i < V; i++)
        {
            parent[i] = i;
        }

        for (int u = 0; u < V; u++)
        {
            for (int j = 0; j < adj[u].size(); j++)
            {
                int v = adj[u][j];
                if (s.count({u, v}) || s.count({v, u}))
                {
                    continue;
                }
                s.insert({u, v});
                int x = find_set(u, parent);
                int y = find_set(v, parent);
                if (x == y)
                {
                    return 1;
                }
                union_sets(x, y, parent, rank);
            }
        }

        return 0;
    }

private:
    struct PairHash
    {
        template <class T1, class T2>
        size_t operator()(const pair<T1, T2> &p) const
        {
            auto h1 = hash<T1>{}(p.first);
            auto h2 = hash<T2>{}(p.second);
            return h1 ^ h2;
        }
    };
};

//{ Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int V, E;
		cin >> V >> E;
		vector<int>adj[V];
		for(int i = 0; i < E; i++){
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		Solution obj;
		int ans = obj.detectCycle(V, adj);
		cout << ans <<"\n";	}
	return 0;
}
// } Driver Code Ends
