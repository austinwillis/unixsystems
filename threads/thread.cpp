#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <cstdlib>
#include <cstring>

using namespace std;


int   m_size; //works up to 719, crashes at 720
int   num_of_thr;

struct v
{
    float *ma;
    float *mb;
	float *mc;
    int n;
    int i;
    int size;
};

void funcA(float *MATA, float *MATB, float *MATC, int N);
void funcB(float *MATA, float *MATB, float *MATC, int N);
void *mult (void *data);


int main(int argc, char **argv)
{

	  if (argc != 3) {
			cout << "Usage: matmultiplye <m / s> <matrix size>\ns=single threaded, m=multi threaded" << endl;
			exit(0);
    }
    if (strcmp(argv[1], "s") != 0 && strcmp(argv[1], "m") != 0) {
			cout << "argument 1 was " << argv[1] << ", please enter 's' or 'm' for argument 1" << endl; 
    }

	  m_size = atoi(argv[2]);
	  num_of_thr = (m_size*m_size)/2;
		float *ma = new float[m_size*m_size];
		float *mb = new float[m_size*m_size];
		float *mc = new float[m_size*m_size];
    for (int i = 0; i < m_size*m_size; i++) {
			  ma[i] = rand() % 100;
			  mb[i] = rand() % 100;
			  mc[i] = 0;
    }
    if (strcmp(argv[1], "s") == 0) {
	    funcA(ma, mb, mc, m_size);
  } else {
	  funcB(ma, mb, mc, m_size);
	}		
}

void funcB(float *MATA, float *MATB, float *MATC, int N){
  struct v data;
  int num_threads = N;
	if (num_threads > 10)
	num_threads = 10;
	int ths = num_threads;
	data.ma = MATA;
	data.mb = MATB;
  data.mc = MATC;
  data.size = N;
  data.n = num_threads;
  pthread_t threads[num_threads];
  for (int i = 0; i < num_threads; i++) {
  	data.i = i;
	pthread_create(&threads[i], NULL, mult, &data);
  }
	for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
	}
}

void *mult (void *data) {
	struct v *params = (struct v*)data;
  int s = params->i;
  int size = params->size;
  int num_thrd = params->n;
  int from = (s*size)/num_thrd;
  int to = ((s+1) * size)/num_thrd;
  for (int i = from; i < to; i++)
  {  
    for (int j = 0; j < size; j++)
    {
      for (int k = 0; k < size; k++)
        *params->mc += params->ma[i*size+k]*params->mb[k*size+j];
    }
  }
}

void funcA(float *MATA, float *MATB, float *MATC, int N){
  	int i = 0;
  	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
     		float sum = 0;
     		for (int i = 0; i < N; i++)
     			sum += MATA[N*r+i] * MATB[c+i*N];
     		MATC[N*r+c] += sum;
        sum = 0;
    	}
  	}
}
