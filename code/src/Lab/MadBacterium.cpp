#include "MadBacterium.hpp"
#include "Nutriment.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>

//static members' initialization:
int MadBacterium::compteur_ = 0;
double MadBacterium::totalBetter_ =0;
double MadBacterium::totalWorse_ =0;
double MadBacterium::totalSpeed_ =0;

MadBacterium::MadBacterium(const Vec2d& poscenter)
    :Bacterium(uniform(getConfig()["energy"]["max"].toDouble(),
      getConfig()["energy"]["min"].toDouble()),
     poscenter,
     Vec2d::fromRandomAngle().normalised(),
     uniform(getConfig()["radius"]["max"].toDouble(),
     getConfig()["radius"]["min"].toDouble()),
     getConfig()["color"]),
     probability_(0),
     tumbleClock_(sf::Time::Zero),
     bacteriaScore_(0)
{
    addProperty("speed", MutableNumber(getSpeedConfig()["initial"].toDouble(),
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
    totalSpeed_ += getProperty("speed").get();
    compteur_ += 1;
}

MadBacterium::~MadBacterium()
{
    totalBetter_ -= getProperty("tumble better").get();
    totalWorse_ -= getProperty("tumble worse").get();
    totalSpeed_ -= getProperty("speed").get();
    compteur_ -= 1;
}

MadBacterium::MadBacterium(const MadBacterium& other)
    :Bacterium(other),
      probability_(other.probability_),
      tumbleClock_(other.tumbleClock_)
{
    compteur_ += 1;
}

void MadBacterium::updateStats()
{
    totalBetter_ += getProperty("tumble better").get();
    totalWorse_ += getProperty("tumble worse").get();
    totalSpeed_ += getProperty("speed").get();
}

//Getters et setters:
j::Value& MadBacterium::getConfig() const
{
    return getAppConfig()["mad bacterium"];
}

Vec2d MadBacterium::getSpeedVector() const
{
    return getDirection().normalised() * getProperty("speed").get();
}

j::Value& MadBacterium::getWorseConfig() const
{
    return getConfig()["tumble"]["worse"];
}

j::Value& MadBacterium::getBetterConfig() const
{
    return getConfig()["tumble"]["better"];
}

int MadBacterium::getCompteur()
{
    return compteur_;
}

double MadBacterium::getAverageBetter()
{
    if (compteur_ == 0)
    {
        return 0;
    }
    return totalBetter_/compteur_;
}
double MadBacterium::getAverageWorse()
{
    if (compteur_ == 0)
    {
        return 0;
    }
    return totalWorse_/compteur_;
}

double MadBacterium::getTotalSpeed()
{
    return totalSpeed_;
}

//Autres méthodes:
void MadBacterium::drawOn(sf::RenderTarget& target) const
{
    int taille_graphique(6);
    auto const& texture = getAppTexture(getConfig()["texture"].toString());
    auto madBacteriumSprite = buildSprite(getPosition(), taille_graphique, texture);
    // adapte la taille du Sprite au rayon e la bactérie:
    madBacteriumSprite.setScale(2 * getRadius() / texture.getSize().x, 2 * getRadius() / texture.getSize().y);
    target.draw(madBacteriumSprite);

    if (isDebugOn()) //mode debug
    {
        sf::Text const texte = buildText(std::to_string(int(getEnergy())),
                            Vec2d(getPosition().x - 5, getPosition().y + getRadius() + 10),
                                         getAppFont(), 15, sf::Color::Black);
        target.draw(texte);
    }
}

void MadBacterium::eat()
{
    if (getAppEnv().getBacteriumColliding(*this) != nullptr
            and !getAbstinence()
            and getMealClock() >= getMealDelay())
    {
        Quantity eaten(getAppEnv().getBacteriumColliding(*this)->attackedBy(*this));
        setEnergy(getEnergy() + eaten);
        setMealClock(sf::Time::Zero);
    }
}

void MadBacterium::move(sf::Time dt)
{
    DiffEqResult result(stepDiffEq(getPosition(), getSpeedVector(), dt, *this));
    //this est une DiffEqFunction
    consumeEnergy(getDisplacementEnergy()* distance(result.position, getPosition()));
    //distance renvoie length des 2 Vec2d

    if ((result.position - getPosition()).lengthSquared() > 0.001)
    {
        this->CircularBody::move((result.position - getPosition()));   //this ??
        //move est moins intuitif mais meilleur pour la hiérarchie des classes
    }

    if(tumbleAttempt(dt))
    {
        tumble();
    }
}

bool MadBacterium::tumbleAttempt(sf::Time dt)
{
    double lambda(0);
    double ancien_score(bacteriaScore_);
    updateBacteriaScore();
    tumbleClock_ += dt;

    if (bacteriaScore_ >= ancien_score)
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

void MadBacterium::tumble()
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

void MadBacterium::updateBacteriaScore()
{
    bacteriaScore_ = getAppEnv().getPositionBacteriaScore(this->getPosition());
}

Bacterium* MadBacterium::copie()
{
    return new MadBacterium(*this);
}

Quantity MadBacterium::eatableQuantity(NutrimentA& nutriment)
{
    return 0;
}

Quantity MadBacterium::eatableQuantity(NutrimentB& nutriment)
{
    return 0;
}

Vec2d MadBacterium::f(Vec2d position, Vec2d speed) const
{
    return Vec2d(); //constructeur de Vec2d par défaut renvoie le vecteur nul
}

void MadBacterium::update(sf::Time dt)
{
   Bacterium::update(dt);
   updateBacteriaScore();
}

void MadBacterium::bestOfN(int n)
{
    Vec2d direction(getDirection());
    Vec2d finalDirection(getDirection());
    double bacteriaScore(bacteriaScore_);

    for (int i(0); i < n ; ++i)
    {
        direction = Vec2d::fromRandomAngle().normalised();
        if (getAppEnv().getPositionBacteriaScore(getPosition()+direction) > bacteriaScore)
        {
            bacteriaScore = getAppEnv().getPositionBacteriaScore(getPosition()+direction);
            finalDirection = direction;
        }
    }
    setDirection(finalDirection);
}

Quantity MadBacterium::attackedBy(MadBacterium& madbact)
{
    return 0;
}

Quantity MadBacterium::eatablePoison(Poison& poison)
{
    return poison.eatenBy(*this);
}
