// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "parser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.tab.hh"

// User implementation prologue.

#line 51 "parser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 21 "parser.yy" // lalr1.cc:413

    #include <iostream>
    #include <cstdlib>
    #include <fstream>

    #include "../Brain.hpp"

#undef yylex
#define yylex scanner.yylex

#line 64 "parser.tab.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.yy" // lalr1.cc:479
namespace cpsl {
#line 150 "parser.tab.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Scanner& scanner_yyarg, Brain& brain_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      brain (brain_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 59: // CHR_CONST
        value.copy< char > (other.value);
        break;

      case 108: // whileExpr
      case 123: // expression
        value.copy< cpsl::Expression > (other.value);
        break;

      case 112: // forHdr
      case 113: // forBegin
        value.copy< cpsl::ForHeaderInfo > (other.value);
        break;

      case 67: // constDecl
      case 95: // assignment
      case 97: // ifHdr
      case 98: // ifKey
      case 102: // elseIfStatement
      case 103: // elseIfHdr
      case 106: // whileHdr
      case 107: // whileKey
      case 110: // repeatHdr
        value.copy< int > (other.value);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 114: // optTo
      case 125: // lvalue
        value.copy< std::string > (other.value);
        break;

      case 121: // optExpressionList
      case 122: // expressionList
        value.copy< std::vector<cpsl::Expression> > (other.value);
        break;

      case 100: // optElseIfStatements
      case 101: // elseIfStatements
        value.copy< std::vector<int> > (other.value);
        break;

      case 88: // identifierList
      case 124: // lvalueList
        value.copy< std::vector<std::string> > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 59: // CHR_CONST
        value.copy< char > (v);
        break;

      case 108: // whileExpr
      case 123: // expression
        value.copy< cpsl::Expression > (v);
        break;

      case 112: // forHdr
      case 113: // forBegin
        value.copy< cpsl::ForHeaderInfo > (v);
        break;

      case 67: // constDecl
      case 95: // assignment
      case 97: // ifHdr
      case 98: // ifKey
      case 102: // elseIfStatement
      case 103: // elseIfHdr
      case 106: // whileHdr
      case 107: // whileKey
      case 110: // repeatHdr
        value.copy< int > (v);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 114: // optTo
      case 125: // lvalue
        value.copy< std::string > (v);
        break;

      case 121: // optExpressionList
      case 122: // expressionList
        value.copy< std::vector<cpsl::Expression> > (v);
        break;

      case 100: // optElseIfStatements
      case 101: // elseIfStatements
        value.copy< std::vector<int> > (v);
        break;

      case 88: // identifierList
      case 124: // lvalueList
        value.copy< std::vector<std::string> > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const char v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const cpsl::Expression v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const cpsl::ForHeaderInfo v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<cpsl::Expression> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<int> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::string> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 59: // CHR_CONST
        value.template destroy< char > ();
        break;

      case 108: // whileExpr
      case 123: // expression
        value.template destroy< cpsl::Expression > ();
        break;

      case 112: // forHdr
      case 113: // forBegin
        value.template destroy< cpsl::ForHeaderInfo > ();
        break;

      case 67: // constDecl
      case 95: // assignment
      case 97: // ifHdr
      case 98: // ifKey
      case 102: // elseIfStatement
      case 103: // elseIfHdr
      case 106: // whileHdr
      case 107: // whileKey
      case 110: // repeatHdr
        value.template destroy< int > ();
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 114: // optTo
      case 125: // lvalue
        value.template destroy< std::string > ();
        break;

      case 121: // optExpressionList
      case 122: // expressionList
        value.template destroy< std::vector<cpsl::Expression> > ();
        break;

      case 100: // optElseIfStatements
      case 101: // elseIfStatements
        value.template destroy< std::vector<int> > ();
        break;

      case 88: // identifierList
      case 124: // lvalueList
        value.template destroy< std::vector<std::string> > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 59: // CHR_CONST
        value.move< char > (s.value);
        break;

      case 108: // whileExpr
      case 123: // expression
        value.move< cpsl::Expression > (s.value);
        break;

      case 112: // forHdr
      case 113: // forBegin
        value.move< cpsl::ForHeaderInfo > (s.value);
        break;

      case 67: // constDecl
      case 95: // assignment
      case 97: // ifHdr
      case 98: // ifKey
      case 102: // elseIfStatement
      case 103: // elseIfHdr
      case 106: // whileHdr
      case 107: // whileKey
      case 110: // repeatHdr
        value.move< int > (s.value);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 114: // optTo
      case 125: // lvalue
        value.move< std::string > (s.value);
        break;

      case 121: // optExpressionList
      case 122: // expressionList
        value.move< std::vector<cpsl::Expression> > (s.value);
        break;

      case 100: // optElseIfStatements
      case 101: // elseIfStatements
        value.move< std::vector<int> > (s.value);
        break;

      case 88: // identifierList
      case 124: // lvalueList
        value.move< std::vector<std::string> > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_ARRAY_KEY (const location_type& l)
  {
    return symbol_type (token::ARRAY_KEY, l);
  }

  Parser::symbol_type
  Parser::make_BEGIN_KEY (const location_type& l)
  {
    return symbol_type (token::BEGIN_KEY, l);
  }

  Parser::symbol_type
  Parser::make_CHR_KEY (const location_type& l)
  {
    return symbol_type (token::CHR_KEY, l);
  }

