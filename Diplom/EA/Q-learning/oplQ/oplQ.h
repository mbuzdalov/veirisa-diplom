#ifndef DIPLOM_OPLQ_H
#define DIPLOM_OPLQ_H


#include <EA/Q-learning/abstract_oplQ.h>

struct oplQ : private abstract_oplQ {

    explicit oplQ(const w_model& new_model, size_t new_lambda, size_t new_n, low_bound l_bound, learning new_learn);
    solution generate_solution(const string& init_s);
    inline parameters get_params() {return convert_params();};
    double get_visit();

private:

    size_t associate_states(size_t state_size, size_t count);
};

#endif //DIPLOM_OPLQ_H
