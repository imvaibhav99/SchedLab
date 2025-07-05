#ifndef FEEDBACK_SCHEDULER_H
#define FEEDBACK_SCHEDULER_H

#include "Scheduler.h"
#include <vector>
#include <queue>

class FeedbackScheduler : public Scheduler {
private:
    std::vector<std::queue<std::pair<int, int>>> queues; // priority queues
    std::vector<int> quantum; // quantum for each priority level
    int maxPriorityLevels;
    bool useVariableQuantum;

public:
    FeedbackScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                      int lastInst, int procCount, bool variableQuantum = false);
    
    void schedule() override;
    
private:
    int getQuantum(int priorityLevel);
    void addToQueue(int processIndex, int priorityLevel);
    std::pair<int, int> getNextProcess();
};

#endif // FEEDBACK_SCHEDULER_H 