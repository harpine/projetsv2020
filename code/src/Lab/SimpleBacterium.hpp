#ifndef SIMPLEBACTERIUM_HPP
#define SIMPLEBACTERIUM_HPP

#include "Bacterium.hpp"
#include "JSON/JSON.hpp"
#include <Utility/DiffEqSolver.hpp>
#include <SFML/Graphics.hpp>

class SimpleBacterium : public Bacterium, public DiffEqFunction
{
public:
    //constructeur:
    SimpleBacterium(const Vec2d& poscenter);

    //getters & setters:
    virtual j::Value& getConfig() const override;
    j::Value& getSpeedConfig() const;
    j::Value& getWorseConfig() const;
    j::Value& getBetterConfig() const;
    //permet de simplifier l'accès aux configurations
    Vec2d getSpeedVector() const;
    //renvoie la vitesse courante (direction * une valeur)

    //méthodes:
    virtual Vec2d f(Vec2d position, Vec2d speed) const override;
    //calcul de la force
    virtual void move(sf::Time dt) override;
    //permet à une bactérie de se déplacer
    virtual Bacterium* copie() override;
    //copie une bactérie

    virtual void drawOn(sf::RenderTarget& target) const override;
    //représentation graphique de la bactérie simple
    virtual void update(sf::Time dt) override;
    //permet de mettre à jour les données et actions de la bactérie simple

private:

    //attributs:
    double t_flagelle_;
    //compteur qui fait varier l'amplitude des flagelles en fonction du temps
    double probability_;
    //probabilité de la bactérie à basculer
    double score_;
    //représente le gradient lié à la position de la bactérie
    sf::Time tumbleClock_;
    //compteur stockant le temps écoulé depuis le dernier basculement

    //méthodes :
    void drawOnFlagelle(sf::RenderTarget& target) const;
    //représentation dela flagelle
    void updateFlagelle(sf::Time dt);
    //mise à jour de la flagelle
    bool tumbleAttempt(sf::Time dt);
    void tumble();
};

#endif // SIMPLEBACTERIUM_HPP

