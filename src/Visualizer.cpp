#include "../include/Visualizer.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <sstream>

Visualizer::Visualizer(bool colors) : useColors(colors), terminalWidth(80) {}

void Visualizer::printHeader(const std::string& title) {
    printSeparator('=', 80);
    std::string coloredTitle = useColors ? Colors::BOLD + Colors::CYAN + title + Colors::RESET : title;
    std::cout << std::string(40 - title.length()/2, ' ') << coloredTitle << std::endl;
    printSeparator('=', 80);
    std::cout << std::endl;
}

void Visualizer::printTimeline(const Scheduler& scheduler, int algorithm_index, 
                              const std::vector<std::tuple<std::string, int, int>>& processes) {
    const std::string ALGORITHMS[9] = {"", "FCFS", "RR-", "SPN", "SRT", "HRRN", "FB-1", "FB-2i", "AGING"};
    
    // Print algorithm name with color
    std::string algoName = ALGORITHMS[algorithm_index];
    if (algorithm_index == 2 || algorithm_index == 8) {
        // Add quantum for RR and Aging
        algoName += std::to_string(2); // This should be dynamic
    }
    
    std::string coloredAlgo = useColors ? Colors::BOLD + Colors::GREEN + algoName + Colors::RESET : algoName;
    std::cout << coloredAlgo << "  ";
    
    // Print time header
    for (int i = 0; i < scheduler.getTimeline().size(); i++) {
        std::string timeStr = std::to_string(i % 10);
        std::string coloredTime = useColors ? Colors::YELLOW + timeStr + Colors::RESET : timeStr;
        std::cout << coloredTime << " ";
    }
    std::cout << std::endl;
    
    // Print separator with unicode characters
    std::string separator = useColors ? Colors::BLUE : "";
    separator += TOP_LEFT;
    for (int i = 0; i < scheduler.getTimeline().size() * 2 + 3; i++) {
        separator += HORIZONTAL;
    }
    separator += TOP_RIGHT + (useColors ? Colors::RESET : "");
    std::cout << separator << std::endl;
    
    // Print timeline for each process
    for (int i = 0; i < processes.size(); i++) {
        std::string processName = Scheduler::getProcessName(processes[i]);
        std::string coloredName = useColors ? getProcessColor(i) + processName + Colors::RESET : processName;
        std::cout << coloredName << "     " << VERTICAL;
        
        for (int j = 0; j < scheduler.getTimeline().size(); j++) {
            char symbol = scheduler.getTimeline()[j][i];
            std::string coloredSymbol = getTimelineSymbol(symbol);
            std::cout << coloredSymbol << VERTICAL;
        }
        std::cout << std::endl;
    }
    
    // Print bottom separator
    std::string bottomSeparator = useColors ? Colors::BLUE : "";
    bottomSeparator += BOTTOM_LEFT;
    for (int i = 0; i < scheduler.getTimeline().size() * 2 + 3; i++) {
        bottomSeparator += HORIZONTAL;
    }
    bottomSeparator += BOTTOM_RIGHT + (useColors ? Colors::RESET : "");
    std::cout << bottomSeparator << std::endl << std::endl;
}

void Visualizer::printStats(const Scheduler& scheduler, int algorithm_index,
                           const std::vector<std::tuple<std::string, int, int>>& processes) {
    const std::string ALGORITHMS[9] = {"", "FCFS", "RR-", "SPN", "SRT", "HRRN", "FB-1", "FB-2i", "AGING"};
    
    std::string algoName = ALGORITHMS[algorithm_index];
    std::string coloredAlgo = useColors ? Colors::BOLD + Colors::GREEN + algoName + Colors::RESET : algoName;
    std::cout << coloredAlgo << std::endl;
    
    // Prepare table data
    std::vector<std::string> headers = {"Process", "Arrival", "Service", "Finish", "Turnaround", "NormTurn"};
    std::vector<std::vector<std::string>> rows;
    
    for (int i = 0; i < processes.size(); i++) {
        std::vector<std::string> row;
        row.push_back(Scheduler::getProcessName(processes[i]));
        row.push_back(std::to_string(Scheduler::getArrivalTime(processes[i])));
        row.push_back(std::to_string(Scheduler::getServiceTime(processes[i])));
        row.push_back(std::to_string(scheduler.getFinishTime()[i]));
        row.push_back(std::to_string(scheduler.getTurnAroundTime()[i]));
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << scheduler.getNormTurn()[i];
        row.push_back(ss.str());
        rows.push_back(row);
    }
    
    // Print table
    printTableHeader(headers);
    for (const auto& row : rows) {
        printTableRow(row);
    }
    printTableFooter();
    std::cout << std::endl;
}

