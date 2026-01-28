grammar TyC;

@lexer::header {
#include "../src/lexererr.hpp"
}

options {
    language = Cpp;
}

/* Parser */
program: .EOF;

/* Lexer */

// Whitespace and newline
WS: [ \r\n\t]+ -> skip;

/* Error */
ERROR_CHAR: .;
UNCLOSED_STRING: .;
ILLEGAL_ESCAPE: .;