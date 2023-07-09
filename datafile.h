#ifndef _datafile_h_
#define _datafile_h_

#include "DataEntry.h"
#include "constants.h"

#include <QString>
#include <QFile>
#include <QDataStream>
/*
*    this file describes the output format for a language file (*.pho) The file format is as follows:
*
*        +--------------------+
*        | header             |
*        +--------------------+
*        | vowels             |
*        +--------------------+
*        | consonants         |
*        +--------------------+
*        | additional classes |
*        +--------------------+
*        | production rules   |
*        +--------------------+
*        | glyph table        |
*        +---------------------
* 
* A expanded view of a file (english_new.pho) is shown below;
* 
* 0x00000000    006F6870  - magic number
*               01        - version    (1)
*               00        - endianness (little)
*               0000      - padding
*               08000000  - number of vowels
*               02000000  - size of vowel
*               38000000  - offset to vowel list
* 0x00000014    19000000  - number of consonants
*               02000000  - size of consonants
*               48000000  - offset to consonant list
*               03000000  - max syllable's per word
* 0x00000024    12000000  - rule length
*               7A000000  - offset to rules
*               00000000  - number of entries in glyph table 
*               06000000  - size of an entry in glyph table
*               8C000000  - offset to glyph table
* 0x00000038    E600      - beginning of vowel list
*               6500 4900 5202 8A02 8C02 5902 5402
* 0x00000048    6200       - start of consonant list
*               6400 6600 6700 6800 6B00 6C00 6D00 6E00 7000 7200 7300 7400
*               7600 7A00 9202 8302 B803 F000 7302 6A00 8D02 7700 A402 A702
* 0x0000007A    28 43 29 56 28 43 29 7C 28 43 29 28 43 29 56 28 43 29
*                (  C  )  V (   C  )  | (  C  )  (  C  )  V  (  C  )      18 characters
* 
*/

class datafile
{
public:
  enum mode: uint8_t { READ, WRITE };

  datafile();
  datafile(QString f);
  ~datafile();

  bool open(int);
  void close();

  bool isOpen() { return m_open; }

  static bool isValid(QString f);

  void readHeader(fileHdr*);
  void writeHeader(CDataEntry* m_pWidget);
  QVector<QChar>  readVowels();
  void writeVowels(CDataEntry* m_pWidget);
  QVector<QChar>  readConsonants();
  void writeConsonants(CDataEntry* m_pWidget);
  QString readRules();
  void writeRules(CDataEntry* m_pWidget);
  QMap<QChar, ptblEntryT> readGlyphs();
  void writeGlyphs(CDataEntry* m_pWidget);





private:
  QString      m_filename;
  QFile*       m_inFile;
  QDataStream* m_in;

  fileHdr      m_hdr;
  bool         m_open;
};

#endif