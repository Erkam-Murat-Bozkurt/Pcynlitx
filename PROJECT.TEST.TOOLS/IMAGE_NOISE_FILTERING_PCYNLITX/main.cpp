 #include <sys/time.h>
 #include <sys/resource.h>
 #include <unistd.h>
 #include <opencv2/opencv.hpp>
 #include <iostream>
 #include "MT_Library_Headers.h"

 #define IMAGE_NUMBER 200   // DEFINES TOTAL NUMBER OF IMAGES THAT WILL BE FILTERED
 #define THREAD_NUMBER 4

 int Elapsed_Time = 0;

 cv::Mat image [IMAGE_NUMBER];

 cv::Mat dst_image [IMAGE_NUMBER];

 cv::Mat kernel;

 int main(int argc, char ** argv){

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

     struct rusage usage;

     struct timeval start, end;

     int return_value = getrusage(RUSAGE_SELF,&usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }

     start = usage.ru_utime;


     pcynlitx::Thread_Server Server;

     Server.Loop_Intervals_IT.set_thread_number(4);

     Server.Loop_Intervals_IT.initialize_thread_intervals();

     int position = 0;

     int increment = 50;

     for(int i=0;i<THREAD_NUMBER;i++){

         Server.Loop_Intervals_IT.set_thread_intervals(position,position+increment,i);

         position = position + increment;
     }

     for(int i=0;i<THREAD_NUMBER;i++){

         Server.Activate(i,Filter_Images);
     }

     for(int i=0;i<THREAD_NUMBER;i++){

         Server.Join(i);
     };

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


 void Filter_Images(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"Filter_Images");

      pcynlitx::Loop_Intervals_Client Loop_Intervals_IT(thread_data);

      int thread_number = Manager.Get_Thread_Number();

      int * interval_pointer = Loop_Intervals_IT.get_thread_interval(thread_number);

      int start = interval_pointer[0];

      int end =   interval_pointer[1];

      for(int i=start;i<end;i++){

          int kernel_size = 5;

          kernel = cv::Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);

          cv::filter2D(image[i], dst_image[i],image[i].depth(),kernel,cv::Point(-1,-1));
      }

      Manager.Exit();
 }
