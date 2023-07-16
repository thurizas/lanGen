# lanGen

Langen is program to help game authors by generating a set of words (Lexicography) for a conlang.  The program allows for defining the phonetic inventory (set of sounds) used by the language by selecting the International 
Phonentic Alphabet (IPA) symbols.  Then the program allows for defining the syllable structure for the language using a C for consonants and V for vowels.  A term in paranthesis is optional.  So for example the syllable 
structure (C)V(C) would correspond the the four syllable structures: V, CV, VC, and CVC.  Finally the program allows for the entry of the maximum number of syllables per word.  The last thing that can be entered is a 
mapping from a sound to a corresponding glyph.

The normal work flow would be
1) Select the phonetic inventory for the language specifing the vowel sounds and the consonant sounds.
2) Specify the maximum number of syllables per word
3) Specify at least on sound to glyph translation scheme
4) Specify the number of words to generate

The process for generating a word is:
1) pick a random number in the range [1, max] where max is the maximum number of syllables per word
2) for each syllable
   2a) pick a random syllable structure
   2b) pick random consonants and vowel sounds to build out syllabel
   2c) add the syllable to the nacent word.
3) add the word to the word-list.  converting the phonetic spelling to a normal spelling using the sound to glyph translation scheme appending the phonetic spelling in a paranthesis.

The phonetic description of the language can be saved (and reloaded from a file), with the default extention of '.pho'

The word list, while displayed on the user interface, can also be saved for future use.
