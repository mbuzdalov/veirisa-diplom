#ifndef DIPLOM_STRUCTURES_H
#define DIPLOM_STRUCTURES_H

#import "source.h"
#include <WModel/w_model.h>

// --- W-model structures ---

const w_model CLEAR_ONE_MAX = w_model(ONE_MAX, false, false, 0);
const w_model NEUTRAL_ONE_MAX = w_model(ONE_MAX, true, false, 0);
const w_model EPISTASIS_ONE_MAX = w_model(ONE_MAX, false, true, 0);
const w_model PLATO_REGGEDNESS_ONE_MAX = w_model(ONE_MAX, false, false, 1);
const w_model REGGEDNESS_ONE_MAX = w_model(ONE_MAX, false, false, 2);

const w_model CLEAR_LEADING_ONES = w_model(LEADING_ONES, false, false, 0);
const w_model NEUTRAL_LEADING_ONES = w_model(LEADING_ONES, true, false, 0);
const w_model EPISTASIS_LEADING_ONES = w_model(LEADING_ONES, false, true, 0);
const w_model PLATO_REGGEDNESS_LEADING_ONES = w_model(LEADING_ONES, false, false, 1);
const w_model REGGEDNESS_LEADING_ONES = w_model(LEADING_ONES, false, false, 2);

// --- Learning structures ---

const none_learning NONE_LEARN = {};

const learning DEFAULT_LEARN = {DEFAULT_ALPHA, DEFAULT_GAMMA, DEFAULT_REWARD, RANDOM, MIN_STATE_SIZE};
const learning DEFAULT_LEARN_AB = {DEFAULT_ALPHA, DEFAULT_GAMMA, DEFAULT_REWARD, AB, MIN_STATE_SIZE};
const learning DEFAULT_NORM_LEARN = {DEFAULT_ALPHA, DEFAULT_GAMMA, DEFAULT_REWARD, RANDOM, DEFAUlT_STATE_SIZE};
const learning DEFAULT_NORM_LEARN_AB = {DEFAULT_ALPHA, DEFAULT_GAMMA, DEFAULT_REWARD, AB, DEFAUlT_STATE_SIZE};

#endif //DIPLOM_STRUCTURES_H