  Parser::symbol_type
  Parser::make_CONST_KEY (const location_type& l)
  {
    return symbol_type (token::CONST_KEY, l);
  }

  Parser::symbol_type
  Parser::make_DO_KEY (const location_type& l)
  {
    return symbol_type (token::DO_KEY, l);
  }

  Parser::symbol_type
  Parser::make_DOWN_TO_KEY (const location_type& l)
  {
    return symbol_type (token::DOWN_TO_KEY, l);
  }

  Parser::symbol_type
  Parser::make_ELSE_KEY (const location_type& l)
  {
    return symbol_type (token::ELSE_KEY, l);
  }

  Parser::symbol_type
  Parser::make_ELSE_IF_KEY (const location_type& l)
  {
    return symbol_type (token::ELSE_IF_KEY, l);
  }

  Parser::symbol_type
  Parser::make_END_KEY (const location_type& l)
  {
    return symbol_type (token::END_KEY, l);
  }

  Parser::symbol_type
  Parser::make_FOR_KEY (const location_type& l)
  {
    return symbol_type (token::FOR_KEY, l);
  }

  Parser::symbol_type
  Parser::make_FORWARD_KEY (const location_type& l)
  {
    return symbol_type (token::FORWARD_KEY, l);
  }

  Parser::symbol_type
  Parser::make_FUNCTION_KEY (const location_type& l)
  {
    return symbol_type (token::FUNCTION_KEY, l);
  }

  Parser::symbol_type
  Parser::make_IF_KEY (const location_type& l)
  {
    return symbol_type (token::IF_KEY, l);
  }

  Parser::symbol_type
  Parser::make_OF_KEY (const location_type& l)
  {
    return symbol_type (token::OF_KEY, l);
  }

  Parser::symbol_type
  Parser::make_ORD_KEY (const location_type& l)
  {
    return symbol_type (token::ORD_KEY, l);
  }

  Parser::symbol_type
  Parser::make_PRED_KEY (const location_type& l)
  {
    return symbol_type (token::PRED_KEY, l);
  }

  Parser::symbol_type
  Parser::make_PROCEDURE_KEY (const location_type& l)
  {
    return symbol_type (token::PROCEDURE_KEY, l);
  }

  Parser::symbol_type
  Parser::make_READ_KEY (const location_type& l)
  {
    return symbol_type (token::READ_KEY, l);
  }

  Parser::symbol_type
  Parser::make_RECORD_KEY (const location_type& l)
  {
    return symbol_type (token::RECORD_KEY, l);
  }

  Parser::symbol_type
  Parser::make_REF_KEY (const location_type& l)
  {
    return symbol_type (token::REF_KEY, l);
  }

  Parser::symbol_type
  Parser::make_REPEAT_KEY (const location_type& l)
  {
    return symbol_type (token::REPEAT_KEY, l);
  }

  Parser::symbol_type
  Parser::make_RETURN_KEY (const location_type& l)
  {
    return symbol_type (token::RETURN_KEY, l);
  }

  Parser::symbol_type
  Parser::make_STOP_KEY (const location_type& l)
  {
    return symbol_type (token::STOP_KEY, l);
  }

  Parser::symbol_type
  Parser::make_SUCC_KEY (const location_type& l)
  {
    return symbol_type (token::SUCC_KEY, l);
  }

  Parser::symbol_type
  Parser::make_THEN_KEY (const location_type& l)
  {
    return symbol_type (token::THEN_KEY, l);
  }

  Parser::symbol_type
  Parser::make_TO_KEY (const location_type& l)
  {
    return symbol_type (token::TO_KEY, l);
  }

  Parser::symbol_type
  Parser::make_TYPE_KEY (const location_type& l)
  {
    return symbol_type (token::TYPE_KEY, l);
  }

  Parser::symbol_type
  Parser::make_UNTIL_KEY (const location_type& l)
  {
    return symbol_type (token::UNTIL_KEY, l);
  }

  Parser::symbol_type
  Parser::make_VAR_KEY (const location_type& l)
  {
    return symbol_type (token::VAR_KEY, l);
  }

  Parser::symbol_type
  Parser::make_WHILE_KEY (const location_type& l)
  {
    return symbol_type (token::WHILE_KEY, l);
  }

  Parser::symbol_type
  Parser::make_WRITE_KEY (const location_type& l)
  {
    return symbol_type (token::WRITE_KEY, l);
  }

  Parser::symbol_type
  Parser::make_AND_OP (const location_type& l)
  {
    return symbol_type (token::AND_OP, l);
  }

  Parser::symbol_type
  Parser::make_ASSIGN_OP (const location_type& l)
  {
    return symbol_type (token::ASSIGN_OP, l);
  }

  Parser::symbol_type
  Parser::make_DIV_OP (const location_type& l)
  {
    return symbol_type (token::DIV_OP, l);
  }

  Parser::symbol_type
  Parser::make_EQ_OP (const location_type& l)
  {
    return symbol_type (token::EQ_OP, l);
  }

  Parser::symbol_type
  Parser::make_GT_OP (const location_type& l)
  {
    return symbol_type (token::GT_OP, l);
  }

  Parser::symbol_type
  Parser::make_GT_EQ_OP (const location_type& l)
  {
    return symbol_type (token::GT_EQ_OP, l);
  }

