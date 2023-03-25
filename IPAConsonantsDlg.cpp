#include "IPAConsonantsDlg.h"


#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include <QBitArray>


const QChar  consLabels[ ROWS_1*COLS_1] = {   'p',    'b',   '\0',   '\0',   '\0',   '\0',    't',    'd',   '\0',   '\0', 0x0288, 0x0256,    'c', 0x025F,   'k',    'g',    'q', 0x0262,   '\0',   '\0', 0x02A1,    '\0', 
                                             '\0',    'm',   '\0', 0x0271,   '\0',   '\0',   '\0',    'n',   '\0',   '\0',   '\0', 0x0273,   '\0', 0x0272,  '\0', 0x014b,   '\0', 0x0274,   '\0',   '\0',   '\0',    '\0',
                                             '\0', 0x0299,   '\0',   '\0',   '\0',   '\0',   '\0',    'r',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',  '\0',   '\0',   '\0', 0x0280,   '\0',   '\0',   '\0',    '\0',
                                             '\0',   '\0',   '\0', 0x2c71,   '\0',   '\0',   '\0', 0x027e,   '\0',   '\0',   '\0', 0x027d,   '\0',   '\0',  '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',    '\0',
                                           0x0278, 0x03B2,    'f',    'v', 0x03B8, 0x00F0,    's',    'z', 0x0283, 0x0292, 0x0282, 0x0290, 0x00E7, 0x029D,   'x', 0x0263, 0x03C7, 0x0281, 0x0127, 0x02A2,    'h', 0x0266,
                                             '\0',   '\0',   '\0',   '\0',   '\0',   '\0', 0x026D, 0x026E,   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',  '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',    '\0',
                                             '\0',   '\0',   '\0', 0x028B,   '\0',   '\0',   '\0', 0x0279,   '\0',   '\0',   '\0', 0x027B,   '\0',    'j',  '\0', 0x0270,   '\0',   '\0',   '\0',   '\0',   '\0',    '\0',
                                             '\0',   '\0',   '\0',   '\0',   '\0',   '\0', 0x026B,    'l',   '\0',   '\0',   '\0', 0x026D,   '\0', 0x028E,  '\0', 0x029F,   '\0',   '\0',   '\0',   '\0',   '\0',    '\0',
                                           0X028D,    'w', 0X0265,   '\0', 0X0295, 0x029C, 0X0294, 0X0291, 0X0255, 0X027A, 0X0267, 0x02A4, 0x02A7,   '\0',  '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',    '\0'};


const QString rowLabels[ROWS_1] = {"Plosive    ", "Nasal      ", "Trill      ", "Tap/Flap   ","Fricative  ", "Lat. Fric  ","Approximant", "Lat Approx ", "Miscell.   "};

