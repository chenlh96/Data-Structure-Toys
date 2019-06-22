#ifndef GRATH_H
#define GRATH_H
#include "stackNQueue.h"
#include <iostream>
#include <limits>
using namespace std;

const int maxNumOfVertex = 50;
const int maxNumOfEdges = maxNumOfVertex * maxNumOfVertex;

template <class DataType>
class adjMatrixGraph
{
  private:
    DataType vertex[maxNumOfVertex];
    int arc[maxNumOfVertex][maxNumOfVertex], numOfVertex, numOfArc;
    bool isDirected;
    void InsertEdge();
    void DFS(int v, int visit[]);
    // void DFS(int v);

  public:
    adjMatrixGraph(/* args */);
    adjMatrixGraph(const adjMatrixGraph<DataType> &matg);
    adjMatrixGraph(DataType arr[], int n, int e, bool isDirect = false);
    ~adjMatrixGraph() {}
    void InsertNoWeightEdge(int i, int j);
    void InsertEdge(int i, int j, int w);
    void BFS(int v);
    void DFS(int v);
    template <class T>
    friend void Prim(adjMatrixGraph<T> &g);
    template <class T>
    friend void Kruskal(adjMatrixGraph<T> &g);
    template <class T>
    friend void Dijkstra(adjMatrixGraph<T> &g, int v);
    template <class T>
    friend void Floyd(adjMatrixGraph<T> &g);
    template <class T>
    friend void HamiltonPath(adjMatrixGraph<T> graph, int v, T path[]);
    template <class T>
    friend void HamiltonPathDFS(adjMatrixGraph<T> &graph, int currIdx, int count, bool visit[], T path[]);
    friend int SelectHospitalPoint(adjMatrixGraph<int> villageGraph);

    template <class T>
    friend int CalNodesOfNDeg(adjMatrixGraph<T> &mat, int n);
};

template <class DataType>
adjMatrixGraph<DataType>::adjMatrixGraph()
{
    this->numOfArc = this->numOfVertex = 0;
    for (int i = 0; i != maxNumOfVertex; i++)
        for (int j = 0; j != maxNumOfVertex; j++)
            this->arc[i][j] = 0;
}

template <class DataType>
adjMatrixGraph<DataType>::adjMatrixGraph(const adjMatrixGraph<DataType> &matg)
{
    this->numOfArc = matg.numOfArc;
    this->numOfVertex = matg.numOfVertex;
    this->isDirected = matg.isDirected;
    for (int i = 0; i != this->numOfVertex; i++)
        this->vertex[i] = matg.vertex[i];

    for (int i = 0; i != maxNumOfVertex; i++)
    {
        for (int j = 0; j != maxNumOfVertex; j++)
        {
            if (i < this->numOfVertex && j < this->numOfVertex)
                this->arc[i][j] = matg.arc[i][j];
            else
                this->arc[i][j] = 0;
        }
    }
}

template <class DataType>
adjMatrixGraph<DataType>::adjMatrixGraph(DataType arr[], int n, int e, bool isDirect)
{
    this->numOfArc = e;
    this->numOfVertex = n;
    for (int i = 0; i != maxNumOfVertex; i++)
        for (int j = 0; j != maxNumOfVertex; j++)
            this->arc[i][j] = 0;
    this->isDirected = isDirect;
    for (int i = 0; i != n; i++)
        this->vertex[i] = arr[i];
    // for (int i = 0; i != this->numOfArc; i++)
    //     InsertEdge();
}

template <class DataType>
void adjMatrixGraph<DataType>::InsertEdge()
{
    cout << "Please input the vertex of this edge: ";
    int i, j;
    cin >> i >> j;
    InsertEdge(i, j, 1);
}

template <class DataType>
void adjMatrixGraph<DataType>::InsertNoWeightEdge(int i, int j)
{
    InsertEdge(i, j, 1);
}

template <class DataType>
void adjMatrixGraph<DataType>::InsertEdge(int i, int j, int w)
{
    this->arc[i][j] = w;
    if (!this->isDirected)
        this->arc[j][i] = w;
}

template <class DataType>
void adjMatrixGraph<DataType>::DFS(int v, int visit[])
{
    cout << vertex[v] << " ";
    visit[v] = 1;
    for (int i = 0; i != numOfVertex; i++)
    {
        if (arc[v][i] != 0 && visit[i] == 0)
            DFS(i, visit);
    }
}

