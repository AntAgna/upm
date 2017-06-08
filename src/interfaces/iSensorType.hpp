#pragma once

#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "iUpmObject.hpp"

namespace upm
{
    template <typename T>
    struct SensorSource
    {
        std::string unit;
        T min;
        T max;
        T accuracy;
    };

    template <typename T>
    void to_json(nlohmann::json& j, const SensorSource<T>& p);

    template <typename T>
    void from_json(const nlohmann::json& j, SensorSource<T>& p);

    /*
     {
        j = nlohmann::json{
            {"unit", p.unit},
                {"min", p.min},
                {"max", p.max},
                {"accuracy", p.accuracy}};
    }

     {
        p.unit = j.at("unit").get<std::string>();
        p.min = j.at("min").get<float>();
        p.max = j.at("max").get<float>();
        p.accuracy = j.at("accuracy").get<float>();
    }

    bool operator==(const SensorSource& lhs, const SensorSource& rhs)
    {
        return lhs.unit == rhs.unit && lhs.min == rhs.min;
    }*/

    /**
     * Forward declaration of iSensorType class for ostream usage
     */
    class iSensorType;

    /**
     * iSensorType abstract class.
     *
     * Provides a common interface for sensor classes.  This interface is
     * meant to be used by derived sensor categories.
     *
     * For example, iTemperatureSensor or iLightSensor
     *
     */
    class iSensorType : public virtual iUpmObject
    {
        public:
            /**
             * Allow derived classes to provide their own destructor
             */
            virtual ~iSensorType();

            std::string LibraryJsonSources();

            /**
             * Return a map reference of sources to units.  This map can
             * be used to get the units for a sensor value given a source.
             *
             * @return Map of sources to units.
             */
            const std::map<std::string, std::string>& SourceMap() const;

            /**
             * Return a vector of all known sources for this sensor.
             *
             * @return Vector of sources
             */
            const std::vector<std::string>& Sources();

            /**
             * Return a vector of all known units for this sensor.
             *
             * @return Vector of units
             */
            const std::vector<std::string>& Units() const;

            /**
             * Return a unit string given a single source.
             *
             * @return Corresponding unit for source or empty string if not found.
             */
            virtual const std::string Unit(std::string source) const;

            /**
             * Determine if this sensor has a given source.
             *
             * @return True if source string is available, fails otherwise.
             */
            virtual bool HasSource(std::string source);

            /**
             * Determine if this sensor has a given unit.
             *
             * @return True if unit string is available, fails otherwise.
             */
            virtual bool HasUnit(std::string unit) const;

            /**
             * Return a JsonDefinition string which defines this sensor
             *
             * @return JsonDefinition-encoded string.
             */
            virtual std::string JsonDefinition();

            /**
             * @brief Json string of sensor data.
             *
             * The JsonValues call serializes ALL values returned by this sensor
             * as a Json string.
             *
             * Example:
             *
             *      "Temperature" : {"value" : 25.0, "units" : "C"}
             *      "Acceleration" : {"value" : 1.1, "units" : "m/s^2"}
             *
             *  @return Json-encoded string.
             */
            virtual std::string JsonValues();

            ///*
            ///**
            // * Overload for stream operator - output a meaningful JsonDefinition string from
            // * an iSensorType Instance
            // *
            //friend std::ostream& operator<<(std::ostream& os, const iSensorType& o)
            //{
            //    os << dynamic_cast<const iUpmObject&>(o) << "," << std::endl;
            //    if (!o.SourceMap().empty())
            //    {
            //        os << "  \"sources\" :" << std::endl << "  {" << std::endl;
            //        for(std::map<std::string, std::string>::const_iterator it = o.SourceMap().begin();
            //                it != o.SourceMap().end();)
            //        {
            //            os << "    \"" << it->first << "\" : {\"units\" : \"" << it->second << "\"}";
            //            if (++it != o.SourceMap().end())
            //                os << "," << std::endl;
            //        }
            //        os << std::endl << "  }";
            //    }
            //    return os;
            //}

            ///**
            // * Overload for stream operator - output a meaningful JsonDefinition string from
            // * an iSensorType Instance
            // *
            //friend std::ostream& operator<<(std::ostream& os, const iSensorType* o)
            //{ return os << *o; }
            //*/

        private:
            /**
             * Sensor source vector
             */
            std::vector<std::string> _sources;

            /**
             * Sensor unit vector
             */
            std::vector<std::string> _units;

            /**
             * Mapping of sources to units
             */
            std::map<std::string, std::string> _sources_2_units;

        protected:
            /**
             * Mapping of sources to units, also re-creates the sources
             * and units vector on each add.
             */
            void AddSource(std::string source, std::string unit);

    };
}
