#include "DataEntry.h"
#include "IPAVowelDlg.h"
#include "IPAConsonantsDlg.h"

#include <QMainWindow>
#include <QToolBar>
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>

QString classes="C,V,";

CDataEntry::CDataEntry(QWidget *parent) : QWidget(parent), m_pParent(parent)
{
    srand(time(NULL));
    setupUI();
    
}

CDataEntry::~CDataEntry()
{

}



/**********************************************************************************************************************
 * function:
 *
 * abstract:
 *
 * inputs  :
 *
 * returns :
 *
 * written :
 *********************************************************************************************************************/
void CDataEntry::setupUI()
{
    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(14);
    this->setFont(font);
    this->setWindowTitle("Language Generator");

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    this->resize(WIN_WIDTH, WIN_HEIGHT);
   

    QWidget* widget = new QWidget(this);
    widget->setObjectName(QStringLiteral("widget"));
    widget->setGeometry(QRect(0, 0, WIN_WIDTH, WIN_HEIGHT));
    
    QGridLayout* gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(11, 11, 11, 11);

    // ui elements dealing with consonants....
    QLabel * label1 = new QLabel(this);
    label1->setObjectName(QStringLiteral("label1"));
    label1->setGeometry(QRect(20, 80, 161, 21));
    label1->setText("Consonants");   
    label1->setFont(font);

    m_consonantList = new QLineEdit(this);
    m_consonantList->setObjectName(QStringLiteral("m_consonantList"));
    m_consonantList->setReadOnly(true);
    m_consonantList->setGeometry(QRect(190, 79, 311, 25));
    m_consonantList->setFont(font);
        
    m_btnConsSelect = new QPushButton(this);
    m_btnConsSelect->setObjectName(QStringLiteral("m_btnConsSelect"));
    m_btnConsSelect->setGeometry(QRect(510, 80, 75, 23));
    m_btnConsSelect->setFont(font);
    m_btnConsSelect->setText("IPA");

    // ui elements dealing with vowels...
    QLabel *label2 = new QLabel(this);
    label2->setObjectName(QStringLiteral("label2"));
    label2->setGeometry(QRect(20, 120, 161, 21));
    label2->setText("Vowels");
    label2->setFont(font);
   
    m_vowelList = new QLineEdit(this);
    m_vowelList->setObjectName(QStringLiteral("m_vowelList"));
    m_vowelList->setReadOnly(true);
    m_vowelList->setGeometry(QRect(190, 120, 301, 25));
    m_vowelList->setFont(font);

    m_btnVowlSelect = new QPushButton(this);
    m_btnVowlSelect->setObjectName(QStringLiteral("m_btnVowlSelect"));
    m_btnVowlSelect->setGeometry(QRect(510, 120, 75, 23));
    m_btnVowlSelect->setText("IPA");
    m_btnVowlSelect->setFont(font);

    //ui elements dealing with syllable structure...
    QLabel *label3 = new QLabel(this);
    label3->setObjectName(QStringLiteral("label3"));
    label3->setGeometry(QRect(20, 160, 161, 21));
    label3->setText(QApplication::translate("LanGenClass", "Structure", 0));
    label3->setFont(font);
               
    m_structureList = new QLineEdit(this);
    m_structureList->setObjectName(QStringLiteral("m_structureList"));
    m_structureList->setGeometry(QRect(190, 160, 311, 25));
    m_structureList->setFont(font);

    m_btnNewStruct = new QPushButton(this);
    m_btnNewStruct->setObjectName(QStringLiteral("m_btnNewStruct"));
    m_btnNewStruct->setGeometry(QRect(510, 160, 101, 23));
    m_btnNewStruct->setText(QApplication::translate("LanGenClass", "new form", 0));
    m_btnNewStruct->setFont(font);

    //ui elements dealing with sonority rules...
    QLabel *label4 = new QLabel(this);
    label4->setObjectName(QStringLiteral("label4"));
    label4->setGeometry(QRect(20, 200, 161, 21));
    label4->setText("Sonority Rules:");
    label4->setFont(font);

    m_sonorityList= new QLineEdit(this);
    m_sonorityList->setObjectName(QStringLiteral("m_sonorityList"));
    m_sonorityList->setGeometry(QRect(190, 200, 311, 25));
    m_sonorityList->setFont(font);

    m_btnNewRule = new QPushButton(this);
    m_btnNewRule->setObjectName(QStringLiteral("m_btnNewRule"));
    m_btnNewRule->setGeometry(QRect(510, 200, 101, 23));
    m_btnNewRule->setText(QApplication::translate("LanGenClass", "new rule", 0));
    m_btnNewRule->setFont(font);
        
    // ui elements for word display control...
    m_wordList = new QTextBrowser(this);
    m_wordList->setObjectName(QStringLiteral("m_wordList"));
    m_wordList->setGeometry(QRect(20, 280, 611, 321));
    m_wordList->setFont(font);

    // ui elements for generation control
    QLabel *label5 = new QLabel(this);
    label5->setObjectName(QStringLiteral("label5"));
    label5->setGeometry(QRect(20, 610, 200, 21));
    label5->setText("Number to Generate:");
    label5->setFont(font);

    m_cntGenerate = new QLineEdit(this);
    m_cntGenerate->setObjectName(QStringLiteral("m_cntGenerate"));
    m_cntGenerate->setGeometry(QRect(230, 610, 113, 25));
    m_cntGenerate->setFont(font);
    m_cntGenerate->setValidator(new QIntValidator(0, 20000, this));

    m_btnGenerate = new QPushButton(this);
    m_btnGenerate->setObjectName(QStringLiteral("m_btnGenerate"));
    m_btnGenerate->setGeometry(QRect(530, 610, 101, 23));
    m_btnGenerate->setText("Generate");
    m_btnGenerate->setFont(font);

    // add controls to the grid...
    //addWidget(widget*, row, column, row_span, column_span)
    gridLayout->addWidget(label1, 0, 0, 1, 1);
    gridLayout->addWidget(m_consonantList, 0, 1, 1, 5);
    gridLayout->addWidget(m_btnConsSelect, 0, 6, 1, 1);
   
    gridLayout->addWidget(label2, 1, 0, 1, 1);   
    gridLayout->addWidget(m_vowelList, 1, 1, 1, 5);
    gridLayout->addWidget(m_btnVowlSelect, 1, 6, 1, 1);

    gridLayout->addWidget(label3, 2, 0, 1, 1);
    gridLayout->addWidget(m_structureList, 2, 1, 1, 5);
    gridLayout->addWidget(m_btnNewStruct, 2, 6, 1, 1);
      
    gridLayout->addWidget(label4, 3, 0, 1, 1);
    gridLayout->addWidget(m_sonorityList, 3, 1, 1, 5);
    gridLayout->addWidget(m_btnNewRule, 3, 6, 1, 1);
   
    gridLayout->addWidget(m_wordList, 5, 0, 1, 7);  
    
    gridLayout->addWidget(label5, 6, 0, 1, 2);
    gridLayout->addWidget(m_cntGenerate, 6, 2, 1, 2);
    gridLayout->addWidget(m_btnGenerate, 6, 6, 1, 1);

    // setup connections....
    connect(m_btnConsSelect, SIGNAL(clicked()), this, SLOT(onShowConsts()));
    connect(m_btnVowlSelect, SIGNAL(clicked()), this, SLOT(onShowVowels()));
    connect(m_btnNewStruct,SIGNAL(clicked()),this, SLOT(onNewStruct()));
    connect(m_btnNewRule,SIGNAL(clicked()),this, SLOT(onNewRule()));
    connect(m_btnGenerate,SIGNAL(clicked()),this, SLOT(onGenerate()));

    connect(m_pParent,SIGNAL(onNewVowel(QChar)), this, SLOT(onAddVowel(QChar)));
    connect(m_pParent,SIGNAL(onNewConsonant(QChar)), this, SLOT(onAddConsonant(QChar)));
}