  Parser::symbol_type
  Parser::make_LT_OP (const location_type& l)
  {
    return symbol_type (token::LT_OP, l);
  }

  Parser::symbol_type
  Parser::make_LT_EQ_OP (const location_type& l)
  {
    return symbol_type (token::LT_EQ_OP, l);
  }

  Parser::symbol_type
  Parser::make_MINUS_OP (const location_type& l)
  {
    return symbol_type (token::MINUS_OP, l);
  }

  Parser::symbol_type
  Parser::make_MOD_OP (const location_type& l)
  {
    return symbol_type (token::MOD_OP, l);
  }

  Parser::symbol_type
  Parser::make_MULT_OP (const location_type& l)
  {
    return symbol_type (token::MULT_OP, l);
  }

  Parser::symbol_type
  Parser::make_NOT_EQ_OP (const location_type& l)
  {
    return symbol_type (token::NOT_EQ_OP, l);
  }

  Parser::symbol_type
  Parser::make_NOT_OP (const location_type& l)
  {
    return symbol_type (token::NOT_OP, l);
  }

  Parser::symbol_type
  Parser::make_OR_OP (const location_type& l)
  {
    return symbol_type (token::OR_OP, l);
  }

  Parser::symbol_type
  Parser::make_PLUS_OP (const location_type& l)
  {
    return symbol_type (token::PLUS_OP, l);
  }

  Parser::symbol_type
  Parser::make_CLOSE_PAR (const location_type& l)
  {
    return symbol_type (token::CLOSE_PAR, l);
  }

  Parser::symbol_type
  Parser::make_CLOSE_SQ (const location_type& l)
  {
    return symbol_type (token::CLOSE_SQ, l);
  }

  Parser::symbol_type
  Parser::make_COL (const location_type& l)
  {
    return symbol_type (token::COL, l);
  }

  Parser::symbol_type
  Parser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::COMMA, l);
  }

  Parser::symbol_type
  Parser::make_DOT (const location_type& l)
  {
    return symbol_type (token::DOT, l);
  }

  Parser::symbol_type
  Parser::make_OPEN_PAR (const location_type& l)
  {
    return symbol_type (token::OPEN_PAR, l);
  }

  Parser::symbol_type
  Parser::make_OPEN_SQ (const location_type& l)
  {
    return symbol_type (token::OPEN_SQ, l);
  }

  Parser::symbol_type
  Parser::make_SEMI_COL (const location_type& l)
  {
    return symbol_type (token::SEMI_COL, l);
  }

  Parser::symbol_type
  Parser::make_IDENTIFIER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::IDENTIFIER, v, l);
  }

  Parser::symbol_type
  Parser::make_INT_CONST (const std::string& v, const location_type& l)
  {
    return symbol_type (token::INT_CONST, v, l);
  }

  Parser::symbol_type
  Parser::make_CHR_CONST (const char& v, const location_type& l)
  {
    return symbol_type (token::CHR_CONST, v, l);
  }

  Parser::symbol_type
  Parser::make_STRING_CONST (const std::string& v, const location_type& l)
  {
    return symbol_type (token::STRING_CONST, v, l);
  }

  Parser::symbol_type
  Parser::make_UMINUS_OP (const location_type& l)
  {
    return symbol_type (token::UMINUS_OP, l);
  }



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 59: // CHR_CONST
        value.move< char > (that.value);
        break;

      case 108: // whileExpr
      case 123: // expression
        value.move< cpsl::Expression > (that.value);
        break;

      case 112: // forHdr
      case 113: // forBegin
        value.move< cpsl::ForHeaderInfo > (that.value);
        break;

      case 67: // constDecl
      case 95: // assignment
      case 97: // ifHdr
      case 98: // ifKey
      case 102: // elseIfStatement
      case 103: // elseIfHdr
      case 106: // whileHdr
      case 107: // whileKey
      case 110: // repeatHdr
        value.move< int > (that.value);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 114: // optTo
      case 125: // lvalue
        value.move< std::string > (that.value);
        break;

      case 121: // optExpressionList
      case 122: // expressionList
        value.move< std::vector<cpsl::Expression> > (that.value);
        break;

      case 100: // optElseIfStatements
      case 101: // elseIfStatements
        value.move< std::vector<int> > (that.value);
        break;

      case 88: // identifierList
      case 124: // lvalueList
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 59: // CHR_CONST
        value.copy< char > (that.value);
        break;

      case 108: // whileExpr
      case 123: // expression
        value.copy< cpsl::Expression > (that.value);
        break;

      case 112: // forHdr
      case 113: // forBegin
        value.copy< cpsl::ForHeaderInfo > (that.value);
        break;

      case 67: // constDecl
      case 95: // assignment
      case 97: // ifHdr
      case 98: // ifKey
      case 102: // elseIfStatement
      case 103: // elseIfHdr
      case 106: // whileHdr
      case 107: // whileKey
      case 110: // repeatHdr
        value.copy< int > (that.value);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 114: // optTo
      case 125: // lvalue
        value.copy< std::string > (that.value);
        break;

      case 121: // optExpressionList
      case 122: // expressionList
        value.copy< std::vector<cpsl::Expression> > (that.value);
        break;

      case 100: // optElseIfStatements
      case 101: // elseIfStatements
        value.copy< std::vector<int> > (that.value);
        break;

      case 88: // identifierList
      case 124: // lvalueList
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 59: // CHR_CONST
        yylhs.value.build< char > ();
        break;

      case 108: // whileExpr
      case 123: // expression
        yylhs.value.build< cpsl::Expression > ();
        break;

      case 112: // forHdr
      case 113: // forBegin
        yylhs.value.build< cpsl::ForHeaderInfo > ();
        break;

      case 67: // constDecl
      case 95: // assignment
      case 97: // ifHdr
      case 98: // ifKey
      case 102: // elseIfStatement
      case 103: // elseIfHdr
      case 106: // whileHdr
      case 107: // whileKey
      case 110: // repeatHdr
        yylhs.value.build< int > ();
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 114: // optTo
      case 125: // lvalue
        yylhs.value.build< std::string > ();
        break;

      case 121: // optExpressionList
      case 122: // expressionList
        yylhs.value.build< std::vector<cpsl::Expression> > ();
        break;

      case 100: // optElseIfStatements
      case 101: // elseIfStatements
        yylhs.value.build< std::vector<int> > ();
        break;

      case 88: // identifierList
      case 124: // lvalueList
        yylhs.value.build< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 8:
