#include "Lab.hpp"
#include "../Application.hpp"
#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>

Lab::Lab()
    :petridish_(getApp().getCentre(), (getApp().getLabSize().x * 0.95)/2)
    /*Positonne l'assiette de pétri au centre de la fenêtre graphique
    avec un diamètre occupant 95% de la largeur de la fenêtre */
{}

bool Lab::contains(const CircularBody& circularbody) const
{
    if (petridish_.contains(circularbody))
    {
        return true;
    }
    return false;
}


void Lab::drawOn(sf::RenderTarget& targetWindow) const
{
    petridish_.drawOn(targetWindow);
}

void Lab::update(sf::Time dt)
{
    petridish_.update(dt);
}

void Lab::reset()
{
    petridish_.reset();
}

void Lab::addNutriment(Nutriment* nutriment)
{
    petridish_.addNutriment(nutriment);
}

double Lab::getTemperature()
{
    return petridish_.getTemperature();
}


 void Lab::increaseTemperature()
{
    petridish_.increaseTemperature();
}

void Lab::decreaseTemperature()
{
    petridish_.decreaseTemperature();
}
