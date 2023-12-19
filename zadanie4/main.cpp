#include <iostream>
#include <bitset>
#include <memory>
#include <array>
#include <algorithm>
#include "main.hpp"

int main(){
    LifeGame game;
    Mutator<WIDTH * HEIGHT> mut(1. / (WIDTH * HEIGHT));
    TournamentSelection<Npop> sel;
    GoLSurvaivalFunc<WIDTH*HEIGHT> surv_func;
    Crosser<WIDTH * HEIGHT> cros;
    GA<WIDTH * HEIGHT> gen_algo(sel, mut, cros, surv_func);

    gen_algo.run_algorithm();
    
    auto best_individ = gen_algo.get_best_individ();
    auto best_criterion = gen_algo.get_best_criterion();

    std::cout << "Best result: " << best_criterion << std::endl;
    game.get_great_descedant(best_individ, 100, true);

    return 0;
}