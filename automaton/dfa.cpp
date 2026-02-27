#include <map>
#include <print>
#include <set>
#include <string>

struct TransitionInput {
  int state;
  char input;

	friend bool operator<(const TransitionInput& a, const TransitionInput& b){
		return a.state < b.state || a.state == b.state && a.input < b.input;
	}
};

class DFA {
  std::map<TransitionInput, int> m_transitions;

  int m_startState;

  std::set<int> m_acceptStates;

public:
  DFA(int start, const std::set<int> accepts)
      : m_startState(start), m_acceptStates(accepts) {}

  void addTransition(TransitionInput input, int newState) {
    m_transitions[input] = newState;
  }

  bool simulate(const std::string &inputString) {
    int currentState = m_startState;

    for (auto c : inputString) {
      auto it = m_transitions.find({currentState, c});

      if (it == m_transitions.end()) {
        return false;
      }

      currentState = it->second;
    }

    return m_acceptStates.count(currentState) > 0;
  }
};

int main() {
  DFA dfa(0, {1});

  dfa.addTransition({0, '0'}, 0);
  dfa.addTransition({0, '1'}, 1);
  dfa.addTransition({1, '0'}, 1);
  dfa.addTransition({1, '1'}, 0);

  std::string test_strings[] = {"000", "001", "1010", "111", "10110"};

  for (const std::string &str : test_strings) {
    bool accepted = dfa.simulate(str);
    std::string out = (accepted ? "True" : "False");
    std::println("Input: {}	Accepted: {}", str, out);
  }
}
