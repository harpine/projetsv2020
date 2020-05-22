#include "Spray.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>

Spray::Spray(const Vec2d& poscenter)
    :CircularBody(poscenter, getConfig()["size"].toDouble()),
     transparency_(255)
{
    if (sprayAudio_.loadFromFile(getApp().getResPath() + getConfig()["audio"].toString()))
    {
        spray_.setBuffer(sprayAudio_);
        spray_.setVolume(100);
        spray_.play();
    }
}

j::Value& Spray::getConfig() const
{
    return getAppConfig()["spray"];
}

void Spray::drawOn(sf::RenderTarget& target) const
{
    int taille_graphique(6);
    auto const& texture = getAppTexture(getConfig()["texture"].toString());
    auto spraySprite = buildSprite(getPosition(), taille_graphique, texture);
    // adapte la taille du Sprite au rayon du spray:
    spraySprite.setScale(2 * getRadius() / texture.getSize().x, 2 * getRadius() / texture.getSize().y);
    spraySprite.setColor(sf::Color(255, 255, 255, transparency_));
    target.draw(spraySprite);
}

void Spray::update(sf::Time dt)
{
    if (dt != sf::Time::Zero)
    {
        double toSubtract(255/(getConfig()["fading time"].toDouble()/dt.asSeconds()));

        if (dt != sf::Time::Zero and transparency_ > toSubtract)
        {
            transparency_ -= toSubtract;
        }
    }
}

bool Spray::hasFaded() const
{
    return clock_.getElapsedTime().asSeconds() > getConfig()["fading time"].toDouble();
}