/**********************************************************************************************************************
 * function:
 *
 * abstract:
 *
 * inputs  :
 *
 * returns :
 *
 * written :
 *********************************************************************************************************************/
void CDataEntry::onShowConsts() 
{
    CIPAConsDlg    dlg(&m_vecConsonants, this);
    connect(&dlg, SIGNAL(onSelected(QChar)), this, SLOT(onAddConsonant(QChar)));
    connect(&dlg, SIGNAL(onDelete(QChar)), this,   SLOT(onDelConsonant(QChar)));

    dlg.exec();
}



/**********************************************************************************************************************
 * function:
 *
 * abstract:
 *
 * inputs  :
 *
 * returns :
 *
 * written :
 *********************************************************************************************************************/
void CDataEntry::onShowVowels() 
{
    CIPAVowelDlg    dlg(&m_vecVowels, this);
    connect(&dlg, SIGNAL(onSelected(QChar)), this, SLOT(onAddVowel(QChar)));
    connect(&dlg, SIGNAL(onDelete(QChar)), this, SLOT(onDelVowel(QChar)));

    dlg.exec();
}



void CDataEntry::onNewStruct() {qDebug() << "inOnNewStruct";}
void CDataEntry::onNewRule() {qDebug() << "inOnNewRule";}



/**********************************************************************************************************************
 * function:
 *
 * abstract:  treat syllabel rule as a regex, i.e. (CCC)V(CCC) == (C){0-3}V(C){0-3} and convert to a state machine
 *    
 *                                       /- C -
 *                                /-  C-<      \
 *                          /- C-<        \     \
 *                  start -<      \         \    \
 *                          \-------------------- V ------------------------ end
 *                                                 \       /       /      /
 *                                                  \- C -<       /      /
 *                                                         \-C -<       /
 *                                                                \- C -
 *  use the following syntax:
 *    ( )   : represents an optional componenet
 *    {#,#} : represents repetition
 *    |     : represents alteration
 *    [ ]   : represents grouping
 *
 *    for example (C){1,3}V(C){1,3} represents 1-3 optional consonants, then a vowel, then 1-3 optional consonants
 *                (C)V | V(C) | V   represents optional consonant, then vowel OR vowel optional consonant OR vowel
 *
 * inputs  :
 *
 * returns :
 *
 * written :
 *********************************************************************************************************************/
