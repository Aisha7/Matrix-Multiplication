#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
void intAlgo(int,int);
long ** intCreateMatrix(int);
void intInitializeMatrix(int,long**);
void intPrintMatrix(long**,int);
void intNaive(long**,long**,long**,int);
void intRecursive(long**,long**,long**,int,int,int,int,int);
void intStrassen(long**,long**,long**,int);
void intAdd(int,long**,long**,long**);
void intSub(int,long**,long**,long**);
void intDivide(int,long**,long**,int,int);
void intJoin(int,long**,long**,int,int);
void intPrintMatrixResult(long**,int,FILE*);

void floatAlgo(int,int);
float ** floatCreateMatrix(int);
void floatInitializeMatrix(int,float**);
void floatPrintMatrix(float**,int);
void floatNaive(float**,float**,float**,int);
void floatRecursive(float**,float**,float**,int,int,int,int,int);
void floatStrassen(float**,float**,float**,int);
void floatAdd(int,float**,float**,float**);
void floatSub(int,float**,float**,float**);
void floatDivide(int,float**,float**,int,int);
void floatJoin(int,float**,float**,int,int);
void floatPrintMatrixResult(float**,int,FILE*);


int main(int argc,char** argv){
    
    int opt;
    int algo;
    int dataType;
    int n;
    
    while ((opt = getopt (argc, argv, "a:ifs:")) != -1)
    {
        switch (opt)
        {
            case 'a':
                algo = atoi(optarg);
                break;
            case 'i':
                dataType = 1;
                break;
            case 'f':
                dataType = 2;
                break;
            case 's':
                n = atoi(optarg);
        }
    }
  /*
    printf("Enter size of matrix:\n4\t\t512\n16\t\t1024\n32\t\t2048\n64\t\t4096\n128\t\t8192\n256\n\n");//arrange properly
    scanf("%d",&n);
    printf("Enter the Algorithm:\n1. Naive\n2. Recursive\n3. Strassen\n");
    scanf("%d",&algo);
    printf("Enter the data type:\n1. Integer\n2. Floating Point\n");
    scanf("%d",&dataType);*/
    switch (n) {
        case 4:
        case 16:
        case 32:
        case 64:
        case 128:
        case 256:
        case 512:
        case 1024:
        case 2048:
        case 4096:
        case 8192:
            break;
        default:
            n = 16;
    }
    
    switch (dataType) {
        case 1:
            intAlgo(n,algo);
            break;
        case 2:
            floatAlgo(n,algo);
            break;
        default:
            intAlgo(n,algo);
            break;
    }
    
    return 0;
}
//Integer
void intAlgo(int n,int algo){
    
    int decision;
    long **a = NULL;
    long **b = NULL;
    long **nResult = NULL;
    long **rResult = NULL;
    long **sResult = NULL;
    
    FILE *nr;
    FILE *rr;
    FILE *sr;
    
    clock_t begin;
    clock_t end;
    double time_spent;
    srand(time(0));
    
    a = intCreateMatrix(n);
    printf("Matrix A:\n");
    intInitializeMatrix(n,a);
    
    b = intCreateMatrix(n);
    printf("Matrix B:\n");
    intInitializeMatrix(n,b);
    
    nResult = intCreateMatrix(n);
    rResult = intCreateMatrix(n);
    sResult = intCreateMatrix(n);
    
    do{
        switch(algo){
            case 1:
                begin = clock();
                intNaive(a,b,nResult,n);
                end = clock();
                printf("Naive Result output:\n");
                nr = fopen("naive","w");
                intPrintMatrix(nResult,n);
                intPrintMatrixResult(nResult,n,nr);
                time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                printf("Time taken by Naive Algorithm for size %d is: %f seconds\n",n,time_spent);
                break;
            case 2:
                begin = clock();
                intRecursive(a,b,rResult,0,0,0,0,n);
                end = clock();
                printf("Recursive Result output:\n");
                rr = fopen("recur","w");
                intPrintMatrix(rResult,n);
                intPrintMatrixResult(rResult,n,rr);
                time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                printf("Time taken by Recursive Algorithm for size %d is: %f seconds\n",n,time_spent);
                break;
            case 3:
                begin = clock();
                intStrassen(a,b,sResult,n);
                end = clock();
                printf("Strassen Result output:\n");
                sr = fopen("stras","w");
                intPrintMatrix(sResult,n);
                intPrintMatrixResult(sResult,n,sr);
                time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                printf("Time taken by Strassen Algorithm for size %d is: %f seconds\n",n,time_spent);
                break;
        }
        printf("Do you want to execute another algorithm for the same input?\n1: yes\n0: no\n");
        scanf("%d",&decision);
        if(decision == 1){
            printf("Enter the algorithm you wish to execute\n1: Naive \n2: Recursive \n3: Strassen\n");
            scanf("%d",&algo);
        }
    } while(decision !=0 );
    fclose(nr);
    fclose(rr);
    fclose(sr);
}

