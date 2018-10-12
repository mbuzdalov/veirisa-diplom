#ifndef DIPLOM_OPL_H
#define DIPLOM_OPL_H


#include <EA/Basic/abstract_opl.h>

struct opl : private abstract_opl {

    explicit opl(problem new_probl, size_t new_lambda, size_t new_n);
    solution generate_solution(const string& init_s);

private:

    const double NUMERATOR_P = 1.0;

};


#endif //DIPLOM_OPL_H