void CDataEntry::onGenerate() 
{
    int cntVol = m_vecVowels.size();
    int cntCon = m_vecConsonants.size();
    if (m_cntGenerate->text().isEmpty())
    {
        QMessageBox::critical(nullptr, "error", "you must provide a number to generate");
        return;
    }

    int cntGen = m_cntGenerate->text().toInt();;    // number of words to generate ....

    if(cntVol == 0 && cntCon == 0)
    {
        QMessageBox::critical(nullptr,"error", "you have not picked any sounds");
    }
    else                                                 // we have sounds defined for the language....
    {
        QStringList rules;

        qDebug() << "generating " << cntGen << " words";

        QString qstrRules = getRule();                   // get the rules from the dialog, eg (C)V | V(C); (C)V(C)
        //QString qstrRules = QString("(C)V | V(C); (C)V(C)");
        int nloc = qstrRules.indexOf(';');
        if (-1 != nloc)                                  // need to tokenize string...
        {
            rules = qstrRules.split(';');
        }
        else                                             // string contains single rule...
        {
            rules << qstrRules;
        }

        int cntRules = rules.size();
        CGenerator    clsGen(cntRules);                                 // initialize generator with number of rules.

        for (int ndx = 0; ndx < cntRules; ndx++)
        {
            clsGen.setString(rules.at(ndx));                       // set a rule string in generator
            clsGen.prepare(ndx);               // prepare the rule, prepend if part of same string
        }

        for (int ndx = 0; ndx < cntGen; ndx++)
        {
            QString     qstrPattern = "";               // gives the pattern to apply for the word.
            QString     qstrPhonetic = "";              // gives the phonetic spelling for the word.
            QString     qstrWord = "";                  // gives the spelling for the word in the current glyph system.

            int cntSyl = rand() % 3 + 1;                // pick a random number of sylabells 1 - 3

            // generate sylabells using spaces ...
            for(int jdx = 0; jdx < cntSyl; jdx++)
            { 
                qstrPattern = qstrPattern + clsGen.generate();
                qstrPattern = qstrPattern + " ";
            }

            // replace C,V with elements from the set(s)....
            // TODO : generate a list of all possible sylabells

            int len = qstrPattern.length();
            for (int ndx = 0; ndx < len; ndx++)
            {
                QChar qchPhoneme;
                QChar qch = qstrPattern.at(ndx);
                if (qch == ' ')                    // convert spaces to "/" to denote sylabells...
                    qstrPhonetic.append('/');
                else
                {
                    if (qch == 'C')               // translate a consonant...
                    {
                        qchPhoneme = m_vecConsonants.at(rand() % cntCon);
                    }
                    else if(qch == 'V')               // translate a vowel...
                    {
                        qchPhoneme = m_vecVowels.at(rand() % cntVol);
                    }
                    else
                    {
                        // TODO : handle errors
                    }

                    qstrPhonetic.append(qchPhoneme);      // add phonetic character

                    QMap<QChar, QString>::iterator miter  =  m_xlateMap.find(qchPhoneme);
                    if(miter != m_xlateMap.end())
                      qstrWord = qstrWord + miter.value();

                }
            }

            m_wordList->append(qstrWord + " (" + qstrPhonetic + ")");
        }
    }
}



