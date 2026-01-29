#include "../headers/LexerSuite.hpp"

TEST_CASE("LexerSuite", "[lexer]") {
    SECTION("Test 001") {
        const std::string input = "int a;";
        const std::string expect = "INT,a,;,<EOF>";
        REQUIRE(TestLexer::test(input, expect, 101) == true);
    }
}