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

TODO:
1) allow for setting preference of syllables - for example a language might prefer CV or VC syllables and only infrequently have CVC syllables.  On thought would be to include a percentage, such as
   (C{15})V{5}(C{25}), which would generate V{5}, C{15}V{5}, V{5}C{25}, and C{15}V{5}C{25} and then the individual weights are summed to yield V{5}, CV{20}, VC{30}, and CVC{45} which says that a syllable
   with a structure of CV is four times more likely the a syllable with a structure of V.  Still missing is a way to decrement the weight applied to a syllable, i.e. to yield something like
   V{5}, CV{40}, VC{40}, and CVC{15}.
2) Add additional support for different writing systems,
   * abjad - writting system where consonants are represented and vowels are infered by the reader.  If necessary vowels can be represented by diacritics markings.  Examples of this writting system
             are Arabic and Aramaic.
   * abugida - writting system where consonant-vowel sequences are expressed as a unit.  Each unit is based on the consonant sound with an auxillary symbol for the vowel.  An example would be 
               any writting system derived from Brahmi script, such as devanagari
   * alphabet - each sound has one or more letters (also called graphemes) associated with it.  Examples of this writting system are Latin, Cyrillic, and Greek (done)
   * logogram - a unique symbol (logogram, logograph, or lexigraph) is used to represent a single word.  Examples of this writting system are Egyptian hieroglyphs, Linear A, Linear B, and Sawndip
   * Syllabary - Each syllable (or mora - a timing unit in the language) is represented by a single grapheme.  Languages that use this writting system include Cherokee, Cypriot, and Kana
3) Specify weights for number of syllables in a word.  Might tie in with #1.
   
