#include <cstdio>
#include <iostream>
#include <locale>
#include <stdio.h>      //* printf, scanf, puts, NULL *
#include <stdlib.h>     //* srand, rand *
#include <time.h>       //* time *
#include "part1a.cpp"
#include <map>
#include <list>

using namespace std;

    Part1 test = Part1();
    //first fit 
    int allocate_process (int size, int PID, int memory [], int numBlocks, int memorySize [], int processSize[]) {
        int i;
        for (i = 0; i < numBlocks; i++) {
            if (memory[i] == -1 && memorySize[i] >= size) {
                memory[i] = PID;
                processSize[i] = test.size();
                break;
            }
        }
        if (i >= numBlocks) {
            printf("Process was not allocated");
            return size;
        }
    
        printf("request at t=%d for i=%d, size(i)=%d pages, satisfied by free block of size %d", time(NULL), size, test.size(), memorySize[i]);
        return 0;
    }
    
    int degreeFragmentation(int processSize[], int numBlocks, int memory[], int memorySize[]) {
        int fragmentation = 0;
        for (int i = 0; i < numBlocks; i++) {
            if (memory[i] != -1){
                fragmentation += memorySize[i] - processSize[i];
            }
        }
        return fragmentation / numBlocks;
    }
    int deallocate_process (int PID, int processSize [],int numBlocks, int memory[], int memorySize[]) {
        int i;
        for (i = 0; i < numBlocks; i++) {
            if (memory[i] == PID) {
                memory[i] = -1;
                processSize[i] = 0;
            }
        }
    
        cout << "Degree of Fragmentation: " << degreeFragmentation(processSize,numBlocks,memory,memorySize) << endl;
    
    
        return 0;
    }
    
int main()
{
    //* initialize random seed: *
    srand (time(NULL));

    // array -> memory
    int numPages = 1000 + (rand() % 99000);
    int numBlocks = numPages / 200; //how many pages, on average, are in one block?
    int memory[numBlocks];

    int memorySize[numBlocks];

    int processSize[numBlocks];
    

    //initializing memory
    for (int i = 0; i < numBlocks; i++) {
        memory[i] = -1;
        memorySize[i] = 64 + (rand() % 400);
        processSize[i] = 0;
    }
    //list current Processes
    list<int> currentProcesses;


    int PID = 0;
    for (int n = 0; n < rand()%10; n++) {
        int numProcess = rand() % 64;
        for (int i = 0; i < numProcess; i++) {

            allocate_process(20 + rand() % 400, ++PID);
            currentProcesses.insert(PID);

        }
        for (int d = 0; d < rand() % 7; d++) {
            deallocate_process(currentProcesses.back());
            currentProcesses.pop_back();
        }

    }

    while (!currentProcesses.empty()) {
        deallocate_process(currentProcesses.back());
        currentProcesses.pop_back();
    }

    return 0;

    //request at t=1738 for i=33, size(i)=12 pages,
    //   satisfied by free block of size 32 starting at 8056 leaving 20 pages as 1x16 + 2x2
}

