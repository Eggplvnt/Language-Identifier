//
// Test Program for Lab 7 - Language Identification
//
// Author: Max Benson
// Date: 09/01/2022
//
#include <cstring>
#include <iostream>
#include <iomanip>
#include <dirent.h>
using std::cout;
using std::endl;
using std::left;
using std::setw;

#include "KGram.h"
#include "KGrams.h"
#include "Corpus.h"
#include "GuessLanguages.h"

// Forward declarations of test functions
void TestKgramClass(unsigned& testsPassed, unsigned& testsFailed);
void TestKgramsInMethod(unsigned& testsPassed, unsigned& testsFailed);
void TestNormalizeMethod(unsigned& testsPassed, unsigned& testsFailed);
void TestTopKGramsInMethod(unsigned& testsPassed, unsigned& testsFailed);
void TestCosignSimilarityMethod(unsigned& testsPassed, unsigned& testsFailed);
void TestCodeComplete(unsigned& testsPassed, unsigned& testsFailed);
void TestGuessLanguage();
void Test(bool condition, const char* message, unsigned& testsPassed, unsigned& testsFailed);

int main(int argc, char* argv[]) {
    // Process arguments
    if (argc == 2 && strcmp(argv[1], "--test:kgram") == 0) {
        unsigned testsPassed = 0;
        unsigned testsFailed = 0;

        TestKgramClass(testsPassed, testsFailed);

        cout << endl << "TEST SUMMARY: " << 100. * testsPassed / (testsPassed + testsFailed) << "%, PASS = "
             << testsPassed << ", FAIL = " << testsFailed << endl;
        cout << endl;
        cout << "=================================================" << endl;
        cout << "==> Don't forget to run this test under valgrind!" << endl;
        cout << "=================================================" << endl;
        return 0;
    }
    else if (argc == 2 && strcmp(argv[1], "--test:kgrams") == 0) {
        unsigned testsPassed = 0;
        unsigned testsFailed = 0;

        TestKgramsInMethod(testsPassed, testsFailed);

        cout << endl << "TEST SUMMARY: " << 100. * testsPassed / (testsPassed + testsFailed) << "%, PASS = "
             << testsPassed << ", FAIL = " << testsFailed << endl;
        cout << endl;
        cout << "=================================================" << endl;
        cout << "==> Don't forget to run this test under valgrind!" << endl;
        cout << "=================================================" << endl;
        return 0;
    }
    else if (argc == 2 && strcmp(argv[1], "--test:normalize") == 0) {
        unsigned testsPassed = 0;
        unsigned testsFailed = 0;

        TestNormalizeMethod(testsPassed, testsFailed);

        cout << endl << "TEST SUMMARY: " << 100. * testsPassed / (testsPassed + testsFailed) << "%, PASS = "
             << testsPassed << ", FAIL = " << testsFailed << endl;
        cout << endl;
        cout << "=================================================" << endl;
        cout << "==> Don't forget to run this test under valgrind!" << endl;
        cout << "=================================================" << endl;
        return 0;
    }
    else if (argc == 2 && strcmp(argv[1], "--test:top") == 0) {
        unsigned testsPassed = 0;
        unsigned testsFailed = 0;

        TestTopKGramsInMethod(testsPassed, testsFailed);

        cout << endl << "TEST SUMMARY: " << 100. * testsPassed / (testsPassed + testsFailed) << "%, PASS = "
             << testsPassed << ", FAIL = " << testsFailed << endl;
        cout << endl;
        cout << "=================================================" << endl;
        cout << "==> Don't forget to run this test under valgrind!" << endl;
        cout << "=================================================" << endl;
        return 0;
    }
    else if (argc == 2 && strcmp(argv[1], "--test:similar") == 0) {
        unsigned testsPassed = 0;
        unsigned testsFailed = 0;

        TestCosignSimilarityMethod(testsPassed, testsFailed);

        cout << endl << "TEST SUMMARY: " << 100. * testsPassed / (testsPassed + testsFailed) << "%, PASS = "
             << testsPassed << ", FAIL = " << testsFailed << endl;
        cout << endl;
        cout << "=================================================" << endl;
        cout << "==> Don't forget to run this test under valgrind!" << endl;
        cout << "=================================================" << endl;
        return 0;
    }
    else if (argc == 2 && strcmp(argv[1], "--test:codecomplete") == 0) {
        unsigned testsPassed = 0;
        unsigned testsFailed = 0;

        TestCodeComplete(testsPassed, testsFailed);

        cout << endl << "TEST SUMMARY: " << 100. * testsPassed / (testsPassed + testsFailed) << "%, PASS = "
             << testsPassed << ", FAIL = " << testsFailed << endl;
        cout << endl;
        cout << "=================================================" << endl;
        cout << "==> Don't forget to run this test under valgrind!" << endl;
        cout << "=================================================" << endl;
        return 0;
    }
    else if (argc == 2 && strcmp(argv[1], "--guess") == 0) {
        TestGuessLanguage();
        return 0;
    }
    cout << "Usage: LanguageIdentifier [--test:kgram | --test:kgrams | --test:normalize | --test:top | --test:similar | --test:codecomplete | --guess ]" << endl;
    return 1;
}

