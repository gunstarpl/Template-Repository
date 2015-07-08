#pragma once

#include "Precompiled.hpp"
#include "Logger/Output.hpp"

//
// Logger File Output
//
//  Writes log messages to a file.
//

namespace Logger
{
    class FileOutput : public Output
    {
    public:
        FileOutput();
        ~FileOutput();

        bool Open(std::string filename);
        void Cleanup();

        void Write(const Message& message);

        bool IsOpen() const
        {
            return m_file.is_open();
        }

    private:
        std::ofstream m_file;
    };
}
