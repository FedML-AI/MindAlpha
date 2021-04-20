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

#pragma once

#include <mindalpha/actor_config.h>

namespace mindalpha
{

class PSRunner
{
public:
    static void RunPS(std::shared_ptr<mindalpha::ActorConfig> config);

private:
    static void RunPSCoordinator(std::shared_ptr<mindalpha::ActorConfig> config);
    static void RunPSServer(std::shared_ptr<mindalpha::ActorConfig> config);
    static void RunPSWorker(std::shared_ptr<mindalpha::ActorConfig> config);
};

}
