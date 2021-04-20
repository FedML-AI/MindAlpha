//
// Copyright 2021 Mobvista
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <stdexcept>
#include <spdlog/spdlog.h>
#include <mindalpha/node_control_command.h>
#include <mindalpha/stack_trace_utils.h>

namespace mindalpha
{

std::string NodeControlCommandToString(NodeControlCommand command)
{
    switch (command)
    {
#undef MINDALPHA_NODE_CONTROL_COMMAND_DEF
#define MINDALPHA_NODE_CONTROL_COMMAND_DEF(n) case NodeControlCommand::n: return #n;
    MINDALPHA_NODE_CONTROL_COMMANDS(MINDALPHA_NODE_CONTROL_COMMAND_DEF)
    default:
        std::string serr;
        serr.append("Invalid NodeControlCommand enum value: ");
        serr.append(std::to_string(static_cast<int>(command)));
        serr.append(".\n\n");
        serr.append(GetStackTrace());
        spdlog::error(serr);
        throw std::runtime_error(serr);
    }
}

NodeControlCommand NodeControlCommandFromString(const std::string& str)
{
#undef MINDALPHA_NODE_CONTROL_COMMAND_DEF
#define MINDALPHA_NODE_CONTROL_COMMAND_DEF(n) if (str == #n) return NodeControlCommand::n;
    MINDALPHA_NODE_CONTROL_COMMANDS(MINDALPHA_NODE_CONTROL_COMMAND_DEF)
    std::string serr;
    serr.append("Invalid NodeControlCommand enum value: ");
    serr.append(str);
    serr.append(".\n\n");
    serr.append(GetStackTrace());
    spdlog::error(serr);
    throw std::runtime_error(serr);
}

std::string NullableNodeControlCommandToString(NodeControlCommand command)
{
    if (command == NullNodeControlCommand)
        return NullNodeControlCommandString;
    return NodeControlCommandToString(command);
}

NodeControlCommand NullableNodeControlCommandFromString(const std::string& str)
{
    if (str == NullNodeControlCommandString)
        return NullNodeControlCommand;
    return NodeControlCommandFromString(str);
}

}
