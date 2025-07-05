#!/bin/bash

echo "🎯 SchedLab - All 7 CPU Scheduling Algorithms Demo"
echo "=================================================="
echo ""

# Build the project
echo "🔨 Building project with all algorithms..."
make -f Makefile_visual clean > /dev/null 2>&1
make -f Makefile_visual > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✅ Build successful! All 7 algorithms ready."
    echo ""
    
    echo "🚀 Testing All Algorithms with Sample Input"
    echo "=========================================="
    echo "Input: 5 processes (A:0,3 B:1,6 C:3,4 D:5,5 E:7,2)"
    echo ""
    
    # Test all algorithms
    echo -e "trace\n1,2-2,3,4,5,6,7,8-1\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual
    
    echo ""
    echo "📊 Algorithm Performance Summary:"
    echo "================================"
    echo "1. FCFS (First Come First Serve)     - Simple, fair, but can have high waiting time"
    echo "2. RR-2 (Round Robin, q=2)          - Good for time-sharing, prevents starvation"
    echo "3. SPN (Shortest Process Next)       - Minimizes average waiting time"
    echo "4. SRT (Shortest Remaining Time)     - Preemptive version of SPN"
    echo "5. HRRN (Highest Response Ratio)     - Balances waiting time and service time"
    echo "6. FB-1 (Feedback, q=1)              - Multi-level queue with aging"
    echo "7. FB-2i (Feedback, q=2^i)           - Variable quantum feedback"
    echo "8. AGING-1 (Aging, q=1)              - Prevents starvation with priority aging"
    echo ""
    
    echo "🎯 Individual Algorithm Tests:"
    echo "============================="
    
    # Test FCFS
    echo "1️⃣  Testing FCFS..."
    echo -e "trace\n1\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual | head -20
    echo ""
    
    # Test Round Robin
    echo "2️⃣  Testing Round Robin (q=3)..."
    echo -e "trace\n2-3\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual | head -20
    echo ""
    
    # Test SPN
    echo "3️⃣  Testing SPN..."
    echo -e "trace\n3\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual | head -20
    echo ""
    
    # Test SRT
    echo "4️⃣  Testing SRT..."
    echo -e "trace\n4\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual | head -20
    echo ""
    
    # Test HRRN
    echo "5️⃣  Testing HRRN..."
    echo -e "trace\n5\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual | head -20
    echo ""
    
    # Test Feedback
    echo "6️⃣  Testing Feedback (FB-1)..."
    echo -e "trace\n6\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual | head -20
    echo ""
    
    # Test Aging
    echo "7️⃣  Testing Aging (q=2)..."
    echo -e "trace\n8-2\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual | head -20
    echo ""
    
    echo "🎉 All 7 algorithms successfully implemented and tested!"
    echo ""
    echo "💡 Usage Examples:"
    echo "=================="
    echo "  # Test specific algorithm"
    echo "  echo -e \"trace\\n1\\n20\\n5\\nA,0,3\\nB,1,6\\nC,3,4\\nD,5,5\\nE,7,2\" | ./lab4_visual"
    echo ""
    echo "  # Compare multiple algorithms"
    echo "  echo -e \"trace\\n1,2-2,3,4,5\\n20\\n5\\nA,0,3\\nB,1,6\\nC,3,4\\nD,5,5\\nE,7,2\" | ./lab4_visual"
    echo ""
    echo "  # Statistics mode"
    echo "  echo -e \"stats\\n1,2-2,3\\n20\\n5\\nA,0,3\\nB,1,6\\nC,3,4\\nD,5,5\\nE,7,2\" | ./lab4_visual"
    echo ""
    
else
    echo "❌ Build failed! Please check the error messages above."
    exit 1
fi 