#include "../include/FCFSScheduler.h"
#include <algorithm>

FCFSScheduler::FCFSScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                             int lastInst, int procCount)
    : Scheduler(procs, lastInst, procCount) {}

void FCFSScheduler::schedule() {
    int time = getArrivalTime(processes[0]);
    
    for (int i = 0; i < processCount; i++) {
        int processIndex = i;
        int arrivalTime = getArrivalTime(processes[i]);
        int serviceTime = getServiceTime(processes[i]);

        finishTime[processIndex] = time + serviceTime;
        
        // Fill timeline for this process
        for (int j = time; j < finishTime[processIndex]; j++) {
            timeline[j][processIndex] = '*';
        }
        
        // Fill waiting time
        for (int j = arrivalTime; j < time; j++) {
            timeline[j][processIndex] = '.';
        }
        
        time += serviceTime;
    }
    
    calculateMetrics();
} 