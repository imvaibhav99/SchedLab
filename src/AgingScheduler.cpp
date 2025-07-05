#include "../include/AgingScheduler.h"
#include <algorithm>

AgingScheduler::AgingScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                               int lastInst, int procCount, int q)
    : Scheduler(procs, lastInst, procCount), quantum(q), agingFactor(1) {
    
    // Initialize priorities (using service time as initial priority)
    priorities.resize(processCount);
    initialPriorities.resize(processCount);
    
    for (int i = 0; i < processCount; i++) {
        initialPriorities[i] = getServiceTime(processes[i]);
        priorities[i] = initialPriorities[i];
    }
}

void AgingScheduler::ageProcesses() {
    for (int i = 0; i < processCount; i++) {
        int arrivalTime = getArrivalTime(processes[i]);
        // Age processes that have arrived but not finished
        if (arrivalTime <= 0 && finishTime[i] == 0) {
            priorities[i] += agingFactor;
        }
    }
}

int AgingScheduler::getHighestPriorityProcess() {
    int highestPriority = -1;
    int selectedProcess = -1;
    
    for (int i = 0; i < processCount; i++) {
        int arrivalTime = getArrivalTime(processes[i]);
        // Only consider processes that have arrived and not finished
        if (arrivalTime <= 0 && finishTime[i] == 0) {
            if (priorities[i] > highestPriority) {
                highestPriority = priorities[i];
                selectedProcess = i;
            }
        }
    }
    
    return selectedProcess;
}

void AgingScheduler::updatePriorities() {
    for (int i = 0; i < processCount; i++) {
        if (finishTime[i] == 0) {
            // Reset current process priority to initial
            priorities[i] = initialPriorities[i];
        }
    }
}

void AgingScheduler::schedule() {
    int j = 0; // process index for arrivals
    std::vector<int> remainingTime(processCount, 0);
    
    // Initialize remaining time
    for (int i = 0; i < processCount; i++) {
        remainingTime[i] = getServiceTime(processes[i]);
    }
    
    for (int time = 0; time < lastInstant; time++) {
        // Add new arrivals
        while (j < processCount && getArrivalTime(processes[j]) == time) {
            j++;
        }
        
        // Age all ready processes
        ageProcesses();
        
        // Get highest priority process
        int processIndex = getHighestPriorityProcess();
        
        if (processIndex != -1) {
            int executionTime = std::min(quantum, remainingTime[processIndex]);
            
            // Execute the process
            for (int t = time; t < time + executionTime; t++) {
                timeline[t][processIndex] = '*';
            }
            
            remainingTime[processIndex] -= executionTime;
            
            if (remainingTime[processIndex] <= 0) {
                // Process finished
                finishTime[processIndex] = time + executionTime;
            }
            
            // Update priorities for next scheduling decision
            updatePriorities();
        }
    }
    
    calculateMetrics();
    fillInWaitTime();
} 