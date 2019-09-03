/*
 * =====================================================================================
 *
 *       Filename:  suite.c
 *
 *    Description:  The main wrapper for the suite
 *
 *        Version:  1.0
 *        Created:  10/22/2009 08:40:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liang Wang (lw2aw), lw2aw@virginia.edu
 *        Company:  CS@UVa
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <thread>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include "common.h"

static int do_verify = 0;

int omp_num_threads = 4;

int Elapsed_Time = 0;

extern void lud_function(float * a, float * duplicated_matrix,int size);

static struct option long_options[] = {
  /* name, has_arg, flag, val */
  {"input", 1, NULL, 'i'},
  {"size", 1, NULL, 's'},
  {"verify", 0, NULL, 'v'},
  {0,0,0,0}
};

int main ( int argc, char *argv[] ){

    int matrix_dim = 32; /* default size */

    int opt, option_index=0;

    func_ret_t ret;

    const char *input_file = NULL;

    float *m, *mm, *mt1, *mt2, *mt3;

    stopwatch sw;


    while ((opt = getopt_long(argc, argv, "::vs:n:i:",
                            long_options, &option_index)) != -1 ) {
    switch(opt){
    case 'i':
      input_file = optarg;
      break;
    case 'v':
      do_verify = 1;
      break;
    case 'n':
      omp_num_threads = atoi(optarg);
      break;
    case 's':
      matrix_dim = atoi(optarg);
      printf("Generate input matrix internally, size =%d\n", matrix_dim);
      // fprintf(stderr, "Currently not supported, use -i instead\n");
      // fprintf(stderr, "Usage: %s [-v] [-s matrix_size|-i input_file]\n", argv[0]);
      // exit(EXIT_FAILURE);
      break;
    case '?':
      fprintf(stderr, "invalid option\n");
      break;
    case ':':
      fprintf(stderr, "missing argument\n");
      break;
    default:
      fprintf(stderr, "Usage: %s [-v] [-s matrix_size|-i input_file]\n",
	      argv[0]);
      exit(EXIT_FAILURE);
    }
    }

  if ( (optind < argc) || (optind == 1)) {
    fprintf(stderr, "Usage: %s [-v] [-n no. of threads] [-s matrix_size|-i input_file]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (input_file) {
    //printf("Reading matrix from file %s\n", input_file);
    ret = create_matrix_from_file(&m, input_file, &matrix_dim);
    if (ret != RET_SUCCESS) {
      m = NULL;
      fprintf(stderr, "error create matrix from file %s\n", input_file);
      exit(EXIT_FAILURE);
    }
  }

  else if (matrix_dim) {
    printf("Creating matrix internally size=%d\n", matrix_dim);
    ret = create_matrix(&m, matrix_dim);
    if (ret != RET_SUCCESS) {
      m = NULL;
      fprintf(stderr, "error create matrix internally size=%d\n", matrix_dim);
      exit(EXIT_FAILURE);
    }
  }

  else {
    printf("No input file specified!\n");
    exit(EXIT_FAILURE);
  }

  if (true){
    /* print_matrix(m, matrix_dim); */
    matrix_duplicate(m, &mm, matrix_dim);
    matrix_duplicate(m, &mt1,matrix_dim);
    matrix_duplicate(m, &mt2,matrix_dim);
    matrix_duplicate(m, &mt3,matrix_dim);
  }

  struct rusage usage;

  struct timeval start, end;

  int return_value = getrusage(RUSAGE_SELF,&usage);

  if(return_value!= 0){

     std::cout << "\n The usage data can not be obtain..\n";

     return 0;
  }

  start = usage.ru_utime;


  std::thread thread_list[4];

  thread_list[0] = std::thread(lud_function,m,mm,matrix_dim);

  thread_list[1] = std::thread(lud_function,mt1,mm,matrix_dim);

  thread_list[2] = std::thread(lud_function,mt2,mm,matrix_dim);

  thread_list[3] = std::thread(lud_function,mt3,mm,matrix_dim);

  for(int i=0;i<4;i++){

      thread_list[i].join();
  }

  return_value = getrusage(RUSAGE_SELF, &usage);

  if(return_value!= 0){

     std::cout << "\n The usage data can not be obtain..\n";

     return 0;
  }

  end = usage.ru_utime;

  Elapsed_Time = end.tv_sec - start.tv_sec;

  free(mm);

  free(m);

  std::cout << Elapsed_Time ;

  return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
