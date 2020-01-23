#include <chrono>
#include <iostream>
#include <ratio>

#include "RecordCollection.h"
#include "QBRecordCollection.h"
#include "PerformanceTestHelpers.h"

void TestPreformance()
{
    auto testFetch = [](uint recordsCount)
    {
        auto data1 = PerformanceTestHelpers::PopulateDummyData<QBRecord, QBRecordCollection>("testdata", recordsCount,
                                                                                            [](auto& collection, const auto& record)
                                                                                            {
                                                                                                collection.emplace_back(record);
                                                                                            });
        PerformanceTestHelpers::TestPerformance("Base implementation data population and fetch - "
                                                + std::to_string(recordsCount) + " records",
                                                [&data1, &recordsCount]()
        {
            auto filteredSet = QBFindMatchingRecords(data1, "column1", "testdata" + std::to_string(recordsCount));
            auto filteredSet2 = QBFindMatchingRecords(data1, "column2", "24");
        });

        auto data2 = PerformanceTestHelpers::PopulateDummyData<Record, RecordCollection>("testdata", recordsCount,
                                                                                        [](auto& collection, const auto& record)
                                                                                        {
                                                                                            collection.Add(record);
                                                                                        });
        PerformanceTestHelpers::TestPerformance("Data population and fetch - " + std::to_string(recordsCount) + " records",
                                                [&data2, &recordsCount]()
        {
            auto filteredSet = data2.FindMatchingRecords("column1", "testdata" + std::to_string(recordsCount / 2));
            auto filteredSet2 = data2.FindMatchingRecords("column2", "24");
        });

        std::cout << "=======================================================\n";
    };

    auto testRemove = [](uint recordsCount)
    {
        auto data = PerformanceTestHelpers::PopulateDummyData<Record, RecordCollection>("testdata", recordsCount,
                                                                                        [](auto& collection, const auto& record)
                                                                                        {
                                                                                            collection.Add(record);
        });

        PerformanceTestHelpers::TestPerformance("Remove with " + std::to_string(recordsCount) + " records",
                                                [&]()
        {
            for(uint i = 0; i < recordsCount / 2; ++i)
            {
                data.DeleteRecordByID(i);
                data.DeleteRecordByID(recordsCount - i - 1);
            }
        });

        std::cout << "=======================================================\n";
    };

    testFetch(10000);
    testFetch(1000000);

    testRemove(100000);
}

int main()
{
//    using namespace std::chrono;
//    // populate a bunch of data
//    auto data = populateDummyData("testdata", 1000);
//    // Find a record that contains and measure the perf
//    auto startTimer = steady_clock::now();
//    auto filteredSet = QBFindMatchingRecords(data, "column1", "testdata500");
//    auto filteredSet2 = QBFindMatchingRecords(data, "column2", "24");
//    std::cout << "profiler: " << double((steady_clock::now() - startTimer).count()) * steady_clock::period::num / steady_clock::period::den << std::endl;

//    // make sure that the function is correct
//    assert(filteredSet.size() == 1);

    TestPreformance();

    return 0;
}
