#ifndef APPLICATIONOFGRAPH_H
#define APPLICATIONOFGRAPH_H
#include "graph.h"
#include <string>

template <class T>
void TopologicalSort(directAcyclicGraph<T> aovn, T order[])
{
    LinkStack<int> orderStack;
    int count = 0;
    for (int i = 0; i != aovn.numOfVertex; i++)
    {
        if (aovn.vertexList[i].inDegree == 0)
            orderStack.Push(i);
    }
    while (!orderStack.IsEmpty())
    {
        int curr = orderStack.Pop();
        order[count++] = aovn.vertexList[curr].vertex;
        arcNode *a = aovn.vertexList[curr].headEdge;
        while (a != NULL)
        {
            if ((--aovn.vertexList[a->vertexIdx].inDegree) == 0)
                orderStack.Push(a->vertexIdx);
            a = a->next;
        }
    }

    if (count < aovn.numOfVertex)
        cout << "Cyclic exists";
    else
    {
        for (int i = 0; i != aovn.numOfVertex; i++)
            cout << order[i] << " ";
    }
}

template <class T>
void CriticalPath(directAcyclicGraph<T> aovn)
{
    int activityEarliest[maxNumOfVertex][maxNumOfVertex],
        activityLatest[maxNumOfVertex][maxNumOfVertex];
    int eventEarliest[maxNumOfVertex], eventLatest[maxNumOfVertex];
    for (int i = 0; i != aovn.numOfVertex; i++)
    {
        eventEarliest[i] = 0;
        eventLatest[i] = INT16_MAX;
        for (int j = 0; j != aovn.numOfVertex; j++)
        {
            activityEarliest[i][j] = activityLatest[i][j] = -1;
        }
    }

    // calculate the earliest finish time of event(vertex)
    LinkStack<int> orderStack;
    int topoOrder[maxNumOfVertex], count = 0;
    for (int i = 0; i != aovn.numOfVertex; i++)
    {
        if (aovn.vertexList[i].inDegree == 0)
        {
            orderStack.Push(i);
            topoOrder[count++] = i;
            eventEarliest[i] = 0;
        }
    }
    while (!orderStack.IsEmpty())
    {
        int curr = orderStack.Pop();
        arcNode *a = aovn.vertexList[curr].headEdge;
        while (a != NULL)
        {
            if ((--aovn.vertexList[a->vertexIdx].inDegree) == 0)
            {
                orderStack.Push(a->vertexIdx);
                topoOrder[count++] = a->vertexIdx;
            }
            if (eventEarliest[curr] + a->weight > eventEarliest[a->vertexIdx])
                eventEarliest[a->vertexIdx] = eventEarliest[curr] + a->weight;
            a = a->next;
        }
    }

    int curr1 = topoOrder[--count];
    eventLatest[curr1] = eventEarliest[curr1];
    while (count != 0)
    {
        curr1 = topoOrder[--count];
        arcNode *a = aovn.vertexList[curr1].headEdge;
        while (a != NULL)
        {
            if (eventLatest[curr1] > eventLatest[a->vertexIdx] - a->weight)
                eventLatest[curr1] = eventLatest[a->vertexIdx] - a->weight;
            a = a->next;
        }
    }

    for (int i = 0; i != aovn.numOfVertex; i++)
    {
        arcNode *a = aovn.vertexList[i].headEdge;
        while (a != NULL)
        {
            activityEarliest[i][a->vertexIdx] = eventEarliest[i];
            activityLatest[i][a->vertexIdx] = eventLatest[a->vertexIdx] - a->weight;
            a = a->next;
        }
    }

    int activity[maxNumOfEdges][2], count1 = 0;
    for (int i = 0; i != aovn.numOfVertex; i++)
    {
        for (int j = 0; j != aovn.numOfVertex; j++)
        {
            if (activityEarliest[i][j] == activityLatest[i][j] && activityEarliest[i][j] >= 0)
            {
                activity[count1][0] = i;
                activity[count1][1] = j;
                count1++;
                cout << i << "->" << j << " ";
                if (count1 % 10 == 0)
                    cout << "\n";
            }
        }
    }
}

template <class T>
void Greedy4TSP(adjMatrix<T> map, int start, T solution[])
{
    int visit[maxNumOfVertex], idx = start, min, minIdx;
    for (int i = 0; i != map.numOfVertex; i++)
        visit[i] = 0;
    solution[0] = map.vertex[idx];
    visit[idx] = 1;
    for (int i = 1; i != map.numOfVertex; i++)
    {
        min = INT16_MAX;
        for (int j = 0; j != map.numOfVertex; j++)
        {
            if (visit[j] == 0 && map.arc[idx][j] != 0 && map.arc[idx][j] < min)
            {
                min = map.arc[idx][j];
                minIdx = j;
            }
        }
        idx = minIdx;
        solution[i] = map.vertex[idx];
        visit[idx] = 1;
    }
}

