
 #include "MT_Library_Headers.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <assert.h>
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <unistd.h>
 #include "timer.h"


 #define M_SEED 9

 #define IN_RANGE(x, min, max)   ((x)>=(min) && (x)<=(max))
 #define CLAMP_RANGE(x, min, max) x = (x<(min)) ? min : ((x>(max)) ? max : x )
 #define MIN(a, b) ((a)<=(b) ? (a) : (b))


 int num_threads = 32;

 int Elapsed_Time_for_user = 0;

 int Elapsed_Time_for_sys = 0;

 int Elapsed_Time_for_total = 0;


 int rows = 0, cols = 0;

 void fatal(char *s){

     fprintf(stderr, "error: %s\n", s);
 }

 int main(int argc, char ** argv){

     if(argc < 3){

        std::cout << "\n\n usage: " << argv[0] << " <Number of Columns> <Number of rows>";

        std::cout << "\n\n";

        exit(0);
     }

     cols = atoi(argv[1]);
     rows = atoi(argv[2]);

     pcynlitx::Thread_Server Server;

     struct rusage usage;

     struct timeval start_us, end_us, start_sys, end_sys;

     int return_value = getrusage(RUSAGE_SELF,&usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }

     start_us = usage.ru_utime;

     start_sys = usage.ru_stime;


     for(int i=0;i<num_threads;i++){

         Server.Activate(i,run);
     }

     for(int i=0;i<num_threads;i++){

         Server.Join(i);
     };

    return_value = getrusage(RUSAGE_SELF, &usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    end_us = usage.ru_utime;

    end_sys = usage.ru_stime;

    Elapsed_Time_for_user = end_us.tv_sec - start_us.tv_sec;

    Elapsed_Time_for_sys = end_sys.tv_sec - start_sys.tv_sec;


    Elapsed_Time_for_total = Elapsed_Time_for_user + Elapsed_Time_for_sys;

    std::cout << Elapsed_Time_for_total << std::endl;

    return 0;
 }


 void run(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"run");

      int * data;
      int ** wall;
      int * result;

      data = new int [rows*cols];
      wall = new int * [rows];

      for(int n=0; n<rows; n++){

         wall[n]=data+cols*n;
      }

      result = new int [cols];

      int seed = M_SEED;

      srand(seed);

      for(int i = 0; i < rows; i++){

         for(int j = 0; j < cols; j++){

             wall[i][j] = rand() % 10;
         }
      }

      for(int j = 0; j < cols; j++){

          result[j] = wall[0][j];
      }

      unsigned long long cycles;

      int *src, *dst, *temp;
      int min;

      dst = result;
      src = new int [cols];

      for (int t = 0; t < rows-1; t++) {
          temp = src;
          src = dst;
          dst = temp;

          for(int n = 0; n < cols; n++){
            min = src[n];
            if (n > 0)
              min = MIN(min, src[n-1]);
            if (n < cols-1)
              min = MIN(min, src[n+1]);
            dst[n] = wall[t+1][n]+min;
          }
      }

      delete [] data;
      delete [] wall;
      delete [] dst;
      delete [] src;

      Manager.Exit();
 }
