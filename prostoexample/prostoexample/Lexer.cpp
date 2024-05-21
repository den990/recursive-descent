#include "Lexer.h"


Lexer::Lexer(const std::string& filename) : lineNumber(0), currentPosition(0) {
    m_inputFile.open(filename);
    m_outputFile.open("output.txt");
}

Lexer::~Lexer() {
    m_inputFile.close();
    m_outputFile.close();
}

Token Lexer::GetMoreTokens() {
    if (count < tokenList.size()) {
        return tokenList[count++];
    }
    else {
        return Token::EndVector;
    }
}

Token Lexer::GetToken() {
    return getNextToken();
}
void Lexer::parseConsts() {
    if (GetToken() != Token::Main) {
        throw std::exception("Expected main at the beginning of the program");
    }
    Consts();
}

void EmptySt() {}
//declaration

void Lexer::SectionVar()
{
    if (GetToken() == Token::Type && GetToken() == Token::Ident)
    {
        token = GetToken();
        if (token == Token::Assignment)
        {
            Expr();
        }
        else if (token == Token::Comma)
        {
            ListId();
        }
        else
            throw std::exception("expected 'Assignment' or 'Comma'");
    }
    else
        throw std::exception("expected 'Type' or 'Ident'");
}

void Lexer::ListSectionVars()
{
    SectionVar();
    if (token == Token::Comma)
        ListSectionVars();
}

void Lexer::Variables()
{
    ListSectionVars();
    if (token != Token::Rav)
    {
        throw std::exception("expected 'Rav'");
    }
}

void Lexer::SectionConst()
{
    if (token == Token::Type)
    {
        if (GetToken() == Token::Ident)
        {

            if (GetToken() == Token::Assignment)
            {
                Expr();
            }
            else
                throw std::exception(("expected Assignment given " + tokenToString[token]).c_str());
        }
        else
            throw std::exception(("expected Ident given " + tokenToString[token]).c_str());
    }
    else
        throw std::exception(("expected Type given " + tokenToString[token]).c_str());


}

void Lexer::ListSectionsConst()
{
    token = GetToken();
    if (token == Token::Noc)
        return;
    else if (token == Token::Type)
    {
        SectionConst();
        if (token == Token::Noc)
            return;
        else if (token == Token::Semicolon)
            ListSectionsConst();
        else
            throw std::exception(("expected Semicolon or Noc given " + tokenToString[token]).c_str());

    }
    else
        throw std::exception(("expected Type or Noc given " + tokenToString[token]).c_str());

}

void Lexer::Consts()
{
    if (GetToken() != Token::Const)
    {
        throw std::exception(("expected Const given " + tokenToString[token]).c_str());
    }
    ListSectionsConst();
    if (token != Token::Noc)
    {
        throw std::exception(("expected Noc given " + tokenToString[token]).c_str());

    }
}
//expression
bool Lexer::CheckMul()
{
    return token == Token::Mul || token == Token::Divine
        || token == Token::Div || token == Token::Mod || token == Token::And;
}

void Lexer::TermPrime()
{
    if (CheckMul())
    {
        F();
        TermPrime();
    }
}

void Lexer::Term()
{
    F();
    TermPrime();
}

bool Lexer::CheckPlus()
{
    return token == Token::Plus
        || token == Token::Or;
}

void Lexer::SimpleExprPrime()
{
    if (CheckPlus())
    {
        Term();
        SimpleExprPrime();
    }
}

void Lexer::SimpleExpr()
{
    Term();
    SimpleExprPrime();
}

bool Lexer::CheckRelation()
{
    return token == Token::Relation;
}

void Lexer::ExprPrime()
{
    if (CheckRelation())
    {
        SimpleExpr();
        ExprPrime();
    }
}

void Lexer::Expr()
{
    SimpleExpr();
    ExprPrime();
}

void Lexer::CheckPrefix()
{
    auto nextToken = tokenList[count];
    if ((nextToken == Token::Minus && token == Token::Minus) ||
        (nextToken == Token::Plus && token == Token::Plus))
    {
        token = GetToken();
    }
    else if (token == Token::Plus && nextToken != Token::Plus)
        throw std::runtime_error("prefix exception");
}

