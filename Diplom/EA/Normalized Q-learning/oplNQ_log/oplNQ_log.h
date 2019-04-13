#ifndef DIPLOM_OPLNQ_LOG_H
#define DIPLOM_OPLNQ_LOG_H


#include <EA/Normalized Q-learning/abstract_oplNQ.h>

struct oplNQ_log : private abstract_oplNQ {

    explicit oplNQ_log(problem new_probl, size_t new_lambda, size_t new_n, low_bound l_bound, reward new_rew);
    solution generate_solution(const string& init_s);
    inline parameters get_params() {return convert_params();};

private:

    const double NUMERATOR_P = 1;
    size_t normalize_states(size_t count);

};

#endif //DIPLOM_OPLNQ_LOG_H
