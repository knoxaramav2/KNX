#ifndef EXEC_KEYWORD
#define EXEC_KEYWORD

token * runKeyword(node * n, token * arg, lexeme word);
token * runOperator(token * arg, lexeme word);

#endif