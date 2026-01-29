
#include "../src/lexererr.hpp"


// Generated from Grammar/src/TyC.g4 by ANTLR 4.13.2


#include "TyCLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct TyCLexerStaticData final {
  TyCLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TyCLexerStaticData(const TyCLexerStaticData&) = delete;
  TyCLexerStaticData(TyCLexerStaticData&&) = delete;
  TyCLexerStaticData& operator=(const TyCLexerStaticData&) = delete;
  TyCLexerStaticData& operator=(TyCLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag tyclexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<TyCLexerStaticData> tyclexerLexerStaticData = nullptr;

void tyclexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (tyclexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(tyclexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<TyCLexerStaticData>(
    std::vector<std::string>{
      "WS", "ERROR_CHAR", "UNCLOSED_STRING", "ILLEGAL_ESCAPE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
    },
    std::vector<std::string>{
      "", "WS", "ERROR_CHAR", "UNCLOSED_STRING", "ILLEGAL_ESCAPE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,4,22,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,1,0,4,0,11,8,0,11,0,12,
  	0,12,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,0,0,4,1,1,3,2,5,3,7,4,1,0,1,3,0,
  	9,10,13,13,32,32,22,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,1,
  	10,1,0,0,0,3,16,1,0,0,0,5,18,1,0,0,0,7,20,1,0,0,0,9,11,7,0,0,0,10,9,1,
  	0,0,0,11,12,1,0,0,0,12,10,1,0,0,0,12,13,1,0,0,0,13,14,1,0,0,0,14,15,6,
  	0,0,0,15,2,1,0,0,0,16,17,9,0,0,0,17,4,1,0,0,0,18,19,9,0,0,0,19,6,1,0,
  	0,0,20,21,9,0,0,0,21,8,1,0,0,0,2,0,12,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  tyclexerLexerStaticData = std::move(staticData);
}

}

TyCLexer::TyCLexer(CharStream *input) : Lexer(input) {
  TyCLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *tyclexerLexerStaticData->atn, tyclexerLexerStaticData->decisionToDFA, tyclexerLexerStaticData->sharedContextCache);
}

TyCLexer::~TyCLexer() {
  delete _interpreter;
}

std::string TyCLexer::getGrammarFileName() const {
  return "TyC.g4";
}

const std::vector<std::string>& TyCLexer::getRuleNames() const {
  return tyclexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& TyCLexer::getChannelNames() const {
  return tyclexerLexerStaticData->channelNames;
}

const std::vector<std::string>& TyCLexer::getModeNames() const {
  return tyclexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& TyCLexer::getVocabulary() const {
  return tyclexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TyCLexer::getSerializedATN() const {
  return tyclexerLexerStaticData->serializedATN;
}

const atn::ATN& TyCLexer::getATN() const {
  return *tyclexerLexerStaticData->atn;
}




void TyCLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  tyclexerLexerInitialize();
#else
  ::antlr4::internal::call_once(tyclexerLexerOnceFlag, tyclexerLexerInitialize);
#endif
}
