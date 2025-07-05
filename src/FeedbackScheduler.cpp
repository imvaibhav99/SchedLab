#include "../include/FeedbackScheduler.h"
#include <algorithm>

FeedbackScheduler::FeedbackScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                                     int lastInst, int procCount, bool variableQuantum)
    : Scheduler(procs, lastInst, procCount), maxPriorityLevels(5), useVariableQuantum(variableQuantum) {
    
    // Initialize queues and quantum
    queues.resize(maxPriorityLevels);
    quantum.resize(maxPriorityLevels);
    
    if (useVariableQuantum) {
        // FB-2i: quantum = 2^i for priority level i
        for (int i = 0; i < maxPriorityLevels; i++) {
            quantum[i] = 1 << i; // 2^i
        }
    } else {
        // FB-1: all queues have quantum = 1
        for (int i = 0; i < maxPriorityLevels; i++) {
            quantum[i] = 1;
        }
    }
}

int FeedbackScheduler::getQuantum(int priorityLevel) {
    if (priorityLevel >= 0 && priorityLevel < maxPriorityLevels) {
        return quantum[priorityLevel];
    }
    return 1; // default quantum
}

void FeedbackScheduler::addToQueue(int processIndex, int priorityLevel) {
    if (priorityLevel >= 0 && priorityLevel < maxPriorityLevels) {
        queues[priorityLevel].push(std::make_pair(processIndex, getServiceTime(processes[processIndex])));
    }
}

std::pair<int, int> FeedbackScheduler::getNextProcess() {
    for (int i = 0; i < maxPriorityLevels; i++) {
        if (!queues[i].empty()) {
            auto process = queues[i].front();
            queues[i].pop();
            return process;
        }
    }
    return std::make_pair(-1, -1); // no process available
}

void FeedbackScheduler::schedule() {
    int j = 0; // process index for arrivals
    std::vector<int> remainingTime(processCount, 0);
    std::vector<int> currentPriority(processCount, 0);
    
    // Initialize remaining time
    for (int i = 0; i < processCount; i++) {
        remainingTime[i] = getServiceTime(processes[i]);
    }
    
    for (int time = 0; time < lastInstant; time++) {
        // Add new arrivals
        while (j < processCount && getArrivalTime(processes[j]) == time) {
            addToQueue(j, 0); // Start at highest priority
            j++;
        }
        
        auto processInfo = getNextProcess();
        int processIndex = processInfo.first;
        int serviceTime = processInfo.second;
        
        if (processIndex != -1) {
            int currentQuantum = getQuantum(currentPriority[processIndex]);
            int executionTime = std::min(currentQuantum, remainingTime[processIndex]);
            
            // Execute the process
            for (int t = time; t < time + executionTime; t++) {
                timeline[t][processIndex] = '*';
            }
            
            remainingTime[processIndex] -= executionTime;
            
            if (remainingTime[processIndex] > 0) {
                // Process not finished, move to lower priority
                currentPriority[processIndex] = std::min(currentPriority[processIndex] + 1, maxPriorityLevels - 1);
                addToQueue(processIndex, currentPriority[processIndex]);
            } else {
                // Process finished
                finishTime[processIndex] = time + executionTime;
            }
        }
    }
    
    calculateMetrics();
    fillInWaitTime();
} 