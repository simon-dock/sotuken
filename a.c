#include        <stdio.h>
#include        <stdlib.h>
#include        <time.h>
#include        <unistd.h>

#define         N       1024
#define         K       1024
#define         Iter    100

void            swap(int _num, int *_index);

int     main(int argc, char *argv[]){
  int   **mat_a, **mat_b;
  int   *index;
  int   i, j, k, num, mem_size;
  struct timespec res;
  struct timespec       tp1, tp2;
  long  sec, nsec;
  double        start, end;

  /* initialize random() */
  srandom(time(NULL));

  /* set matrix size */
  if( argc == 2 )
    num = atoi(argv[1]);
  else
    num = N;

  mem_size = num * num * sizeof(int) * 2 + num * sizeof(int);
  if( mem_size < K )
    printf("Occupied memory size: %d(B)\n", mem_size);
  else
    printf("Occupied memory size: %d(KB)\n", mem_size / K );
  /* declare memory area for matrix */
  if(( mat_a = (int**)malloc(sizeof(int*) * num )) == NULL ){
    perror("malloc");
    exit(-1);
  }
  if(( mat_b = (int**)malloc(sizeof(int*) * num )) == NULL ){
    perror("malloc");
    exit(-1);
  }
  if(( index = (int*)malloc(sizeof(int) * num )) == NULL ){
    perror("malloc");
    exit(-1);
  }
  for( i = 0; i < num; i++ ){
    if(( mat_a[i] = (int*)malloc(sizeof(int) * num )) == NULL ){
      perror("malloc");
      exit(-1);
    }
    if(( mat_b[i] = (int*)malloc(sizeof(int) * num )) == NULL ){
      perror("malloc");
      exit(-1);
    }
    index[i] = i;
  }

  /* randomize access sequence index */
  swap(num, index);

  /* initialize matrix */
  for( i = 0; i < num; i++ ){
    for( j = 0; j < num; j++ ){
      mat_a[i][j] = random() % N + 1;
      mat_b[i][j] = 0;
 }
  }

  /* case 1: sequantial horizontal access */
  if( clock_gettime(CLOCK_REALTIME, &tp1) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  for ( k = 0; k < Iter; k++ ){
    for( i = 0; i < num; i++ ){
      for( j = 0; j < num; j++ ){
        mat_b[i][j] = mat_a[i][j] * mat_a[i][j];
      }
    }
  }
  if( clock_gettime(CLOCK_REALTIME, &tp2) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  printf("Case 1: ");
  if( tp2.tv_nsec < tp1.tv_nsec ){
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec - 1,
           tp2.tv_nsec + 1000000000 - tp1.tv_nsec );
  }else{
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec,
           tp2.tv_nsec - tp1.tv_nsec);
  }

  /* case 2: sequential vertical access */
  if( clock_gettime(CLOCK_REALTIME, &tp1) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  for( k = 0; k < Iter; k++ ){
    for( i = 0; i < num; i++ ){
      for( j = 0; j < num; j++ ){
        mat_b[j][i] = mat_a[j][i] * mat_a[j][i];
      }
    }
  }
  if( clock_gettime(CLOCK_REALTIME, &tp2) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  printf("Case 2: ");
  if( tp2.tv_nsec < tp1.tv_nsec ){
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec - 1,
           tp2.tv_nsec + 1000000000 - tp1.tv_nsec );
  }else{
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec,
           tp2.tv_nsec - tp1.tv_nsec);
  }

  /* case 3: random horizontal access */
  if( clock_gettime(CLOCK_REALTIME, &tp1) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  for( k = 0; k < Iter; k++ ){
    for( i = 0; i < num; i++ ){
      for( j = 0; j < num; j++ ){
        mat_b[i][index[j]] = mat_a[i][index[j]] * mat_a[i][index[j]];
      }
    }
  }
  if( clock_gettime(CLOCK_REALTIME, &tp2) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  printf("Case 3: ");
  if( tp2.tv_nsec < tp1.tv_nsec ){
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec - 1,
           tp2.tv_nsec + 1000000000 - tp1.tv_nsec );
  }else{
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec,
           tp2.tv_nsec - tp1.tv_nsec);
  }


  /* case 4: random vertical access */
  if( clock_gettime(CLOCK_REALTIME, &tp1) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  for( k = 0; k < Iter; k++ ){
    for( i = 0; i < num; i++ ){
      for( j = 0; j < num; j++ ){
        mat_b[index[i]][j] = mat_a[index[i]][j] * mat_a[index[i]][j];
      }
    }
  }
  if( clock_gettime(CLOCK_REALTIME, &tp2) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  printf("Case 4: ");
  if( tp2.tv_nsec < tp1.tv_nsec ){
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec - 1,
           tp2.tv_nsec + 1000000000 - tp1.tv_nsec );
  }else{
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec,
           tp2.tv_nsec - tp1.tv_nsec);
  }

  /* case 5 : random horizontal and vertical access */
  if( clock_gettime(CLOCK_REALTIME, &tp1) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  for( k = 0; k < Iter; k++ ){
    for( i = 0; i < num; i++ ){
      for( j = 0; j < num; j++ ){
        mat_b[index[i]][index[j]] = mat_a[index[i]][index[j]] * mat_a[index[i]][index[j]];
      }
    }
  }
  if( clock_gettime(CLOCK_REALTIME, &tp2) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  printf("Case 5: ");
  if( tp2.tv_nsec < tp1.tv_nsec ){
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec - 1,
           tp2.tv_nsec + 1000000000 - tp1.tv_nsec );
  }else{
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec,
  if( tp2.tv_nsec < tp1.tv_nsec ){
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec - 1,
           tp2.tv_nsec + 1000000000 - tp1.tv_nsec );
  }else{
    printf("%10ld.%09ld\n",
           tp2.tv_sec - tp1.tv_sec,
           tp2.tv_nsec - tp1.tv_nsec);
  }

  
  /* free memory */
  for( i = 0; i < num; i++ ){
    free(mat_a[i]);
    free(mat_b[i]);
  }
  free(mat_a);
  free(mat_b);
  free(index);
}

void    swap(int _num, int *_index){
  int   max;
  int   tmp, i, j, k;

  max = _num * 100;
  for( k = 0; k < max; k++ ){
    i = (int)((random()/((double)RAND_MAX + 1.0)) * _num);
    j = (int)((random()/((double)RAND_MAX + 1.0)) * _num);
    tmp = _index[i];
    _index[i] = _index[j];
    _index[j] = tmp;
  }
}

#include        <stdio.h>
#include        <stdlib.h>
#include        <time.h>

#define         TRIAL           1000

int     main(int argc, char *argv[]){
  register int          MAX_ELEMENTS = 262144;
  register int          half_elements;  
  register double       sum;
  double                src[MAX_ELEMENTS];
  double                elapse;
  int                   ret, i, trial, tmp_max;
  struct timespec       start, stop;
  FILE                  *output;

  if((output = fopen("pipe_perf1.dat", "w")) == NULL){
    perror("fopen");
    exit(-1);
  }
  
  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }else{
    srandom(start.tv_nsec);
  }

  for( i = 0; i < MAX_ELEMENTS; i++){
    src[i]      = (double)(10.0*random()/(RAND_MAX + 10.0));
  }

  /*    case 1  */
  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
perror("clock_gettime");
    exit(-1);
  }
  for( trial = 0; trial < TRIAL; trial++){
    sum = 0.0;
    for( i = 0; i < MAX_ELEMENTS; i++)
      sum += src[i];
  }
  if( clock_gettime(CLOCK_REALTIME, &stop) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  fprintf(output, "Case 1[sum=%lf]: ", sum);
  if( stop.tv_nsec < start.tv_nsec ){
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec - 1,
            stop.tv_nsec + 1000000000 - start.tv_nsec);
  }else{
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec,
            stop.tv_nsec - start.tv_nsec);
  }

  /*    case 2  */
  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  for(trial = 0; trial < TRIAL; trial++){
    sum = 0.0;
    for( i = 0; i < MAX_ELEMENTS/2; i++)
      sum += (src[i] + src[MAX_ELEMENTS-i-1]);
  }
  if( clock_gettime(CLOCK_REALTIME, &stop) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  fprintf(output, "Case 2[sum=%lf]: ", sum);
  if( stop.tv_nsec < start.tv_nsec ){
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec - 1,
            stop.tv_nsec + 1000000000 - start.tv_nsec);
  }else{
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec,
            stop.tv_nsec - start.tv_nsec);
  }

  /*    case 3  */
  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  half_elements = MAX_ELEMENTS/2;       
  for(trial = 0; trial < TRIAL; trial++){
    sum = 0.0;
    for( i = 0; i < half_elements; i++)
      sum += (src[i] + src[MAX_ELEMENTS-i-1]);
  }
  if( clock_gettime(CLOCK_REALTIME, &stop) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  fprintf(output, "Case 3[sum=%lf]: ", sum);
  if( stop.tv_nsec < start.tv_nsec ){
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec - 1,
            stop.tv_nsec + 1000000000 - start.tv_nsec);
  }else{
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec,
            stop.tv_nsec - start.tv_nsec);
  }

  /*    case 4  */
  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  for(trial = 0; trial < TRIAL; trial++){
    sum = 0.0;
    for( i = 0; i < MAX_ELEMENTS; i+=2)
      sum += (src[i] + src[i+1]);
  }
  if( clock_gettime(CLOCK_REALTIME, &stop) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  fprintf(output, "Case 4[sum=%lf]: ", sum);
  if( stop.tv_nsec < start.tv_nsec ){
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec - 1,
            stop.tv_nsec + 1000000000 - start.tv_nsec);
  }else{
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec,
            stop.tv_nsec - start.tv_nsec);
  }

  /*    case 5  */
  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
    perror("clock_gettime");
            stop.tv_nsec + 1000000000 - start.tv_nsec);
  }else{
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec,
            stop.tv_nsec - start.tv_nsec);
  }

  /*    case 5  */
  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  tmp_max = MAX_ELEMENTS - 3;
  for(trial = 0; trial < TRIAL; trial++){
    sum = 0.0;
    for( i = 0; i < tmp_max; i+=4)
      sum += (src[i] + src[i+1] + src[i+2] + src[i+3]);
  }
  if( clock_gettime(CLOCK_REALTIME, &stop) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  fprintf(output, "Case 5[sum=%lf]: ", sum);
  if( stop.tv_nsec < start.tv_nsec ){
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec - 1,
            stop.tv_nsec + 1000000000 - start.tv_nsec);
  }else{
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec,
            stop.tv_nsec - start.tv_nsec);
  }
  fclose(output);
}

