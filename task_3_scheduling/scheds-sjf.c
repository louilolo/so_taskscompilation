#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Function to find the waiting time for all processes
int waitingtime(int proc[], int n,
int burst_time[], int wait_time[]) {
   // waiting time for first process is 0
   wait_time[0] = 0;
   // calculating waiting time
   for (int i = 1; i < n ; i++ )
   wait_time[i] = burst_time[i-1] + wait_time[i-1] ;
   return 0;
}
// Function to calculate turn around time
int turnaroundtime( int proc[], int n,
int burst_time[], int wait_time[], int tat[]) {
   // calculating turnaround time by adding
   // burst_time[i] + wait_time[i]
   int i;
   for ( i = 0; i < n ; i++)
   tat[i] = burst_time[i] + wait_time[i];
   return 0;
}
//Function to calculate average time
int avgtime( int proc[], int n, int burst_time[]) {
   int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
   int i;
   //Function to find waiting time of all processes
   waitingtime(proc, n, burst_time, wait_time);
   //Function to find turn around time for all processes
   turnaroundtime(proc, n, burst_time, wait_time, tat);
   //Display processes along with all details
   printf("Processes  Burst   Waiting Turn around \n");
   // Calculate total waiting time and total turn
   // around time
   for ( i=0; i<n; i++) {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];
      printf(" %d\t  %d\t\t %d \t%d\n", i+1, burst_time[i], wait_time[i], tat[i]);
   }
   printf("Average waiting time = %f\n", (float)total_wt / (float)n);
   printf("Average turn around time = %f\n", (float)total_tat / (float)n);
   return 0;
}
void selectionSort(int processos[30], int times[30]){
   int min, aux, j;
   printf("%d\n", processos[30]);
   for(int i=0; i<29; i++){
      min = i;
      for(j=i+1; j<30; j++){
         if(times[j]<times[min]){
            min = j;
         }
      }
      aux = times[i];
      times[i] = times[j];
      times[j] = aux;
      aux = processos[i];
      processos[i] = processos[j];
      processos[j] = aux;
   }
   for (int i=0; i<30; i++){
      printf("%d, %d\n", processos[i], times[i]);
}
}
// main function
int main() {
   srand(time(NULL));   // Initialization, should only be called once.
   //process id's
   int proc[30];
   //Burst time of all processes
   int burst_time[30];
   //initialization
   int possible_times[] = {5, 8, 12};
   for(int i=0; i<30; i++){
      proc[i] = i+1;
      burst_time[i] = possible_times[(rand()%3)];
   }
   int n = sizeof proc / sizeof proc[0];
   selectionSort(proc, burst_time);
   avgtime(proc, n, burst_time);
   return 0;
}