template <class DataType>
void adjMatrixGraph<DataType>::DFS(int v)
{
    int visit[maxNumOfVertex];
    for (int i = 0; i != this->numOfVertex; i++)
        visit[i] = 0;
    DFS(v, visit);
}

template <class DataType>
void adjMatrixGraph<DataType>::BFS(int v)
{
    int visit[maxNumOfVertex];
    for (int i = 0; i != this->numOfVertex; i++)
        visit[i] = 0;
    DataType vertexQueue[maxNumOfEdges];
    int front = -1, rear = -1;

    cout << vertex[v] << " ";
    visit[v] = 1;
    vertexQueue[++rear] = v;
    while (front != rear)
    {
        v = vertexQueue[++front];
        for (int i = 0; i != numOfVertex; i++)
        {
            if (arc[v][i] != 0 && visit[i] == 0)
            {
                cout << vertex[i] << " ";
                visit[i] = 1;
                vertexQueue[++rear] = i;
            }
        }
    }
}

struct arcNode
{
    int vertexIdx, weight;
    arcNode *next;
};

template <class DataType>
struct vertexNode
{
    DataType vertex;
    arcNode *headEdge;
};

template <class DataType>
class adjListGraph
{
  private:
    vertexNode<DataType> vertexList[maxNumOfVertex];
    int numOfVertex, numOfArc;
    bool isDirect;
    void InsertEdge();
    void DFS(int v, int visit[]);
    bool IsArrivalAll(int visit[]);

  public:
    adjListGraph(/* args */);
    adjListGraph(const adjListGraph<DataType> &graph);
    adjListGraph(DataType arr[], int n, int e, bool isDirected = false);
    ~adjListGraph();
    void InsertEdge(int i, int j, int w);
    void InsertNoWeightEdge(int i, int j);
    void BFS(int v);
    void DFS(int v);
    void RoutineBFS(int i, int j);
    void RoutineDFS(int i, int j);
    void NoRecursiveDFS(int v);
};

template <class DataType>
adjListGraph<DataType>::adjListGraph(/* args */)
{
    this->numOfArc = this->numOfVertex = 0;
}

template <class DataType>
adjListGraph<DataType>::adjListGraph(const adjListGraph<DataType> &graph)
{
    this->numOfArc = graph.numOfArc;
    this->numOfVertex = graph.numOfVertex;
    this->isDirect = graph.isDirect;
    for (int i = 0; i != this->numOfVertex; i++)
    {
        this->vertexList[i] = graph.vertexList[i];
        arcNode *a = graph.vertexList[i].headEdge, *newa = new arcNode, *nexta;
        newa->vertexIdx = a->vertexIdx;
        newa->next = NULL;
        this->vertexList[i].headEdge = newa;
        while (a->next != NULL)
        {
            a = a->next;
            nexta = new arcNode;
            nexta->vertexIdx = a->vertexIdx;
            nexta->next = NULL;
            newa->next = nexta;
            newa = nexta;
        }
    }
}

template <class DataType>
adjListGraph<DataType>::adjListGraph(DataType arr[], int n, int e, bool isDirected)
{
    this->numOfArc = e;
    this->numOfVertex = n;
    this->isDirect = isDirected;
    for (int i = 0; i != n; i++)
    {
        vertexList[i].vertex = arr[i];
        vertexList[i].headEdge = NULL;
    }

    // for (int i = 0; i != numOfArc; i++)
    //     InsertEdge();
}

template <class DataType>
adjListGraph<DataType>::~adjListGraph()
{
    for (int i = 0; i != this->numOfVertex; i++)
    {
        arcNode *del = vertexList[i].headEdge;
        while (vertexList[i].headEdge != NULL)
        {
            vertexList[i].headEdge = vertexList[i].headEdge->next;
            delete del;
            del = vertexList[i].headEdge;
        }
    }
}

template <class DataType>
void adjListGraph<DataType>::InsertEdge()
{
    cout << "Please input the vertex of this edge: ";
    int i, j;
    cin >> i >> j;
    InsertEdge(i, j, 1);
}

template <class DataType>
void adjListGraph<DataType>::InsertNoWeightEdge(int i, int j)
{
    InsertEdge(i, j, 1);
}