void Lexer::CheckPostfix()
{
    auto nextToken = tokenList[count];
    if ((nextToken == Token::Minus && token == Token::Minus) ||
        (nextToken == Token::Plus && token == Token::Plus))
    {
        token = GetToken();
        token = GetToken();
        if (token == Token::Minus)
            F();
    }
    else if (token == Token::Minus && nextToken != Token::Minus)
        throw std::runtime_error("postfix exception");
}

void Lexer::F()
{
    token = GetToken();
    if (
        token == Token::Minus
        || token == Token::Not || token == Token::Plus
        )
    {
        CheckPrefix();
        F();
    }
    else if (token == Token::OpBracket)
    {
        Expr();
        if (token == Token::ClBracket) {
            token = GetToken();
            if (token == Token::Minus)
                F();
            else
                return;
        }
        else
        {
            throw std::exception("ClBracket expected");
        }
    }
    else if (
        token == Token::Numb
        || token == Token::Ident || token == Token::String || token == Token::Char
        )
    {
        token = GetToken();
        CheckPostfix();
        return;
    }
    else
        throw std::exception("Expected number or ident or string or char or minus or not or plus");
}
//if
void Lexer::Assign()
{
    token = GetToken();

    if (token != Token::Assignment)
    {
        throw std::exception("excepted ':='");
        return;
    }

    Expr();

    if (token != Token::Semicolon)
    {
        throw std::exception("excepted ';'");
    }
}

void Lexer::A()
{
    if (token == Token::Semicolon)
    {
        EmptySt();
    }
    else if (token == Token::Else)
    {
        ListStmsElse();
    }
    else {
        ListStmsElse();
    }
}

void Lexer::If()
{
    if (GetToken() != Token::OpBracket)
    {
        throw std::exception("excepted 'OpBracket1'");
        return;
    }

    Expr();

    if (token != Token::ClBracket)
    {
        throw std::exception("excepted 'ClBracket'");
        return;
    }

    if (GetToken() != Token::Then)
    {
        throw std::exception("excepted 'then'");
        return;
    }

    ListStmsElse();
    A();


    if (token != Token::EndIf)
    {
        throw std::exception("excepted 'fi'");
    }
}

void Lexer::St()
{
    token = GetToken();

    switch (token)
    {
    case Token::Semicolon:
        EmptySt();
        break;
    case Token::Ident:
        Assign();
        break;
    case Token::If:
        If();
        break;
    case Token::While:
        While();
        break;
    case Token::For:
        For();
        break;
    case Token::Write:
        Write();
        break;
    case Token::Tirw:
        return;
        break;
    case Token::Read:
        Read();
        break;
    case Token::Daer:
        return;
        break;
    case Token::Switch:
        SwitchCaseBlock();
        break;
    case Token::CBracket:
        break;
    case Token::Endm:
        throw std::exception("expected }");
        break;
    case Token::EndFor:
        return;
        break;
    case Token::Od:
        return;
        break;
    case Token::EndIf:
        return;
        break;
    case Token::Tea:
        return;
        break;
    case Token::Repeat:
        Repeat();
        break;
    case Token::Until:
        return;
        break;
    case Token::Else:
        return;
        break;
    case Token::End:
        return;
        break;
    default:
        throw std::exception("St error");
        break;
    }
}

//Repeat
void Lexer::Repeat() {
    if (token != Token::Repeat)
    {
        throw std::exception("Expected 'Repeat'");
    }
    ListStmsElse();
    if (GetToken() != Token::Until)
    {
        throw std::exception("Expected 'Until'");
    }
    Expr();
}

void Lexer::ListStms()
{

    St();

    if (token != Token::CBracket)
    {
        if (count == tokenList.size())
        {
            throw std::exception("expected }");
        }
        ListStms();
    }
}

void Lexer::ListStmsElse()
{

    St();

    if ((token != Token::EndFor) && (token != Token::Od) && (token != Token::EndIf) && (token != Token::Tea) && (token != Token::Else))
    {
        if (count == tokenList.size())
        {
            throw std::exception("expected do or rof");
        }
        ListStmsElse();
    }
    else return;
}
//readwrite
void Lexer::ListId()
{
    if (GetToken() != Token::Ident)
        throw std::exception("Operator READ expected 'Ident'");
    if (GetToken() == Token::Comma) {
        ListId();
    }

    else if (token == Token::Ident) {
        throw std::exception("expected comma");
    }
}

