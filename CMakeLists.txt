cmake_minimum_required(VERSION 3.10)
project(LanguageIdentifier)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LanguageIdentifier main.cpp Corpus.cpp KGrams.cpp KGram.cpp GuessLanguages.cpp)