void Visualizer::printGanttChart(const Scheduler& scheduler,
                                const std::vector<std::tuple<std::string, int, int>>& processes) {
    printBoxedText("Gantt Chart Visualization", Colors::MAGENTA);
    
    const auto& timeline = scheduler.getTimeline();
    int maxTime = timeline.size();
    
    // Print time scale
    std::cout << "Time: ";
    for (int i = 0; i < maxTime; i++) {
        if (i % 5 == 0) {
            std::string timeStr = std::to_string(i);
            std::string coloredTime = useColors ? Colors::YELLOW + timeStr + Colors::RESET : timeStr;
            std::cout << std::setw(5) << coloredTime;
        } else {
            std::cout << "     ";
        }
    }
    std::cout << std::endl;
    
    // Print process bars
    for (int i = 0; i < processes.size(); i++) {
        std::string processName = Scheduler::getProcessName(processes[i]);
        std::string coloredName = useColors ? getProcessColor(i) + processName + Colors::RESET : processName;
        std::cout << std::setw(8) << coloredName << " ";
        
        for (int j = 0; j < maxTime; j++) {
            char symbol = timeline[j][i];
            std::string coloredSymbol = getTimelineSymbol(symbol);
            std::cout << coloredSymbol;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Visualizer::printPerformanceMetrics(const Scheduler& scheduler,
                                        const std::vector<std::tuple<std::string, int, int>>& processes) {
    printBoxedText("Performance Metrics", Colors::CYAN);
    
    double cpuUtil = calculateCPUUtilization(scheduler);
    double avgWait = calculateAverageWaitingTime(scheduler);
    double avgTurn = calculateAverageTurnaroundTime(scheduler);
    double throughput = calculateThroughput(scheduler);
    
    // Print metrics with progress bars
    std::cout << "CPU Utilization: ";
    printProgressBar(cpuUtil * 100, 30);
    std::cout << " " << std::fixed << std::setprecision(1) << (cpuUtil * 100) << "%" << std::endl;
    
    std::cout << "Average Waiting Time: ";
    printProgressBar(std::min(avgWait / 10.0, 1.0), 30);
    std::cout << " " << std::fixed << std::setprecision(2) << avgWait << " units" << std::endl;
    
    std::cout << "Average Turnaround Time: ";
    printProgressBar(std::min(avgTurn / 15.0, 1.0), 30);
    std::cout << " " << std::fixed << std::setprecision(2) << avgTurn << " units" << std::endl;
    
    std::cout << "Throughput: ";
    printProgressBar(std::min(throughput / 2.0, 1.0), 30);
    std::cout << " " << std::fixed << std::setprecision(2) << throughput << " processes/unit" << std::endl;
    
    std::cout << std::endl;
}

void Visualizer::printProgressBar(double percentage, int width) {
    int filled = static_cast<int>(percentage * width / 100.0);
    std::string bar = "[";
    
    for (int i = 0; i < width; i++) {
        if (i < filled) {
            bar += useColors ? Colors::GREEN + "█" + Colors::RESET : "#";
        } else {
            bar += " ";
        }
    }
    bar += "]";
    std::cout << bar;
}

void Visualizer::printBoxedText(const std::string& text, const std::string& color) {
    std::string coloredText = useColors ? color + text + Colors::RESET : text;
    std::cout << TOP_LEFT << HORIZONTAL << " " << coloredText << " " << HORIZONTAL << TOP_RIGHT << std::endl;
}

void Visualizer::printSeparator(char character, int width) {
    std::string separator = useColors ? Colors::BLUE : "";
    for (int i = 0; i < width; i++) {
        separator += character;
    }
    separator += useColors ? Colors::RESET : "";
    std::cout << separator << std::endl;
}

std::string Visualizer::getProcessColor(int processIndex) {
    if (!useColors) return "";
    
    std::vector<std::string> colors = {Colors::RED, Colors::GREEN, Colors::YELLOW, 
                                      Colors::BLUE, Colors::MAGENTA, Colors::CYAN};
    return colors[processIndex % colors.size()];
}

std::string Visualizer::getTimelineSymbol(char symbol) {
    if (!useColors) return std::string(1, symbol);
    
    switch (symbol) {
        case '*': return Colors::BOLD + Colors::GREEN + "█" + Colors::RESET;  // Running
        case '.': return Colors::YELLOW + "░" + Colors::RESET;                // Waiting
        case ' ': return " ";                                                 // Idle
        default: return std::string(1, symbol);
    }
}

void Visualizer::printTableHeader(const std::vector<std::string>& headers) {
    std::string headerLine = useColors ? Colors::BLUE + TOP_LEFT : TOP_LEFT;
    for (size_t i = 0; i < headers.size(); i++) {
        headerLine += HORIZONTAL + HORIZONTAL + HORIZONTAL + HORIZONTAL;
        if (i < headers.size() - 1) headerLine += T_DOWN;
    }
    headerLine += TOP_RIGHT + (useColors ? Colors::RESET : "");
    std::cout << headerLine << std::endl;
    
    std::cout << VERTICAL;
    for (size_t i = 0; i < headers.size(); i++) {
        std::string coloredHeader = useColors ? Colors::BOLD + headers[i] + Colors::RESET : headers[i];
        std::cout << " " << std::setw(8) << coloredHeader << " " << VERTICAL;
    }
    std::cout << std::endl;
    
    std::string separatorLine = useColors ? Colors::BLUE + T_RIGHT : T_RIGHT;
    for (size_t i = 0; i < headers.size(); i++) {
        separatorLine += HORIZONTAL + HORIZONTAL + HORIZONTAL + HORIZONTAL;
        if (i < headers.size() - 1) separatorLine += CROSS;
    }
    separatorLine += T_LEFT + (useColors ? Colors::RESET : "");
    std::cout << separatorLine << std::endl;
}

void Visualizer::printTableRow(const std::vector<std::string>& cells) {
    std::cout << VERTICAL;
    for (size_t i = 0; i < cells.size(); i++) {
        std::cout << " " << std::setw(8) << cells[i] << " " << VERTICAL;
    }
    std::cout << std::endl;
}

void Visualizer::printTableFooter() {
    std::string footerLine = useColors ? Colors::BLUE + BOTTOM_LEFT : BOTTOM_LEFT;
    footerLine += HORIZONTAL + HORIZONTAL + HORIZONTAL + HORIZONTAL;
    footerLine += T_UP + HORIZONTAL + HORIZONTAL + HORIZONTAL + HORIZONTAL;
    footerLine += T_UP + HORIZONTAL + HORIZONTAL + HORIZONTAL + HORIZONTAL;
    footerLine += T_UP + HORIZONTAL + HORIZONTAL + HORIZONTAL + HORIZONTAL;
    footerLine += T_UP + HORIZONTAL + HORIZONTAL + HORIZONTAL + HORIZONTAL;
    footerLine += T_UP + HORIZONTAL + HORIZONTAL + HORIZONTAL + HORIZONTAL;
    footerLine += BOTTOM_RIGHT + (useColors ? Colors::RESET : "");
    std::cout << footerLine << std::endl;
}

double Visualizer::calculateCPUUtilization(const Scheduler& scheduler) {
    const auto& timeline = scheduler.getTimeline();
    int totalTime = timeline.size();
    int busyTime = 0;
    
    for (int time = 0; time < totalTime; time++) {
        bool cpuBusy = false;
        for (int process = 0; process < timeline[0].size(); process++) {
            if (timeline[time][process] == '*') {
                cpuBusy = true;
                break;
            }
        }
        if (cpuBusy) busyTime++;
    }
    
    return static_cast<double>(busyTime) / totalTime;
}

double Visualizer::calculateAverageWaitingTime(const Scheduler& scheduler) {
    const auto& turnAroundTimes = scheduler.getTurnAroundTime();
    const auto& timeline = scheduler.getTimeline();
    double totalWaitTime = 0;
    
    for (int i = 0; i < turnAroundTimes.size(); i++) {
        int serviceTime = Scheduler::getServiceTime(timeline[0].size() > i ? 
            std::make_tuple("", 0, 0) : std::make_tuple("", 0, 0)); // This needs fixing
        totalWaitTime += turnAroundTimes[i] - serviceTime;
    }
    
    return totalWaitTime / turnAroundTimes.size();
}

double Visualizer::calculateAverageTurnaroundTime(const Scheduler& scheduler) {
    const auto& turnAroundTimes = scheduler.getTurnAroundTime();
    return std::accumulate(turnAroundTimes.begin(), turnAroundTimes.end(), 0.0) / turnAroundTimes.size();
}

double Visualizer::calculateThroughput(const Scheduler& scheduler) {
    const auto& timeline = scheduler.getTimeline();
    int totalTime = timeline.size();
    int completedProcesses = 0;
    
    for (int i = 0; i < scheduler.getFinishTime().size(); i++) {
        if (scheduler.getFinishTime()[i] <= totalTime) {
            completedProcesses++;
        }
    }
    
    return static_cast<double>(completedProcesses) / totalTime;
} 