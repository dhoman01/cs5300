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

    #include "Brain.hpp"

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
      case 115: // expression
        value.copy< cpsl::Expression > (other.value);
        break;

      case 67: // constDecl
      case 95: // assignment
        value.copy< int > (other.value);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 59: // CHR_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 117: // lvalue
        value.copy< std::string > (other.value);
        break;

      case 113: // optExpressionList
      case 114: // expressionList
        value.copy< std::vector<cpsl::Expression> > (other.value);
        break;

      case 88: // identifierList
      case 116: // lvalueList
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
      case 115: // expression
        value.copy< cpsl::Expression > (v);
        break;

      case 67: // constDecl
      case 95: // assignment
        value.copy< int > (v);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 59: // CHR_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 117: // lvalue
        value.copy< std::string > (v);
        break;

      case 113: // optExpressionList
      case 114: // expressionList
        value.copy< std::vector<cpsl::Expression> > (v);
        break;

      case 88: // identifierList
      case 116: // lvalueList
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
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const cpsl::Expression v, const location_type& l)
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
      case 115: // expression
        value.template destroy< cpsl::Expression > ();
        break;

      case 67: // constDecl
      case 95: // assignment
        value.template destroy< int > ();
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 59: // CHR_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 117: // lvalue
        value.template destroy< std::string > ();
        break;

      case 113: // optExpressionList
      case 114: // expressionList
        value.template destroy< std::vector<cpsl::Expression> > ();
        break;

      case 88: // identifierList
      case 116: // lvalueList
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
      case 115: // expression
        value.move< cpsl::Expression > (s.value);
        break;

      case 67: // constDecl
      case 95: // assignment
        value.move< int > (s.value);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 59: // CHR_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 117: // lvalue
        value.move< std::string > (s.value);
        break;

      case 113: // optExpressionList
      case 114: // expressionList
        value.move< std::vector<cpsl::Expression> > (s.value);
        break;

      case 88: // identifierList
      case 116: // lvalueList
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
  Parser::make_CHR_CONST (const std::string& v, const location_type& l)
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
      case 115: // expression
        value.move< cpsl::Expression > (that.value);
        break;

      case 67: // constDecl
      case 95: // assignment
        value.move< int > (that.value);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 59: // CHR_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 117: // lvalue
        value.move< std::string > (that.value);
        break;

      case 113: // optExpressionList
      case 114: // expressionList
        value.move< std::vector<cpsl::Expression> > (that.value);
        break;

      case 88: // identifierList
      case 116: // lvalueList
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
      case 115: // expression
        value.copy< cpsl::Expression > (that.value);
        break;

      case 67: // constDecl
      case 95: // assignment
        value.copy< int > (that.value);
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 59: // CHR_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 117: // lvalue
        value.copy< std::string > (that.value);
        break;

      case 113: // optExpressionList
      case 114: // expressionList
        value.copy< std::vector<cpsl::Expression> > (that.value);
        break;

      case 88: // identifierList
      case 116: // lvalueList
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
      case 115: // expression
        yylhs.value.build< cpsl::Expression > ();
        break;

      case 67: // constDecl
      case 95: // assignment
        yylhs.value.build< int > ();
        break;

      case 57: // IDENTIFIER
      case 58: // INT_CONST
      case 59: // CHR_CONST
      case 60: // STRING_CONST
      case 82: // type
      case 83: // simpleType
      case 89: // identifier
      case 117: // lvalue
        yylhs.value.build< std::string > ();
        break;

      case 113: // optExpressionList
      case 114: // expressionList
        yylhs.value.build< std::vector<cpsl::Expression> > ();
        break;

      case 88: // identifierList
      case 116: // lvalueList
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
#line 127 "parser.yy" // lalr1.cc:859
    { brain.statements.ConstDeclaration(yystack_[3].value.as< std::string > (), yystack_[1].value.as< cpsl::Expression > ()); }
#line 1272 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 149 "parser.yy" // lalr1.cc:859
    {  }
#line 1278 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 150 "parser.yy" // lalr1.cc:859
    { }
#line 1284 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 153 "parser.yy" // lalr1.cc:859
    { }
#line 1290 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 154 "parser.yy" // lalr1.cc:859
    { }
#line 1296 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 157 "parser.yy" // lalr1.cc:859
    {  }
#line 1302 "parser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 182 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1308 "parser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 183 "parser.yy" // lalr1.cc:859
    { }
#line 1314 "parser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 184 "parser.yy" // lalr1.cc:859
    { }
#line 1320 "parser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 187 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1326 "parser.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 190 "parser.yy" // lalr1.cc:859
    { }
