#ifndef _mutation
#define _mutation

#include <random>
#include <memory>
#include <bitset>

template<size_t N>
class Mutator {
public:
    Mutator(double _prob): prob(_prob) {};

    std::unique_ptr<Mutator<N>> clone() const {
        return std::make_unique<Mutator>(*this);
    }

    std::bitset<N> mutate(const std::bitset<N>& individ) {
        std::bitset<N> res(individ);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> mutation_prob(0, 1);

        for (unsigned i = 0; i <= res.size(); i++) {
            if (mutation_prob(gen) < prob) {
                res[i] = ~res[i]; 
            }
        }
        return res;
    }
private:
    double prob;    // mutation probability
};

#endif // _mutation