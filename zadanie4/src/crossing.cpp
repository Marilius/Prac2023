#ifndef _crossing
#define _crossing

#include <bitset>
#include <utility>
#include <memory>

template<size_t N>
class Crossing{
public:
    virtual std::pair<std::bitset<N>, std::bitset<N>> cross(const std::bitset<N>& lhs, const std::bitset<N>& rhs) = 0;
    virtual std::unique_ptr<Crossing<N>> clone() const = 0;
    virtual double get_crossing_prob() const = 0;
    virtual ~Crossing() {};
};

template<size_t N>
class Crosser : public Crossing<N>{
public:
    Crosser(double _prob = 0.8): point1(N / 3), point2(N * 2 / 3), prob(_prob){};
    Crosser(const Crosser& other) = default;
    ~Crosser() = default;

    std::unique_ptr<Crossing<N>> clone() const override{
        return std::make_unique<Crosser<N>>(*this);
    }

    // 2-point crossover
    std::pair<std::bitset<N>, std::bitset<N>> cross(const std::bitset<N>& lhs, const std::bitset<N>& rhs) override{
        std::bitset<N> descendant1 = lhs;
        std::bitset<N> descendant2 = rhs;
        for (unsigned i = point2; i >= point1; i--){
            descendant1[i] = rhs[i];
            descendant2[i] = lhs[i];
        }
        return {descendant1, descendant2};
    }

    double get_crossing_prob() const override{
        return prob;
    }

private:
    unsigned int point1;
    unsigned int point2;
    double prob;
};


#endif // _crossing