template <class DataType>
void adjListGraph<DataType>::InsertEdge(int i, int j, int w)
{
    arcNode *a = new arcNode;
    a->vertexIdx = j;
    a->next = vertexList[i].headEdge;
    vertexList[i].headEdge = a;
    if (!this->isDirect)
    {
        arcNode *arev = new arcNode;
        arev->vertexIdx = i;
        arev->next = vertexList[j].headEdge;
        vertexList[j].headEdge = arev;
    }
}

template <class DataType>
void adjListGraph<DataType>::BFS(int v)
{
    int vertexQueue[numOfVertex], visit[maxNumOfVertex], front = -1, rear = -1;
    for (int i = 0; i != this->numOfVertex; i++)
        visit[i] = 0;
    cout << vertexList[v].vertex << " ";
    visit[v] = 1;
    vertexQueue[++rear] = v;

    while (front != rear)
    {
        arcNode *a = vertexList[vertexQueue[++front]].headEdge;
        while (a != NULL)
        {
            int i = a->vertexIdx;
            if (visit[i] == 0)
            {
                cout << vertexList[i].vertex << " ";
                visit[i] = 1;
                vertexQueue[++rear] = i;
            }
            a = a->next;
        }
    }
}

template <class DataType>
void adjListGraph<DataType>::DFS(int v)
{
    int visit[this->numOfVertex];
    for (int i = 0; i != this->numOfVertex; i++)
        visit[i] = 0;
    DFS(v, visit);
}

template <class DataType>
bool adjListGraph<DataType>::IsArrivalAll(int visit[])
{
    for (int i = 0; i != this->numOfVertex; i++)
    {
        if (visit[i] == 0)
            return false;
    }
    return true;
}

template <class DataType>
void adjListGraph<DataType>::NoRecursiveDFS(int v)
{
    int visit[maxNumOfVertex], vertexStack[maxNumOfVertex], top = -1, cv = v;
    for (int i = 0; i != this->numOfVertex; i++)
        visit[i] = 0;

    cout << this->vertexList[cv].vertex << " ";
    vertexStack[++top] = cv;
    visit[cv] = 1;
    arcNode *a = this->vertexList[cv].headEdge;
    while (a != NULL && top != -1)
    {
        while (a != NULL)
        {
            if (visit[a->vertexIdx] == 0)
            {
                cout << this->vertexList[a->vertexIdx].vertex << " ";
                vertexStack[++top] = a->vertexIdx;
                visit[a->vertexIdx] = 1;
                a = this->vertexList[a->vertexIdx].headEdge;
            }
            else
                a = a->next;
        }
        if (top != -1)
        {
            cv = vertexStack[top--];
            a = vertexList[cv].headEdge;
            while (a != NULL && visit[a->vertexIdx])
                a = a->next;
        }
    }
}

template <class DataType>
void adjListGraph<DataType>::RoutineBFS(int i, int j)
{
    int visit[maxNumOfVertex], vertexQueue[this->numOfVertex], front = -1, rear = front;
    for (int i = 0; i != this->numOfVertex; i++)
        visit[i] = 0;
    visit[i] = 1;
    vertexQueue[++rear] = i;
    bool hasRoutine = false;

    while (front != rear && !hasRoutine)
    {
        int curr = vertexQueue[++front];
        arcNode *a = this->vertexList[curr].headEdge;
        while (a != NULL && !hasRoutine)
        {
            if (a->vertexIdx == j)
                hasRoutine = true;
            else
            {
                if (visit[a->vertexIdx] == 0)
                {
                    visit[a->vertexIdx] = 1;
                    vertexQueue[++rear] = a->vertexIdx;
                }
                else
                    a = a->next;
            }
        }
    }

    cout << "Routine Exist: " << (hasRoutine ? "Y" : "N");
}

template <class DataType>
void adjListGraph<DataType>::RoutineDFS(int i, int j)
{
    int visit[maxNumOfVertex], vertexStack[maxNumOfVertex], top = -1;
    for (int i = 0; i != this->numOfVertex; i++)
        visit[i] = 0;
    visit[i] = 1;
    vertexStack[++top] = i;
    bool hasRoutine = false;
    arcNode *a = this->vertexList[i].headEdge;

    while (top != -1 && !hasRoutine)
    {
        while (a != NULL && !hasRoutine)
        {
            if (a->vertexIdx == j)
                hasRoutine = true;
            else if (visit[a->vertexIdx] == 0)
            {
                vertexStack[++top] = a->vertexIdx;
                visit[a->vertexIdx] = 1;
                a = this->vertexList[a->vertexIdx].headEdge;
            }
            else
                a = a->next;
        }

        if (top != -1 && !hasRoutine)
        {
            i = vertexStack[--top];
            a = vertexList[i].headEdge;
        }
    }

    if (top == -1)
        cout << "No routine";
    else
    {
        cout << "Routine: " << this->vertexList[j].vertex << "<-";
        while (top != 0)
            cout << this->vertexList[vertexStack[top--]].vertex << "<-";
        cout << this->vertexList[vertexStack[top--]].vertex;
    }
}

