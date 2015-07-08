#pragma once

//
// NonCopyable
//

class NonCopyable
{
protected:
    // Empty constructor and destructor.
    NonCopyable()
    {
    }
    
    ~NonCopyable()
    {
    }

private:
    // Make default copy constructor and copy operator private.
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};
