//
// Interface definition for the KGram class storing a kgram and its frequency
// Used for items in the priority queue employed by TopKGramsIn
//
// Author: Max Benson
// Date: 08/30/2022
//

#ifndef KGRAM_H
#define KGRAM_H

#include <string>
using std::string;

class KGram {
public:
    KGram(string text, double frequency);

    string Text();
    double Frequency();

    friend bool operator< (const KGram& lhs, const KGram& rhs);

private:
    string _text;
    double _frequency;
};

#endif //KGRAM_H
