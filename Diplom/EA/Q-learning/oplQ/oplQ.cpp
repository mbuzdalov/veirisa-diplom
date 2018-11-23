#include "oplQ.h"

oplQ::oplQ(problem new_probl, size_t new_lambda, size_t new_n, reward new_rew) {
    probl = new_probl;
    lambda = new_lambda;
    n = new_n;
    rew = new_rew;
    def_p = NUMERATOR_P / new_n;
    min_p = 1.0 / (new_n * new_n);
    max_p = 1.0 / 2;
    alpha = DEFAULT_ALPHA;
    gamma = DEFAULT_GAMMA;
    Q.resize(new_lambda + 1);
}

solution oplQ::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    init_p();
    init_Q();
    representative cur(init_s, init_func(init_s));
    init_params(cur.f, p);
    size_t evaluations = 1;
    size_t generations = 0;
    size_t suc = UNDEF_STATE;
    operation op = UNDEF;
    while (cur.f < n) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        size_t new_suc = 0;
        for (size_t i = 0; i < lambda; ++i) {
            vector<size_t> dif = move(generate_dif(cur.s, p));
            size_t f = func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
            }
            if (f > cur.f) {
                ++new_suc;
            }
        }
        learn(suc, op, get_reward(best_f, cur.f), new_suc);
        operation new_op = change_p(new_suc);
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        params.push_back({cur.f, p});
        evaluations += lambda;
        ++generations;
        suc = new_suc;
        op = new_op;
    }
    return {evaluations, generations};
}