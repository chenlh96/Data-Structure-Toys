#ifndef APPLICATIONOFSORT_H
#define APPLICATIONOFSORT_H
#include "sort.h"

#define MAX_NUM_OF_JOB 100
#define MAX_NUM_OF_MACHINE 100

struct machine
{
    int ID, spareTime, jobOrder[MAX_NUM_OF_JOB], numOfJob;
};

struct job
{
    int ID, time;
};

bool operator<(const job &ljob, const job &rjob)
{
    return ljob.time < rjob.time;
}
bool operator==(const job &ljob, const job &rjob)
{
    return ljob.time == rjob.time;
}
bool operator<=(const job &ljob, const job &rjob)
{
    return ljob < rjob || ljob == rjob;
}
bool operator>(const job &ljob, const job &rjob)
{
    return !(ljob <= rjob);
}
bool operator>=(const job &ljob, const job &rjob)
{
    return !(ljob < rjob);
}

bool operator<(const machine &lmachine, const machine &rmachine)
{
    return lmachine.spareTime < rmachine.spareTime;
}
bool operator==(const machine &lmachine, const machine &rmachine)
{
    return lmachine.spareTime == rmachine.spareTime;
}
bool operator<=(const machine &lmachine, const machine &rmachine)
{
    return lmachine < rmachine || lmachine == rmachine;
}
bool operator>(const machine &lmachine, const machine &rmachine)
{
    return !(lmachine <= rmachine);
}
bool operator>=(const machine &lmachine, const machine &rmachine)
{
    return !(lmachine < rmachine);
}

template <class T>
void BigSift(T arr[], int key, int bound)
{
    int i = key, j = 2 * i + 1;
    while (j <= bound)
    {
        if (j < bound && arr[j] < arr[j + 1])
            j++;
        if (arr[i] > arr[j])
            break;
        else
        {
            T tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i = j, j = 2 * i;
        }
    }
}
template <class T>
void SmallSift(T arr[], int key, int bound)
{
    int i = key, j = 2 * i + 1;
    while (j <= bound)
    {
        if (j < bound && arr[j] > arr[j + 1])
            j++;
        if (arr[i] < arr[j])
            break;
        else
        {
            T tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i = j, j = 2 * i;
        }
    }
}

int LPT(int jobTimeUse[], int numOfJob, int numOfMachine)
{
    job jobList[MAX_NUM_OF_JOB];
    machine machineList[MAX_NUM_OF_MACHINE];

    for (int i = 0; i != numOfJob; i++)
    {
        jobList[i].ID = i;
        jobList[i].time = jobTimeUse[i];
    }
    for (int i = 0; i != numOfMachine; i++)
    {
        machineList[i].ID = i;
        machineList[i].spareTime = 0;
        machineList[i].numOfJob = 0;
    }

    for (int i = numOfJob / 2 - 1; i != -1; i--)
        BigSift<job>(jobList, i, numOfJob - 1);

    for (int i = 0; i != numOfJob; i++)
    {
        BigSift<job>(jobList, i, numOfJob - 1);
        SmallSift<machine>(machineList, 0, numOfMachine - 1);
        machineList[0].spareTime += jobList[i].time;
        machineList[0].jobOrder[machineList[0].numOfJob++] = jobList[i].ID;
    }
    int maxIdx = 0;
    for (int i = 0; i != numOfMachine; i++)
    {
        if (machineList[i].spareTime > machineList[maxIdx].spareTime)
            maxIdx = i;
    }
    return machineList[maxIdx].spareTime;
}

#endif // !APPLICATIONOFSORT_H