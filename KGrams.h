//
// Interface definition for the KGrams class, for storing a map from a kgram string to its frequency
//
// Author: Max Benson
// Date: 08/30/2022
//
#ifndef KGRAMS_H
#define KGRAMS_H

#include <map>
#include <string>
using std::map;
using std::string;

class KGrams {
public:
    KGrams();

    map<string, double> Profile() const;

    bool LoadProfileFromFile(const string& fileName);
    void CreateProfileFromText(const string& text, unsigned kgramLength, unsigned numberKgrams);

    // These are public so they can be tested independently
    static map<string, double> KGramsIn(const string& text, unsigned kGramLength);
    static map<string, double> Normalize(const map<string, double>& profile);
    static map<string, double> TopKGramsIn(const map<string, double>& profile, unsigned numToKeep);
    static double CosineSimilarityOf(const map<string, double>& lhs, const map<string, double>& rhs);

private:
    static bool GetChar(const string& token, size_t& index, char& ch);

    map<string, double> _profile;
};


#endif //KGRAMS_H
