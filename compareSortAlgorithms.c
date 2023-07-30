#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int extraMemoryAllocated;


void merge(int data[],int b, int m, int e){
    
    int x, y, z = b;
    
    int s1 = m - b + 1;
    int s2 = e - m;
    
    int *ds1 = (int*) malloc(s1*sizeof(int));
    int *ds2 = (int*) malloc(s2*sizeof(int));
    
    extraMemoryAllocated += ((s1 + s2)*sizeof(int));

    
    
    
    for (x = 0; x < s1; x++)
        ds1[x] = data[b + x];
    for (y = 0; y < s2; y++)
        ds2[y] = data[m + 1+ y];
    
    x = 0;
    y = 0;
    
    while (x < s1 && y < s2)
    {
        if (ds1[x] <= ds2[y])
        {
            data[z] = ds1[x];
            x++;
        } else {
            data[z] = ds2[y];
            y++;
        }
        z++;
    }

    
    while (x < s1)
    {
        data[z] = ds1[x];
        x++;
        z++;
    }

    
    while (y < s2)
    {
        data[z] = ds2[y];
        y++;
        z++;
    }
    
    free(ds1);
    free(ds2);

}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    if(l < r){
         
         int midPoint = (l+r)/2;
         
         mergeSort(pData, l, midPoint);
         mergeSort(pData, midPoint+1, r);
         
         
         merge(pData, l, midPoint, r);
     }
    
    
}

void swap(int* n1, int* n2){
    
    int placeholder = *n1;
    
    *n1 = *n2;
    *n2 = placeholder;
    
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    int x,currentItem,y;
    for (x = 1; x < n; x++) {
        currentItem = pData[x];
        
        for (y=x-1; y >= 0; y--) {
            if(pData[y] > currentItem)
                pData[y+1] = pData[y];
            else
                break;
        }
        pData[y+1] = currentItem;
        
        

    }
    
    
}


// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    int x,y,swaps;
    
    swaps = 0;
    
    
    for (x = 0; x < n; x++) {
        swaps = 0;
        for (y = 0; y < n - x - 1; y++) {
            if(pData[y] > pData[y+1]){
                swap(&pData[y],&pData[y+1]);
                swaps++;
            }
        }
        
        if(swaps == 0)
            break;
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int minIndex,x,y,temp;
    for (x = 0; x < n-1; x++) {
        minIndex = x;
        
        for (y = x+1; y < n; y++)
            if(pData[y] < pData[minIndex])
                minIndex = y;
        
        temp = pData[x];
        pData[x] = pData[minIndex];
        pData[minIndex] = temp;
    }
}

// parses input file to an integer pDataay
int parseData(char *inputFileName, int **ppData)
{
    FILE* inFile = fopen(inputFileName,"r");
    int dataSz = 0;
    int i,n,*data;
    *ppData = NULL;
    
    if (inFile)
    {
        fscanf(inFile,"%d\n",&dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i=0;i<dataSz;++i)
        {
            fscanf(inFile, "%d ",&n);
            data = *ppData + i;
            *data = n;
        }

        fclose(inFile);
    }
    
    return dataSz;
}

// prints first and last 100 items in the data pDataay
void printArray(int pData[], int dataSz)
{
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i=0;i<100;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\t");
    
    for (i=sz;i<dataSz;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
   // char* fileNames[] = {"input3.txt"};
    for (i=0;i<3;++i)
    {
        int *pDataSrc, *pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);
        
        if (dataSz <= 0)
            continue;
        
        pDataCopy = (int *)malloc(sizeof(int)*dataSz);
    
        printf("---------------------------\n");
        printf("Dataset Size : %d\n",dataSz);
        printf("---------------------------\n");
        
        printf("Selection Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        selectionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Insertion Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        insertionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Bubble Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        bubbleSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);
        
        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);
        
        free(pDataCopy);
        free(pDataSrc);
    }
    
}