/**
 * Perform validation testing on the KGram class
 * @param testsPassed
 * @param testsFailed
 */
void TestKgramClass(unsigned& testsPassed, unsigned& testsFailed) {
    KGram kgram1(" th", 667);
    KGram kgram2("the", 616);

    Test(kgram1.Text() == " th" && kgram2.Text() == "the", "Test Kgram::Text()",
         testsPassed, testsFailed);
    Test(kgram1.Frequency() == 667.0 && kgram2.Frequency() == 616.0, "Test Kgram::Frequency()",
         testsPassed, testsFailed);
    Test(kgram1 <  kgram2, "Test Kgram::operator <",
         testsPassed, testsFailed);
    Test(!(kgram2 <  kgram1), "Test Kgram::operator <",
         testsPassed, testsFailed);
    Test(!(kgram1 <  kgram1), "Test Kgram::operator <",
         testsPassed, testsFailed);
}

/**
 * Perform validation testing on the KGrams:KGramsIn method
 * @param testsPassed
 * @param testsFailed
 */
void TestKgramsInMethod(unsigned& testsPassed, unsigned& testsFailed) {
    bool correct;
    map<string, double> kGramMap;

    // Test kGramsIn
    cout << "Test KGramsIn static method" << endl;
    kGramMap = KGrams::KGramsIn("^_^", 3);
    correct = kGramMap.size() == 1
              && kGramMap["^_^"] == 1;
    Test(correct, "Test '*_&', 3", testsPassed, testsFailed);

    kGramMap = KGrams::KGramsIn("them", 3);
    correct = kGramMap.size() == 2
              && kGramMap["the"] == 1
              && kGramMap["hem"] == 1;
    Test(correct, "Test 'them', 3", testsPassed, testsFailed);

    kGramMap = KGrams::KGramsIn("aaaa", 3);
    correct = kGramMap.size() == 1
              && kGramMap["aaa"] == 2;
    Test(correct, "Test 'aaaa', 3", testsPassed, testsFailed);

    kGramMap = KGrams::KGramsIn("ABANANABANDANA", 1);
    correct = kGramMap.size() == 4
              && kGramMap["A"] == 7
              && kGramMap["B"] == 2
              && kGramMap["D"] == 1
              && kGramMap["N"] == 4;
    Test(correct, "Test 'ABANANABANDANA', 1", testsPassed, testsFailed);

    kGramMap = KGrams::KGramsIn("ABANANABANDANA", 2);
    correct = kGramMap.size() == 6
              && kGramMap["AB"] == 2
              && kGramMap["AN"] == 4
              && kGramMap["BA"] == 2
              && kGramMap["DA"] == 1
              && kGramMap["NA"] == 3
              && kGramMap["ND"] == 1;
    Test(correct, "Test 'ABANANABANDANA', 2", testsPassed, testsFailed);

    string devanagari = "दे";
    kGramMap = KGrams::KGramsIn(devanagari, 3);
    correct = kGramMap.size() == 4
              && kGramMap["\244\246\340"] == 1
              && kGramMap["\246\340\245"] == 1
              && kGramMap["\340\244\246"] == 1
              && kGramMap["\340\245\207"] == 1;
    Test(correct, "Test 'दे', 3", testsPassed, testsFailed);

    string ktavAshuri = "דָג";
    kGramMap = KGrams::KGramsIn(ktavAshuri, 3);
    correct = kGramMap.size() == 4
              && kGramMap["\223\326\270"] == 1
              && kGramMap["\270\327\222"] == 1
              && kGramMap["\326\270\327"] == 1
              && kGramMap["\327\223\326"] == 1;
    Test(correct, "Test 'דָג' ", testsPassed, testsFailed);

    kGramMap = KGrams::KGramsIn("ABANANABANDANA", 137);
    correct = kGramMap.size() == 0;
    Test(correct, "Test 'ABANANABANDANA', 137 ", testsPassed, testsFailed);

    kGramMap = KGrams::KGramsIn("A BANANA BANDANA", 3);
    correct = kGramMap.size() == 9
              && kGramMap["ANA"] == 3
              && kGramMap[" BA"] == 2
              && kGramMap["A B"] == 2
              && kGramMap["BAN"] == 2
              && kGramMap["AND"] == 1
              && kGramMap["DAN"] == 1
              && kGramMap["NA "] == 1
              && kGramMap["NAN"] == 1
              && kGramMap["NDA"] == 1;
    Test(correct, "Test 'A BANANA BANDANA', 3", testsPassed, testsFailed);
}

