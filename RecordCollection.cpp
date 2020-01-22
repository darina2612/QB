#include "RecordCollection.h"

#include "Record.h"

void RecordCollection::Add(const Record& record)
{
    recordsStorge_[record.column0] = record;

    serchIndex_["column0"][std::to_string(record.column0)].emplace_back(record.column0);
    serchIndex_["column1"][record.column1].emplace_back(record.column0);
    serchIndex_["column2"][std::to_string(record.column2)].emplace_back(record.column0);
    serchIndex_["column3"][record.column3].emplace_back(record.column0);
}

RecordCollection RecordCollection::FindMatchingRecords(const std::string& columnName,
                                                       const std::string& matchString) const
{
    auto it = serchIndex_.find(columnName);
    if(it != serchIndex_.end())
    {
        auto innerIt = it->second.find(matchString);
        if(innerIt != it->second.end())
        {
            RecordCollection resultCollection{};

            for(const auto& id : innerIt->second)
            {
                resultCollection.Add(recordsStorge_.at(id));
            }
        }
    }

    return {};
}
