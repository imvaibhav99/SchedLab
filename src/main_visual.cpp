#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include <memory>
#include <unordered_map>
#include <iomanip>
#include <stdexcept>

#include "../include/SchedulerFactory.h"
#include "../include/Scheduler.h"
#include "../include/Visualizer.h"

using namespace std;

// Global constants
const string TRACE = "trace";
const string SHOW_STATISTICS = "stats";
const string ALGORITHMS[9] = {"", "FCFS", "RR-", "SPN", "SRT", "HRRN", "FB-1", "FB-2i", "AGING"};

// Global variables (keeping for compatibility with existing input format)
string operation;
int last_instant, process_count;
vector<pair<char, int>> algorithms;
vector<tuple<string, int, int>> processes;
unordered_map<string, int> processToIndex;

// Global visualizer
Visualizer visualizer(true); // Enable colors

void parse_algorithms(const string& algorithm_chunk) {
    stringstream stream(algorithm_chunk);
    while (stream.good()) {
        string temp_str;
        getline(stream, temp_str, ',');
        stringstream ss(temp_str);
        getline(ss, temp_str, '-');
        char algorithm_id = temp_str[0];
        getline(ss, temp_str, '-');
        int quantum = temp_str.size() >= 1 ? stoi(temp_str) : -1;
        algorithms.push_back(make_pair(algorithm_id, quantum));
    }
}

void parse_processes() {
    string process_chunk, process_name;
    int process_arrival_time, process_service_time;
    
    for (int i = 0; i < process_count; i++) {
        cin >> process_chunk;
        
        stringstream stream(process_chunk);
        string temp_str;
        getline(stream, temp_str, ',');
        process_name = temp_str;
        getline(stream, temp_str, ',');
        process_arrival_time = stoi(temp_str);
        getline(stream, temp_str, ',');
        process_service_time = stoi(temp_str);
        
        processes.push_back(make_tuple(process_name, process_arrival_time, process_service_time));
        processToIndex[process_name] = i;
    }
}

void parse() {
    string algorithm_chunk;
    cin >> operation >> algorithm_chunk >> last_instant >> process_count;
    parse_algorithms(algorithm_chunk);
    parse_processes();
}

void printAlgorithm(int algorithm_index) {
    cout << ALGORITHMS[algorithm_index];
    if (algorithm_index == 2 || algorithm_index == 8) {
        cout << algorithms[algorithm_index - 1].second;
    }
    cout << "  ";
}

void execute_algorithm(char algorithm_id, int quantum, const string& operation) {
    try {
        AlgorithmType type = static_cast<AlgorithmType>(algorithm_id - '0');
        
        auto scheduler = SchedulerFactory::createScheduler(
            type, processes, last_instant, process_count, quantum
        );
        
        scheduler->schedule();
        
        // Print header for this algorithm
        string algoName = ALGORITHMS[algorithm_id - '0'];
        if (algorithm_id == '2' || algorithm_id == '8') {
            algoName += "-" + to_string(quantum);
        }
        visualizer.printHeader("Algorithm: " + algoName);
        
        if (operation == TRACE) {
            // Enhanced timeline visualization
            visualizer.printTimeline(*scheduler, algorithm_id - '0', processes);
            
            // Add Gantt chart visualization
            visualizer.printGanttChart(*scheduler, processes);
            
            // Add performance metrics
            visualizer.printPerformanceMetrics(*scheduler, processes);
            
        } else if (operation == SHOW_STATISTICS) {
            // Enhanced statistics table
            visualizer.printStats(*scheduler, algorithm_id - '0', processes);
            
            // Add performance metrics
            visualizer.printPerformanceMetrics(*scheduler, processes);
        }
        
    } catch (const std::exception& e) {
        cerr << "Error executing algorithm " << algorithm_id << ": " << e.what() << endl;
    }
}

int main() {
    try {
        // Print welcome header
        visualizer.printHeader("CPU Scheduling Algorithms - Enhanced Visualization");
        
        // Print input summary
        visualizer.printBoxedText("Input Summary", Colors::GREEN);
        cout << "Operation: " << (operation.empty() ? "trace" : operation) << endl;
        cout << "Last Instant: " << last_instant << endl;
        cout << "Process Count: " << process_count << endl;
        cout << endl;
        
        parse();
        
        // Print process information
        visualizer.printBoxedText("Process Information", Colors::YELLOW);
        for (int i = 0; i < processes.size(); i++) {
            string processName = Scheduler::getProcessName(processes[i]);
            int arrivalTime = Scheduler::getArrivalTime(processes[i]);
            int serviceTime = Scheduler::getServiceTime(processes[i]);
            
            string coloredName = visualizer.getProcessColor(i) + processName + Colors::RESET;
            cout << "Process " << coloredName << ": Arrival=" << arrivalTime 
                 << ", Service=" << serviceTime << endl;
        }
        cout << endl;
        
        // Execute each algorithm
        for (const auto& algo : algorithms) {
            execute_algorithm(algo.first, algo.second, operation);
        }
        
        // Print summary
        visualizer.printBoxedText("Simulation Complete", Colors::GREEN);
        cout << "All algorithms have been executed successfully!" << endl;
        cout << "Use --help for more options." << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
} 