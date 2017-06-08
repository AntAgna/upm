#include "gtest/gtest.h"
#include "iUpmObject.hpp"
#include "iSensorType.hpp"
#include "external/json/json.hpp"


class TestSensorClass : public virtual upm::iSensorType
{
};

/* Interfaces test fixture */
class iSensorType_unit : public ::testing::Test
{
protected:
    /* One-time setup logic if needed */
    iSensorType_unit()
    {
        obj.initFromJsonLibDesc("./json_init.json");
    }

    /* One-time tear-down logic if needed */
    virtual ~iSensorType_unit() {}

    /* Per-test setup logic if needed */
    virtual void SetUp() {}

    /* Per-test tear-down logic if needed */
    virtual void TearDown() {}

    TestSensorClass obj;
};

TEST_F(iSensorType_unit, test_sources_deserialize)
{
    /* Deserialize the JSON to a map of sources */
    std::map<std::string, upm::SensorSource<float>> sources =
            obj.LibraryJson()["Sensor Class"]["TestSensorClass"]["Sources"];

    ASSERT_EQ(2, sources.size());

    ASSERT_TRUE(sources.find("temperature") != sources.end());
    ASSERT_TRUE(sources.find("humidity-relative") != sources.end());
    ASSERT_EQ("C", sources["temperature"].unit);
    ASSERT_EQ(-17.0, sources["temperature"].min);
    ASSERT_EQ(49.0, sources["temperature"].max);
    ASSERT_EQ(1.0, sources["temperature"].accuracy);
}
