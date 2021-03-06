#ifndef GAME_SCRIPT_SCRIPTMANAGER_H
#define GAME_SCRIPT_SCRIPTMANAGER_H

#include <map>
#include <string>

#include <components/compiler/streamerrorhandler.hpp>
#include <components/compiler/fileparser.hpp>

#include <components/interpreter/interpreter.hpp>
#include <components/interpreter/types.hpp>

#include "../mwbase/scriptmanager.hpp"

#include "globalscripts.hpp"

namespace MWWorld
{
    struct ESMStore;
}

namespace Compiler
{
    class Context;
}

namespace Interpreter
{
    class Context;
    class Interpreter;
}

namespace MWScript
{
    class ScriptManager : public MWBase::ScriptManager
    {
            Compiler::StreamErrorHandler mErrorHandler;
            const MWWorld::ESMStore& mStore;
            bool mVerbose;
            Compiler::Context& mCompilerContext;
            Compiler::FileParser mParser;
            Interpreter::Interpreter mInterpreter;
            bool mOpcodesInstalled;

            typedef std::pair<std::vector<Interpreter::Type_Code>, Compiler::Locals> CompiledScript;
            typedef std::map<std::string, CompiledScript> ScriptCollection;

            ScriptCollection mScripts;
            GlobalScripts mGlobalScripts;
            std::map<std::string, Compiler::Locals> mOtherLocals;
            std::vector<std::string> mScriptBlacklist;

        public:

            ScriptManager (const MWWorld::ESMStore& store, bool verbose,
                Compiler::Context& compilerContext, int warningsMode,
                const std::vector<std::string>& scriptBlacklist);

            virtual void run (const std::string& name, Interpreter::Context& interpreterContext);
            ///< Run the script with the given name (compile first, if not compiled yet)

            virtual bool compile (const std::string& name);
            ///< Compile script with the given namen
            /// \return Success?

            virtual std::pair<int, int> compileAll();
            ///< Compile all scripts
            /// \return count, success

            virtual const Compiler::Locals& getLocals (const std::string& name);
            ///< Return locals for script \a name.

            virtual GlobalScripts& getGlobalScripts();
    };
}

#endif
