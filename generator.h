#pragma once

#include <QPair>
#include <QDebug>

#include <vector>
#include <iostream>

enum { TOKEN_START, TOKEN_OPT, TOKEN_REQ, TOKEN_END };


typedef struct token
{
    int                         type;      // optional | required | start | end
    QChar                       value;
    QPair<int, int>             rep;
    
    friend std::ostream& operator<<(std::ostream& os, const struct token&);
    void print() 
    { 
        qDebug() << "Token type    : " << type;
        qDebug() << "   Token value: " << value.toLatin1();
        qDebug() << "   token reps : (" << rep.first << ", " << rep.second << ")";
    }
} tokenT, *pTokenT;

typedef struct rule
{
    QString                                   str;
    int                                       ruleNbr;
    std::vector<std::vector<struct token*>* > rules;   // list of alternatives in a rule

} ruleT, *pruleT;



class CGenerator 
{
public:
    CGenerator(int);
    ~CGenerator();

    QString getString() { return m_qstrRules; }
    void    setString(QString str) { m_qstrRules = str; }

    bool    prepare(int);    // int -- what rule we working with
    QString generate();      // generates a syllabel
    void    print();



private:
    CGenerator();                           // hide default constructor force use of paramertized
    QString                m_qstrRules;     // string passed in.
    QString                m_qstrClasses;   // phoneme class we know about,  default is C V
    std::vector<pruleT>*   m_productions;   // productions for the syllabel

    void parse(int, int);
    bool isMember(QChar, QString);


};
