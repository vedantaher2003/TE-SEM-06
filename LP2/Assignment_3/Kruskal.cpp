#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    map<string, vector<pair<string, int>>> adj;
    map<string, string> parent;
    map<string, int> size;
    vector<pair<int, pair<string, string>>> edges;

    void addEdge(string computer1, string computer2, int distance)
    {
        adj[computer1].push_back({computer2, distance});
        adj[computer2].push_back({computer1, distance});
        edges.push_back({distance, {computer1, computer2}});
    }

    void printGraph()
    {
        for (auto computer : adj)
        {
            cout << computer.first << " -> ";
            for (auto neighbour : computer.second)
            {
                cout << "(" << neighbour.first << ", " << neighbour.second << ") ";
            }
            cout << endl;
        }
    }

    string find(string computer)
    {
        if (computer == parent[computer])
        {
            return computer;
        }
        return parent[computer] = find(parent[computer]);
    }

    void make_union(string computer1, string computer2)
    {
        string upc1 = find(computer1);
        string upc2 = find(computer2);

        if (upc1 == upc2)
        {
            return;
        }

        if (size[upc1] > size[upc2])
        {
            parent[upc2] = upc1;
            size[upc1] += size[upc2];
        }
        else
        {
            parent[upc1] = upc2;
            size[upc2] += size[upc1];
        }
    }

    void kruskal()
    {
        vector<pair<int, pair<string, string>>> mst;

        for (auto computer : adj)
        {
            parent[computer.first] = computer.first;
            size[computer.first] = 1;
        }

        sort(edges.begin(), edges.end());

        for (auto edge : edges)
        {
            if (find(edge.second.first) == find(edge.second.second))
            {
                continue;
            }
            mst.push_back(edge);
            make_union(edge.second.first, edge.second.second);
        }

        printMST(mst);
    }

    void printMST(vector<pair<int, pair<string, string>>> &mst)
    {
        int cost = 0;
        cout << "MST -> ";
        for (auto edge : mst)
        {
            cout << "(" << edge.second.first << ", " << edge.second.second << ", " << edge.first << ") ";
            cost += edge.first;
        }
        cout << endl;
        cout << "Cost -> " << cost << endl;
    }
};

int main()
{
    Graph g;
    g.addEdge("computer1", "computer2", 10);
    g.addEdge("computer2", "computer3", 20);
    g.addEdge("computer1", "computer3", 40);

    g.printGraph();

    g.kruskal();

    return 0;
}

// Output :

// computer1 -> (computer2, 10) (computer3, 40)
// computer2 -> (computer1, 10) (computer3, 20)
// computer3 -> (computer2, 20) (computer1, 40)
// MST -> (computer2, computer1, 10) (computer3, computer2, 20)
// Cost -> 30