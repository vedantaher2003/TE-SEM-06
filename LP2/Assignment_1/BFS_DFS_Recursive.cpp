#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    map<string, vector<string>> adj;

    void addEdge(string computer1, string computer2)
    {
        adj[computer1].push_back(computer2);
        adj[computer2].push_back(computer1);
    }

    void printGraph()
    {
        for (auto computer : adj)
        {
            cout << computer.first << " -> ";
            for (auto neighbour : computer.second)
            {
                cout << neighbour << " ";
            }
            cout << endl;
        }
    }

    void BFS(queue<pair<string, int>> &q, set<string> &visited, vector<pair<string, int>> &result)
    {
        if (q.empty())
        {
            return;
        }

        pair<string, int> computer = q.front();
        q.pop();

        result.push_back(computer);

        for (auto neighbour : adj[computer.first])
        {
            if (visited.find(neighbour) == visited.end())
            {
                visited.insert(computer.first);
                q.push({neighbour, computer.second + 1});
            }
        }

        BFS(q, visited, result);
    }

    void BFS_Traversal(string src)
    {
        vector<pair<string, int>> traversal;
        set<string> visited;
        queue<pair<string, int>> q;

        visited.insert(src);
        q.push({src, 0});

        BFS(q, visited, traversal);

        printTraversal("BFS", traversal);
    }

    void DFS(string computer, int level, set<string> &visited, vector<pair<string, int>> &traversal)
    {
        traversal.push_back({computer, level});
        visited.insert(computer);

        for (auto neighbour : adj[computer])
        {
            if (visited.find(neighbour) == visited.end())
            {
                DFS(neighbour, level + 1, visited, traversal);
            }
        }
    }

    void DFS_Traversal(string computer)
    {
        vector<pair<string, int>> traversal;
        set<string> visited;

        DFS(computer, 0, visited, traversal);

        printTraversal("DFS", traversal);
    }

    void printTraversal(string name, vector<pair<string, int>> &traversal)
    {
        cout << name << " Traversal -> ";
        for (auto computer : traversal)
        {
            cout << "(" << computer.first << ", " << computer.second << ") ";
        }
        cout << endl;
    }
};

int main()
{
    Graph g;
    g.addEdge("computer1", "computer2");
    g.addEdge("computer1", "computer3");
    g.addEdge("computer2", "computer4");
    g.addEdge("computer3", "computer5");
    g.addEdge("computer4", "computer6");

    g.printGraph();

    g.BFS_Traversal("computer1");
    g.DFS_Traversal("computer1");

    return 0;
}

// Output :

// computer1 -> computer2 computer3
// computer2 -> computer1 computer4
// computer3 -> computer1 computer5
// computer4 -> computer2 computer6
// computer5 -> computer3
// computer6 -> computer4
// BFS Traversal -> (computer1, 0) (computer2, 1) (computer3, 1) (computer4, 2) (computer5, 2) (computer6, 3)
// DFS Traversal -> (computer1, 0) (computer2, 1) (computer4, 2) (computer6, 3) (computer3, 1) (computer5, 2)