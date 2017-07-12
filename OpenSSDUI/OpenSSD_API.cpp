#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "OpenSSD_API.h"
#include "OpenSSD.h"
using namespace std;
extern "C"
{
    #include "nvme_low_lib.h"
}

int Run_OpenSSD(char *device, char *weight_file_path, char *image_file_path,int image_flag) {

  // read weight_file blocks from ssd
  int flag = 0;
  if(image_flag)
  {
    printf("\n------run image process task-----\n");
    run_image_data(device,image_file_path);
    return 0;
  }
  else
  {
    flag = move_weight_data(device,weight_file_path);
  }

  return flag;
}


int move_weight_data(const char *dev , const char *weight_file_path)
{
  nvme_cmd command;
  nvme_data data;
  nvme_error err;
  nvme_handle device;
  uint8_t *dptr;
  int i,fd,ret,blocks_count;
  int physic_blocks_id;
  int flag;

  err = nvme_open(&device, dev);
  if (err) {
    printf("Error0: %d - %s\n", err, nvme_get_error_message(err));
    goto clean;
  }
  // read weight_file blocks from ssd
  i = 0;
  fd = open(weight_file_path,O_RDONLY);
  if(fd<0)
  {
    return 1;
  }
  struct stat buf;
  ret = fstat(fd,&buf);
  blocks_count = buf.st_blocks/8;
  printf("-----%d -----\n",blocks_count);
  physic_blocks_id = 0;
  ret = ioctl(fd , FIBMAP , &physic_blocks_id);
  physic_blocks_id +=256;
  printf("-----%d \t %d-----\n",i,physic_blocks_id);
  close(fd);
  //end read file blocks


  // Setting command
  memset(&command, 0, sizeof(nvme_cmd));
  command.cdw0 = 0x0000000A;                  // Identify
  command.cdw10 = physic_blocks_id;          // Identify controller
  //command.cdw12 = 0x000003CB;
  command.cdw14 = blocks_count;
  command.cdw13 = 0x20000000;
  //command.cdw13 = 0x203A4C00;

  // Allocate data pointer
  err = nvme_alloc_data(&data, 8192);
  if (err) {
    printf("Error1: %d - %s\n", err, nvme_get_error_message(err));
    goto clean;
  }
  // Send command
  err = nvme_submit_io(device, &command, NULL, data);
  if (err) {
    printf("Error2: %d - %s\n", err, nvme_get_error_message(err));
    goto free_and_clean;
  }
  // Get data pointer
  err = nvme_get_data_pointer(data, (void **)&dptr);
  if (err) {
    printf("Error3: %d - %s\n", err, nvme_get_error_message(err));
    goto free_and_clean;
  }
  //Print result
  //binary_print((char *)dptr, 8192, 16);

  flag = test_weight_copy((unsigned char *)dptr, 8192, 16);
  if(flag == 1)
  {
    printf("\n-------weight_map_successful------\n");
    return 1;
  }
  else{
    printf("\n-------weight_map_error and please try again------\n");
    return 0;
  }

  // Close device
  nvme_close(device);
free_and_clean:
  nvme_free_data(data);
  clean:
  if(flag == 1)
  {
    return 1;
  }
  else{
    printf("\n-------weight_map_error------\n");
    return 0;
  }


}

int run_weight_data(const char *dev , const char *weight_file_path)
{
  nvme_cmd command;
  nvme_data data;
  nvme_error err;
  nvme_handle device;
  uint8_t *dptr;
  int i,fd,ret,blocks_count;
  int physic_blocks_id;
  int flag;

  err = nvme_open(&device, dev);
  if (err) {
    printf("Error0: %d - %s\n", err, nvme_get_error_message(err));
    goto clean;
  }
  // read weight_file blocks from ssd
  i = 0;
  fd = open(weight_file_path,O_RDONLY);
  if(fd<0)
  {
    return 1;
  }
  struct stat buf;
  ret = fstat(fd,&buf);
  blocks_count = buf.st_blocks/8;
  printf("-----%d -----\n",blocks_count);
  physic_blocks_id = 0;
  ret = ioctl(fd , FIBMAP , &physic_blocks_id);
  physic_blocks_id +=256;
  printf("-----%d \t %d-----\n",i,physic_blocks_id);
  close(fd);
  //end read file blocks


  // Setting command
  memset(&command, 0, sizeof(nvme_cmd));
  command.cdw0 = 0x00000010;                  // Identify
  command.cdw10 = physic_blocks_id;          // Identify controller
  //command.cdw12 = 0x000003CB;
  command.cdw14 = blocks_count;
  command.cdw13 = 0x20000000;
  //command.cdw13 = 0x203A4C00;

  // Allocate data pointer
  err = nvme_alloc_data(&data, 8192);
  if (err) {
    printf("Error1: %d - %s\n", err, nvme_get_error_message(err));
    goto clean;
  }
  // Send command
  err = nvme_submit_io(device, &command, NULL, data);
  if (err) {
    printf("Error2: %d - %s\n", err, nvme_get_error_message(err));
    goto free_and_clean;
  }

  // Get data pointer
  err = nvme_get_data_pointer(data, (void **)&dptr);
  if (err) {
    printf("Error3: %d - %s\n", err, nvme_get_error_message(err));
    goto free_and_clean;
  }
  //Print result
  //binary_print((char *)dptr, 8192, 16);

  flag = test_weight_copy((unsigned char *)dptr, 8192, 16);
  if(flag == 1)
  {
    printf("\n-------weight_map_successful------\n");
    return 1;
  }
  else{
    printf("\n-------weight_map_error and please try again------\n");
    return 0;
  }

  // Close device
  nvme_close(device);
free_and_clean:
  nvme_free_data(data);
  clean:
  if(flag == 1)
  {
    return 1;
  }
  else{
    printf("\n-------weight_map_error------\n");
    return 0;
  }


}




