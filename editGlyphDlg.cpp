#include "editGlyphDlg.h"
#include "logger.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>


CEditGlyphDlg::CEditGlyphDlg( QVector<QChar>* pvowels,  QVector<QChar>* pconsonants, QMap<QChar, ptblEntryT>* pxlate, QWidget* parent) : QDialog(parent)
{
    setupUI(cntXlations+1);               // one more column than number of translations.

    if(pvowels->size() <= 0)
    {
        CLogger::getInstance()->outMsg(cmdLine, CLogger::level::WARNING,"you have not defined any vowels for your language yet");
        QDialog::reject();
    }

    if(pconsonants->size() <= 0)
    {
        CLogger::getInstance()->outMsg(cmdLine, CLogger::level::WARNING, "you have not defined any consonants for your language yet");
        QDialog::reject();
    }
    
    int   row = 0;
    m_phonemesList->setRowCount(pvowels->size() + pconsonants->size());

    QVector<QChar>::iterator   viter = pvowels->begin();
    while(pvowels->end() != viter)
    {
        m_phonemesList->setItem(row++, 0, new QTableWidgetItem(QString(*viter)));

        ++viter;
    }

    QVector<QChar>::iterator  citer = pconsonants->begin();
    while (pconsonants->end() != citer)
    {
        m_phonemesList->setItem(row++, 0, new QTableWidgetItem(QString(*citer)));
        ++citer;
    }

    if (pxlate->size() > 0)
    {
      setXlationMap(pxlate);
    }
}


CEditGlyphDlg::CEditGlyphDlg(QVector<QString>* psyllabols, QWidget* parent) : QDialog(parent)
{
    setupUI(3);

    if (psyllabols->size() == 0)
    {
        qDebug() << "no syllabels given";
        QMessageBox::warning(this, "Missing sound inventory", "you have not defined any sounds for your language yet", QMessageBox::Ok);
        QDialog::reject();
    }

    if ((psyllabols->size() != 0))
    {
        int   row = 0;
        m_phonemesList->setRowCount(psyllabols->size());

        QVector<QString>::iterator   viter = psyllabols->begin();
        while (psyllabols->end() != viter)
        {
            qDebug() << "got vowel: " << (*viter);
            m_phonemesList->setItem(row++, 0, new QTableWidgetItem(QString(*viter)));

            ++viter;
        }
    }
}


CEditGlyphDlg::~CEditGlyphDlg() 
{ 

}



void CEditGlyphDlg::setupUI(int cols)
{
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *spacerItem;

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    this->resize(443, 481);
    this->setWindowTitle("Edit Sounds to Glyphs");
       
    // setup font for the dialog....
    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(14);
    this->setFont(font);
 
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    
    // build the main list view....
    m_phonemesList = new QTableWidget(this);
    m_phonemesList->setObjectName(QStringLiteral("m_phonemesList"));
    m_phonemesList->setColumnCount(cols);
    m_phonemesList->setFont(font);
    QStringList  qstrHeaders;
    qstrHeaders << "sound" << "glyph 1" <<"glyph 2";

    m_phonemesList->setHorizontalHeaderLabels(qstrHeaders);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

    // the cancel button...
    m_btnCancel = new QPushButton(this);
    m_btnCancel->setObjectName(QStringLiteral("m_btnCancel"));
    m_btnCancel->setText("Cancel");
    
    // the OK button....
    m_btnOK = new QPushButton(this);
    m_btnOK->setObjectName(QStringLiteral("m_btnOK"));   
    m_btnOK->setText("OK");
    
    // layout the button box...
    horizontalLayout->addItem(spacerItem);
    horizontalLayout->addWidget(m_btnCancel);
    horizontalLayout->addWidget(m_btnOK);

    // layout the vertical widgets...
    verticalLayout->addWidget(m_phonemesList);
    verticalLayout->addLayout(horizontalLayout);

    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    QObject::connect(m_btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(m_btnCancel, SIGNAL(clicked()), this, SLOT(reject()));   
} // setupUi


// build map from phenome to glyph...
void CEditGlyphDlg::buildXlationMap()
{
    int cntRows = m_phonemesList->rowCount();

    for (int ndx = 0; ndx < cntRows; ndx++)
    {
      ptblEntryT   temp = new tblEntryT{ nullptr, nullptr };                   // entry for the row 

      QChar    qchPhoneme = m_phonemesList->item(ndx, 0)->text().front();    // get the phoneme, phoneme is a single charater
      QTableWidgetItem* pItem;
      
      for (int xlation = 0; xlation < cntXlations; xlation++)
      {
        if (nullptr != (pItem = m_phonemesList->item(ndx, xlation+1)))
        {
          temp->xlations[xlation] = new glyphT{ 0, nullptr };            
          temp->xlations[xlation]->first = pItem->text().length();                  // set length of  translation
          temp->xlations[xlation]->second = new char[pItem->text().length() + 1];   // allocate space for  translation
          memset((void*)temp->xlations[xlation]->second, '\0', pItem->text().length() + 1);
          for (int ndx = 0; ndx < pItem->text().length(); ndx++)
            temp->xlations[xlation]->second[ndx] = (pItem->text().toStdString().c_str())[ndx];  // copy  translation
        }
      }

      m_xlateMap.insert(qchPhoneme, temp);                                  // insert into map
    }
}


void CEditGlyphDlg::setXlationMap(QMap<QChar, ptblEntryT>* pmap)
{
      int cntRows = m_phonemesList->rowCount();

    for (int ndx = 0; ndx < cntRows; ndx++)
    {
        QChar  qchPhoneme = m_phonemesList->item(ndx, 0)->text().front();        // get phoneme from row
        
        QMap<QChar, ptblEntryT>::iterator imap =   pmap->find(qchPhoneme);       // search of phoneme in pmap
        if (imap != pmap->end())              // found the item
        {
          for (int jdx = 0; jdx < cntXlations; jdx++)                            // if founded, insert in row.
          {
            if (nullptr != imap.value()->xlations[jdx])
            {
              QString  xlation;                                                  // translation of phonetic -> normal language.
              //m_phonemesList->setItem(ndx, jdx + 1, new QTableWidgetItem(imap.value()->xlations[jdx]->second));
              for (int kdx = 0; kdx < imap.value()->xlations[jdx]->first; kdx++)
              {
                xlation.append(imap.value()->xlations[jdx]->second[kdx]);        // append character by character
              }
              m_phonemesList->setItem(ndx, jdx + 1, new QTableWidgetItem(xlation));
            }
          }
        }
        else
        {
            QMessageBox::warning(this, "Warning", "No xlation exists for " + QString(qchPhoneme));
        }

    }
}

 

void CEditGlyphDlg::accept()
{    
  buildXlationMap();
  QDialog::accept();

}



void CEditGlyphDlg::reject()
{
    QDialog::reject();
}