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

void printTimeline(const Scheduler& scheduler, int algorithm_index) {
    printAlgorithm(algorithm_index);
    
    // Print time header
    for (int i = 0; i < last_instant; i++) {
        cout << i % 10 << " ";
    }
    cout << endl;
    
    // Print separator
    for (int i = 0; i < last_instant * 2 + 5; i++) {
        cout << "-";
    }
    cout << endl;
    
    // Print timeline for each process
    for (int i = 0; i < process_count; i++) {
        cout << Scheduler::getProcessName(processes[i]) << "     |";
        for (int j = 0; j < last_instant; j++) {
            cout << scheduler.getTimeline()[j][i] << "|";
        }
        cout << endl;
    }
    
    // Print separator
    for (int i = 0; i < last_instant * 2 + 5; i++) {
        cout << "-";
    }
    cout << endl << endl;
}

void printStats(const Scheduler& scheduler, int algorithm_index) {
    printAlgorithm(algorithm_index);
    cout << endl;
    
    cout << "Process    ";
    for (int i = 0; i < process_count; i++) {
        cout << Scheduler::getProcessName(processes[i]) << "  ";
    }
    cout << endl;
    
    cout << "Arrival    ";
    for (int i = 0; i < process_count; i++) {
        cout << Scheduler::getArrivalTime(processes[i]) << "  ";
    }
    cout << endl;
    
    cout << "Service    ";
    for (int i = 0; i < process_count; i++) {
        cout << Scheduler::getServiceTime(processes[i]) << "  ";
    }
    cout << endl;
    
    cout << "Finish     ";
    for (int i = 0; i < process_count; i++) {
        cout << scheduler.getFinishTime()[i] << "  ";
    }
    cout << endl;
    
    cout << "Turnaround ";
    for (int i = 0; i < process_count; i++) {
        cout << scheduler.getTurnAroundTime()[i] << "  ";
    }
    cout << endl;
    
    cout << "NormTurn   ";
    for (int i = 0; i < process_count; i++) {
        cout << fixed << setprecision(2) << scheduler.getNormTurn()[i] << " ";
    }
    cout << endl << endl;
}

void execute_algorithm(char algorithm_id, int quantum, const string& operation) {
    try {
        AlgorithmType type = static_cast<AlgorithmType>(algorithm_id - '0');
        
        auto scheduler = SchedulerFactory::createScheduler(
            type, processes, last_instant, process_count, quantum
        );
        
        scheduler->schedule();
        
        if (operation == TRACE) {
            printTimeline(*scheduler, algorithm_id - '0');
        } else if (operation == SHOW_STATISTICS) {
            printStats(*scheduler, algorithm_id - '0');
        }
        
    } catch (const std::exception& e) {
        cerr << "Error executing algorithm " << algorithm_id << ": " << e.what() << endl;
    }
}

int main() {
    try {
        parse();
        
        for (const auto& algo : algorithms) {
            execute_algorithm(algo.first, algo.second, operation);
        }
        
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
} 