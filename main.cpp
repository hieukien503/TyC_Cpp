#include "main.hpp"

std::wstring utf8_to_wstring(const std::string& str) {
    if (str.empty()) return L"";

    int size_needed = MultiByteToWideChar(
        CP_UTF8,            // Source is UTF-8
        0,
        str.c_str(),
        (int)str.size(),
        nullptr,
        0
    );

    std::wstring wstr(size_needed, 0);

    MultiByteToWideChar(
        CP_UTF8,
        0,
        str.c_str(),
        (int)str.size(),
        &wstr[0],
        size_needed
    );

    return wstr;
}

void printUsage() {
    std::cout << "./main gen\n./main run";
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printUsage();
        return 0;
    }

    if (std::strcmp(argv[1], "gen") == 0) {
        STARTUPINFOW si{};
        PROCESS_INFORMATION pi{};

        si.cb = sizeof(si);
        const char* antlrJar = std::getenv("ANTLR_JAR");
        if (antlrJar) {
            const std::string cmdStr = "java -jar " + std::string(antlrJar) + " -o ./Grammar/target -no-listener -visitor ./Grammar/src/TyC.g4";
            const std::wstring cmdW = utf8_to_wstring(cmdStr);
            std::vector<wchar_t> buffer(cmdW.begin(), cmdW.end());
            buffer.push_back(L'\0');
            BOOL success = CreateProcessW(
                nullptr,
                buffer.data(),
                nullptr,
                nullptr,
                FALSE, 0,
                nullptr, nullptr,
                &si, &pi
            );

            if (!success) {
                std::cerr << "CreateProcess failed: "
                        << GetLastError() << "\n";
                return 1;
            }

            // Wait for process to finish
            WaitForSingleObject(pi.hProcess, INFINITE);

            DWORD exitCode;
            GetExitCodeProcess(pi.hProcess, &exitCode);

            if (exitCode == 0) {
                std::cout << "ANTLR grammar generated successfully with exitcode = " << exitCode << ".";
                std::cout << "\nOutput directory: ./Grammar/target";
            }
            
            else {
                std::cout << "ANTLR grammar generated failed with exitcode = " << exitCode << ".";
            }

            // CLEANUP (MANDATORY)
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }

        else {
            std::cerr << "No ANTLR_JAR environment variable";
        }
    }
    
    else if (std::strcmp(argv[1], "run") == 0) {
        std::ifstream stream("./main.tyc");
        try {
            std::cout << "Success";
        } 
        
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

    else {
        printUsage();
    }
}