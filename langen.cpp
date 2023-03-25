#include "langen.h"
#include "DataEntry.h"
#include "editGlyphDlg.h"

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QWidget>
#include <QToolBar>
#include <QFileDialog>

#include <qdebug>

#include <errno.h>

// TODO : add QPhonome class to allow from 2 / 3 character symbols -- can we do....
// TODO : make edit boxes editable while keeping updating IPA charts

LanGen::LanGen(QWidget *parent) : QMainWindow(parent), m_qstrFileName("")
{
    setupUI();
    setupActions();
    setupMenus();
}



LanGen::~LanGen()
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
void LanGen::setupUI()
{
    QWidget *centralwidget;
    //QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    this->resize(WIN_WIDTH, WIN_HEIGHT+MNU_HEIGHT);
    this->setFixedSize(WIN_WIDTH, WIN_HEIGHT+MNU_HEIGHT);
    this->setWindowTitle("Language Generator");


    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QStringLiteral("centralwidget"));
 
    m_pWidget = new CDataEntry(this);
    m_pWidget->setObjectName(QStringLiteral("dataEntry"));
    m_pWidget->setGeometry(QRect(0, MNU_HEIGHT,WIN_WIDTH,WIN_HEIGHT));

    this->setCentralWidget(centralwidget);
    
    menubar = new QMenuBar(this);
    menubar->setObjectName(QStringLiteral("menubar"));
    menubar->setGeometry(QRect(0, 0,WIN_WIDTH, 21));
    this->setMenuBar(menubar);
    
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QStringLiteral("statusbar"));
    this->setStatusBar(statusbar);
} // setupUi



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
void LanGen::setupActions()
{
    m_fileOpen = new QAction("&Open", this);
    m_fileOpen->setShortcuts(QKeySequence::Open);
    m_fileOpen->setStatusTip("opens existing configuration file");
    connect(m_fileOpen, &QAction::triggered, this, &LanGen::onFileOpen);

    m_fileNew = new QAction("&New", this);
    m_fileNew->setShortcuts(QKeySequence::New);
    m_fileNew->setStatusTip("creates a new configuration file");
    connect(m_fileNew, &QAction::triggered, this, &LanGen::onFileNew);

    m_fileSave = new QAction("&Save", this);
    m_fileSave->setShortcuts(QKeySequence::Save);
    m_fileSave->setStatusTip("saves the current configuration");
    connect(m_fileSave, &QAction::triggered, this, &LanGen::onFileSave);

    m_fileSaveAs = new QAction("Save As", this);
    m_fileSaveAs->setShortcuts(QKeySequence::New);
    m_fileSaveAs->setStatusTip("saves the current configuration with a new name");
    connect(m_fileSaveAs, &QAction::triggered, this, &LanGen::onFileSaveAs);

    m_fileSaveWords = new QAction("Save word list", this);
    //m_fileSaveWords->setShortcuts(QKeySequence::New);
    m_fileSaveWords->setStatusTip("saves the current generated word liat");
    connect(m_fileSaveWords, &QAction::triggered, this, &LanGen::onFileSaveWords);

    m_fileExit = new QAction("e&Xit", this);
    m_fileExit->setShortcuts(QKeySequence::Quit);
    m_fileExit->setStatusTip("exits the application");
    connect(m_fileExit, &QAction::triggered, this, &LanGen::onFileExit);

    m_editAlphabet = new QAction("Alphabet", this);
    m_editAlphabet->setStatusTip("assign glyphs to phonemes");
    connect(m_editAlphabet, &QAction::triggered, this, &LanGen::onAlphabetGlyphs);

    m_editGlyphs = new QAction("Glyphs", this);
    //m_editGlyphs->setShortcuts();
    m_editGlyphs->setStatusTip("assign glyphs to syllabols");
    connect(m_editGlyphs, &QAction::triggered, this, &LanGen::onSyllabelGlyphs);

    m_HelpAbout  = new QAction("About", this);
    //m_HelpAbout->setShortcuts(QKeySequence::About);
    m_HelpAbout->setStatusTip("shows progam information");
    connect(m_HelpAbout, &QAction::triggered, this, &LanGen::onHelpAbout);

    m_HelpHelp = new QAction("&Help", this);
    m_HelpHelp->setShortcuts(QKeySequence::HelpContents);
    m_HelpHelp->setStatusTip("creates a new configuration file");
    connect(m_HelpHelp, &QAction::triggered, this, &LanGen::onHelpHelp);
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
void LanGen::setupMenus()
{
    m_fileMenu = menuBar()->addMenu("&File");
    m_fileMenu->addAction(m_fileNew);
    m_fileMenu->addAction(m_fileOpen);
    m_fileMenu->addAction(m_fileSave);
    m_fileMenu->addAction(m_fileSaveAs);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_fileSaveWords);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_fileExit);

    m_editMenu = menuBar()->addMenu("&Edit");
    QMenu*  m_glyphMenu = m_editMenu->addMenu("glyphs");
    m_glyphMenu->addAction(m_editAlphabet);
    m_glyphMenu->addAction(m_editGlyphs);


    m_helpMenu = menuBar()->addMenu("&Help");
    m_helpMenu->addAction(m_HelpAbout);
    m_helpMenu->addAction(m_HelpHelp);
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
void LanGen::onFileNew()      
{
    m_pWidget->clear();
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
void LanGen::onFileOpen()     
{ 
    QString strFileName = QFileDialog::getOpenFileName(this, "Open language file", "./", "Language Files (*.pho);;All Files (*.*)");
    QFile inFile(strFileName);

    m_pWidget->clear();

    if (inFile.open(QIODevice::ReadOnly))
    {
        unsigned int cntVowels;
        unsigned int cntCons;

        QDataStream in(&inFile);

        in >> cntCons;
        //qDebug() << "found: " << cntCons << "consonents";
        for (unsigned int ndx = 0; ndx < cntCons; ndx++)
        {
            QChar  qch;
            in >> qch;
            emit onNewConsonant(qch);
        }

        // read in the vowels...
        in >> cntVowels;
        //qDebug() << "found: " << cntVowels << " vowels";

        for (unsigned int ndx = 0; ndx < cntVowels; ndx++)
        {
            QChar  qch;
            in >> qch;

            emit onNewVowel(qch);
        }

        // read in the rules...
        QString qstrRules;
        in >> qstrRules;
        m_pWidget->setRule(qstrRules);

        // read in the translation map
        /*
        00 00 00 0A 
        01 00 65 00 65              len = 1, phoneme = 65    xlation =
        01 00 69 00 69              len = 1, phoneme = 69    xlation =
        01 00 6B 00 6B              len = 1, phoneme = 6B    xlation =
        01 00 6F 00 6F              len = 1, phoneme = 6F    xlation =
        01 00 70 00 70              len = 1, phoneme = 70    xlation =
        01 00 74 00 74              len = 1, phoneme = 74    xlation =
        02 02 56 00 74 00 68        len = 2, phoneme = 56 02 xlation =
        03 02 6E 00 74 00 73 00 63  len = 3, phoneme = 6E 02 xlation =
        02 02 A7 00 74 00 73        len = 2, phoneme = A7 02 xlation =
        02 03 C7 00 63 00 68        len = 2, phoneme = C7 03 xlation =                                  
        */
        
        int cntXlations;
        in >> cntXlations;             // read in number of translations..
        QMap<QChar, QString>         mXlations;
        for (int ndx = 0; ndx < cntXlations; ndx++)
        {
            unsigned char   size;
            QChar           phoneme;
            QChar           qchGlyph;
            QString glyph = "";

            in >> size;         // get size of glyph
            in >> phoneme;
            for (int jdx = 0; jdx < size; jdx++)
            {
                in >> qchGlyph;
                glyph += qchGlyph;
            }

            mXlations.insert(phoneme, glyph);
        }
        m_pWidget->setXlationMap(&mXlations);

        m_qstrFileName = strFileName;

        // adjust the title of the window to reflect the file being used
        this->setWindowTitle(QString("Language Generator - %1").arg(strFileName));
    }
    else
    {
        QString   errMsg = inFile.errorString();
        qDebug() << "failed to open file" << errMsg;
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
void LanGen::onFileSave()     
{
    QVector<QChar>::iterator     viter;

    if(m_qstrFileName != "")      // we already have a file name, do it...
    {
        // TODO : we need to write a header out
        //      : part of header should be number of consonants and offset to consonants
        //      :                          number of vowels and offset to vowels
        //      : phoneme to glyph translation offset and number of records
        QFile  outFile(m_qstrFileName);
    
        if(outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QDataStream out(&outFile);
        
            // save off the consonants....
            QVector<QChar>*   pVec = m_pWidget->getConsonants();
            if(pVec->size() > 0)
            {
                out << pVec ->size();
                viter = pVec->begin();
                while(pVec->end() != viter)
                {
                    out << (*viter);
                    ++viter;
                }
            }
            else
            {
                qDebug() << "no consonants in languate";
            }

            // save off the vowels....
            pVec = m_pWidget->getVowels();
            if(pVec->size() > 0)
            {
                out << pVec->size();
                viter = pVec->begin();

                while(pVec->end() != viter)
                {
                    out << (*viter);
                    ++viter;
                }
            }
            else
            {
                qDebug() << "no vowels in langage";
            }

            // save off the generation rule....
            QString  qstrRules = m_pWidget->getRule();
            if (qstrRules != "")
            {
                out << qstrRules;
            }
            else
            {
                qDebug() << "no structrual rules given";
            }

            // save off phonemes to glyphs mapping...
            QMap<QChar, QString> xlateMap = m_pWidget->getXlationMap();
            int cntXlations = xlateMap.size();
            if (cntXlations > 0)
            {
                out << cntXlations;
                //write each xlation  len( unsigned char 2 + strlen), phoneme (QChar, 2 bytes), mapping (char[len]);
                QMap<QChar, QString>::iterator miter = xlateMap.begin();
                while (xlateMap.end() != miter)
                {
                    unsigned char  valLen = miter.value().length();
                    out << valLen;/* +2;*/
                    out << miter.key();
                    for(int ndx = 0; ndx < valLen; ndx++)
                        out << (miter.value()).at(ndx);
                    ++miter;
                }
            }
            else
            {
                qDebug() << "no coversion rules supplied";
            }
        }
        else
        {
            QString   errMsg = outFile.errorString();
            qDebug() << "failed to open file" << errMsg;
        }

        outFile.close();                // we be done, close the file....

    }
    else      // we do not have a name, go get a name and try again...
    {
        onFileSaveAs();
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
void LanGen::onFileSaveAs()   
{
    QString strFileName = QFileDialog::getSaveFileName(this, "Save Language File", "./", "Language Files (*.pho)");
    if (strFileName != "")
    {
        m_qstrFileName = strFileName;
        onFileSave();
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
void LanGen::onFileSaveWords()
{
    QString strFileName = QFileDialog::getSaveFileName(this, "Save word list", "./", "Dictionary files  (*.dict);;All files (*.*)");

    if (strFileName != "")
    {
        QFile  outFile(strFileName);

        if (outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QTextStream out(&outFile);
            out.setCodec("UTF-8");           // so we can print unicode characters
            

            QStringList words = m_pWidget->getText().split('\n');
            words = words.toSet().toList();                        // remove duplicate entries...
            words.sort();                                          // so in alphabetical order

            QStringList::iterator  qsliter;
            qsliter = words.begin();
            while (words.end() != qsliter)
            {
                QString word = (*qsliter);

                out << word << "\n";
                ++qsliter;
            }

            outFile.close();                // we be done, close the file....
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
void LanGen::onAlphabetGlyphs()
{
    CEditGlyphDlg dlg(m_pWidget->getVowels(), m_pWidget->getConsonants());

    if (m_pWidget->getXlationMap().size() > 0)                        // we have an xlation map
        dlg.setXlationMap(&(m_pWidget->getXlationMap()));

    if (QDialog::Accepted == dlg.exec())
    {
        QMap<QChar, QString> xlateMap = dlg.getXlationMapping();      // get translation mapping
        m_pWidget->setXlationMap(&xlateMap);                          // pass translation mapping to dataentry class 
    }
    else
    {

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
void LanGen::onSyllabelGlyphs()
{
    qDebug() << "in onSyllabelGlyphs";

    // TODO : generate list of syllabels.

    CEditGlyphDlg dlg(m_pWidget->getVowels(), m_pWidget->getConsonants());
    if(QDialog::Accepted == dlg.exec())
    { 
        // TODO : build translation map                   
    }
    else
    {

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
void LanGen::onFileExit()     
{
    if (m_pWidget->isDirty())
    {
        // TODO : ask to save the word list.
    }
    QApplication::quit();
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
void LanGen::onHelpAbout()    
{
    qDebug() << "in onHelpAbout";
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
void LanGen::onHelpHelp()     
{
    qDebug() << "in onHelpHelp";
}

