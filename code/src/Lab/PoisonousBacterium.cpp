#include "PoisonousBacterium.hpp"
#include "Nutriment.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include <Random/Random.hpp>
#include <Application.hpp>
#include <Utility/Utility.hpp>
#include "Poison.hpp"

//static members' initialization:
int PoisonousBacterium::compteur_ = 0;
double PoisonousBacterium::totalBetter_ = 0;
double PoisonousBacterium::totalWorse_ = 0;
double PoisonousBacterium::totalSpeed_ = 0;

//Constructeur et destructeur:
PoisonousBacterium::PoisonousBacterium(const Vec2d& poscenter)
    :Bacterium(uniform(getConfig()["energy"]["max"].toDouble(),
      getConfig()["energy"]["min"].toDouble()),
     poscenter,
     Vec2d::fromRandomAngle().normalised(),
     uniform(getConfig()["radius"]["max"].toDouble(),
      getConfig()["radius"]["min"].toDouble()),
     MutableColor()), //?? à enlever dans app.json??
     probability_(), tumbleClock_(sf::Time::Zero), poisonClock_(sf::Time::Zero)
{
    addProperty(s::SPEED, MutableNumber(getSpeedConfig()["initial"].toDouble(),
                getSpeedConfig()["rate"].toDouble(), getSpeedConfig()["sigma"].toDouble(), true, 5));
    //nous avons utilisé un MutableNumber général, afin que la vitesse ne puisse pas
    //descendre à 0 (et donc la bactérie être immortelle en ne bougeant plus: développement
    //observé car cela lui est favorable) nous avons pris 5 afin d'en avoir le retour visuel.

    addProperty("tumble better",MutableNumber::positive(getBetterConfig()["initial"].toDouble(),
                getBetterConfig()["rate"].toDouble(), getBetterConfig()["sigma"].toDouble()));

    addProperty("tumble worse",MutableNumber::positive(getWorseConfig()["initial"].toDouble(),
                getWorseConfig()["rate"].toDouble(), getWorseConfig()["sigma"].toDouble()));
    totalBetter_ += getProperty("tumble better").get();
    totalWorse_ += getProperty("tumble worse").get();
    totalSpeed_ += getProperty(s::SPEED).get();
    compteur_ += 1;
}

PoisonousBacterium::~PoisonousBacterium()
{
    totalBetter_ -= getProperty("tumble better").get();
    totalWorse_ -= getProperty("tumble worse").get();
    totalSpeed_ -= getProperty(s::SPEED).get();
    compteur_ -= 1;
}

PoisonousBacterium::PoisonousBacterium(const PoisonousBacterium& other)
    :Bacterium(other),
      probability_(other.probability_),
      tumbleClock_(other.tumbleClock_)
{
    compteur_ += 1;
}

void PoisonousBacterium::updateStats()
{
    totalBetter_ += getProperty("tumble better").get();
    totalWorse_ += getProperty("tumble worse").get();
    totalSpeed_ += getProperty(s::SPEED).get();
}

//Getters:
j::Value& PoisonousBacterium::getConfig() const
{
    return getAppConfig()[s::POISONOUS_BACTERIUM];
}

j::Value& PoisonousBacterium::getWorseConfig() const
{
    return getConfig()["tumble"]["worse"];
}

j::Value& PoisonousBacterium::getBetterConfig() const
{
    return getConfig()["tumble"]["better"];
}

Vec2d PoisonousBacterium::getSpeedVector() const
{
    return getDirection().normalised() * getProperty(s::SPEED).get();
}

double PoisonousBacterium::getAverageBetter()
{
    if (compteur_ == 0)
    {
        return 0;
    }
    return totalBetter_/compteur_;
}
double PoisonousBacterium::getAverageWorse()
{
    if (compteur_ == 0)
    {
        return 0;
    }
    return totalWorse_/compteur_;
}

double PoisonousBacterium::getTotalSpeed()
{
    return totalSpeed_;
}

int PoisonousBacterium::getCompteur()
{
    return compteur_;
}
//Autres méthodes:
Vec2d PoisonousBacterium::f(Vec2d position, Vec2d speed) const
{
    return Vec2d(); //constructeur de Vec2d par défaut renvoie le vecteur nul
}

void PoisonousBacterium::move(sf::Time dt)
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

void PoisonousBacterium::drawOn(sf::RenderTarget& target) const
{
    int taille_graphique(6);
    auto const& texture = getAppTexture(getConfig()["texture"].toString());
    auto nutrimentSprite = buildSprite(getPosition(), taille_graphique, texture);
    // adapte la taille du Sprite au rayon du nutriment:
    nutrimentSprite.setScale(2 * getRadius() / texture.getSize().x, 2 * getRadius() / texture.getSize().y);
    target.draw(nutrimentSprite);
    if (isDebugOn()) //mode debug
    {
        int energy(getEnergy());
        sf::Text const texte = buildText(std::to_string(energy),
                            Vec2d(getPosition().x - 5, getPosition().y + getRadius() + 10),
                                         getAppFont(), 15, sf::Color::Black);
        target.draw(texte);
    }
}

void PoisonousBacterium::update(sf::Time dt)
{
    Bacterium::update(dt);
    if (canPoison(dt))
    {
        putPoison();
    }
}

Bacterium* PoisonousBacterium::copie()
{
    return new PoisonousBacterium(*this);
}

Quantity PoisonousBacterium::eatableQuantity(NutrimentA& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity PoisonousBacterium::eatableQuantity(NutrimentB& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity PoisonousBacterium::eatablePoison(Poison& poison)
{
    return poison.eatenBy(*this);
}

bool PoisonousBacterium::canPoison(sf::Time dt)
{
    poisonClock_ += dt;
    if (poisonClock_.asSeconds() >= 10 and getEnergy() >= 20)
        //les bactéries n'ont pas l'énergie de déposer du poison
        //si leur énergie est inférieure à 20
    {
        poisonClock_ = sf::Time::Zero;
        return true;
    }
    return false;

}
void PoisonousBacterium::putPoison()
{
    getAppEnv().addPoison(new Poison(getPosition()));
    setEnergy(getEnergy() - 20);
}

bool PoisonousBacterium::tumbleAttempt(sf::Time dt)
{
    double lambda(0);
    double ancien_score(getScore());
    updateScore();
    tumbleClock_ += dt;

    if (getScore() >= ancien_score)
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

void PoisonousBacterium::tumble()
{
    if (getConfig()["tumble"]["algo"].toString() == "single random vector")
    {
        setDirection(Vec2d::fromRandomAngle());
    }
    else if(getConfig()["tumble"]["algo"].toString().find("best of ") != std::string::npos)
    {
        bestOfN(std::stoi(getConfig()["tumble"]["algo"].toString().substr(8, 2)));
        //permet de trouver une meilleure position parmis le nombre donné (entre 1 et 99)
    }
    tumbleClock_ = sf::Time::Zero;
}
