//
// Interface definition for the Corpus class storing a language and its kgram profile
//
// Author: Max Benson
// Date: 08/30/2022
//

#ifndef CORPUS_H
#define CORPUS_H

#include <string>
#include <set>
using std::string;
using std::set;

#include "KGrams.h"

class Corpus {
public:
    Corpus(const string& language);

    string Language() const;
    map<string, double> Profile() const;

    bool LoadProfileFromFile(const string& filePath);
    void CreateProfileFromText(const string& text, unsigned kgramLength, unsigned numberKgrams);

    friend bool operator< (const Corpus& lhs, const Corpus& rhs);

    static string GuessLanguageOf(const map<string, double>& profile, const set<Corpus>& corpora);

private:
    string _language;
    KGrams _kgrams;
};


#endif //CORPUS_H
