#ifndef UI_IPAVOWELDLG_H
#define UI_IPAVOWELDLG_H


#include <QDialog>
#include <QBitArray>

#define ROWS    7
#define COLS   13 /*15*/
#define BUT_SZ 30
#define MARGIN_SZ 6
#define DLG_WIDTH  COLS*BUT_SZ + 2* MARGIN_SZ
#define DLG_HEIGHT ROWS*BUT_SZ + 3*MARGIN_SZ + BUT_SZ

class CIPAVowelDlg : public QDialog
{
    Q_OBJECT

public:
    CIPAVowelDlg( QVector<QChar>* pList, QWidget* parent = nullptr);
    ~CIPAVowelDlg();

    void setupUI();

signals:
        void onSelected(QChar);
        void onDelete(QChar);

private slots:
    void onClicked();

private:
    QPushButton*     m_buttons[ROWS][COLS];
    QBitArray        m_btnState;              // records if a sound has been choosen or not.
    QWidget*         m_pParent;               // who created us.

    void changeBackground(int);               // helper function to manage background color of button.
};


#endif // UI_IPAVOWELDLG_H