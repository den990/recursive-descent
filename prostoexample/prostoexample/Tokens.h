#pragma once
#include <map>
#include <string>
#include <algorithm>

enum class Token {
    Const = 0,
    Var,
    Ident,
    Type,
    Assignment,
    Semicolon,
    Relation,
    Numb,
    Minus,
    Mul,
    Div,
    Mod,
    Divine,
    Not,
    LParen,
    RParen,
    Plus,
    Or,
    And,
    Comma,
    Noc,
    Rav,
    If,
    Then,
    Else,
    Fi,
    Endm,
    While,
    For,
    Write,
    Read,
    Do,
    Od,
    Rof,
    OpBracket,
    ClBracket,
    OBracket,
    CBracket,
    Quote,
    Daer,
    Tirw,
    Eof,
    String,
    Char,
    Main,
    Default,
    Case,
    Switch,
    Colon,
    Break,
    QOBracket,
    QCBracket,
    Repeat,
    Until,
    Tea,
    EndVector,
    Begin, 
    End
};
inline std::map<Token, std::string> tokenToString = {
    {Token::Const, "Const"},
    {Token::Var, "Var"},
    {Token::Ident, "Ident"},
    {Token::Type, "Type"},
    {Token::Assignment, "Assignment"},
    {Token::Semicolon, "Semicolon"},
    {Token::Relation, "Relation"},
    {Token::Numb, "Numb"},
    {Token::Minus, "Minus"},
    {Token::Mul, "Mul"},
    {Token::Div, "Div"},
    {Token::Mod, "Mod"},
    {Token::Divine, "Divine"},
    {Token::Not, "Not"},
    {Token::LParen, "LParen"},
    {Token::RParen, "RParen"},
    {Token::Plus, "Plus"},
    {Token::Or, "Or"},
    {Token::And, "And"},
    {Token::Comma, "Comma"},
    {Token::Noc, "NOC"},
    {Token::Rav, "Rav"},
    {Token::If, "If"},
    {Token::Then, "Then"},
    {Token::Else, "Else"},
    {Token::Fi, "Fi"},
    {Token::Endm, "Endm"},//
    {Token::While, "While"},
    {Token::For, "For"},
    {Token::Write, "Write"},
    {Token::Read, "Read"},
    {Token::Do, "Do"},
    {Token::Od, "Od"},//
    {Token::Rof, "Rof"},//
    {Token::OpBracket, "OpBracket"},
    {Token::ClBracket, "ClBracket"},
    {Token::OBracket, "OBracket"},
    {Token::CBracket, "CBracket"},
    {Token::QOBracket, "QOBracket"},
    {Token::QCBracket, "QCBracket"},
    {Token::Quote, "Quote"},
    {Token::Daer, "Daer"},
    {Token::Tirw, "Tirw"},
    {Token::String, "String"},//�� � ���������
    {Token::Char, "Char"},//
    {Token::Eof, "EOF"},
    {Token::Main, "FUNMAIN"},
    {Token::Default, "Default"},
    {Token::Colon, "Colon"},
    {Token::Case, "Case"},
    {Token::Switch, "Switch"},
    {Token::Break, "Break"},
    {Token::Until, "Until"},
    {Token::Repeat, "Repeat"},
    {Token::Tea, "Tea"},
    {Token::EndVector, "EndVector" },
    {Token::Begin, "BEGIN"},
    {Token::End, "END"}

};

inline std::string toLowerFunc(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

inline std::map<std::string, Token> keywords = {
     std::make_pair(toLowerFunc("not"), Token::Not),
    std::make_pair(toLowerFunc("funmain"), Token::Main),
    std::make_pair(toLowerFunc("begin"), Token::Begin),
    std::make_pair(toLowerFunc("end"), Token::End),
    std::make_pair(toLowerFunc("int"), Token::Type),
    std::make_pair(toLowerFunc("char"), Token::Type),
    std::make_pair(toLowerFunc("double"), Token::Type),
    std::make_pair(toLowerFunc("float"), Token::Type),
    std::make_pair(toLowerFunc("string"), Token::Type),
    std::make_pair(toLowerFunc("for"), Token::For),
    std::make_pair(toLowerFunc("rof"), Token::Rof),
    std::make_pair(toLowerFunc("while"), Token::While),
    std::make_pair(toLowerFunc("if"), Token::If),
    std::make_pair(toLowerFunc("fi"), Token::Fi),
    std::make_pair(toLowerFunc("else"), Token::Else),
    std::make_pair(toLowerFunc("then"), Token::Then),
    std::make_pair(toLowerFunc("const"), Token::Const),
    std::make_pair(toLowerFunc("noc"), Token::Noc),
    std::make_pair(toLowerFunc("read"), Token::Read),
    std::make_pair(toLowerFunc("daer"), Token::Daer),
    std::make_pair(toLowerFunc("endm"), Token::Endm),
    std::make_pair(toLowerFunc("write"), Token::Write),
    std::make_pair(toLowerFunc("tirw"), Token::Tirw),
    std::make_pair(toLowerFunc("do"), Token::Do),
    std::make_pair(toLowerFunc("od"), Token::Od),
    std::make_pair(toLowerFunc("div"), Token::Div),
    std::make_pair(toLowerFunc("mod"), Token::Mod),
    std::make_pair(toLowerFunc("var"), Token::Var),
    std::make_pair(toLowerFunc("rav"), Token::Rav),
    std::make_pair(toLowerFunc("/"), Token::Divine),
    std::make_pair(toLowerFunc("break"), Token::Break),
    std::make_pair(toLowerFunc("default"), Token::Default),
    std::make_pair(toLowerFunc("case"), Token::Case),
    std::make_pair(toLowerFunc("switch"), Token::Switch),
    std::make_pair(toLowerFunc("Repeat"), Token::Repeat),
    std::make_pair(toLowerFunc("Until"), Token::Until),
    std::make_pair(toLowerFunc("Tea"), Token::Tea),

};

inline std::map<std::string, Token> separators = {
    std::make_pair(toLowerFunc("("), Token::OpBracket),
    std::make_pair(toLowerFunc(")"), Token::ClBracket),
    std::make_pair(toLowerFunc("["), Token::QOBracket),
    std::make_pair(toLowerFunc("]"), Token::QCBracket),
    std::make_pair(toLowerFunc("{"), Token::OBracket),
    std::make_pair(toLowerFunc("}"), Token::CBracket),
    std::make_pair(toLowerFunc(";"), Token::Semicolon),
    std::make_pair(toLowerFunc(","), Token::Comma),
    std::make_pair(toLowerFunc("/"), Token::Divine),
    std::make_pair(toLowerFunc("*"), Token::Mul),
    std::make_pair(toLowerFunc("+"), Token::Plus),
    std::make_pair(toLowerFunc("-"), Token::Minus),
    std::make_pair(toLowerFunc("or"), Token::Or),
    std::make_pair(toLowerFunc("And"), Token::And),
    std::make_pair(toLowerFunc(":="), Token::Assignment),
    std::make_pair(toLowerFunc(":>"), Token::Colon)
};
inline std::map<std::string, Token> Relation = {
    std::make_pair("==", Token::Relation),
    std::make_pair("<=", Token::Relation),
    std::make_pair(">=", Token::Relation),
    std::make_pair("=<", Token::Relation),
    std::make_pair("<", Token::Relation),
    std::make_pair(">", Token::Relation),
    std::make_pair("<>", Token::Relation)
};