yosou 

5>4>3>2>1

Case 1[sum=1309360.279134]:          0.829117476
Case 2[sum=1309360.279134]:          0.400875027
Case 3[sum=1309360.279134]:          0.399706724
Case 4[sum=1309360.279134]:          0.400317474
Case 5[sum=1309360.279134]:          0.223279496


include        <stdio.h>
#include        <stdlib.h>
#include        <time.h>
#include        <math.h>

#define         MAX_ELEMENTS    262144
#define         RANGE           11
#define         TRIAL           1000

void            case1(int *SRC, int *DIST);
void            case2(int *SRC, int *DIST);

int     main(int argc, char *argv[]){
  int                   src[MAX_ELEMENTS];
  int                   dist[11];
  double                sum1, sum2;     
  double                elapse;
  int                   i, ret;
  struct timespec       start, stop;
  FILE                  *output;

  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  srandom(start.tv_nsec);

  if(( output = fopen("pipe_perf2.dat", "w")) == NULL){
    perror("fopen");
    exit(-1);
  }

  for( i = 0; i < MAX_ELEMENTS; i++){
    src[i] = (int)(10.0*random()/(RAND_MAX + 10.0));
 }

  for( i = 0; i < RANGE; i++)
    dist[i] = 0;

  /* case 1     */
  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  for( i = 0; i < TRIAL; i++)
    case1(src, dist);
  if( clock_gettime(CLOCK_REALTIME, &stop) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  fprintf(output, "Case 1: ");
  if( stop.tv_nsec < start.tv_nsec ){
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec - 1,
            stop.tv_nsec + 1000000000 - start.tv_nsec);
  }else{
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec,
            stop.tv_nsec - start.tv_nsec);
  }
  for( i = 0; i < RANGE; i++)
    fprintf(output, "NUM[%d] = %d\n", i, dist[i]);

  /*    case 2  */
  for( i = 0; i < RANGE; i++)
    dist[i] = 0;
  if( clock_gettime(CLOCK_REALTIME, &start) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  for( i = 0; i < TRIAL; i++)
    case2(src, dist);
  if( clock_gettime(CLOCK_REALTIME, &stop) < 0 ){
    perror("clock_gettime");
    exit(-1);
  }
  fprintf(output, "Case 2: ");
  if( stop.tv_nsec < start.tv_nsec ){
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec - 1,
            stop.tv_nsec + 1000000000 - start.tv_nsec);
  }else{
    fprintf(output, "%10ld.%09ld\n",
            stop.tv_sec - start.tv_sec,
            stop.tv_nsec - start.tv_nsec);
  }

  for( i = 0; i < RANGE; i++)
    fprintf(output, "NUM[%d] = %d\n", i, dist[i]);
  
  fclose(output);
}

