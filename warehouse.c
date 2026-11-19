// Provide a report which counts the number of products in each container
// Amelia Stronska 
// 30/03/2026

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINE sizes for the structs for the different data sets A, B, C, D
#define SIZEA 11 
#define SIZEB 11
#define SIZEC 11
#define SIZED 11


// struct signature for time as seperate values for hours, seconds and minutes 
struct TIME
{
    int hour; // BETWEEN 8 AND 17
    int minute; // 0 - 59
    int second; // 0 - 59
};

// struct signature for data of each product 
typedef struct {
    int ContainerID;
    struct TIME time; // time struct nested 
    int weight;
    int productCode;
    int temp;
    int CourierID; // 1 - 4

} DATAFILE; // "struct DATAFILE"

// struct signature for container and amount of products 
struct container {

    int ID;
    int productNo;

};

// TASK 1 function signature - merging sorted parts of an array for merge sort 
void merge(DATAFILE *arr, int, int, int);

// TASK 1 function signature - merge sort 
void merge_sort(DATAFILE *A, int, int);

// TASK 2 function signature - combine the sorted data sets into one 'two at a time' to create a dispatch file
DATAFILE* merge2(DATAFILE *arr1,int, DATAFILE *arr2, int);

// TASK 3 user interface to find first product occurance at given time
int findProduct(DATAFILE *A, int, int, int, int);

// TASK 4 function to count number of products in each container 
void countProducts(DATAFILE *A, struct container *cont , int);


