#include "datafile.h"
#include "logger.h"
#include "constants.h"


#include <QString>
#include <QFile>
#include <QDataStream>

datafile::datafile() : m_filename(""), m_inFile(nullptr), m_in(nullptr), m_open(false)
{

}


datafile::datafile(QString f) : m_filename(f), m_inFile(nullptr), m_in(nullptr), m_open(false)
{

}

datafile::~datafile()
{
  if (m_open)
    close();
}

bool datafile::open(int m)
{
  auto mode =  (m == datafile::mode::READ ? QIODevice::ReadOnly : QIODevice::WriteOnly);

  if (m_filename != "")
  {
    m_inFile = new QFile(m_filename);
    if (m_inFile->open(mode))
    {
      m_in = new QDataStream(m_inFile);

      m_open = true;
    }
  }
  else
  {
    CLogger::getInstance()->outMsg(cmdLine, CLogger::level::WARNING, "Please supply a file name");
  }

  return m_open;
}

void datafile::close()
{
  m_inFile->close();
  delete m_in;
  delete m_inFile;
  m_in = nullptr;
  m_inFile = nullptr;
  m_open = false;
}

/************************************************************************************************************************
* function  : isValid   (static function)
*
* abstract  : checks that the magic number and file version are correct.
*
* parameters:
*
* returns   :
*
* written   : Jul 2023 (GKHuber)
************************************************************************************************************************/
bool datafile::isValid(QString f)
{
  bool bRet = false;

  QFile inFile(f);

  if (inFile.open(QIODevice::ReadOnly))
  {
    fileHdr      hdr;
    QDataStream in(&inFile);

    in.readRawData((char*)&hdr, sizeof(fileHdr));

    if ( (hdr.e_id[0] == 0x00) && (hdr.e_id[1] == 0x6f) && (hdr.e_id[2] == 0x68) && (hdr.e_id[3] == 0x70) && (hdr.e_id[4] <= version))
      bRet = true;
    else
    {
      CLogger::getInstance()->outMsg(cmdLine, CLogger::level::WARNING, "file does not appear to be an language generation data file");
    }
  }
  else
  {
    CLogger::getInstance()->outMsg(cmdLine, CLogger::level::WARNING, "unable to open file, check name and retry");
  }

  return bRet;
}

void datafile::readHeader(fileHdr* phdr) 
{
  if (m_open)
  {
    m_in->readRawData((char*)&m_hdr, sizeof(fileHdr));
  }

  memcpy((void*)phdr, &m_hdr, sizeof(fileHdr));
}

void datafile::writeHeader(CDataEntry* m_pWidget)
{
  uint32_t cntVowels = m_pWidget->getVowels()->size();
  uint32_t cntConsonants = m_pWidget->getConsonants()->size();
  uint32_t ruleLen = m_pWidget->getRule().length();
  //fileHdr    hdr;
  
  if (m_open)
  {
    m_hdr.e_id[0] = 0x00; m_hdr.e_id[1] = 0x6f; m_hdr.e_id[2] = 0x68; m_hdr.e_id[3] = 0x70;
    m_hdr.e_id[4] = 0x02; m_hdr.e_id[5] = 0x00; m_hdr.e_id[6] = 0x00; m_hdr.e_id[7] = 0x00;
    m_hdr.e_cntVowels = cntVowels;
    m_hdr.e_vowelSize = sizeof(QChar);
    m_hdr.e_offsetVowels = sizeof(fileHdr);
    m_hdr.e_cntConsonants = cntConsonants;
    m_hdr.e_consonantSize = sizeof(QChar);
    m_hdr.e_offsetConsonants = m_hdr.e_offsetVowels + cntVowels * sizeof(QChar);
    m_hdr.e_maxSyllablesWord = 3;                 // TODO: this needs to be read from the data entry form
    m_hdr.e_syllabelRuleLen = ruleLen;
    m_hdr.e_offsetSyllable = m_hdr.e_offsetConsonants + cntConsonants * sizeof(QChar);
    m_hdr.e_cntGlyphEntries = m_pWidget->getXlationMap().size();
    m_hdr.e_glyphRecordSize = sizeof(tblEntryT);
    m_hdr.e_offsetGlyphTable = m_hdr.e_offsetSyllable + m_hdr.e_syllabelRuleLen;

    m_in->writeRawData((const char*)&m_hdr, sizeof(fileHdr));
  }
}

QVector<QChar> datafile::readVowels()
{
  QVector<QChar>       vecVowels;

  for (int ndx = 0; ndx < m_hdr.e_cntVowels; ndx++)
  {
    uint16_t ch;
    m_in->readRawData((char*)&ch, sizeof(QChar));
    vecVowels.push_back(QChar(ch));
  }

  return vecVowels;
} 

