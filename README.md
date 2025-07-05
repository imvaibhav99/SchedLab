# 🎨 SchedLab - CPU Scheduling Algorithms with Visualization

A modern implementation of CPU scheduling algorithms featuring beautiful visualizations and comprehensive performance metrics.

## ✨ Features

- **7 Complete Algorithms**: FCFS, Round Robin, SPN, SRT, HRRN, Feedback, Aging
- **Visual Output**: Color-coded timelines, Gantt charts, progress bars
- **Performance Metrics**: CPU utilization, waiting time, turnaround time, throughput
- **Modern C++**: Object-oriented design with smart pointers and exception handling

## 🚀 Quick Start

```bash
# Build the project
make -f Makefile_visual

# Run demo
./demo_visual.sh

# Run with test file
./lab4_visual < testcases/01a-input.txt
```

## 📝 Usage

### Input Format
```
Line 1: "trace" or "stats"
Line 2: Algorithm list (e.g., "1" for FCFS, "2-4" for RR with quantum=4)
Line 3: Last instant for simulation
Line 4: Number of processes
Line 5+: Process descriptions (name,arrival_time,service_time)
```

### Algorithm Codes
- `1` - FCFS (First Come First Serve)
- `2-q` - Round Robin with quantum q
- `3` - SPN (Shortest Process Next)
- `4` - SRT (Shortest Remaining Time)
- `5` - HRRN (Highest Response Ratio Next)
- `6` - FB-1 (Feedback with q=1)
- `7` - FB-2i (Feedback with q=2^i)
- `8-q` - Aging with quantum q

## 🎯 Example

```bash
# Run FCFS algorithm
echo -e "trace\n1\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual
```

## 📁 Project Structure

```
SchedLab/
├── include/          # Header files
├── src/             # Source files
├── testcases/       # Test input files
├── lab4_visual      # Main executable
├── Makefile_visual  # Build system
└── demo_visual.sh   # Demo script
```

## 🔧 Build Commands

```bash
make -f Makefile_visual        # Build
make -f Makefile_visual clean  # Clean
make -f Makefile_visual test   # Run tests
```

---

**SchedLab** - Where algorithms meet visualization! 🚀



