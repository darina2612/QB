#include <chrono>
#include <iostream>
#include <ratio>

#include "RecordCollection.h"
#include "QBRecordCollection.h"


RecordCollection myPopulateDummyData(const std::string& prefix, int numRecords)
{
    RecordCollection data;
    for (uint i = 0; i < numRecords; i++)
    {
        Record rec = { i, prefix + std::to_string(i), i % 100, std::to_string(i) + prefix };
        data.Add(rec);
    }
    return data;
}

int main()
{
    using namespace std::chrono;
    // populate a bunch of data
    auto data = populateDummyData("testdata", 100000);
    auto myData = myPopulateDummyData("testdata", 100000);
    // Find a record that contains and measure the perf
    auto startTimer = steady_clock::now();
    auto filteredSet = QBFindMatchingRecords(data, "column1", "testdata500");
    auto filteredSet2 = QBFindMatchingRecords(data, "column2", "24");
    std::cout << "profiler: " << double((steady_clock::now() - startTimer).count()) * steady_clock::period::num / steady_clock::period::den << std::endl;

    startTimer = steady_clock::now();
    auto myFilteredSet = myData.FindMatchingRecords("column1", "testdata500");
    auto myFilteredSet2 = myData.FindMatchingRecords("column2", "24");
    std::cout << "profiler 2: " << double((steady_clock::now() - startTimer).count()) * steady_clock::period::num / steady_clock::period::den << std::endl;

    // make sure that the function is correct
    assert(filteredSet.size() == 1);
    assert(filteredSet2.size() == 1000);
    assert(myFilteredSet.Size() == 1);
    assert(myFilteredSet2.Size() == 1000);
    return 0;
}
