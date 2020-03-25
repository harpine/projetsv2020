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
    return petridish_.contains(circularbody);
}

bool Lab::doesCollideWithDish(const CircularBody& body) const
{
    return !petridish_.contains(body);
    //Sachant que la bactérie créée est forcément dans l'assiette de
    //petri, si elle n'est plus contenue, cela signifie qu'elle entre
    //en collision avec les parois de l'assiette.
}

Nutriment* Lab::getNutrimentColliding(const CircularBody& body) const
{
    return petridish_.getNutrimentColliding(body);
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

void Lab::addBacterium(Bacterium* bacterium)
{
    petridish_.addBacterium(bacterium);
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

void Lab::resetTemperature()
{
    petridish_.resetTemperature();
}
