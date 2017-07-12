#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTextBrowser>

#include "OpenSSD.h"
using namespace std;

bool compare(sortclass & m1, sortclass & m2){
    return m1.data >= m2.data;

}


void binprint(unsigned char *buf, int len, int width)
{
  int i,j, offset = 0;
  printf("     ");
  unsigned char result_max[20];
  unsigned char result[1024];
  unsigned char Fc8result[1024];
  for (i = 1424; i < 2448; i++) {
    /*if(i%16 == 0)
      printf( "\n");
    printf( " %02x", buf[i]);*/
    result[i-1424] = buf[i];
  }
  for(i =0; i<1024;i+=16){
    for(j=0;j<16;j++)
    {
      Fc8result[i+j]  = result[15+i-j];
    }
  }
  for (i = 0; i < 1024; i++) {
    if(i%16 == 0)
      printf( "\n");
    printf( " %02x", Fc8result[i]);
  }

  printf( "\n");
  partialSort(Fc8result,result_max);
  printf( "\n");
  for (i = 0; i < 20; i++) {
    if(i%16 == 0)
      printf( "\n");
    printf( " %d", result_max[i]);
  }
}
int partialSort(unsigned char *arr,unsigned char *index){ // soft sort function
    std::vector<sortclass> s;
    std::vector<sortclass> result;
    for(int i=0;i<SortSize;i++){
        sortclass my(i,arr[i]);
        s.push_back(my);
    }
    partial_sort(s.begin(),s.begin()+5,s.end(),compare);
    for(int i =0;i<5;i++)
    {
        result.push_back(s[i]);
    }
    cout<<"result:";
    for(int i=0;i<5;i++) printf("(%3d,%02x) ", s[i].index,s[i].data);
    cout<<endl;
    for(int i=0;i<5;i++){
            *(index+i*4)=(s[i].index%1000)/100+'0';
            *(index+i*4+1)=(s[i].index%100)/10+'0';
            *(index+i*4+2)=s[i].index%10+'0';
            *(index+i*4+3)=' ';
    }
    return 0;
}

vector<sortclass> Vector_print(unsigned char *buf, int len, int width)
{
  int i,j, offset = 0;
  printf("     ");
  unsigned char result_max[20];
  unsigned char result[1024];
  unsigned char Fc8result[1024];
  for (i = 1424; i < 2448; i++) {
    /*if(i%16 == 0)
      printf( "\n");
    printf( " %02x", buf[i]);*/
    result[i-1424] = buf[i];
  }
  for(i =0; i<1024;i+=16){
    for(j=0;j<16;j++)
    {
      Fc8result[i+j]  = result[15+i-j];
    }
  }
  for (i = 0; i < 1024; i++) {
    if(i%16 == 0)
      printf( "\n");
    printf( " %02x", Fc8result[i]);
  }

  printf( "\n");
  std::vector<sortclass> results;
  results = ReturnVectorSort(Fc8result,result_max);
  printf( "\n");
  for (i = 0; i < 20; i++) {
    if(i%16 == 0)
      printf( "\n");
    printf( " %d", result_max[i]);
  }
  return results;
}


vector<sortclass> ReturnVectorSort(unsigned char *arr,unsigned char *index){ // soft sort function
    std::vector<sortclass> s;
    std::vector<sortclass> result;
    for(int i=0;i<SortSize;i++){
        sortclass my(i,arr[i]);
        s.push_back(my);
    }
    partial_sort(s.begin(),s.begin()+15,s.end(),compare);
    for(int i =0;i<15;i++)
    {
        result.push_back(s[i]);
    }
    cout<<"result:";
    for(int i=0;i<5;i++) printf("(%3d,%02x) ", s[i].index,s[i].data);
    cout<<endl;
    for(int i=0;i<5;i++){
            *(index+i*4)=(s[i].index%1000)/100+'0';
            *(index+i*4+1)=(s[i].index%100)/10+'0';
            *(index+i*4+2)=s[i].index%10+'0';
            *(index+i*4+3)=' ';
    }
    return result;
}

