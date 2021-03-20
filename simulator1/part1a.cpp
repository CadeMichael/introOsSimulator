#include <cstdlib>
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

class Part1 {
    private:
        int numBlocks;
        int allocated = 0;
        int * memoryBlocks;
        int block = 0;
    public: Part1(){
        srand((unsigned) time(0));
        this->numBlocks = 11 + (rand() % 990);
        int mem[this->numBlocks]; 
        // initialize the array of "memory" 
        // all unused "memory" has int value -1 
        for (int i = 0; i < this->numBlocks; i++) {
            mem[i] = -1;
        }
        this->memoryBlocks =  mem;
        for (int j = 0; j < this->numBlocks; j++) {
            //printf("[%d]\n", this->memoryBlocks[j]);
        }
    }

    double req() {
        // block is some random chunk of memory 0 ~ all of the memory 
        this-> block = (rand() % this->numBlocks);
        // if there is more memory in block than is free return 0
        if (this->block > (this->numBlocks - this->allocated))
            return 0;
        // else return probablility that one free chunk will be part of 
        // block
        // cast to double for precise probablility 
        this->allocated += this->block;
        return (double(this->block) / (this->numBlocks - this->allocated));
    }

    int size() { 
        int block = this->block; 
        int n = block % 20; // page size is 50 so we %20 as it will yeild a min of 1 or max of 20
        return n;
    }

    double free() {
        // block is some random chunk of memory 0 ~ all of the memory 
        // if there is more memory in block than is free return 1
        // as all memory should be free 
        if (this->allocated <= 0)
            return 0;
        int currentBlock = (rand() % this->allocated);
        double prob = (double(currentBlock) / this->allocated);
        allocated -= currentBlock;
        return prob;
    }

    static void testSim(int n, Part1 test) {
        double reqProb = -1;
        while (n > 0 && reqProb != 0) { 
            reqProb = test.req();

            int f = (rand() % 5);
            while (f > 0) {
                double freeS = test.free();
                printf("%f,%f,%d \n", reqProb, freeS, test.size());
                f--;
            }
            n--;
        }
    }

};

int main() {
    Part1 test = Part1();
    //std::cout << test.req();
    //printf("testing the size() function gives %d \n",test.size());
    //std::cout << test.req();
    //std::cout << test.req();
    //printf("testing the free() function gives %d percent chance of having free space when a block is removed",int(100*test.free()));
    for (int i = 0; i < 256; i++)
        test.testSim( 256, test);
    return 0;
}