template <class DataType>
void adjListGraph<DataType>::DFS(int v, int visit[])
{
    cout << vertexList[v].vertex << " ";
    visit[v] = 1;
    arcNode *a = vertexList[v].headEdge;
    while (a != NULL)
    {
        int i = a->vertexIdx;
        if (visit[i] == 0)
            DFS(i, visit);
        a = a->next;
    }
}

template <class DataType>
struct DAGVertexNode
{
    DataType vertex;
    int inDegree;
    arcNode *headEdge;
};

template <class DataType>
class directAcyclicGraph
{
  private:
    DAGVertexNode<DataType> vertexList[maxNumOfVertex];
    int numOfVertex, numOfArc;
    void InsertEdge();

  public:
    directAcyclicGraph(/* args */);
    directAcyclicGraph(const directAcyclicGraph<DataType> &graph);
    directAcyclicGraph(DataType arr[], int n, int e);
    ~directAcyclicGraph();
    void InsertEdge(int i, int j, int w);
    void InsertNoWeightEdge(int i, int j);
    template <class T>
    friend void TopologicalSort(directAcyclicGraph<T> aovn, T order[]);
    template <class T>
    friend void CriticalPath(directAcyclicGraph<T> aovn);
};

template <class DataType>
directAcyclicGraph<DataType>::directAcyclicGraph(/* args */)
{
    this->numOfArc = this->numOfVertex = 0;
}

template <class DataType>
directAcyclicGraph<DataType>::directAcyclicGraph(DataType arr[], int n, int e)
{
    this->numOfArc = e;
    this->numOfVertex = n;
    for (int i = 0; i != n; i++)
    {
        vertexList[i].vertex = arr[i];
        vertexList[i].inDegree = 0;
        vertexList[i].headEdge = NULL;
    }

    // for (int i = 0; i != numOfArc; i++)
    //     InsertEdge();
}

template <class DataType>
directAcyclicGraph<DataType>::directAcyclicGraph(const directAcyclicGraph<DataType> &graph)
{
    this->numOfArc = graph.numOfArc;
    this->numOfVertex = graph.numOfVertex;
    for (int i = 0; i != this->numOfVertex; i++)
    {
        this->vertexList[i] = graph.vertexList[i];
        arcNode *a = graph.vertexList[i].headEdge, *newa = new arcNode, *nexta;
        if (a != NULL)
        {
            newa->vertexIdx = a->vertexIdx;
            newa->weight = a->weight;
            newa->next = NULL;
            this->vertexList[i].headEdge = newa;
            while (a->next != NULL)
            {
                a = a->next;
                nexta = new arcNode;
                nexta->vertexIdx = a->vertexIdx;
                nexta->weight = a->weight;
                nexta->next = NULL;
                newa->next = nexta;
                newa = nexta;
            }
        }
    }
}

template <class DataType>
directAcyclicGraph<DataType>::~directAcyclicGraph()
{
    for (int i = 0; i != this->numOfVertex; i++)
    {
        arcNode *del = vertexList[i].headEdge;
        while (vertexList[i].headEdge != NULL)
        {
            vertexList[i].headEdge = vertexList[i].headEdge->next;
            delete del;
            del = vertexList[i].headEdge;
        }
    }
}

template <class DataType>
void directAcyclicGraph<DataType>::InsertEdge()
{
    cout << "Please input the vertex of this edge: ";
    int i, j;
    cin >> i >> j;
    InsertEdge(i, j, 1);
}

template <class DataType>
void directAcyclicGraph<DataType>::InsertEdge(int i, int j, int w)
{
    arcNode *a = new arcNode;
    a->vertexIdx = j;
    a->weight = w;
    a->next = vertexList[i].headEdge;
    vertexList[i].headEdge = a;
    vertexList[j].inDegree++;
}

