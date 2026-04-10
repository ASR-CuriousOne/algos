#include <concepts>
#include <print>
#include <vector>

template <std::floating_point T> struct OdeState {
    T t;
    T y;
};

template <std::floating_point T, typename F>
    requires std::invocable<F, T, T>

std::vector<OdeState<T>> solveRK4(F &&f, T t0, T y0, T h, size_t steps) {
    std::vector<OdeState<T>> history;
    history.reserve(steps + 1);
    history.push_back({t0, y0});

    T t = t0;
    T y = y0;

    for (size_t i = 0; i < steps; i++) {
        T k1 = f(t, y);
        T k2 = f(t + h / 2.0, y + (h / 2.0) * k1);
        T k3 = f(t + h / 2.0, y + (h / 2.0) * k2);
        T k4 = f(t + h, y + h * k3);

        y += (h / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
        t += h;

        history.push_back({t, y});
    }

    return history;
}

int main() {
    auto ode = [](double t, double y) { return -2.0 * t * y; };

    auto results = solveRK4(ode, 0.0, 1.0, 0.1, 10);

    std::println("Step | t      | y");
    std::println("----------------------");

    for (size_t i = 0; i < results.size(); i++) {
        const auto &[t, y] = results[i];
        std::println("{:4} | {:6.3f} | {:6.5f}", i, t, y);
    }

    return 0;
}
