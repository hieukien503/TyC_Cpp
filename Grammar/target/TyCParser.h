
// Generated from ./Grammar/src/TyC.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  TyCParser : public antlr4::Parser {
public:
  enum {
    WS = 1, ERROR_CHAR = 2, UNCLOSED_STRING = 3, ILLEGAL_ESCAPE = 4
  };

  enum {
    RuleProgram = 0
  };

  explicit TyCParser(antlr4::TokenStream *input);

  TyCParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~TyCParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

