#include "abstract_opl.h"

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