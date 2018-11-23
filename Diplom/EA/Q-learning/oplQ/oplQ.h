#ifndef DIPLOM_OPLQ_H
#define DIPLOM_OPLQ_H


#include <EA/Q-learning/abstract_oplQ.h>

struct oplQ : private abstract_oplQ {

    explicit oplQ(problem new_probl, size_t new_lambda, size_t new_n, reward new_rew);
    solution generate_solution(const string& init_s);
    inline vector<parameters> get_params() {return params;}

private:

    const double NUMERATOR_P = 1;

};


#endif //DIPLOM_OPLQ_H