/**
 * Perform validation testing on the KGrams::Normalize method
 * @param testsPassed
 * @param testsFailed
 */
void TestNormalizeMethod(unsigned& testsPassed, unsigned& testsFailed) {
    bool correct;
    map<string, double> normalizationInputMap;
    map<string, double> normalizationOutputMap;

    // Test Normalize
    cout << "Test Normalize static method" << endl;
    normalizationInputMap.clear();
    normalizationInputMap["C"] = 1;
    normalizationInputMap["O"] = 1;
    normalizationInputMap["N"] = 1;
    normalizationInputMap["E"] = 1;
    normalizationOutputMap = KGrams::Normalize(normalizationInputMap);
    correct = normalizationOutputMap.size() == 4
              && normalizationOutputMap["C"] == 0.5
              && normalizationOutputMap["O"] == 0.5
              && normalizationOutputMap["N"] == 0.5
              && normalizationOutputMap["E"] == 0.5;
    Test(correct, "Test 'CONE' all frequencies 1", testsPassed, testsFailed);

    normalizationInputMap.clear();
    normalizationInputMap["C"] = -1;
    normalizationInputMap["O"] = -1;
    normalizationInputMap["N"] = -1;
    normalizationInputMap["E"] = -1;
    normalizationOutputMap = KGrams::Normalize(normalizationInputMap);
    correct = normalizationOutputMap.size() == 4
              && normalizationOutputMap["C"] == -0.5
              && normalizationOutputMap["O"] == -0.5
              && normalizationOutputMap["N"] == -0.5
              && normalizationOutputMap["E"] == -0.5;
    Test(correct, "Test 'CONE' all frequencies -1", testsPassed, testsFailed);

    normalizationInputMap.clear();
    normalizationInputMap["O"] = 3;
    normalizationInputMap["N"] = -4;
    normalizationOutputMap = KGrams::Normalize(normalizationInputMap);
    correct = normalizationOutputMap.size() == 2
              && normalizationOutputMap["O"] == 0.6
              && normalizationOutputMap["N"] == -0.8;
    Test(correct, "Test 'ON' w/ frequencies 3, -4", testsPassed, testsFailed);

    normalizationInputMap.clear();
    normalizationInputMap["simpleton"] = 1e18;
    normalizationOutputMap = KGrams::Normalize(normalizationInputMap);
    correct = normalizationOutputMap.size() == 1
              && normalizationOutputMap.count("simpleton") == 1
              && normalizationOutputMap["simpleton"] >= 0.0
              && normalizationOutputMap["simpleton"] <= 10;
    Test(correct, "Test 'simpleton' w/ frequency 1e18 (huge number)", testsPassed, testsFailed);
}

/**
 * Perform validation testing on the KGrams::TopKGramsIn method
 * @param testsPassed
 * @param testsFailed
 */
