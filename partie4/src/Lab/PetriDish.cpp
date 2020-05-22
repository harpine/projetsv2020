#include "PetriDish.hpp"
#include "Nutriment.hpp"
#include "Bacterium.hpp"
#include "Swarm.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>
#include <cmath>

//Constructeur et destructeur:
PetriDish::PetriDish(const Vec2d& poscenter, const double radius)
    : CircularBody(poscenter, radius),
      temperature_(getAppConfig()["petri dish"]["temperature"]["default"].toDouble()),
      exponent_((getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble()
                 + getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble()) / 2)
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
    for (auto swarm: swarms_) {
        if (swarm->getId() == id) {
            return swarm;
        }
    }

    return nullptr;
}

//Ajouts:
bool PetriDish::addBacterium(Bacterium* bacterium)
{
    if (bacterium != nullptr) {
        if (contains(*bacterium)) {
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
    if (nutriment != nullptr) {
        if (contains(*nutriment)) {
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
    if (swarm != nullptr) {
        swarms_.push_back(swarm);
    }
}

//Autres méthodes:
Nutriment* PetriDish::getNutrimentColliding(const CircularBody& body) const
{
    for (auto& nutriment : nutriments_) {
        if (nutriment->isColliding(body)) {
            return nutriment;
        }
    }

    return nullptr;
}

void PetriDish::update(sf::Time dt)
{
    for (auto& nutriment : nutriments_) {
        nutriment->update(dt);

        if ((*nutriment).isDepleted()) {
            delete nutriment;
            nutriment = nullptr;
        }
    }

    nutriments_.erase(std::remove(nutriments_.begin(), nutriments_.end(), nullptr), nutriments_.end());

    std::vector<Bacterium*> cloned;

    for (auto& bacterium : bacteria_) {
        bacterium->update(dt);
        cloned.push_back(bacterium->clone());
        if (bacterium->isDead()) {
            delete bacterium;
            bacterium = nullptr;
        }
    }

    append(cloned, bacteria_);
    cloned.clear();

    bacteria_.erase(std::remove(bacteria_.begin(), bacteria_.end(), nullptr), bacteria_.end());

    for (auto& swarm: swarms_) {
        swarm->updateLeader();
    }
}

void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    auto border = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5);
    targetWindow.draw(border);

    for (size_t i(0); i< nutriments_.size(); ++i) {
        nutriments_[i]->drawOn(targetWindow);
    }
    for (size_t i(0); i< bacteria_.size(); ++i) {
        bacteria_[i]->drawOn(targetWindow);
    }

}

void PetriDish::reset()
{
    //Désalloue la mémoire occupée par les bactéries, puis vide l'ensemble des bactéries.
    for (auto& bacterium : bacteria_) {
        delete bacterium;
    }
    bacteria_.clear();

    //Désalloue la mémoire occupée par les nutriments, puis vide l'ensemble des nutriments.
    for (auto& nutriment : nutriments_) {
        delete nutriment;
    }
    nutriments_.clear();

    for (auto& swarm : swarms_) {
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

    for (auto& nutriment : nutriments_) {
        score += nutriment->getQuantity() / std::pow((distance(p, nutriment->getPosition())), exponent_);
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
