#ifndef TWITCHINGBACTERIUM_HPP
#define TWITCHINGBACTERIUM_HPP

#include "Bacterium.hpp"
#include "Grip.hpp"
#include <SFML/Graphics.hpp>
#include <Utility/Types.hpp>
#include <Utility/Vec2d.hpp>

enum State {IDLE, WAIT_TO_DEPLOY, DEPLOY, ATTRACT, RETRACT, EAT};

class TwitchingBacterium : public Bacterium
{
public:
    //Constructeur:
    TwitchingBacterium(const Vec2d& poscenter);

    //Getters utilitaires et setters:
    virtual j::Value& getConfig() const override;
    //Permet d'accéder aux paramètres de la bactérie à tentacules
    Quantity getTentacleEnergy() const;
    //Renvoie le "consumption factor" correspondant au "tentacle"
    Quantity getDisplacementEnergy() const;
    //renvoie le "consumption factor" correspondant au "move"
    j::Value& getTentacleSpeed() const;
    //renvoie les paramètres de la vitesse de la tentacule
    j::Value& getTentacleLength() const;
    //renvoie les paramètres de longueur de la tentacule

    //Autres méthodes:
    virtual Bacterium* copie() override;
    //Renvoie un pointeur sur une TwitchingBacterium qui est une copie de this
    virtual void drawOn(sf::RenderTarget& target) const override;
    //Représentation graphique d'une bactérie à tentacules
    void moveGrip(const Vec2d& v);
    //Déplace le grapin de la tentacule d'un vecteur v

    virtual void move(sf::Time dt) override;
    //Permet de déplacer la bactérie d'un pas de temps dt

private:
    Grip grip_;
    State mystate_;

};

#endif // TWITCHINGBACTERIUM_HPP
