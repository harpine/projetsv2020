#include "Lab.hpp"
#include "PetriDish.hpp"
#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <sstream>

//Constructeur:
Lab::Lab()
    :petridish_(getApp().getCentre(), (getApp().getLabSize().x * 0.95)/2)
    /*Positonne l'assiette de pétri au centre de la fenêtre graphique
    avec un diamètre occupant 95% de la largeur de la fenêtre */
{}

//Getters:
Vec2d Lab::getCenter() const
{
    return petridish_.getPosition();
}

Swarm* Lab::getSwarmWithId(std::string id) const
{
    return petridish_.getSwarmWithId(id);
}

//Autres méthodes:
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

Bacterium* Lab::getBacteriumColliding(const CircularBody& body) const
{
    return petridish_.getBacteriumColliding(body);
}

Poison* Lab::getPoisonColliding(const CircularBody &body) const
{
    return petridish_.getPoisonColliding(body);
}

Spray* Lab::getSprayColliding(const CircularBody& body) const
{
    return petridish_.getSprayColliding(body);
}
void Lab::setTime(const sf::Time toAdd)
{
    time_ += toAdd;
}

void Lab::drawOn(sf::RenderTarget& targetWindow) const
{
    petridish_.drawOn(targetWindow);
    drawOnTime(targetWindow);
}

void Lab::update(sf::Time dt)
{
    nutrimentGenerator_.update(dt);
    petridish_.update(dt);
}

void Lab::reset()
{
    nutrimentGenerator_.reset();
    petridish_.reset();
    time_ = sf::Time::Zero;
}

void Lab::resetControls()
{
    resetTemperature();
    resetGradientExponent();
}

//Ajouts:
void Lab::addNutriment(Nutriment* nutriment)
{
    petridish_.addNutriment(nutriment);
}

void Lab::addBacterium(Bacterium* bacterium)
{
    petridish_.addBacterium(bacterium);
}

void Lab::addSwarm(Swarm *swarm)
{
    petridish_.addSwarm(swarm);
}

void Lab::addPoison(Poison *poison)
{
    petridish_.addPoison(poison);
}

void Lab::addSpray(Spray *spray)
{
    petridish_.addSpray(spray);
}

//Pour la température:
double Lab::getTemperature() const
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

//Pour le score de la position
double Lab::getPositionScore(const Vec2d& p) const
{
    return petridish_.getPositionScore(p);
}

double Lab::getPositionBacteriaScore(const Vec2d& p) const
{
    return petridish_.getPositionBacteriaScore(p);
}

double Lab::getGradientExponent() const
{
    return petridish_.getGradientExponent();
}

void Lab::increaseGradientExponent()
{
    petridish_.increaseGradientExponent();
}

void Lab::decreaseGradientExponent()
{
    petridish_.decreaseGradientExponent();
}

void Lab::resetGradientExponent()
{
    petridish_.resetGradientExponent();
}

//Pour les statistiques:
std::unordered_map<std::string, double> Lab::fetchData(const std::string & title) const
{
    return petridish_.fetchData(title);
}

//Private:
void Lab::drawOnTime(sf::RenderTarget& targetWindow) const
{
    int minutes(time_.asSeconds()/60);
    int seconds(int(time_.asSeconds())%60);
    std::stringstream timeprinted;
    timeprinted << std::setw(2) << std::setfill('0') << minutes << " : " << std::setw(2) << std::setfill('0') << seconds;
    sf::Text const texte = buildText("Time :  " + timeprinted.str(),
                        Vec2d(10,10), getAppFont(), 30, sf::Color::Red);
    targetWindow.draw(texte);
}
