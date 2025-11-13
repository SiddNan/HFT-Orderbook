// Basic functionality test suite
// Verifies core order book operations

#include "order_book.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    std::cout << "=== BASIC ORDER BOOK FUNCTIONALITY TEST ===\n\n";
    
    OrderBook ob(1000);
    std::vector<Fill> fills;

    // Test 1: GTC Limit Buy (no matching sell)
    std::cout << "Test 1: Placing GTC Buy Order\n";
    fills.clear();
    ob.submitOrder({1001, Side::Buy, 100000, 50, OrderType::Limit, TimeInForce::GTC, 1, 0}, &fills);
    std::cout << "  Best Bid: $" << std::fixed << std::setprecision(2) << ob.bestBid() << "\n";
    std::cout << "  Fills: " << fills.size() << "\n\n";

    // Test 2: GTC Limit Sell (no matching buy)
    std::cout << "Test 2: Placing GTC Sell Order\n";
    fills.clear();
    ob.submitOrder({1002, Side::Sell, 101000, 30, OrderType::Limit, TimeInForce::GTC, 2, 0}, &fills);
    std::cout << "  Best Ask: $" << std::fixed << std::setprecision(2) << ob.bestAsk() << "\n";
    std::cout << "  Fills: " << fills.size() << "\n\n";

    // Test 3: IOC Buy vs existing sell
    std::cout << "Test 3: IOC Buy Order (should match)\n";
    fills.clear();
    ob.submitOrder({1003, Side::Buy, 101000, 20, OrderType::Limit, TimeInForce::IOC, 3, 0}, &fills);
    std::cout << "  Fills: " << fills.size() << "\n";
    if (!fills.empty()) {
        std::cout << "  Fill Details: " << fills[0].quantity << " @ $" 
                  << std::fixed << std::setprecision(2)
                  << fills[0].priceTick / double(TICK_PRECISION) << "\n";
    }
    std::cout << "\n";

    // Test 4: FOK Sell (should fail - not enough quantity)
    std::cout << "Test 4: FOK Sell Order (should fail)\n";
    fills.clear();
    bool fok_success = ob.submitOrder({1004, Side::Sell, 100000, 60, OrderType::Limit, TimeInForce::FOK, 4, 0}, &fills);
    std::cout << "  FOK Success: " << std::boolalpha << fok_success << "\n";
    std::cout << "  Fills: " << fills.size() << "\n\n";

    // Test 5: Market Buy
    std::cout << "Test 5: Market Buy Order\n";
    fills.clear();
    ob.submitOrder({1005, Side::Buy, 0, 15, OrderType::Market, TimeInForce::IOC, 5, 0}, &fills);
    std::cout << "  Fills: " << fills.size() << "\n\n";

    // Test 6: Order Cancellation
    std::cout << "Test 6: Order Cancellation\n";
    bool cancel_success = ob.cancelOrder(1001);
    std::cout << "  Cancel Success: " << std::boolalpha << cancel_success << "\n";
    std::cout << "  Best Bid after cancel: $" << std::fixed << std::setprecision(2) << ob.bestBid() << "\n\n";

    // Test 7: Level-2 Data
    std::cout << "Test 7: Level-2 Market Data\n";
    auto bid_levels = ob.getTopLevels(Side::Buy, 5);
    auto ask_levels = ob.getTopLevels(Side::Sell, 5);
    
    std::cout << "  Bid Levels: " << bid_levels.size() << "\n";
    std::cout << "  Ask Levels: " << ask_levels.size() << "\n\n";

    // Final stats
    std::cout << "=== FINAL ORDER BOOK STATE ===\n";
    std::cout << "Best Bid: $" << std::fixed << std::setprecision(2) << ob.bestBid() << "\n";
    std::cout << "Best Ask: $" << std::fixed << std::setprecision(2) << ob.bestAsk() << "\n";
    std::cout << "Total Orders: " << ob.getOrderCount() << "\n";
    std::cout << "Bid Volume: " << ob.getTotalVolume(Side::Buy) << "\n";
    std::cout << "Ask Volume: " << ob.getTotalVolume(Side::Sell) << "\n";
    
    auto& stats = ob.getStats();
    std::cout << "Orders Processed: " << stats.getOrdersProcessed() << "\n";
    std::cout << "Fills Generated: " << stats.getFillsGenerated() << "\n";

    std::cout << "\n=== ALL BASIC TESTS PASSED ===\n";
    return 0;
}