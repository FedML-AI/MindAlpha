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

#include <stddef.h>
#include <stdint.h>
#include <vector>

//
// ``hash_uniquifier.h`` defines class ``HashUniquifier``. Its static
// method ``Uniquify`` can be used to uniquify feature hash codes produced
// by ``EmbeddingOperator`` so that communication can be reduced.
//

namespace mindalpha
{

class HashUniquifier
{
public:
    static std::vector<uint64_t> Uniquify(uint64_t* items, size_t count);
    static std::vector<uint64_t> Uniquify(std::vector<uint64_t>& items);

private:
    static int32_t FindEntryAndBucket(uint64_t key, uint64_t hashCode,
                                      const std::vector<uint64_t>& entries,
                                      const std::vector<int32_t>& buckets,
                                      uint64_t& bucket);

    static uint64_t GetHashCapacity(uint64_t minSize);

    static bool InsertHashEntry(uint64_t key, uint64_t& offset,
                                std::vector<uint64_t>& entries,
                                std::vector<int32_t>& buckets);
};

}
