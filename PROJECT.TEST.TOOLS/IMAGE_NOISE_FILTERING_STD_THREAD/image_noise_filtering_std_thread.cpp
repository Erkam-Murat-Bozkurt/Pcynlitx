
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int MAX_KERNEL_LENGTH = 31;

#define IMAGE_NUMBER 200   // DEFINES TOTAL NUMBER OF IMAGES THAT WILL BE FILTERED
#define THREAD_WORK 50     // DEFINES EACH THREAD FOR LOOP

int Elapsed_Time = 0;

cv::Mat image [IMAGE_NUMBER];

cv::Mat dst_image [IMAGE_NUMBER];

cv::Mat kernel;

void Filter_Images(int start, int end);

int main(int argc, char** argv)
{
  image[0] = cv::imread("/home/erkam/oPENCV_Applications/mountain.jpg");

  cv::Mat noise(image[0].size(),image[0].type());

  float m = (15,15,15);

  float sigma = (25,25,25);

  cv::randn(noise, m, sigma); //mean and variance

  for(int i=1;i<IMAGE_NUMBER;i++){

      image[i] = image[0];
  }

  for(int i=0;i<IMAGE_NUMBER;i++){

      image[i] = image[i] + noise;
  }

  for(int i=0;i<IMAGE_NUMBER;i++){

      dst_image[i] = image[i].clone();
  }

  std::thread threads[4];

  struct rusage usage;

  struct timeval start, end;

  int return_value = getrusage(RUSAGE_SELF,&usage);

  if(return_value!= 0){

     std::cout << "\n The usage data can not be obtain..\n";

     return 0;
  }

  start = usage.ru_utime;

  threads[0] = std::thread(Filter_Images,0,50);

  threads[1] = std::thread(Filter_Images,50,100);

  threads[2] = std::thread(Filter_Images,100,150);

  threads[3] = std::thread(Filter_Images,150,200);

  threads[0].join();

  threads[1].join();

  threads[2].join();

  threads[3].join();

  return_value = getrusage(RUSAGE_SELF, &usage);

  if(return_value!= 0){

     std::cout << "\n The usage data can not be obtain..\n";

     return 0;
  }

  end = usage.ru_utime;

  Elapsed_Time = end.tv_sec - start.tv_sec;

  std::cout << Elapsed_Time;

  return 0;
}

void Filter_Images(int start, int end){

     for(int i=start;i<end;i++){

         int kernel_size = 5;

         kernel = cv::Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);

         cv::filter2D(image[i], dst_image[i],image[i].depth(),kernel,cv::Point(-1,-1));
     }
}
