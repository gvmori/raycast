#include "include/LocalMath.h"

using namespace LocalMath;

double LocalMath::DegToRad(double degrees){
    return (degrees * pi() / 180);
}

double LocalMath::RadToDeg(double degrees){
    return (degrees * 180 / pi());
}

constexpr double LocalMath::pi() { 
    return acos(-1); 
}