#include<iostream>
using namespace std;

#define MAX 100
#define TEMP 0
#define PERM 1
#define infinity 9999
#define NIL -1

void findpath(int s, int v);
void dijkstra(int s);
int min_temp();
void create_graph();

int n;
int adj[MAX][MAX];
int predecessor[MAX];
int pathlength[MAX];
int status[MAX];

int main() {
    int s, v;
    create_graph();
    cout << "Enter the source vertex: ";
    cin >> s;
    dijkstra(s);
    while (true) {
        cout << "Enter the destination vertex (-1 to quit): ";
        cin >> v;
        if (v == -1)
            break;
        if (v < 0 || v >= n)
            cout << "These vertex does not exist.\n";
        else if (v == s)
            cout << "Source and destination vertices are the same.\n";
        else if (pathlength[v] == infinity)
            cout << "There is no path from source to destination vertex.\n";
        else
            findpath(s, v);
    }
    return 0;
}

void dijkstra(int s) {
    int i, current;
    for (i = 0; i < n; i++) {
        predecessor[i] = NIL;
        pathlength[i] = infinity;
        status[i] = TEMP;
    }
    pathlength[s] = 0;
    while (true) {
        current = min_temp();
        if (current == NIL)
            return;
        status[current] = PERM;
        for (i = 0; i < n; i++) {
            if (adj[current][i] != 0 && status[i] == TEMP) {
                if (pathlength[current] + adj[current][i] < pathlength[i]) {
                    predecessor[i] = current;
                    pathlength[i] = pathlength[current] + adj[current][i];
                }
            }
        }
    }
}

int min_temp() {
    int i;
    int min = infinity;
    int k = NIL;
    for (i = 0; i < n; i++) {
        if (status[i] == TEMP && pathlength[i] < min) {
            min = pathlength[i];
            k = i;
        }
    }
    return k;
}

void findpath(int s, int v) {
    int i, u;
    int path[MAX];
    int shortlist = 0;
    int count = 0;
    while (v != s) {
        count++;
        path[count] = v;
        u = predecessor[v];
        shortlist += adj[u][v];
        v = u;
    }
    count++;
    path[count] = s;
    cout << "Shortest path is: ";
    for (i = count; i >= 1; i--)
        cout << path[i] << " ";
    cout << "\nShortest distance is: " << shortlist << endl;
}

void create_graph() {
    int i, max_edges, origin, destin, wt;
    cout << "Enter the number of vertices: ";
    cin >> n;
    max_edges = n * (n - 1);
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }
    for (i = 1; i <= max_edges; i++) {
        cout << "Enter edge (-1 -1 to quit): ";
        cin >> origin >> destin;
        if (origin == -1 && destin == -1)
            break;
        cout << "Enter the weight for edge: ";
        cin >> wt;
        if (origin == -1 || destin >= n || origin < 0 || destin < 0) {
            cout << "Invalid edge.\n";
            i--;
        }
        else
            adj[origin][destin] = wt;
    }
}

/*

OUTPUT:
Enter the number of vertices: 8
Enter edge (-1 -1 to quit): 0 1
Enter the weight for edge: 8
Enter edge (-1 -1 to quit): 0 2
Enter the weight for edge: 2
Enter edge (-1 -1 to quit): 0 3
Enter the weight for edge: 7
Enter edge (-1 -1 to quit): 1 5
Enter the weight for edge: 16
Enter edge (-1 -1 to quit): 2 0
Enter the weight for edge: 5
Enter edge (-1 -1 to quit): 2 3
Enter the weight for edge: 4
Enter edge (-1 -1 to quit): 2 6
Enter the weight for edge: 3
Enter edge (-1 -1 to quit): 3 4
Enter the weight for edge: 9
Enter edge (-1 -1 to quit): 4 0
Enter the weight for edge: 4
Enter edge (-1 -1 to quit): 4 5
Enter the weight for edge: 5
Enter edge (-1 -1 to quit): 4 7
Enter the weight for edge: 8
Enter edge (-1 -1 to quit): 6 2
Enter the weight for edge: 6
Enter edge (-1 -1 to quit): 6 3
Enter the weight for edge: 3
Enter edge (-1 -1 to quit): 6 4
Enter the weight for edge: 4
Enter edge (-1 -1 to quit): 7 6
Enter the weight for edge: 5
Enter edge (-1 -1 to quit): 7 5
Enter the weight for edge: 2
Enter edge (-1 -1 to quit): -1 -1
Enter the source vertex: 0
Enter the destination vertex (-1 to quit): 3
Shortest path is: 0 2 3 
Shortest distance is: 6
Enter the destination vertex (-1 to quit): 4
Shortest path is: 0 2 6 4 
Shortest distance is: 9
Enter the destination vertex (-1 to quit): 
*/