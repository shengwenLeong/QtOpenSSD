#ifndef OPENSSD_H_INCLUDED
#define OPENSSD_H_INCLUDED
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define SortSize 1000

class sortclass{
    public:
        int index;
        int data;
    public:
        sortclass(){
           int index =-1;
           int data=-1;
        }

        sortclass(int index,int data){
            this->index=index;
            this->data=data;
        }

};

int partialSort(unsigned char *arr,unsigned char *index);
void binprint(unsigned char *buf, int len, int width);
vector<sortclass> Vector_print(unsigned char *buf, int len, int width);
vector<sortclass> ReturnVectorSort(unsigned char *arr,unsigned char *index);

#endif // OPENSSD_H_INCLUDED
