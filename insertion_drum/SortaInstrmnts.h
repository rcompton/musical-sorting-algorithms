#ifndef SORTAINSTRUMENTS_H
#define SORTAINSTRUMENTS

#include "Plucked.h"
#include "Saxofony.h"
#include "Drummer.h"
using namespace stk;

struct SortaInstrmnt{
    double sort_value;
    StkFloat freq;
    StkFloat loudness;
};

//You specify drums via their MIDI numbers
//it's not as easy as specifying frequency

#endif /* SORTAINSTRUMENTS */
