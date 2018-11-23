#include "opl_separating.h"

opl_separating::opl_separating(problem new_probl, size_t new_lambda, size_t new_n) {
    probl = new_probl;
    lambda = new_lambda;
    n = new_n;
    def_p = NUMERATOR_P / new_n;
    min_p = 2.0 / (new_n * new_n);
    max_p = 1.0 / 4;
}

void opl_separating::change_p(operation op) {
    if (choice(0.5)) {
        if (op == MUL) {
            p = min(p * 2, max_p);
        } else {
            p = max(p / 2, min_p);
        }
    } else {
        if (choice(0.5)) {
            p = min(p * 2, max_p);
        } else {
            p = max(p / 2, min_p);
        }
    }
}

solution opl_separating::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    init_p();
    representative cur(init_s, init_func(init_s));
    init_params(cur.f, p);
    size_t evaluations = 1;
    size_t generations = 0;
    while (cur.f < n) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        operation best_op = UNDEF;
        for (size_t i = 0; i < lambda; ++i) {
            bool is_mul = i < (lambda >> 1);
            vector<size_t> dif = move(generate_dif(cur.s, is_mul ? p * 2 : p / 2));
            size_t f = func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
                best_op = is_mul ? MUL : DIV;
            }
        }
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        change_p(best_op);
        params.push_back({cur.f, p});
        evaluations += lambda;
        ++generations;
    }
    return {evaluations, generations};
}