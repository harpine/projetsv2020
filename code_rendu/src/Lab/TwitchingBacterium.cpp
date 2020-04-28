#include "TwitchingBacterium.hpp"
#include <Application.hpp>
#include <Random/Random.hpp>
#include <Utility/Utility.hpp>

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
    switch (mystate_) {
    case IDLE : {
        mystate_ = WAIT_TO_DEPLOY;
        break;
    }
    case WAIT_TO_DEPLOY : {
        Vec2d direction(getDirection());
        Vec2d finalDirection(getDirection());
        double score(getAppEnv().getPositionScore(getPosition()));

        for (int i(0); i <=20 ; ++i) {
            direction = Vec2d::fromRandomAngle();
            if (getAppEnv().getPositionScore(getPosition()+direction) > score) {
                score = getAppEnv().getPositionScore(getPosition()+direction);
                finalDirection = direction;
            }
        }

        setDirection(finalDirection.normalised());
        mystate_ = DEPLOY;
        break;
    }
    case DEPLOY : {
        moveGrip(getDirection() * getProperty("tentacle speed").get() * dt.asSeconds());
        consumeEnergy(getTentacleEnergy() * getProperty("tentacle speed").get() * dt.asSeconds());
        if (getAppEnv().getNutrimentColliding(grip_) != nullptr) {
            mystate_ = ATTRACT;
        } else if((grip_.getPosition() - getPosition()).length() > getProperty("tentacle length").get()
                  or getAppEnv().doesCollideWithDish(grip_)) {
            mystate_ = RETRACT;
        }
        break;
    }
    case ATTRACT : {
        if (getAppEnv().getNutrimentColliding(*this) != nullptr) {
            mystate_ = EAT;
        } else {
            CircularBody::move((grip_.getPosition() - getPosition()).normalised() * getProperty("tentacle speed").get() *
                               getConfig()["speed factor"].toDouble() * dt.asSeconds());
            consumeEnergy(getDisplacementEnergy() * getProperty("tentacle speed").get() *
                          getConfig()["speed factor"].toDouble() * dt.asSeconds());
        }

        if (getAppEnv().getNutrimentColliding(grip_) == nullptr) {
            mystate_ = RETRACT;
        }
        break;
    }
    case RETRACT : {
        if (distance(grip_.getPosition(), getPosition()) <= getRadius()) {
            mystate_ = IDLE;
        } else {
            moveGrip((getPosition() - grip_.getPosition()).normalised() *
                     getProperty("tentacle speed").get() * dt.asSeconds());
            consumeEnergy(getTentacleEnergy() * getProperty("tentacle speed").get() * dt.asSeconds());
        }
        break;
    }

    case EAT : {
        if(getAppEnv().getNutrimentColliding(*this) == nullptr) {
            mystate_ = IDLE;
        }
        break;
    }
    }
}
