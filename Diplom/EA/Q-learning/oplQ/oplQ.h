#ifndef DIPLOM_OPLQ_H
#define DIPLOM_OPLQ_H


#include <EA/Q-learning/abstract_oplQ.h>

struct oplQ : private abstract_oplQ {

    explicit oplQ(problem new_probl, size_t new_lambda, size_t new_n, low_bound l_bound, learning new_learn);
    solution generate_solution(const string& init_s);
    inline parameters get_params() {return convert_params();};

private:

    const double NUMERATOR_P = 1;
    size_t associate_states(double split, size_t count);

};

#endif //DIPLOM_OPLQ_H