void TestTopKGramsInMethod(unsigned& testsPassed, unsigned& testsFailed) {
    bool correct;
    map<string, double> topKGramsInputMap;
    map<string, double> topKGramsOutputMap;

    // Test TopKGramsIn
    cout << "Test TopKGramsIn static method" << endl;
    topKGramsInputMap.clear();
    topKGramsInputMap["A"] = 10;
    topKGramsInputMap["B"] = 30;
    topKGramsInputMap["C"] = 20;

    topKGramsOutputMap = KGrams::TopKGramsIn(topKGramsInputMap, 1);
    correct = topKGramsOutputMap.size() == 1
              && topKGramsOutputMap.count("B") == 1
              && topKGramsOutputMap["B"] == 30;
    Test(correct, "Test A, B, C with frequencies 10, 30, 20, keep = 1", testsPassed, testsFailed);

    topKGramsOutputMap = KGrams::TopKGramsIn(topKGramsInputMap, 2);
    correct = topKGramsOutputMap.size() == 2
              && topKGramsOutputMap.count("B") == 1
              && topKGramsOutputMap.count("C") == 1
              && topKGramsOutputMap["B"] == 30
              && topKGramsOutputMap["C"] == 20;
    Test(correct, "Test A, B, C with frequencies 10, 30, 20, keep = 2", testsPassed, testsFailed);

    topKGramsOutputMap = KGrams::TopKGramsIn(topKGramsInputMap, 3);
    correct = topKGramsOutputMap.size() == 3
              && topKGramsOutputMap.count("A") == 1
              && topKGramsOutputMap.count("B") == 1
              && topKGramsOutputMap.count("C") == 1
              && topKGramsOutputMap["A"] == 10
              && topKGramsOutputMap["B"] == 30
              && topKGramsOutputMap["C"] == 20;
    Test(correct, "Test A, B, C with frequencies 10, 30, 20, keep = 3", testsPassed, testsFailed);

    topKGramsOutputMap = KGrams::TopKGramsIn(topKGramsInputMap, 137);
    correct = topKGramsOutputMap.size() == 3
              && topKGramsOutputMap.count("A") == 1
              && topKGramsOutputMap.count("B") == 1
              && topKGramsOutputMap.count("C") == 1
              && topKGramsOutputMap["A"] == 10
              && topKGramsOutputMap["B"] == 30
              && topKGramsOutputMap["C"] == 20;
    Test(correct, "Test A, B, C with frequencies 10, 30, 20, keep = 137", testsPassed, testsFailed);

    topKGramsOutputMap = KGrams::TopKGramsIn(topKGramsInputMap, 0);
    correct = topKGramsOutputMap.size() == 0;
    Test(correct, "Test A, B, C with frequencies 10, 30, 20, keep = 0", testsPassed, testsFailed);

    topKGramsInputMap.clear();
    topKGramsInputMap["A"] = 2;
    topKGramsInputMap["B"] = 1;
    topKGramsInputMap["C"] = 0;
    topKGramsInputMap["D"] = -1;
    topKGramsInputMap["E"] = -2;
    topKGramsInputMap["F"] = -3;
    topKGramsInputMap["G"] = -4;
    topKGramsInputMap["H"] = -5;
    topKGramsOutputMap = KGrams::TopKGramsIn(topKGramsInputMap, 5);
    correct = topKGramsOutputMap.size() == 5
              && topKGramsOutputMap.count("A") == 1
              && topKGramsOutputMap.count("B") == 1
              && topKGramsOutputMap.count("C") == 1
              && topKGramsOutputMap.count("D") == 1
              && topKGramsOutputMap.count("E") == 1
              && topKGramsOutputMap["A"] == 2
              && topKGramsOutputMap["B"] == 1
              && topKGramsOutputMap["C"] == 0
              && topKGramsOutputMap["D"] == -1
              && topKGramsOutputMap["E"] == -2;
    Test(correct, "Test with zero and negative frequencies", testsPassed, testsFailed);

    topKGramsInputMap.clear();
    topKGramsInputMap["A"] = 10.1;
    topKGramsInputMap["B"] = 10.2;
    topKGramsInputMap["C"] = 10.3;
    topKGramsOutputMap = KGrams::TopKGramsIn(topKGramsInputMap, 1);
    correct = topKGramsOutputMap.size() == 1
              && topKGramsOutputMap.count("C") == 1
              && topKGramsOutputMap["C"] == 10.3;
    Test(correct, "Test with fractional frequencies - 1", testsPassed, testsFailed);

    topKGramsInputMap.clear();
    topKGramsInputMap["A"] = 10.3;
    topKGramsInputMap["B"] = 10.2;
    topKGramsInputMap["C"] = 10.1;
    topKGramsOutputMap = KGrams::TopKGramsIn(topKGramsInputMap, 1);
    correct = topKGramsOutputMap.size() == 1
              && topKGramsOutputMap.count("A") == 1
              && topKGramsOutputMap["A"] == 10.3;
    Test(correct, "Test with fractional frequencies - 2", testsPassed, testsFailed);

    topKGramsInputMap.clear();
    topKGramsInputMap["A"] = 10.2;
    topKGramsInputMap["B"] = 10.3;
    topKGramsInputMap["C"] = 10.1;
    topKGramsOutputMap = KGrams::TopKGramsIn(topKGramsInputMap, 1);
    correct = topKGramsOutputMap.size() == 1
              && topKGramsOutputMap.count("B") == 1
              && topKGramsOutputMap["B"] == 10.3;
    Test(correct, "Test with fractional frequencies - 3", testsPassed, testsFailed);
}

