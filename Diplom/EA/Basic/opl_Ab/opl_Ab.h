#ifndef DIPLOM_OPL_AB_H
#define DIPLOM_OPL_AB_H


#include <EA/Basic/abstract_opl.h>

struct opl_Ab : private abstract_opl {

    explicit opl_Ab(const w_model& new_model, size_t new_lambda, size_t new_n, low_bound l_bound);
    solution generate_solution(const string& init_s);
    inline parameters get_params() {return convert_params();};

};


#endif //DIPLOM_OPL_AB_H
