#!/bin/bash

echo "🎨 CPU Scheduling Algorithms - Visual Demo"
echo "=========================================="
echo ""

# Build the visual version
echo "🔨 Building visual version..."
make -f Makefile_visual clean > /dev/null 2>&1
make -f Makefile_visual > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    echo ""
    
    echo "🚀 Running FCFS Algorithm Demo..."
    echo "================================="
    echo -e "trace\n1\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual
    echo ""
    
    echo "⏱️  Running Round Robin Algorithm Demo (Quantum=2)..."
    echo "=================================================="
    echo -e "trace\n2-2\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual
    echo ""
    
    echo "📊 Running Statistics Mode Demo..."
    echo "================================="
    echo -e "stats\n1\n20\n5\nA,0,3\nB,1,6\nC,3,4\nD,5,5\nE,7,2" | ./lab4_visual
    echo ""
    
    echo "🎯 Visual Features Showcase:"
    echo "============================"
    echo "✅ Color-coded process names"
    echo "✅ Enhanced timeline with Unicode borders"
    echo "✅ Gantt chart visualization"
    echo "✅ Performance metrics with progress bars"
    echo "✅ Formatted statistics tables"
    echo "✅ Professional headers and separators"
    echo ""
    
    echo "💡 Usage Examples:"
    echo "=================="
    echo "  # Run with test file"
    echo "  ./lab4_visual < testcases/01a-input.txt"
    echo ""
    echo "  # Run with custom input"
    echo "  echo -e \"trace\\n1\\n20\\n5\\nA,0,3\\nB,1,6\\nC,3,4\\nD,5,5\\nE,7,2\" | ./lab4_visual"
    echo ""
    echo "  # Run statistics mode"
    echo "  echo -e \"stats\\n1\\n20\\n5\\nA,0,3\\nB,1,6\\nC,3,4\\nD,5,5\\nE,7,2\" | ./lab4_visual"
    echo ""
    
else
    echo "❌ Build failed! Please check the error messages above."
    exit 1
fi 