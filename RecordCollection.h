#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Record.h"


class RecordCollection
{
public:
    RecordCollection() = default;

    void Add(const Record& record);

    RecordCollection FindMatchingRecords(const std::string& columnName, const std::string& matchString) const;

private:
    std::unordered_map<unsigned, Record> recordsStorge_;

    using IdList = std::vector<unsigned>;
    using IdsCollection = std::unordered_map<std::string, IdList>;
    std::unordered_map<std::string, IdsCollection> serchIndex_;
};