void Lexer::Read()
{
    if (GetToken() != Token::OpBracket) {
        throw std::exception("expected '('");
    }
    ListId();
    if (token != Token::ClBracket) {
        throw std::exception("expected ')'");
    }
    GetToken();
    if (token != Token::Daer) {
        throw std::exception("expected 'Daer'");
    }
}

void Lexer::ElemWrite()
{
    token = GetToken();
    if (token == Token::Ident || token == Token::String || token == Token::CBracket || token == Token::Char)
    {
        token = GetToken();
    }
    else if ((token != Token::String) && (token != Token::Ident) && (token != Token::Char))
    {
        throw std::exception("expected 'String' or 'Ident' or 'Char'");
    }
    else {
        token = GetToken();
    }
}

void Lexer::ListWrite()
{
    ElemWrite();
    if (token == Token::Comma)
    {
        ListWrite();
    }
    else if (token == Token::Ident || token == Token::String || token == Token::Char) {
        throw std::exception("expected comma");
    }

}


void Lexer::Write()
{
    if (GetToken() != Token::OpBracket) {
        throw std::exception("expected '('");
    }
    ListWrite();

    if (token != Token::ClBracket) {
        throw std::exception("expected ')'");
    }
    if (GetToken() != Token::Tirw) {
        throw std::exception("expected 'Tirw'");
    }
}

//while
void Lexer::While() {
    if (GetToken() != Token::OpBracket)
    {
        throw std::exception("Expected 'OpBracket'");
    }
    Expr();
    if (token != Token::ClBracket)
    {
        throw std::exception("Expected 'ClBracket'");
    }
    if (GetToken() != Token::Do)
    {
        throw std::exception("Expected 'do'");
    }
    ListStmsElse();
    if (token != Token::Od)
    {
        throw std::exception("Expected 'od'");
    }
}
//for
void Lexer::For()
{
    if (GetToken() != Token::OpBracket)
    {
        throw std::exception("Expected 'OpBracket'");
    }
    if (GetToken() != Token::Type)
    {
        throw std::exception("Expected type");
    }
    if (GetToken() != Token::Ident)
    {
        throw std::exception("Expected identi");
    }
    if (GetToken() != Token::Assignment)
    {
        throw std::exception("Expected assignment");
    }
    Expr();
    if (token != Token::Semicolon)
    {
        throw std::exception("Expected semicolon");
    }
    if (GetToken() != Token::Ident)
    {
        throw std::exception("Expected identi");
    }
    if (GetToken() != Token::Relation)
    {
        throw std::exception("Expected relation");
    }
    Expr();
    if (token != Token::Semicolon)
    {
        throw std::exception("Expected comma");
    }
    Expr();
    ListStmsElse();
    if (GetToken() != Token::EndFor)
    {
        throw std::exception("Expected 'rof'");
    }
}


void Lexer::parseVariables() {
    if (GetToken() != Token::Var) {
        throw std::exception("Expected var");
    }
    while (token != Token::Rav) {
        SectionVar();
    }
}

void Lexer::parseSt() {
    if (GetToken() != Token::Begin) {
        throw std::exception("expected begin");
    }

    ListStms();

    if (GetToken() != Token::Endm) {
        throw std::exception("expected endm");
    }
    if (GetMoreTokens() != Token::EndVector) {
        throw std::exception("error you have code after endm");
    }
}

