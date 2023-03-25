#ifndef LANGEN_H
#define LANGEN_H

#include "DataEntry.h"

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QMainWindow>




class LanGen : public QMainWindow
{
    Q_OBJECT

public:
    LanGen(QWidget *parent = 0);
    ~LanGen();

    void setupUI();
    void setupActions();
    void setupMenus();

signals:
    void onNewVowel(QChar);
    void onNewConsonant(QChar);

private slots:
    void onFileNew();
    void onFileSave();
    void onFileSaveAs();
    void onFileOpen();
    void onFileSaveWords();
    void onFileExit();
    void onAlphabetGlyphs();
    void onSyllabelGlyphs();
    void onHelpAbout();
    void onHelpHelp();

private:
    QString          m_qstrFileName;

    QMenu*         m_fileMenu;
    QMenu*         m_helpMenu;
    QMenu*         m_editMenu;

    CDataEntry*    m_pWidget;

    QAction*       m_fileNew;
    QAction*       m_fileSave;
    QAction*       m_fileSaveAs;
    QAction*       m_fileOpen;
    QAction*       m_fileSaveWords;
    QAction*       m_fileExit;
    QAction*       m_editAlphabet;
    QAction*       m_editGlyphs;
    QAction*       m_HelpAbout;
    QAction*       m_HelpHelp;
};

#endif // LANGEN_H