#line 129 "parser.yy" // lalr1.cc:859
    { brain.statements.ConstDeclaration(yystack_[3].value.as< std::string > (), yystack_[1].value.as< cpsl::Expression > ()); }
#line 1447 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 151 "parser.yy" // lalr1.cc:859
    {  }
#line 1453 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 152 "parser.yy" // lalr1.cc:859
    { }
#line 1459 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 155 "parser.yy" // lalr1.cc:859
    { }
#line 1465 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 156 "parser.yy" // lalr1.cc:859
    { }
#line 1471 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 159 "parser.yy" // lalr1.cc:859
    {  }
#line 1477 "parser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 184 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1483 "parser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 185 "parser.yy" // lalr1.cc:859
    { }
#line 1489 "parser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 186 "parser.yy" // lalr1.cc:859
    { }
#line 1495 "parser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 189 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1501 "parser.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 192 "parser.yy" // lalr1.cc:859
    { }
#line 1507 "parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 201 "parser.yy" // lalr1.cc:859
    { }
#line 1513 "parser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 204 "parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > (); }
#line 1519 "parser.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 205 "parser.yy" // lalr1.cc:859
    { std::vector<std::string> list; list.push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< std::vector<std::string> > () = list; }
#line 1525 "parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 208 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1531 "parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 219 "parser.yy" // lalr1.cc:859
    { brain.statements.VariableDeclaration(yystack_[3].value.as< std::vector<std::string> > (), yystack_[1].value.as< std::string > ()); }