/**********************************************************************************************************************
 * function:
 *
 * abstract:
 *
 * inputs  :
 *
 * returns :
 *
 * written :
 *********************************************************************************************************************/
void CDataEntry::onAddVowel(QChar ch)
{
    m_vecVowels.push_back(ch);                  // append the new vowel to the list of vowels

    QString   strVowels = m_vowelList->text();  // append the new vowel to teh display...
    strVowels = strVowels + ch + ",";
    m_vowelList->setText(strVowels);
}


 
/**********************************************************************************************************************
 * function:
 *
 * abstract: vowel goes in with a trailing comma, we need to delete the trailing comma as well
 *
 * inputs  :
 *
 * returns :
 *
 * written :
 *********************************************************************************************************************/
void CDataEntry::onDelVowel(QChar ch)
{
    // remove the vowel from the internal list...
    QVector<QChar>::iterator   viter = m_vecVowels.begin();

    while(m_vecVowels.end() != viter)
    {
        if( (*viter) == ch)
        {
            break;
        }
        ++viter;
    }

    if(m_vecVowels.end() != viter)            // we have a match
    {
        m_vecVowels.erase(viter);
    }
    else                    // this should not happen..we only get he by selected an already slected item
    {
        qDebug() << "could not find vowel in the vowel vector!!";
    }

    // remove teh vowel from the display
    QString  str = QString(ch) + ",";
    QString  strVowels = m_vowelList->text();
    strVowels = strVowels.remove(str);
    m_vowelList->setText(strVowels);
}



/**********************************************************************************************************************
 * function:
 *
 * abstract: 
 *
 * inputs  :
 *
 * returns :
 *
 * written :
 *********************************************************************************************************************/
void CDataEntry::onAddConsonant(QChar ch) 
{
    m_vecConsonants.push_back(ch);                      // append the new vowel to the list of vowels

    QString   strConsonants = m_consonantList->text();  // append the new vowel to teh display...
    strConsonants = strConsonants + ch + ",";
    m_consonantList->setText(strConsonants);
}



/**********************************************************************************************************************
 * function:
 *
 * abstract: 
 *
 * inputs  :
 *
 * returns :
 *
 * written :
 *********************************************************************************************************************/
void CDataEntry::onDelConsonant(QChar ch)
{
    // remove the vowel from the internal list...
    QVector<QChar>::iterator   viter = m_vecConsonants.begin();

    while(m_vecConsonants.end() != viter)
    {
        if( (*viter) == ch)
        {
            break;
        }
        ++viter;
    }

    if(m_vecConsonants.end() != viter)            // we have a match
    {
        m_vecConsonants.erase(viter);
    }
    else                    // this should not happen..we only get he by selected an already slected item
    {
        qDebug() << "could not find vowel in the vowel vector!!";
    }

    // remove teh vowel from the display
    QString  str = QString(ch) + ",";
    QString  strConsonants = m_consonantList->text();
    strConsonants = strConsonants.remove(str);
    m_consonantList->setText(strConsonants);
}



/**********************************************************************************************************************
 * function:
 *
 * abstract:
 *
 * inputs  :
 *
 * returns :
 *
 * written :
 *********************************************************************************************************************/
void CDataEntry::clear()
{
    // clear the edit controls....
    m_consonantList->clear();
    m_vowelList->clear();
    m_structureList->clear();
    m_sonorityList->clear();
    m_cntGenerate->clear();
    m_wordList->clear();

    // clear the lists...
    m_vecConsonants.erase(m_vecConsonants.begin(), m_vecConsonants.end());
    m_vecVowels.erase(m_vecVowels.begin(), m_vecVowels.end());
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function for input of data from a file

void CDataEntry::setVowels(QVector<QChar>*)
{}


void CDataEntry::setConsonants(QVector<QChar>*)
{}


void CDataEntry::setXlationMap(QMap<QChar, QString>* pmap)
{
    if (m_xlateMap.size() > 0)
        m_xlateMap.clear();

    QMap<QChar, QString>::iterator miter = pmap->begin();

    while (pmap->end() != miter)
    {
        m_xlateMap.insert(miter.key(), miter.value());
        ++miter;
    }
}

