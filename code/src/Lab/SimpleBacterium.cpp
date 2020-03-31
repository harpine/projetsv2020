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
{}

j::Value& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}

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

    consumeEnergy(getConfig()["energy"]["consumption factor"].toDouble()
            * distance(result.position, getPosition())); //distance renvoie length des 2 Vec2d
}

Vec2d SimpleBacterium::getSpeedVector() const
{
    return getDirection() * 5;
}

void SimpleBacterium::setSpeedVector(const Vec2d& speed)
{
    setDirection(speed);
}

Bacterium* SimpleBacterium::clone() const
{

}
