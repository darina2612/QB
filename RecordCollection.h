#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>

#include "Record.h"


class RecordCollection
{
public:
    RecordCollection() = default;

    bool Add(const Record& record);

    RecordCollection FindMatchingRecords(const std::string& columnName, const std::string& matchString) const;

    void DeleteRecordByID(uint id);

    size_t Size() const;

private:
    std::unordered_map<uint, Record> recordsStorge_;

    using IdSet = std::unordered_set<uint>;
    using IdsCollection = std::unordered_map<std::string, IdSet>;
    std::unordered_map<std::string, IdsCollection> searchIndex_;

    static const char* column0;
    static const char* column1;
    static const char* column2;
    static const char* column3;
};
