#ifndef _selection
#define _selection

#include <memory>
#include <bitset>
#include <array>
#include <numeric>
#include <algorithm>
#include <random>
#include "lims.hpp"

/*ln best selection*/
template <size_t popSize>
class BestSelection {
public:
    virtual std::unique_ptr<BestSelection<popSize>> clone() const {
        return std::make_unique<BestSelection<popSize>>(*this);
    }

    virtual std::array<int, popSize> select(const std::array<int, popSize>& surv_func_vals) {
        std::array<int, popSize> res;

        std::random_device rd;     // Only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(0, popSize); // Guaranteed unbiased

        for (unsigned i = 0; i < popSize; i++) {
            auto x = uni(rng);
            auto y = uni(rng);

            if (surv_func_vals[x] > surv_func_vals[y]) {
                res[i] = x;
            } else {
                res[i] = y;
            }
        }

        return res;
    }
};

#endif // _selection