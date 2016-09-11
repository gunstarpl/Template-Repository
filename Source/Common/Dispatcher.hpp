#pragma once

#include "Precompiled.hpp"
#include "Collector.hpp"
#include "Receiver.hpp"

// Forward declarations.
template<typename Type>
class Receiver;

//
// Dispatcher
//  Holds a list of subscribed receivers that can be invoked all at once. 
//  More safe than using raw delegates as unsubscribing is automated at 
//  receiver's destruction. No dangerous dangling pointers are left.
//
//  A single dispatcher instance can have multiple receivers subscribed,
//  but a single receiver can be only subscribed to one dispatcher.
//
//  Example usage:
//      struct EventData { /* ... */ };
//      
//      void Class::FunctionA(const EventData& event) { /*...*/ }
//      void Class::FunctionB(const EventData& event) { /*...*/ }
//      Class instance;
//      
//      Receiver<void(const EventData&)> receiverA;
//      receiverA.Bind<Class, &Class::FunctionA>(&instance);
//      
//      Receiver<void(const EventData&)> receiverB;
//      receiverB.Bind<Class, &Class::FunctionB>(&instance);
//      
//      Dispatcher<void(const EventData&)> dispatcher;
//      dispatcher.Subscribe(receiverA);
//      dispatcher.Subscribe(receiverB);
//      dispatcher.Dispatch(EventData(/* ... */));
//

// Dispatcher base class.
template<typename Type>
class DispatcherBase;

template<typename ReturnType, typename... Arguments>
class DispatcherBase<ReturnType(Arguments...)>
{
protected:
    DispatcherBase();
    virtual ~DispatcherBase();

    // Restores instance to it's original state.
    void Cleanup();

public:
    // Subscribes a receiver.
    void Subscribe(Receiver<ReturnType(Arguments...)>& receiver);

    // Unsubscribes a receiver.
    void Unsubscribe(Receiver<ReturnType(Arguments...)>& receiver);

    // Checks if has any subscribers.
    bool HasSubscribers() const;

protected:
    // Invokes receivers with following arguments.
    template<typename Collector>
    ReturnType Dispatch(Arguments... arguments);

private:
    // List of receivers.
    Receiver<ReturnType(Arguments...)>* m_begin;
    Receiver<ReturnType(Arguments...)>* m_end;
};

// Dispatcher class.
template<typename Type, class Collector = CollectDefault<typename std::function<Type>::result_type>>
class Dispatcher;

template<typename Collector, typename ReturnType, typename... Arguments>
class Dispatcher<ReturnType(Arguments...), Collector> : public DispatcherBase<ReturnType(Arguments...)>
{
public:
    // Restores instance to it's original state.
    void Cleanup();

    // Invokes receivers with following arguments.
    ReturnType Dispatch(Arguments... arguments);

    // Overloaded call operator that is used as dispatch.
    ReturnType operator()(Arguments... arguments);
};

// Receiver invoker class.
template<typename Type>
class ReceiverInvoker;

template<typename ReturnType, typename... Arguments>
class ReceiverInvoker<ReturnType(Arguments...)>
{
protected:
    ReturnType Dispatch(Receiver<ReturnType(Arguments...)>* receiver, Arguments... arguments)
    {
        Assert(receiver != nullptr, "Receiver is nullptr!");
        return receiver->Receive(std::forward<Arguments>(arguments)...);
    }
};

// Collector invocation for non void return types.
template<typename Collector, typename Type>
class CollectorInvocation;

template<class Collector, typename ReturnType, typename... Arguments>
class CollectorInvocation<Collector, ReturnType(Arguments...)> : public ReceiverInvoker<ReturnType(Arguments...)>
{
public:
    bool operator()(Collector& collector, Receiver<ReturnType(Arguments...)>* receiver, Arguments... arguments)
    {
        Assert(receiver != nullptr, "Receiver is nullptr!");
        return collector(this->Dispatch(receiver, std::forward<Arguments>(arguments)...));
    }
};

// Collector invocation for void return types.
template<class Collector, typename... Arguments>
class CollectorInvocation<Collector, void(Arguments...)> : public ReceiverInvoker<void(Arguments...)>
{
public:
    bool operator()(Collector& collector, Receiver<void(Arguments...)>* receiver, Arguments... arguments)
    {
        Assert(receiver != nullptr, "Receiver is nullptr!");
        this->Dispatch(receiver, std::forward<Arguments>(arguments)...);
        return collector();
    }
};

// Template definitions.
template<typename ReturnType, typename... Arguments>
DispatcherBase<ReturnType(Arguments...)>::DispatcherBase() :
    m_begin(nullptr),
    m_end(nullptr)
{
}

template<typename ReturnType, typename... Arguments>
DispatcherBase<ReturnType(Arguments...)>::~DispatcherBase()
{
    this->Cleanup();
}

