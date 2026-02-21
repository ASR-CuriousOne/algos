#include "ds.hpp" 
#include <cassert>
#include <print>

void runTests() {
  ll n = 5;
  DS ds(n);
  
  for (ll i = 1; i <= n; i++) {
    assert(ds.getSize(i) == 1 && "Initial size should be 1");
    assert(ds.find(i) == i && "Initial parent should be self");
  }
  assert(ds.getComponentsCount() == 5 && "Initial components count should be n");

  ds.unite(1, 2);
  assert(ds.connected(1, 2) && "1 and 2 should be connected");
  assert(ds.getSize(1) == 2 && "Size of the set containing 1 should be 2");
  assert(ds.getSize(2) == 2 && "Size of the set containing 2 should be 2");
  assert(ds.getComponentsCount() == 4 && "Components count should decrease by 1");

  
  ds.unite(3, 4);
  ds.unite(4, 5);
	assert(ds.connected(3, 5) && "3 and 5 should be transitively connected");
  assert(ds.getSize(3) == 3 && "Size of the set {3, 4, 5} should be 3");
  assert(ds.getComponentsCount() == 2 && "2 components should remain: {1,2} and {3,4,5}");

  ds.unite(2, 4); 
	assert(ds.connected(1, 5) && "All elements should now be connected");
  assert(ds.getSize(1) == 5 && "Size of the fully connected set should be 5");
  assert(ds.getComponentsCount() == 1 && "Only 1 component should remain");

  ds.unite(1, 3);  
	assert(ds.getSize(1) == 5 && "Size should not change on redundant union");
  assert(ds.getComponentsCount() == 1 && "Components count should not change on redundant union");

  std::println("All Disjoint Set assertions passed successfully!");
}

int main() {
  runTests();
  return 0;
}
