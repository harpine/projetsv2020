#include "SwarmBacterium.hpp"
#include "CircularBody.hpp"
#include "Swarm.hpp"
#include "Nutriment.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Vec2d.hpp>
#include <Random/Random.hpp>

int SwarmBacterium::compteur_ = 0;
double SwarmBacterium::totalspeed_ = 0;

//Constructeur et destructeur:
SwarmBacterium::SwarmBacterium(const Vec2d& poscenter, Swarm*& swarm)
    :Bacterium(uniform(getConfig()["energy"]["max"].toDouble(),
     getConfig()["energy"]["min"].toDouble()),
     poscenter,
     Vec2d::fromRandomAngle(),
     uniform(getConfig()["radius"]["max"].toDouble(),
     getConfig()["radius"]["min"].toDouble()),
     swarm->getInitialColor()),
     swarm_(swarm)
{
    swarm_->addSwarmBacterium(this);
    totalspeed_ += getSpeedVector().length();
    compteur_ += 1;
}

SwarmBacterium::~SwarmBacterium()
{
    swarm_->removeSwarmBacterium(this);
    totalspeed_ -= getSpeedVector().length();
    compteur_ -= 1;
}

SwarmBacterium::SwarmBacterium(const SwarmBacterium& other)
    :Bacterium(other),
      swarm_(other.swarm_)
{
    totalspeed_ += getSpeedVector().length();
    compteur_ += 1;
}

void SwarmBacterium::updateStats()
{
    //vide car pas de paramètre mutable à mettre à jour
}

//Getters:
j::Value& SwarmBacterium::getConfig() const
{
    return getAppConfig()[s::SWARM_BACTERIUM];
}

Vec2d SwarmBacterium::getSpeedVector() const
{
    return getDirection().normalised() * getSpeedConfig()["initial"].toDouble();
}

int SwarmBacterium::getCompteur()
{
    return compteur_;
}

double SwarmBacterium::getTotalSpeed()
{
    return totalspeed_;
}

//Autres méthodes:
Bacterium* SwarmBacterium::copie()
{
    SwarmBacterium* newSwarmBacterium(new SwarmBacterium(*this));
    swarm_->addSwarmBacterium(newSwarmBacterium);
    return newSwarmBacterium;
}

void SwarmBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);

    if (isDebugOn() and swarm_->isLeader(this))
    {
        auto border = buildAnnulus(getPosition(), getRadius() + 20, sf::Color::Red, 3);
        target.draw(border);
        swarm_->drawDebug(target); //lignes entre bactéries d'un même swarm
    }
}

void SwarmBacterium::move(sf::Time dt)
{
    DiffEqResult result(stepDiffEq(getPosition(), getSpeedVector(), dt, *this));
    //this est une DiffEqFunction
    consumeEnergy(getDisplacementEnergy()* distance(result.position, getPosition()));
    //distance renvoie length des 2 Vec2d

    if ((result.position - getPosition()).lengthSquared() > 0.001)
    {
        this->CircularBody::move((result.position - getPosition()));
        //move est moins intuitif mais meilleur pour la hiérarchie des classes
    }

    if (swarm_->isLeader(this))
    {
        bestOfN(20);
    }
}

Vec2d SwarmBacterium::f(Vec2d position, Vec2d speed) const
{
    if (swarm_->hasNoLeader())
    {
        return Vec2d();
    }

    return (swarm_->getConfig()[swarm_->getId()]["force factor"].toDouble() *
            (swarm_->getPositionLeader() - position));
}

Quantity SwarmBacterium::eatableQuantity(NutrimentA& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity SwarmBacterium::eatableQuantity(NutrimentB& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity SwarmBacterium::eatablePoison(Poison& poison)
{
    return poison.eatenBy(*this);
}
