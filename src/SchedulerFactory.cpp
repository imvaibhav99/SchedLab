#include "../include/SchedulerFactory.h"
#include "../include/FCFSScheduler.h"
#include "../include/RoundRobinScheduler.h"

std::unique_ptr<Scheduler> SchedulerFactory::createScheduler(
    AlgorithmType type,
    const std::vector<std::tuple<std::string, int, int>>& processes,
    int lastInstant,
    int processCount,
    int quantum) {
    
    switch (type) {
        case AlgorithmType::FCFS:
            return std::make_unique<FCFSScheduler>(processes, lastInstant, processCount);
        
        case AlgorithmType::ROUND_ROBIN:
            if (quantum <= 0) {
                throw std::invalid_argument("Round Robin requires a positive quantum value");
            }
            return std::make_unique<RoundRobinScheduler>(processes, lastInstant, processCount, quantum);
        
        // TODO: Add other algorithms as they are implemented
        case AlgorithmType::SPN:
        case AlgorithmType::SRT:
        case AlgorithmType::HRRN:
        case AlgorithmType::FB_1:
        case AlgorithmType::FB_2I:
        case AlgorithmType::AGING:
            throw std::runtime_error("Algorithm not yet implemented");
        
        default:
            throw std::invalid_argument("Unknown algorithm type");
    }
} 