#ifndef SRT_SCHEDULER_H
#define SRT_SCHEDULER_H

#include "Scheduler.h"
#include <queue>

class SRTScheduler : public Scheduler {
public:
    SRTScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                 int lastInst, int procCount);
    
    void schedule() override;
};

#endif // SRT_SCHEDULER_H 