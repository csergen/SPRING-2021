#ifndef PARSER_ERROR_H
#define PARSER_ERROR_H

typedef enum _error
{
    UNDEFINED_REFERENCE_MAIN,
    SYNTAX_ERROR,
    EXPECTED,
    OUT_OF_SCOPE,
    UNEXPECTED_DEFINITION,
    UNEXPECTED_CHARACTER,
    UNEXPECTED_ASSIGN_OPERATOR,
    MISSING,
    INVALID
} Error;

void error(Error e)
{
    char *s;

    switch (e)
    {
        case UNDEFINED_REFERENCE_MAIN:
            s = "undefined reference to main";
            break;
        case SYNTAX_ERROR:
            s = "syntax error";
            break;
        case EXPECTED:
            s = "expected character";
            break;
        case OUT_OF_SCOPE:
            s = "out of scope";
            break;
        case UNEXPECTED_DEFINITION:
            s = "unexpected definition";
            break;
        case UNEXPECTED_CHARACTER:
            s = "unexpected character";
            break;
        case UNEXPECTED_ASSIGN_OPERATOR:
            s = "unexpected assign operator";
            break;
        case MISSING:
            s = "missing character";
            break;
        case INVALID:
            s = "invalid";
            break;
    }

    printf(RED"\n\n[Out]: Oops! Something went wrong '%s' before ~~~%s\n%s\n^\n\n" RESET, s, s_current_lexeme, s_current_lexeme);
    exit(true);
}

#endif //PARSER_ERROR_H
