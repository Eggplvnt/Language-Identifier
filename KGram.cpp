//
// Implementation of the KGram class storing a kgram and its frequency
// Used for items in the priority queue employed by TopKGramsIn
//
// Author: Max Benson
// Date: 08/30/2022
// Modifier: Ilya Bukhalau
// Modification Date: 11/28/22
//

#include <cassert>
#include <iostream>
#include "KGram.h"

/**
 * Constructor for KGram
 * @param text kgram string
 * @param frequency associated frequency
 */
KGram::KGram(string text, double frequency) {
    _text = text;
    _frequency = frequency;
}

/**
 * Accessor for Text
 * @return kgram string
 */
string KGram::Text() {
    return _text;
};

/**
 * Accessor for Frequency
 * @return frequency of kgram
 */
double KGram::Frequency() {
    return _frequency;
}

/**
 * Operator overload for <
 * It is necessary to overload < in order to form priority_queue<KGram>
 * and we define < based on frequencies because we want to keep the most
 * frequent kgrams.  However since the priority_queue template is a
 * max-priority-queue data structure, we have to reverse the sense of the
 * comparison to effectively make it a min-priority-queue data structure
 * @param lhs the kgram to compare to
 * @param rhs the other kgram to compare to
 * @return true if the frequency of **kgram** is less than the frequency of this
 */
bool operator< (const KGram& lhs, const KGram& rhs) {
    if (lhs._frequency > rhs._frequency) {
        return true;
    }
    return false;
}