const QString pronGuide[ROWS_1*COLS_1] = { "<b>p</b>ater, s<b>p</b>in     ","<b>b</b>ut, <b>b</b>utt       ",                            '\0',                            '\0',                            '\0',                            '\0',"s<b>t</b>op                   ","<b>d</b>i<b>d</b>, <b>d</b>o  ",                            '\0',                            '\0', "<b>t</b>ime","<b>d</b>ine                   ","n/a                           ","<b>g</b>eese                  ","s<b>c</b>an, ta<b>k</b>e      ","<b>g</b>o, <b>g</b>et         ","n/a                           ","<b>g</b>audy                  ",                            '\0',                            '\0',"epiglotal stop                ",                            '\0',
                                           '\0'                            ,"<b>m</b>an, le<b>m</b>on      ",                            '\0',"sy<b>m</b>phony               ",                            '\0',                            '\0',                            '\0',"<b>n</b>emo, <b>n</b>o        ",                            '\0',                            '\0',                                           '\0',"ca<b>ny</b>on                 ",                            '\0',"n/a                           ",                            '\0',"si<b>ng</b>er, ri<b>ng</b>    ",                            '\0',"n/a                           ",                            '\0',                            '\0',                            '\0',                            '\0',
                                           '\0'                            ,"n/a                           ",                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',"<b>r</b>ed, t<b>r</b>y        ",                            '\0',                            '\0',                                           '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',"<b>r</b>ot (german)           ",                            '\0',                            '\0',                            '\0',                            '\0',
                                           '\0'                            ,                            '\0',                            '\0',"n/a                           ",                            '\0',                            '\0',                            '\0',"<b>r</b>oma, be<b>tt</b>er    ",                            '\0',                            '\0',                                           '\0',"<b>r</b>iem (dutch)           ",                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',
                                           "n/a                           ","a<b>b</b>er (german)          ","<b>f</b>ool, enou<b>gh</b>    ","<b>v</b>oice                  ","<b>th</b>ing                  ","<b>th</b>is                   ","<b>s</b>ee, pa<b>ss</b>       ","<b>z</b>oo, ro<b>s</b>es      ","<b>sh</b>e, cra<b>sh</b>      ","vi<b>si</b>on, trea<b>s</b>ure","n/a                                          ","n/a                           ","<b>h</b>uge                   ","<b>J</b>acke (german)         ","lo<b>ch</b>                   ","damali<b>g</b>e (german)      ","Da<b>ch</b> (german)          ","<b>R</b>ost (german)          ","<b>h</b>at                    ","n/a                           ","<b>h</b>onor, <b>h</b>am      ","a<b>h</b>ead                  ",
                                           '\0'                            ,                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',"n/a                           ","n/a                           ",                            '\0',                            '\0',                                           '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',
                                           '\0'                            ,                            '\0',                            '\0',"<b>w</b>ang (dutch)           ",                            '\0',                            '\0',                            '\0',"<b>R</b>ebe (german)          ",                            '\0',                            '\0',                                           '\0',"<b>r</b>un, ve<b>r</b>y       ",                            '\0',"<b>j</b>ucundus, <b>y</b>es   ",                            '\0',"e<b>m</b>phasis               ",                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',
                                           '\0'                            ,                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',"pu<b>ll</b>                   ","<b>l</b>udus, <b>l</b>eft     ",                            '\0',                            '\0',                                           '\0',"n/a                           ",                            '\0',"mi<b>lli</b>on                ",                            '\0',"mi<b>l</b>k                   ",                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',
                                           "<b>wh</b>ine                  ","<b>v</b>olvo,<b>w</b>e        ","n/a                           ",                            '\0',"Mutter<b>r</b> (german)       ","n/a                           ","uh-oh (glottal stop)          ","vi<b>si</b>on                 ","<b>sh</b>ip                   ","n/a                           ","n/a                                          ","lar<b>ge</b>, <b>j</b>ust     ","<b>ch</b>air, pic<b>t</b>ure  ",                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0',                            '\0' };



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
CIPAConsDlg::CIPAConsDlg(QVector<QChar>* pList, QWidget* parent) : QDialog(parent), m_pParent(parent/*this*/) 
{
    setupUI();

    m_btnState.resize(ROWS_1*COLS_1);
    m_btnState.fill(false);

    // TODO process list of vowels already entered and mark them.
    if(pList->size() > 0)
    {
        int ndx;
        QVector<QChar>::iterator    iter = pList->begin();
        while(pList->end() != iter)
        {
            for(ndx = 0; ndx <  ROWS_1*COLS_1; ndx++)
            {
                if(consLabels[ndx] == (*iter))
                {
                    m_btnState[ndx] = true;                             // mark button as selected
                    m_buttons[ndx/COLS_1][ndx%COLS_1]->setStyleSheet(QLatin1String("background-color: rgb(168, 255, 168);\nfont: 14pt \"Courier New\";")); 
                    break;
                }
            }

            ++iter;
        }
    }
    // TODO : setup hover help dialogs... see https://stackoverflow.com/questions/411823/how-do-i-implement-qhoverevent-in-qt
}

CIPAConsDlg::~CIPAConsDlg()
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
void CIPAConsDlg::setupUI()
{
    const int label_size=140;
    const int label_height=20;

    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(14);
    this->setFont(font);

    QPushButton *cancelButton;
    QPushButton *okButton;
 
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    this->resize(CONS_DLG_WIDTH+ label_size,  CONS_DLG_HEIGHT+label_height);
    this->setFixedSize(CONS_DLG_WIDTH+ label_size, CONS_DLG_HEIGHT+label_height);
    this->setWindowTitle("IPAConsonants");

    okButton = new QPushButton(this);
    okButton->setObjectName(QStringLiteral("okButton"));
    okButton->setGeometry(QRect(730/*381*/, BUT_SZ*(ROWS_1+1)+MARGIN_SZ, 70, BUT_SZ));  // 381 - left side of button, 70 - length of button.  19*30 = 570
    okButton->setText("Close");

    // create our butttons...
    for(int row = 0; row <  ROWS_1; row++)
    {
        QLabel*  pLabel = new QLabel(this);
        pLabel->setGeometry(0, (BUT_SZ)*row + label_height + MARGIN_SZ, label_size, BUT_SZ);
        pLabel->setText(rowLabels[row]);

        for(int col = 0; col < COLS_1; col++)
        {
            int ndx = row*COLS_1 + col;
            m_buttons[row][col] = new QPushButton(this);
            m_buttons[row][col]->setObjectName(QString("btn_%1").arg(ndx));
            m_buttons[row][col]->resize(BUT_SZ,BUT_SZ);
            m_buttons[row][col]->move(BUT_SZ*col+MARGIN_SZ + label_size,BUT_SZ*row+MARGIN_SZ+label_height);
            m_buttons[row][col]->setStyleSheet(QLatin1String("background-color: rgb(240, 240, 240);\nfont: 14pt \"Courier New\";"));   
            m_buttons[row][col]->setToolTip(QString(pronGuide[ndx]));
            m_buttons[row][col]->show();
            if(QChar('\0') != consLabels[ndx])
                m_buttons[row][col]->setText(QString("%1").arg(consLabels[ndx]));
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
void CIPAConsDlg::onClicked()
{
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
void CIPAConsDlg::changeBackground(int ndx)
{
    if(QChar('\0') != consLabels[ndx])
    {   
        
        if(!m_btnState[ndx])                                    // button is currently in deselected state
        {
            m_btnState[ndx] = true;                             // mark button as selected
            m_buttons[ndx/COLS_1][ndx%COLS_1]->setStyleSheet(QLatin1String("background-color: rgb(168, 255, 168);\nfont: 14pt \"Courier New\";")); 
            emit onSelected(consLabels[ndx]);                    // emit our signal
        }
        else                                                   // button is currently in selected state
        {
            m_btnState[ndx] = false;                             // mark button as deselected
            m_buttons[ndx/COLS_1][ndx%COLS_1]->setStyleSheet(QLatin1String("background-color: rgb(240, 240, 240);\nfont: 14pt \"Courier New\";")); 
            emit onDelete(consLabels[ndx]);
        }
    }
}
