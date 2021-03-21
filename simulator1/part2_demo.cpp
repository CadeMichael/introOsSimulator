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
    //first fit allocation algorithm 
    int allocate_process (int size, int PID, int numBlocks,int memory[], int memorySize [], int processSize[]) {
        int i;
        //checks from the start of the array for an empty block, and allocates the process on the first empty block that fits  
        for (i = 0; i < numBlocks; i++) {
            if (memory[i] == -1 && memorySize[i] >= size) {
                memory[i] = PID;
                processSize[i] = test.size();
                break;
            }
        }
        //if no empty block was found that fits the process   
        if (i >= numBlocks) {
            printf("Process was not allocated\n");
            return size;
        }
    
        printf("request at t=%d for i=%d, size(i)=%d pages, satisfied by free block of size %d\n", int(clock()), size, test.size(size), memorySize[i]);
        return 0;
    }

    //returns the degree of internal fragmentation  
    int degreeFragmentation(int numBlocks, int memory[], int memorySize[], int processSize[]) {
        int fragmentation = 0;
        for (int i = 0; i < numBlocks; i++) {
            if (memory[i] != -1){
                fragmentation += memorySize[i] - processSize[i];
            }
        }
        return fragmentation / numBlocks;
    }

    //dealocated the process by its PID
    int deallocate_process (int PID,int numBlocks, int memory[], int memorySize[], int processSize[]) {
        int i;
        for (i = 0; i < numBlocks; i++) {
            if (memory[i] == PID) {
                memory[i] = -1;
                processSize[i] = 0;
            }
        }
    
    
        return 0;
    }
    
/* this is commented out when running the part 1 file in the jupyter notebook, simply comment out the int main() 
 * in part1a and uncomment this main to see how this function works
int main()
{
    //* initialize random seed: *
    srand (time(NULL));

    // array -> memory
    int numPages = 1000 + (rand() % 99000);
    int numBlocks = numPages / 200; //how many pages, on average, are in one block?
    
    //represent the memory
    int memory[numBlocks]; //has the PID's of the processes

    int memorySize[numBlocks]; //has the size of the blocks

    int processSize[numBlocks]; //has the size of the process ruuning in its corressponding block
    

    //initializing memory
    for (int i = 0; i < numBlocks; i++) {
        memory[i] = -1;
        memorySize[i] = 64 + (rand() % 400); //each block has a randomized size in between a certain range
        processSize[i] = 0;
    }
    //list current Processes
    list<int> currentProcesses;


    int PID = 0;
    //creates new processes with a random size and allocates/deallocates them 
    for (int n = 0; n < rand() % 20; n++) {
        int numProcess = rand() % 25;
        for (int i = 0; i < numProcess; i++) {

            allocate_process(20 + rand() % 400, ++PID, numBlocks, memory, memorySize, processSize);
            currentProcesses.push_front(PID);

        }
        for (int d = 0; d < rand() % 15; d++) {
            if (!currentProcesses.empty()) {
                deallocate_process(currentProcesses.back(), numBlocks, memory, memorySize, processSize);
                currentProcesses.pop_back();
            }
        }
        cout << "Degree of Fragmentation: " << degreeFragmentation(numBlocks,memory,memorySize, processSize) << endl;

    }
    //deallocates all remaining processes 
    while (!currentProcesses.empty()) {
        deallocate_process(currentProcesses.back(), numBlocks, memory, memorySize, processSize);
        currentProcesses.pop_back();
    }

    

    return 0;

}
*/
