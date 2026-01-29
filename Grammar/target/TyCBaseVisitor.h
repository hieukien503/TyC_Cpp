
// Generated from Grammar/src/TyC.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "TyCVisitor.h"


/**
 * This class provides an empty implementation of TyCVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  TyCBaseVisitor : public TyCVisitor {
public:

  virtual std::any visitProgram(TyCParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }


};