template <class DataType>
void directAcyclicGraph<DataType>::InsertNoWeightEdge(int i, int j)
{
    InsertEdge(i, j, 1);
}

struct costOfVertex
{
    int minCostAdjIdx, minCost;
};

template <class T>
void Prim(adjMatrixGraph<T> &g)
{
    costOfVertex cost[maxNumOfVertex];
    for (int i = 1; i != g.numOfVertex; i++)
    {
        cost[i].minCost = g.arc[0][i];
        if (cost[i].minCost == 0)
            cost[i].minCost = INT16_MAX;
        cost[i].minCostAdjIdx = 0;
    }

    cost[0].minCost = 0;
    cost[0].minCostAdjIdx = 0;

    for (int i = 1; i != g.numOfVertex; i++)
    {
        int minIdx, minCost = INT16_MAX;
        for (int j = 0; j != g.numOfVertex; j++)
        {
            if (cost[j].minCost != 0 && minCost > cost[j].minCost)
            {
                minCost = cost[j].minCost;
                minIdx = j;
            }
        }
        cout << g.vertex[minIdx] << " -> " << g.vertex[cost[minIdx].minCostAdjIdx]
             << " weight: " << cost[minIdx].minCost << "\n";
        cost[minIdx].minCost = 0;
        for (int j = 0; j != g.numOfVertex; j++)
        {
            if (g.arc[minIdx][j] != 0 && g.arc[minIdx][j] < cost[j].minCost)
            {
                cost[j].minCost = g.arc[minIdx][j];
                cost[j].minCostAdjIdx = minIdx;
            }
        }
    }
}

struct edge
{
    int start, end, weight;
};

struct edgeNode
{
    edge e;
    edgeNode *next;
};

template <class DataType>
struct edgeBasedGraph
{
    int numOfVertex, numOfEdges;
    DataType vertex[maxNumOfVertex];
    edgeNode *front, *rear;
};

template <class T>
void Kruskal(adjMatrixGraph<T> &g)
{
    edgeBasedGraph<T> eg;
    eg.numOfVertex = g.numOfVertex;
    eg.numOfEdges = g.numOfArc;
    for (int i = 0; i != g.numOfVertex; i++)
        eg.vertex[i] = g.vertex[i];

    eg.front = new edgeNode;
    eg.front->next = NULL;
    eg.rear = eg.front;
    for (int i = 0; i != g.numOfVertex; i++)
    {
        for (int j = 0; j != i; j++)
        {
            if (g.arc[i][j] != 0)
            {
                edgeNode *curr = new edgeNode;
                curr->e.start = i;
                curr->e.end = j;
                curr->e.weight = g.arc[i][j];
                curr->next = NULL;

                edgeNode *p = eg.front;
                bool isInserted = false;
                while (p->next != NULL && !isInserted)
                {
                    if (g.arc[i][j] < p->next->e.weight)
                    {
                        curr->next = p->next;
                        p->next = curr;
                        isInserted = true;
                    }
                    p = p->next;
                }
                if (!isInserted)
                {
                    curr->next = NULL;
                    eg.rear->next = curr;
                    eg.rear = curr;
                }
            }
        }
    }

    Kruskal<T>(eg);
}

int FindRoot(int parent[], int v)
{
    int t = v;
    while (parent[t] > -1)
        t = parent[t];
    return t;
}

template <class T>
void Kruskal(edgeBasedGraph<T> &g)
{
    int parentIdx[maxNumOfVertex];
    for (int i = 0; i != g.numOfVertex; i++)
        parentIdx[i] = -1;

    edgeNode *curr = g.front->next;
    int i = 0;
    while (curr != NULL && i != g.numOfVertex - 1)
    {
        int v1 = FindRoot(parentIdx, curr->e.start);
        int v2 = FindRoot(parentIdx, curr->e.end);
        if (v1 != v2)
        {
            cout << "Add edge: " << curr->e.start << " -> " << curr->e.end << "\n";
            parentIdx[v2] = v1;
            i++;
        }
        curr = curr->next;
    }
}

