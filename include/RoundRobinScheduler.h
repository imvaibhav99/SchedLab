#ifndef ROUND_ROBIN_SCHEDULER_H
#define ROUND_ROBIN_SCHEDULER_H

#include "Scheduler.h"
#include <queue>
#include <utility>

class RoundRobinScheduler : public Scheduler {
private:
    int quantum;

public:
    RoundRobinScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                        int lastInst, int procCount, int q);
    
    void schedule() override;
};

#endif // ROUND_ROBIN_SCHEDULER_H 