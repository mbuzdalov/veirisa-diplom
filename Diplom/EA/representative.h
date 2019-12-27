#ifndef DIPLOM_REPRESENTATIVE_H
#define DIPLOM_REPRESENTATIVE_H

#include "source.h"


struct representative {

    string s;
    size_t f;

    representative(const string& new_s, size_t new_f) : s(new_s), f(new_f) {};
    void change(const vector<size_t>& dif, size_t new_f);

};

#endif //DIPLOM_REPRESENTATIVE_H
