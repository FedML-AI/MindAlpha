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

#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sstream>
#include <mindalpha/thread_utils.h>

namespace mindalpha
{

std::string GetThreadIdentifier()
{
    std::ostringstream sout;
    sout << "pid: " << getpid() << ", ";
    sout << "tid: " << syscall(SYS_gettid) << ", ";
    sout << "thread: 0x" << std::hex << static_cast<uint64_t>(pthread_self());
    return sout.str();
}

}
