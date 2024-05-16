//
// Implementation of the Corpus class storing a language and its kgram profile
//
// Author: Max Benson
// Date: 08/30/2022
// Modifier: Ilya Bukhalau
// Modification Date: 11/28/22
//

#include <cassert>
#include <iostream>
#include "Corpus.h"

/**
 * Constructor for Corpus
 * Construction only sets the language, users need to call either CreateProfileFromText
 * or LoadProfileFromFile to create the profile
 * @param language language of this corpus
 */
Corpus::Corpus(const string& language) {
    _language = language;
}

/**
 * Accessor for language
 * @return language associated to this corpus
 */
string Corpus::Language() const {
    return _language;
}

/**
 * Accessor for profile
 * Only meaningful after the profiles is created by calling either
 * CreateProfileFromText or LoadProfileFromFile
 * @return kgram profile for corpus
 */
map<string, double> Corpus::Profile() const {
    return _kgrams.Profile();
}

/**
 * Creates a kgram profile from a text string
 * @param text text to form kgrams from
 * @param kgramLength the value of "k", e.g. if =3, forms trigrams
 * @param numberKgrams retain at most this many of the most frequent kgrams
 */
void Corpus::CreateProfileFromText(const string& text, unsigned kgramLength, unsigned numberKgrams) {
    _kgrams.CreateProfileFromText(text, kgramLength, numberKgrams);
}

/**
 * Creates a kgram profile by reading them from a file in JSON value format
 * @param filePath path name of file tp read from
 * @return true if file could be loaded successfully, false otherwise
 */
bool Corpus::LoadProfileFromFile(const string& fileName) {
    return _kgrams.LoadProfileFromFile(fileName);
}

/**
 * Operator overload for <
 * It is necessary to overload < in order to form set<Corpus>
 * We simply need a way to compare two corpora, so we use the language of the corpus
 * @param lhs the corpus to compare to
 * @param rhs the other corpus to compare to
 * @return true if the language of this is before the language of corpus
 */
bool operator< (const Corpus& lhs, const Corpus& rhs) {
    if (lhs._language < rhs._language) {
        return true;
    }
    return false;
}

/**
 * Static method for finding the language of the corpus in a set of corpora
 * that best matches a specified profile.  There may be >1 corpus that are
 * best, if so its arbitrary which language we return
 * @param profile profile derived from some text that we want to identify the language of
 * @param corpora a set of corpora that we should match against
 * @return name of language of best matching corpus
 */
string Corpus::GuessLanguageOf(const map<string, double>& profile, const set<Corpus>& corpora) {
    string ret;
    double curr;
    double sim = 0;
    if (corpora.empty()) {
        return "ERROR";
    } else {
        for (const auto& p : corpora) {
            curr = KGrams::CosineSimilarityOf(profile, p._kgrams.Profile());
            if (sim < curr) {
                sim = curr;
                ret = p._language;
            }
        }
    }
    return ret;
}

