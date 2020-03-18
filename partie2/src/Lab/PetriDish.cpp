#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Utility/Vec2d.hpp"
#include "Utility/Utility.hpp"

PetriDish::PetriDish(const Vec2d& poscenter, const double radius)
    : CircularBody(poscenter, radius)
{}

PetriDish::~PetriDish()
{
    reset();
}



bool PetriDish::addBacterium(Bacterium* bacterium)
{
    bacteria_.push_back(bacterium);
    //Conditions à ajouter
}

bool PetriDish::addNutriment(Nutriment* nutriment)
{
    nutriments_.push_back(nutriment);

}

void PetriDish::update(sf::Time dt)
{
    //A remplir : fonciton qui fait evoluer toutes les bacteries/nutriments)
    //à chaque pas de temps
}

void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    auto border = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5);
    targetWindow.draw(border);
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
}



























