#include "Lexer.h"


int main()
{
    Lexer lexer("input_code.txt");
    std::vector<Token> tokenList;

    try {
        lexer.parse();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    lexer.printTokens(tokenList);
    return 0;
}
