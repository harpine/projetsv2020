#include "../Utility/MutableNumber.hpp"
#include "SimpleBacterium.hpp"
#include "Nutriment.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include <Application.hpp>
#include <Random/Random.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Utility/DiffEqSolver.hpp>
#include <string>

//static members' initialization:
int SimpleBacterium::compteur_ = 0;
double SimpleBacterium::totalBetter_ =0;
double SimpleBacterium::totalWorse_ =0;
double SimpleBacterium::totalSpeed_ =0;

//Constructeur et destructeur:
SimpleBacterium::SimpleBacterium(const Vec2d& poscenter)
    :Bacterium(uniform(getConfig()["energy"]["max"].toDouble(),
      getConfig()["energy"]["min"].toDouble()),
     poscenter,
     Vec2d::fromRandomAngle().normalised(),
     uniform(getConfig()["radius"]["max"].toDouble(),
      getConfig()["radius"]["min"].toDouble()),
     getConfig()["color"]),
     t_flagelle_(uniform(0.0, PI)),
     probability_(), tumbleClock_(sf::Time::Zero)
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

SimpleBacterium::~SimpleBacterium()
{
    totalBetter_ -= getProperty("tumble better").get();
    totalWorse_ -= getProperty("tumble worse").get();
    totalSpeed_ -= getProperty(s::SPEED).get();
    compteur_ -= 1;
}

SimpleBacterium::SimpleBacterium(const SimpleBacterium& other)
    :Bacterium(other),
      t_flagelle_(other.t_flagelle_),
      probability_(other.probability_),
      tumbleClock_(other.tumbleClock_)
{
    compteur_ += 1;
}

void SimpleBacterium::updateStats()
{
    totalBetter_ += getProperty("tumble better").get();
    totalWorse_ += getProperty("tumble worse").get();
    totalSpeed_ += getProperty(s::SPEED).get();
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
    return getDirection().normalised() * getProperty(s::SPEED).get();
}

int SimpleBacterium::getCompteur()
{
    return compteur_;
}

double SimpleBacterium::getAverageBetter()
{
    if (compteur_ == 0)
    {
        return 0;
    }
    return totalBetter_/compteur_;
}
double SimpleBacterium::getAverageWorse()
{
    if (compteur_ == 0)
    {
        return 0;
    }
    return totalWorse_/compteur_;
}

double SimpleBacterium::getTotalSpeed()
{
    return totalSpeed_;
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

void SimpleBacterium::tumble()
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

Quantity SimpleBacterium::eatableQuantity(NutrimentA& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity SimpleBacterium::eatableQuantity(NutrimentB& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity SimpleBacterium::eatablePoison(Poison& poison)
{
    return poison.eatenBy(*this);
}
