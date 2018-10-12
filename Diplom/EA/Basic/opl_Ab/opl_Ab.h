#ifndef DIPLOM_OPL_AB_H
#define DIPLOM_OPL_AB_H


#include <EA/Basic/abstract_opl.h>

struct opl_Ab : private abstract_opl {

    explicit opl_Ab(problem new_probl, size_t new_lambda, size_t new_n);
    solution generate_solution(const string& init_s);

private:

    size_t border;
    const double NUMERATOR_P = 1;
    void change_p(operation op);

};


#endif //DIPLOM_OPL_AB_H
