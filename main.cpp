
// CPP program to print the number of largest
// connected component in a grid and show you all subgraph groups
// input is every Adjacency_matrix

#include <bits/stdc++.h>
using namespace std;

// struct for position of cells
struct Node
{
    int i;
    int j;
};

class Graph
{

    // length and width
    int n;
    int m;

    //Adjacency matrix
    int** input;

    int connected_subgraph_number = 2;

public:

    //Constructor
    Graph(int n, int m)
    {
        this->n = n;
        this->m = m;
        input = new int*[n];
        for(int i=0; i<n; i++)
        {
            input[i] = new int[m];
        }

    }

    void make_adjacency_matrix(int x, int y, int value)
    {
        input[x][y] = value;
    }

    // Convert Adjacency matrix to matrix which show connected subgraph
    void connected_subgraph()
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                if(input[i][j] == 1)
                {
                    input[i][j] = connected_subgraph_number;
                    connected_subgraph_number++;
                    list<Node> nodes;
                    nodes.push_back({i,j});
                    while(!nodes.empty())
                    {
                        Node node = nodes.back();
                        nodes.pop_back();
                        nodes.splice(nodes.end(), color_neighbor(node.i, node.j));
                    }
                }

            }
        }
    }


    // This function give you number of members in biggest subgraph;
    void find_biggest_subgraph()
    {
        int find_biggest[connected_subgraph_number-1];
        for (int j = 0; j<connected_subgraph_number; j++)
        {
            find_biggest[j] = 0;
        }

        for(int i=0; i<n; i++)
        {
            for (int j = 0; j<m; j++)
            {
                if(input[i][j] != 0)
                {
                    find_biggest[input[i][j]-1]++;
                }
            }
        }

        int max = 0;
        for (int j = 0; j<connected_subgraph_number; j++)
        {
            if(find_biggest[j] > max)
            {
                max = find_biggest[j];
            }
        }

        cout << max;
    }

    // This function show you connect subgraph by different number
    // Each connect subgraph has specific number
    // Zero means empty cell in input
    void print()
    {
        for(int i=0; i<n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << input[i][j] << " ";
            }
            cout << endl;
        }
    }


private:

    //Find all neighbors of cell
    list<Node> color_neighbor(int i, int j)
    {
        list<Node> nodes;
        if(i > 0 && input[i-1][j] == 1)
        {
            input[i-1][j] = input[i][j];
            nodes.push_back({i-1, j});
        }
        if(i < n-1 && input[i+1][j] == 1)
        {
            input[i+1][j] = input[i][j];
            nodes.push_back({i+1, j});
        }
        if(j > 0 && input[i][j-1] == 1)
        {
            input[i][j-1] = input[i][j];
            nodes.push_back({i, j-1});
        }
        if(j < m-1 && input[i][j+1] == 1)
        {
            input[i][j+1] = input[i][j];
            nodes.push_back({i, j+1});
        }

        return nodes;
    }
};





int main()
{
    int n, m;
    cin >> n;
    cin >> m;

    Graph g(n, m);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            int v;
            cin >> v;
            g.make_adjacency_matrix(i, j, v);
        }
    }

    g.connected_subgraph();
    g.print();
    g.find_biggest_subgraph();

    return 0;
}
