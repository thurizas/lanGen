#ifndef _constants_h_
#define _constants_h_

#include <cstdint>

static const uint8_t major = 1;
static const uint8_t minor = 1;
static const uint8_t patch = 0;


// structures to define the file format

static const uint32_t magic = 0x006f6870;
static const uint8_t  version = 0x02;
static const uint8_t  little = 0x00;
static const uint8_t  big = 0x01;
static const uint32_t cntXlations = 2;      // number of translations for a phonetic character


typedef struct _header
{
  char      e_id[8];            // identification string 4: magic number 1: version 1: endian-ness 2: padding
  uint32_t  e_cntVowels;        // number of vowels
  uint32_t  e_vowelSize;        // size of a vowel record
  uint32_t  e_offsetVowels;     // offset from beginning of file to where vowels records start
  uint32_t  e_cntConsonants;    // number of consonants
  uint32_t  e_consonantSize;    // size of a consonant record
  uint32_t  e_offsetConsonants; // offset from beginning of file to start of consonant records
  uint32_t  e_maxSyllablesWord; // maximum number of syllables in a word
  uint32_t  e_syllabelRuleLen;  // length of syllable rule
  uint32_t  e_offsetSyllable;   // offset for syllable rule
  uint32_t  e_cntGlyphEntries;  // number of element in glyph table
  uint32_t  e_glyphRecordSize;  // size of a glyph record
  uint32_t  e_offsetGlyphTable; // offset from beginning of file to glyph table start
} fileHdr, * pfileHdr;


typedef std::pair<int, char*> glyphT;  // typedef defining a glyph -- length of ascii encoded string, and the ascii encoded string

typedef struct _xlationHdr
{
  uint32_t  xhCntXlations;      // maximum # of translations for a glyph
  uint32_t  xhCntEntries;       // number of entries 
} xlationHdr, * pxlationHdr;

typedef struct _entry
{
  glyphT*     xlations[2];   // TODO : this needs to reflect cntXlations
} tblEntryT, * ptblEntryT;


#endif