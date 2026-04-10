#include "missiz/trie.hpp"
#include <cassert>
#include <iostream>

// Tests written by Gemini :) (should write them myself though)
int main() {
    Trie<char> trie;

    std::cout << "Running GenericTrie<char> tests...\n";

    trie.insert("bat");
    trie.insert("bath");
    trie.insert("batman");
    trie.insert("apple");

    assert(trie.hasWord("bat") == true);
    assert(trie.hasWord("bath") == true);
    assert(trie.hasWord("batman") == true);
    assert(trie.hasWord("apple") == true);

    assert(trie.hasWord("ba") == false);
    assert(trie.hasWord("batm") == false);
    assert(trie.hasWord("apples") == false);
    std::cout << "[PASS] Basic Insertion and Search\n";

    assert(trie.hasPrefix("b") == true);
    assert(trie.hasPrefix("ba") == true);
    assert(trie.hasPrefix("bat") == true);
    assert(trie.hasPrefix("batm") == true);
    assert(trie.hasPrefix("app") == true);

    assert(trie.hasPrefix("cat") == false);
    assert(trie.hasPrefix("baths") == false);
    std::cout << "[PASS] Prefix Searching\n";

    trie.remove("bat");

    assert(trie.hasWord("bat") == false);
    assert(trie.hasWord("bath") == true);
    assert(trie.hasWord("batman") == true);
    assert(trie.hasPrefix("bat") == true);
    std::cout << "[PASS] Removal (Prefix Word)\n";

    trie.remove("bath");

    assert(trie.hasWord("bath") == false);
    assert(trie.hasWord("batman") == true);
    assert(trie.hasPrefix("bath") == false);
    assert(trie.hasPrefix("bat") == true);
    std::cout << "[PASS] Removal (Leaf Word / Pruning)\n";

    trie.remove("hello");
    trie.remove("apples");

    assert(trie.hasWord("apple") == true);
    std::cout << "[PASS] Removal (Non-existent words)\n";

    trie.insert("Cat!");
    assert(trie.hasWord("Cat!") == true);
    assert(trie.hasWord("cat!") == false);
    assert(trie.hasWord("at") == false);
    std::cout << "[PASS] Edge Cases (Case sensitivity and symbols handled "
                 "correctly)\n";

    std::cout << "\n-----------------------------------\n\n";

    Trie<wchar_t> wideTrie;

    std::cout << "Running GenericTrie<wchar_t> tests...\n";

    wideTrie.insert(L"こんにちは");
    wideTrie.insert(L"こん");

    assert(wideTrie.hasWord(L"こんにちは") == true);
    assert(wideTrie.hasWord(L"こん") == true);
    assert(wideTrie.hasPrefix(L"こんに") == true);
    assert(wideTrie.hasWord(L"さようなら") == false);
    std::cout << "[PASS] Wide string (Unicode) Insertion and Search\n";

    wideTrie.remove(L"こん");
    assert(wideTrie.hasWord(L"こん") == false);
    assert(wideTrie.hasPrefix(L"こん") == true);
    assert(wideTrie.hasWord(L"こんにちは") == true);
    std::cout << "[PASS] Wide string (Unicode) Removal\n";

    std::cout << "\nAll Generic Trie tests passed successfully!\n";

    return 0;
}
