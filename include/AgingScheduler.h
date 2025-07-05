#ifndef AGING_SCHEDULER_H
#define AGING_SCHEDULER_H

#include "Scheduler.h"
#include <vector>
#include <queue>

class AgingScheduler : public Scheduler {
private:
    std::vector<int> priorities; // current priorities
    std::vector<int> initialPriorities; // initial priorities
    int quantum;
    int agingFactor;

public:
    AgingScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                   int lastInst, int procCount, int q);
    
    void schedule() override;
    
private:
    void ageProcesses();
    int getHighestPriorityProcess();
    void updatePriorities();
};

#endif // AGING_SCHEDULER_H 