# Language Identification

If you use a web browser to navigate to a site that is not written in your native language it may be able to automatically detect the language the site is written in.  You might wonder how it can do this.
This lab will lead you through implementing a method for performing automatic language detection that will give you practice using the STL `map` and `priority_queue` template classes.
### Trigram Profiles
The approach we’ll be using for language identification is based on **trigram profiles**. To understand what a trigram profile is, let’s do an example. Suppose we have this (admittedly silly) piece of text:
`A BANANA BANDANA`
The trigram profile for this string is a collection of all its length-three substrings, along with the number of times that length-three substring appears. Specifically, it’s this group:
```
"ANA": 3
" BA": 2
"A B": 2
"BAN": 2
"AND": 1
"DAN": 1
"NA ": 1
"NAN": 1
"NDA": 1
```
That is, the pattern `ANA` appears three times, the pattern `BAN` appears twice, and the pattern `NDA` appears exactly once. These substrings are called trigrams.
Trigram profiles are useful for language identification because the patterns of trigrams that appear in a long piece of text often heavily reflects the language that text was written in. For example, the top trigrams of one Wikipedia article written in English were:
```
" th": 667
"the": 616
"he ": 533
" an": 497
"nd ": 492
"and": 470
"ion": 423
" of": 376
" in": 375
"of ": 363
"tio": 333
"ed ": 320
"ing": 318
"man": 289
"ng ": 288
…
```
That top entry, " th", indicates that the text has a lot of words that start with th. You can see that the word "the" is extremely common, as are the suffixes "ing" and "ion".
Contrast this with the most frequent trigrams appearing in a piece written in Spanish:

```
" de": 531
"os ": 396
"de ": 374
"ent": 298
" la": 293
"es ": 277
"la ": 239
"el ": 232
" co": 217
" es": 208
"en ": 198
"ien": 198
"nte": 196
"as ": 193
" en": 185
…
```

The trigram frequencies in written English are very different than in Spanish, this is true for other languages as well.   

Your repo contains a database of typical trigram frequencies for many different languages.  Once you have implemented the lab, you will be able to take some text, compute the frequencies of the trigrams appearing the text, and determine which language in the database has the most similar trigram frequencies. 

### Step 0: Add your name and date to the file headers

You will want to do this for **Corpus.cpp**, **KGrams.cpp**, **KGram.cpp**, and **GuessLanguages.cpp**.
### Step 1: Form **k-grams**
A *trigram* is a three-character sequence in a string.  More generally a *k-gram* is a *k*-character sequence in a string where *k* is some integer.  Although we are only going to use trigrams for language identification, the classes will write will work for any positive value of *k*.

You should now implement the `KGrams::KGramsIn` static method.  This method takes as input a `string`, and returns a `map<string, double>` containing the frequencies of all the k-grams of length `kGramLength`. Each key stored in the map should be a substring of length `kGramLength`, and the value associated to the key should be the number of times that this k-gram appears in the string. 
Any k-gram that doesn’t appear in the text should not be present in the map, not even with value zero.

The input string might be shorter than `kGramLength`. If that happens, there are no k-grams, and you should return an empty map.

Make sure that your code passes the **--test:kgrams** validation test.

By the way, if you look at the test code, you may be surprised to see test cases for a string in Devanagari (used in the northern Indian subcontinent) and a string in Hebrew.  The scripts used for these languages require more than one C++ `char` per glyph.  And even worse, the char values representing the glyphs do not correspond to characters on our keyboards.  Instead, they are specified in octal (base 8) format `\ddd` where the d’s are digits.

That may seem a little scary, but you don’t have to code specially for these cases. 


### Step 2: Normalize Frequencies
We now have a `map<string, double>` representing the trigrams in the original text.  But right now, the frequencies aren’t readily comparable because if you computed them from a long piece of text the frequencies would be larger in magnitude than if you computed them from a short piece of text.
You next job is to *normalize* the frequencies in a map by doing the following:
-	Add up the squares of all the frequencies in the map.
-	Divide each frequency by the square root of this number.
For example, suppose we have these trigrams:
```
"aaa": 3
"baa": 1
"aab": 1
```
Then we would compute the number 32 + 12 + 12 = 11, then divide each number by the square root of eleven to get these new frequencies:
```
"aaa": 0.904534
"baa": 0.301511
"aab": 0.301511
```
You should now implement the `KGrams::Normalize` static method that takes k-gram profile and returns a normalized version of the profile.
If the input map is empty or does not contain any nonzero values, then you should return an empty map.

Make sure that your code passes the **--test:normalize** validation test.

### Step 3: Implement the `KGram` class

We are going to use the `KGram` class in next step, so let’s implement the class now.
The `KGram` class is not complicated.  It stores the text of a k-gram and its frequency.  

Implement the constructor, the two accessors, and the `<` operator.  

There is wrinkle with the `<` operator.   You are going to push `KGram` objects on an STL `priority_queue`.  Then you will remove the least frequent k-grams from the queue until you have the desired number of most frequent k-grams left on the queue.  It turns out that  the STL  `priority_	queue` is based on a *max-heap* and it uses the `<` operator to compare the `KGram` objects.  So if you dequeue an item, you would be taking off the most frequent item.  That's not what you want.  The solution is to "lie" and and return `true` when `>` is true, and `false` when it `>` is not true.

Make sure that your code passes the **--test:kgram** validation test.


### Step 4: Filter out uncommon **k-grams**
While all texts written in a particular language will show a strong degree of similarity between their most frequent trigrams, the infrequent trigrams in two pieces of text written in the same language often differ greatly. For example, these infrequent trigrams often reflect uncommon words that appear a few times in a text.

