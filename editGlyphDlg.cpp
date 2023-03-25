#include "editGlyphDlg.h"


#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>


CEditGlyphDlg::CEditGlyphDlg( QVector<QChar>* pvowels,  QVector<QChar>* pconsonants, QWidget* parent) : QDialog(parent)
{
    setupUI(3);

    if(pvowels->size() <= 0)
    {
        qDebug() << "there are no vowels selected!";
        QMessageBox::warning(this, "Missing sound inventory", "you have not defined any vowels for your language yet", QMessageBox::Ok);
        QDialog::reject();
    }

    if(pconsonants->size() <= 0)
    {
        qDebug() << "there aer no consonants selected";
        QMessageBox::warning(this, "Missing sound inventory", "you have not defined any consonants for your language yet", QMessageBox::Ok);
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
        QChar    qchPhoneme = m_phonemesList->item(ndx, 0)->text().front();  // get the phoneme, phoneme is a single charater
        QString  qstrGlyph = m_phonemesList->item(ndx, 1)->text();           // get the glyph

        m_xlateMap.insert(qchPhoneme, qstrGlyph);                            // insert into map
    }
}


void CEditGlyphDlg::setXlationMap(QMap<QChar, QString>* pmap)
{
    // TODO : get phoneme from row
    // TODO : search of phoneme in pmap
    // TODO : if founded, insert in row.

    int cntRows = m_phonemesList->rowCount();

    for (int ndx = 0; ndx < cntRows; ndx++)
    {
        QChar  qchPhoneme = m_phonemesList->item(ndx, 0)->text().front();
        
        QMap<QChar, QString>::iterator imap =   pmap->find(qchPhoneme);
        if (imap != pmap->end())              // found the item
        {
            m_phonemesList->setItem(ndx, 1, new QTableWidgetItem(imap.value()));
        }
        else
        {
            QMessageBox::warning(this, "Warning", "No xlation exists for " + QString(qchPhoneme));
        }

    }
}

 

void CEditGlyphDlg::accept()
{
    QDialog::accept();
    buildXlationMap();
}



void CEditGlyphDlg::reject()
{

    QDialog::reject();
}