#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Utility/Vec2d.hpp"
#include "Utility/Utility.hpp"
#include "../Application.hpp"
#include "Nutriment.hpp"

PetriDish::PetriDish(const Vec2d& poscenter, const double radius)
    : CircularBody(poscenter, radius),
     temperature_(getAppConfig()["petri dish"]["temperature"]["default"].toDouble())
{}

PetriDish::~PetriDish()
{
    reset();
}

double PetriDish::getTemperature()
{
    return temperature_;
}

bool PetriDish::addBacterium(Bacterium* bacterium)
{
    bacteria_.push_back(bacterium);
    //Conditions à ajouter
    return true;
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

void PetriDish::update(sf::Time dt)
{
    for (auto nutriment : nutriments_)
    {
       (*nutriment).update(dt);
    }
    //A remplir : fonciton qui fait evoluer toutes les bacteries/nutriments)
    //à chaque pas de temps
}

void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    auto border = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5);
    targetWindow.draw(border);
    for (size_t i(0); i< nutriments_.size(); ++i)
    {
        //à décommenter plus tard
        //nutriments_[i]->update();
        nutriments_[i]->drawOn(targetWindow);
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
