template <class T>
void Dijkstra(adjMatrixGraph<T> &g, int v)
{
    int dist[maxNumOfVertex], selected[maxNumOfVertex], prev[maxNumOfVertex];
    for (int i = 0; i != g.numOfVertex; i++)
    {
        dist[i] = INT16_MAX;
        selected[i] = 0;
    }

    dist[v] = 0;
    selected[v] = 1;
    int n = 1, currMinIdx = v, currMin;
    while (n != g.numOfVertex)
    {
        for (int i = 0; i != g.numOfVertex; i++)
        {
            if (selected[i] == 0 && g.arc[currMinIdx][i] != 0 && dist[currMinIdx] + g.arc[currMinIdx][i] < dist[i])
            {
                dist[i] = dist[currMinIdx] + g.arc[currMinIdx][i];
                prev[i] = currMinIdx;
            }
        }

        currMin = INT16_MAX;
        for (int i = 0; i != g.numOfVertex; i++)
        {
            if (dist[i] < currMin && selected[i] == 0)
            {
                currMin = dist[i];
                currMinIdx = i;
            }
        }
        selected[currMinIdx] = 1;
        n++;
    }

    for (int i = 0; i != g.numOfVertex; i++)
    {
        cout << "Path to " << i << " is: ";
        int prevIdx = i;
        while (prevIdx != v)
        {
            cout << prevIdx << "->";
            prevIdx = prev[prevIdx];
        }
        cout << v << " length: " << dist[i] << "\n";
    }
}

