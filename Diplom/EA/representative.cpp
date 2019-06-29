#include "representative.h"

void representative::change(const vector<size_t>& dif, size_t new_f) {
    f = new_f;
    for (size_t i = 0; i < dif.size(); ++i) {
        if (s[dif[i]] == '1') {
            s[dif[i]] = '0';
        } else {
            s[dif[i]] = '1';
        }
    }
}