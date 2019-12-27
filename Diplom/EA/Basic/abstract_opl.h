#ifndef DIPLOM_ABSTRACT_OPL_H
#define DIPLOM_ABSTRACT_OPL_H


#include "source.h"
#include "EA/representative.h"
#include "WModel/w_model.h"

struct abstract_opl {

    w_model model;
    size_t lambda, n;
    double p;
    double def_p, min_p, max_p;
    random_jump jump;
    vector<size_t> param_f;
    vector<size_t> param_p_size;
    vector<double> param_p_sum;

    mt19937 generator = mt19937(3);

    inline void init_p() {
        p = def_p;
    }

    inline bool choice(double prob) {
        return (double)generator() / generator.max() < prob;
    }

    inline size_t get_next_ind(size_t start_ind, double prob) {
        return start_ind + size_t(log((double)generator() / generator.max()) / log(1 - prob));
    }

    inline size_t next_inv_ind( size_t start_ind, double prob) {
        size_t next_ind = get_next_ind(start_ind, prob);
        while (start_ind == 0 && next_ind >= n) {
            next_ind = generator() % n;
        }
        return next_ind;
    }

    double calc_low_bound(low_bound l_bound);
    void init_params();
    void update_params(size_t cur_f, double cur_p);
    parameters convert_params();
    vector<size_t> generate_dif(const string& s, double prob);
    void change_p(operation op);
};


#endif //DIPLOM_ABSTRACT_OPL_H
