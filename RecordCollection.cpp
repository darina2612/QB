#include "RecordCollection.h"

#include <cassert>
#include "Record.h"


const char* RecordCollection::column0 = "column0";
const char* RecordCollection::column1 = "column1";
const char* RecordCollection::column2 = "column2";
const char* RecordCollection::column3 = "column3";

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

    searchIndex_[column1][record.column1].emplace(id);
    searchIndex_[column2][std::to_string(record.column2)].emplace(id);
    searchIndex_[column3][record.column3].emplace(id);
}

RecordCollection RecordCollection::FindMatchingRecords(const std::string& columnName,
                                                       const std::string& matchString) const
{
    RecordCollection resultCollection{};

    IdSet matchingIds{};
    if(columnName == column0)
    {
        matchingIds.emplace(std::stoul(matchString));
    }
    else
    {
        auto it = searchIndex_.find(columnName);
        if(it != searchIndex_.end())
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

void RecordCollection::DeleteRecordByID(uint id)
{
    auto it = recordsStorge_.find(id);

    if(it != recordsStorge_.end())
        recordsStorge_.erase(it);
}

size_t RecordCollection::Size() const
{
    return recordsStorge_.size();
}

