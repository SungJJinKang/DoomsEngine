#include "UUID.h"

#include <random>
#include <sstream>
#include <unordered_set>

#ifndef VERIFY_UUID_DUPLICATION

#ifdef DEBUG_MODE
#define VERIFY_UUID_DUPLICATION 1
#else
#define VERIFY_UUID_DUPLICATION 1
#endif

#endif

namespace dooms
{
    namespace uuid
    {
        static std::random_device              rd;
        static std::mt19937_64                 gen(rd());
        static std::uniform_int_distribution<> dis(0, 15);
        static std::uniform_int_distribution<> dis2(8, 11);

#if VERIFY_UUID_DUPLICATION
        static std::unordered_set<D_UUID> GeneratedUUIDListForVerify{};
#endif
    }
}

dooms::D_UUID dooms::GenerateUUID()
{
    D_ASSERT(dooms::thread::IsInGameThread());

    // reference : https://stackoverflow.com/a/60198074
    // @todo : check the comments of referenced post

    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << uuid::dis(uuid::gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << uuid::dis(uuid::gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << uuid::dis(uuid::gen);
    }
    ss << "-";
    ss << uuid::dis2(uuid::gen);
    for (i = 0; i < 3; i++) {
        ss << uuid::dis(uuid::gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << uuid::dis(uuid::gen);
    };

    dooms::D_UUID GeneratedUUID = { ss.str() };

#if VERIFY_UUID_DUPLICATION
    const auto iter = dooms::uuid::GeneratedUUIDListForVerify.find(GeneratedUUID);
    if (iter != dooms::uuid::GeneratedUUIDListForVerify.end())
    {
        D_ASSERT_LOG(false, "Duplicated UUID");
    }
    else
    {
        dooms::uuid::GeneratedUUIDListForVerify.emplace_hint(iter, GeneratedUUID);
    }
#endif

    return std::move(GeneratedUUID);
}

bool operator==(const dooms::D_UUID& Lhs, const dooms::D_UUID& Rhs)
{
    return Lhs.operator==(Rhs);
}