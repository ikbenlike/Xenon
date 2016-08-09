/*
    CXenon VM v0.0.2
*/

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "parser.h"
#include "./mpc/mpc.h"

int parse(char* file_to_parse){
    mpc_parser_t* Ident       = mpc_new("ident");
    mpc_parser_t* Number      = mpc_new("number");
    mpc_parser_t* Character   = mpc_new("character");
    mpc_parser_t* String      = mpc_new("string");
    mpc_parser_t* Factor      = mpc_new("factor");
    mpc_parser_t* Term        = mpc_new("term");
    mpc_parser_t* Lexp        = mpc_new("lexp");
    mpc_parser_t* Stmt        = mpc_new("stmt");
    mpc_parser_t* Exp         = mpc_new("exp");
    mpc_parser_t* Typeident   = mpc_new("typeident");
    mpc_parser_t* Decls       = mpc_new("decls");
    mpc_parser_t* Args        = mpc_new("args");
    mpc_parser_t* Body        = mpc_new("body");
    mpc_parser_t* Procedure   = mpc_new("procedure");
    mpc_parser_t* Main        = mpc_new("main");
    mpc_parser_t* Includes    = mpc_new("includes");
    mpc_parser_t* Xenon       = mpc_new("xenon");

    mpc_err_t* err = mpca_lang(MPCA_LANG_DEFAULT,
        //" ident     : /[a-zA-Z_][a-zA-Z0-9_] ;                                                   \n"
        //" number    : /[0-9]+/ ;                                                                   \n"
        //" character : '.' ;                                                                        \n"
        //" string    : /\"(\\\\.|[^\"])*\"/ ;                                                       \n"
        //"                                                                                          \n"
        //" factor    : '(' <lexp> ')'                                                               \n"
        //"           | <number>                                                                     \n"
        //"           | <character>                                                                  \n"
        //"           | <string>                                                                     \n"
        //"           | <ident> '(' <lexp>? (',' <lexp>)* ')'                                        \n"
        //"           | <ident> ;                                                                    \n"
        //"                                                                                          \n"
        //" term      : <factor> (('*' | '/' | '%') <factor> )* ;                                    \n"
        //" lexp      : <term> (('+' | '-') <term>)* ;                                               \n"
        //" stmt      : '{' <stmt>* '}'                                                              \n"
        //"           | \"while\" '(' <exp> ')' <stmt>                                               \n"
        //"           | \"if\" '(' <exp> ')' <stmt>                                                  \n"
        //"           | <ident> '=' <lexp> ';'                                                       \n"
        //"           | \"print\" '(' <lexp>? ')' ';'                                                \n"
        //"           | \"return\" <lexp>? ';'                                                       \n"
        //"           | <ident> '(' <ident>? (',' <ident>)* ')' ';' ;                                \n"
        //"                                                                                          \n"
        //" exp       : <lexp> '>' <lexp>                                                            \n"
        //"           | <lexp> '<' <lexp>                                                            \n"
        //"           | <lexp> \">=\" <lexp>                                                         \n"
        //"           | <lexp> \"<=\" <lexp>                                                         \n"
        //"           | <lexp> \"!=\" <lexp>                                                         \n"
        //"           | <lexp> \"==\" <lexp> ;                                                       \n"
        //"                                                                                          \n"
        //" typeident : (\"int\" | \"char\" | \"string\" | \"bool\") <ident> ;                       \n"
        //" decls     : (<typeident> ';')* ;                                                         \n"
        //" args      : <typeident>? (',' <typeident>)* ;                                            \n"
        //" body      : '{' <decls> <stmt>* '}' ;                                                    \n"
        //" procedure : (\"int\" | \"char\" | \"string\" | \"bool\") <ident> '(' <args> ')' <body> ; \n"
        //" main      : <typeident> \"main\" '(' ')' <body> ;                                        \n"
        //" use       : (\"use\" <string>)* ;                                                        \n"
        //" xenon     : /^/ <use> <decls> <procedure>* <main>* /$/ ;                                 \n",
        " ident     : /[a-zA-Z_][a-zA-Z0-9_] ;                           \n"
        " number    : /[0-9]+/ ;                                           \n"
        " character : /'.'/ ;                                              \n"
        " string    : /\"(\\\\.|[^\"])*\"/ ;                               \n"
        "                                                                  \n"
        " factor    : '(' <lexp> ')'                                       \n"
        "           | <number>                                             \n"
        "           | <character>                                          \n"
        "           | <string>                                             \n"
        "           | <ident> '(' <lexp>? (',' <lexp>)* ')'                \n"
        "           | <ident> ;                                            \n"
        "                                                                  \n"
        " term      : <factor> (('*' | '/' | '%') <factor>)* ;             \n"
        " lexp      : <term> (('+' | '-') <term>)* ;                       \n"
        "                                                                  \n"
        " stmt      : '{' <stmt>* '}'                                      \n"
        "           | \"while\" '(' <exp> ')' <stmt>                       \n"
        "           | \"if\"    '(' <exp> ')' <stmt>                       \n"
        "           | <ident> '=' <lexp> ';'                               \n"
        "           | \"print\" '(' <lexp>? ')' ';'                        \n"
        "           | \"return\" <lexp>? ';'                               \n"
        "           | <ident> '(' <ident>? (',' <ident>)* ')' ';' ;        \n"
        "                                                                  \n"
        " exp       : <lexp> '>' <lexp>                                    \n"
        "           | <lexp> '<' <lexp>                                    \n"
        "           | <lexp> \">=\" <lexp>                                 \n"
        "           | <lexp> \"<=\" <lexp>                                 \n"
        "           | <lexp> \"!=\" <lexp>                                 \n"
        "           | <lexp> \"==\" <lexp> ;                               \n"
        "                                                                  \n"
        " typeident : (\"int\" | \"char\") <ident> ;                       \n"
        " decls     : (<typeident> ';')* ;                                 \n"
        " args      : <typeident>? (',' <typeident>)* ;                    \n"
        " body      : '{' <decls> <stmt>* '}' ;                            \n"
        " procedure : (\"int\" | \"char\") <ident> '(' <args> ')' <body> ; \n"
        " main      : \"main\" '(' ')' <body> ;                            \n"
        " includes  : (\"#include\" <string>)* ;                           \n"
        " xenon     : /^/ <includes> <decls> <procedure>* <main> /$/ ;     \n",
        Ident, Number, Character, String, Factor, Term, Lexp, Stmt, Exp, Typeident, Decls, Args, Body,
        Procedure, Main, Includes, Xenon, NULL);

    if (err != NULL){
        mpc_err_print(err);
        mpc_err_delete(err);
        exit(1);
    }

    mpc_result_t r;
    if(mpc_parse_contents(file_to_parse, Xenon, &r)) {
        mpc_ast_print(r.output);
        mpc_ast_delete(r.output);
    } else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }

    mpc_cleanup(17, Ident, Number, Character, String, Factor, Term, Lexp, Stmt, Exp, Typeident, Decls, Args, Body,
                Procedure, Main, Includes, Xenon);

    return 0;

}*/

