#include "../include/SchedulerFactory.h"
#include "../include/FCFSScheduler.h"
#include "../include/RoundRobinScheduler.h"
#include "../include/SPNScheduler.h"
#include "../include/SRTScheduler.h"
#include "../include/HRRNScheduler.h"
#include "../include/FeedbackScheduler.h"
#include "../include/AgingScheduler.h"

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
            return std::make_unique<SPNScheduler>(processes, lastInstant, processCount);
        
        case AlgorithmType::SRT:
            return std::make_unique<SRTScheduler>(processes, lastInstant, processCount);
        
        case AlgorithmType::HRRN:
            return std::make_unique<HRRNScheduler>(processes, lastInstant, processCount);
        
        case AlgorithmType::FB_1:
            return std::make_unique<FeedbackScheduler>(processes, lastInstant, processCount, false);
        
        case AlgorithmType::FB_2I:
            return std::make_unique<FeedbackScheduler>(processes, lastInstant, processCount, true);
        
        case AlgorithmType::AGING:
            if (quantum <= 0) {
                throw std::invalid_argument("Aging requires a positive quantum value");
            }
            return std::make_unique<AgingScheduler>(processes, lastInstant, processCount, quantum);
        
        default:
            throw std::invalid_argument("Unknown algorithm type");
    }
} 