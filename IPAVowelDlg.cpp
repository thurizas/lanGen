#include "IPAVowelDlg.h"


#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QDebug>

const QChar  vowelLabels[ROWS*COLS] = {'i', 'y' , '\0',    '\0', '\0',    '\0',   '\0',  0x0268,   0x289,   '\0',   '\0',   0x026f,    'u', 
                                      '\0', '\0', '\0',   0x26A,  'Y',    '\0',   '\0',    '\0',    '\0',   '\0', 0x028A,     '\0',   '\0', 
                                      '\0', '\0',  'e',  0x00F8, '\0',    '\0',   '\0',  0x0258,  0x0275,   '\0',   '\0',   0x0264,    'o',
                                      '\0', '\0', '\0',    '\0', '\0',    '\0',   '\0',    '\0',  0x0259,   '\0',   '\0',     '\0',   '\0',   
                                      '\0', '\0', '\0',    '\0', '\0',  0x025b, 0x0153,    '\0',  0x025C, 0x025E,   '\0',   0x028C, 0x0254, 
                                      '\0', '\0', '\0',    '\0', '\0',  0x00E6,   '\0',    '\0',    '\0', 0x0250,   '\0',     '\0',   '\0',
                                      '\0', '\0', '\0',    '\0', '\0',    '\0',    'a',  0x0276,    '\0',   '\0',   '\0',    0x0251, 0x0252};

const QString rowLabels[ROWS] = {"Close    ", "         ", "Close-Mid", "         ","Open-Mid ", "         ","Open     "};

const QString pronGuide[ROWS*COLS] = { "eas<b>y</b>", "d<b>uu</b>r ", "            ", "                         ", "                    ", "                       ", "                          ", "l<b>i</b>p              ", "g<b>oo</b>se            ", "            ", "                          ", "h<b>oo<\b>k  ", "bl<b>u</b>e,f<b>oo</b>d",
                                       "           ", "            ", "            ", "h<b>i</>t, s<b>i</>tting ", "Gl<b>u</b>ck(german)", "                       ", "                          ", "                        ", "                        ", "            ", "p<b>u</b>t,c<b>ou</b>ld   ", "             ", "                       ",
                                       "           ", "            ", "m<b>e</b>t  ", "d<b>e</b>ur(dutch)       ", "                    ", "                       ", "                          ", "n<b>u</b>t              ", "f<b>u</b>ll(swedish)    ", "            ", "                          ", "f<b>oo</b>t  ", "M<b>o</b>tiv(german)   ",
                                       "           ", "            ", "            ", "                         ", "                    ", "                       ", "                          ", "                        ", "<b>a</b>bout            ", "            ", "                          ", "             ", "                       ",
                                       "           ", "            ", "            ", "                         ", "                    ", "b<b>e</b>d             ", "g<b>o</b>                 ", "                        ", "t<b>u</b>rn,l<b>ea</b>rn", "b<b>u</b>t  ", "                          ", "r<b>u</b>n   ", "<b>o</b>besus          ",
                                       "           ", "            ", "            ", "                         ", "                    ", "c<b>a</b>t             ", "                          ", "                        ", "                        ", "c<b>u</b>t  ", "                          ", "             ", "                       ",
                                       "           ", "            ", "            ", "                         ", "                    ", "                       ", "<b>a</b>rm, f<b>a</b>ther ", "?                       ", "                        ", "            ", "                          ", " h<b>o</b>t  ", "c<b>ou</b>gh           " };
    


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
CIPAVowelDlg::CIPAVowelDlg( QVector<QChar>* pList, QWidget* parent) : QDialog(parent), m_pParent(parent/*this*/) 
{
    setupUI();

    m_btnState.resize(ROWS*COLS);
    m_btnState.fill(false);

    if(pList->size() > 0)
    {
        int ndx;
        QVector<QChar>::iterator    iter = pList->begin();
        while(pList->end() != iter)
        {
            for(ndx = 0; ndx < ROWS*COLS; ndx++)
            {
                if((*iter) == vowelLabels[ndx])
                {
                    m_btnState[ndx] = true;                             // mark button as selected
                    m_buttons[ndx/COLS][ndx%COLS]->setStyleSheet(QLatin1String("background-color: rgb(168, 255, 168);\nfont: 14pt \"Courier New\";")); 
                    break;
                }
            }

            ++iter;
        }
    }
}

