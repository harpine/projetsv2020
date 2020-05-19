#include "Spray.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>

Spray::Spray(const Vec2d& poscenter)
    :CircularBody(poscenter, getConfig()["size"].toDouble())
{

    sprayAudio_.loadFromFile(getApp().getResPath() + getConfig()["audio"].toString());
    spray_.setBuffer(sprayAudio_);
    spray_.play();
}


//    sf::Music music;
//    music.openFromFile(getApp().getResPath() + getConfig()["audio"].toString());
//    music.setVolume(100);
//    music.play();
//    sf::SoundBuffer* sprayAudio = new sf::SoundBuffer();

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
    target.draw(spraySprite);
}

bool Spray::hasFaded() const
{
    return clock_.getElapsedTime().asSeconds() > getConfig()["fading time"].toDouble();
}
