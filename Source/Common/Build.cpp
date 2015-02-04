#include "Precompiled.hpp"
#include "Common/Build.hpp"

namespace
{
    std::string workingDir;
    std::string sourceDir;
}

void Build::LoadInfo()
{
    workingDir = GetTextFileContent("WorkingDir.txt");
    sourceDir = GetTextFileContent("SourceDir.txt");
}

std::string Build::GetWorkingDir()
{
    return workingDir;
}

std::string Build::GetSourceDir()
{
    return sourceDir;
}
