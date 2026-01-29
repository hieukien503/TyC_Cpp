
// Generated from Grammar/src/TyC.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "TyCParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by TyCParser.
 */
class  TyCVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by TyCParser.
   */
    virtual std::any visitProgram(TyCParser::ProgramContext *context) = 0;


};

