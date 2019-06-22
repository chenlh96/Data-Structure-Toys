#include "Header/applicationOfGraph.h"
#include "Header/search.h"

// 1. 拓扑排序算法TopSort的实现：课本p175页

// 2. TSP问题：实验书p225
// 3. 哈密顿路径：实验书p226
// 4.  AOE网与关键路径：课本p179

// 5. 农夫过河：实验书p228
// https://blog.csdn.net/u011889952/article/details/44805069
// 6. 医院选址：实验书p229

int main()
{
    cout << "Begin to test the topologicla sort algoriton implement by DFS: \n"
         << "Construct the sample: \n";
    const int numOfVertex = 6, numOfEdge = 8;
    int vertex[numOfVertex] = {1, 2, 3, 4, 5, 6};
    int edge[numOfEdge][2] = {{0, 1},
                              {0, 2},
                              {0, 3},
                              {2, 1},
                              {2, 4},
                              {3, 4},
                              {5, 3},
                              {5, 4}};
    directAcyclicGraph<int> aovnSample(vertex, numOfVertex, numOfEdge);

    cout << "The vertexes has: ";
    for (int i = 0; i != numOfVertex; i++)
        cout << vertex[i] << " ";
    cout << "\n";
    for (int i = 0; i != numOfEdge; i++)
    {
        cout << "Insert edge: " << vertex[edge[i][0]] << " to " << vertex[edge[i][1]] << "\n";
        aovnSample.InsertNoWeightEdge(edge[i][0], edge[i][1]);
    }

    int topoOrder[numOfVertex];
    cout << "The Topological order of the AOV network is: ";
    TopologicalSort<int>(aovnSample, topoOrder);

    cout << "\n"
         << "Begin to test the TSP problem solved by greedy algorithm.\n"
         << "Construct an adjancy matrix: \n";
    const int numOfVertex1 = 5, numOfEdge1 = 10;
    bool isDirect = false;
    char vertex1[numOfVertex1] = {'a', 'b', 'c', 'd', 'e'};
    int edge1[numOfEdge1][3] = {{0, 1, 3},
                                {0, 2, 1},
                                {0, 3, 5},
                                {0, 4, 8},
                                {1, 2, 6},
                                {1, 3, 7},
                                {1, 4, 9},
                                {2, 3, 4},
                                {2, 4, 2},
                                {3, 4, 3}};

    adjMatrix<char> tspSample;
    CreateAdjMatrix<char>(tspSample, vertex1, edge1, numOfVertex1, numOfEdge1, isDirect);
    PrintAdjMatrix<char>(tspSample);
    char path[numOfVertex1];
    int start = 0;
    Greedy4TSP<char>(tspSample, start, path);
    cout << "Start from " << tspSample.vertex[start] << " a greedy search solution is: ";
    for (int i = 0; i != tspSample.numOfVertex; i++)
        cout << path[i] << "->";
    cout << path[0];

    cout << "\n"
         << "Begin to test the Hamilton loop solver.\n"
         << "Construct a graph and implement it by both adjMatrixGraph and adjListGraph.\n";
    const int numOfVertex2 = 6, numOfEdge2 = 9;
    bool isDirect2 = true;
    char vertex2[numOfVertex2] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int edge2[numOfEdge2][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 5}, {2, 3}, {2, 4}, {3, 1}, {4, 5}};

    adjMatrixGraph<char> hamiltonSample(vertex2, numOfVertex2, numOfEdge2, isDirect2);
    cout << "The vertexes has: ";
    for (int i = 0; i != numOfVertex2; i++)
        cout << vertex2[i] << " ";
    cout << "\n";
    for (int i = 0; i != numOfEdge2; i++)
    {
        cout << "Insert edge: " << vertex2[edge2[i][0]] << " to " << vertex2[edge2[i][1]] << "\n";
        hamiltonSample.InsertNoWeightEdge(edge2[i][0], edge2[i][1]);
    }

    char loop[numOfVertex2];
    HamiltonPath<char>(hamiltonSample, 0, loop);
    cout << "The result of graph implement by adj matrix is: ";
    for (int i = 0; i != numOfVertex2 - 1; i++)
        cout << loop[i] << "->";
    cout << loop[numOfVertex2 - 1];

    cout << "\n"
         << "\n"
         << "Begin to test the citical path: ";
    const int numOfVertex3 = 9, numOfEdge3 = 11;
    int vertex3[numOfVertex3] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int edge3[numOfEdge3][3] =
        {{0, 1, 6},
         {0, 2, 4},
         {0, 3, 5},
         {1, 4, 1},
         {2, 4, 1},
         {3, 5, 2},
         {4, 6, 9},
         {4, 7, 7},
         {5, 7, 4},
         {6, 8, 2},
         {7, 8, 4}};
    directAcyclicGraph<int> aovnSample1(vertex3, numOfVertex3, numOfEdge3);
    cout << "The vertexes has: ";
    for (int i = 0; i != numOfVertex3; i++)
        cout << vertex3[i] << " ";
    cout << "\n";
    for (int i = 0; i != numOfEdge3; i++)
    {
        cout << "Insert edge: " << vertex3[edge3[i][0]] << " to " << vertex3[edge3[i][1]] << " with weight: " << edge3[i][2] << "\n";
        aovnSample1.InsertEdge(edge3[i][0], edge3[i][1], edge3[i][2]);
    }
    cout << "Start to search critical path: \n";
    CriticalPath<int>(aovnSample1);

    cout << "\n"
         << "Begin to test the algorithm to select the hospital: the sample we use is printed as follows: \n";
    const int numOfVertex4 = 5, numOfEdge4 = 10;
    bool isDirect4 = false;
    int vertex4[numOfVertex4] = {1, 2, 3, 4, 5};
    int edge4[numOfEdge4][3] = {{0, 1, 3},
                                {0, 2, 1},
                                {0, 3, 5},
                                {0, 4, 8},
                                {1, 2, 6},
                                {1, 3, 7},
                                {1, 4, 9},
                                {2, 3, 4},
                                {2, 4, 2},
                                {3, 4, 3}};
    adjMatrixGraph<int> village(vertex4, numOfVertex4, numOfEdge4, isDirect4);
    cout << "Vertex: ";
    for (int i = 0; i != numOfVertex4; i++)
        cout << vertex4[i] << " ";
    cout << "\n";
    for (int i = 0; i != numOfEdge4; i++)
    {
        cout << "Edge: " << edge4[i][0] << "->" << edge4[i][1] << " weight: " << edge4[i][2] << "\n";
        village.InsertEdge(edge4[i][0], edge4[i][1], edge4[i][2]);
    }
    int point = SelectHospitalPoint(village);
    cout << "The hospital point: " << vertex4[point] << "\n";

    cout << "\n"
         << "Begin to test the binary sort tree: \n";
    const int numofRecords = 10;
    int record[numofRecords] = {63, 55, 90, 42, 58, 70, 10, 45, 67, 83}, record1[numofRecords];
    bool isRdInsert = false;
    cout << "The records has: ";
    for (int i = 0; i != numofRecords; i++)
    {
        cout << record[i] << " ";
        record1[i] = record[i];
    }
    cout << "\n"
         << "Construct a binary sort tree and select the record by ascending order \n";
    binarySortTree bstSample(record, numofRecords, isRdInsert);
    cout << "Construct a binary sort tree and select the record by random order \n";
    binarySortTree bstSample1(record, numofRecords, !isRdInsert);

    cout << "Begin search for the element in both tree.\n";
    const int numOfSearch = 4;
    int searchRecord[numOfSearch] = {4, 6, 9, 3}, count;
    cout << "record ascending random\n";
    for (int i = 0; i != numOfSearch; i++)
    {
        cout << record1[searchRecord[i]] << "   ";
        bstSample.Search(record1[searchRecord[i]], count);
        cout << count << "   ";
        bstSample1.Search(record1[searchRecord[i]], count);
        cout << count << "   \n";
    }

    cout << "For each record, the compare counts using the random generate bst is: \n";
    int max = INT16_MIN, min = INT16_MAX, mean = 0;
    for (int i = 0; i != numofRecords; i++)
    {
        bstSample1.Search(record1[i], count);
        if (count > max)
            max = count;
        else if (count < min)
            min = count;
        mean += count;
        cout << count << " ";
    }
    mean /= numofRecords;
    cout << "\n"
         << "The best condition is: " << min << " The wost condition is: " << max << " And the mean condition is: " << mean << "\n";

    cout << "\n"
         << "Begin to test the sequential and binary search.\n";
    const int numOfRecords1 = numofRecords;
    int record1_seq[numOfRecords1], record1_bin[numOfRecords1] = {7, 13, 21, 22, 39, 45, 61, 82, 87, 92};
    for (int i = 1; i != numOfRecords1 + 1; i++)
        record1_seq[i] = record1[i - 1];

    cout << "The record that uesd to test the seq search: ";
    for (int i = 1; i != numOfRecords1 + 1; i++)
        cout << record1_seq[i] << " ";
    cout << "\n"
         << "The record that uesd to test the binary search: ";
    for (int i = 0; i != numOfRecords1; i++)
        cout << record1_bin[i] << " ";
    int count1 = 0, index1;
    cout << "\n"
         << "Sequential locate count Binary locate count\n";
    for (int i = 0; i != numOfSearch; i++)
    {
        index1 = SeqSearch(record1_seq, numOfRecords1, record1_seq[searchRecord[i]], count1);
        cout << record1_seq[searchRecord[i]] << "    " << index1 << "     " << count1 << "    ";
        index1 = BinarySearch(record1_bin, numOfRecords1, record1_bin[searchRecord[i]], count1);
        cout << record1_bin[searchRecord[i]] << "    " << index1 << "     " << count1 << "    \n";
    }

    FarmerCrossRiver();

    cout << "\n";
    system("pause");
}