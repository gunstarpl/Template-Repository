#pragma once

/*
    Scope Guard Template

    Executes a set function at the end of its lifetime.
    
    Creating a scope guard:
        int* array = new int[10];
        auto Cleanup = MakeScopeGuard([&]()
        {
            delete[] array;
        });
    
    Using a scope guard macro:
        int* array = new int[10];
        SCOPE_GUARD(delete[] array);
    
    Using a conditional scope guard macro:
        bool cleanup = true;
        int* array = new int[10];
        SCOPE_GUARD_IF(cleanup, delete[] array);
    
    Using braced scope guard macros:
        int* array = new int[10];
        SCOPE_GUARD_BEGIN();
        {
            delete[] array;
            array = nullptr;
        }
        SCOPE_GUARD_END();
    
    Using braced conditonal scope guard macros:
        bool cleanup = true;
        int* array = new int[10];
        SCOPE_GUARD_BEGIN(cleanup);
        {
            delete[] array;
            array = nullptr;
        }
        SCOPE_GUARD_END();
*/

// Scope guard template class.
template<typename Type>
class ScopeGuard : private NonCopyable
{
public:
    explicit ScopeGuard(Type function) :
        m_function(function)
    {
    }

    ScopeGuard(ScopeGuard<Type>&& other)
    {
        m_function = std::move(other.m_function);
    }

    ~ScopeGuard()
    {
        m_function();
    }

public:
    // Helper boolean wrapper.
    class Condition
    {
    public:
        Condition() :
            m_value(true)
        {
        }

        Condition(bool value) :
            m_value(value)
        {
        }

        explicit operator bool()
        {
            return m_value;
        }

    private:
        bool m_value;
    };

private:
    Type m_function;
};

// Creates a scope guard.
template<typename Type>
ScopeGuard<Type> MakeScopeGuard(Type function)
{
    return ScopeGuard<Type>(function);
}

// Utility macros.
#define SCOPE_GUARD_BEGIN(...) auto SCOPE_GUARD_NAME(__LINE__) = MakeScopeGuard([&]() { if(ScopeGuard<void>::Condition(__VA_ARGS__)) { 
#define SCOPE_GUARD_END() } });

#define SCOPE_GUARD(code) auto SCOPE_GUARD_NAME(__LINE__) = SCOPE_GUARD_MAKE(code)
#define SCOPE_GUARD_MAKE(code) MakeScopeGuard([&]() { code; })

#define SCOPE_GUARD_IF(condition, code) auto SCOPE_GUARD_NAME(__LINE__) = SCOPE_GUARD_IF_MAKE(condition, code)
#define SCOPE_GUARD_IF_MAKE(condition, code) MakeScopeGuard([&]() { if(condition) { code; } })

#define SCOPE_GUARD_NAME(line) SCOPE_GUARD_STRING(line)
#define SCOPE_GUARD_STRING(line) scopeguardLine ## line
