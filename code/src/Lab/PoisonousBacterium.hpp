#ifndef POISONOUSBACTERIUM_HPP
#define POISONOUSBACTERIUM_HPP
#include "Bacterium.hpp"
#include "Utility/DiffEqSolver.hpp"
#include <SFML/Graphics.hpp>

class PoisonousBacterium: public Bacterium, public DiffEqFunction
{
public:
    //Constructeurs et destructeurs:
    PoisonousBacterium(const Vec2d& poscenter);
    ~PoisonousBacterium() override;
    PoisonousBacterium(const PoisonousBacterium& other);
    //fonction à polymorphisme induit permettant de mettre les statistiques
    //à jour après que la mutation soit effectuée
    void updateStats() override;

    //Getters & setters:
    //permet de simplifier l'accès aux configurations
    virtual j::Value& getConfig() const override;
    j::Value& getWorseConfig() const;
    j::Value& getBetterConfig() const;
    //renvoie la vitesse courante (direction * une valeur)
    Vec2d getSpeedVector() const;
    //renvoie la moyenne des tumbles better des bactéries existantes
    static double getAverageBetter();
    //renvoie la moyenne des tumbles better des bactéries existantes
    static double getAverageWorse();
    //renvoie la somme des vitesses des bactéries existantes
    static double getTotalSpeed();
    //renvoie le nombre d'instances existantes
    static int getCompteur();
    //Renvoie la quantité d'énergie perdue en déposant du poison
    //(quantity de poison à déposer * facteur)
    double getEnergylosedByPoison() const;

    //Autres méthodes:

    //calcul de la force
    virtual Vec2d f(Vec2d position, Vec2d speed) const override;
    //permet à une bactérie de se déplacer
    virtual void move(sf::Time dt) override;
    //copie une bactérie
    virtual Bacterium* copie() override;
    //représentation graphique de la bactérie simple
    virtual void drawOn(sf::RenderTarget& target) const override;
    //permet de mettre à jour les données et actions de la bactérie simple
    virtual void update(sf::Time dt) override;
    //renvoie la quantité de nutriment consommée en fonction du nutriment
    virtual Quantity eatableQuantity(NutrimentA& nutriment) override;
    virtual Quantity eatableQuantity(NutrimentB& nutriment) override;
    //Renvoie les effets du poison sur les bactéries selon leur type
    virtual Quantity eatablePoison(Poison& poison) override;
    //Renvoie true si la bactérie peut poser du poison
    bool canPoison(sf::Time dt);
    //Pose un poison
    void putPoison();

private:
    //probabilité de la bactérie à basculer
    double probability_;
    //compteur stockant le temps écoulé depuis le dernier basculement
    sf::Time tumbleClock_;
    //compteur stocka
    sf::Time poisonClock_;
    //compteur du nombre d'instances existantes
    static int compteur_;
    //somme des tumbles better des bactéries existantes
    static double totalBetter_;
    //somme des tumbles worse des bactéries existantes
    static double totalWorse_;
    //sommes des vitesses
    static double totalSpeed_;

    //retourne le booléen indiquant s'il y a basculement ou non
    bool tumbleAttempt(sf::Time dt);
    //fait basculer la bactérie
    void tumble();
};

#endif // POISONOUSBACTERIUM_HPP
