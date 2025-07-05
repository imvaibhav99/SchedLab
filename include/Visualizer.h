#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <string>
#include <vector>
#include <tuple>
#include <iomanip>
#include <iostream>
#include "Scheduler.h"

// ANSI Color Codes
namespace Colors {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string BOLD = "\033[1m";
    const std::string UNDERLINE = "\033[4m";
    
    // Background colors
    const std::string BG_RED = "\033[41m";
    const std::string BG_GREEN = "\033[42m";
    const std::string BG_YELLOW = "\033[43m";
    const std::string BG_BLUE = "\033[44m";
    const std::string BG_MAGENTA = "\033[45m";
    const std::string BG_CYAN = "\033[46m";
}

class Visualizer {
private:
    bool useColors;
    int terminalWidth;
    
    // Unicode box drawing characters
    const std::string TOP_LEFT = "╔";
    const std::string TOP_RIGHT = "╗";
    const std::string BOTTOM_LEFT = "╚";
    const std::string BOTTOM_RIGHT = "╝";
    const std::string HORIZONTAL = "═";
    const std::string VERTICAL = "║";
    const std::string T_DOWN = "╦";
    const std::string T_UP = "╩";
    const std::string T_RIGHT = "╠";
    const std::string T_LEFT = "╣";
    const std::string CROSS = "╬";

public:
    Visualizer(bool colors = true);
    
    // Main visualization methods
    void printHeader(const std::string& title);
    void printTimeline(const Scheduler& scheduler, int algorithm_index, 
                      const std::vector<std::tuple<std::string, int, int>>& processes);
    void printStats(const Scheduler& scheduler, int algorithm_index,
                   const std::vector<std::tuple<std::string, int, int>>& processes);
    void printGanttChart(const Scheduler& scheduler,
                        const std::vector<std::tuple<std::string, int, int>>& processes);
    void printPerformanceMetrics(const Scheduler& scheduler,
                                const std::vector<std::tuple<std::string, int, int>>& processes);
    void printComparisonTable(const std::vector<std::unique_ptr<Scheduler>>& schedulers,
                             const std::vector<std::string>& algorithmNames);
    
    // Utility methods
    void printProgressBar(double percentage, int width = 50);
    void printBoxedText(const std::string& text, const std::string& color = Colors::CYAN);
    void printSeparator(char character = '=', int width = 80);
    std::string getProcessColor(int processIndex);
    std::string getTimelineSymbol(char symbol);
    
private:
    void printTableHeader(const std::vector<std::string>& headers);
    void printTableRow(const std::vector<std::string>& cells);
    void printTableFooter();
    double calculateCPUUtilization(const Scheduler& scheduler);
    double calculateAverageWaitingTime(const Scheduler& scheduler);
    double calculateAverageTurnaroundTime(const Scheduler& scheduler);
    double calculateThroughput(const Scheduler& scheduler);
};

#endif // VISUALIZER_H 