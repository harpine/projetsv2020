#include "PetriDish.hpp"
#include "Nutriment.hpp"
#include "Bacterium.hpp"
#include "Swarm.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"
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
     temperature_(getAppConfig()["petri dish"]["temperature"]["default"].toDouble()),
     exponent_((getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble()
                + getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble()) / 2),
     bacteriaExponent_(getAppConfig()["petri dish"]["gradient"]["bacteria exponent"].toDouble())
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
    for (auto swarm: swarms_)
    {
        if (swarm->getId() == id)
        {
            return swarm;
        }
    }

    return nullptr;
}

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
        bacterium = nullptr; //c'est surtout important pour la gestion des swarms
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
        nutriment = nullptr;
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

//Autres méthodes:
Nutriment* PetriDish::getNutrimentColliding(const CircularBody& body) const
{
    for (auto& nutriment : nutriments_)
    {
        if (nutriment != nullptr)
        {
            if (nutriment->isColliding(body))
            {
                return nutriment;
            }

        }
    }

    return nullptr;
}

Bacterium* PetriDish::getBacteriumColliding(const CircularBody& body) const
{
    for (auto& bacterium : bacteria_)
    {
        if (bacterium != nullptr)
        {
            if (bacterium->isColliding(body))
            {
                if (bacterium->getEnergyForScore() != 0)
                //Permet d'éviter de sélectionner une madbactérie (dont getEnergyScore vaut 0)
                //car cela stoppe l'itération et la madbacterium est incapable de manger une bactérie
                //sous-jacente si elle est en meme temps en contact avec une autre madbacterium.
                //Si une autre bactérie a une énergie de 0, elle sera éliminé de toute manière donc
                //ça ne pose pas de problème
                {
                    return bacterium;
                }
            }
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

    resetTemperature();
    resetGradientExponent();
}

//Pour la température:
void PetriDish::increaseTemperature()
{
    temperature_ += getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
}

void PetriDish::decreaseTemperature()
{
  temperature_ -= getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
}

void PetriDish::resetTemperature()
{
    temperature_ = getAppConfig()["petri dish"]["temperature"]["default"].toDouble();
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

double PetriDish::getPositionBacteriaScore(const Vec2d& p) const
{
    double score(0);

    for (auto& bacterium : bacteria_)
    {
        if (bacterium != nullptr)
        {
            if (distance (p, bacterium->getPosition()) > 0)
            {
                score += bacterium->getEnergyForScore() / std::pow((distance(p, bacterium->getPosition())), bacteriaExponent_);
                //getEnergyForScore() est polymorphique et permet d'adapter la sensibilité du score au type de bactérie concerné.
                //Une MadBacterium ne sera donc pas sensible à d'autres MadBacterium, peu sensible aux SwarmBacterium...
            }
        }
    }

    return score;
}

void PetriDish::increaseGradientExponent()
{
    exponent_ += getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
}

void PetriDish::decreaseGradientExponent()
{
    exponent_ -= getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
}

void PetriDish::resetGradientExponent()
{
    exponent_ = (getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble() + getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble()) / 2;
}

//Pour les statistiques:
std::unordered_map<std::string, double> PetriDish::fetchData(const std::string & title) const
{
    if (title == s::GENERAL)
    {
        int simple(SimpleBacterium::getCompteur());
        int twitching(TwitchingBacterium::getCompteur());
        int swarmbact(SwarmBacterium::getCompteur());
        int nutriment(Nutriment::getCompteur());
        std::unordered_map<std::string, double> new_data;
        new_data = {{"simple bacteria", simple}, {"twitching bacteria", twitching},
                    {"swarm bacteria", swarmbact},{"nutriment sources", nutriment},
                    {"temperature", temperature_}};
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
        new_data = {{"nutriment quantity", totalQuantity}};
        return new_data;
    }
    else if (title == s::SIMPLE_BACTERIA)
    {
        double averagebetter(SimpleBacterium::getAverageBetter());
        double averageworse(SimpleBacterium::getAverageWorse());
        return std::unordered_map<std::string, double>({{"tumble better prob", averagebetter},{"tumble worse prob", averageworse}});
    }
    else if (title == s::TWITCHING_BACTERIA)
    {
        double tentacleLength(TwitchingBacterium::getAverageTentacleLength());
        double tentacleSpeed(TwitchingBacterium::getAverageTentacleSpeed());
        return std::unordered_map<std::string, double> ({{"tentacle length", tentacleLength}, {"tentacle speed", tentacleSpeed}});
    }
    else if (title == s::BACTERIA)
    {
        double speed(0);
        if (SimpleBacterium::getCompteur() + SwarmBacterium::getCompteur() + TwitchingBacterium::getCompteur() != 0)
        {
            speed = (SimpleBacterium::getTotalSpeed() + SwarmBacterium::getTotalSpeed() + TwitchingBacterium::getTotalSpeed()) /
                         (SimpleBacterium::getCompteur() + SwarmBacterium::getCompteur() + TwitchingBacterium::getCompteur());
        }

        return std::unordered_map<std::string, double>({{"speed", speed}});
    }
    return std::unordered_map<std::string,double>();
}

