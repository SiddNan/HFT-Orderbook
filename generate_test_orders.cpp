// Test data generator for performance benchmarks
// Creates CSV files with reproducible random orders

#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

void generateCSV(const std::string& filename, int num_orders) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to create " << filename << "\n";
        return;
    }
    
    file << "SIDE,PRICE,QUANTITY,TYPE,TIF\n";
    
    std::mt19937 rng(12345); // Fixed seed for reproducibility
    std::uniform_real_distribution<> price_dist(500.0, 540.0);
    std::uniform_int_distribution<> qty_dist(10, 500);
    std::uniform_int_distribution<> side_dist(0, 1);
    std::uniform_int_distribution<> tif_dist(0, 2);
    
    const char* sides[] = {"BUY", "SELL"};
    const char* tifs[] = {"GTC", "IOC", "FOK"};
    
    for (int i = 0; i < num_orders; ++i) {
        file << sides[side_dist(rng)] << ","
             << std::fixed << std::setprecision(2) << price_dist(rng) << ","
             << qty_dist(rng) << ","
             << "LIMIT,"
             << tifs[tif_dist(rng)] << "\n";
    }
    
    file.close();
    std::cout << "✓ Created " << filename << " with " << num_orders << " orders\n";
}

int main() {
    std::cout << "=== Generating CSV Test Files ===\n\n";
    
    generateCSV("orders_small.csv", 1000);      // Quick demo (1K orders)
    generateCSV("orders_medium.csv", 10000);    // Standard test (10K orders)
    generateCSV("orders_large.csv", 100000);    // Stress test (100K orders)
    
    std::cout << "\n✅ All CSV files generated successfully!\n";
    std::cout << "These files contain randomized orders for performance testing.\n";
    
    return 0;
}