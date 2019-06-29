#include "deceptiveness.h"

size_t deceptiveness::apply_ruggedness(size_t num, size_t s, size_t f) {
    auto df = (double)f;
    switch (num) {
        case 1:
            assert(f <= s);
            if (f == s) {
                return (size_t)ceil(df * 0.5) + 1;
            }
            if (s % 2 == 0) {
                return (size_t)floor(df * 0.5) + 1;
            } else {
                return (size_t)ceil(df * 0.5) + 1;
            }
        case 2:
            if (f == s){
                return f;
            }
            if (f % 2 == s % 2) {
                return f + 1;
            } else {
                return (f == 0 ? 0 : f - 1);
            }
        default:
            return f;
    }
}

size_t deceptiveness::size_after_ruggedness(size_t num, size_t size) {
    switch (num) {
        case 1:
            return (size + 1) / 2 + 1;
        case 2:
            return size;
        default:
            return size;
    }
}