/**
 * Perform validation testing on the KGrams class
 * @param testsPassed
 * @param testsFailed
 */
void TestCosignSimilarityMethod(unsigned& testsPassed, unsigned& testsFailed) {
    bool correct;
    map<string, double> similarityInputMap1;
    map<string, double> similarityInputMap2;

    // Test CosineSimilarityOf
    cout << "Test CosineSimilarityOf static method" << endl;
    similarityInputMap1.clear();
    similarityInputMap2.clear();
    similarityInputMap1["A"] = 1;
    similarityInputMap2["A"] = 1;
    Test(KGrams::CosineSimilarityOf(similarityInputMap1, similarityInputMap2) == 1,
         "Test similarity with one shared key", testsPassed, testsFailed);

    similarityInputMap1.clear();
    similarityInputMap2.clear();
    similarityInputMap1["A"] = 1;
    similarityInputMap2["B"] = 1;
    Test(KGrams::CosineSimilarityOf(similarityInputMap1, similarityInputMap2) == 0,
         "Test similarity with no shared keys", testsPassed, testsFailed);

    similarityInputMap1.clear();
    similarityInputMap2.clear();
    similarityInputMap1["O"] = 1;
    similarityInputMap1["C"] = 2;
    similarityInputMap1["E"] = 3;
    similarityInputMap1["A"] = 4;
    similarityInputMap1["N"] = 5;
    similarityInputMap2["C"] = -2;
    similarityInputMap2["E"] = -3;
    similarityInputMap2["A"] = -4;
    similarityInputMap2["N"] = -5;
    Test(KGrams::CosineSimilarityOf(similarityInputMap1, similarityInputMap2) == -54,
         "Test similarity with some keys in RHS but not in LHS", testsPassed, testsFailed);

    similarityInputMap1.clear();
    similarityInputMap2.clear();
    similarityInputMap1["C"] = 2;
    similarityInputMap1["E"] = 3;
    similarityInputMap1["A"] = 4;
    similarityInputMap1["N"] = 5;
    similarityInputMap2["O"] = 1;
    similarityInputMap2["C"] = -2;
    similarityInputMap2["E"] = -3;
    similarityInputMap2["A"] = -4;
    similarityInputMap2["N"] = -5;
    Test(KGrams::CosineSimilarityOf(similarityInputMap1, similarityInputMap2) == -54,
         "Test similarity with some keys in LHS but not in RHS", testsPassed, testsFailed);

    similarityInputMap1.clear();
    similarityInputMap2.clear();
    similarityInputMap1["C"] = 2;
    similarityInputMap1["E"] = 3;
    similarityInputMap1["A"] = 4;
    similarityInputMap2["O"] = 1;
    similarityInputMap2["E"] = -3;
    similarityInputMap2["A"] = -4;
    Test(KGrams::CosineSimilarityOf(similarityInputMap1, similarityInputMap2) == -25,
         "Test similarity with keys missing from both sidesS", testsPassed, testsFailed);
}

/**
 * Perform validation testing on code complete
 * @param testsPassed
 * @param testsFailed
 */
