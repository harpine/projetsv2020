#include "../Utility/MutableNumber.hpp"
#include "SimpleBacterium.hpp"
#include <Application.hpp>
#include <Random/Random.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Utility/DiffEqSolver.hpp>

//Constructeur:
SimpleBacterium::SimpleBacterium(const Vec2d& poscenter)
    :Bacterium(uniform(getConfig()["energy"]["max"].toDouble(),
      getConfig()["energy"]["min"].toDouble()),
     poscenter,
     Vec2d::fromRandomAngle(),
     uniform(getConfig()["radius"]["max"].toDouble(),
      getConfig()["radius"]["min"].toDouble()),
     getConfig()["color"]),
     t_flagelle_(uniform(0.0, PI)),
     probability_()
{
    addProperty("speed", MutableNumber::positive(getSpeedConfig()["initial"].toDouble(),
                getSpeedConfig()["rate"].toDouble(), getSpeedConfig()["sigma"].toDouble()));

    addProperty("tumble better",MutableNumber::positive(getBetterConfig()["initial"].toDouble(),
                getBetterConfig()["rate"].toDouble(), getBetterConfig()["sigma"].toDouble()));

    addProperty("tumble worse",MutableNumber::positive(getWorseConfig()["initial"].toDouble(),
                getWorseConfig()["rate"].toDouble(), getWorseConfig()["sigma"].toDouble()));
}

//Getters:
j::Value& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}

j::Value& SimpleBacterium::getWorseConfig() const
{
    return getConfig()["tumble"]["worse"];
}

j::Value& SimpleBacterium::getBetterConfig() const
{
    return getConfig()["tumble"]["better"];
}

Vec2d SimpleBacterium::getSpeedVector() const
{
    return getDirection().normalised() * getProperty("speed").get();
}

//Autres méthodes:
Vec2d SimpleBacterium::f(Vec2d position, Vec2d speed) const
{
    return Vec2d(); //constructeur de Vec2d par défaut renvoie le vecteur nul
}

void SimpleBacterium::move(sf::Time dt)
{
    DiffEqResult result(stepDiffEq(getPosition(), getSpeedVector(), dt,
               *this));
    //this est une DiffEqFunction
    consumeEnergy(getDisplacementEnergy()* distance(result.position, getPosition()));
    //distance renvoie length des 2 Vec2d

    if ((result.position - getPosition()).lengthSquared() > 0.001)
    {
        this->CircularBody::move((result.position - getPosition()));
        //move est moins intuitif mais meilleur pour la hiérarchie des classes
    }

    if(tumbleAttempt(dt))
    {
        tumble();
    }
}

bool SimpleBacterium::tumbleAttempt(sf::Time dt)
{
    double lambda(0);
    double ancien_score(score_);
    score_ = getAppEnv().getPositionScore(getPosition());
    tumbleClock_ += dt;

    if (score_ >= ancien_score)
    {
        lambda = getProperty("tumble better").get();
    }
    else
    {
        lambda = getProperty("tumble worse").get();
    }

    probability_ = 1 - exp(-tumbleClock_.asSeconds()/lambda);
    return bernoulli(probability_);
}

void SimpleBacterium::tumble()
{
    if (getConfig()["tumble"]["algo"] == "single random vector")
    {
        setDirection(Vec2d::fromRandomAngle());
    }
    else if(getConfig()["tumble"]["algo"] == "best of 20")
    {
        Vec2d direction(getDirection());
        Vec2d finalDirection(getDirection());
        double score(score_);

        for (int i(0); i <20 ; ++i)
        {
            direction = Vec2d::fromRandomAngle();

            if (getAppEnv().getPositionScore(getPosition()+direction) > score)
            {
                score = getAppEnv().getPositionScore(getPosition()+direction);
                finalDirection = direction;
            }
        }
        setDirection(finalDirection.normalised());
    }
    tumbleClock_ = sf::Time::Zero;
}

void SimpleBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);
    drawOnFlagelle(target);
}

void SimpleBacterium::drawOnFlagelle(sf::RenderTarget &target) const
{
    auto flagelle = sf::VertexArray(sf::TrianglesStrip);
    flagelle.append({{0, 0}, getColor().get()});
    for (int i(1); i <= 30 ; ++i)
    {
        float x(-i * getRadius() / 10.0);
        float y(getRadius() * std::sin(t_flagelle_) * std::sin(2 * i / 10.0));
        flagelle.append({{x, y}, getColor().get()});
        flagelle.append({{x+2, y-2}, getColor().get()});
    }

    auto transform = sf::Transform();
    transform.translate(getPosition());
    transform.rotate(getAngle() / DEG_TO_RAD);
    target.draw(flagelle, transform);
}

void SimpleBacterium::update(sf::Time dt)
{
    Bacterium::update(dt);
    updateFlagelle(dt);
}

void SimpleBacterium::updateFlagelle(sf::Time dt)
{
    t_flagelle_ += 3 * dt.asSeconds();

    auto const angleDiff = angleDelta(getDirection().angle(), getAngle()); //en radian
    auto dalpha = PI * dt.asSeconds();
    // calcule dα en radian
    dalpha = std::min(dalpha, std::abs(angleDiff));
    //on ne peut tourner de plus que dalpha
    dalpha = std::copysign(dalpha, angleDiff);
    // on tourne dans la direction indiquée par angleDiff
    setAngle(getAngle() + dalpha);
    //mise à jour de l'angle de rotation
}

Bacterium* SimpleBacterium::copie()
{
    return new SimpleBacterium(*this);
}
