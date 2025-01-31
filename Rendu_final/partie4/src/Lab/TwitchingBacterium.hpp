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

    //Permet d'accéder aux paramètres de la bactérie à tentacules
    virtual j::Value& getConfig() const override;
    //Renvoie le "consumption factor" correspondant au "tentacle"
    Quantity getTentacleEnergy() const;
    //renvoie le "consumption factor" correspondant au "move"
    Quantity getDisplacementEnergy() const;
    //renvoie les paramètres de la vitesse de la tentacule
    j::Value& getTentacleSpeed() const;
    //renvoie les paramètres de longueur de la tentacule
    j::Value& getTentacleLength() const;

    //Autres méthodes:

    //Renvoie un pointeur sur une TwitchingBacterium qui est une copie de this
    virtual Bacterium* copie() override;
    //Représentation graphique d'une bactérie à tentacules
    virtual void drawOn(sf::RenderTarget& target) const override;
    //Déplace le grapin de la tentacule d'un vecteur v
    void moveGrip(const Vec2d& v);

    //Permet de déplacer la bactérie d'un pas de temps dt
    virtual void move(sf::Time dt) override;

private:
    //Attributs:
    Grip grip_;
    State mystate_;

    //Méthodes privées:

    //Permettent d'entreprendre les actions dorrespondant à chaque état
    void idle();
    void waitToDeploy();
    void deploy(sf::Time dt);
    void attract(sf::Time dt);
    void retract(sf::Time dt);
    void eatingState();

};

#endif // TWITCHINGBACTERIUM_HPP
