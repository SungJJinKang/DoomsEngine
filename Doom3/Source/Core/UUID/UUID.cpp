#include "UUID.h"

#include <random>
#include <sstream>

static std::random_device              rd;
static std::mt19937_64                 gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

dooms::D_UUID dooms::GenerateUUID()
{
    // reference : https://stackoverflow.com/a/60198074
    // @todo : check the comments of referenced post

    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    return ss.str();
}

bool operator==(const dooms::D_UUID& Lhs, const dooms::D_UUID& Rhs)
{
    return Lhs.operator==(Rhs);
}