int main(){

    // initialise lengths of the arrays 
    int n1 = SIZEA;
    int n2 = SIZEB;
    int n3 = SIZEC;
    int n4 = SIZED;

    // initialise time variables for user to input
    int hour;
    int min;
    int sec;

    // initialise the data
    //  data file A
    DATAFILE dataA[] = {
        {101,{8,15,42}, 12,1001,18,1},
        {101,{9,30,17}, 7,1002,21,1},
        {101,{10,5,55},14,1003,19,1},
        {103,{11,45,8}, 9,1004,22,1},
        {102,{12,20,33},11,1005,17,1},
        {103,{13,10,4}, 6,1006,20,1},
        {103,{14,55,29},8,1007,23,1},
        {103,{15,0,51},13,1008,18,1},
        {102,{15,40,16},10,1009,21,1},
        {102,{16,25,38},5,1010,19,1},
        {102,{16,50,22},9,1011,24,1}
    };

    //  data file B
    DATAFILE dataB[] = {
        {201,{8,15,42}, 12, 2001, 18, 2},
        {202,{9,30,17}, 7,  2002, 21, 2},
        {203,{10,5,55}, 14, 2003, 19, 2},
        {201,{11,45,8}, 9,  2004, 22, 2},
        {202,{12,20,33}, 11,2005, 17, 2},
        {203,{13,10,4}, 6,  2006, 20, 2},
        {201,{14,55,29}, 8, 2007, 23, 2},
        {202,{15,0,51}, 13, 2008, 18, 2},
        {203,{9,40,16}, 10, 2009, 21, 2},
        {203,{10,25,38}, 5, 2010, 19, 2},
        {203,{16,50,22}, 9, 2011, 24, 2},
    };

    //  data file C
    DATAFILE dataC[] = {
        {309,{15,5,27},12,3009,20,3},
        {302,{8,50,37},9,3002,20,3},
        {301,{16,55,49},9,3011,24,3},
        {306,{11,9,41},13,3005,19,3},
        {306,{8,5,14},15,3001,16,3},
        {306,{14,12,9},8,3008,23,3},
        {306,{10,18,5},7,3004,22,3},
        {307,{13,30,56},10,3007,21,3},
        {303,{9,22,48},11,3003,18,3},
        {300,{16,10,33},14,3010,18,3},
        {306,{12,45,12},6,3006,17,3}
    };

    //  data file D
    DATAFILE dataD[] = {
        {405,{8,30,25}, 9,  4001, 21, 4},
        {405,{11,15,58}, 13, 4002, 19, 4},
        {405,{10,50,41}, 6, 4003, 23, 4},
        {405,{11,35,14}, 11,4004, 18, 4},
        {405,{12,55,37}, 8, 4005, 20, 4},
        {406,{13,55,20}, 14,4006, 22, 4},
        {407,{12,40,3}, 10, 4007, 17, 4},
        {408,{15,25,46}, 7, 4008, 21, 4},
        {409,{16,55,33}, 12, 4009, 19, 4},
        {405,{9,45,12}, 5,  4010, 23, 4},
        {405,{16,20,55}, 9, 4011, 20, 4},
    };


    // pointers pointing at structs
    DATAFILE* data1 = dataA;
    DATAFILE* data2 = dataB;
    DATAFILE* data3 = dataC;
    DATAFILE* data4 = dataD;

    // print the raw data in its initial state

    printf("\n---------- PRINTING ORIGINAL DATA -------------\n");
    
    // print data A

    printf("\n---------- ORIGINAL DATA FILE A -------------\n");
    for (int i = 0; i < n1; i++) {
        printf("Container ID: %d | Time: %d:%d:%d | Weight: %d | Product Code: %d | Temperature: %d | Courier ID: %d\n",
        (data1+i)->ContainerID, (data1+i)->time.hour, (data1+i)->time.minute, (data1+i)->time.second, (data1+i)->weight, (data1+i)->productCode, (data1+i)->temp, (data1+i)->CourierID);
    }

    // print data B

    printf("\n---------- ORIGINAL DATA FILE B  -------------\n");
    for (int i = 0; i < n2; i++) {
        printf("Container ID: %d | Time: %d:%d:%d | Weight: %d | Product Code: %d | Temperature: %d | Courier ID: %d\n",
        (data2+i)->ContainerID, (data2+i)->time.hour, (data2+i)->time.minute, (data2+i)->time.second, (data2+i)->weight, (data2+i)->productCode, (data2+i)->temp,(data2+i)->CourierID);
    }

    // print data C

    printf("\n---------- ORIGINAL DATA FILE C  -------------\n");
    for (int i = 0; i < n3; i++) {
        printf("Container ID: %d | Time: %d:%d:%d | Weight: %d | Product Code: %d | Temperature: %d | Courier ID: %d\n",
        (data3+i)->ContainerID, (data3+i)->time.hour, (data3+i)->time.minute,(data3+i)->time.second, (data3+i)->weight, (data3+i)->productCode, (data3+i)->temp, (data3+i)->CourierID);
    }

    // print data D

    printf("\n---------- ORIGINAL DATA FILE D  -------------\n");
    for (int i = 0; i < n4 - 1; i++) {
        printf("Container ID: %d | Time: %d:%d:%d | Weight: %d | Product Code: %d | Temperature: %d | Courier ID: %d\n",
        (data4+i)->ContainerID, (data4+i)->time.hour, (data4+i)->time.minute, (data4+i)->time.second, (data4+i)->weight, (data4+i)->productCode, (data4+i)->temp, (data4+i)->CourierID);
    }

    // sorting of data and printing the sorted data 

    printf("\n---------- PRINTING SORTED DATA -------------\n");

    // sort data file A

    merge_sort(dataA, 0, n1 - 1); 

    printf("\n---------- DATA FILE A -------------\n");

    // print out data A
    for (int i = 0; i < n1; i++) {
        printf("Container ID: %d | Time: %d:%d:%d | Weight: %d | Product Code: %d | Temperature: %d | Courier ID: %d\n",
        (data1+i)->ContainerID, (data1+i)->time.hour, (data1+i)->time.minute, (data1+i)->time.second, (data1+i)->weight, (data1+i)->productCode, (data1+i)->temp, (data1+i)->CourierID);
    }

    // sort data data B

    merge_sort(dataB, 0, n2 - 1);

    printf("\n---------- DATA FILE B -------------\n");

    // print out data B
    for (int i = 0; i < n2; i++) {
        printf("Container ID: %d | Time: %d:%d:%d | Weight: %d | Product Code: %d | Temperature: %d | Courier ID: %d\n",
        (data2+i)->ContainerID, (data2+i)->time.hour, (data2+i)->time.minute, (data2+i)->time.second, (data2+i)->weight, (data2+i)->productCode, (data2+i)->temp,(data2+i)->CourierID);
    }

    // sort data C

    merge_sort(dataC, 0, n3 - 1);

    printf("\n---------- DATA FILE C -------------\n");

    // print out data C
    for (int i = 0; i < n3; i++) {
        printf("Container ID: %d | Time: %d:%d:%d | Weight: %d | Product Code: %d | Temperature: %d | Courier ID: %d\n",
        (data3+i)->ContainerID, (data3+i)->time.hour, (data3+i)->time.minute,(data3+i)->time.second, (data3+i)->weight, (data3+i)->productCode, (data3+i)->temp, (data3+i)->CourierID);
    }

    // sort data data D

    merge_sort(dataD, 0, n4 - 1);

    printf("\n---------- DATA FILE D -------------\n");

    // print out data D
    for (int i = 0; i < n4 - 1; i++) {
        printf("Container ID: %d | Time: %d:%d:%d | Weight: %d | Product Code: %d | Temperature: %d | Courier ID: %d\n",
        (data4+i)->ContainerID, (data4+i)->time.hour, (data4+i)->time.minute, (data4+i)->time.second, (data4+i)->weight, (data4+i)->productCode, (data4+i)->temp, (data4+i)->CourierID);
    }

    // creating dispatch file 

    DATAFILE *mergedAB = merge2(dataA, n1, dataB, n2); // merge dataA and dataB in sorted order
    DATAFILE *mergedCD = merge2(dataC, n3, dataD, n4); // merge dataC and dataD in sorted order 
    DATAFILE *mergedfinal = merge2(mergedAB, n1+n2 , mergedCD, n3+n4); // merge the two merge arrays created above

    // print dispatch list 

    printf("\n-------------Dispatch order---------------\n");

    for(int i = 0; i < n1+n2+n3+n4-1; i++){

        printf("Container ID: %d | Time: %d:%d:%d | Weight: %d | Product Code: %d | Temperature: %d | Courier ID: %d\n",
        mergedfinal[i].ContainerID, mergedfinal[i].time.hour, mergedfinal[i].time.minute, mergedfinal[i].time.second, mergedfinal[i].weight, mergedfinal[i].productCode, mergedfinal[i].temp, mergedfinal[i].CourierID);
    }

    // prompt user to input a time (h m s)
    printf("\nEnter hour: ");
    scanf("%d", &hour);

    printf("\nEnter minute: ");
    scanf("%d", &min);

    printf("\nEnter second: ");
    scanf("%d", &sec);

    // search for product at time entered above

    int foundProduct = findProduct(mergedfinal, n1+n2+n3+n4, hour, min, sec); // returns 0 if product is not found
    if (foundProduct != 0){ // if found print product 

        printf("\nThe first occurance of a product as %d:%d:%d is %d\n", hour, min, sec, foundProduct);

    }

    // count amount of products per container 
    // initialises a struct to hold all the unique container IDs
    struct container *unique = calloc((n1+n2+n3+n4), sizeof(struct container));

    // count amount of products in each container
    countProducts(mergedfinal, unique, n1+n2+n3+n4);

    // free memory 
    free(mergedAB);
    free(mergedCD);
    free(mergedfinal);

    free(data1);
    free(data2);
    free(data3);
    free(data4);

    free(unique);

    return 0;

}

