#include "MadBacterium.hpp"
#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>

MadBacterium::MadBacterium(const Vec2d& poscenter)
    :Bacterium(uniform(getConfig()["energy"]["max"].toDouble(),
      getConfig()["energy"]["min"].toDouble()),
     poscenter,
     Vec2d::fromRandomAngle().normalised(),
     uniform(getConfig()["radius"]["max"].toDouble(),
     getConfig()["radius"]["min"].toDouble()),
     getConfig()["color"]),
     probability_()
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
    if (getAppEnv().getNutrimentColliding(*this) != nullptr
            and clock_ >= getMealDelay())
    {
        Quantity eaten(getAppEnv().getNutrimentColliding(*this)->eatenBy(*this));
        energy_ += eaten;
        clock_ = sf::Time::Zero ;
    }
}











