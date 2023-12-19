#ifndef _survival
#define _survival

#include <memory>
#include <bitset>
#include "life_engine.hpp"
#include "lims.hpp"

template <size_t N>
class SurvaivalFunc{
public:
    virtual ~SurvaivalFunc() {};
    virtual std::unique_ptr<SurvaivalFunc> clone() const = 0;
    virtual int get_criterion_val(const std::bitset<N>& individ) = 0;
};


template <size_t N>
class GoLSurvaivalFunc : public SurvaivalFunc<N>{
public:
    GoLSurvaivalFunc(): engine(){}

    virtual std::unique_ptr<SurvaivalFunc<N>> clone() const override{
        return std::make_unique<GoLSurvaivalFunc<N>>(*this);
    }

    virtual int get_criterion_val(const std::bitset<N>& individ) override{
        auto target_desc = engine.get_great_descedant(individ, iterN);
        int res = target_desc.count();
        if (target_desc == engine.get_descedant(target_desc)){
            res -= PENALTY;
        }
        return res;
    }
private:
    LifeGame engine;
};

#endif  // _survival