CIPAVowelDlg::~CIPAVowelDlg()
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
void CIPAVowelDlg::setupUI()
{
    const int label_size=100;
    const int label_height=20;

    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(14);
    this->setFont(font);

    QPushButton *cancelButton;
    QPushButton *okButton;
 
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    this->resize(DLG_WIDTH + label_size,  DLG_HEIGHT+label_height);
    this->setFixedSize(DLG_WIDTH + label_size, DLG_HEIGHT+label_height);
    this->setWindowTitle("IPA Vowels");

    okButton = new QPushButton(this);
    okButton->setObjectName(QStringLiteral("okButton"));
    okButton->setGeometry(QRect(381, BUT_SZ*ROWS+MARGIN_SZ+label_height, 70, BUT_SZ));  // 381 - left side of button, 70 - length of button.
    okButton->setText("Close");

    //build top level labels...
    QLabel* label1 = new QLabel(this);
    QLabel* label2 = new QLabel(this);
    QLabel* label3 = new QLabel(this);
    label1->setGeometry(106, 0, 150, 25);
    label2->setGeometry(256, 0, 150, 25);
    label3->setGeometry(406, 0,  90, 25);
    label1->setStyleSheet("border: 1px inset grey");
    label2->setStyleSheet("border: 1px inset grey");
    label3->setStyleSheet("border: 1px inset grey");
    label1->setText("Front    ");
    label2->setText("Center   ");
    label3->setText("Back     ");
    
    // create our butttons...
    for(int row = 0; row < ROWS; row++)
    {
        QLabel*  pLabel = new QLabel(this);
        pLabel->setGeometry(0, (BUT_SZ)*row + label_height + MARGIN_SZ, label_size, BUT_SZ);
        pLabel->setText(rowLabels[row]);

        for(int col = 0; col < COLS; col++)
        {
            int ndx = row*COLS + col;
            m_buttons[row][col] = new QPushButton(this);
            m_buttons[row][col]->setObjectName(QString("btn_%1").arg(ndx));
            m_buttons[row][col]->resize(BUT_SZ,BUT_SZ);
            m_buttons[row][col]->move(BUT_SZ*col+MARGIN_SZ + label_size, BUT_SZ*row+MARGIN_SZ+label_height);
            m_buttons[row][col]->setStyleSheet(QLatin1String("background-color: rgb(240, 240, 240);\nfont: 14pt \"Courier New\";"));   
            m_buttons[row][col]->setToolTip(QString(pronGuide[ndx]));
            m_buttons[row][col]->show();
            if(QChar('\0') != vowelLabels[ndx])
                m_buttons[row][col]->setText(QString("%1").arg(vowelLabels[ndx]));
            else
                m_buttons[row][col]->setEnabled(false);

            connect(m_buttons[row][col], SIGNAL(clicked()), this, SLOT(onClicked()));
        }
    }
    
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
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
void CIPAVowelDlg::onClicked()
{
    //static QBitArray   btnState(ROWS*COLS);                   // bit array to denote if a button has been selected.
    QObject*   obj = sender();
    QString   strName = obj->objectName();                    // name is in form 'btn_## when ## is index in vowel array
    QString   strNdx = strName.right(strName.length() - 4);   // remove fixed preamble, 'btn_'
    int       ndx = atoi(strNdx.toStdString().c_str());       // extract the index

    changeBackground(ndx);

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
void CIPAVowelDlg::changeBackground(int ndx)
{
    if(QChar('\0') != vowelLabels[ndx])
    {   
        if(!m_btnState[ndx])                                    // button is currently in deselected state
        {
            m_btnState[ndx] = true;                             // mark button as selected
            m_buttons[ndx/COLS][ndx%COLS]->setStyleSheet(QLatin1String("background-color: rgb(168, 255, 168);\nfont: 14pt \"Courier New\";")); 
            emit onSelected(vowelLabels[ndx]);                    // emit our signal
        }
        else                                                   // button is currently in selected state
        {
            m_btnState[ndx] = false;                             // mark button as deselected
            m_buttons[ndx/COLS][ndx%COLS]->setStyleSheet(QLatin1String("background-color: rgb(240, 240, 240);\nfont: 14pt \"Courier New\";")); 
            emit onDelete(vowelLabels[ndx]);
        }
    }
}