// merge sort function for structs 
void merge_sort(DATAFILE *A, int low, int high){

    // base case, if 1 left in array 
    if(low >= high){

        return; // start stack 
    }

    else{

        int mid = (low+high)/2;
        merge_sort(A, low, mid);
        merge_sort(A, mid+1, high);
        merge(A, low, mid, high);

    }
}

// merge function to be used in merge sort, merges arrays in sorted order 
void merge(DATAFILE *A, int low, int mid, int high) {
    int left  = low; // starting point of left array
    int right = mid + 1; // starting point of right array
    int temp  = 0; // index of temporary array
    DATAFILE *tempA = (DATAFILE *)malloc((high - low + 1) * sizeof(DATAFILE)); // creates temporary array 

    // comparison to find the smaller value between left or right 
    while (left <= mid && right <= high){

        if ((A[left].time.hour < A[right].time.hour) || // check if hour of left side is smaller that right side or...
        ((A[left].time.hour == A[right].time.hour) && (A[left].time.minute < A[right].time.minute)) || // if hours are the same check if minute on left is smaller or...
        ((A[left].time.hour == A[right].time.hour) && (A[left].time.minute == A[right].time.minute) && (A[left].time.second < A[right].time.second))) // if hours and minutes are same check if seconds are smaller 
        {
            tempA[temp++] = A[left++]; // if condition is met copy left value into tempA
        }
        else
        {
            tempA[temp++] = A[right++]; // else copy right side into tempA
        }

    }

    // copy the remaining values 
    while (left  <= mid) {
        tempA[temp++] = A[left++];
    }
    while (right <= high){
        tempA[temp++] = A[right++];
    }

    // copy the tempA values back into the array A
    for (int i = low; i <= high; i++) {
        A[i] = tempA[i - low];
    }

    free(tempA); // free up tempA, no longer needed 
}

