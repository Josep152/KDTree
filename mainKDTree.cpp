#include<bits/stdc++.h>
using namespace std;

const int k = 2;

struct Node
{
    int point[k];
    Node* left, * right;
};

template <class T>
struct KDTree {
    Node* root = NULL;
    // A method to create a node of K D tree
    struct Node* newNode(int arr[]) {
        struct Node* temp = new Node;

        for (int i = 0; i < k; i++)
            temp->point[i] = arr[i];

        temp->left = temp->right = NULL;
        return temp;
    }
    // Inserts a new node and returns root of modified tree
    // The parameter depth is used to decide axis of comparison
    Node* insertRec(Node* p, int point[], unsigned depth) {
        if (p == NULL)
            return newNode(point);
        // Calculate current dimension (cd) of comparison
        unsigned cd = depth % k;
        //cout << "depth: " << depth << '\n';
        // Compare the new point with root on current dimension 'cd'
        // and decide the left or right subtree
        if (point[cd] < (p->point[cd]))
            p->left = insertRec(p->left, point, depth + 1);
        else
            p->right = insertRec(p->right, point, depth + 1);

        return p;
    }
    Node* insert(int point[]) {
        return insertRec(root, point, 0);
    }

    // A utility method to determine if two Points are same
    // in K Dimensional space
    bool arePointsSame(int point1[], int point2[]) {
        // Compare individual pointinate values
        for (int i = 0; i < k; ++i)
            if (point1[i] != point2[i])
                return false;

        return true;
    }
    bool searchRec(Node* root, int point[], unsigned depth) {
        // Base cases
        if (root == NULL)
            return false;
        if (arePointsSame(root->point, point))
            return true;

        // Current dimension is computed using current depth and total
        // dimensions (k)
        unsigned cd = depth % k;

        // Compare point with root with respect to cd (Current dimension)
        if (point[cd] < root->point[cd])
            return searchRec(root->left, point, depth + 1);

        return searchRec(root->right, point, depth + 1);
    }

    // Searches a Point in the K D tree. It mainly uses
    // searchRec()
    bool search(int point[])
    {
        // Pass current depth as 0
        return searchRec(root, point, 0);
    }

    int distance(int point1[], int point2[]) {
        int sum = 0;
        for (int i = 0; i < k; ++i)
            sum += pow(point1[i] - point2[i], 2);
        return pow(sum, 1 / 2);
    }

    Node* nearest_neighbor(int key[], Node* current_node, Node* nearest_neighbors_candidate = NULL, double best_distance = 0, int depth = 0) {
        if (!current_node) {
            return NULL;
        }
        double probably = distance(current_node->point, key);
        if (probably < best_distance) {
            best_distance = probably;
            nearest_neighbors_candidate = current_node;
        }

        int axis = depth % k;
        bool right = false;
        if (key[axis] < current_node->point[axis]) {
            right = true;
            return nearest_neighbor(key, current_node->left, nearest_neighbors_candidate, best_distance, ++depth);
        }
        else {
            right = false;
            return nearest_neighbor(key, current_node->right, nearest_neighbors_candidate, best_distance, ++depth);
        }

        if (abs(current_node->point[axis] - key[axis]) < nearest_neighbors_candidate->point[axis]) {
            if (right) {
                return nearest_neighbor(key, current_node->left, nearest_neighbors_candidate, best_distance, ++depth);
            }
            else {
                return nearest_neighbor(key, current_node->right, nearest_neighbors_candidate, best_distance, ++depth);
            }
        }
    }
    void vecino_mas_cercano(int point1[]) {
        if (root && search(point1)) {
            double best_now = distance(root->point, point1);
            Node* result = nearest_neighbor(point1, root, NULL, best_now, 0);
            cout << "\n" << result->point[0] << ' ' << result->point[1] << '\n';
        }
        else {
            cout << "\nNo hay vecinos cercanos\n";
        }
    }
};

int main()
{
    struct KDTree<int> first;
    int points[][k] = { {3, 6}, {17, 15}, {13, 15}, {6, 12},
                       {9, 1}, {2, 7}, {10, 19} };

    int n = sizeof(points) / sizeof(points[0]);

    for (int i = 0; i < n; i++)
        first.root = first.insert(points[i]);
    int point_proof[k] = { 3 , 6 };
    int point1[] = { 3, 6 };
    (first.search(point1)) ? cout << "Found\n" : cout << "Not Found\n";

    int point2[] = { 10, 19 };
    (first.search(point2)) ? cout << "Found\n" : cout << "Not Found\n";
    //first.vecino_mas_cercano(point_proof);            //No se termino de adaptar por completo el codigo de la estructura
                                                        //con el codigo dado en clase, se encontraron bastantes fallos
                                                        //A lo que si se llego, fue a insertar y buscar puntos en el arbol
    return 0;
}