#pragma once

#include <string>
#include <functional>

namespace PerformanceTestHelpers
{
template <typename RecordType, typename CollectionType>
CollectionType PopulateDummyData(const std::string& prefix, uint numRecords,
                                 const std::function<void(CollectionType& collection, const RecordType& record)>& add,
                                 const std::function<RecordType(uint id)>& generateRecord = {})
{
    CollectionType data;
    for(uint i = 0; i < numRecords; i++)
    {
        if(generateRecord == nullptr)
            add(data, { i, prefix + std::to_string(i), i % 100, std::to_string(i) + prefix });
        else
            add(data, generateRecord(i));
    }
    return data;
}

double ExecutionTime(const std::function<void()>& task);
void TestPerformance(const std::string& testInfo, const std::function<void()>& task);
}
