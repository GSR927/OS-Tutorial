// C++ program to implement Shortest Remaining Time First
// ShortestRemainingTimeFirst (SRTF)
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;
class process{
   public:
    int pd;//Process id
    int bt;//Burst Time
    int at;//Arrival time
    //parameterized constructor to initialize the variable
    process(int pd,int bt,int at){
        this->pd=pd;
        this->bt=bt;
        this->at=at;
    }
};
//function to find the waiting time for all processes
void findWaitingTime(vector<process>& proc,int n,vector<int>& wt){
  vector<int> rt(n);
  //copy the burst time to rt[]
  for(int i=0;i<n;i++){
      rt[i]=proc[i].bt;
  }
  int complete=0,t=0,minm=INT_MAX;
  int shortest=0,finish_time;
  bool check=false;
  //process unitl all process gets completed
  while(complete!=n)
  {
      // Find process with minimum
        // remaining time among the
        // processes that arrives till the
        // current time`
      for(int j=0;j<n;j++){
          if((proc[j].at<=t)&&(rt[j]<minm)&&rt[j]>0){
              minm=rt[j];
              shortest=j;
              check=true;
          }
      }
      //if there are no process within the current time, increment the time
      if(check==false){
          t++;
          continue;
      }
      //reduce remaining time by 1
      rt[shortest]--;
      //update minimum
      minm=rt[shortest];
     
      if(minm==0)
        minm=INT_MAX;
      //if a process gets completely executed
      if(rt[shortest]==0){
          //increment complete
          complete++;
          check=false;
          //find finish time of current process
          finish_time=t+1;
          //calculate waiting time(wt=ft-bt-at)
          wt[shortest]=finish_time-proc[shortest].bt-proc[shortest].at;
          if(wt[shortest]<0)
            wt[shortest]=0;
      }
      //increment time
      t++;
  }
}
//function to calculate turn around time
void findTurnAroundTime(vector<process>& proc,int n,vector<int>& wt,vector<int>& tat){
    //calculating turnaround time by adding bt[i]+wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}
// Function to calculate average time
void findAvgTime(vector<process>& proc,int n){
    vector<int> wt(n);
    vector<int> tat(n);
    int total_wt=0;
    int total_tat=0;
    // Function to find waiting time of all
    // processes
    findWaitingTime(proc,n,wt);
    // Function to find turn around time for
    // all processes
    findTurnAroundTime(proc,n,wt,tat);
     // Display processes along with all
    // details
    cout << "Processes "
        << " Burst time "
        << " Waiting time "
        << " Turn around time\n";
 
    // Calculate total waiting time and
    // total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout<<" "<<proc[i].pd<<"\t\t"<<proc[i].bt<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<endl;
    }
 
    cout << "\nAverage waiting time = "
        << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
        << (float)total_tat / (float)n;

}
int main(){
     int n,pd1,bt1,at1;
     cout<<"Enter the number of process"<<endl;
     cin>>n;
     cout<<"Enter the process Id, Arrival time, Burst Time"<<endl;
     vector<process> proc;
     for(int i=0;i<n;i++)
     {
         cin>>pd1>>bt1>>at1;
         process item(pd1,bt1,at1);
         proc.push_back(item);
     }
     findAvgTime(proc,n);
     return 0;
}