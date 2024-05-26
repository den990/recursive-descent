#pragma once
#include <fstream>
#include <vector>
#include <deque>
#include <sstream>
#include <iostream>
#include "Tokens.h"

class Lexer {
private:
    std::ifstream m_inputFile;
    std::ofstream m_outputFile;
    std::deque<std::string> stringAndChar;
    int lineNumber;
    std::string currentLine;
    size_t currentPosition;
    std::vector<Token> tokenList;
    Token token = Token::Default;
    int count = 0;
    Token getNextToken() {
        token = tokenList[count++];
        return token;
    }

public:
  
    Lexer(const std::string& filename);
    ~Lexer();
    Token GetMoreTokens();
    Token GetToken();
    void parseConsts();
    void SectionVar();
    void ListSectionVars();
    void Variables();
    void SectionConst();
    void ListSectionsConst();
    void Consts();
    bool CheckMul();
    void TermPrime();
    void Term();
    bool CheckPlus();
    void SimpleExprPrime();
    void SimpleExpr();
    bool CheckRelation();
    void ExprPrime();
    void Expr();
    void CheckPrefix();
    void CheckPostfix();
    void F();
    void Assign();
    void A();
    void If();
    void St();
    void Repeat();
    void ListStms();
    void ListStmsElse();
    void ListId();
    void Read();
    void ElemWrite();
    void ListWrite();
    void Write();
    void While();
    void For();
    void parseVariables();
    void parseSt();
    void parse();
    std::string tokenToStringFunc(Token token);
    bool MakeToken(std::string& word, int indexStr, size_t position, std::deque<std::string>& vectorOfStringAndChar, std::ofstream& outputFile, std::vector<Token>& tokenList);
    void processStringAndChar(std::deque<std::string>& vectorOfStringAndChar, std::string& inputStr, size_t indexStart);
    void ProcessStr(std::ifstream& inputFile, std::string& inputStr, int& indexStr, std::ofstream& outputFile, std::vector<Token>& tokenList);
    void printTokens(const std::vector<Token>& tokenList);
    void Process(std::ifstream& input, std::ofstream& output, std::vector<Token>& tokenList);
    void CaseBody();
    void SwitchCaseBlock();
    void SwitchCase();
    size_t CountDoubleQuotes(const std::string& str);
};