#include "langen.h"
#include "DataEntry.h"
#include "editGlyphDlg.h"
#include "datafile.h"
#include "constants.h"

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
  m_pWidget->clear();
  QString strFileName = QFileDialog::getOpenFileName(this, "Open language file", "./", "Language Files (*.pho);;All Files (*.*)");

  if (datafile::isValid(strFileName))                       // we have a valid language definition file to use
  {
    m_qstrFileName = strFileName;

    datafile  infile(m_qstrFileName);
    if (infile.open(datafile::mode::READ))
    {
      fileHdr      hdr;
      infile.readHeader(&hdr);

      QVector<QChar> vecVowels = infile.readVowels();
      m_pWidget->setVowels(&vecVowels);

      QVector<QChar> vecConsonants = infile.readConsonants();
      m_pWidget->setConsonants(&vecConsonants);

      QString rules = infile.readRules();
      m_pWidget->setRule(rules);

      if (hdr.e_id[4] == 2)                  // if we have a new version of file, supporting glyph header
      {
        QMap<QChar, ptblEntryT> xlationMap = infile.readGlyphs();
        m_pWidget->setXlationMap(&xlationMap);
      }



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
void LanGen::onFileSave()     
{
    if (m_qstrFileName != "")      // we already have a file name, do it...
    {
      datafile  outfile(m_qstrFileName);
      if (outfile.open(datafile::mode::WRITE))
      {
        outfile.writeHeader(m_pWidget);
        outfile.writeVowels(m_pWidget);
        outfile.writeConsonants(m_pWidget);
        outfile.writeRules(m_pWidget);
        outfile.writeGlyphs(m_pWidget);

        outfile.close();
      }
    }
    else                          // we do not have a name, go get a name and try again...
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
            //out.setCodec("UTF-8");                                  // so we can print unicode characters
            out.setEncoding(QStringConverter::Utf8);
            

            QStringList words = m_pWidget->getText().split('\n');
            words.removeDuplicates();                              // remove duplicate entries...
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
    QMap<QChar, ptblEntryT>  xlationMap = m_pWidget->getXlationMap();

    CEditGlyphDlg dlg(m_pWidget->getVowels(), m_pWidget->getConsonants(), &xlationMap);

    //if (m_pWidget->getXlationMap().size() > 0)                        // we have an xlation map
    //    dlg.setXlationMap(&(m_pWidget->getXlationMap()));

    if (QDialog::Accepted == dlg.exec())
    {
        QMap<QChar, ptblEntryT> xlateMap = dlg.getXlationMapping();    // get translation mapping
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

    QMap<QChar, ptblEntryT>  xlationMap = m_pWidget->getXlationMap();

    // TODO : generate list of syllabels.

    CEditGlyphDlg dlg(m_pWidget->getVowels(), m_pWidget->getConsonants(), &xlationMap);
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

