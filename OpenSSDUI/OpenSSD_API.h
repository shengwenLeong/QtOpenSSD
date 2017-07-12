#ifndef OPENSSD_API_H_INCLUDED
#define OPENSSD_API_H_INCLUDED
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "OpenSSD_API.h"
#include "OpenSSD.h"
using namespace std;
extern "C"
{
    #include "nvme_low_lib.h"
}
int Run_OpenSSD(char *device, char *weight_file_path, char *image_file_path,int image_flag);
int move_weight_data(const char *dev , const char *weight_file_path);
int run_weight_data(const char *dev , const char *weight_file_path);
int run_image_data(const char *device , const char *image_file_path);
vector<sortclass> run_image_result(const char *dev , const char *image_file_path);
int test_weight_copy(unsigned char *buf, int len, int width);
void bin_print(unsigned char *buf, int len, int width);
#endif // OPENSSD_API_H_INCLUDED
