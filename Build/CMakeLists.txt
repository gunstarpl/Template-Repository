#
# Build
#

# Minimun version required.
CMake_Minimum_Required(VERSION 3.1.1)

#
# Config
#

# Build settings.
Set(ProjectName "Project")
Set(TargetName "Application")

# Application settings.
Set(ShowConsole "Yes")

#
# Source
#

# Source files.
Set(SourceDir "../Source")
Set(PrecompiledHeader "Precompiled.hpp")
Set(PrecompiledSource "Precompiled.cpp")

Set(SourceFiles
    "${PrecompiledHeader}"
    "${PrecompiledSource}"

    "Main.cpp"

    "Common/Debug.hpp"
    "Common/Build.hpp"
    "Common/Build.cpp"
    "Common/Logger.hpp"
    "Common/Logger.cpp"
    "Common/Utility.hpp"
    "Common/Utility.cpp"
)

#
# Project
#

# Create a build project.
Project(${ProjectName})

# Add the source directory as an include directory.
Include_Directories(${SourceDir})

# Enable target folders.
Set_Property(GLOBAL PROPERTY USE_FOLDERS ON)

# Move CMake predefined targets to a separate folder.
Set_Property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# Append source directory path to each source file.
Set(SourceFilesTemp)

ForEach(SourceFile ${SourceFiles})
    List(APPEND SourceFilesTemp "${SourceDir}/${SourceFile}")
EndForEach()

Set(SourceFiles ${SourceFilesTemp})

# Organize source files based on their file paths.
ForEach(SourceFile ${SourceFiles})
    # Get the source file directory path.
    Get_Filename_Component(SourceFilePath ${SourceFile} PATH)
    
    # Remove the source directory path.
    String(REPLACE "${SourceDir}" "" SourceFilePath ${SourceFilePath})

    # Add source file to a group.
    If(NOT ${SourceFilePath} STREQUAL "")
        # Replace folder separators.
        String(REPLACE "/" "\\" SourceFilePath ${SourceFilePath})
        
        # Remove leading folder separator.
        String(SUBSTRING ${SourceFilePath} 0 1 FirstCharacter)

        If(FirstCharacter STREQUAL "\\")
            String(LENGTH ${SourceFilePath} SourceFilePathLength)
            Math(EXPR SourceFilePathLength "${SourceFilePathLength} - 1")
            String(SUBSTRING ${SourceFilePath} 1 ${SourceFilePathLength} SourceFilePath)
        EndIf()
    
        # Add a source file to a corresponding group.
        Source_Group("Source\\${SourceFilePath}" FILES ${SourceFile})
    Else()
        # Add source file to the default group.
        Source_Group("Source" FILES ${SourceFile})
    EndIf()
EndForEach()

#
# Target
#

# Create an executable target.
Add_Executable(${TargetName} ${SourceFiles})

# Enable unicode support.
Add_Definitions(-DUNICODE -D_UNICODE)

#
# Build
#

# Write a file in the build directory that will point to the working directory.
Get_Filename_Component(WorkingDir "${CMAKE_CURRENT_LIST_DIR}/../Deploy" ABSOLUTE)
File(WRITE "${CMAKE_BINARY_DIR}/WorkingDir.txt" "${WorkingDir}/")

# Write a file in the build directory that will point to the source directory.
Get_Filename_Component(SourceDir "${CMAKE_CURRENT_LIST_DIR}/../Source" ABSOLUTE)
File(WRITE "${CMAKE_BINARY_DIR}/SourceDir.txt" "${SourceDir}/")

#
# Windows
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

#
# Linux
#

# GCC compiler.
If("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # Enable C++11 support.
    List(APPEND CMAKE_CXX_FLAGS "-std=c++0x")
EndIf()

#
# Boost
#

# Set Boost options.
Set(Boost_USE_STATIC_LIBS ON)
Set(Boost_USE_MULTITHREADED ON)
Set(Boost_USE_STATIC_RUNTIME OFF)

# Find installed Boost library.
Find_Package(Boost 1.58.0 COMPONENTS chrono thread system date_time filesystem log log_setup REQUIRED)

# Add include directory.
Include_Directories(${Boost_INCLUDE_DIRS})

# Link library targets.
Target_Link_Libraries(${TargetName} ${Boost_LIBRARIES})

