#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    map<string, vector<pair<string, int>>> adj;

    void addEdge(string city1, string city2, int distance)
    {
        adj[city1].push_back({city2, distance});
        adj[city2].push_back({city1, distance});
    }

    void printGraph()
    {
        for (auto city : adj)
        {
            cout << city.first << " -> ";
            for (auto neighbour : city.second)
            {
                cout << "(" << neighbour.first << ", " << neighbour.second << ") ";
            }
            cout << endl;
        }
    }

    void dijkstra(string src)
    {
        set<string> visited;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        map<string, int> distance;

        pq.push({0, src});

        while (!pq.empty())
        {
            pair<int, string> city = pq.top();
            pq.pop();

            if (visited.find(city.second) != visited.end())
            {
                continue;
            }

            distance[city.second] = city.first;
            visited.insert(city.second);

            for (auto neighbour : adj[city.second])
            {
                if (visited.find(neighbour.first) == visited.end())
                {
                    pq.push({neighbour.second + city.first, neighbour.first});
                }
            }
        }

        printSD(distance);
    }

    void printSD(map<string, int> &distance)
    {
        cout << "Shortest Distance From Src -> ";
        for (auto node : distance)
        {
            cout << "(" << node.first << ", " << node.second << ") ";
        }
        cout << endl;
    }
};

int main()
{
    Graph g;
    g.addEdge("city1", "city2", 10);
    g.addEdge("city2", "city3", 20);
    g.addEdge("city3", "city5", 5);
    g.addEdge("city1", "city3", 40);

    g.printGraph();

    g.dijkstra("city1");

    return 0;
}

// Output :

// city1 -> (city2, 10) (city3, 40)
// city2 -> (city1, 10) (city3, 20)
// city3 -> (city2, 20) (city5, 5)(city1, 40)
// city5 -> (city3, 5)
// Shortest Distance From Src -> (city1, 0) (city2, 10) (city3, 30) (city5, 35)