long** intCreateMatrix(int n){
    
    long **arr;
    int i,j;
    arr = (long **)malloc(n * sizeof(long *));
    for (i=0; i<n; i++)
        arr[i] = (long *)malloc(n * sizeof(long));
    return arr;
    
}

void intInitializeMatrix(int n,long** arr){
    
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            arr[i][j] = rand()%10;
    }
    
    intPrintMatrix(arr,n);
    
}

void intNaive(long** a,long** b,long** result,int n){
    
    int i,j,k;
    
    for(i=0; i<n; i++){
        for(j=0;j<n;j++){
            result[i][j]=0;
            for(k=0;k<n;k++){
                result[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    
}

void intRecursive(long** a,long** b,long** result,int rowA, int colA, int rowB, int colB,int n){
    if(n==1){
        result[rowA][colB] += a[rowA][colA]*b[rowB][colB];
    }
    else{
        intRecursive(a,b,result,rowA,colA,rowB,colB,n/2);
        intRecursive(a,b,result,rowA,colA+(n/2),rowB+(n/2),colB,n/2);
        intRecursive(a,b,result,rowA,colA,rowB,colB+(n/2),n/2);
        intRecursive(a,b,result,rowA,colA+(n/2),rowB+(n/2),colB+(n/2),n/2);
        intRecursive(a,b,result,rowA+(n/2),colA,rowB,colB,n/2);
        intRecursive(a,b,result,rowA+(n/2),colA+(n/2),rowB+(n/2),colB,n/2);
        intRecursive(a,b,result,rowA+(n/2),colA,rowB,colB+(n/2),n/2);
        intRecursive(a,b,result,rowA+(n/2),colA+(n/2),rowB+(n/2),colB+(n/2),n/2);
    }
}

void intAdd(int n,long** a,long** b,long** result)
{
    int i,j;
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void intSub(int n,long** a,long** b,long ** result)
{
    
    int i,j;
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

void intDivide(int n,long** a,long** c,int i,int j)
{
    int i1,i2,j1,j2;
    for(i1=0,i2=i;i1<n/2;i1++,i2++)
    {
        for(j1=0,j2=j;j1<n/2;j1++,j2++)
        {
            c[i1][j1] = a[i2][j2];
        }
    }
}

void intJoin(int n,long** a,long** c,int i,int j)
{
    int i1,i2,j1,j2;
    for(i1=0,i2=i;i1<(n/2);i1++,i2++)
    {
        for(j1=0,j2=j;j1<(n/2);j1++,j2++)
        {
            a[i2][j2] = c[i1][j1];
        }
    }
}

void intStrassen(long** a,long** b ,long** result,int n){
    
    int i,j;
    
    if(n==2)
    {
        
        long p1 = (a[0][0]+a[1][1])*(b[0][0]+b[1][1]);
        long p2 = (a[1][0]+a[1][1])*b[0][0];
        long p3 = a[0][0]*(b[0][1]-b[1][1]);
        long p4 = a[1][1]*(b[1][0]-b[0][0]);
        long p5 = (a[0][0]+a[0][1])*b[1][1];
        long p6 = (a[1][0]-a[0][0])*(b[0][0]+b[0][1]);
        long p7 = (a[0][1]-a[1][1])*(b[1][0]+b[1][1]);
        
        long c11 = p1 + p4 - p5 + p7;
        long c12 = p3 + p5;
        long c21 = p2 + p4;
        long c22 = p1 + p3 - p2 + p6;
        
        result[0][0] = c11;
        result[0][1] = c12;
        result[1][0] = c21;
        result[1][1] = c22;
        
    }
    
    else
    {
        long** a11 = intCreateMatrix(n/2);
        long** a12 = intCreateMatrix(n/2);
        long** a21 = intCreateMatrix(n/2);
        long** a22 = intCreateMatrix(n/2);
        
        long** b11 = intCreateMatrix(n/2);
        long** b12 = intCreateMatrix(n/2);
        long** b21 = intCreateMatrix(n/2);
        long** b22 = intCreateMatrix(n/2);
        
        //divide matrices A & B into four parts
        intDivide(n,a,a11,0,0);
        intDivide(n,a,a12,0,n/2);
        intDivide(n,a,a21,n/2,0);
        intDivide(n,a,a22,n/2,n/2);
        
        intDivide(n,b,b11,0,0);
        intDivide(n,b,b12,0,n/2);
        intDivide(n,b,b21,n/2,0);
        intDivide(n,b,b22,n/2,n/2);
        
        //partial products
        long** p1 = intCreateMatrix(n/2);
        long** p2 = intCreateMatrix(n/2);
        long** p3 = intCreateMatrix(n/2);
        long** p4 = intCreateMatrix(n/2);
        long** p5 = intCreateMatrix(n/2);
        long** p6 = intCreateMatrix(n/2);
        long** p7 = intCreateMatrix(n/2);
        
        long** c11 = intCreateMatrix(n/2);
        long** c12 = intCreateMatrix(n/2);
        long** c21 = intCreateMatrix(n/2);
        long** c22 = intCreateMatrix(n/2);
        
        long** i1 = intCreateMatrix(n/2);
        long** i2 = intCreateMatrix(n/2);
        long** i3 = intCreateMatrix(n/2);
        long** i4 = intCreateMatrix(n/2);
        long** i5 = intCreateMatrix(n/2);
        long** i6 = intCreateMatrix(n/2);
        long** i7 = intCreateMatrix(n/2);
        long** i8 = intCreateMatrix(n/2);
        long** i9 = intCreateMatrix(n/2);
        long** i10 = intCreateMatrix(n/2);
        
        intAdd(n/2,a11,a22,i1);
        intAdd(n/2,b11,b22,i2);
        intStrassen(i1,i2,p1,n/2);
        
        intAdd(n/2,a21,a22,i3);
        intStrassen(i3,b11,p2,n/2);
        
        intSub(n/2,b12,b22,i4);
        intStrassen(a11,i4,p3,n/2);
        
        intSub(n/2,b21,b11,i5);
        intStrassen(a22,i5,p4,n/2);
        
        intAdd(n/2,a11,a12,i6);
        intStrassen(i6,b22,p5,n/2);
        
        intSub(n/2,a21,a11,i7);
        intAdd(n/2,b11,b12,i8);
        intStrassen(i7,i8,p6,n/2);
        
        intSub(n/2,a12,a22,i9);
        intAdd(n/2,b21,b22,i10);
        intStrassen(i9,i10,p7,n/2);
        
        //for c11
        long** r1 = intCreateMatrix(n/2);
        long** r2 = intCreateMatrix(n/2);
        long** r3 = intCreateMatrix(n/2);
        long** r4 = intCreateMatrix(n/2);
        
        intAdd(n/2,p1,p4,r1);        //sub operation
        intSub(n/2,r1,p5,r2);        //sub operation
        intAdd(n/2,r2,p7,c11);        //main operation
        
        //for c12
        intAdd(n/2,p3,p5,c12);
        
        //for c21
        intAdd(n/2,p2,p4,c21);
        
        //for c22
        intAdd(n/2,p1,p3,r3);       //sub operation
        intSub(n/2,r3,p2,r4);       //sub operation
        intAdd(n/2,r4,p6,c22);       //main operation
        
        
        intJoin(n,result,c11,0,0);
        intJoin(n,result,c12,0,n/2);
        intJoin(n,result,c21,n/2,0);
        intJoin(n,result,c22,n/2,n/2);
        
    }
    
}

void intPrintMatrix(long** arr,int n){
    
    int i,j;
    
    for(i=0; i<n; i++){
        for(j=0;j<n;j++){
            printf("%ld\t",arr[i][j]);
        }
        printf("\n");
    }
}
void intPrintMatrixResult(long** arr,int n, FILE* fp){
    
    int i,j;
    
    for(i=0; i<n; i++){
        for(j=0;j<n;j++){
            fprintf(fp,"%ld\t",arr[i][j]);
        }
        fprintf(fp,"\n");
    }
}

//Float
void floatAlgo(int n,int algo){
    
    int decision;
    float **a = NULL;
    float **b = NULL;
    float **c = NULL;
    float **nResult = NULL;
    float **rResult = NULL;
    float **sResult = NULL;
    
    FILE *nrf;
    FILE *rrf;
    FILE *srf;
    
    clock_t begin;
    clock_t end;
    double time_spent;
    
    srand(time(0));
    
    a = floatCreateMatrix(n);
    printf("Matrix A:\n");
    floatInitializeMatrix(n,a);
    
    b = floatCreateMatrix(n);
    printf("Matrix B:\n");
    floatInitializeMatrix(n,b);
    
    nResult = floatCreateMatrix(n);
    rResult = floatCreateMatrix(n);
    sResult = floatCreateMatrix(n);
    do{
        switch(algo){
            case 1:
                begin = clock();
                floatNaive(a,b,nResult,n);
                end = clock();
                printf("Naive Result output:\n");
                nrf = fopen("naivefloat","w");
                floatPrintMatrix(nResult,n);
                floatPrintMatrixResult(nResult,n,nrf);
                time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                printf("Time taken by Naive Algorithm for size %d is: %f seconds\n",n,time_spent);
                break;
            case 2:
                begin = clock();
                floatRecursive(a,b,rResult,0,0,0,0,n);
                end = clock();
                printf("Recursive Result output:\n");
                rrf = fopen("recurfloat","w");
                floatPrintMatrix(rResult,n);
                floatPrintMatrixResult(rResult,n,rrf);
                time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                printf("Time taken by Recursive Algorithm for size %d is: %f seconds\n",n,time_spent);
                break;
            case 3:
                begin = clock();
                floatStrassen(a,b,sResult,n);
                end = clock();
                printf("Strassen Result output:\n");
                srf = fopen("strassfloat","w");
                floatPrintMatrix(sResult,n);
                floatPrintMatrixResult(sResult,n,srf);
                time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                printf("Time taken by Strassen Algorithm for size %d is: %f seconds\n",n,time_spent);
                break;
        }
        printf("Do you want to execute another algorithm for the same input?\n1: yes\n0: no\n");
        scanf("%d",&decision);
        if(decision == 1){
            printf("Enter the algorithm you wish to execute\n1: Naive \n2: Recursive \n3: Strassen\n");
            scanf("%d",&algo);
        }
    }while(decision == 1);
    
}

float** floatCreateMatrix(int n){
    
    float** arr;
    int i;
    arr = (float **)malloc(n * sizeof(float *));
    for (i=0; i<n; i++)
        arr[i] = (float *)malloc(n * sizeof(float));
    return arr;
}

void floatInitializeMatrix(int n,float** arr){
    
    int i,j;
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            arr[i][j] = (float)rand()/RAND_MAX;
    }
    floatPrintMatrix(arr,n);
    
}

void floatNaive(float** a,float** b,float** result,int n){
    
    int i,j,k;
    
    for(i=0; i<n; i++){
        for(j=0;j<n;j++){
            result[i][j]=0;
            for(k=0;k<n;k++){
                result[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    
}

void floatRecursive(float** a,float** b,float** result,int rowA, int colA, int rowB, int colB,int n){
    if(n==1){
        result[rowA][colB] += a[rowA][colA]*b[rowB][colB];
    }
    else{
        floatRecursive(a,b,result,rowA,colA,rowB,colB,n/2);
        floatRecursive(a,b,result,rowA,colA+(n/2),rowB+(n/2),colB,n/2);
        floatRecursive(a,b,result,rowA,colA,rowB,colB+(n/2),n/2);
        floatRecursive(a,b,result,rowA,colA+(n/2),rowB+(n/2),colB+(n/2),n/2);
        floatRecursive(a,b,result,rowA+(n/2),colA,rowB,colB,n/2);
        floatRecursive(a,b,result,rowA+(n/2),colA+(n/2),rowB+(n/2),colB,n/2);
        floatRecursive(a,b,result,rowA+(n/2),colA,rowB,colB+(n/2),n/2);
        floatRecursive(a,b,result,rowA+(n/2),colA+(n/2),rowB+(n/2),colB+(n/2),n/2);
    }
}

void floatAdd(int n,float** a,float** b,float** result)
{
    int i,j;
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void floatSub(int n,float** a,float** b,float ** result)
{
    
    int i,j;
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

void floatDivide(int n,float** a,float** c,int i,int j)
{
    int i1,i2,j1,j2;
    for(i1=0,i2=i;i1<n/2;i1++,i2++)
    {
        for(j1=0,j2=j;j1<n/2;j1++,j2++)
        {
            c[i1][j1] = a[i2][j2];
        }
    }
}

void floatJoin(int n,float** a,float** c,int i,int j)
{
    int i1,i2,j1,j2;
    for(i1=0,i2=i;i1<(n/2);i1++,i2++)
    {
        for(j1=0,j2=j;j1<(n/2);j1++,j2++)
        {
            a[i2][j2] = c[i1][j1];
        }
    }
}

void floatStrassen(float** a,float** b ,float** result,int n){
    
    int i,j;
    
    if(n==2)
    {
        
        float p1 = (a[0][0]+a[1][1])*(b[0][0]+b[1][1]);
        float p2 = (a[1][0]+a[1][1])*b[0][0];
        float p3 = a[0][0]*(b[0][1]-b[1][1]);
        float p4 = a[1][1]*(b[1][0]-b[0][0]);
        float p5 = (a[0][0]+a[0][1])*b[1][1];
        float p6 = (a[1][0]-a[0][0])*(b[0][0]+b[0][1]);
        float p7 = (a[0][1]-a[1][1])*(b[1][0]+b[1][1]);
        
        float c11 = p1 + p4 - p5 + p7;
        float c12 = p3 + p5;
        float c21 = p2 + p4;
        float c22 = p1 + p3 - p2 + p6;
        
        result[0][0] = c11;
        result[0][1] = c12;
        result[1][0] = c21;
        result[1][1] = c22;
        
    }
    
    else
    {
        float** a11 = floatCreateMatrix(n/2);
        float** a12 = floatCreateMatrix(n/2);
        float** a21 = floatCreateMatrix(n/2);
        float** a22 = floatCreateMatrix(n/2);
        
        float** b11 = floatCreateMatrix(n/2);
        float** b12 = floatCreateMatrix(n/2);
        float** b21 = floatCreateMatrix(n/2);
        float** b22 = floatCreateMatrix(n/2);
        
        //divide matrices A & B into four parts
        floatDivide(n,a,a11,0,0);
        floatDivide(n,a,a12,0,n/2);
        floatDivide(n,a,a21,n/2,0);
        floatDivide(n,a,a22,n/2,n/2);
        
        floatDivide(n,b,b11,0,0);
        floatDivide(n,b,b12,0,n/2);
        floatDivide(n,b,b21,n/2,0);
        floatDivide(n,b,b22,n/2,n/2);
        
        //partial products
        float** p1 = floatCreateMatrix(n/2);
        float** p2 = floatCreateMatrix(n/2);
        float** p3 = floatCreateMatrix(n/2);
        float** p4 = floatCreateMatrix(n/2);
        float** p5 = floatCreateMatrix(n/2);
        float** p6 = floatCreateMatrix(n/2);
        float** p7 = floatCreateMatrix(n/2);
        
        float** c11 = floatCreateMatrix(n/2);
        float** c12 = floatCreateMatrix(n/2);
        float** c21 = floatCreateMatrix(n/2);
        float** c22 = floatCreateMatrix(n/2);
        
        float** i1 = floatCreateMatrix(n/2);
        float** i2 = floatCreateMatrix(n/2);
        float** i3 = floatCreateMatrix(n/2);
        float** i4 = floatCreateMatrix(n/2);
        float** i5 = floatCreateMatrix(n/2);
        float** i6 = floatCreateMatrix(n/2);
        float** i7 = floatCreateMatrix(n/2);
        float** i8 = floatCreateMatrix(n/2);
        float** i9 = floatCreateMatrix(n/2);
        float** i10 = floatCreateMatrix(n/2);
        
        floatAdd(n/2,a11,a22,i1);
        floatAdd(n/2,b11,b22,i2);
        floatStrassen(i1,i2,p1,n/2);
        
        floatAdd(n/2,a21,a22,i3);
        floatStrassen(i3,b11,p2,n/2);
        
        floatSub(n/2,b12,b22,i4);
        floatStrassen(a11,i4,p3,n/2);
        
        floatSub(n/2,b21,b11,i5);
        floatStrassen(a22,i5,p4,n/2);
        
        floatAdd(n/2,a11,a12,i6);
        floatStrassen(i6,b22,p5,n/2);
        
        floatSub(n/2,a21,a11,i7);
        floatAdd(n/2,b11,b12,i8);
        floatStrassen(i7,i8,p6,n/2);
        
        floatSub(n/2,a12,a22,i9);
        floatAdd(n/2,b21,b22,i10);
        floatStrassen(i9,i10,p7,n/2);
        
        //for c11
        float** r1 = floatCreateMatrix(n/2);
        float** r2 = floatCreateMatrix(n/2);
        float** r3 = floatCreateMatrix(n/2);
        float** r4 = floatCreateMatrix(n/2);
        
        floatAdd(n/2,p1,p4,r1);        //sub operation
        floatSub(n/2,r1,p5,r2);        //sub operation
        floatAdd(n/2,r2,p7,c11);        //main operation
        
        //for c12
        floatAdd(n/2,p3,p5,c12);
        
        //for c21
        floatAdd(n/2,p2,p4,c21);
        
        //for c22
        floatAdd(n/2,p1,p3,r3);       //sub operation
        floatSub(n/2,r3,p2,r4);       //sub operation
        floatAdd(n/2,r4,p6,c22);       //main operation
        
        
        floatJoin(n,result,c11,0,0);
        floatJoin(n,result,c12,0,n/2);
        floatJoin(n,result,c21,n/2,0);
        floatJoin(n,result,c22,n/2,n/2);
        
    }
    
}

void floatPrintMatrix(float** arr,int n){
    
    int i,j;
    
    for(i=0; i<n; i++){
        for(j=0;j<n;j++){
            printf("%f\t",arr[i][j]);
        }
        printf("\n");
    }
}

void floatPrintMatrixResult(float** arr,int n,FILE* fp){
    
    int i,j;
    
    for(i=0; i<n; i++){
        for(j=0;j<n;j++){
            fprintf(fp,"%f\t",arr[i][j]);
        }
        fprintf(fp,"\n");
    }
}


