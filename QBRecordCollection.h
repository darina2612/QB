#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>


/**
    Represents a Record Object
*/
struct QBRecord
{
    uint column0; // unique id column
    std::string column1;
    long column2;
    std::string column3;
};

/**
Represents a Record Collections
*/
typedef std::vector<QBRecord> QBRecordCollection;

/**
    Return records that contains a string in the StringValue field
    records - the initial set of records to filter
    matchString - the string to search for
*/
QBRecordCollection QBFindMatchingRecords(const QBRecordCollection& records, const std::string& columnName, const std::string& matchString);

/**
    Utility to populate a record collection
    prefix - prefix for the string value for every record
    numRecords - number of records to populate in the collection
*/
QBRecordCollection populateDummyData(const std::string& prefix, int numRecords);
