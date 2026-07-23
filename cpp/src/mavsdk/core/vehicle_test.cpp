#include "vehicle.hpp"
#include <gtest/gtest.h>
#include <sstream>

using namespace mavsdk;

TEST(Vehicle, ToVehicleFromMavTypeCommon)
{
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_GENERIC), Vehicle::Generic);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_FIXED_WING), Vehicle::FixedWing);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_QUADROTOR), Vehicle::Quadrotor);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_HELICOPTER), Vehicle::Helicopter);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_GROUND_ROVER), Vehicle::GroundRover);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_SURFACE_BOAT), Vehicle::SurfaceBoat);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_SUBMARINE), Vehicle::Submarine);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_HEXAROTOR), Vehicle::Hexarotor);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_OCTOROTOR), Vehicle::Octorotor);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_TRICOPTER), Vehicle::Tricopter);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_VTOL_TILTROTOR), Vehicle::VtolTiltrotor);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_GENERIC_MULTIROTOR), Vehicle::GenericMultirotor);
}

TEST(Vehicle, ToVehicleFromMavTypeUnknownFallback)
{
    auto bogus = static_cast<MAV_TYPE>(250);
    EXPECT_EQ(to_vehicle_from_mav_type(bogus), Vehicle::Unknown);
}

TEST(Vehicle, StreamOperatorKnownAndUnknown)
{
    {
        std::ostringstream oss;
        oss << Vehicle::Quadrotor;
        EXPECT_EQ(oss.str(), "Quadrotor");
    }
    {
        std::ostringstream oss;
        oss << Vehicle::FixedWing;
        EXPECT_EQ(oss.str(), "FixedWing");
    }
    {
        std::ostringstream oss;
        oss << Vehicle::Unknown;
        EXPECT_EQ(oss.str(), "Unknown");
    }
    {
        std::ostringstream oss;
        oss << static_cast<Vehicle>(250);
        EXPECT_EQ(oss.str(), "Unknown");
    }
}

TEST(Vehicle, VtolAndExoticStream)
{
    std::ostringstream oss;
    oss << Vehicle::VtolTailsitter << "," << Vehicle::Parachute << "," << Vehicle::Dodecarotor;
    EXPECT_EQ(oss.str(), "VtolTailsitter,Parachute,Dodecarotor");
}

TEST(Vehicle, ToVehicleFromMavTypeRemainingTypes)
{
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_COAXIAL), Vehicle::Coaxial);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_AIRSHIP), Vehicle::Airship);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_FREE_BALLOON), Vehicle::FreeBalloon);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_ROCKET), Vehicle::Rocket);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_FLAPPING_WING), Vehicle::FlappingWing);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_KITE), Vehicle::Kite);
    EXPECT_EQ(
        to_vehicle_from_mav_type(MAV_TYPE_VTOL_TAILSITTER_DUOROTOR),
        Vehicle::VtolTailsitterDuorotor);
    EXPECT_EQ(
        to_vehicle_from_mav_type(MAV_TYPE_VTOL_TAILSITTER_QUADROTOR),
        Vehicle::VtolTailsitterQuadrotor);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_VTOL_FIXEDROTOR), Vehicle::VtolFixedrotor);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_VTOL_TAILSITTER), Vehicle::VtolTailsitter);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_VTOL_TILTWING), Vehicle::VtolTiltwing);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_PARAFOIL), Vehicle::Parafoil);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_DODECAROTOR), Vehicle::Dodecarotor);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_DECAROTOR), Vehicle::Decarotor);
    EXPECT_EQ(to_vehicle_from_mav_type(MAV_TYPE_PARACHUTE), Vehicle::Parachute);
}

TEST(Vehicle, StreamOperatorAllKnownLabels)
{
    const std::pair<Vehicle, const char*> cases[] = {
        {Vehicle::Unknown, "Unknown"},
        {Vehicle::Generic, "Generic"},
        {Vehicle::FixedWing, "FixedWing"},
        {Vehicle::Quadrotor, "Quadrotor"},
        {Vehicle::Coaxial, "Coaxial"},
        {Vehicle::Helicopter, "Helicopter"},
        {Vehicle::Airship, "Airship"},
        {Vehicle::FreeBalloon, "FreeBalloon"},
        {Vehicle::Rocket, "Rocket"},
        {Vehicle::GroundRover, "GroundRover"},
        {Vehicle::SurfaceBoat, "SurfaceBoat"},
        {Vehicle::Submarine, "Submarine"},
        {Vehicle::Hexarotor, "Hexarotor"},
        {Vehicle::Octorotor, "Octorotor"},
        {Vehicle::Tricopter, "Tricopter"},
        {Vehicle::FlappingWing, "FlappingWing"},
        {Vehicle::Kite, "Kite"},
        {Vehicle::VtolTailsitterDuorotor, "VtolTailsitterDuorotor"},
        {Vehicle::VtolTailsitterQuadrotor, "VtolTailsitterQuadrotor"},
        {Vehicle::VtolTiltrotor, "VtolTiltrotor"},
        {Vehicle::VtolFixedrotor, "VtolFixedrotor"},
        {Vehicle::VtolTailsitter, "VtolTailsitter"},
        {Vehicle::VtolTiltwing, "VtolTiltwing"},
        {Vehicle::Parafoil, "Parafoil"},
        {Vehicle::Dodecarotor, "Dodecarotor"},
        {Vehicle::Decarotor, "Decarotor"},
        {Vehicle::Parachute, "Parachute"},
        {Vehicle::GenericMultirotor, "GenericMultirotor"},
    };
    for (const auto& c : cases) {
        std::ostringstream oss;
        oss << c.first;
        EXPECT_EQ(oss.str(), c.second) << "vehicle label mismatch";
    }
}