void TestCodeComplete(unsigned& testsPassed, unsigned& testsFailed) {
    bool correct;
    // Test GuessLanguageOf
    cout << "Test GuessLanguageOf static method" << endl;
    map<string, double> profile1;
    map<string, double> profile2;
    map<string, double> profile3;
    map<string, double> profile4;
    map<string, double> profile5;

    map<string, double> cprofile1;
    map<string, double> cprofile2;
    map<string, double> cprofile3;
    map<string, double> cprofile4;
    map<string, double> cprofile5;

    set<Corpus> corpora;

    // First test case
    {
        Corpus corpus1("O");
        Corpus corpus2("C");
        Corpus corpus3("E");
        Corpus corpus4("A");
        Corpus corpus5("N");

        corpus1.CreateProfileFromText("O", 1, 1);
        corpus2.CreateProfileFromText("C", 1, 1);
        corpus3.CreateProfileFromText("E", 1, 1);
        corpus4.CreateProfileFromText("A", 1, 1);
        corpus5.CreateProfileFromText("N", 1, 1);

        cprofile1 = corpus1.Profile();
        cprofile2 = corpus2.Profile();
        cprofile3 = corpus3.Profile();
        cprofile4 = corpus4.Profile();
        cprofile5 = corpus5.Profile();

        corpora.clear();
        corpora.insert(corpus1);
        corpora.insert(corpus2);
        corpora.insert(corpus3);
        corpora.insert(corpus4);
        corpora.insert(corpus5);

        profile1.clear();
        profile1["O"] = 1;
        profile2.clear();
        profile2["C"] = 1;
        profile3.clear();
        profile3["E"] = 1;
        profile4.clear();
        profile4["A"] = 1;
        profile5.clear();
        profile5["N"] = 1;

        correct = cprofile1.size() == 1 && cprofile1.count("O") == 1 && cprofile1["O"] == 1
                  && cprofile2.size() == 1 && cprofile2.count("C") == 1 && cprofile2["C"] == 1
                  && cprofile3.size() == 1 && cprofile3.count("E") == 1 && cprofile3["E"] == 1
                  && cprofile4.size() == 1 && cprofile4.count("A") == 1 && cprofile4["A"] == 1
                  && cprofile5.size() == 1 && cprofile5.count("N") == 1 && cprofile5["N"] == 1
                  && Corpus::GuessLanguageOf(profile1, corpora) == "O"
                  && Corpus::GuessLanguageOf(profile2, corpora) == "C"
                  && Corpus::GuessLanguageOf(profile3, corpora) == "E"
                  && Corpus::GuessLanguageOf(profile4, corpora) == "A"
                  && Corpus::GuessLanguageOf(profile5, corpora) == "N";
        Test(correct, "Test GuessLanguageOf with perfect similarity", testsPassed, testsFailed);
    }

    //Second test case
    {
        Corpus corpus1("O");
        Corpus corpus2("C");
        Corpus corpus3("E");
        Corpus corpus4("A");
        Corpus corpus5("N");

        corpus1.CreateProfileFromText("OOC", 1, 2);
        corpus2.CreateProfileFromText("CCE", 1, 2);
        corpus3.CreateProfileFromText("EEA", 1, 2);
        corpus4.CreateProfileFromText("AAN", 1, 2);
        corpus5.CreateProfileFromText("NNO", 1, 2);

        cprofile1 = corpus1.Profile();
        cprofile2 = corpus2.Profile();
        cprofile3 = corpus3.Profile();
        cprofile4 = corpus4.Profile();
        cprofile5 = corpus5.Profile();

        corpora.clear();
        corpora.insert(corpus1);
        corpora.insert(corpus2);
        corpora.insert(corpus3);
        corpora.insert(corpus4);
        corpora.insert(corpus5);

        profile1.clear();
        profile1["O"] = 1;
        profile2.clear();
        profile2["C"] = 1;
        profile3.clear();
        profile3["E"] = 1;
        profile4.clear();
        profile4["A"] = 1;
        profile5.clear();
        profile5["N"] = 1;

        correct = cprofile1.size() == 2 && cprofile1.count("O") == 1 && cprofile1["O"] == 0.8944271909999159
                  && cprofile1.count("C") && cprofile1["C"] == 0.4472135954999579
                  && cprofile2.size() == 2 && cprofile2.count("C") == 1 && cprofile2["C"] == 0.8944271909999159
                  && cprofile2.count("E") && cprofile2["E"] == 0.4472135954999579
                  && cprofile3.size() == 2 && cprofile3.count("E") == 1 && cprofile3["E"] == 0.8944271909999159
                  && cprofile3.count("A") && cprofile3["A"] == 0.4472135954999579
                  && cprofile4.size() == 2 && cprofile4.count("A") == 1 && cprofile4["A"] == 0.8944271909999159
                  && cprofile4.count("N") && cprofile4["N"] == 0.4472135954999579
                  && cprofile5.size() == 2 && cprofile5.count("N") == 1 && cprofile5["N"] == 0.8944271909999159
                  && cprofile5.count("O") && cprofile5["O"] == 0.4472135954999579
                  && Corpus::GuessLanguageOf(profile1, corpora) == "O"
                  && Corpus::GuessLanguageOf(profile2, corpora) == "C"
                  && Corpus::GuessLanguageOf(profile3, corpora) == "E"
                  && Corpus::GuessLanguageOf(profile4, corpora) == "A"
                  && Corpus::GuessLanguageOf(profile5, corpora) == "N";
        Test(correct, "Test GuessLanguageOf with imperfect similarity", testsPassed, testsFailed);
    }

    //Third test case
    {
        Corpus corpus1("Karel");
        Corpus corpus2("Trisha");
        Corpus corpus3("Chris");
        Corpus corpus4("Jerry");

        corpus1.CreateProfileFromText("ROOBT", 1, 6);
        corpus2.CreateProfileFromText("TRISHA", 1, 6);
        corpus3.CreateProfileFromText("CHRIS", 1, 6);
        corpus4.CreateProfileFromText("JERRY", 1, 6);

        cprofile1 = corpus1.Profile();
        cprofile2 = corpus2.Profile();
        cprofile3 = corpus3.Profile();
        cprofile4 = corpus4.Profile();

        corpora.clear();
        corpora.insert(corpus1);
        corpora.insert(corpus2);
        corpora.insert(corpus3);
        corpora.insert(corpus4);

        profile1.clear();
        profile1["R"] = 1;

        correct = cprofile1.size() == 4 && cprofile2.size() == 6 && cprofile3.size() == 5 && cprofile4.size() == 4
                  && Corpus::GuessLanguageOf(profile1, corpora) == "Jerry";
        Test(correct, "Test GuessLanguageOf with more complex inputs", testsPassed, testsFailed);
    }

}

