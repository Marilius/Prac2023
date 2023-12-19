#ifndef _ga
#define _ga

#include <cmath>
#include <memory>
#include <array>
#include <algorithm>
#include "lims.hpp"
#include "mutation.cpp"
#include "selection.cpp"
#include "survival.cpp"
#include "crossing.cpp"

#include <iostream>

template <size_t Ngens>
class GA {
public:
    GA(Selection<Npop> &_selector, Mutation<Ngens> &_mutator,
                Crossing<Ngens> &_crosser, SurvaivalFunc<Ngens> &_surv_func) : selector(_selector.clone()), mutator(_mutator.clone()),
                                                                               crosser(_crosser.clone()), surv_func(_surv_func.clone()),
                                                                               best_res(0){};

    void run_algorithm() {
        init_population();
        best_res = 0;

    
        std::array<int, Npop> survaival_vals;
        best_individ = population[0];

        int stable_iter = 0;
        while (stable_iter < MAX_NON_BEST_ITER) {
            // std::cout << get_best_criterion() << std::endl;

            stable_iter++;
            survaival_vals = std::move(population_survaival_func());

            if (is_new_best(survaival_vals)) {
                stable_iter = 0;
            }

            auto selected_individs = std::move(population_selection(survaival_vals));
            population = std::move(population_crossing(selected_individs));
            population_mutation();
        }
    }

    std::bitset<Ngens> get_best_individ() const {
        return best_individ;
    }

    int get_best_criterion() const {
        return best_res;
    }

private:
    std::shared_ptr<Selection<Npop>> selector;
    std::shared_ptr<Mutation<Ngens>> mutator;
    std::shared_ptr<Crossing<Ngens>> crosser;
    std::shared_ptr<SurvaivalFunc<Ngens>> surv_func;
    std::array<std::bitset<Ngens>, Npop> population;

    std::bitset<Ngens> best_individ;
    int best_res = 0;

    void init_population() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<> dist(0, 1); // distribution in discrete range [0, 1]

        std::bitset<Ngens> tmp_individ;

        for (unsigned i = 0; i < Npop; i++) {
            for (unsigned j = 0; j < Ngens; j++) {
                tmp_individ[j] = dist(rng);
            }
            population[i] = tmp_individ;
        }
    }

    std::array<int, Npop>
    population_survaival_func() {
        std::array<int, Npop> res;
        for (unsigned i = 0; i < Npop; i++) {
            res[i] = surv_func->get_criterion_val(population[i]);
        }
        return res;
    }

    std::array<std::bitset<Ngens>, Npop>
    population_selection(const std::array<int, Npop> &surv_func_vals) {
        std::array<int, Npop> indices = selector->select(surv_func_vals);
        std::array<std::bitset<Ngens>, Npop> selected_individs;
        for (unsigned i = 0; i < Npop; i++) {
            selected_individs[i] = population[indices[i]];
        }
        return selected_individs;
    }

    std::array<std::bitset<Ngens>, Npop>
    population_crossing(const std::array<std::bitset<Ngens>, Npop> &selected_individs) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<> ind_dist(0, Npop - 1);
        std::uniform_real_distribution<> cross_prob_dist(0, 1);

        int i, j, k = 0;
        std::array<std::bitset<Ngens>, Npop> new_population;
        double cross_prob = crosser->get_crossing_prob();
        while (k < Npop - 1) {
            i = ind_dist(rng);
            j = ind_dist(rng);

            while (selected_individs[i] == selected_individs[j]) {
                i = ind_dist(rng);
                j = ind_dist(rng);
            }

            if (cross_prob_dist(rng) < cross_prob) {
                auto descedants = crosser->cross(selected_individs[i], selected_individs[j]);
                new_population[k] = std::move(descedants.first);
                new_population[k + 1] = std::move(descedants.second);
                k += 2;
            }
        }
        return new_population;
    }

    void population_mutation() {
        for (unsigned i = 0; i < Npop; i++) {
            population[i] = mutator->mutate(population[i]);
        }
    }

    // new best
    inline bool is_new_best(const std::array<int, Npop> &surv_func_vals) {
        auto argmin_iter = std::max_element(surv_func_vals.begin(), surv_func_vals.end());
        int argmin = argmin_iter - surv_func_vals.begin();

        // std::cout <<  << std::endl;


        if (*argmin_iter > best_res) {
            best_individ = population[argmin];
            best_res = *argmin_iter;
            return true;
        }

        return false;
    }
};

#endif // _ga