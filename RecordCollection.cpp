#include "RecordCollection.h"

#include <cassert>
#include "Record.h"

void RecordCollection::Add(const Record& record)
{
    const auto& id = record.column0;
    auto it = recordsStorge_.find(id);
    if(it != recordsStorge_.end())
    {
        assert(false);
        return;
    }

    recordsStorge_[record.column0] = record;

    serchIndex_["column1"][record.column1].emplace(id);
    serchIndex_["column2"][std::to_string(record.column2)].emplace(id);
    serchIndex_["column3"][record.column3].emplace(id);
}

RecordCollection RecordCollection::FindMatchingRecords(const std::string& columnName,
                                                       const std::string& matchString) const
{
    RecordCollection resultCollection{};

    IdSet matchingIds{};
    if(columnName == "column0")
    {
        matchingIds.emplace(std::stoi(matchString));
    }
    else
    {
        auto it = serchIndex_.find(columnName);
        if(it != serchIndex_.end())
        {
            auto innerIt = it->second.find(matchString);
            if(innerIt != it->second.end())
                matchingIds = innerIt->second;
        }
    }

    for(const auto& id : matchingIds)
    {
        auto idIt = recordsStorge_.find(id);
        if(idIt != recordsStorge_.end())
            resultCollection.Add(recordsStorge_.at(id));
        else
            assert(false);
    }

    return resultCollection;
}

void RecordCollection::DeleteRecordByID(unsigned id)
{
    auto it = recordsStorge_.find(id);

    if(it != recordsStorge_.end())
        recordsStorge_.erase(it);
}
