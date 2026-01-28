
// Generated from c:/Users/VOSTRO 3490/OneDrive/Desktop/TyC_Cpp/Grammar/src/TyC.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "TyCListener.h"


/**
 * This class provides an empty implementation of TyCListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  TyCBaseListener : public TyCListener {
public:

  virtual void enterProgram(TyCParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(TyCParser::ProgramContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

