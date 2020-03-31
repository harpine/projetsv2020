#include "SimpleBacterium.hpp"
#include "../Application.hpp"
#include "Random/Random.hpp"
#include <cmath>
#include <Utility/Vec2d.hpp>
#include <Utility/DiffEqSolver.hpp>


SimpleBacterium::SimpleBacterium(const Vec2d& poscenter)
    :Bacterium(uniform(getConfig()["energy"]["max"].toDouble(),
      getConfig()["energy"]["min"].toDouble()),
     poscenter,
     Vec2d::fromRandomAngle(),
     uniform(getConfig()["radius"]["max"].toDouble(),
      getConfig()["radius"]["min"].toDouble()),
     getConfig()["color"])
{
    addProperty("speed",MutableNumber(getSpeedConfig()["initial"].toDouble(),
            getSpeedConfig()["rate"].toDouble(), getSpeedConfig()["sigma"].toDouble(), 1));

    addProperty("tumble better",MutableNumber(getBetterConfig()["initial"].toDouble(),
                getBetterConfig()["rate"].toDouble(), getBetterConfig()["sigma"].toDouble(), 1));

    addProperty("tumble worse",MutableNumber(getWorseConfig()["initial"].toDouble(),
                getWorseConfig()["rate"].toDouble(), getWorseConfig()["sigma"].toDouble(), 1));
}

j::Value& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}
j::Value& SimpleBacterium::getSpeedConfig() const
{
    return getConfig()["speed"];
}

j::Value& SimpleBacterium::getWorseConfig() const
{
    return getConfig()["tumble"]["worse"];
}

j::Value& SimpleBacterium::getBetterConfig() const
{
    return getConfig()["tumble"]["better"];
}

//Méthodes:

Vec2d SimpleBacterium::f(Vec2d position, Vec2d speed) const
{
    return Vec2d(); //constructeur par défaut renvoie le vecteur nul
}

void SimpleBacterium::move(sf::Time dt)
{
    DiffEqResult result(stepDiffEq(getPosition(), getSpeedVector(), dt,
               *this));
    //this est une DiffEqFunction
    if ((result.position- getPosition()).lengthSquared() > 0.001)
    {
        setPosition(result.position);
    }

    consumeEnergy(getDisplacementEnergy()* distance(result.position, getPosition()));
    //distance renvoie length des 2 Vec2d
}

Vec2d SimpleBacterium::getSpeedVector() const
{
    return getDirection() * getProperty("speed").get();
}

Bacterium* SimpleBacterium::copie()
{
    return new SimpleBacterium(*this);
}
