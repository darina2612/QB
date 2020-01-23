#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>

#include "Record.h"


class RecordCollection
{
public:
    RecordCollection() = default;

/**
  * @brief Adds a new record, if one with the same id does not exist already
  *
  * @return True, if the record is successfully added, false, if a record with the same id is already present, so nothing was added
  */
    bool Add(const Record& record);

/**
  * @brief Generates a new collection, containig only the records with given values in given column
  *
  * @param  columnName The name of the column
  *
  * @param matchString The value to be searched, as a string
  *
  * @return A new collection, containing the requested reords
  */
    RecordCollection FindMatchingRecords(const std::string& columnName, const std::string& matchString) const;

/**
  * @brief Removes the record with given id from the collection (if such is present)
  *
  * @param The unique id of the record to be removed
  */
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
