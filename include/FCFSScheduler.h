#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "Scheduler.h"

class FCFSScheduler : public Scheduler {
public:
    FCFSScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                  int lastInst, int procCount);
    
    void schedule() override;
};

#endif // FCFS_SCHEDULER_H 