#include <iostream>
#include <fstream>
using namespace std;
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <vector>

typedef struct ThreadData{

    int start;
    int end;
     //int* array;
    
}ThreadData;

int array_size;
vector<int> final_arr;


void merge(int start, int mid, int high){
	   int leftsize = mid- start +1; 
    int rightsize = high-mid;
	
		
	vector<int> leftarr(leftsize);
    vector<int> rightarr(rightsize); 
	for (int i = 0; i < leftsize; i++)
        leftarr[i] = final_arr[start + i];
        
        for (int j = 0; j < rightsize; j++)
        rightarr[j] = final_arr[mid+ 1+ j];
        
	
	
	int i=0,j=0,k=start;
    
	while (i< leftsize && j<rightsize){
	if(leftarr[i] < rightarr[j])
	{
		final_arr[k] = leftarr[i];
		i++;
	}	
	else{
		final_arr[k] = rightarr[j];
		j++;
			
	}
	k++;
	}
	
	while(i < leftsize){
		final_arr[k] = leftarr[i];
		i++;
		k++;
	}
		while(j < rightsize){
		final_arr[k] = rightarr[j];
		j++;
		k++;
	}
}



void* merge_sort(void* arg) {
ThreadData data = *((ThreadData*)arg);
//vector<int> array = data.array;
int start = data.start;
int end = data.end;

    if (start < end) {
        
    
    
    int middle = start +(end-start) / 2;	
	pthread_t left_thread;
        ThreadData leftdata = {start, middle};
        
        pthread_t right_thread;
        ThreadData rightdata = { middle + 1, end};
        
        
	pthread_create(&left_thread, NULL, merge_sort, &leftdata);
        pthread_create(&right_thread, NULL, merge_sort, &rightdata);
	
	pthread_join(left_thread, NULL);
    	pthread_join(right_thread, NULL);
    	
    	
	

merge(start, middle, end);
}
return NULL;

}

int main(int argv,char ** argc) {
string name;
cout<<"\n";
ifstream inputFile1(argc[1]);
   if (!inputFile1.is_open()) {
        cout << "File openning faild!" << endl;
        return 1;
    }
 inputFile1 >> array_size;
 final_arr.resize(array_size);
  //cout<<"array size:\n"<<array_size;
    for (int i = 0; i < array_size; i++) {
            inputFile1 >> final_arr[i];
    }
    //cout<<"\n\ninput array:\n";
    //    for (int i = 0; i < array_size; i++) {
    //        cout<< final_arr[i] <<" ";
    //}
    //cout<<"\n";
	ThreadData data = {0, array_size};
    
    pthread_t first;
    
    pthread_create(&first, NULL, merge_sort, &data);
    pthread_join(first, NULL);
    	cout<<"Sorted array: ";
      for (int i = 0; i < array_size; i++) {
            cout<< final_arr[i] <<" ";
    }
    cout<<"\n\n";

return 0;
}
