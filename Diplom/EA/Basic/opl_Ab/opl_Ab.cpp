#include "opl_Ab.h"

opl_Ab::opl_Ab(problem new_probl, size_t new_lambda, size_t new_n, low_bound l_bound) {
    probl = new_probl;
    lambda = new_lambda;
    n = new_n;
    def_p = NUMERATOR_P / n;
    max_p = 1.0 / 2;
    min_p = calc_low_bound(l_bound);
    border = (size_t)max(1.0, DEFAULT_BORDER_COEF * lambda);
}

void opl_Ab::change_p(operation op) {
    if (op == MUL) {
        p = min(p * 2, max_p);
    } else {
        p = max(p / 2, min_p);
    }
}

solution opl_Ab::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    init_p();
    init_params();
    representative cur(init_s, init_func(init_s));
    size_t evaluations = 1;
    size_t generations = 0;
    while (cur.f < n) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        size_t better_children = 0;
        for (size_t i = 0; i < lambda; ++i) {
            vector<size_t> dif = move(generate_dif(cur.s, p));
            size_t f = func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
            }
            if (f >= cur.f) {
                ++better_children;
            }
        }
        update_params(cur.f, p);
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        change_p(better_children >= border ? MUL : DIV);
        evaluations += lambda;
        ++generations;
    }
    update_params(cur.f, p);
    return {evaluations, generations};
}