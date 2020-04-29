#include "TwitchingBacterium.hpp"
#include "Nutriment.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include <Application.hpp>
#include <Random/Random.hpp>
#include <Utility/Utility.hpp>

int TwitchingBacterium::compteur_ = 0;

//Constructeur:
TwitchingBacterium::TwitchingBacterium(const Vec2d& poscenter)
    :Bacterium(uniform(getConfig()["energy"]["max"].toDouble(),
      getConfig()["energy"]["min"].toDouble()),
      poscenter,
      Vec2d::fromRandomAngle(),
      uniform(getConfig()["radius"]["max"].toDouble(),
      getConfig()["radius"]["min"].toDouble()),
      getConfig()["color"]),
      grip_(poscenter, getRadius()/4),
      mystate_(IDLE)
{
    addProperty("tentacle speed", MutableNumber::positive(getTentacleSpeed()["initial"].toDouble(),
            getTentacleSpeed()["rate"].toDouble(), getTentacleSpeed()["sigma"].toDouble() ));

    addProperty("tentacle length",MutableNumber::positive(getTentacleLength()["initial"].toDouble(),
                getTentacleLength()["rate"].toDouble(), getTentacleLength()["sigma"].toDouble() ));
    compteur_ += 1;
}

TwitchingBacterium::~TwitchingBacterium()
{
    compteur_ -= 1;
}

TwitchingBacterium::TwitchingBacterium(const TwitchingBacterium& other)
    :Bacterium(other),
      grip_(other.grip_),
      mystate_(other.mystate_)
{
    compteur_ += 1;
}

//Getters utilitaires et setters :
j::Value& TwitchingBacterium::getConfig() const
{
    return getAppConfig()["twitching bacterium"];
}

Quantity TwitchingBacterium::getTentacleEnergy() const
{
    return getConfig()["energy"]["consumption factor"]["tentacle"].toDouble();
}

Quantity TwitchingBacterium::getDisplacementEnergy() const
{
    return getConfig()["energy"]["consumption factor"]["move"].toDouble();
}

j::Value& TwitchingBacterium::getTentacleSpeed() const
{
    return getConfig()["tentacle"]["speed"];
}

j::Value& TwitchingBacterium::getTentacleLength() const
{
    return getConfig()["tentacle"]["length"];
}

int TwitchingBacterium::getCompteur()
{
    return compteur_;
}

//Autres méthodes:
void TwitchingBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);
    auto tentacle = buildLine(getPosition(), grip_.getPosition(), getColor().get(), 1);
    target.draw(tentacle);
    auto gripBorder = buildAnnulus(grip_.getPosition(), grip_.getRadius(), getColor().get(), 1);
    target.draw(gripBorder);
}

Bacterium* TwitchingBacterium::copie()
{
    TwitchingBacterium* twitching(new TwitchingBacterium(*this));
    twitching->moveGrip(twitching->getPosition() - grip_.getPosition());
    return twitching;
}

void TwitchingBacterium::moveGrip(const Vec2d& v)
{
    grip_.move(v);
}

void TwitchingBacterium::move(sf::Time dt)
{
    switch (mystate_)
    {
        case IDLE :
        {
            idle();
            break;
        }
        case WAIT_TO_DEPLOY :
        {
            waitToDeploy();
            break;
        }
        case DEPLOY :
        {
            deploy(dt);
            break;
        }
        case ATTRACT :
        {
            attract(dt);
            break;
        }
        case RETRACT :
        {
            retract(dt);
            break;
        }

        case EAT :
        {
            eatingState();
            break;
        }
    }
}

void TwitchingBacterium::idle()
{
    mystate_ = WAIT_TO_DEPLOY;
}

void TwitchingBacterium::waitToDeploy()
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

    setDirection(finalDirection.normalised());
    mystate_ = DEPLOY;
}

void TwitchingBacterium::deploy(sf::Time dt)
{
    moveGrip(getDirection() * getProperty("tentacle speed").get() * dt.asSeconds());
    consumeEnergy(getTentacleEnergy() * getProperty("tentacle speed").get() * dt.asSeconds());
    if (getAppEnv().getNutrimentColliding(grip_) != nullptr)
    {
        mystate_ = ATTRACT;
    }
    else if((grip_.getPosition() - getPosition()).length() > getProperty("tentacle length").get()
            or getAppEnv().doesCollideWithDish(grip_))
    {
        mystate_ = RETRACT;
    }
}

void TwitchingBacterium::attract(sf::Time dt)
{
    if (getAppEnv().getNutrimentColliding(*this) != nullptr)
    {
        mystate_ = EAT;
    }
    else
    {
        CircularBody::move((grip_.getPosition() - getPosition()).normalised() * getProperty("tentacle speed").get() *
                           getConfig()["speed factor"].toDouble() * dt.asSeconds());
        consumeEnergy(getDisplacementEnergy() * getProperty("tentacle speed").get() *
                      getConfig()["speed factor"].toDouble() * dt.asSeconds());
    }

    if (getAppEnv().getNutrimentColliding(grip_) == nullptr)
    {
        mystate_ = RETRACT;
    }
}

void TwitchingBacterium::retract(sf::Time dt)
{
    if (distance(grip_.getPosition(), getPosition()) <= getRadius())
    {
        mystate_ = IDLE;
    }
    else
    {
        moveGrip((getPosition() - grip_.getPosition()).normalised() *
                 getProperty("tentacle speed").get() * dt.asSeconds());
        consumeEnergy(getTentacleEnergy() * getProperty("tentacle speed").get() * dt.asSeconds());
    }
}

void TwitchingBacterium::eatingState()
{
    if(getAppEnv().getNutrimentColliding(*this) == nullptr)
    {
        mystate_ = IDLE;
    }
}

Quantity TwitchingBacterium::eatableQuantity(NutrimentA& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity TwitchingBacterium::eatableQuantity(NutrimentB& nutriment)
{
    return nutriment.eatenBy(*this);
}
