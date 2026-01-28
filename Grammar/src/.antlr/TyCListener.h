
// Generated from c:/Users/VOSTRO 3490/OneDrive/Desktop/TyC_Cpp/Grammar/src/TyC.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "TyCParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by TyCParser.
 */
class  TyCListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(TyCParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(TyCParser::ProgramContext *ctx) = 0;


};

