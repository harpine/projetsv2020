#include "SwarmBacterium.hpp"
#include <Application.hpp>
#include "CircularBody.hpp"
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Vec2d.hpp>
#include <Random/Random.hpp>
#include "Swarm.hpp"
#include <iostream> //à enlever

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
    std::cerr << "j'fais mon job";
    swarm_->removeSwarmBacterium(this);
}

j::Value& SwarmBacterium::getConfig() const
{
    return getAppConfig()["swarm bacterium"];
}

Vec2d SwarmBacterium::getSpeedVector() const
{
    return (getDirection().normalised() * getConfig()["speed"]["initial"].toDouble());
}

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
    Vec2d speed(getSpeedVector());
    DiffEqResult result(stepDiffEq(getPosition(), getSpeedVector(), dt, *this));
    //this est une DiffEqFunction
    consumeEnergy(getDisplacementEnergy()* distance(result.position, getPosition()));
    //distance renvoie length des 2 Vec2d
    if ((result.position - getPosition()).lengthSquared() > 0.001)
    {
        this->CircularBody::move((result.position - getPosition()));
//        //move est moins intuitif mais meilleur pour la hiérarchie des classes
//        //set vitesse??
    }
    if (swarm_->isLeader(this))
    {
        Vec2d direction(getDirection());
        Vec2d finalDirection(getDirection());
        double score(getAppEnv().getPositionScore(getPosition()));
        for (int i(0); i <=20 ; ++i)
        {
            direction = Vec2d::fromRandomAngle();
            if (getAppEnv().getPositionScore(getPosition()+direction) > score)
            {
                score = getAppEnv().getPositionScore(getPosition()+direction);
                finalDirection = direction;
            }
        }
        setDirection(finalDirection);
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
