#ifndef DataEntry_H
#define DataEntry_H

#include "editGlyphDlg.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QGridLayout>

#define WIN_WIDTH  645
#define WIN_HEIGHT 460
#define MNU_HEIGHT 20



class CDataEntry : public QWidget
{
    Q_OBJECT

public:
    CDataEntry(QWidget *parent = 0);
    ~CDataEntry();

    void setupUI();
    void clear();

    QVector<QChar>*         getVowels() {return &m_vecVowels;}
    void                    setVowels(QVector<QChar>*);
    QVector<QChar>*         getConsonants() {return &m_vecConsonants;}
    void                    setConsonants(QVector<QChar>*);
    QVector<QString>*       getSyllabols() { return &m_vecSyllabols; }
    QString                 getRule() { return m_structureList->text(); }
    void                    setRule(QString qstrRule) { m_structureList->setText(qstrRule); }
    QMap<QChar, ptblEntryT> getXlationMap() { return m_xlateMap; }
    void                    setXlationMap(QMap<QChar, ptblEntryT>*);
    bool                    isDirty() { return m_wordList->isWindowModified(); }
    QString                 getText() { return m_wordList->toPlainText(); }

private slots:
    void onShowConsts();
    void onShowVowels();
    void onNewStruct();
    void onNewRule();
    void onGenerate();

    void onAddVowel(QChar);
    void onDelVowel(QChar);
    void onAddConsonant(QChar);
    void onDelConsonant(QChar);

private:
    QWidget*       m_pParent;
    QLineEdit*     m_consonantList;
    QLineEdit*     m_vowelList;
    QLineEdit*     m_structureList;
    QLineEdit*     m_syllablesPerWord;
    QLineEdit*     m_sonorityList;
    QLineEdit*     m_cntGenerate;
    QTextBrowser*  m_wordList;
    
    QPushButton*   m_btnVowlSelect;
    QPushButton*   m_btnNewRule;
    QPushButton*   m_btnGenerate;
    QPushButton*   m_btnConsSelect;

    QVector<QChar>          m_vecConsonants;
    QVector<QChar>          m_vecVowels;
    QVector<QString>        m_vecSyllabols;
    QMap<QChar, ptblEntryT> m_xlateMap;
    uint8_t                 m_spw;               // syllables per word, default is three
};

#endif
