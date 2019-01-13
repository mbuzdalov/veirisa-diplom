#include "abstract_opl.h"

double abstract_opl::calc_low_bound(low_bound l_bound) {
    switch (l_bound) {
        case LINEAR:
            return 1.0 / n;
        case QUADRATIC:
            return 1.0 / (n * n);
        default:
            return 0;
    }
}

void abstract_opl::init_params() {
    param_f.clear();
    param_p_sum = vector<double>(n + 1, 0);
    param_p_size = vector<size_t>(n + 1, 0);
}

void abstract_opl::update_params(size_t cur_f, double cur_p) {
    param_f.push_back(cur_f);
    param_p_sum[cur_f] += cur_p;
    ++param_p_size[cur_f];
}

parameters abstract_opl::convert_params() {
    vector<double> param_p;
    for (size_t i = 0; i < n; ++i) {
        param_p.push_back(param_p_sum[i] / param_p_size[i]);
    }
    return {param_f, param_p};
}

size_t abstract_opl::init_func(const string& s) {
    if (probl == ONE_MAX) {
        size_t result = 0;
        for (size_t i = 0; i < n; ++i) {
            if (s[i] == '1') {
                ++result;
            }
        }
        return result;
    }
    if (probl == LEADING_ONES) {
        size_t result = 0;
        for (size_t i = 0; i < n; ++i) {
            if (s[i] == '1') {
                ++result;
            } else {
                return result;
            }
        }
        return result;
    }
    return 0;
}

size_t abstract_opl::func(const representative& parent, const vector<size_t>& dif) {
    assert(!dif.empty());
    if (probl == ONE_MAX) {
        size_t result = parent.f;
        for (size_t j = 0; j < dif.size(); ++j) {
            if (parent.s[dif[j]] == '1') {
                --result;
            } else {
                ++result;
            }
        }
        return result;
    }
    if (probl == LEADING_ONES) {
        if (dif[0] < parent.f) {
            return dif[0];
        }
        size_t result = parent.f;
        for (size_t j = 0; j < dif.size(); ++j) {
            while (result < dif[j]) {
                if (parent.s[result] == '0') {
                    return result;
                }
                ++result;
            }
            if (parent.s[dif[j]] == '0') {
                ++result;
            } else {
                return result;
            }
        }
        while (result < n) {
            if (parent.s[result] == '0') {
                return result;
            }
            ++result;
        }
        return result;
    }
    return 0;
}

vector<size_t> abstract_opl::generate_dif(const string& s, double prob) {
    vector<size_t> dif;
    size_t ind = next_inv_ind(0, prob);
    while (ind < n) {
        dif.push_back(ind);
        ind = next_inv_ind(ind + 1, prob);
    }
    return dif;
}