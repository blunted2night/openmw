#ifndef GAME_MWSCRIPT_REF_H
#define GAME_MWSCRIPT_REF_H

#include <string>

#include <components/interpreter/runtime.hpp>

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"

#include "../mwworld/ptr.hpp"

#include "interpretercontext.hpp"

namespace MWScript
{
    struct ExplicitRef
    {
        static const bool implicit = false;

        MWWorld::Ptr operator() (Interpreter::Runtime& runtime, bool required=true,
            bool activeOnly = false) const
        {
            std::string id = runtime.getStringLiteral (runtime[0].mInteger);
            runtime.pop();

            if (required)
                return MWBase::Environment::get().getWorld()->getPtr (id, activeOnly);
            else
                return MWBase::Environment::get().getWorld()->searchPtr (id, activeOnly);
        }
    };

    struct ImplicitRef
    {
        static const bool implicit = true;

        MWWorld::Ptr operator() (Interpreter::Runtime& runtime, bool required=true,
            bool activeOnly = false) const
        {
            MWScript::InterpreterContext& context
                = static_cast<MWScript::InterpreterContext&> (runtime.getContext());

            return context.getReference(required);
        }
    };
}

#endif
