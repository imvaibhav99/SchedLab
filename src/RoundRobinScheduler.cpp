#include "../include/RoundRobinScheduler.h"
#include <queue>
#include <utility>

RoundRobinScheduler::RoundRobinScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                                         int lastInst, int procCount, int q)
    : Scheduler(procs, lastInst, procCount), quantum(q) {}

void RoundRobinScheduler::schedule() {
    std::queue<std::pair<int, int>> q; // pair of process index and remaining time
    int j = 0;
    
    // Add first process if it arrives at time 0
    if (getArrivalTime(processes[j]) == 0) {
        q.push(std::make_pair(j, getServiceTime(processes[j])));
        j++;
    }
    
    int currentQuantum = quantum;
    
    for (int time = 0; time < lastInstant; time++) {
        if (!q.empty()) {
            int processIndex = q.front().first;
            q.front().second = q.front().second - 1;
            int remainingServiceTime = q.front().second;
            int arrivalTime = getArrivalTime(processes[processIndex]);
            int serviceTime = getServiceTime(processes[processIndex]);
            currentQuantum--;
            timeline[time][processIndex] = '*';
            
            // Add new arrivals
            while (j < processCount && getArrivalTime(processes[j]) == time + 1) {
                q.push(std::make_pair(j, getServiceTime(processes[j])));
                j++;
            }

            if (currentQuantum == 0 && remainingServiceTime == 0) {
                finishTime[processIndex] = time + 1;
                currentQuantum = quantum;
                q.pop();
            } else if (currentQuantum == 0 && remainingServiceTime != 0) {
                q.pop();
                q.push(std::make_pair(processIndex, remainingServiceTime));
                currentQuantum = quantum;
            } else if (currentQuantum != 0 && remainingServiceTime == 0) {
                finishTime[processIndex] = time + 1;
                q.pop();
                currentQuantum = quantum;
            }
        }
        
        // Add new arrivals
        while (j < processCount && getArrivalTime(processes[j]) == time + 1) {
            q.push(std::make_pair(j, getServiceTime(processes[j])));
            j++;
        }
    }
    
    calculateMetrics();
    fillInWaitTime();
} 