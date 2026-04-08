#include "blockchain/bloomFilter.hpp"
#include <print>

int main() {

    BloomFilter<std::string> filter(1'000'000, 0.01);

    filter.printStats();

    filter.insert("jotaro");
    filter.insert("josuke");

    std::println("Contains jotaro?  {}",
                 filter.contains("jotaro") ? "Probably" : "No");
    std::println("Contains josuke? {}",
                 filter.contains("josuke") ? "Probably" : "No");
    std::println("Contains dio? {}",
                 filter.contains("dio") ? "Probably" : "No");
}