void Lexer::parse() {
    lineNumber++;
    currentPosition = 0;
    Process(m_inputFile, m_outputFile, tokenList);
    parseConsts();
    parseVariables();
    parseSt();
    printTokens(tokenList);

}
std::string Lexer::tokenToStringFunc(Token token) {
    if (tokenToString.find(token) != tokenToString.end()) {
        return tokenToString[token];
    }
    else {
        return "Unknown Token";
    }
}
bool Lexer::MakeToken(std::string& word, int indexStr, size_t position, std::deque<std::string>& vectorOfStringAndChar, std::ofstream& outputFile, std::vector<Token>& tokenList)
{
    if (word == "")
    {
        return false;
    }

    for (auto& item : keywords)
    {
        size_t index;
        if (word == item.first)
        {
            index = 0;
            word.erase(index, item.first.size());
            std::string secondStr = word.substr(index, word.size() - index);
            word = word.substr(0, index);
            MakeToken(word, indexStr, position, vectorOfStringAndChar, outputFile, tokenList);
            tokenList.push_back(item.second);
            MakeToken(secondStr, indexStr, position + index + word.size(), vectorOfStringAndChar, outputFile, tokenList);
            return true;
        }
    }

    for (auto& item : separators)
    {
        size_t index = word.find(item.first);
        if (index != std::string::npos)
        {
            word.erase(index, item.first.size());
            std::string secondStr = word.substr(index, word.size() - index);
            word = word.substr(0, index);
            MakeToken(word, indexStr, position, vectorOfStringAndChar, outputFile, tokenList);
            tokenList.push_back(item.second);
            MakeToken(secondStr, indexStr, position + index + word.size(), vectorOfStringAndChar, outputFile, tokenList);
            return true;
        }
    }

    for (auto& item : Relation)
    {
        size_t index = word.find(item.first);
        if (index != std::string::npos)
        {
            word.erase(index, item.first.size());
            std::string secondStr = word.substr(index, word.size() - index);
            word = word.substr(0, index);
            MakeToken(word, indexStr, position, vectorOfStringAndChar, outputFile, tokenList);
            tokenList.push_back(item.second);
            MakeToken(secondStr, indexStr, position + index + word.size(), vectorOfStringAndChar, outputFile, tokenList);
            return true;
        }
    }

    if (word.front() == '\"' && word.back() == '\"')
    {
        tokenList.push_back(Token::String);
        return true;
    }
    else if (word.front() == '\'' && word.back() == '\'')
    {
        tokenList.push_back(Token::Char);
        return true;
    }


    //numbers
    if (word.find_first_not_of("0123456789.") == std::string::npos)
    {
        tokenList.push_back(Token::Numb);
        return true;
    }

    Token output;
    if (keywords.find(word) != keywords.end())
    {
        output = keywords[word];
        tokenList.push_back(output);
        return true;
    }

    if (separators.find(word) != separators.end())
    {
        output = separators[word];
        tokenList.push_back(output);
        return true;
    }

    if (word == "\"" && !vectorOfStringAndChar.empty())
    {
        word = vectorOfStringAndChar[0];
        vectorOfStringAndChar.pop_front();
        size_t i = word.find("\"") + 1;
        if (i < word.size() && word.find("\"", i) != std::string::npos)
        {
            tokenList.push_back(Token::Type);
        }
        else
        {
            outputFile << word << indexStr << " --- position " << position << "\n";
        }
        return true;
    }

    if (word == "\'" && !vectorOfStringAndChar.empty())
    {
        word = vectorOfStringAndChar[0];
        vectorOfStringAndChar.pop_front();
        size_t i = word.find("\'") + 1;
        if (i < word.size() && word.find("\'", i) != std::string::npos && word.size() == 3)
        {
            tokenList.push_back(Token::Type);
        }
        else
        {
            outputFile << word << indexStr << " --- position " << position << "\n";
        }
        return true;
    }

    if (isalpha(word[0]) || word[0] == '_') {
        for (auto i = 1; i < word.size(); i++) {
            if (!isalnum(word[i]) && word[i] != '_') {
                outputFile << word << indexStr << " --- position " << position << "\n";
                return true;
            }
        }

        tokenList.push_back(Token::Ident);
        return true;
    }

    outputFile << word << indexStr << " --- position " << position << "\n";
}

