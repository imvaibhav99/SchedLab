#include "../include/HRRNScheduler.h"
#include <vector>
#include <algorithm>

HRRNScheduler::HRRNScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                             int lastInst, int procCount)
    : Scheduler(procs, lastInst, procCount) {}

double HRRNScheduler::calculateResponseRatio(int waitTime, int serviceTime) {
    return (waitTime + serviceTime) * 1.0 / serviceTime;
}

std::tuple<std::string, double, int> HRRNScheduler::findHighestResponseRatio(int currentTime) {
    std::vector<std::tuple<std::string, double, int>> candidates;
    
    for (int i = 0; i < processCount; i++) {
        int arrivalTime = getArrivalTime(processes[i]);
        int serviceTime = getServiceTime(processes[i]);
        
        // Only consider processes that have arrived and not finished
        if (arrivalTime <= currentTime && finishTime[i] == 0) {
            int waitTime = currentTime - arrivalTime;
            double responseRatio = calculateResponseRatio(waitTime, serviceTime);
            candidates.push_back(std::make_tuple(getProcessName(processes[i]), responseRatio, i));
        }
    }
    
    if (candidates.empty()) {
        return std::make_tuple("", 0.0, -1);
    }
    
    // Sort by response ratio in descending order
    std::sort(candidates.begin(), candidates.end(), 
              [](const std::tuple<std::string, double, int>& a, 
                 const std::tuple<std::string, double, int>& b) {
                  return std::get<1>(a) > std::get<1>(b);
              });
    
    return candidates[0];
}

void HRRNScheduler::schedule() {
    int currentTime = 0;
    int completedProcesses = 0;
    
    while (completedProcesses < processCount) {
        auto result = findHighestResponseRatio(currentTime);
        std::string processName = std::get<0>(result);
        int processIndex = std::get<2>(result);
        
        if (processIndex == -1) {
            // No process available, advance time
            currentTime++;
            continue;
        }
        
        int arrivalTime = getArrivalTime(processes[processIndex]);
        int serviceTime = getServiceTime(processes[processIndex]);
        
        // Fill waiting time
        for (int t = arrivalTime; t < currentTime; t++) {
            timeline[t][processIndex] = '.';
        }
        
        // Fill execution time
        for (int t = currentTime; t < currentTime + serviceTime; t++) {
            timeline[t][processIndex] = '*';
        }
        
        finishTime[processIndex] = currentTime + serviceTime;
        currentTime += serviceTime;
        completedProcesses++;
    }
    
    calculateMetrics();
} 