// function to merge two sorted arrays into a bigger sorted array, used to create the dispatch file
DATAFILE* merge2(DATAFILE *a1, int na1, DATAFILE *a2, int na2){

    int i = 0; // start position in a1
    int j = 0; // start position in a2
    int k = 0; // position in result merged array
    DATAFILE* result = (DATAFILE*)malloc((na1 + na2) * sizeof(DATAFILE)); // create array to hold the merges array, (length is the lengths of the two arrays added together)

    while (i < na1 && j < na2) {
        if (a1[i].time.hour < a2[j].time.hour || // same time comparison as above in merge 
            (a1[i].time.hour == a2[j].time.hour && a1[i].time.minute < a2[j].time.minute) ||
            (a1[i].time.hour == a2[j].time.hour && a1[i].time.minute == a2[j].time.minute && a1[i].time.second < a2[j].time.second))
            result[k++] = a1[i++]; // add the left value to the result 
        else
            result[k++] = a2[j++]; // add the right value to the result 
    }


    // copy any leftovers
    while (i < na1) {
        result[k++] = a1[i++];
    }

    while (j < na2) {
        result[k++] = a2[j++];
    }

    return result; // return the merged array 

}

// function to find product at given time 
int findProduct(DATAFILE *A, int n, int h, int m, int s){ // struct, length of array, hour, minute, second

    int low = 0; // low is the beginning if the array aka 0
    int high = n - 1; // high is set to length of array aka end 
    int foundProduct = 0;

    while(low <= high){ 

        int middle = (low + high)/2;

        // checks if the hour minute and second are the same as inputted by the user 
        if((A[middle].time.hour == h) && (A[middle].time.minute == m) && (A[middle].time.second == s)){

            // if they are identical return product code 
            foundProduct = A[middle].productCode;
            printf("\nproduct found");
            return foundProduct; // returns product code 
            

        }

        // if time is smaller than the one inputted, shift to the right side 
        if(A[middle].time.hour < h || 
            (A[middle].time.hour == h && A[middle].time.minute < m) ||
            (A[middle].time.hour == h && A[middle].time.minute == m && A[middle].time.second < s))
            {
                low = middle + 1; // shift to the right side 
            }
        
        // if time is bigger than the one inputted shift to the left side 
        if(A[middle].time.hour > h || // same time comparison as above in merge 
            (A[middle].time.hour == h && A[middle].time.minute > m) ||
            (A[middle].time.hour == h && A[middle].time.minute == m && A[middle].time.second > s))
            {
                high = middle - 1; // shift to the left side 
            }
        
    }

    printf("\nProduct not found");
    return 0;
    
}



void countProducts(DATAFILE *A, struct container *C, int n){

    
    int UCindex = 0; // variable to keep track of index in the unique array 
    int condition = 0; // variable checks if container id already exists 

    for(int i = 0; i < n; i++){

        // reset condition, assume container not found in unique list 
        condition = 0;

        for(int j = 0; j < UCindex; j++){

            if(A[i].ContainerID == C[j].ID){ // check if container is ine unique container ID list 

                condition = 1; // found, condition set to 1
                C[j].productNo += 1; // make number of products set to 1 since its a new addition 

                break;
            }

        }

        if(condition == 0){ // if not found add to array 

            C[UCindex].ID = A[i].ContainerID;
            C[UCindex].productNo = 1;
            UCindex ++;

        }

        
    }


    for(int k = 0; k < UCindex; k++){

        printf("\nContainer %d contains: %d products", C[k].ID, C[k].productNo);
    }
}