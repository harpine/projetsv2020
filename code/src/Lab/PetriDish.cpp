#include "PetriDish.hpp"
#include "Nutriment.hpp"
#include "Bacterium.hpp"
#include "Swarm.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "PoisonousBacterium.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>
#include <cmath>
#include <string>

//Constructeur et destructeur:
PetriDish::PetriDish(const Vec2d& poscenter, const double radius)
    : CircularBody(poscenter, radius),
     temperature_(getAppConfig()[s::PETRI_DISH][s::DISH_TEMPERATURE]["default"].toDouble()),
     exponent_((getAppConfig()[s::PETRI_DISH]["gradient"]["exponent"]["max"].toDouble()
                + getAppConfig()[s::PETRI_DISH]["gradient"]["exponent"]["min"].toDouble()) / 2)
{}

PetriDish::~PetriDish()
{
    reset();
}

//Getters:
double PetriDish::getTemperature() const
{
    return temperature_;
}

double PetriDish::getGradientExponent() const
{
    return exponent_;
}

Swarm* PetriDish::getSwarmWithId(const std::string& id) const
{
    return *(std::find_if(swarms_.begin(), swarms_.end(), [id](Swarm* swarm){return swarm->getId() == id;}));
 }
//    for (auto swarm: swarms_)
//    {
//        if (swarm->getId() == id)
//        {
//            return swarm;
//        }
//    }

//    return nullptr;
//}

//Ajouts:
bool PetriDish::addBacterium(Bacterium* bacterium)
{
    if (bacterium != nullptr)
    {
        if (contains(*bacterium))
        {
            bacteria_.push_back(bacterium);
            return true;
        }

        delete bacterium;   //permet d'éviter d'avoir des bactéries "inertes" qui traînent hors de la boîte de petri
                            //c'est surtout important pour la gestion des swarms
    }

    return false;
}

bool PetriDish::addNutriment(Nutriment* nutriment)
{
    if (nutriment != nullptr)
    {
        if (contains(*nutriment))
        {
            nutriments_.push_back(nutriment);
            return true;
        }

        delete nutriment;
    }

    return false;
}

void PetriDish::addSwarm(Swarm *swarm)
{
    if (swarm != nullptr)
    {
        swarms_.push_back(swarm);
    }
}

void PetriDish::addPoison(Poison *poison)
{
    if (poison!= nullptr)
    {
        poisons_.push_back(poison);
    }
}

//Autres méthodes:
Nutriment* PetriDish::getNutrimentColliding(const CircularBody& body) const
{
    for (auto& nutriment : nutriments_)
    {
        if (nutriment->isColliding(body))
        {
            return nutriment;
        }
    }

    return nullptr;
}

Poison* PetriDish::getPoisonColliding(const CircularBody& body) const
{
    for (auto& poison : poisons_)
    {
        if (poison->isColliding(body))
        {
            return poison;
        }
    }

    return nullptr;
}

void PetriDish::update(sf::Time dt)
{
    for (auto& nutriment : nutriments_)
    {
        nutriment->update(dt);

        if ((*nutriment).isDepleted())
        {
            delete nutriment;
            nutriment = nullptr;
        }
    }

    nutriments_.erase(std::remove(nutriments_.begin(), nutriments_.end(), nullptr), nutriments_.end());

    std::vector<Bacterium*> cloned;

    for (auto& bacterium : bacteria_)
    {
        bacterium->update(dt);
        cloned.push_back(bacterium->clone());

        if (bacterium->isDead())
        {
            delete bacterium;
            bacterium = nullptr;
        }
    }

    append(cloned, bacteria_);
    cloned.clear();

    bacteria_.erase(std::remove(bacteria_.begin(), bacteria_.end(), nullptr), bacteria_.end());

    for (auto& swarm: swarms_)
    {
        swarm->updateLeader();
    }

    for (auto& poison: poisons_)
    {
        if (poison->iseaten())
        {
            delete poison;
            poison = nullptr;
        }
    }
    poisons_.erase(std::remove(poisons_.begin(), poisons_.end(), nullptr), poisons_.end());
}

void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    auto border = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5);
    targetWindow.draw(border);

    for (size_t i(0); i< nutriments_.size(); ++i)
    {
        nutriments_[i]->drawOn(targetWindow);
    }
    for (size_t i(0); i< bacteria_.size(); ++i)
    {
        bacteria_[i]->drawOn(targetWindow);
    }
    for (size_t i(0); i< poisons_.size(); ++i)
    {
        poisons_[i]->drawOn(targetWindow);
    }
}

void PetriDish::reset()
{
    //Désalloue la mémoire occupée par les bactéries, puis vide l'ensemble des bactéries.
    for (auto& bacterium : bacteria_)
    {
        delete bacterium;
    }
    bacteria_.clear();

    //Désalloue la mémoire occupée par les nutriments, puis vide l'ensemble des nutriments.
    for (auto& nutriment : nutriments_)
    {
        delete nutriment;
    }
    nutriments_.clear();

    for (auto& swarm : swarms_)
    {
        delete swarm;
    }
    swarms_.clear();

    for(auto& poison: poisons_)
    {
        delete poison;
    }
    poisons_.clear();

    resetTemperature();
    resetGradientExponent();
}

