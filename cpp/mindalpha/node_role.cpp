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
#include <mindalpha/node_role.h>
#include <mindalpha/stack_trace_utils.h>

namespace mindalpha
{

std::string NodeRoleToString(NodeRole role)
{
    switch (role)
    {
#undef MINDALPHA_NODE_ROLE_DEF
#define MINDALPHA_NODE_ROLE_DEF(n) case NodeRole::n: return #n;
    MINDALPHA_NODE_ROLES(MINDALPHA_NODE_ROLE_DEF)
    default:
        std::string serr;
        serr.append("Invalid NodeRole enum value: ");
        serr.append(std::to_string(static_cast<int>(role)));
        serr.append(".\n\n");
        serr.append(GetStackTrace());
        spdlog::error(serr);
        throw std::runtime_error(serr);
    }
}

NodeRole NodeRoleFromString(const std::string& str)
{
#undef MINDALPHA_NODE_ROLE_DEF
#define MINDALPHA_NODE_ROLE_DEF(n) if (str == #n) return NodeRole::n;
    MINDALPHA_NODE_ROLES(MINDALPHA_NODE_ROLE_DEF)
    std::string serr;
    serr.append("Invalid NodeRole enum value: ");
    serr.append(str);
    serr.append(".\n\n");
    serr.append(GetStackTrace());
    spdlog::error(serr);
    throw std::runtime_error(serr);
}

std::string NullableNodeRoleToString(NodeRole role)
{
    if (role == NullNodeRole)
        return NullNodeRoleString;
    return NodeRoleToString(role);
}

NodeRole NullableNodeRoleFromString(const std::string& str)
{
    if (str == NullNodeRoleString)
        return NullNodeRole;
    return NodeRoleFromString(str);
}

}