bool IsVisitAll(bool visit[], int n)
{
    for (int i = 0; i != n; i++)
    {
        if (!visit[i])
            return false;
    }
    return true;
}

template <class T>
void HamiltonPath(adjMatrixGraph<T> graph, int v, T path[])
{
    bool visited[maxNumOfVertex];
    for (int i = 0; i != graph.numOfVertex; i++)
        visited[i] = false;
    int count = 0;
    HamiltonPathDFS(graph, v, count, visited, path);
}

template <class T>
void HamiltonPathDFS(adjMatrixGraph<T> &graph, int currIdx, int count, bool visit[], T path[])
{
    visit[currIdx] = true;
    path[count++] = graph.vertex[currIdx];
    if (IsVisitAll(visit, graph.numOfVertex))
        return;
    int i;
    for (i = 0; i != graph.numOfVertex; i++)
    {
        if (graph.arc[currIdx][i] != 0 && !visit[i])
            HamiltonPathDFS(graph, i, count, visit, path);
    }
    if (i == graph.numOfVertex)
    {
        visit[currIdx] = false;
        count--;
    }
}

int SelectHospitalPoint(adjMatrixGraph<int> villageGraph)
{
    int dist[maxNumOfVertex][maxNumOfVertex];
    for (int i = 0; i != villageGraph.numOfVertex; i++)
        for (int j = 0; j != villageGraph.numOfVertex; j++)
            dist[i][j] = villageGraph.arc[i][j];

    for (int k = 0; k != villageGraph.numOfVertex; k++)
    {
        for (int i = 0; i != villageGraph.numOfVertex; i++)
        {
            for (int j = 0; j != villageGraph.numOfVertex; j++)
            {
                if (dist[i][k] != 0 && dist[k][j] != 0 && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    int eccentricity[maxNumOfVertex], minEcce = INT16_MAX, minIdx;
    for (int i = 0; i != villageGraph.numOfVertex; i++)
    {
        eccentricity[i] = -1;
        for (int j = 0; j != villageGraph.numOfVertex; j++)
        {
            if (eccentricity[i] < dist[j][i])
                eccentricity[i] = dist[j][i];
        }
        if (minEcce > eccentricity[i])
        {
            minEcce = eccentricity[i];
            minIdx = i;
        }
    }
    return 1;
}

struct position
{
    bool faramer, wolf, lamb, cabbage;
};

ostream &operator<<(ostream &os, const position &pos)
{
    cout << "Left: ";
    if (!pos.faramer)
        cout << "Farmer ";
    if (!pos.wolf)
        cout << "wolf ";
    if (!pos.lamb)
        cout << "lamb ";
    if (!pos.cabbage)
        cout << "cabbage ";
    cout << " ------------------------- Right: ";
    if (pos.faramer)
        cout << "Farmer ";
    if (pos.wolf)
        cout << "wolf ";
    if (pos.lamb)
        cout << "lamb ";
    if (pos.cabbage)
        cout << "cabbage ";
    cout << "\n";
    return os;
}

bool IsDangerPosition(position pos)
{
    return (pos.lamb == pos.wolf && pos.faramer != pos.lamb) 
    || (pos.lamb == pos.cabbage && pos.faramer != pos.lamb);
}
bool IsLegalCrossRiver(position prev, position curr)
{
    if (prev.faramer == curr.faramer)
        return false;
    if (prev.faramer == prev.wolf && curr.faramer == curr.wolf 
    && prev.cabbage == curr.cabbage && prev.lamb == curr.lamb)
        return true;
    if (prev.faramer == prev.lamb && curr.faramer == curr.lamb 
    && prev.cabbage == curr.cabbage && prev.wolf == curr.wolf)
        return true;
    if (prev.faramer == prev.cabbage && curr.faramer == curr.cabbage 
    && prev.wolf == curr.wolf && prev.lamb == curr.lamb)
        return true;
    if (prev.wolf == curr.wolf && prev.wolf == curr.wolf 
    && prev.lamb == curr.lamb)
        return true;
    return false;
}

void FarmerCrossRiver()
{
    position state[16];
    for (int i = 0; i != 16; i++)
    {
        int tmp = i;
        state[i].faramer = tmp % 2 == 0 ? false : true;
        tmp /= 2;
        state[i].wolf = tmp % 2 == 0 ? false : true;
        tmp /= 2;
        state[i].lamb = tmp % 2 == 0 ? false : true;
        tmp /= 2;
        state[i].cabbage = tmp % 2 == 0 ? false : true;
    }

    adjListGraph<position> stateMap(state, 16, 120, true);
    for (int i = 0; i != 16; i++)
    {
        if (IsDangerPosition(state[i]))
            continue;
        for (int j = 0; j != 16; j++)
        {
            if (IsLegalCrossRiver(state[i], state[j]))
                stateMap.InsertNoWeightEdge(i, j);
        }
    }

    stateMap.RoutineDFS(0, 15);
}

#endif // !APPLICATIONOFGRAPH_H