template <class T>
void Floyd(adjMatrixGraph<T> &g)
{
    int dist[maxNumOfVertex][maxNumOfVertex];
    for (int i = 0; i != g.numOfVertex; i++)
        for (int j = 0; j != g.numOfVertex; j++)
            dist[i][j] = g.arc[i][j];

    for (int k = 0; k != g.numOfVertex; k++)
    {
        for (int i = 0; i != g.numOfVertex; i++)
        {
            for (int j = 0; j != g.numOfVertex; j++)
            {
                if (dist[i][k] != 0 && dist[k][j] != 0 && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    int count = 0;
    for (int i = 0; i != g.numOfVertex; i++)
    {
        for (int j = 0; j != g.numOfVertex; j++)
        {
            if (dist[i][j] != 0)
            {
                cout << "Path: " << g.vertex[i] << "->" << g.vertex[j] << " length: " << dist[i][j] << " ";
                count++;
            }
            if (count == 5)
            {
                cout << "\n";
                count = 0;
            }
        }
    }
}

template <class DataType>
struct adjList
{
    vertexNode<DataType> vertexList[maxNumOfVertex];
    int numOfVertex, numOfArc;
    bool isDirected;
};

template <class DataType>
struct adjMatrix
{
    DataType vertex[maxNumOfVertex];
    int arc[maxNumOfVertex][maxNumOfVertex], numOfVertex, numOfArc;
    bool isDirected;
};

template <class DataType>
void CreateAdjMatrix(adjMatrix<DataType> &adjMat, DataType v[], int e[][3], int nv, int ne, bool isDirect)
{
    adjMat.numOfVertex = nv;
    adjMat.numOfArc = ne;
    adjMat.isDirected = isDirect;
    for (int i = 0; i != nv; i++)
        adjMat.vertex[i] = v[i];
    for (int i = 0; i != nv; i++)
        for (int j = 0; j != nv; j++)
            adjMat.arc[i][j] = 0;
    for (int i = 0; i != ne; i++)
    {
        adjMat.arc[e[i][0]][e[i][1]] = e[i][2];
        if (!isDirect)
            adjMat.arc[e[i][1]][e[i][0]] = e[i][2];
    }
}
template <class DataType>
void CreateAdjList(adjList<DataType> &adjLit, DataType v[], int e[][3], int nv, int ne, bool isDirect)
{
    adjLit.numOfVertex = nv;
    adjLit.numOfArc = ne;
    adjLit.isDirected = isDirect;
    for (int i = 0; i != nv; i++)
    {
        adjLit.vertexList[i].vertex = v[i];
        adjLit.vertexList[i].headEdge = NULL;
    }

    for (int i = 0; i != ne; i++)
    {
        arcNode *a = new arcNode;
        a->vertexIdx = e[i][1];
        a->weight = e[i][2];
        if (adjLit.vertexList[e[i][0]].headEdge != NULL)
            a->next = adjLit.vertexList[e[i][0]].headEdge;
        adjLit.vertexList[e[i][0]].headEdge = a;

        if (!isDirect)
        {
            arcNode *reva = new arcNode;
            reva->vertexIdx = e[i][0];
            reva->weight = e[i][2];
            if (adjLit.vertexList[e[i][1]].headEdge != NULL)
                reva->next = adjLit.vertexList[e[i][1]].headEdge;
            adjLit.vertexList[e[i][1]].headEdge = reva;
        }
    }
}

template <class DataType>
void PrintAdjMatrix(adjMatrix<DataType> adjMat)
{
    cout << " |";
    for (int i = 0; i != adjMat.numOfVertex; i++)
        cout << adjMat.vertex[i] << " ";
    cout << "\n"
         << "--";
    for (int i = 0; i != adjMat.numOfVertex; i++)
        cout << "--";
    cout << "\n";
    for (int i = 0; i != adjMat.numOfVertex; i++)
    {
        cout << adjMat.vertex[i] << "|";
        for (int j = 0; j != adjMat.numOfVertex; j++)
            cout << adjMat.arc[i][j] << " ";
        cout << "\n";
    }
}

template <class DataType>
void PrintAdjList(adjList<DataType> adjlist)
{
    for (int i = 0; i != adjlist.numOfVertex; i++)
    {
        cout << adjlist.vertexList[i].vertex;
        arcNode *a = adjlist.vertexList[i].headEdge;
        while (a != NULL)
        {
            cout << " -> " << adjlist.vertexList[a->vertexIdx].vertex;
            a = a->next;
        }
        cout << "\n";
    }
}

template <class DataType>
void Matrix2List(adjMatrix<DataType> &mat, adjList<DataType> &lit)
{
    lit.numOfVertex = mat.numOfVertex;
    lit.numOfArc = mat.numOfArc;
    for (int i = 0; i != lit.numOfVertex; i++)
        lit.vertexList[i].vertex = mat.vertex[i];

    for (int i = 0; i != lit.numOfVertex; i++)
    {
        for (int j = 0; j != lit.numOfVertex; j++)
        {
            if (mat.arc[i][j] != 0)
            {
                arcNode *a = new arcNode;
                a->vertexIdx = j;
                a->weight = mat.arc[i][j];
                a->next = lit.vertexList[i].headEdge;
                lit.vertexList[i].headEdge = a;
            }
        }
    }
}

template <class DataType>
void List2Matrix(adjMatrix<DataType> &mat, adjList<DataType> &lit)
{
    mat.numOfVertex = lit.numOfVertex;
    mat.numOfArc = lit.numOfArc;
    for (int i = 0; i != mat.numOfVertex; i++)
    {
        for (int j = 0; j != mat.numOfVertex; j++)
            mat.arc[i][j] = 0;
    }

    for (int i = 0; i != lit.numOfVertex; i++)
    {
        arcNode *a = lit.vertexList[i].headEdge;
        while (a != NULL)
        {
            mat.arc[i][a->vertexIdx] = a->weight;
            a = a->next;
        }
    }
}

template <class DataType>
int CalNodesOfNDeg(adjMatrixGraph<DataType> &mat, int n)
{
    int num = 0, m;
    for (int i = 0; i != mat.numOfVertex; i++)
    {
        m = 0;
        for (int j = 0; j != mat.numOfVertex; j++)
        {
            if (mat.arc[i][j] != 0)
                m++;
        }
        if (m == n)
            num++;
    }
    return num;
}

template <class DataType>
int CalZero(adjMatrixGraph<DataType> &mat)
{
    return CalNodesOfNDeg(mat, 0);
}

template <class DataType>
void ReverseAdjList(adjList<DataType> &des, adjList<DataType> &src)
{
    des.numOfVertex = src.numOfVertex;
    des.numOfArc = des.numOfArc;
    des.isDirected = des.isDirected;

    for (int i = 0; i != des.numOfVertex; i++)
    {
        des.vertexList[i].vertex = src.vertexList[i].vertex;
        des.vertexList[i].headEdge = NULL;
    }
    for (int i = 0; i != des.numOfVertex; i++)
    {
        arcNode *a = src.vertexList[i].headEdge;

        while (a != NULL)
        {
            arcNode *reva = new arcNode;
            reva->vertexIdx = i;
            reva->weight = a->weight;
            if (des.vertexList[a->vertexIdx].headEdge != NULL)
                reva->next = des.vertexList[a->vertexIdx].headEdge;
            des.vertexList[a->vertexIdx].headEdge = reva;
            a = a->next;
        }
    }
}

#endif // !GRATH_H