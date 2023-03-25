#ifndef _IPAConsonantsDlg_h_
#define _IPAConsonantsDlg_h_


#include <QDialog>
#include <QBitArray>

#define ROWS_1    9
#define COLS_1   22
#define BUT_SZ 30
#define MARGIN_SZ 6
#define CONS_DLG_WIDTH  COLS_1*BUT_SZ + 2* MARGIN_SZ
#define CONS_DLG_HEIGHT  ROWS_1*BUT_SZ + 3*MARGIN_SZ + BUT_SZ

class CIPAConsDlg : public QDialog
{
    Q_OBJECT

public:
    CIPAConsDlg( QVector<QChar>* pList, QWidget* parent = nullptr);
    ~CIPAConsDlg();

    void setupUI();

signals:
        void onSelected(QChar);
        void onDelete(QChar);

private slots:
    void onClicked();

private:
    QPushButton*     m_buttons[ROWS_1][COLS_1];
    QBitArray        m_btnState;              // records if a sound has been choosen or not.
    QWidget*         m_pParent;               // who created us.

    void changeBackground(int);               // helper function to manage background color of button.
};



#endif