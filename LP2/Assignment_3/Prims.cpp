#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    map<string, vector<pair<string, int>>> adj;

    void addEdge(string computer1, string computer2, int distance)
    {
        adj[computer1].push_back({computer2, distance});
        adj[computer2].push_back({computer1, distance});
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

    void prims(string src)
    {
        set<string> visited;
        priority_queue<pair<int, pair<string, string>>, vector<pair<int, pair<string, string>>>, greater<pair<int, pair<string, string>>>> pq;
        vector<pair<int, pair<string, string>>> mst;

        pq.push({0, {src, src}});

        while (!pq.empty())
        {
            pair<int, pair<string, string>> computer = pq.top();
            pq.pop();

            if (visited.find(computer.second.first) != visited.end())
            {
                continue;
            }

            if (computer.second.first != src)
            {
                mst.push_back(computer);
            }

            visited.insert(computer.second.first);

            for (auto neighbour : adj[computer.second.first])
            {
                if (visited.find(neighbour.first) == visited.end())
                {
                    pq.push({neighbour.second, {neighbour.first, computer.second.first}});
                }
            }
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

    g.prims("computer1");

    return 0;
}

// Output :

// computer1 -> (computer2, 10) (computer3, 40)
// computer2 -> (computer1, 10) (computer3, 20)
// computer3 -> (computer2, 20) (computer1, 40)
// MST -> (computer2, computer1, 10) (computer3, computer2, 20)
// Cost -> 30