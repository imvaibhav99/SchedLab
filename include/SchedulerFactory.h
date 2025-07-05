#ifndef SCHEDULER_FACTORY_H
#define SCHEDULER_FACTORY_H

#include <memory>
#include <vector>
#include <tuple>
#include <string>
#include "Scheduler.h"

enum class AlgorithmType {
    FCFS = 1,
    ROUND_ROBIN = 2,
    SPN = 3,
    SRT = 4,
    HRRN = 5,
    FB_1 = 6,
    FB_2I = 7,
    AGING = 8
};

class SchedulerFactory {
public:
    static std::unique_ptr<Scheduler> createScheduler(
        AlgorithmType type,
        const std::vector<std::tuple<std::string, int, int>>& processes,
        int lastInstant,
        int processCount,
        int quantum = -1
    );
};

#endif // SCHEDULER_FACTORY_H 