void    case1(int *SRC, int *DIST){
  int   i;

 for( i = 0; i < MAX_ELEMENTS; i++){
    if( SRC[i] < 1 )
      DIST[0]++;
    else if( SRC[i] >= 1 && SRC[i] < 2 )
      DIST[1]++;
    else if( SRC[i] >= 2 && SRC[i] < 3 )
  int   i;

 for( i = 0; i < MAX_ELEMENTS; i++){
    if( SRC[i] < 1 )
      DIST[0]++;
    else if( SRC[i] >= 1 && SRC[i] < 2 )
      DIST[1]++;
    else if( SRC[i] >= 2 && SRC[i] < 3 )
      DIST[2]++;
    else if( SRC[i] >= 3 && SRC[i] < 4 )
      DIST[3]++;
    else if( SRC[i] >= 4 && SRC[i] < 5 )
      DIST[4]++;
    else if( SRC[i] >= 5 && SRC[i] < 6 )
      DIST[5]++;
    else if( SRC[i] >= 6 && SRC[i] < 7 )
      DIST[6]++;
    else if( SRC[i] >= 7 && SRC[i] < 8 )
      DIST[7]++;
    else if( SRC[i] >= 8 && SRC[i] < 9 )
      DIST[8]++;
    else if( SRC[i] >= 9 && SRC[i] < 10 )
      DIST[9]++;
    else
      DIST[10]++;
  }
}

void    case2(int *SRC, int *DIST){
  int   i;

  for( i = 0; i < MAX_ELEMENTS; i++)
    DIST[SRC[i]]++;
}
Case 1:          6.566262652
NUM[0] = 26373000
NUM[1] = 26009000
NUM[2] = 26191000
NUM[3] = 26156000
NUM[4] = 26334000
NUM[5] = 25966000
NUM[6] = 25921000
NUM[7] = 26237000
NUM[8] = 26265000
NUM[9] = 26692000
NUM[10] = 0
Case 2:          0.788093675
NUM[0] = 26373000
NUM[1] = 26009000
NUM[2] = 26191000
NUM[3] = 26156000
NUM[4] = 26334000
NUM[5] = 25966000
NUM[6] = 25921000
NUM[7] = 26237000
NUM[8] = 26265000
NUM[9] = 26692000
NUM[10] = 0
~
~
~
~
~
~
~