To address this, you are now going to implement the static method `KGrams::TopKGramsIn`.  This method takes as input a k-gram profile and a maximum number of k-grams to keep, then returns a map containing only the `numToKeep` most frequent k-grams in the profile. If `numToKeep` is bigger than the number of k-grams in the profile, you should return all the original k-grams. 

You should form a `KGram` object for each (key, frequency) pair in the profile and enqueue them into a priority queue.  Then you will dequeue `KGram` objects until there are at most `numToKeep` `KGram` objects left in the queue.  At that point you will insert the information from those remaining objects into the new map that you are going to return. 

Make sure that your code passes the **--test:top** validation test.

### Step 5: Compute the cosine similarity

Once we have profiles with normalized frequencies we can measure the similarity between two k-gram profiles.  There are many ways to define what “most similar to” means, but one of the most common ways to do this uses something called the cosine similarity (also called the dot product).  

Here’s how you compute it: for each trigram that appears in both P₁ and P₂, multiply the frequency of that trigram in P₁ and P₂, then add up all the numbers you found this way.

As an example, consider these two trigram profiles:
```
Profile 1
"aaa": 0.333
"bbb": 0.667
"ccc": 0.667
Profile 2
"bbb": 0.333
"ccc": 0.667
"ddd": 0.667
```
These two trigram sets have the trigrams "bbb" and "ccc" in common. We’d therefore find their cosine similarity by computing
```
(product of "bbb" frequencies) + (product of "ccc" frequencies)
    = (0.667 × 0.333) + (0.667 × 0.667)
    = 0.667
```
The frequencies of "aaa" and "ddd" aren’t relevant here, since those trigrams appear in only one of the two trigram sets.
In the context of trigrams, cosine similarities range from 0 (the two documents have no trigrams in common) to 1 (the two documents have identical relative trigram frequencies).

Implement the static method `KGrams::CosineSimilarityOf`.

Make sure that your code passes the **--test:similar** validation test.

### Step 6: Complete the implementation of the `KGrams` class

The following methods still need implementation:
1)	Default constructor – this doesn’t have to do anything, but it is required.  Make sure you figure out why it is required.  If you are having trouble figuring out why, comment it out and see what doesn’t compile.
2)	`Profile()` accessor
3)	`CreateProfileFromText()` Unlike the methods you’ve written in the previous steps, this is not static.  It generates the k-grams from the string, normalizes them, and selects the most frequent `numberKgrams` and saves them into `_profile` data member.  Call the methods you’ve written above to implement this method.

### Step 7: Work on the `Corpus` class

A string of text with an associated language is called a *corpus* (plural *corpora*).  The `Corpus` class is based on this idea.  
We are going to use **composition** to implement most of the methods of this class.

It has two data members:
```
string _language;
KGrams _kgrams;
```
When a `Corpus` object is constructed, the value for `_language` is passed in as a parameter, but `_kgrams` object is filled with k-grams post-construction time by calling a method.  
1)	Implement the constructor for the `Corpus` class.
2)	Implement the `Language` accessor for the `Corpus` class
3)	Then using composition implement `Profile()`, `CreateProfileFromText`, and `LoadProfileFromText`
4)	Finally, implement the `<` operator on the `Corpus` class.  You can just compare the values of `_language`.  This is needed because we want to use the STL `set` template class to form set of `Corpus` objects.

### Step 8: Guess a text’s language

At this point, you have the ability to take a text, extract its trigrams, and normalize its profile. You also have the ability to take two normalized profiles and compare their scores against one another. All that’s left to do now is put everything together to guess the language of a text.

You should do this now by implementing the static method `Corpus::GuessLanguageOf`.  This method takes as input a text’s k-gram profile (which has been normalized and then trimmed to store only the most frequent k-grams) and a set of corpora for different languages. This function then returns the name of the language that has the highest cosine similarity to the text. 

As an edge case, if the set of corpora is empty, you return the string “ERROR”, since in that case there aren’t any languages to pick from.

Once you finish this step you are code complete!

Make sure that your code passes the **--test:codecomplete** validation test.

### Step 9: Find some text in a foreign language and see if it can guess the correct language

The **trigram** subdirectory has one file per language, for many of the world’s different languages. Each file stores a representative trigram profile for its associated language.  The provided test code reads in these files and builds a set of corpora that can be passed to your `GuessLanguageOf `.

Run your code with **--guess** command line parameter.  Check out the fourteen examples of where it your code was used to guess the language of some string of next.  It should guess the first ten examples correctly.  The last four examples give you some ideas about when this trigrams method will fail.

Now look for some text in a foreign language and add a fifteenth example at the end of the `GuessLanguages` function and see if it can successfully guess the language.  If you happen to discuss this with a fellow student, try to make sure the two of you submit examples from different languages.

For example I found a Wikipedia page that was in Tagalog, and copied some of the text from that page, and it was successful in guessing Tagalog:  

```
15. This example is from  a Tagalog Wikipedia site. 
The language probably is Tagalog
```
### Grading

Grading will be based on 

- 20% --test:kgrams 
- 15% --test:normalize 
- 10% --test:kgram
- 20% --test:top
- 15% --test:similar 
- 15% --test:codecomplete
- 5% --guess

You not have to do any calls to dynamic allocation in this lab.  But you still should run **valgrind** because it might tell you that you have problem like a buffer overrun in your code.

There will be deductions for problems such as:

- run time errors
- errors leaks reported by **valgrind**
- modifying any repository files other than **Corpus.cpp**, **KGrams.cpp**,  **KGram.cpp**, and **GuessLanguages.cpp**.
- not editing the file header comments for **Corpus.cpp**, **KGrams.cpp**,  **KGram.cpp**, and **GuessLanguages.cpp**.
- bad coding practices

In most cases, a lab that does not compile will not be worth any credit.