#line 1537 "parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 239 "parser.yy" // lalr1.cc:859
    { brain.statements.Assignment(yystack_[2].value.as< std::string > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1543 "parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 242 "parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<int> > ().push_back(yystack_[3].value.as< int > ()); brain.statements.IfEnd(yystack_[2].value.as< std::vector<int> > ()); }
#line 1549 "parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 245 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[1].value.as< int > (); brain.statements.IfHeader(yystack_[1].value.as< int > ()); }
#line 1555 "parser.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 248 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = brain.statements.IfBegin(yystack_[0].value.as< cpsl::Expression > ()); }
#line 1561 "parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 254 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<int> > () = yystack_[0].value.as< std::vector<int> > (); }
#line 1567 "parser.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 255 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<int> > () = std::vector<int>(0); }
#line 1573 "parser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 258 "parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ()); yylhs.value.as< std::vector<int> > () = yystack_[1].value.as< std::vector<int> > (); }
#line 1579 "parser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 259 "parser.yy" // lalr1.cc:859
    { std::vector<int> list; list.push_back(yystack_[0].value.as< int > ()); yylhs.value.as< std::vector<int> > () = list; }
#line 1585 "parser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 262 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[1].value.as< int > (); brain.statements.IfHeader(yystack_[1].value.as< int > ()); }
#line 1591 "parser.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 265 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = brain.statements.IfBegin(yystack_[0].value.as< cpsl::Expression > ()); }
#line 1597 "parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 272 "parser.yy" // lalr1.cc:859
    { brain.statements.WhileEnd(yystack_[2].value.as< int > ()); }
#line 1603 "parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 275 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[2].value.as< int > (); brain.statements.WhileHeader(yystack_[2].value.as< int > (), yystack_[1].value.as< cpsl::Expression > ()); }
#line 1609 "parser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 278 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = brain.statements.WhileBegin(); }
#line 1615 "parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 281 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = yystack_[0].value.as< cpsl::Expression > (); }
#line 1621 "parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 284 "parser.yy" // lalr1.cc:859
    { brain.statements.RepeatEnd(yystack_[3].value.as< int > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1627 "parser.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 287 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = brain.statements.RepeatBegin(); }
#line 1633 "parser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 290 "parser.yy" // lalr1.cc:859
    { brain.statements.ForEnd(yystack_[3].value.as< cpsl::ForHeaderInfo > ()); }
#line 1639 "parser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 293 "parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< cpsl::ForHeaderInfo > ().optTo = yystack_[1].value.as< std::string > (); brain.statements.ForHeader(yystack_[2].value.as< cpsl::ForHeaderInfo > (), yystack_[0].value.as< cpsl::Expression > ()); yylhs.value.as< cpsl::ForHeaderInfo > () = yystack_[2].value.as< cpsl::ForHeaderInfo > (); }
#line 1645 "parser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 296 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::ForHeaderInfo > () = brain.statements.ForBegin(yystack_[2].value.as< std::string > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1651 "parser.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 299 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "1"; }
#line 1657 "parser.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 300 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "-1"; }
#line 1663 "parser.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 303 "parser.yy" // lalr1.cc:859
    { brain.statements.StopStatement(); }
#line 1669 "parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 310 "parser.yy" // lalr1.cc:859
    { brain.statements.ReadStatement(yystack_[1].value.as< std::vector<std::string> > ()); }
#line 1675 "parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 313 "parser.yy" // lalr1.cc:859
    { brain.statements.WriteStatement(yystack_[1].value.as< std::vector<cpsl::Expression> > ()); }
#line 1681 "parser.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 322 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<cpsl::Expression> > () = yystack_[0].value.as< std::vector<cpsl::Expression> > ();}
#line 1687 "parser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 323 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<cpsl::Expression> > () = std::vector<cpsl::Expression>(); }
#line 1693 "parser.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 326 "parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<cpsl::Expression> > ().push_back(yystack_[0].value.as< cpsl::Expression > ()); yylhs.value.as< std::vector<cpsl::Expression> > () = yystack_[2].value.as< std::vector<cpsl::Expression> > ();}
#line 1699 "parser.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 327 "parser.yy" // lalr1.cc:859
    { std::vector<cpsl::Expression> list; list.push_back(yystack_[0].value.as< cpsl::Expression > ()); yylhs.value.as< std::vector<cpsl::Expression> > () = list;}
#line 1705 "parser.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 330 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.OrExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1711 "parser.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 331 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.AndExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1717 "parser.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 332 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.EqExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1723 "parser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 333 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.NotEqExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1729 "parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 334 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.LtEqExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1735 "parser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 335 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.GtEqExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1741 "parser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 336 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.LtExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1747 "parser.tab.cc" // lalr1.cc:859
    break;

  case 105:
#line 337 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.GtExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1753 "parser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 338 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.PlusExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1759 "parser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 339 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.MinusExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1765 "parser.tab.cc" // lalr1.cc:859
    break;

  case 108:
#line 340 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.MultExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1771 "parser.tab.cc" // lalr1.cc:859
    break;

  case 109:
#line 341 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.DivExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1777 "parser.tab.cc" // lalr1.cc:859
    break;

  case 110:
#line 342 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.ModExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1783 "parser.tab.cc" // lalr1.cc:859
    break;

  case 111:
#line 343 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.NotExpression(yystack_[0].value.as< cpsl::Expression > ()); }
#line 1789 "parser.tab.cc" // lalr1.cc:859
    break;

  case 112:
#line 344 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.UMinusExpression(yystack_[0].value.as< cpsl::Expression > ()); }
#line 1795 "parser.tab.cc" // lalr1.cc:859
    break;

  case 113:
#line 345 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = yystack_[1].value.as< cpsl::Expression > (); }
#line 1801 "parser.tab.cc" // lalr1.cc:859
    break;

  case 114:
#line 346 "parser.yy" // lalr1.cc:859
    {  }
#line 1807 "parser.tab.cc" // lalr1.cc:859
    break;

  case 115:
#line 347 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.ChrExpression(yystack_[1].value.as< cpsl::Expression > ()); }
#line 1813 "parser.tab.cc" // lalr1.cc:859
    break;

  case 116:
#line 348 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.OrdExpression(yystack_[1].value.as< cpsl::Expression > ()); }
#line 1819 "parser.tab.cc" // lalr1.cc:859
    break;

  case 117:
#line 349 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.PredExpression(yystack_[1].value.as< cpsl::Expression > ()); }
#line 1825 "parser.tab.cc" // lalr1.cc:859
    break;

  case 118:
#line 350 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.SuccExpression(yystack_[1].value.as< cpsl::Expression > ()); }
#line 1831 "parser.tab.cc" // lalr1.cc:859
    break;

  case 119:
#line 351 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.IntConstant(yystack_[0].value.as< std::string > ()); }
#line 1837 "parser.tab.cc" // lalr1.cc:859
    break;

  case 120:
#line 352 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.CharConstant(yystack_[0].value.as< char > ()); }
#line 1843 "parser.tab.cc" // lalr1.cc:859
    break;

  case 121:
#line 353 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.addString(yystack_[0].value.as< std::string > ()); }
#line 1849 "parser.tab.cc" // lalr1.cc:859
    break;

  case 122:
#line 354 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.statements.LoadVariable(yystack_[0].value.as< std::string > ()); }
#line 1855 "parser.tab.cc" // lalr1.cc:859
    break;

  case 123:
#line 357 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > (); }
#line 1861 "parser.tab.cc" // lalr1.cc:859
    break;

  case 124:
#line 358 "parser.yy" // lalr1.cc:859
    { std::vector<std::string> list; list.push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< std::vector<std::string> > () = list;}
#line 1867 "parser.tab.cc" // lalr1.cc:859
    break;

  case 125:
#line 361 "parser.yy" // lalr1.cc:859
    { }
#line 1873 "parser.tab.cc" // lalr1.cc:859
    break;

  case 126:
#line 362 "parser.yy" // lalr1.cc:859
    { }
#line 1879 "parser.tab.cc" // lalr1.cc:859
    break;

  case 127:
#line 363 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();}
#line 1885 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1889 "parser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int Parser::yypact_ninf_ = -184;

  const signed char Parser::yytable_ninf_ = -26;

  const short int
  Parser::yypact_[] =
  {
      19,   -44,    39,    38,    25,  -184,   -44,  -184,    27,  -184,
     136,     3,   -44,    42,  -184,   116,   -44,   116,    24,  -184,
     116,  -184,  -184,    41,    43,    -5,  -184,  -184,  -184,    83,
      69,  -184,   136,   116,  -184,   136,  -184,    91,    15,  -184,
    -184,  -184,  -184,  -184,  -184,   -15,  -184,   -44,  -184,    67,
     -44,  -184,    51,    52,    53,    70,   116,   116,   116,  -184,
    -184,  -184,    71,   158,   -41,    92,   333,   -44,   333,   116,
     116,  -184,   136,   116,   117,    83,  -184,    69,   136,  -184,
       5,   123,   333,   -20,   136,  -184,  -184,   116,   116,   -44,
     116,  -184,     0,    17,  -184,   -44,  -184,    31,   116,   116,
     116,   116,  -184,   191,   253,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,  -184,
     116,  -184,   -25,   -41,   -23,   333,    82,    80,  -184,   333,
     136,   124,  -184,  -184,    81,  -184,  -184,   116,     7,   333,
     333,  -184,   223,    85,  -184,    88,  -184,  -184,  -184,  -184,
       0,   -44,  -184,   -44,   -44,  -184,    49,  -184,    68,   269,
     285,   301,   317,  -184,    87,   191,  -184,   346,   346,   346,
     346,   346,    36,  -184,  -184,   346,   191,    36,   333,  -184,
     -44,  -184,   116,  -184,    81,  -184,   333,  -184,  -184,   116,
      -9,  -184,    90,  -184,    84,    93,    98,    25,    99,   101,
     107,  -184,  -184,  -184,  -184,  -184,   -41,   333,   207,  -184,
    -184,    33,  -184,    10,    10,  -184,    42,  -184,  -184,  -184,
     116,     0,  -184,  -184,   115,   109,  -184,   -44,   118,    38,
     238,   110,   120,     6,    35,   121,  -184,   156,  -184,     0,
    -184,     0,  -184,     0,   125,  -184,  -184,  -184
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       5,     0,     0,     0,    29,    44,     4,     7,     0,     1,
      93,     0,     0,    46,     6,     0,     0,     0,     0,    81,
      89,    87,    78,     0,   127,     0,    51,    52,    53,    69,
       0,    54,    93,     0,    55,    93,    56,     0,     0,    57,
      58,    59,    60,    61,    62,     0,     2,    28,    31,     0,
       0,    11,     0,     0,     0,     0,     0,     0,     0,   119,
     120,   121,   127,     0,   122,     0,    66,     0,    88,     0,
      95,    27,    93,     0,    75,    68,    71,     0,    93,    65,
       0,     0,    79,     0,    93,    86,    85,     0,     0,     0,
       0,    30,     0,     0,    43,    45,    48,     3,     0,     0,
       0,     0,   112,   111,     0,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       0,   127,     0,   124,     0,    97,     0,    94,    50,    73,
      93,     0,    70,    72,    67,    76,    77,     0,     0,    83,
      63,   125,     0,     0,    39,     0,    33,    34,    35,    36,
       0,     0,    47,     0,     0,     9,     5,    10,     5,     0,
       0,     0,     0,   113,     0,    99,   109,   100,   105,   103,
     104,   102,   107,   110,   108,   101,    98,   106,    84,    90,
       0,    91,     0,    92,    74,    64,    80,    82,   126,     0,
       0,    32,     0,    42,     0,     0,     0,    29,     0,     0,
       0,   115,   116,   117,   118,   114,   123,    96,     0,    37,
      38,     0,    49,    19,    19,    12,    46,    13,    15,    16,
       0,     0,    24,    23,     0,    18,    21,     0,     0,     0,
       0,     0,     0,    25,     0,     0,    26,     0,    40,     0,
      20,     0,    14,     0,     0,    22,    41,    17
  };

  const short int
  Parser::yypgoto_[] =
  {
    -184,  -184,  -184,   180,  -184,   176,  -184,  -184,  -184,  -184,
    -184,   -29,  -184,   -50,  -184,    28,   -42,    -7,  -184,   141,
     -98,  -184,  -184,  -184,  -184,  -184,  -183,    -1,   -12,  -184,
     112,   -31,   137,  -184,  -184,  -184,  -184,   131,  -184,  -184,
     135,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,   106,
     143,     2,  -184,    -2
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,   197,     6,     7,    97,   155,   156,   157,
     158,   224,   225,   226,   227,   198,    11,    13,    47,    48,
     145,   146,   147,   190,   210,   148,    93,    62,    51,    95,
      96,    25,    26,    27,    28,    29,    30,    79,    74,    75,
      76,    77,   131,    31,    32,    33,    81,    34,    35,    36,
      37,    38,    87,    39,    40,    41,    42,    43,    44,   126,
     127,   125,   122,    64
  };

  const short int
  Parser::yytable_[] =
  {
       8,    80,   209,   143,    83,     8,    71,   211,    45,    24,
     137,    49,    89,     5,    90,    65,   135,    63,   187,    66,
      88,   144,    68,    85,   179,     1,   181,   180,   222,   182,
      45,    24,   222,    45,    24,    82,    72,   223,    89,     9,
      90,   223,    10,    86,   234,   153,    49,   134,     5,    94,
     154,    72,   192,   138,    12,     1,    46,     5,   102,   103,
     104,    72,   196,    72,    15,   123,   121,   -25,   150,   151,
      45,    24,   107,    50,     1,   129,    45,    24,    67,   114,
     115,   199,    45,    24,   221,   151,   241,   151,   141,   139,
     140,   149,   142,    73,    94,    69,    78,    70,    84,   184,
     159,   160,   161,   162,    92,    98,    99,   100,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,    52,   178,   231,   101,   105,   130,   120,    45,    24,
     136,   183,   182,    53,    54,   185,   205,    72,   213,   186,
     189,   244,    55,   245,   191,   246,   212,   214,    16,   149,
     193,    17,   194,   195,   215,   217,    18,   218,    56,    19,
      20,    21,    57,   219,   232,   233,   238,   235,    22,    23,
      58,   239,   243,     5,    59,    60,    61,   242,   206,   121,
       4,   247,    14,   240,   207,   228,   200,   236,    91,    94,
     216,   208,   106,     5,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   229,   117,   118,   152,   133,   128,
     132,   164,   124,     0,   119,     0,     0,     0,     0,     0,
     149,     0,   230,     0,     0,     0,    94,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,     0,   149,   118,
     149,   106,   149,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,   117,   118,     0,   106,   220,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,     0,
     117,   118,   106,   188,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,     0,   117,   118,   106,   237,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,     0,
     117,   118,   163,   106,     0,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,   117,   118,   201,   106,
       0,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     0,   117,   118,   202,   106,     0,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,     0,   117,   118,
     203,   106,     0,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,   117,   118,   204,   106,     0,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,     0,
     117,   118,   107,   -26,   -26,   -26,   -26,   -26,   113,   114,
     115,   -26,     0,     0,   118
  };

  const short int
  Parser::yycheck_[] =
  {
       1,    32,    11,     3,    35,     6,    11,   190,    10,    10,
      30,    12,    53,    57,    55,    16,    11,    15,    11,    17,
      35,    21,    20,     8,    49,     6,    49,    52,    22,    52,
      32,    32,    22,    35,    35,    33,    56,    31,    53,     0,
      55,    31,     4,    28,   227,    14,    47,    78,    57,    50,
      19,    56,   150,    84,    29,     6,    53,    57,    56,    57,
      58,    56,    13,    56,    37,    67,    67,    57,    51,    52,
      72,    72,    36,    31,     6,    73,    78,    78,    54,    43,
      44,    13,    84,    84,    51,    52,    51,    52,    89,    87,
      88,    92,    90,    10,    95,    54,    27,    54,     7,   130,
      98,    99,   100,   101,    37,    54,    54,    54,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,     5,   120,   221,    54,    54,     9,    35,   130,   130,
       7,    49,    52,    17,    18,    11,    49,    56,    54,   137,
      55,   239,    26,   241,    56,   243,    56,    54,    12,   150,
     151,    15,   153,   154,    56,    56,    20,    56,    42,    23,
      24,    25,    46,    56,    49,    56,    56,    49,    32,    33,
      54,    51,    16,    57,    58,    59,    60,    56,   180,   180,
       0,    56,     6,   233,   182,   214,   158,   229,    47,   190,
     197,   189,    34,    57,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,   216,    47,    48,    95,    77,    72,
      75,   105,    69,    -1,    56,    -1,    -1,    -1,    -1,    -1,
     221,    -1,   220,    -1,    -1,    -1,   227,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,   239,    48,
     241,    34,   243,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    -1,    34,    51,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    34,    50,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    34,    50,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    34,    -1,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    34,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    49,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    -1,    48
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     6,    63,    64,    65,    57,    66,    67,    89,     0,
       4,    78,    29,    79,    67,    37,    12,    15,    20,    23,
      24,    25,    32,    33,    89,    93,    94,    95,    96,    97,
      98,   105,   106,   107,   109,   110,   111,   112,   113,   115,
     116,   117,   118,   119,   120,   125,    53,    80,    81,    89,
      31,    90,     5,    17,    18,    26,    42,    46,    54,    58,
      59,    60,    89,   123,   125,    89,   123,    54,   123,    54,
      54,    11,    56,    10,   100,   101,   102,   103,    27,    99,
      93,   108,   123,    93,     7,     8,    28,   114,    35,    53,
      55,    81,    37,    88,    89,    91,    92,    68,    54,    54,
      54,    54,   123,   123,   123,    54,    34,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    47,    48,    56,
      35,    89,   124,   125,   122,   123,   121,   122,    94,   123,
       9,   104,   102,    99,    93,    11,     7,    30,    93,   123,
     123,    89,   123,     3,    21,    82,    83,    84,    87,    89,
      51,    52,    92,    14,    19,    69,    70,    71,    72,   123,
     123,   123,   123,    49,   121,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,    49,
      52,    49,    52,    49,    93,    11,   123,    11,    50,    55,
      85,    56,    82,    89,    89,    89,    13,    65,    77,    13,
      77,    49,    49,    49,    49,    49,   125,   123,   123,    11,
      86,    88,    56,    54,    54,    56,    79,    56,    56,    56,
      51,    51,    22,    31,    73,    74,    75,    76,    73,    90,
     123,    82,    49,    56,    88,    49,    78,    50,    56,    51,
      75,    51,    56,    16,    82,    82,    82,    56
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    62,    63,    64,    65,    65,    66,    66,    67,    68,
      68,    68,    69,    69,    70,    71,    71,    72,    73,    73,
      74,    74,    75,    76,    76,    76,    77,    78,    79,    79,
      80,    80,    81,    82,    82,    82,    83,    84,    85,    85,
      86,    87,    88,    88,    89,    90,    90,    91,    91,    92,
      93,    93,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    95,    96,    97,    98,    99,   100,   100,
     101,   101,   102,   103,   104,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   114,   115,   116,   116,
     117,   118,   119,   120,   121,   121,   122,   122,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   124,   124,   125,   125,   125
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     3,     4,     2,     0,     2,     1,     4,     2,
       2,     0,     3,     3,     6,     3,     3,     8,     1,     0,
       3,     1,     4,     1,     1,     0,     4,     3,     2,     0,
       2,     1,     4,     1,     1,     1,     1,     3,     2,     0,
       4,     8,     3,     1,     1,     2,     0,     2,     1,     4,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     4,     2,     2,     2,     1,     0,
       2,     1,     2,     2,     2,     0,     3,     3,     1,     1,
       4,     1,     4,     3,     4,     1,     1,     1,     2,     1,
       4,     4,     4,     0,     1,     0,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     3,     4,     4,     4,     4,     4,     1,
       1,     1,     1,     3,     1,     3,     4,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "ARRAY_KEY", "BEGIN_KEY", "CHR_KEY",
  "CONST_KEY", "DO_KEY", "DOWN_TO_KEY", "ELSE_KEY", "ELSE_IF_KEY",
  "END_KEY", "FOR_KEY", "FORWARD_KEY", "FUNCTION_KEY", "IF_KEY", "OF_KEY",
  "ORD_KEY", "PRED_KEY", "PROCEDURE_KEY", "READ_KEY", "RECORD_KEY",
  "REF_KEY", "REPEAT_KEY", "RETURN_KEY", "STOP_KEY", "SUCC_KEY",
  "THEN_KEY", "TO_KEY", "TYPE_KEY", "UNTIL_KEY", "VAR_KEY", "WHILE_KEY",
  "WRITE_KEY", "AND_OP", "ASSIGN_OP", "DIV_OP", "EQ_OP", "GT_OP",
  "GT_EQ_OP", "LT_OP", "LT_EQ_OP", "MINUS_OP", "MOD_OP", "MULT_OP",
  "NOT_EQ_OP", "NOT_OP", "OR_OP", "PLUS_OP", "CLOSE_PAR", "CLOSE_SQ",
  "COL", "COMMA", "DOT", "OPEN_PAR", "OPEN_SQ", "SEMI_COL", "IDENTIFIER",
  "INT_CONST", "CHR_CONST", "STRING_CONST", "UMINUS_OP", "$accept",
  "program", "progHead", "optConstDecl", "constDecls", "constDecl",
  "optProcFuncs", "procedureDecl", "procedureSig", "functionDecl",
  "functionSig", "optFormalParameters", "formalParameters",
  "formalParameter", "optVar", "body", "block", "optTypeDecl", "typeDecls",
  "typeDecl", "type", "simpleType", "recordType", "fields", "field",
  "arrayType", "identifierList", "identifier", "optVarDecl", "varDecls",
  "varDecl", "statementList", "statement", "assignment", "ifStatement",
  "ifHdr", "ifKey", "thenStatement", "optElseIfStatements",
  "elseIfStatements", "elseIfStatement", "elseIfHdr", "elseStatement",
  "whileStatement", "whileHdr", "whileKey", "whileExpr", "repeatStatement",
  "repeatHdr", "forStatement", "forHdr", "forBegin", "optTo",
  "stopStatement", "returnStatement", "readStatement", "writeStatement",
  "procedureCall", "nullStatement", "optExpressionList", "expressionList",
  "expression", "lvalueList", "lvalue", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   115,   115,   118,   121,   122,   125,   126,   129,   132,
     133,   134,   137,   138,   141,   144,   145,   148,   151,   152,
     155,   156,   159,   162,   163,   164,   167,   170,   173,   174,
     177,   178,   181,   184,   185,   186,   189,   192,   195,   196,
     198,   201,   204,   205,   208,   211,   212,   215,   216,   219,
     222,   223,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   239,   242,   245,   248,   251,   254,   255,
     258,   259,   262,   265,   268,   269,   272,   275,   278,   281,
     284,   287,   290,   293,   296,   299,   300,   303,   306,   307,
     310,   313,   316,   319,   322,   323,   326,   327,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   357,   358,   361,   362,   363
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
    };
    const unsigned int user_token_number_max_ = 316;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 5 "parser.yy" // lalr1.cc:1167
} // cpsl
#line 2525 "parser.tab.cc" // lalr1.cc:1167
#line 366 "parser.yy" // lalr1.cc:1168


void cpsl::Parser::error(const location_type& l, const std::string& err_message)
{
    std::cerr << "Syntax Error: " << err_message << " at " << l << "\n";
}