#line 1332 "parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 199 "parser.yy" // lalr1.cc:859
    { }
#line 1338 "parser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 202 "parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > (); }
#line 1344 "parser.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 203 "parser.yy" // lalr1.cc:859
    { std::vector<std::string> list; list.push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< std::vector<std::string> > () = list; }
#line 1350 "parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 206 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1356 "parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 217 "parser.yy" // lalr1.cc:859
    { brain.statements.VariableDeclaration(yystack_[3].value.as< std::vector<std::string> > (), yystack_[1].value.as< std::string > ()); }
#line 1362 "parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 237 "parser.yy" // lalr1.cc:859
    { brain.statements.Assignment(yystack_[2].value.as< std::string > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1368 "parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 277 "parser.yy" // lalr1.cc:859
    { brain.statements.StopStatement(); }
#line 1374 "parser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 284 "parser.yy" // lalr1.cc:859
    { brain.statements.ReadStatement(yystack_[1].value.as< std::vector<std::string> > ()); }
#line 1380 "parser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 287 "parser.yy" // lalr1.cc:859
    { brain.statements.WriteStatement(yystack_[1].value.as< std::vector<cpsl::Expression> > ()); }
#line 1386 "parser.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 296 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<cpsl::Expression> > () = yystack_[0].value.as< std::vector<cpsl::Expression> > ();}
#line 1392 "parser.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 297 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<cpsl::Expression> > () = std::vector<cpsl::Expression>(); }
#line 1398 "parser.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 300 "parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<cpsl::Expression> > ().push_back(yystack_[0].value.as< cpsl::Expression > ()); yylhs.value.as< std::vector<cpsl::Expression> > () = yystack_[2].value.as< std::vector<cpsl::Expression> > ();}
#line 1404 "parser.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 301 "parser.yy" // lalr1.cc:859
    { std::vector<cpsl::Expression> list; list.push_back(yystack_[0].value.as< cpsl::Expression > ()); yylhs.value.as< std::vector<cpsl::Expression> > () = list;}
#line 1410 "parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 304 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.OrExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1416 "parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 305 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.AndExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1422 "parser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 306 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.EqExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1428 "parser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 307 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.NotEqExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1434 "parser.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 308 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.LtEqExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1440 "parser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 309 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.GtEqExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1446 "parser.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 310 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.LtExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1452 "parser.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 311 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.GtExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1458 "parser.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 312 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.PlusExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1464 "parser.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 313 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.MinusExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1470 "parser.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 314 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.MultExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1476 "parser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 315 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.DivExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1482 "parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 316 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.ModExpression(yystack_[2].value.as< cpsl::Expression > (), yystack_[0].value.as< cpsl::Expression > ()); }
#line 1488 "parser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 317 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.NotExpression(yystack_[0].value.as< cpsl::Expression > ()); }
#line 1494 "parser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 318 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.UMinusExpression(yystack_[0].value.as< cpsl::Expression > ()); }
#line 1500 "parser.tab.cc" // lalr1.cc:859
    break;

  case 105:
#line 319 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = yystack_[1].value.as< cpsl::Expression > (); }
#line 1506 "parser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 320 "parser.yy" // lalr1.cc:859
    {  }
#line 1512 "parser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 321 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.ChrExpression(yystack_[1].value.as< cpsl::Expression > ()); }
#line 1518 "parser.tab.cc" // lalr1.cc:859
    break;

  case 108:
#line 322 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.OrdExpression(yystack_[1].value.as< cpsl::Expression > ()); }
#line 1524 "parser.tab.cc" // lalr1.cc:859
    break;

  case 109:
#line 323 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.PredExpression(yystack_[1].value.as< cpsl::Expression > ()); }
#line 1530 "parser.tab.cc" // lalr1.cc:859
    break;

  case 110:
#line 324 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.SuccExpression(yystack_[1].value.as< cpsl::Expression > ()); }
#line 1536 "parser.tab.cc" // lalr1.cc:859
    break;

  case 111:
#line 325 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.IntConstant(yystack_[0].value.as< std::string > ()); }
#line 1542 "parser.tab.cc" // lalr1.cc:859
    break;

  case 112:
#line 326 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.expressions.CharConstant(yystack_[0].value.as< std::string > ()); }
#line 1548 "parser.tab.cc" // lalr1.cc:859
    break;

  case 113:
#line 327 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.addString(yystack_[0].value.as< std::string > ()); }
#line 1554 "parser.tab.cc" // lalr1.cc:859
    break;

  case 114:
#line 328 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< cpsl::Expression > () = brain.statements.LoadVariable(yystack_[0].value.as< std::string > ()); }
#line 1560 "parser.tab.cc" // lalr1.cc:859
    break;

  case 115:
#line 331 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > (); }
#line 1566 "parser.tab.cc" // lalr1.cc:859
    break;

  case 116:
#line 332 "parser.yy" // lalr1.cc:859
    { std::vector<std::string> list; list.push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< std::vector<std::string> > () = list;}
#line 1572 "parser.tab.cc" // lalr1.cc:859
    break;

  case 117:
#line 335 "parser.yy" // lalr1.cc:859
    { }
#line 1578 "parser.tab.cc" // lalr1.cc:859
    break;

  case 118:
#line 336 "parser.yy" // lalr1.cc:859
    { }
#line 1584 "parser.tab.cc" // lalr1.cc:859
    break;

  case 119:
#line 337 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();}
#line 1590 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1594 "parser.tab.cc" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -168;

  const signed char Parser::yytable_ninf_ = -26;

  const short int
  Parser::yypact_[] =
  {
       2,   -45,    31,    43,    45,  -168,   -45,  -168,    24,  -168,
       1,    41,   -45,    49,  -168,    33,   -45,    33,    47,     1,
      33,  -168,    33,    50,    59,    -7,  -168,  -168,  -168,  -168,
    -168,  -168,    78,  -168,  -168,  -168,  -168,  -168,  -168,   -25,
    -168,   -45,  -168,    60,   -45,  -168,    77,    84,    95,    98,
      33,    33,    33,  -168,  -168,  -168,   100,   217,   -26,    51,
     240,   -45,   -24,   386,   103,    33,    33,  -168,     1,     1,
      33,   -45,    33,  -168,    -2,    26,  -168,   -45,  -168,    25,
      33,    33,    33,    33,  -168,    79,   306,    33,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    33,    33,
      33,  -168,    33,     1,    89,  -168,     5,   -26,    33,     1,
      17,   386,    65,    80,  -168,     6,   386,  -168,   276,   101,
    -168,   102,  -168,  -168,  -168,  -168,    -2,   -45,  -168,   -45,
     -45,  -168,    29,  -168,    35,   322,   338,   354,   370,  -168,
     108,    79,  -168,   183,   183,   183,   183,   183,    20,  -168,
    -168,   183,    79,    20,   162,   105,    33,   150,    89,  -168,
    -168,   -45,   386,     9,  -168,    33,  -168,  -168,  -168,    33,
      -4,  -168,   106,  -168,   113,   114,   128,    45,   130,   131,
     136,  -168,  -168,  -168,  -168,  -168,  -168,  -168,    33,   240,
       1,   184,  -168,   -26,  -168,   386,   260,  -168,  -168,    30,
    -168,    14,    14,  -168,    49,  -168,  -168,  -168,   386,  -168,
     105,  -168,    33,    -2,  -168,  -168,   145,   141,  -168,   -45,
     159,    43,   291,   155,   163,    -8,    32,   157,  -168,   199,
    -168,    -2,  -168,    -2,  -168,    -2,   160,  -168,  -168,  -168
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       5,     0,     0,     0,    29,    44,     4,     7,     0,     1,
      85,     0,     0,    46,     6,     0,     0,     0,     0,    85,
      81,    79,     0,     0,   119,     0,    51,    52,    53,    54,
      55,    56,     0,    57,    58,    59,    60,    61,    62,     0,
       2,    28,    31,     0,     0,    11,     0,     0,     0,     0,
       0,     0,     0,   111,   112,   113,   119,     0,   114,     0,
       0,     0,     0,    80,     0,     0,    87,    27,    85,    85,
       0,     0,     0,    30,     0,     0,    43,    45,    48,     3,
       0,     0,     0,     0,   104,   103,     0,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     0,    85,    67,   119,     0,   116,     0,    85,
       0,    89,     0,    86,    50,     0,    63,   117,     0,     0,
      39,     0,    33,    34,    35,    36,     0,     0,    47,     0,
       0,     9,     5,    10,     5,     0,     0,     0,     0,   105,
       0,    91,   101,    92,    97,    95,    96,    94,    99,   102,
     100,    93,    90,    98,     0,    65,     0,    72,    66,    69,
      82,     0,    74,     0,    83,     0,    84,    75,   118,     0,
       0,    32,     0,    42,     0,     0,     0,    29,     0,     0,
       0,   107,   108,   109,   110,   106,    78,    77,     0,     0,
      85,     0,    68,   115,    73,    88,     0,    37,    38,     0,
      49,    19,    19,    12,    46,    13,    15,    16,    76,    70,
      71,    64,     0,     0,    24,    23,     0,    18,    21,     0,
       0,     0,     0,     0,     0,    25,     0,     0,    26,     0,
      40,     0,    20,     0,    14,     0,     0,    22,    41,    17
  };

  const short int
  Parser::yypgoto_[] =
  {
    -168,  -168,  -168,   229,  -168,   227,  -168,  -168,  -168,  -168,
    -168,    34,  -168,    10,  -168,   104,    16,    63,  -168,   200,
    -124,  -168,  -168,  -168,  -168,  -168,  -167,    -1,    38,  -168,
     166,     3,   176,  -168,  -168,    56,  -168,  -168,    88,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,   179,   182,    83,  -168,    27
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,   177,     6,     7,    79,   131,   132,   133,
     134,   216,   217,   218,   219,   178,    11,    13,    41,    42,
     121,   122,   123,   170,   198,   124,    75,    56,    45,    77,
      78,    25,    26,    27,    28,   104,   157,   158,   159,   191,
      29,    30,    31,    32,   188,    33,    34,    35,    36,    37,
      38,   112,   113,   111,   106,    58
  };

  const short int
  Parser::yytable_[] =
  {
       8,   119,   172,   199,    67,     8,   108,   197,     1,    24,
      70,    43,     5,    16,   214,    59,    17,   167,    24,   120,
     194,    18,    62,   215,    19,    20,    21,    71,    71,    72,
      72,     9,    68,    22,    23,     1,   214,    39,    46,   129,
      43,     1,   176,    76,   130,   215,    39,    10,   179,    68,
      47,    48,   226,     5,   160,     5,    89,   161,     5,    49,
     105,    15,    68,    96,    97,    68,   164,    24,    24,   165,
     117,   -25,   115,   125,    12,    50,    76,   126,   127,    51,
      44,   213,   127,   233,   127,    69,   102,    52,   107,   223,
       5,    53,    54,    55,    40,    39,    39,    74,    57,   156,
      60,    61,    24,    63,    65,    64,   155,   236,    24,   237,
     109,   238,   163,    66,   166,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,   125,   173,   100,   174,   175,
      39,    80,   165,    84,    85,    86,    39,    88,    81,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    82,
      99,   100,    83,   116,    87,   118,   169,   185,   171,   190,
     105,    68,   200,   135,   136,   137,   138,   201,   202,    76,
     186,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   203,   154,   205,   206,   193,    24,
     187,   162,   207,   210,   224,   211,    88,   225,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   227,    99,
     100,   230,   125,   234,   231,   235,   239,    39,    76,    89,
     -26,   -26,   -26,   -26,   -26,    95,    96,    97,   -26,     4,
     125,   100,   125,    14,   125,   232,   220,   228,   180,   189,
     204,    73,   221,   128,   114,   209,   192,   110,   195,     0,
       0,    88,   196,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     0,    99,   100,   140,   103,     0,     0,
       0,   208,     0,   101,    88,     0,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,     0,    99,   100,     0,
       0,     0,     0,     0,    88,   222,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,     0,    99,   100,     0,
      88,   212,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,    99,   100,    88,   168,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,     0,    99,   100,
      88,   229,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,    99,   100,   139,    88,     0,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,     0,    99,
     100,   181,    88,     0,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,     0,    99,   100,   182,    88,     0,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
       0,    99,   100,   183,    88,     0,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,     0,    99,   100,   184,
      88,     0,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,    99,   100
  };

  const short int
  Parser::yycheck_[] =
  {
       1,     3,   126,   170,    11,     6,    30,    11,     6,    10,
      35,    12,    57,    12,    22,    16,    15,    11,    19,    21,
      11,    20,    19,    31,    23,    24,    25,    53,    53,    55,
      55,     0,    56,    32,    33,     6,    22,    10,     5,    14,
      41,     6,    13,    44,    19,    31,    19,     4,    13,    56,
      17,    18,   219,    57,    49,    57,    36,    52,    57,    26,
      61,    37,    56,    43,    44,    56,    49,    68,    69,    52,
      71,    57,    69,    74,    29,    42,    77,    51,    52,    46,
      31,    51,    52,    51,    52,     7,    35,    54,    61,   213,
      57,    58,    59,    60,    53,    68,    69,    37,    15,    10,
      17,    54,   103,    20,    54,    22,   103,   231,   109,   233,
       7,   235,   109,    54,    49,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,   126,   127,    48,   129,   130,
     103,    54,    52,    50,    51,    52,   109,    34,    54,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    54,
      47,    48,    54,    70,    54,    72,    55,    49,    56,     9,
     161,    56,    56,    80,    81,    82,    83,    54,    54,   170,
       8,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    56,   102,    56,    56,   161,   190,
      28,   108,    56,   190,    49,    11,    34,    56,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    49,    47,
      48,    56,   213,    56,    51,    16,    56,   190,   219,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
     231,    48,   233,     6,   235,   225,   202,   221,   134,   156,
     177,    41,   204,    77,    68,   189,   158,    65,   165,    -1,
      -1,    34,   169,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    87,    27,    -1,    -1,
      -1,   188,    -1,    56,    34,    -1,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    34,   212,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    -1,
      34,    51,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    34,    50,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      34,    50,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    49,    34,    -1,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    34,    -1,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    34,    -1,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    34,    -1,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      34,    -1,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     6,    63,    64,    65,    57,    66,    67,    89,     0,
       4,    78,    29,    79,    67,    37,    12,    15,    20,    23,
      24,    25,    32,    33,    89,    93,    94,    95,    96,   102,
     103,   104,   105,   107,   108,   109,   110,   111,   112,   117,
      53,    80,    81,    89,    31,    90,     5,    17,    18,    26,
      42,    46,    54,    58,    59,    60,    89,   115,   117,    89,
     115,    54,    93,   115,   115,    54,    54,    11,    56,     7,
      35,    53,    55,    81,    37,    88,    89,    91,    92,    68,
      54,    54,    54,    54,   115,   115,   115,    54,    34,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    47,
      48,    56,    35,    27,    97,    89,   116,   117,    30,     7,
     114,   115,   113,   114,    94,    93,   115,    89,   115,     3,
      21,    82,    83,    84,    87,    89,    51,    52,    92,    14,
      19,    69,    70,    71,    72,   115,   115,   115,   115,    49,
     113,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,    93,    10,    98,    99,   100,
      49,    52,   115,    93,    49,    52,    49,    11,    50,    55,
      85,    56,    82,    89,    89,    89,    13,    65,    77,    13,
      77,    49,    49,    49,    49,    49,     8,    28,   106,   115,
       9,   101,   100,   117,    11,   115,   115,    11,    86,    88,
      56,    54,    54,    56,    79,    56,    56,    56,   115,    97,
      93,    11,    51,    51,    22,    31,    73,    74,    75,    76,
      73,    90,   115,    82,    49,    56,    88,    49,    78,    50,
      56,    51,    75,    51,    56,    16,    82,    82,    82,    56
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
      94,    94,    94,    95,    96,    97,    98,    98,    99,    99,
     100,   101,   101,   102,   103,   104,   105,   106,   106,   107,
     108,   108,   109,   110,   111,   112,   113,   113,   114,   114,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   116,   116,   117,   117,   117
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
       1,     1,     1,     3,     6,     2,     1,     0,     2,     1,
       3,     2,     0,     5,     4,     4,     6,     1,     1,     1,
       2,     1,     4,     4,     4,     0,     1,     0,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     4,     4,     4,     4,
       4,     1,     1,     1,     1,     3,     1,     3,     4,     1
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
  "thenStatement", "optElseIfStatements", "elseIfStatements",
  "elseIfStatement", "elseStatement", "whileStatement", "repeatStatement",
  "forStatement", "forHead", "optTo", "stopStatement", "returnStatement",
  "readStatement", "writeStatement", "procedureCall", "nullStatement",
  "optExpressionList", "expressionList", "expression", "lvalueList",
  "lvalue", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   113,   113,   116,   119,   120,   123,   124,   127,   130,
     131,   132,   135,   136,   139,   142,   143,   146,   149,   150,
     153,   154,   157,   160,   161,   162,   165,   168,   171,   172,
     175,   176,   179,   182,   183,   184,   187,   190,   193,   194,
     196,   199,   202,   203,   206,   209,   210,   213,   214,   217,
     220,   221,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   237,   240,   243,   246,   247,   250,   251,
     254,   257,   258,   261,   264,   267,   270,   273,   274,   277,
     280,   281,   284,   287,   290,   293,   296,   297,   300,   301,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   331,   332,   335,   336,   337
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
#line 2229 "parser.tab.cc" // lalr1.cc:1167
#line 340 "parser.yy" // lalr1.cc:1168


void cpsl::Parser::error(const location_type& l, const std::string& err_message)
{
    std::cerr << "Syntax Error: " << err_message << " at " << l << "\n";
}
