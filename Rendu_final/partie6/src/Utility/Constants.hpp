/*
 * prjsv 2015
 * 2014
 * Marco Antognini
 */

#ifndef INFOSV_CONSTANTS_HPP
#define INFOSV_CONSTANTS_HPP

#include <string>

// Numerical constants
double const DEG_TO_RAD = 0.0174532925; ///< Degree to Radian conversion constant
double const TAU = 6.283185307;         ///< TAU constant (= 2 * PI)
double const PI = 3.141592654;          ///< PI constant
double const EPSILON = 1e-8;            ///< a small epsilon value

// Stats titles
namespace s
{

std::string const GENERAL = "general";
std::string const SIMPLE_BACTERIA = "simple bacteria";
std::string const TWITCHING_BACTERIA = "twitching bacteria";
std::string const TWITCHING_BACTERIUM = "twitching bacterium";
std::string const SWARM_BACTERIA = "swarm bacteria";
std::string const SWARM_BACTERIUM = "swarm bacterium"; //ajouté par nous
std::string const POISONOUS_BACTERIUM = "poisonous bacterium";
std::string const POISONOUS_BACTERIA = "poisonous bacteria";
std::string const MAD_BACTERIA = "mad bacteria";
std::string const MAD_BACTERIUM = "mad bacterium";
std::string const BACTERIA = "bacteria";
std::string const SPEED = "speed";
std::string const BETTER = "tumble better prob";
std::string const WORSE = "tumble worse prob";
std::string const NUTRIMENT_QUANTITY = "nutriment quantity";
std::string const NUTRIMENT_SOURCES = "nutriment sources";
std::string const TENTACLE_LENGTH = "tentacle length";
std::string const TENTACLE_SPEED = "tentacle speed";
std::string const DISH_TEMPERATURE = "temperature";
std::string const PETRI_DISH = "petri dish"; //ajouté par nous
std::string const POISON = "poison"; //ajouté par nous

} // s

#endif // INFOSV_CONSTANTS_HPP
