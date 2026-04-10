#include "matrix/matrix.hpp"
#include <concepts>
#include <print>
#include <vector>

struct SystemState {
    float t;
    Vec y;
};

template <typename F>
    requires std::invocable<F, float, const Vec &>
std::vector<SystemState> solveSystemRK4(F &&f, float t0, const Vec &y0, float h,
                                        size_t steps) {
    std::vector<SystemState> history;
    history.reserve(steps + 1);
    history.push_back({t0, y0});

    float t = t0;
    Vec y = y0;

    for (size_t i = 0; i < steps; i++) {
        Vec k1 = f(t, y);
        Vec k2 = f(t + h / 2.0f, y + k1 * (h / 2.0f));
        Vec k3 = f(t + h / 2.0f, y + k2 * (h / 2.0f));
        Vec k4 = f(t + h, y + k3 * h);

        y = y + (k1 + k2 * 2.0f + k3 * 2.0f + k4) * (h / 6.0f);
        t += h;

        history.push_back({t, y});
    }

    return history;
}

int main() {
    auto harmonicOscillator = [](float t, const Vec &y) -> Vec {
        Vec dy(2);
        dy[0] = y[1];
        dy[1] = -y[0];
        return dy;
    };

    Vec y0(2);
    y0[0] = 1.0f;
    y0[1] = 0.0f;

    auto results = solveSystemRK4(harmonicOscillator, 0.0f, y0, 0.1f, 50);

    for (size_t i = 0; i < results.size(); i++) {
        const auto &[t, y] = results[i];
        std::println("Step {}: t = {:.2f}", i, t);
        y.display();
        std::println("");
    }

    return 0;
}
