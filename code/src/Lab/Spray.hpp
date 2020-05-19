#ifndef SPRAY_HPP
#define SPRAY_HPP
#include "CircularBody.hpp"
#include <Utility/Vec2d.hpp>
#include <Interface/Drawable.hpp>
#include <SFML/Audio.hpp>

class Spray : public CircularBody, public Drawable
{
public:
    //Constructeur
    Spray(const Vec2d& poscenter);


    //Getters
    //permet d'accéder aux configs des sprays sans
    //devoir écrire ["spray"]
    j::Value& getConfig() const;

    //Autres méthodes:
    //permet de dessiner le spray
    void drawOn(sf::RenderTarget& target) const override;
    //renvoie si le spray dépasse son temps d'action
    bool hasFaded() const;


private :
    sf::Clock clock_;
    sf::SoundBuffer sprayAudio_;
    sf::Sound spray_;
};

#endif // SPRAY_HPP
