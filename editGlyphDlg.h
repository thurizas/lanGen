#ifndef _editGlyphDlg_h_
#define _editGlyphDlg_h_

#include <QDialog>
#include <QMap>


class QTableWidget;
class QPushButton;

class CEditGlyphDlg : public QDialog
{
    Q_OBJECT

public:
    CEditGlyphDlg( QVector<QChar>*,  QVector<QChar>*, QWidget* parent = nullptr);
    CEditGlyphDlg(QVector<QString>*, QWidget* parent = nullptr);

    QMap<QChar, QString> getXlationMapping() { return m_xlateMap; }
    void                 setXlationMap(QMap<QChar, QString>*);

    ~CEditGlyphDlg();

private:
    void setupUI(int);
    void buildXlationMap();

    QTableWidget*   m_phonemesList;
    QPushButton*    m_btnCancel;
    QPushButton*    m_btnOK;

    QMap<QChar, QString>  m_xlateMap;

private slots:
    void accept();
    void reject();
};


#endif