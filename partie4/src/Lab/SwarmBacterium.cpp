#include "SwarmBacterium.hpp"
#include "CircularBody.hpp"
#include "Swarm.hpp"
#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Vec2d.hpp>
#include <Random/Random.hpp>

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
}

SwarmBacterium::~SwarmBacterium()
{
    swarm_->removeSwarmBacterium(this);
}

//Getters:
j::Value& SwarmBacterium::getConfig() const
{
    return getAppConfig()["swarm bacterium"];
}

Vec2d SwarmBacterium::getSpeedVector() const
{
    return (getDirection().normalised() * getSpeedConfig()["initial"].toDouble());
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
