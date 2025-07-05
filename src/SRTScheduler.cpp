#include "../include/SRTScheduler.h"
#include <queue>
#include <algorithm>

SRTScheduler::SRTScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                           int lastInst, int procCount)
    : Scheduler(procs, lastInst, procCount) {}

void SRTScheduler::schedule() {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
                       std::greater<std::pair<int, int>>> pq; // pair of remaining time and index
    int j = 0;
    
    for (int i = 0; i < lastInstant; i++) {
        // Add new arrivals at time i
        while (j < processCount && getArrivalTime(processes[j]) == i) {
            pq.push(std::make_pair(getServiceTime(processes[j]), j));
            j++;
        }
        
        if (!pq.empty()) {
            int processIndex = pq.top().second;
            int remainingTime = pq.top().first;
            pq.pop();
            
            // Execute for 1 time unit
            timeline[i][processIndex] = '*';
            
            if (remainingTime == 1) {
                // Process finished
                finishTime[processIndex] = i + 1;
            } else {
                // Process still has remaining time
                pq.push(std::make_pair(remainingTime - 1, processIndex));
            }
        }
    }
    
    calculateMetrics();
    fillInWaitTime();
} 