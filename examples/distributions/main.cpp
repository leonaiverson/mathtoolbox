#include <cmath>
#include <mathtoolbox/distributions.hpp>
#include <random>

double CalculateNumericalDifferentiation(const std::function<double(double)>& f, const double x, const double h = 1e-04)
{
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

bool CheckConsistency(const std::function<double(double)>& f, const std::function<double(double)>& g, const double x)
{
    const double dfdx_numerical = CalculateNumericalDifferentiation(f, x);
    const double dfdx_analytic  = g(x);

    return std::abs(dfdx_numerical - dfdx_analytic) < 1e-08;
}

int main(int argc, char** argv)
{
    constexpr int num_tests = 100;

    std::random_device                     seed;
    std::default_random_engine             engine(seed());
    std::uniform_real_distribution<double> uniform_dist(0.0, 1.0);

    // NormalDist
    for (int i = 0; i < num_tests; ++i)
    {
        const double mu      = 20.0 * uniform_dist(engine) - 10.0;
        const double sigma_2 = 10.0 * uniform_dist(engine) + 1e-16;

        const auto f = [&mu, &sigma_2](const double x) { return mathtoolbox::GetNormalDist(x, mu, sigma_2); };
        const auto g = [&mu, &sigma_2](const double x) { return mathtoolbox::GetNormalDistDerivative(x, mu, sigma_2); };

        const double x = 100.0 * uniform_dist(engine) - 50.0;

        if (!CheckConsistency(f, g, x))
        {
            return 1;
        }
    }

    // LogNormalDist
    for (int i = 0; i < num_tests; ++i)
    {
        const double mu      = 20.0 * uniform_dist(engine) - 10.0;
        const double sigma_2 = 10.0 * uniform_dist(engine) + 1e-16;

        const auto f = [&mu, &sigma_2](const double x) { return mathtoolbox::GetLogNormalDist(x, mu, sigma_2); };
        const auto g = [&mu, &sigma_2](const double x) { return mathtoolbox::GetLogNormalDistDerivative(x, mu, sigma_2); };

        const double x = 100.0 * uniform_dist(engine) + 1e-16;

        if (!CheckConsistency(f, g, x))
        {
            return 1;
        }
    }

    // Log of LogNormalDist
    for (int i = 0; i < num_tests; ++i)
    {
        const double mu      = 20.0 * uniform_dist(engine) - 10.0;
        const double sigma_2 = 10.0 * uniform_dist(engine) + 1e-16;

        const auto f = [&mu, &sigma_2](const double x) { return mathtoolbox::GetLogOfLogNormalDist(x, mu, sigma_2); };
        const auto g = [&mu, &sigma_2](const double x) { return mathtoolbox::GetLogOfLogNormalDistDerivative(x, mu, sigma_2); };

        const double x = 100.0 * uniform_dist(engine) + 1e-16;

        if (!CheckConsistency(f, g, x))
        {
            return 1;
        }
    }

    return 0;
}
