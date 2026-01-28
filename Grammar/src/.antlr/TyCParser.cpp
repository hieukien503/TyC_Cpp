
// Generated from c:/Users/VOSTRO 3490/OneDrive/Desktop/TyC_Cpp/Grammar/src/TyC.g4 by ANTLR 4.13.1



#include "TyCParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct TyCParserStaticData final {
  TyCParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TyCParserStaticData(const TyCParserStaticData&) = delete;
  TyCParserStaticData(TyCParserStaticData&&) = delete;
  TyCParserStaticData& operator=(const TyCParserStaticData&) = delete;
  TyCParserStaticData& operator=(TyCParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag tycParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
TyCParserStaticData *tycParserStaticData = nullptr;

void tycParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (tycParserStaticData != nullptr) {
    return;
  }
#else
  assert(tycParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<TyCParserStaticData>(
    std::vector<std::string>{
      "program"
    },
    std::vector<std::string>{
    },
    std::vector<std::string>{
      "", "WS", "ERROR_CHAR", "UNCLOSED_STRING", "ILLEGAL_ESCAPE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,4,6,2,0,7,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,4,0,2,1,0,0,0,2,3,9,0,0,0,
  	3,4,5,0,0,1,4,1,1,0,0,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  tycParserStaticData = staticData.release();
}

}

TyCParser::TyCParser(TokenStream *input) : TyCParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

TyCParser::TyCParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  TyCParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *tycParserStaticData->atn, tycParserStaticData->decisionToDFA, tycParserStaticData->sharedContextCache, options);
}

TyCParser::~TyCParser() {
  delete _interpreter;
}

const atn::ATN& TyCParser::getATN() const {
  return *tycParserStaticData->atn;
}

std::string TyCParser::getGrammarFileName() const {
  return "TyC.g4";
}

const std::vector<std::string>& TyCParser::getRuleNames() const {
  return tycParserStaticData->ruleNames;
}

const dfa::Vocabulary& TyCParser::getVocabulary() const {
  return tycParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TyCParser::getSerializedATN() const {
  return tycParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

TyCParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TyCParser::ProgramContext::EOF() {
  return getToken(TyCParser::EOF, 0);
}


size_t TyCParser::ProgramContext::getRuleIndex() const {
  return TyCParser::RuleProgram;
}


TyCParser::ProgramContext* TyCParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, TyCParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2);
    matchWildcard();
    setState(3);
    match(TyCParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void TyCParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  tycParserInitialize();
#else
  ::antlr4::internal::call_once(tycParserOnceFlag, tycParserInitialize);
#endif
}