template<typename ReturnType, typename... Arguments>
void DispatcherBase<ReturnType(Arguments...)>::Cleanup()
{
    // Unsubscribe all receivers.
    Receiver<ReturnType(Arguments...)>* iterator = m_begin;
    
    while(iterator != nullptr)
    {
        // Get the receiver instance.
        Receiver<ReturnType(Arguments...)>* receiver = iterator;
        Assert(receiver->m_dispatcher != nullptr, "Receiver's dispatcher is nullptr!");

        // Advance to the next receiver.
        iterator = iterator->m_next;

        // Unsubscribe a receiver.
        receiver->m_dispatcher = nullptr;
        receiver->m_previous = nullptr;
        receiver->m_next = nullptr;
    }
    
    m_begin = nullptr;
    m_end = nullptr;
}

template<typename ReturnType, typename... Arguments>
void DispatcherBase<ReturnType(Arguments...)>::Subscribe(Receiver<ReturnType(Arguments...)>& receiver)
{
    // Check if receiver is already subscribed somewhere else.
    if(receiver.m_dispatcher != nullptr)
        return;

    Assert(receiver.m_previous == nullptr, "Receiver's previous list element is not nullptr!");
    Assert(receiver.m_next == nullptr, "Receiver's next list element is not nullptr!");
    
    // Add receiver to the linked list.
    if(m_begin == nullptr)
    {
        Assert(m_end == nullptr, "Linked list's beginning is nullptr but the end is not!");

        m_begin = &receiver;
        m_end = &receiver;
    }
    else
    {
        Assert(m_end != nullptr, "Linked list's end is nullptr but the beginning is not!");

        m_end->m_next = &receiver;
        receiver.m_previous = m_end;
        m_end = &receiver;
    }

    // Set receiver's members.
    receiver.m_dispatcher = this;
}

template<typename ReturnType, typename... Arguments>
void DispatcherBase<ReturnType(Arguments...)>::Unsubscribe(Receiver<ReturnType(Arguments...)>& receiver)
{
    // Check if receiver is subscribed to this dispatcher.
    if(receiver.m_dispatcher != this)
        return;

    // Remove receiver from the linked list.
    if(m_begin == &receiver)
    {
        if(m_end == &receiver)
        {
            // Removing as the only element on the list.
            m_begin = nullptr;
            m_end = nullptr;
        }
        else
        {
            Assert(receiver.m_next != nullptr, "Receiver's next list element is nullptr!");

            // Removing from the beginning of the list.
            m_begin = receiver.m_next;
            m_begin->m_previous = nullptr;
        }
    }
    else
    {
        if(m_end == &receiver)
        {
            Assert(receiver.m_previous != nullptr, "Receiver's previous list element is nullptr!");

            // Removing from the end of the list.
            m_end = receiver.m_previous;
            m_end->m_next = nullptr;

        }
        else
        {
            Assert(receiver.m_previous != nullptr, "Receiver's previous list element is nullptr!");
            Assert(receiver.m_next != nullptr, "Receiver's next list element is nullptr!");

            // Removing in the middle of the list.
            receiver.m_previous->m_next = receiver.m_next;
            receiver.m_next->m_previous = receiver.m_previous;
        }
    }

    // Clear receiver's members.
    receiver.m_dispatcher = nullptr;
    receiver.m_previous = nullptr;
    receiver.m_next = nullptr;
}

template<typename ReturnType, typename... Arguments>
template<typename Collector>
ReturnType DispatcherBase<ReturnType(Arguments...)>::Dispatch(Arguments... arguments)
{
    // Create a result collector.
    Collector collector;

    // Send an event to all receivers.
    Receiver<ReturnType(Arguments...)>* receiver = m_begin;

    while(receiver != nullptr)
    {
        // Send an event to a receiver and collect the result.
        CollectorInvocation<Collector, ReturnType(Arguments...)> invocation;
        if(!invocation(collector, receiver, std::forward<Arguments>(arguments)...))
            break;

        // Advance to the next receiver.
        receiver = receiver->m_next;
    }

    // Return collected result.
    return collector.GetResult();
}

template<typename ReturnType, typename... Arguments>
bool DispatcherBase<ReturnType(Arguments...)>::HasSubscribers() const
{
    return m_begin != nullptr;
}

template<typename Collector, typename ReturnType, typename... Arguments>
void Dispatcher<ReturnType(Arguments...), Collector>::Cleanup()
{
    DispatcherBase<ReturnType(Arguments...)>::Cleanup();
}

template<typename Collector, typename ReturnType, typename... Arguments>
ReturnType Dispatcher<ReturnType(Arguments...), Collector>::Dispatch(Arguments... arguments)
{
    return DispatcherBase<ReturnType(Arguments...)>::Dispatch<Collector>(std::forward<Arguments>(arguments)...);
}

template<typename Collector, typename ReturnType, typename... Arguments>
ReturnType Dispatcher<ReturnType(Arguments...), Collector>::operator()(Arguments... arguments)
{
    return DispatcherBase<ReturnType(Arguments...)>::Dispatch<Collector>(std::forward<Arguments>(arguments)...);
}
