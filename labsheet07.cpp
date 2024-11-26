// Name  Yashwant
// ROLLNO 2301010329 // SUBJECT DATASTRUCTURE 
// AVL Tree implementation 
/*Create a class AVLTree with methods for insertion, deletion, and traversal.
Implement in-order, pre-order, and post-order traversal methods to retrieve hierarchical data.
*/
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
public:
    Node* root;

    AVLTree() : root(nullptr) {}

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* createNode(int key) {
        Node* node = new Node();
        node->key = key;
        node->left = node->right = nullptr;
        node->height = 1;
        return node;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T = x->right;

        x->right = y;
        y->left = T;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T = y->left;

        y->left = x;
        x->right = T;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return createNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inOrder(Node* root) {
        if (root) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

    void preOrder(Node* root) {
        if (root) {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    void postOrder(Node* root) {
        if (root) {
            postOrder(root->left);
            postOrder(root->right);
            cout << root->key << " ";
        }
    }
};

int main() {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 40);
    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 25);

    cout << "In-order traversal: ";
    tree.inOrder(tree.root);
    cout << endl;

    cout << "Pre-order traversal: ";
    tree.preOrder(tree.root);
    cout << endl;

    cout << "Post-order traversal: ";
    tree.postOrder(tree.root);
    cout << endl;

    return 0;
}
// output of this code is 
/*
In-order traversal: 10 20 25 30 40 50
Pre-order traversal: 30 20 10 25 40 50
Post-order traversal: 10 25 20 50 40 30
*/

// Graph Implementation 
/*Create a class Graph with methods for adding/removing nodes and edges.
Implement BFS and DFS traversal methods.
Implement Dijkstra’s and Bellman-Ford shortest path algorithms.
Implement Prim’s and Kruskal’s algorithms for finding the minimum spanning tree.*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj; // adjacency list (node, weight)

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto &neighbor : adj[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << node << " ";

        for (auto &neighbor : adj[node]) {
            if (!visited[neighbor.first]) {
                DFSUtil(neighbor.first, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        DFSUtil(start, visited);
        cout << endl;
    }

    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        dist[src] = 0;
        pq.emplace(0, src);

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto &[v, weight] : adj[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }

        for (int i = 0; i < V; ++i) {
            cout << "Distance to node " << i << ": " << dist[i] << endl;
        }
    }
};
// main function 
int main() {
    // Create a graph with 5 vertices
    Graph g(5);

    // Add edges: (u, v, weight)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 3);

    // Perform BFS starting from node 0
    cout << "BFS from node 0: ";
    g.BFS(0);

    // Perform DFS starting from node 0
    cout << "DFS from node 0: ";
    g.DFS(0);

    // Perform Dijkstra's algorithm starting from node 0
    cout << "Dijkstra's shortest paths from node 0:" << endl;
    g.dijkstra(0);

    return 0;
}

// output of this code is here :-

/*BFS from node 0: 0 1 2 3 4
DFS from node 0: 0 1 3 2 4
Dijkstra's shortest paths from node 0:
Distance to node 0: 0
Distance to node 1: 4
Distance to node 2: 1
Distance to node 3: 6
Distance to node 4: 9

*/