//Pour la température:
void PetriDish::increaseTemperature()
{
    temperature_ += getAppConfig()[s::PETRI_DISH][s::DISH_TEMPERATURE]["delta"].toDouble();
}

void PetriDish::decreaseTemperature()
{
  temperature_ -= getAppConfig()[s::PETRI_DISH][s::DISH_TEMPERATURE]["delta"].toDouble();
}

void PetriDish::resetTemperature()
{
    temperature_ = getAppConfig()[s::PETRI_DISH][s::DISH_TEMPERATURE]["default"].toDouble();
}

//Pour le score d'une position:
double PetriDish::getPositionScore(const Vec2d& p) const
{
    double score(0);

    for (auto& nutriment : nutriments_)
    {
        score += nutriment->getQuantity() / std::pow((distance(p, nutriment->getPosition())), exponent_);
    }

    return score;
}

void PetriDish::increaseGradientExponent()
{
    exponent_ += getAppConfig()[s::PETRI_DISH]["gradient"]["exponent"]["delta"].toDouble();
}

void PetriDish::decreaseGradientExponent()
{
    exponent_ -= getAppConfig()[s::PETRI_DISH]["gradient"]["exponent"]["delta"].toDouble();
}

void PetriDish::resetGradientExponent()
{
    exponent_ = (getAppConfig()[s::PETRI_DISH]["gradient"]["exponent"]["max"].toDouble() + getAppConfig()[s::PETRI_DISH]["gradient"]["exponent"]["min"].toDouble()) / 2;
}

//Pour les statistiques:
//?? à modulariser et mettre les string en S::...
std::unordered_map<std::string, double> PetriDish::fetchData(const std::string & title) const
{
    if (title == s::GENERAL)
    {
        int simple(SimpleBacterium::getCompteur());
        int twitching(TwitchingBacterium::getCompteur());
        int swarmbact(SwarmBacterium::getCompteur());
        int nutriment(Nutriment::getCompteur());
        int poisonous(PoisonousBacterium::getCompteur());
        std::unordered_map<std::string, double> new_data;
        new_data = {{s::SIMPLE_BACTERIA, simple}, {s::TWITCHING_BACTERIA, twitching},
                    {s::SWARM_BACTERIA, swarmbact},{s::NUTRIMENT_SOURCES, nutriment},
                    {s::POISONOUS_BACTERIA, poisonous},
                    {s::DISH_TEMPERATURE, temperature_}};
        return new_data;
    }
    else if (title == s::NUTRIMENT_QUANTITY)
    {
        Quantity totalQuantity(0);
        for (auto& nutriment : nutriments_)
        {
            totalQuantity += nutriment->getQuantity();
        }
        std::unordered_map<std::string, double> new_data;
        new_data = {{s::NUTRIMENT_QUANTITY, totalQuantity}};
        return new_data;
    }
    else if (title == s::SIMPLE_BACTERIA)
    {
        double averagebetter(SimpleBacterium::getAverageBetter());
        double averageworse(SimpleBacterium::getAverageWorse());
        return std::unordered_map<std::string, double>({{s::BETTER, averagebetter},{s::WORSE, averageworse}});
    }
    else if (title == s::POISONOUS_BACTERIA)
    {
        double averagebetter(PoisonousBacterium::getAverageBetter());
        double averageworse(PoisonousBacterium::getAverageWorse());
        return std::unordered_map<std::string, double>({{s::BETTER, averagebetter},{s::WORSE, averageworse}});
    }
    else if (title == s::TWITCHING_BACTERIA)
    {
        double tentacleLength(TwitchingBacterium::getAverageTentacleLength());
        double tentacleSpeed(TwitchingBacterium::getAverageTentacleSpeed());
        return std::unordered_map<std::string, double> ({{s::TENTACLE_LENGTH, tentacleLength}, {s::TENTACLE_SPEED, tentacleSpeed}});
    }
    else if (title == s::BACTERIA)
    {
        double speed(0);
        if (SimpleBacterium::getCompteur() + SwarmBacterium::getCompteur() + TwitchingBacterium::getCompteur()
                + PoisonousBacterium::getCompteur()!= 0)
        {
            speed = (SimpleBacterium::getTotalSpeed() + SwarmBacterium::getTotalSpeed() + TwitchingBacterium::getTotalSpeed()
                     + PoisonousBacterium::getTotalSpeed()) /
                         (SimpleBacterium::getCompteur() + SwarmBacterium::getCompteur() + TwitchingBacterium::getCompteur()
                          + PoisonousBacterium::getCompteur());
        }

        return std::unordered_map<std::string, double>({{s::SPEED, speed}});
    }
    return std::unordered_map<std::string,double>();
}