/**
 * Test language identification using profiles of real languages
 * @param testsPassed
 * @param testsFailed
 */
void TestGuessLanguage() {
    set<Corpus> corpora;

    // Read in a set of corpora
    corpora.clear();

    DIR *dir;
    struct dirent *ent;
    string dirName = "../trigrams";

    if ((dir = opendir(dirName.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            string fileName = ent->d_name;
            if (fileName.find(".3grams") != string::npos) {
                string language = fileName.substr(0, fileName.find('.'));
                Corpus corpus(language);

                if (corpus.LoadProfileFromFile(dirName + "/" + fileName)) {
                    corpora.insert(corpus);
                } else {
                    cout << "ERROR cannot load the trigram file named '" << fileName << "'" << endl;
                }
            }
        }
        closedir(dir);
        cout << corpora.size() << " language corpora loaded" << endl;
    } else {
        cout << "ERROR: cannot open the trigrams directory" << endl;
    }

    // Now use it to guess languages
    GuessLanguages(corpora);
}

/**
 * Test the implementation of the SortedList class.  This code doesn't catch memory problems
 * make sure you run under valgrind to find and correct them
 * @param testsPassed running total of number of tests passed, updated upon return
 * @param testsFailed running total of number of tests failed, updated upon return
 */
void Test(bool condition, const char* message, unsigned& testsPassed, unsigned& testsFailed){
    if (condition){
        cout << "+\tTEST PASSED (" << left << setw(70) << message << ") Total Passed: " << ++testsPassed << endl;
    }
    else{
        ++testsFailed;
        cout << "-\tTEST FAILED (" << left << setw(70) << message << ") " << string(25, '*') << "   <----- Failed" << endl;
    }
}
