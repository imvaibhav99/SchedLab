#ifndef HRRN_SCHEDULER_H
#define HRRN_SCHEDULER_H

#include "Scheduler.h"
#include <vector>
#include <algorithm>

class HRRNScheduler : public Scheduler {
public:
    HRRNScheduler(const std::vector<std::tuple<std::string, int, int>>& procs, 
                  int lastInst, int procCount);
    
    void schedule() override;
    
private:
    double calculateResponseRatio(int waitTime, int serviceTime);
    std::tuple<std::string, double, int> findHighestResponseRatio(int currentTime);
};

#endif // HRRN_SCHEDULER_H 