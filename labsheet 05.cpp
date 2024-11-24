// NAME YASHWANT ROLLNO 2301010329 BTECH CSE 5
// lab sheet 05 data structure submit to : Sumen mam(professor )
// CODE 1 BINARY TREE 


#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left, *right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode *root;

    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        if (!root) {
            root = new TreeNode(value);
            return;
        }
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *temp = q.front();
            q.pop();
            if (!temp->left) {
                temp->left = new TreeNode(value);
                return;
            } else {
                q.push(temp->left);
            }
            if (!temp->right) {
                temp->right = new TreeNode(value);
                return;
            } else {
                q.push(temp->right);
            }
        }
    }

    void inOrder(TreeNode *node) {
        if (node) {
            inOrder(node->left);
            cout << node->value << " ";
            inOrder(node->right);
        }
    }

    void traverseInOrder() {
        inOrder(root);
        cout << endl;
    }
};
// main methode of this code is here 
int main()
{
    
void testBinaryTree() {
    BinaryTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    cout << "Binary Tree In-Order Traversal: ";
    tree.traverseInOrder(); // Expected: 40 20 50 10 30
}


}


// CODE 2 BST 
class BinarySearchTree : public BinaryTree {
public:
    void insertBST(TreeNode *&node, int value) {
        if (!node) {
            node = new TreeNode(value);
            return;
        }
        if (value < node->value)
            insertBST(node->left, value);
        else
            insertBST(node->right, value);
    }

    void insert(int value) {
        insertBST(root, value);
    }
};
// main methode is here 
int main()
{
    
void testBinarySearchTree() {
    BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    cout << "BST In-Order Traversal: ";
    bst.traverseInOrder(); // Expected: 20 30 40 50 60 70 80
}
void testBSTDeletion() {
    BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    bst.deleteNode(50); // Delete root node
    cout << "BST In-Order Traversal After Deletion: ";
    bst.traverseInOrder(); // Expected: 20 30 40 60 70 80
}

}


// CODE 3 AVL TREE 
class AVLTree : public BinarySearchTree {
private:
    int height(TreeNode *node) {
        if (!node) return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

    int balanceFactor(TreeNode *node) {
        if (!node) return 0;
        return height(node->left) - height(node->right);
    }

    TreeNode *rotateRight(TreeNode *y) {
        TreeNode *x = y->left;
        TreeNode *T = x->right;
        x->right = y;
        y->left = T;
        return x;
    }

    TreeNode *rotateLeft(TreeNode *x) {
        TreeNode *y = x->right;
        TreeNode *T = y->left;
        y->left = x;
        x->right = T;
        return y;
    }

    TreeNode *balance(TreeNode *node) {
        int bf = balanceFactor(node);
        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    TreeNode *insertAVL(TreeNode *node, int value) {
        if (!node) return new TreeNode(value);
        if (value < node->value)
            node->left = insertAVL(node->left, value);
        else if (value > node->value)
            node->right = insertAVL(node->right, value);
        else
            return node;
        return balance(node);
    }

public:
    void insert(int value) {
        root = insertAVL(root, value);
    }
};
// main methode of this code is here 
int main()
{
    void testAVLTree() {
    AVLTree avl;
    avl.insert(30);
    avl.insert(20);
    avl.insert(40);
    avl.insert(10);
    avl.insert(25);

    cout << "AVL Tree In-Order Traversal: ";
    avl.traverseInOrder(); // Expected: 10 20 25 30 40
}
void testAVLTreeDeletion() {
    AVLTree avl;
    avl.insert(30);
    avl.insert(20);
    avl.insert(40);
    avl.insert(10);
    avl.insert(25);

    avl.deleteNode(30);
    cout << "AVL Tree In-Order Traversal After Deletion: ";
    avl.traverseInOrder(); // Expected: 10 20 25 40
}
void testAdjacencyList() {
    Graph g(5);
    g.addEdgeList(0, 1);
    g.addEdgeList(0, 2);
    g.addEdgeList(1, 3);
    g.addEdgeList(2, 4);

    cout << "Adjacency List BFS Traversal Starting from Node 0: ";
    g.BFS(0); // Expected: 0 1 2 3 4
}
void testAdjacencyMatrix() {
    Graph g(3);
    g.addEdgeMatrix(0, 1);
    g.addEdgeMatrix(1, 2);

    cout << "Adjacency Matrix BFS Traversal Starting from Node 0: ";
    g.BFS(0); // Expected: 0 1 2
}

}




// GRAPH IMPLEMETATION 
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> adjList;

public:
    Graph(int v) : vertices(v), adjMatrix(v, vector<int>(v, 0)), adjList(v) {}

    void addEdgeList(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // For undirected graph
    }

    void addEdgeMatrix(int u, int v, int weight = 1) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; // For undirected graph
    }

    void BFS(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        cout << endl;
    }

    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << node << " ";
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor])
                DFSUtil(neighbor, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(vertices, false);
        DFSUtil(start, visited);
        cout << endl;
    }
};


// main methode is here 
int main()
{
    void testGraphTraversals() {
    Graph g(5);
    g.addEdgeList(0, 1);
    g.addEdgeList(0, 2);
    g.addEdgeList(1, 3);
    g.addEdgeList(2, 4);

    cout << "Graph BFS Traversal: ";
    g.BFS(0); // Expected: 0 1 2 3 4

    cout << "Graph DFS Traversal: ";
    g.DFS(0); // Expected: 0 1 3 2 4
}
void testDijkstra() {
    Graph g(5);
    g.addEdgeMatrix(0, 1, 2);
    g.addEdgeMatrix(0, 2, 4);
    g.addEdgeMatrix(1, 2, 1);
    g.addEdgeMatrix(1, 3, 7);
    g.addEdgeMatrix(2, 4, 3);

    g.dijkstra(0);
    // Expected Shortest Distances:
    // Node 0: 0
    // Node 1: 2
    // Node 2: 3
    // Node 3: 9
    // Node 4: 6
}
void testBellmanFord() {
    Graph g(5);
    g.addEdgeMatrix(0, 1, -1);
    g.addEdgeMatrix(0, 2, 4);
    g.addEdgeMatrix(1, 2, 3);
    g.addEdgeMatrix(1, 3, 2);
    g.addEdgeMatrix(3, 2, 5);
    g.addEdgeMatrix(3, 4, 1);

    g.bellmanFord(0);
    // Expected Shortest Distances:
    // Node 0: 0
    // Node 1: -1
    // Node 2: 2
    // Node 3: 1
    // Node 4: 2
}
void testPrimsAlgorithm() {
    Graph g(5);
    g.addEdgeMatrix(0, 1, 2);
    g.addEdgeMatrix(0, 3, 6);
    g.addEdgeMatrix(1, 2, 3);
    g.addEdgeMatrix(1, 3, 8);
    g.addEdgeMatrix(1, 4, 5);
    g.addEdgeMatrix(2, 4, 7);
    g.addEdgeMatrix(3, 4, 9);

    g.prims();
    // Expected MST Edges and Weights
}
void testKruskalsAlgorithm() {
    Graph g(5);
    g.addEdgeMatrix(0, 1, 10);
    g.addEdgeMatrix(0, 2, 6);
    g.addEdgeMatrix(0, 3, 5);
    g.addEdgeMatrix(1, 3, 15);
    g.addEdgeMatrix(2, 3, 4);

    g.kruskals();
    // Expected MST Edges and Weights
}

}



