#include "Precompiled.hpp"
#include "Logger.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
using namespace boost;

void Logger::Initialize()
{
    // Get the logger core.
    auto core = log::core::get();

    // Setup attributes.
    log::add_common_attributes();

    #ifdef _DEBUG
        log::core::get()->add_global_attribute("Scope", log::attributes::named_scope());
    #endif

    // Create a console sink.
    #ifdef _DEBUG
        typedef log::sinks::text_ostream_backend ConsoleBackend;

        auto consoleBackend = boost::make_shared<ConsoleBackend>();

        consoleBackend->add_stream(boost::shared_ptr<std::ostream>(&std::cout, boost::null_deleter()));
        consoleBackend->auto_flush(true);

        auto consoleSink = boost::make_shared<log::sinks::synchronous_sink<ConsoleBackend>>(consoleBackend);

        consoleSink->set_formatter(
            log::expressions::stream
                << log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "[%H:%M:%S]")
                << " : " << log::expressions::smessage
        );

        core->add_sink(consoleSink);
    #endif

    // Create a debugger sink.
    #ifdef _DEBUG
        typedef log::sinks::debug_output_backend DebuggerBackend;

        auto debuggerBackend = boost::make_shared<DebuggerBackend>();
        auto debuggerSink = boost::make_shared<log::sinks::synchronous_sink<DebuggerBackend>>(debuggerBackend);

        debuggerSink->set_formatter(
            log::expressions::stream
                << log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "[%H:%M:%S]")
                << " : " << log::expressions::smessage << " " 
                << log::expressions::format_named_scope("Scope",
                    log::keywords::format = "(%f:%l)", 
                    log::keywords::depth = 1,
                    log::keywords::empty_marker = "",
                    log::keywords::incomplete_marker = "")
                << '\n'
        );

        debuggerSink->set_filter(log::expressions::is_debugger_present());

        core->add_sink(debuggerSink);
    #endif

    // Create a file sink.
    typedef log::sinks::text_file_backend FileBackend;

    auto fileBackend = boost::make_shared<FileBackend>(log::keywords::file_name = "Log.txt");
    auto fileSink = boost::make_shared<log::sinks::synchronous_sink<FileBackend>>(fileBackend);

    fileSink->set_formatter(
        log::expressions::stream
            << log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "[%H:%M:%S]")
            << " : " << log::expressions::smessage

            #ifdef _DEBUG
                << " " << log::expressions::format_named_scope("Scope", log::keywords::format = "(%f:%l)")
            #endif
    );

    core->add_sink(fileSink);
}
