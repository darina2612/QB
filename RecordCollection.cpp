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
    IdSet matchingIds{};
    if(columnName == column0)
    {
        // column0's value is unique key, no more thn one record should contain this value
        matchingIds.emplace(std::stoul(matchString));
    }
    else
    {
        //searching for the set of ids of recors, containig the requested value for that field
        auto it = searchIndex_.find(columnName);
        if(it != searchIndex_.end())
        {
            auto innerIt = it->second.find(matchString);
            if(innerIt != it->second.end())
                matchingIds = innerIt->second;
        }
    }

    RecordCollection resultCollection{};

    //now adding the records to the result collection
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
    {
        //removing record's info from search index
        auto removeFromIndex = [this, id](const auto& columnName, const auto& valueStr)
        {
            auto it = searchIndex_.find(columnName);
            if(it != searchIndex_.end())
            {
                auto valueIt = it->second.find(valueStr);
                if(valueIt != it->second.end())
                {
                    auto& indexSet = valueIt->second;

                    auto indexIt = indexSet.find(id);
                    if(indexIt != indexSet.end())
                        indexSet.erase(indexIt);
                }
            }
        };

        const auto& record = it->second;
        removeFromIndex(column1, record.column1);
        removeFromIndex(column2, std::to_string(record.column2));
        removeFromIndex(column3, record.column3);

        //removing the record from storage
        recordsStorge_.erase(it);
    }
}

size_t RecordCollection::Size() const
{
    return recordsStorge_.size();
}

