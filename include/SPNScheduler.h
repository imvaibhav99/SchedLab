#ifndef SPN_SCHEDULER_H
#define SPN_SCHEDULER_H

#include "Scheduler.h"
#include <queue>

class SPNScheduler : public Scheduler {
public:
    SPNScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                 int lastInst, int procCount);
    
    void schedule() override;
};

#endif // SPN_SCHEDULER_H 