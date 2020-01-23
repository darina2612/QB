#pragma once

#include <string>
#include <cstdint>

struct Record
{
    Record() = default;

    Record(uint c0, std::string c1, long c2, std::string c3) :
    column0(c0), column1(std::move(c1)), column2(c2), column3(std::move(c3))
    {}

    uint column0; // unique id column
    long column2;
    std::string column1;
    std::string column3;
};
