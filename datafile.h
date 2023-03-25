#pragma once

/*
   this file describes the output format for a language file (*.pho) 
   The file format is as follows:

   +--------------------+
   | header             |
   +--------------------+
   | vowels             |
   +--------------------+
   | consonants         |
   +--------------------+
   | additional classes |
   +--------------------+
   | production rules   |
   +--------------------+
   | glyph table        |
   +---------------------

   header
      magic number            4 bytes     
      version                 1 byte
      number of vowels        1 byte
      offset for vowels       4 bytes
      size of vowel rec       4 bytes
      number of consonants    1 unsigned byte
      offset for consonants   4 bytes
      size of consonant rec   4 bytes
      number of add'n classes 1 unsigned byte
      offset for consonants   4 bytes
      size of consonant rec   4 bytes
      number of rules         1 unsigned byte
      offset for rules        4 bytes
      size of rule record     4 bytes
      offset for glyph table  4 bytes


 */
