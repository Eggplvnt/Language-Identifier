//
// Implementation of the KGrams class,  for storing a map from a kgram string to its frequency
//
// Author: Max Benson
// Date: 08/30/2022
// Modifier: Ilya Bukhalau
// Modification Date: 11/28/22
//

#include <fstream>
#include <iostream>
#include <cmath>
#include <queue>
#include <cassert>
using std::ifstream;
using std::priority_queue;

#include "KGrams.h"
#include "KGram.h"

/**
 * Default Constructor for KGrams
 * This is necessary because the corpus constructor
 * has KGrams as a member variable which is not
 * initialized at construction time
 */
KGrams::KGrams() {
    map<string, double> init;
    _profile = init;
}

/**
 * Accessor for Profile
 * The result is only meaningful after the profiles is created by
 * calling either CreateProfileFromText or LoadProfileFromFile
 * @return kgram profile
 */
map<string, double> KGrams::Profile() const {
    return _profile;
}


/**
 * Creates a kgram profile by reading them from a file in JSON value format
 * @param filePath path name of file tp read from
 * @return true if file could be loaded successfully, false otherwise
 */
void KGrams::CreateProfileFromText(const string& text, unsigned kgramLength, unsigned numberKgrams) {
    map<string, double> first = KGramsIn(text, kgramLength);
    first = Normalize(first);
    first = TopKGramsIn(first, numberKgrams);
    _profile = first;
}

/**
 * Static method that breaks a string into kgrams and tabulates their
 * frequencies (occurrence count) building a map
 * @param text text to form kgrams from
 * @param kgramLength the value of "k", e.g. if =3, forms trigrams
 * @return the map that was generated
 */
map<string, double> KGrams::KGramsIn(const string& text, unsigned kGramLength) {
    map<string, double> profile;
    string arr[1000];
    int pos = 0;
    int freq = 1;
    if (kGramLength <= text.length()) {
        for (int i = 0; i <= text.length() - kGramLength; i++) {
            string gram;
            for (int j = 0; j < kGramLength; j++) {
                gram += text[i + j];
            }
            arr[pos] = gram;
            pos++;
        }
        for (int i = 0; i < pos; i++) {
            for (int j = i + 1; j < pos; j++) {
                if (arr[i] != "found" && arr[i] == arr[j]) {
                    freq++;
                    arr[j] = "found";
                }
            }
            if (arr[i] != "found") {
                profile.insert({arr[i], freq});
            }
            freq = 1;
        }
    }
    return profile;
}

/**
 * Static method that normalizes a kgram frequencies by making the
 * frequency vector be a unit vector.  Specifically it sums up the
 * squares of the frequencies, takes the square root, and then divides
 * each frequency by that square root
 * @param profile map to normalize
 * @return normalized map
 */
map<string, double> KGrams::Normalize(const map<string, double>& profile) {
    map<string, double> ret;
    string oldString;
    double newFreq;
    double sum;

    for (const auto& s : profile) {
        sum += fabs(pow(s.second, 2));
    }
    for (const auto& s : profile) {
        ret.insert({s.first, (s.second / sqrt(sum))});
    }
    return ret;
}

/**
 * Static method that removes less frequent kgrams, retaining at most
 * numToKeep kgrams.  Uses a min priority queue to remove the lesser ones
 * @param profile map to prune
 * @param numToKeep number of kgrams to retain
 * @return pruned map
 */
map<string, double> KGrams::TopKGramsIn(const map<string, double>& profile, unsigned numToKeep) {
    map<string, double> toReturn;
    priority_queue<KGram> grams;
    int size;

    if (numToKeep == 0) {
        return toReturn;
    } else if (profile.size() > numToKeep) {
        for (const auto &s: profile) {
            KGram kg = KGram(s.first, s.second);
            grams.push(kg);
        }
        size = grams.size()-numToKeep;
        for (int i = 0; i < size; i++) {
            KGram kg = grams.top();
            grams.pop();
        }
        size = grams.size();
        for (int i = 0; i < size; i++) {
            KGram kg = grams.top();
            toReturn.insert({kg.Text(), kg.Frequency()});
            grams.pop();
        }
    } else {
        return profile;
    }
    return toReturn;
}

/**
 * Static method to compute the "cosing similarity" or dot product
 * between the frequency vectors of two profiles
 * @param left first profile
 * @param right second profile
 * @return cosine similarity between the two
 */
double KGrams::CosineSimilarityOf(const map<string, double>& lhs, const map<string, double>& rhs)  {
    double sim;
    double total = 0;

    for (const auto& l : lhs) {
        for (const auto &r: rhs) {
            if (l.first == r.first) {
                sim = l.second * r.second;
                total += sim;
            }
        }
    }
    return total;
}

/**
 * Creates a kgram profile from a text string
 * @param text text to form kgrams from
 * @param kgramLength the value of "k", e.g. if =3, forms trigrams
 * @param numberKgrams retain at most this many of the most frequent kgrams
 */
