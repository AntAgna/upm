#include "iActuatorType.hpp"
#include "external/json/json.hpp"

using namespace upm;

std::string iActuatorType::LibraryJsonCommands()
{
    std::stringstream ss;
    ss << this->LibraryJson()["Sensor Class"][Name()]["Commands"] << std::endl;
    return ss.str();
}

std::string iActuatorType::JsonDefinition ()
{
    std::stringstream ss;

    ss << "{" << std::endl
        << "  \"name\" : \"" << Name() << "\"," << std::endl
        << "  \"description\" : \"" << Description() << "\"";

    ss << std::endl << "}";
    return ss.str();
}

iActuatorType::~iActuatorType () {}
