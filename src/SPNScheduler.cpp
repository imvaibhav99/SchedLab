#include "../include/SPNScheduler.h"
#include <queue>
#include <algorithm>

SPNScheduler::SPNScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                           int lastInst, int procCount)
    : Scheduler(procs, lastInst, procCount) {}

void SPNScheduler::schedule() {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
                       std::greater<std::pair<int, int>>> pq; // pair of service time and index
    int j = 0;
    
    for (int i = 0; i < lastInstant; i++) {
        // Add all processes that have arrived by time i
        while (j < processCount && getArrivalTime(processes[j]) <= i) {
            pq.push(std::make_pair(getServiceTime(processes[j]), j));
            j++;
        }
        
        if (!pq.empty()) {
            int processIndex = pq.top().second;
            int arrivalTime = getArrivalTime(processes[processIndex]);
            int serviceTime = getServiceTime(processes[processIndex]);
            pq.pop();

            // Fill waiting time (from arrival to current time)
            int temp = arrivalTime;
            for (; temp < i; temp++) {
                timeline[temp][processIndex] = '.';
            }

            // Fill execution time
            temp = i;
            for (; temp < i + serviceTime; temp++) {
                timeline[temp][processIndex] = '*';
            }

            finishTime[processIndex] = i + serviceTime;
            i = temp - 1; // Continue from where we left off
        }
    }
    
    calculateMetrics();
} 