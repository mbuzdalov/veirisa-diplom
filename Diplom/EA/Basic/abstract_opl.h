#ifndef DIPLOM_ABSTRACT_OPL_H
#define DIPLOM_ABSTRACT_OPL_H


#include "source.h"

struct abstract_opl {

    problem probl;
    size_t lambda, n;
    double p;
    double def_p, min_p, max_p;
    vector<size_t> param_f;
    vector<size_t> param_p_size;
    vector<double> param_p_sum;

    mt19937 generator = mt19937(unsigned(time(0)));

    struct representative {
        string s;
        size_t f;

        representative(const string& new_s, size_t new_f) : s(new_s), f(new_f) {};

        void change(const vector<size_t>& dif, size_t new_f) {
            f = new_f;
            for (size_t i = 0; i < dif.size(); ++i) {
                if (s[dif[i]] == '1') {
                    s[dif[i]] = '0';
                } else {
                    s[dif[i]] = '1';
                }
            }
        }
    };

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
    size_t init_func(const string& s);
    size_t func(const representative& parent, const vector<size_t>& dif);
    vector<size_t> generate_dif(const string& s, double prob);
};


#endif //DIPLOM_ABSTRACT_OPL_H