bool KGrams::LoadProfileFromFile(const string& fileName) {
    ifstream fin;
    string line;
    size_t indexRunning;
    map<string, double> rawKgrams;
    bool ending = false;

    // Open the file
    fin.open(fileName);
    if (!fin.is_open()) {
        return false;
    }

    // It's all on one line
    getline(fin, line);

    // First character should be {
    if (line.length() == 0 || line[0] != '{') {
        return false;
    }
    indexRunning = 1;

    // Loop over kgrams
    do {
        size_t indexStartQuote;
        size_t indexEndQuote;
        size_t indexStartNumber;
        size_t indexEndNumber;
        string trigram;
        string number;
        double frequency;

        //
        // Isolate the quoted kgram string
        //
        indexStartQuote = line.find('\"',indexRunning);
        if (indexStartQuote == string::npos) {
            return false;
        }

        // Find the ending quote
        indexEndQuote = indexStartQuote+1;
        while(true) {
            indexEndQuote = line.find('\"',indexEndQuote);
            if (indexEndQuote == string::npos) {
                return false;
            }
            // Unless it is preceded by a backslash (and not by two backslashes) we are done
            if (line[indexEndQuote-1] != '\\' || line[indexEndQuote-2] == '\\' ) {
                break;
            }
            indexEndQuote = indexEndQuote+1;
        }

        // Get the three characters of the trigram
        indexRunning = indexStartQuote+1;
        for (size_t i = 0; i < 3; i ++) {
            char ch;

            if (!GetChar(line, indexRunning, ch)) {
                return false;
            }
            trigram += ch;
        }

        // At this point we should be sitting on the end quote
        if (indexRunning++ != indexEndQuote) {
            return false;
        }

        // A colon should come next;
        if (indexRunning >= line.length() || line[indexRunning++] != ':') {
            return false;
        }

        // Search for a comma or closing brace
        indexStartNumber = indexRunning;
        indexEndNumber = line.find(',', indexStartNumber);
        if (indexEndNumber == string::npos) {
            indexEndNumber = line.find('}', indexStartNumber);
            if (indexEndNumber == string::npos) {
                return false;
            }
            ending = true;
        }
        number = line.substr(indexStartNumber,indexEndNumber-indexStartNumber);
        frequency = stod(number);
        rawKgrams[trigram] = frequency;

        //cout << Escape(trigram) << ", " << frequency << endl;

        //Advnace our index
        indexRunning = indexEndNumber+1;
    } while (!ending);

    map<string, double> normalized = Normalize(rawKgrams);
    _profile = TopKGramsIn(normalized, 2000);
    return true;
}

/**
 * Private static method to decode a "character" inside a string in a file
 * This is complicated because it "understands" various character escape sequences
 * Note when we decode a "character" we might advance the index up to 4 positions because
 * of octal escape sequences of the form \nnn
 * @param token string
 * @param index begins at the start of the "character", is advanced to next "character" upon return
 * @param ch the "character" we decoded
 * @return true if decoding succeeded, false otherwise
 */
bool KGrams::GetChar(const string& token, size_t& index, char& ch) {
    // We ran off end of token
    if (index >= token.length()) {
        return false;
    }

    // No double quotes allowed
    if (token[index] == '\"') {
        return false;
    }

    // Not an escape sequence
    if (token[index] != '\\') {
        ch = token[index++];
        return true;
    }

    // Skip over backslash, check if we ran off end of token
    if (++index >= token.length()) {
        return false;
    }

    // Handle letter escape sequences
    if (!isdigit(token[index])) {
        switch (token[index]) {
            case 'a':
                ch = '\x07';
                break;
            case 'b':
                ch = '\x08';
                break;
            case 'e':
                ch = '\x1B';
                break;
            case 'f':
                ch = '\x0C';
                break;
            case 'n':
                ch = '\x0A';
                break;
            case 'r':
                ch = '\x0D';
                break;
            case 't':
                ch = '\x09';
                break;
            case 'v':
                ch = '\x0B';
            case '\\':
                ch = '\x5C';
                break;
            case '\'':
                ch = '\x27';
                break;
            case '\"':
                ch = '\x22';
                break;
            case '?':
                ch = '\x3F';
                break;
            default:
                return false;
        }
        index++;
        return true;
    }

    // Now handle NN notation where N's are octal digits

    // Not room left for three digits
    if (index + 2 >= token.length()) {
        return false;
    }

    // Check that all three are octal digits
    if ('0' <= token[index] && token[index] <= '7'
        && '0' <= token[index + 1] && token[index + 1] <= '7'
        && '0' <= token[index + 2] && token[index + 2] <= '7') {

        int code;

        code = (token[index] - '0') * 64 + (token[index + 1] - '0') * 8 + (token[index + 2] - '0');
        if (code > 255) {
            return false;
        }
        ch = (char)code;
        index += 3;
        return true;
    }
    return false;
}
