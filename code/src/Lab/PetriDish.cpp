#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Utility/Vec2d.hpp"
#include "Utility/Utility.hpp"
#include "../Application.hpp"
#include "Nutriment.hpp"
#include "Bacterium.hpp"
#include <cmath>
#include <iostream> //à enlever

PetriDish::PetriDish(const Vec2d& poscenter, const double radius)
    : CircularBody(poscenter, radius),
     temperature_(getAppConfig()["petri dish"]["temperature"]["default"].toDouble()),
     exponent_((getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble() + getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble()) / 2)
{}

PetriDish::~PetriDish()
{
    reset();
}

double PetriDish::getTemperature() const
{
    return temperature_;
}

double PetriDish::getGradientExponent() const
{
    return exponent_;
}

bool PetriDish::addBacterium(Bacterium* bacterium)
{
    if (contains(*bacterium))
    {
        bacteria_.push_back(bacterium);
        return true;
    }
    return false;
}

bool PetriDish::addNutriment(Nutriment* nutriment)
{
    if (contains(*nutriment))
    {
        nutriments_.push_back(nutriment);
        return true;
    }
    return false;
}

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


void PetriDish::update(sf::Time dt)
{
    for (auto& nutriment : nutriments_)
    {
        nutriment->update(dt);
        if ((*nutriment).depleted())
        {
            delete nutriment;
            nutriment = nullptr; 
        }
    }
    nutriments_.erase(std::remove(nutriments_.begin(), nutriments_.end(), nullptr), nutriments_.end());
    append(cloned_,bacteria_);

    for (auto& clone : cloned_)
    {
        clone = nullptr;
    }

    cloned_.erase(std::remove(cloned_.begin(), cloned_.end(), nullptr), cloned_.end());
    for (auto& bacterium : bacteria_)
    {
        bacterium->update(dt);
        if (bacterium->death())
        {
            delete bacterium;
            bacterium = nullptr;
        }
    }
    bacteria_.erase(std::remove(bacteria_.begin(), bacteria_.end(), nullptr), bacteria_.end());
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
    resetTemperature();
    resetGradientExponent();
}

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

void PetriDish::addClone(Bacterium* bacterium)
{
    if (bacterium != nullptr)
    {
        cloned_.push_back(bacterium);
    }
}

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




















