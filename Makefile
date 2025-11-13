# Cross-Platform High-Performance Order Book Makefile
# Works on macOS (Intel & Apple Silicon) and Linux

CXX = g++
CXXFLAGS = -std=c++20 -O3 -DNDEBUG -Wall -Wextra -pthread
LDFLAGS = -pthread

# Source files
SOURCES = order_book.cpp

# Target executables
TARGETS = basic_test safe_test generate_test_orders web_demo

.PHONY: all clean test demo help

all: $(TARGETS)

# Basic functionality test
basic_test: basic_test.cpp $(SOURCES)
	@echo "Building basic test..."
	$(CXX) $(CXXFLAGS) -o $@ basic_test.cpp $(SOURCES) $(LDFLAGS)

# Performance test suite
safe_test: safe_test.cpp $(SOURCES)
	@echo "Building performance test..."
	$(CXX) $(CXXFLAGS) -o $@ safe_test.cpp $(SOURCES) $(LDFLAGS)

# CSV test file generator
generate_test_orders: generate_test_orders.cpp
	@echo "Building CSV generator..."
	$(CXX) $(CXXFLAGS) -o $@ generate_test_orders.cpp

# Web visualization demo
web_demo: web_demo.cpp $(SOURCES)
	@echo "Building web demo..."
	$(CXX) $(CXXFLAGS) -o $@ web_demo.cpp $(SOURCES) $(LDFLAGS)

# Run basic tests
test: basic_test
	@echo "Running basic functionality test..."
	./basic_test

# Run performance benchmarks
benchmark: safe_test
	@echo "Running performance benchmarks..."
	./safe_test

# Complete demo workflow
demo: generate_test_orders web_demo
	@echo "=== Generating CSV test files ==="
	./generate_test_orders
	@echo ""
	@echo "=== Running performance tests ==="
	./web_demo
	@echo ""
	@echo "✅ Demo complete! Open performance_report.html in your browser"
	@echo ""

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(TARGETS)
	rm -f *.o
	rm -rf *.dSYM

# Debug build
debug: CXXFLAGS = -std=c++20 -O0 -g3 -DDEBUG -Wall -Wextra -pthread
debug: $(TARGETS)

# Help
help:
	@echo "Available targets:"
	@echo "  all                  - Build all executables"
	@echo "  basic_test           - Build basic functionality test"
	@echo "  safe_test            - Build performance test suite"
	@echo "  generate_test_orders - Build CSV file generator"
	@echo "  web_demo             - Build web visualization demo"
	@echo "  test                 - Run basic functionality test"
	@echo "  benchmark            - Run performance benchmarks"
	@echo "  demo                 - Generate CSVs and run web demo"
	@echo "  debug                - Build debug version"
	@echo "  clean                - Remove build artifacts"
	@echo "  help                 - Show this help message"