#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <tuple>
#include <string>
#include <memory>

class Scheduler {
protected:
    std::vector<std::tuple<std::string, int, int>> processes;
    std::vector<std::vector<char>> timeline;
    std::vector<int> finishTime;
    std::vector<int> turnAroundTime;
    std::vector<float> normTurn;
    int lastInstant;
    int processCount;

public:
    Scheduler(const std::vector<std::tuple<std::string, int, int>>& procs, int lastInst, int procCount);
    virtual ~Scheduler() = default;
    
    // Pure virtual function that each algorithm must implement
    virtual void schedule() = 0;
    
    // Common utility functions
    void fillInWaitTime();
    void calculateMetrics();
    
    // Getters for results
    const std::vector<std::vector<char>>& getTimeline() const { return timeline; }
    const std::vector<int>& getFinishTime() const { return finishTime; }
    const std::vector<int>& getTurnAroundTime() const { return turnAroundTime; }
    const std::vector<float>& getNormTurn() const { return normTurn; }
    
    // Utility functions
    static std::string getProcessName(const std::tuple<std::string, int, int>& process);
    static int getArrivalTime(const std::tuple<std::string, int, int>& process);
    static int getServiceTime(const std::tuple<std::string, int, int>& process);
};

#endif // SCHEDULER_H 