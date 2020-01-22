#pragma once

#include <set>
#include <string>
#include <unordered_map>

#include "Record.h"


class RecordCollection
{
public:
    RecordCollection() = default;

    void Add(const Record& record);

    RecordCollection FindMatchingRecords(const std::string& columnName, const std::string& matchString) const;

    void DeleteRecordByID(unsigned id);

private:
    std::unordered_map<unsigned, Record> recordsStorge_;

    using IdSet = std::set<unsigned>;
    using IdsCollection = std::unordered_map<std::string, IdSet>;
    std::unordered_map<std::string, IdsCollection> serchIndex_;
};
