# Minimum version required.
CMake_Minimum_Required(VERSION 3.6.2)

#
# Config
#

# Build settings.
Set(ProjectName "Project")
Set(TargetName "Application")

# Application settings.
Set(WorkingDir "../Deploy")
Set(ShowConsole "Yes")

#
# Source
#

# Source files.
Set(SourceDir "../Source")
Set(PrecompiledHeader "Precompiled.hpp")
Set(PrecompiledSource "Precompiled.cpp")

Set(SourceFiles
    "Main.cpp"
    
    "${PrecompiledHeader}"
    "${PrecompiledSource}"
    
    "Common/Debug.hpp"
    "Common/Build.hpp"
    "Common/Build.cpp"
    "Common/Utility.hpp"
    "Common/Utility.cpp"
    "Common/Noncopyable.hpp"
    "Common/ScopeGuard.hpp"
    "Common/Delegate.hpp"
    "Common/Receiver.hpp"
    "Common/Dispatcher.hpp"
    "Common/Collector.hpp"

    "Logger/Logger.hpp"
    "Logger/Logger.cpp"
    "Logger/Message.hpp"
    "Logger/Message.cpp"
    "Logger/Output.hpp"
    "Logger/Sink.hpp"
    "Logger/Sink.cpp"
    "Logger/Outputs/DebuggerOutput.hpp"
    "Logger/Outputs/DebuggerOutput.cpp"
    "Logger/Outputs/ConsoleOutput.hpp"
    "Logger/Outputs/ConsoleOutput.cpp"
    "Logger/Outputs/FileOutput.hpp"
    "Logger/Outputs/FileOutput.cpp"
)

# Append source directory path to each source file.
Message("-- Appending source directory path...")

Set(SourceFilesTemp)

ForEach(SourceFile ${SourceFiles})
    List(APPEND SourceFilesTemp "${SourceDir}/${SourceFile}")
    Message("SourceFile: ${SourceFile} => ${SourceDir}/${SourceFile}")
EndForEach()

Set(SourceFiles ${SourceFilesTemp})

# Organize source files based on their directory structure.
Message("-- Organizing source files...")

ForEach(SourceFile ${SourceFiles})
    # Get the relative path to source file's directory.
    Get_Filename_Component(SourceFilePath ${SourceFile} PATH)
    
    # Remove the path to base source directory.
    String(REPLACE "${SourceDir}" "" SourceFilePath ${SourceFilePath})
    
    # Add a source file to a group.
    If(NOT ${SourceFilePath} STREQUAL "")
        # Normalize path separators as required by Visual Studio.
        String(REPLACE "/" "\\" SourceFilePath ${SourceFilePath})
        
        # Remove the leading path separator.
        String(SUBSTRING ${SourceFilePath} 0 1 FirstCharacter)
        
        If(FirstCharacter STREQUAL "\\")
            String(LENGTH ${SourceFilePath} SourceFilePathLength)
            Math(EXPR SourceFilePathLength "${SourceFilePathLength} - 1")
            String(SUBSTRING ${SourceFilePath} 1 ${SourceFilePathLength} SourceFilePath)
        EndIf()
        
        # Add a source file to a corresponding group.
        Source_Group("Source\\${SourceFilePath}" FILES ${SourceFile})
    Else()
        # Add a source file to the root group.
        Source_Group("Source" FILES ${SourceFile})
    EndIf()
    
    Message("SourceFilePath: ${SourceFile} => ${SourceFilePath}")
EndForEach()

#
# Build
#

# Create the project.
Project(${ProjectName})

# Create an executable target.
Add_Executable(${TargetName} ${SourceFiles})

# Add the source directory as an include directory.
Include_Directories(${SourceDir})

# Enable unicode support.
Add_Definitions(-DUNICODE -D_UNICODE)

# Enable target folders.
Set_Property(GLOBAL PROPERTY USE_FOLDERS ON)

# Move CMake predefined targets to a separate folder.
Set_Property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

#
# Debug
#

# Write a file in the build directory that will point to the working directory.
Get_Filename_Component(WorkingDirPath "${CMAKE_CURRENT_LIST_DIR}/${WorkingDir}" ABSOLUTE)
File(WRITE "${CMAKE_BINARY_DIR}/WorkingDir.txt" "${WorkingDirPath}/")

# Write a file in the build directory that will point to the source directory.
Get_Filename_Component(SourceDirPath "${CMAKE_CURRENT_LIST_DIR}/${SourceDir}" ABSOLUTE)
File(WRITE "${CMAKE_BINARY_DIR}/SourceDir.txt" "${SourceDirPath}/")

#
# Platform
#

# Visual C++ compiler.
If("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Show or hide the console window.
    If(ShowConsole)
        Set_Property(TARGET ${TargetName} APPEND_STRING PROPERTY LINK_FLAGS "/SUBSYSTEM:Console ")
    Else()
        Set_Property(TARGET ${TargetName} APPEND_STRING PROPERTY LINK_FLAGS "/SUBSYSTEM:Windows ")
    EndIf()
    
    # Restore default main() entry instead of WinMain().
    Set_Property(TARGET ${TargetName} APPEND_STRING PROPERTY LINK_FLAGS "/ENTRY:mainCRTStartup ")
    
    # Disable Standard C++ Library warnings.
    Set_Property(TARGET ${TargetName} APPEND_STRING PROPERTY COMPILE_DEFINITIONS "_CRT_SECURE_NO_WARNINGS")
    Set_Property(TARGET ${TargetName} APPEND_STRING PROPERTY COMPILE_DEFINITIONS "_SCL_SECURE_NO_WARNINGS")
    
    # Use the precompiled header.
    Get_Filename_Component(PrecompiledName ${PrecompiledHeader} NAME_WE)
    
    Set(PrecompiledBinary "$(IntDir)/${PrecompiledName}.pch")
    
    Set_Source_Files_Properties(${SourceFiles} PROPERTIES 
        COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
        OBJECT_DEPENDS "${PrecompiledBinary}"
    )
    
    Set_Source_Files_Properties("${SourceDir}/${PrecompiledSource}" PROPERTIES 
        COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
        OBJECT_OUTPUTS "${PrecompiledBinary}"
    )
EndIf()

# GCC compiler.
If("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # Enable C++11 support.
    List(APPEND CMAKE_CXX_FLAGS "-std=c++11")
EndIf()
