#include "Spray.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>

Spray::Spray(const Vec2d& poscenter)
    :CircularBody(poscenter, getConfig()["size"].toDouble())
{}

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