void Lexer::processStringAndChar(std::deque<std::string>& vectorOfStringAndChar, std::string& inputStr, size_t indexStart)
{
    if (inputStr.find("\"", indexStart) != std::string::npos)
    {
        std::string str;
        size_t start = inputStr.find("\"", indexStart);
        size_t end = inputStr.size() - 1;
        if (start + 1 < inputStr.size() && inputStr.find("\"", start + 1) != std::string::npos)
        {
            end = inputStr.find("\"", start + 1);
        }
        str = inputStr.substr(start, end - start + 1);
        vectorOfStringAndChar.push_back(str);
        inputStr.erase(start + 1, end - start);

        processStringAndChar(vectorOfStringAndChar, inputStr, start + 1);
    }
    if (inputStr.find("\'", indexStart) != std::string::npos)
    {
        std::string str;
        size_t start = inputStr.find("\'", indexStart);
        size_t end = inputStr.size() - 1;
        if (start + 1 < inputStr.size() and inputStr.find("\'", start + 1) != std::string::npos)
        {
            end = inputStr.find("\'", start + 1);
        }
        str = inputStr.substr(start, end - start + 1);
        vectorOfStringAndChar.push_back(str);
        inputStr.erase(start + 1, end - start);

        processStringAndChar(vectorOfStringAndChar, inputStr, start + 1);
    }
}

void Lexer::ProcessStr(std::ifstream& inputFile, std::string& inputStr, int& indexStr, std::ofstream& outputFile, std::vector<Token>& tokenList)
{
    std::deque<std::string> vectorOfStringAndChar;
    processStringAndChar(vectorOfStringAndChar, inputStr, 0);

    size_t position = 1;
    if (!inputStr.empty())
    {
        std::vector<std::string> words;
        std::string item;
        std::istringstream strStream(inputStr);
        while (getline(strStream, item, ' '))
        {
            MakeToken(item, indexStr, position, vectorOfStringAndChar, outputFile, tokenList);
            position += item.size() + 1;
        }
    }
}
void Lexer::printTokens(const std::vector<Token>& tokenList) {
    for (Token token : tokenList) {
        std::cout << "Token: " << tokenToStringFunc(token) << std::endl;
    }
}

void Lexer::Process(std::ifstream& input, std::ofstream& output, std::vector<Token>& tokenList) {
    std::string inputStr, inputString;
    int indexStr = 1;

    while (getline(input, inputStr)) {
        if (inputStr.empty()) {
            continue;
        }
        inputString = toLowerFunc(inputStr);
        ProcessStr(input, inputString, indexStr, output, tokenList);
        indexStr++;
    }
}

void Lexer::CaseBody()
{
    if (GetToken() == Token::Colon)
    {
        St();
        if (GetToken() == Token::Semicolon &&
            GetToken() == Token::Break &&
            GetToken() == Token::Semicolon)
        {
            return;
        }
        else
        {
            throw std::exception("Expected sequence '; break ;' after statement");
        }
    }
    else
    {
        throw std::exception("Expected sequence 'ident :' inside switch case");
    }
}

void Lexer::SwitchCaseBlock()
{
    SwitchCase();
}

void Lexer::SwitchCase()
{
    if (token == Token::Switch && GetToken() == Token::Ident && GetToken() == Token::QOBracket)
    {
        const unsigned CaseCountLimit = 1000;
        for (unsigned caseNumber = 0; caseNumber <= CaseCountLimit; caseNumber++)
        {
            token = GetToken();
            if (token == Token::QCBracket)
            {
                if (caseNumber == 0)
                {
                    throw std::exception("Expected min 1 case or default case inside switch case body!'");
                }
                return;
            }
            else if (caseNumber == CaseCountLimit)
            {
                std::string msg = "Error: Out of switch case range! Max available cases count ";
                std::stringstream ss;
                ss << msg << CaseCountLimit;
                throw std::exception(ss.str().c_str());
            }
            else if (token == Token::Default)
            {
                CaseBody();
                if (GetToken() == Token::QCBracket)
                {
                    return;
                }
                else
                {
                    throw std::exception("Expected ']' after default case !'");
                }
            }
            else if (token == Token::Case)
            {
                if (GetToken() == Token::Ident)
                {
                    CaseBody();
                }
                else
                {
                    throw std::exception("Expected ident after 'case'");
                }
            }
            else
            {
                throw std::exception("Expected 'case' or 'default' inside switch case");
            }
        }
    }
    else
    {
        throw std::exception("Expected sequence 'switch ident ['");
    }
}