void datafile::writeVowels(CDataEntry* m_pWidget) 
{
  QVector<QChar>* pVowels = m_pWidget->getVowels();

  if(m_open && (0 < pVowels->size()))
  {
    for (QChar c : *pVowels)
    {
      m_in->writeRawData((const char*)&c, sizeof(QChar));
    }
  }
}

QVector<QChar>  datafile::readConsonants()
{
  QVector<QChar>        vecConsonants;

  for (int ndx = 0; ndx < m_hdr.e_cntConsonants; ndx++)
  {
    uint16_t ch;
    m_in->readRawData((char*)&ch, sizeof(QChar));
    vecConsonants.push_back(QChar(ch));
  }

  return vecConsonants;
}

void datafile::writeConsonants(CDataEntry* m_pWidget) 
{
  QVector<QChar>* pConsonants = m_pWidget->getConsonants();

  if (m_open && (0 < pConsonants->size()))
  {
    for (QChar c : *pConsonants)
    {
      m_in->writeRawData((const char*)&c, sizeof(QChar));
    }
  }
}

QString datafile::readRules() 
{
  char* buf = new char[m_hdr.e_syllabelRuleLen + 1];
  memset((void*)buf, '\0', m_hdr.e_syllabelRuleLen + 1);

  m_in->readRawData(buf, m_hdr.e_syllabelRuleLen);

  QString rules(buf);
  delete[] buf;

  return rules;
}

void datafile::writeRules(CDataEntry* m_pWidget)
{
  QString rules = m_pWidget->getRule();

  if (m_open && (0 < rules.length()))
  {
    m_in->writeRawData((const char*)rules.toStdString().c_str(), rules.length());
  }
}


QMap<QChar, ptblEntryT> datafile::readGlyphs()
{
  xlationHdr   hdr;
  QMap<QChar, ptblEntryT> xlateMap;

  // read header
  m_in->readRawData((char*)&hdr, sizeof(xlationHdr));

  if (m_open && (hdr.xhCntEntries != 0))
  {
    for (int jdx = 0; jdx < hdr.xhCntEntries; jdx++)
    {
      uint16_t phonetic;

      m_in->readRawData((char*)&phonetic, sizeof(QChar));             // get phonetic spelling
      ptblEntryT   temp = new tblEntryT{ nullptr, nullptr };          // entry for the row                                                 // TODO : this needs to reflect cntXlations

      for (int ndx = 0; ndx < hdr.xhCntXlations; ndx++)
      {
        unsigned char len;

        m_in->readRawData((char*)&len, sizeof(unsigned char));       // get number characters in the current xlation

        if (len == 0) { temp->xlations[ndx] = nullptr;  continue; }           // no data for this xlation, skip
        else                                                        // we have data
        {
          //temp->xlations[ndx]->second = new char[len];
          char* buf = new char[len+1];
          memset((void*)buf, '\0', len + 1);
          m_in->readRawData((char*)buf, len);
          temp->xlations[ndx] = new glyphT{ 0, nullptr };
          temp->xlations[ndx]->first = len;
          temp->xlations[ndx]->second = buf;                        // move contents for buffer into glyphT.
        }
      }

      xlateMap.insert(QChar(phonetic), temp);
    }
  }

  return xlateMap;
}

void datafile::writeGlyphs(CDataEntry* m_pWidget)
{
  if (nullptr != m_pWidget)
  {
    QMap<QChar, ptblEntryT> xlationMap = m_pWidget->getXlationMap();

    if (xlationMap.size() > 0)
    {
      // write out the header...
      xlationHdr   hdr;
      hdr.xhCntXlations = cntXlations;
      hdr.xhCntEntries = xlationMap.size();

      m_in->writeRawData((const char*)&hdr, sizeof(xlationHdr));

      for (auto iter = xlationMap.cbegin(); iter != xlationMap.cend(); iter++)
      {
        QChar phGlyph = iter.key();
        ptblEntryT xlation = iter.value();

        m_in->writeRawData((const char*)&phGlyph, sizeof(QChar));

        for (int ndx = 0; ndx < cntXlations; ndx++)
        {
          QString  text = "";
          unsigned char bySize = 0;                                            // size of individual translation

          if (nullptr != xlation->xlations[ndx])
          {
            bySize = xlation->xlations[ndx]->first;                          // how long is the translation
            text = QString(xlation->xlations[ndx]->second);

            m_in->writeRawData((const char*)&bySize, 1);
            m_in->writeRawData((const char*)text.toStdString().c_str(), text.size());
          }
          else
          {
            m_in->writeRawData((const char*)&bySize, 1);                    // write the size of the data
          }
        }
      }
    }
  }
}




