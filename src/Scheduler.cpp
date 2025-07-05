#include "../include/Scheduler.h"
#include <algorithm>

Scheduler::Scheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                     int lastInst, int procCount) 
    : processes(procs), lastInstant(lastInst), processCount(procCount) {
    
    // Initialize result vectors
    finishTime.resize(processCount);
    turnAroundTime.resize(processCount);
    normTurn.resize(processCount);
    timeline.resize(lastInstant);
    
    // Initialize timeline with spaces
    for (auto& row : timeline) {
        row.resize(processCount, ' ');
    }
}

void Scheduler::fillInWaitTime() {
    for (int i = 0; i < processCount; i++) {
        int arrivalTime = getArrivalTime(processes[i]);
        for (int k = arrivalTime; k < finishTime[i]; k++) {
            if (timeline[k][i] != '*') {
                timeline[k][i] = '.';
            }
        }
    }
}

void Scheduler::calculateMetrics() {
    for (int i = 0; i < processCount; i++) {
        int arrivalTime = getArrivalTime(processes[i]);
        int serviceTime = getServiceTime(processes[i]);
        
        turnAroundTime[i] = finishTime[i] - arrivalTime;
        normTurn[i] = static_cast<float>(turnAroundTime[i]) / serviceTime;
    }
}

std::string Scheduler::getProcessName(const std::tuple<std::string, int, int>& process) {
    return std::get<0>(process);
}

int Scheduler::getArrivalTime(const std::tuple<std::string, int, int>& process) {
    return std::get<1>(process);
}

int Scheduler::getServiceTime(const std::tuple<std::string, int, int>& process) {
    return std::get<2>(process);
} 