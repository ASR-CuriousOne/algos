#include "caching/lru.hpp"
#include <iostream>

// TestBench made by Gemini (I just make the algos :) )
int main() {
    int capacity;
    std::cout << "Enter the capacity of the LRU Cache: ";
    if (!(std::cin >> capacity) || capacity <= 0) {
        std::cerr << "Invalid capacity. Exiting.\n";
        return 1;
    }

    LRU<long long, long long> cache(capacity);
    std::cout << "\n[Cache created with capacity " << capacity << "]\n";
    std::cout << "Available Commands:\n";
    std::cout << "  PUT <key> <value>  (e.g., PUT 1 100)\n";
    std::cout << "  GET <key>          (e.g., GET 1)\n";
    std::cout << "  EXIT\n";

    std::string command;
    while (true) {
        std::cout << "\n> ";
        std::cin >> command;

        for (char &c : command)
            c = toupper(c);

        if (command == "EXIT") {
            std::cout << "Shutting down cache test...\n";
            break;
        } else if (command == "PUT") {
            int key, value;
            if (std::cin >> key >> value) {
                cache.put(key, value);
                std::cout << " -> Inserted/Updated Key " << key
                          << " with Value " << value << "\n";
            } else {
                std::cout << " -> Error: Invalid input for PUT. Expected two "
                             "integers.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        } else if (command == "GET") {
            int key;
            if (std::cin >> key) {
                auto result = cache.get(key);
                if (!result.has_value()) {
                    std::cout << " -> Cache Miss! Key " << key
                              << " not found or was evicted.\n";
                } else {
                    std::cout << " -> Cache Hit! Value: " << result.value()
                              << "\n";
                }
            } else {
                std::cout << " -> Error: Invalid input for GET. Expected one "
                             "integer.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        } else {
            std::cout << " -> Unknown command. Please use PUT, GET, or EXIT.\n";
            std::cin.ignore(10000, '\n');
        }
    }

    return 0;
}
