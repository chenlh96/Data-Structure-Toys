#include "Header/graph.h"

// 1.	邻接矩阵的实现：实验书p219页
// 2.	邻接表的实现：实验书p222页
// 3.	最小生成树算法Prim的实现：课本p164页
// 4.	最小生成树算法Kruskal的实现：课本p167页
// 5.	 Dijkstra算法的实现：课本p170页
// 6.	 Floyd算法的实现：课本p173页

// 7.	设计算法，将一个无向图的邻接矩阵转换为邻接表：实验书p102
// 8.	设计算法，将一个无向图的邻接表转换为邻接矩阵：实验书p103
// 9.	设计算法，计算图中出度为0的顶点个数：实验书p104
// 10.	以邻接表作存储结构，设计按深度优先遍历图的非递归算法：实验书p104
// 11.	已知一个有向图的邻接表，编写算法建立其逆邻接表。实验书p104
// 12.	分别基于深度优先和广度优先搜索编写算法，判断以邻接表存储的有向图中是否存在由顶点vi到顶点vj的路径（i≠j)。实验书p105

template <class T>
void PrintGraphInfo(adjMatrixGraph<T> &graph, T infoOfVertex[], int infoOfEdge[][3], int numOfVertex, int numOfEdge)
{
    cout << "The vertexes has: ";
    for (int i = 0; i != numOfVertex; i++)
        cout << infoOfVertex[i] << " ";
    cout << "\n";
    for (int i = 0; i != numOfEdge; i++)
    {
        cout << "Insert edge: " << infoOfVertex[infoOfEdge[i][0]] << " to " << infoOfVertex[infoOfEdge[i][1]] << " with weight " << infoOfEdge[i][2] << "\n";
        graph.InsertEdge(infoOfEdge[i][0], infoOfEdge[i][1], infoOfEdge[i][2]);
    }
}

template <class T>
void PrintGraphInfo(adjListGraph<T> &graph, T infoOfVertex[], int infoOfEdge[][3], int numOfVertex, int numOfEdge)
{
    cout << "The vertexes has: ";
    for (int i = 0; i != numOfVertex; i++)
        cout << infoOfVertex[i] << " ";
    cout << "\n";
    for (int i = 0; i != numOfEdge; i++)
    {
        cout << "Insert edge: " << infoOfVertex[infoOfEdge[i][0]] << " to " << infoOfVertex[infoOfEdge[i][1]] << " with weight " << infoOfEdge[i][2] << "\n";
        graph.InsertEdge(infoOfEdge[i][0], infoOfEdge[i][1], infoOfEdge[i][2]);
    }
}

