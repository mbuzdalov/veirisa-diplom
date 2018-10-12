#ifndef DIPLOM_OPL_SEPARATING_H
#define DIPLOM_OPL_SEPARATING_H


#include <EA/Basic/abstract_opl.h>

struct opl_separating : private abstract_opl {

    explicit opl_separating(problem new_probl, size_t new_lambda, size_t new_n);
    solution generate_solution(const string& init_s);

private:

    const double NUMERATOR_P = 2;
    void change_p(operation op);

};


#endif //DIPLOM_OPL_SEPARATING_H
