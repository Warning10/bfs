#include<iostream>
#include<vector>
#include<omp.h>
#include<queue>
#include<bits/stdc++.h>

using namespace std;

queue<int> q;

// Serial BFS function
void bfs_serial(int start, int* arr, int n, int visit[]) {
    for(int i = 0; i < n; i++) {
        if(*(arr + (n * start) + i) == 1 && visit[i] == 0) {
            cout << i << " ";
            q.push(i);
            visit[i] = 1;
        }
    }

    q.pop();

    if(!q.empty()) bfs_serial(q.front(), (int*)arr, n, visit);
}

// Parallel BFS function
void bfs_parallel(int start, int* arr, int n, int visit[]) {
    #pragma omp parallel for
    for(int i = 0; i < n; i++) {
        if((*(arr + (n * start) + i) == 1) && (visit[i] == 0)) {
            #pragma omp critical
            {
                cout << i << " ";
                q.push(i);
                visit[i] = 1;
            }
        }
    }

    #pragma omp single
    {
        q.pop();
    }

    if(!q.empty()) bfs_parallel(q.front(), (int*)arr, n, visit);
}

int main() {
    cout << "Enter the number of vertices: ";
    int n;
    cin >> n;

    int arr[n][n] = {0};

    cout << "Enter the number of edges: ";
    int edges;
    cin >> edges;

    for(int j = 0; j < edges; j++) {
        int a, b;
        cout << "Enter the two edges:" << endl;
        cin >> a >> b;
        arr[a][b] = 1;
        arr[b][a] = 1;
    }

    int visit[n] = {0};

    cout << "Enter the start vertex: ";
    int start;
    cin >> start;

    // Serial execution
    clock_t strt_serial = clock();

    visit[start] = 1;
    cout << start << " ";
    q.push(start);

    bfs_serial(start, (int*)arr, n, visit);

    clock_t stop_serial = clock();

    cout << "\nTime required (serial): " << (double)(stop_serial - strt_serial) << " ms" << endl;

    // Parallel execution
    clock_t strt_parallel = clock();

    memset(visit, 0, sizeof(visit)); // Reset visit array for parallel execution

    visit[start] = 1;
    cout << start << " ";
    q.push(start);

    bfs_parallel(start, (int*)arr, n, visit);

    clock_t stop_parallel = clock();

    cout << "\nTime required (parallel): " << (double)(stop_parallel - strt_parallel) << " ms" << endl;

    return 0;
}
