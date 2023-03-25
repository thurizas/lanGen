/*
productions is an array (vector) of rule(s)

a rule is an array of tokens

for example, the string "(C)V | V(C); (C)V(C)" contains two rules, the string "(C)V|V(C)"
and the string "(C)V(C)" thus we can think of productions as:
              +-------------+
productions = | (C)V ^ V(C) |   where ^ is read 'or'
              +------+------+
              |   (C)V(C)   |
              +-------------+
*/
#include <QString>
#include <QDebug>

#include "generator.h"

CGenerator::CGenerator() : m_qstrClasses("CV")
{ }


CGenerator::CGenerator(int cntRules) : m_qstrClasses("CV")
{
    // allocate space for our rules array...
    m_productions = new std::vector<pruleT>[cntRules];

    for (int ndx = 0; ndx < cntRules; ndx++)
    {
        pruleT ptemp = new ruleT{ 0 };      // initialize everything to null

        m_productions->push_back(ptemp);
    }
}


CGenerator::~CGenerator() 
{ 

}


 // parses the input string and builds the production rule
bool    CGenerator::prepare(int ndxRule) 
{ 
    // populate information compents of rule structure....
    ruleT* rule = m_productions->at(ndxRule);
    rule->ruleNbr = ndxRule;
    rule->str = m_qstrRules;

    // determine number of choices in the rule, and allocate enough vectors.
    int cntOpts = m_qstrRules.count('|') + 1;
    tokenT    start;
    start.type = TOKEN_START;
    start.value = ' ';
    start.rep.first = 1;
    start.rep.second = 1;
    for (int ndx = 0; ndx < cntOpts; ndx++)
    {
        std::vector<pTokenT>* pvtemp = new std::vector<pTokenT>;
        //pvtemp->push_back(&start);
        rule->rules.push_back(pvtemp);                            
    }

    // parse the rule.
    parse(ndxRule, cntOpts);

    return true;
}

// generates a syllabel
QString CGenerator::generate() 
{ 
    QString ret = "";
    int    ruleNbr = 0;
    int    seqNbr = 0;
    pruleT rule;
    std::vector<pTokenT>*   psequence = nullptr;

    // pick which production to use....
    int cntProd = m_productions->size();
    if (cntProd > 1)        
    {
        ruleNbr = rand() % cntProd;
    }
    rule = m_productions->at(ruleNbr);

    // pick which rule (sequence) to use....
    int   cntRule = rule->rules.size();  
    if (cntRule > 1)
    {
        seqNbr = rand() % cntRule;
    }
    
    psequence = rule->rules.at(seqNbr);

    // evaluate the sequence
    std::vector<pTokenT>::iterator   viter;
    viter = psequence->begin();
    while (psequence->end() != viter)
    {
        switch ((*viter)->type)
        {
            case TOKEN_REQ:
                ret.append((*viter)->value);
                break;
            case TOKEN_OPT:
            {
                // TODO : handle multiple optional 
                int choice = rand() % 100 + 1;       // generate random number [1, 100]
                if (choice > 50)
                    ret.append((*viter)->value);
                break;
            }
        }
        ++viter;
    }


    return ret;
}


void CGenerator::parse(int ruleNbr, int opts)
{
    bool bOptional = false;         // optional construct
    bool bInRange = false;          // range construct
    int  nPos = 0;                  // which position of range we mucking with
    int cntOpts = opts;             // number of alterations in the rule...

    ruleT* rule = m_productions->at(ruleNbr);


    int curChild = 0;
    int len = m_qstrRules.length();

    for (unsigned int ndx = 0; ndx < len; ndx++)
    {
        QChar  chCur = m_qstrRules.at(ndx);

        if (isMember(chCur, m_qstrClasses))
        {
            pTokenT pnew = new(std::nothrow) tokenT;            // use array of vectors instead of pointers...
            if (pnew != nullptr)
            {
                    bOptional ? pnew->type = TOKEN_OPT : pnew->type = TOKEN_REQ;
                    pnew->value = chCur;
                    pnew->rep.first = 0;
                    pnew->rep.second = 1;

                    rule->rules.at(curChild)->push_back(pnew);               
            }
            else if (chCur.isDigit())
            {
                if (nPos = 0)
                    pnew->rep.first = chCur.digitValue();
                else if (nPos = 1)
                    pnew->rep.second = chCur.digitValue();
                else
                    qDebug() << "error in reading digit";

            }
        }
        else if (chCur == '(')
        {
            bOptional = !bOptional;
        }
        else if (chCur == ')')
        {
            bOptional = !bOptional;
        }
        else if (chCur == '|')
        {
            curChild++;               // increment our current child
        }
        else if (chCur == '{')
        {
            bInRange = !bInRange;
            nPos = 0;
        }
        else if (chCur == '}')
        {
            bInRange = !bInRange;
            nPos = 0;
        }
        else if (chCur == '[')
        {
            
        }
        else if (chCur == ']')
        {

        }
        else if (chCur == ',')
        {
            nPos++;
        }
        else if (chCur == ' ')           // eat white space...
        {

        }
        else
        {
            qDebug() << "...unrecognized token" << chCur;
        }
    }
}


bool CGenerator::isMember(QChar ch, QString classes)
{
    return (0 <= classes.indexOf(ch));
}




void CGenerator::print()
{
    int cntRules = m_productions->size();

    for (int ndx = 0; ndx < cntRules; ndx++)
    {
        pruleT  prule = m_productions->at(ndx);

        qDebug() << "rule index      : " << prule->ruleNbr;
        qDebug() << "rule string     : " << prule->str.toLatin1().data();
        int cntRules = prule->rules.size();
        qDebug() << "   number of alterations:" << cntRules;
        for (int jdx = 0; jdx < cntRules; jdx++)
        {
            qDebug() << "    alteration " << jdx;
            std::vector<struct token*>* pvtemp = prule->rules.at(jdx); 
            std::vector<struct token*>::iterator  viter = pvtemp->begin();
            while (pvtemp->end() != viter)
            {
                (*viter)->print();
                viter++;
            }
        }
    }
}


std::ostream& operator<<(std::ostream& os, const struct token& t)
{
    os << "Token type    : " << t.type << std::endl;
    os << "   Token value: " << t.value.toLatin1() << std::endl;
    os << "   token reps : (" << t.rep.first << ", " << t.rep.second << ")" << std::endl;
    return os;
}