int main()
{
    cout << "Begin to test the graph class implement by adjacency matrix\n";
    bool isDirectGraph = false;
    const int numOfVertex = 5, numOfEdge = 7;
    char infoOfVertex[numOfVertex] = {'a', 'b', 'c', 'd', 'e'};
    int infoOfEdge[numOfEdge][3] = {{0, 1, 9},
                                    {3, 0, 3},
                                    {1, 2, 4},
                                    {0, 2, 6},
                                    {1, 3, 5},
                                    {4, 3, 8},
                                    {2, 4, 7}};

    adjMatrixGraph<char> matg(infoOfVertex, numOfVertex, numOfEdge, isDirectGraph);
    PrintGraphInfo<char>(matg, infoOfVertex, infoOfEdge, numOfVertex, numOfEdge);

    cout << "BFS result is: ";
    matg.BFS(1);
    cout << "\n"
         << "DFS result is: ";
    matg.DFS(0);

    cout << "\n"
         << "Begin to test the graph class implement by adjacency LIST\n";

    adjListGraph<char> listg(infoOfVertex, numOfVertex, numOfEdge, isDirectGraph);
    PrintGraphInfo<char>(listg, infoOfVertex, infoOfEdge, numOfVertex, numOfEdge);

    cout << "BFS result is: ";
    listg.BFS(1);
    cout << "\n"
         << "DFS result is: ";
    listg.DFS(0);

    cout << "\n"
         << "\n"
         << "Begin to test the PRIM algorithm: \n";

    const int numOfVertex1 = 6, numOfEdge1 = 9;
    int infoOfVertex1[numOfVertex1] = {1, 2, 3, 4, 5, 6};
    int infoOfEdge1[numOfEdge1][3] = {{0, 1, 34},
                                      {0, 2, 46},
                                      {0, 5, 19},
                                      {1, 4, 12},
                                      {2, 3, 17},
                                      {2, 5, 25},
                                      {3, 4, 38},
                                      {3, 5, 25},
                                      {4, 5, 26}};
    bool isDirectGraph1 = false;
    adjMatrixGraph<int> primTestGraph(infoOfVertex1, numOfVertex1, numOfEdge1, isDirectGraph1);
    PrintGraphInfo<int>(primTestGraph, infoOfVertex1, infoOfEdge1, numOfVertex1, numOfEdge1);

    Prim<int>(primTestGraph);

    adjMatrixGraph<int> kruskalTestGraph(primTestGraph);
    cout << "\n"
         << "Begin to test the KRUSKAL algorithm: \n"
         << "we use the same graph as a test graph and the result is: \n";
    Kruskal<int>(kruskalTestGraph);

    cout << "\n"
         << "Begin to test the DIJSKTRA algorithm. The test graph is constructed below: \n";
    const int numOfVertex2 = 6, numOfEdge2 = 9;
    bool isDirectGraph2 = false;
    char infoOfVertex2[numOfVertex2] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int infoOfEdge2[numOfEdge2][3] = {{0, 1, 6},
                                      {0, 2, 3},
                                      {1, 2, 2},
                                      {1, 3, 5},
                                      {2, 3, 3},
                                      {2, 4, 4},
                                      {3, 4, 2},
                                      {3, 5, 3},
                                      {4, 5, 5}};
    adjMatrixGraph<char> minPathTestSample(infoOfVertex2, numOfVertex2, numOfEdge2, isDirectGraph2);
    PrintGraphInfo<char>(minPathTestSample, infoOfVertex2, infoOfEdge2, numOfVertex2, numOfEdge2);

    Dijkstra<char>(minPathTestSample, 0);

    cout << "\n"
         << "Also use this sample to test the FLOYD algorithm, the result is: \n";
    Floyd<char>(minPathTestSample);

    cout << '\n'
         << "Begin to test the transfer algorothm between adjancent matrix and adjancent list.\n";
    // PrintGraphInfo<char>(matg, infoOfVertex, infoOfEdge, numOfVertex, numOfEdge);
    adjMatrix<char> adjMatSample;
    adjList<char> adjListSample, adjListSample1;
    CreateAdjMatrix<char>(adjMatSample, infoOfVertex2, infoOfEdge2, numOfVertex2, numOfEdge2, isDirectGraph2);
    cout << "print the adjancent matrix in the following line: \n";
    PrintAdjMatrix<char>(adjMatSample);
    Matrix2List(adjMatSample, adjListSample);
    cout << "\n"
         << "After transfer to the adjancent list, the list is; \n";
    PrintAdjList(adjListSample);

    CreateAdjList<char>(adjListSample, infoOfVertex2, infoOfEdge2, numOfVertex2, numOfEdge2, !isDirectGraph2);
    cout << "\n"
         << "print the adjancent list in the following line: \n";
    PrintAdjList<char>(adjListSample);
    List2Matrix<char>(adjMatSample, adjListSample);
    cout << "\n"
         << "After transfer to the adjancent matrix, the list is; \n";
    PrintAdjMatrix(adjMatSample);

    cout << "\n"
         << "Print the reverse of the last adj list: \n";
    ReverseAdjList<char>(adjListSample1, adjListSample);
    PrintAdjList<char>(adjListSample1);

    cout << "\n"
         << "\n"
         << "also use the sample to test the funcion for calculating the output degree: \n"
         << "We change the graph as a directed graph\n";
    adjMatrixGraph<char> graphSample(infoOfVertex2, numOfVertex2, numOfEdge2, !isDirectGraph2);
    for (int i = 0; i != numOfEdge2; i++)
        graphSample.InsertEdge(infoOfEdge2[i][0], infoOfEdge2[i][1], infoOfEdge2[i][2]);
    cout << "The number of the 0 output degree is: " << CalZero<char>(graphSample) << "\n";

    cout << "\n"
         << "Begin to test the no recrusive DFS algorithm of the graph implement by adjancy list: \n"
         << "The sample we use is the above sample which is to test the recursive BFS and DFS.\n";
    adjListGraph<char> graphSample1(listg);
    cout << "The result of no recursive DFS is: ";
    graphSample1.NoRecursiveDFS(0);
    cout << "\n"
         << "As a comparison, The result of recursive DFS is: ";
    graphSample1.DFS(0);

    cout << "\n"
         << "Begin to test the BFS and DFS routine search from i to j. The sample we use is descirbed as followed: \n";

    const int numOfVertex3 = 6, numOfEdge3 = 9;
    bool isDirectGraph3 = true;
    int infoOfVertex3[numOfVertex3] = {0, 1, 2, 3, 4, 5};
    int infoOfEdge3[numOfEdge3][3] = {{0, 1, 1},
                                      {0, 2, 1},
                                      {1, 2, 1},
                                      {1, 3, 1},
                                      {1, 4, 1},
                                      {2, 4, 1},
                                      {3, 4, 1},
                                      {3, 5, 1},
                                      {4, 5, 1}};
    adjListGraph<int> graphSample2(infoOfVertex3, numOfVertex3, numOfEdge3, isDirectGraph3);
    PrintGraphInfo<int>(graphSample2, infoOfVertex3, infoOfEdge3, numOfVertex3, numOfEdge3);

    const int numOfPairs = 4;
    int startEnd[numOfPairs][2] = {{0, 5}, {0, 3}, {2, 3}, {3, 0}};
    cout << "Test of DFS: \n";
    for (int i = 0; i != numOfPairs; i++)
    {
        cout << "search path: " << startEnd[i][0] << "->" << startEnd[i][1] << " ";
        graphSample2.RoutineDFS(startEnd[i][0], startEnd[i][1]);
        cout << "\n";
    }
    cout << "Test of BFS: \n";
    for (int i = 0; i != numOfPairs; i++)
    {
        cout << "search path: " << startEnd[i][0] << "->" << startEnd[i][1] << " ";
        graphSample2.RoutineBFS(startEnd[i][0], startEnd[i][1]);
        cout << "\n";
    }

    cout << "\n";
    system("pause");
}