#include "mpc/mpc.h"

int main(int argc, char **argv) {

  mpc_parser_t* Ident     = mpc_new("ident");
  mpc_parser_t* Number    = mpc_new("number");
  mpc_parser_t* Character = mpc_new("character");
  mpc_parser_t* String    = mpc_new("string");
  mpc_parser_t* Factor    = mpc_new("factor");
  mpc_parser_t* Term      = mpc_new("term");
  mpc_parser_t* Lexp      = mpc_new("lexp");
  mpc_parser_t* Stmt      = mpc_new("stmt");
  mpc_parser_t* Exp       = mpc_new("exp");
  mpc_parser_t* Typeident = mpc_new("typeident");
  mpc_parser_t* Decls     = mpc_new("decls");
  mpc_parser_t* Args      = mpc_new("args");
  mpc_parser_t* Body      = mpc_new("body");
  mpc_parser_t* Procedure = mpc_new("procedure");
  mpc_parser_t* Use       = mpc_new("use");
  mpc_parser_t* Xenon     = mpc_new("xenon");

  mpc_err_t* err = mpca_lang(MPCA_LANG_DEFAULT,
    " ident     : /[a-zA-Z_][a-zA-Z0-9_]*/ ;                           \n"
    " number    : /[0-9]+/ ;                                           \n"
    " character : /'.' | \".\"/ ;                                              \n"
    " string    : /\"(\\\\.|[^\"])*\"/ ;                               \n"
    "                                                                  \n"
    " factor    : '(' <lexp> ')'                                       \n"
    "           | <number>                                             \n"
    "           | <character>                                          \n"
    "           | <string>                                             \n"
    "           | <ident> '(' <lexp>? (',' <lexp>)* ')'                \n"
    "           | <ident> ;                                            \n"
    "                                                                  \n"
    " term      : <factor> (('*' | '/' | '%') <factor>)* ;             \n"
    " lexp      : <term> (('+' | '-') <term>)* ;                       \n"
    "                                                                  \n"
    " stmt      : '{' <stmt>* '}'                                      \n"
    "           | \"while\" '(' <exp> ')' <stmt>                       \n"
    "           | \"if\"    '(' <exp> ')' <stmt>                       \n"
    "           | <ident> '=' <lexp> ';'                               \n"
    "           | \"print\" '(' <lexp>? ')' ';'                        \n"
    "           | \"return\" <lexp>? ';'                               \n"
    "           | <ident> '(' <ident>? (',' <ident>)* ')' ';' ;        \n"
    "                                                                  \n"
    " exp       : <lexp> '>' <lexp>                                    \n"
    "           | <lexp> '<' <lexp>                                    \n"
    "           | <lexp> \">=\" <lexp>                                 \n"
    "           | <lexp> \"<=\" <lexp>                                 \n"
    "           | <lexp> \"!=\" <lexp>                                 \n"
    "           | <lexp> \"==\" <lexp> ;                               \n"
    "                                                                  \n"
    " typeident : (\"int\" | \"char\" | \"str\" | \"bool\") <ident> ;  \n"
    " decls     : (<typeident> ';')* ;                                 \n"
    " args      : <typeident>? (',' <typeident>)* ;                    \n"
    " body      : '{' <decls> <stmt>* '}' ;                                                 \n"
    " procedure : (\"int\" | \"char\" | \"str\" | \"bool\") <ident> '(' <args> ')' <body> ; \n"
    " use       : (\"use\" <string>)* ;                                \n"
    " xenon     : /^/ <use> <decls> <procedure>* /$/ ; \n",
    Ident, Number, Character, String, Factor, Term, Lexp, Stmt, Exp,
    Typeident, Decls, Args, Body, Procedure, Use, Xenon, NULL);

  if (err != NULL) {
    mpc_err_print(err);
    mpc_err_delete(err);
    exit(1);
  }

  if (argc > 1) {

    mpc_result_t r;
    if (mpc_parse_contents(argv[1], Xenon, &r)) {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

  } else {

    mpc_result_t r;
    if (mpc_parse_pipe("<stdin>", stdin, Xenon, &r)) {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

  }

  mpc_cleanup(16, Ident, Number, Character, String, Factor, Term, Lexp, Stmt, Exp,
                  Typeident, Decls, Args, Body, Procedure, Use, Xenon);

  return 0;

}