int run_image_data(const char *dev, const char *image_file_path)
{
  nvme_cmd command;
  nvme_data data;
  nvme_error err;
  nvme_handle device;
  uint8_t *dptr;
  int i,fd,ret,blocks_count;
  int physic_blocks_id;
  int flag;
  err = nvme_open(&device, dev);
  if (err) {
    printf("Error0: %d - %s\n", err, nvme_get_error_message(err));
    goto clean;
  }
  // read weight_file blocks from ssd
  i = 0;
  fd = open(image_file_path,O_RDONLY);
  if(fd<0)
  {
    return 1;
  }
  struct stat buf;
  ret = fstat(fd,&buf);
  blocks_count = buf.st_blocks/8;
  printf("-----%d -----\n",blocks_count);
  physic_blocks_id = 0;
  ret = ioctl(fd , FIBMAP , &physic_blocks_id);
  physic_blocks_id +=256;
  printf("-----%d \t %d-----\n",i,physic_blocks_id);
  close(fd);
  //end read file blocks


  // Setting command
  memset(&command, 0, sizeof(nvme_cmd));
  command.cdw0 = 0x0000000A;                  // Identify
  command.cdw10 = physic_blocks_id;          // Identify controller
  //command.cdw12 = 0x000003CB;
  command.cdw14 = blocks_count;
  //command.cdw13 = 0x20000000;
  command.cdw13 = 0x203A4C00;

  // Allocate data pointer
  err = nvme_alloc_data(&data, 8192);
  if (err) {
    printf("Error1: %d - %s\n", err, nvme_get_error_message(err));
    goto clean;
  }
  // Send command
  err = nvme_submit_io(device, &command, NULL, data);
  if (err) {
    printf("Error2: %d - %s\n", err, nvme_get_error_message(err));
    goto free_and_clean;
  }

  // Get data pointer
  err = nvme_get_data_pointer(data, (void **)&dptr);
  if (err) {
    printf("Error3: %d - %s\n", err, nvme_get_error_message(err));
    goto free_and_clean;
  }
  //Print result
  //binary_print((char *)dptr, 8192, 16);

  bin_print((unsigned char *)dptr, 8192, 16);


  // Close device
  nvme_close(device);
free_and_clean:
  nvme_free_data(data);
  clean:
    return 0;


}


int test_weight_copy(unsigned char *buf, int len, int width)
{
  int i,j, offset = 0;
  printf("     ");
  char right_result[16] = {0x00,0x00,0x00,0x03,0x02,0x04,0x03,0x00,0x01,0x03,0x00,0x02,0x00,0x01,0x00,0x03};
  char result[16];
  for (i = 1424; i < 1440; i++) {
    result[i-1424] = buf[i];
  }
  for(i=0;i<16;i++)
  {
    if(right_result[i] != result[i])
    {
        return 0;
    }
  }
  return 1;
}
void bin_print(unsigned char *buf, int len, int width)
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
  for (i = 0; i < 200; i++) {
    if(i%16 == 0)
      printf( "\n");
    printf( " %02x", Fc8result[i]);
  }

  printf( "\n");
  partialSort(Fc8result,result_max);
  printf( "\n");
  for (i = 0; i < 20; i++) {
    printf( " %d", result_max[i]);
  }
  printf( "\n-------finish---------\n");
}

vector<sortclass> run_image_result(const char *dev , const char *image_file_path)
{
      nvme_cmd command;
      nvme_data data;
      nvme_error err;
      nvme_handle device;
      uint8_t *dptr;
      int i,fd,ret,blocks_count;
      int physic_blocks_id;
      int flag;
      err = nvme_open(&device, dev);
      if (err) {
        printf("Error0: %d - %s\n", err, nvme_get_error_message(err));
        //goto clean;
      }
      // read weight_file blocks from ssd
      i = 0;
      fd = open(image_file_path,O_RDONLY);
      if(fd<0)
      {
        //return 0;
      }
      struct stat buf;
      ret = fstat(fd,&buf);
      blocks_count = buf.st_blocks/8;
      printf("-----%d -----\n",blocks_count);
      physic_blocks_id = 0;
      ret = ioctl(fd , FIBMAP , &physic_blocks_id);
      physic_blocks_id +=256;
      printf("-----%d \t %d-----\n",i,physic_blocks_id);
      close(fd);
      //end read file blocks


      // Setting command
      memset(&command, 0, sizeof(nvme_cmd));
      command.cdw0 = 0x00000010;                  // Identify
      command.cdw10 = physic_blocks_id;          // Identify controller
      //command.cdw12 = 0x000003CB;
      command.cdw14 = blocks_count;
      //command.cdw13 = 0x20000000;
      command.cdw13 = 0x203A4C00;

      // Allocate data pointer
      err = nvme_alloc_data(&data, 8192);
      if (err) {
        printf("Error1: %d - %s\n", err, nvme_get_error_message(err));
        //goto clean;
      }
      // Send command
      err = nvme_submit_io(device, &command, NULL, data);
      if (err) {
        printf("Error2: %d - %s\n", err, nvme_get_error_message(err));
        //goto free_and_clean;
      }

      // Get data pointer
      err = nvme_get_data_pointer(data, (void **)&dptr);
      if (err) {
        printf("Error3: %d - %s\n", err, nvme_get_error_message(err));
        //goto free_and_clean;
      }
      //Print result
      //binary_print((char *)dptr, 8192, 16);
      std::vector<sortclass> result;
      result = Vector_print((unsigned char *)dptr, 8192, 16);

      //return result;
      // Close device
      nvme_close(device);

      nvme_free_data(data);
      return result;
}

