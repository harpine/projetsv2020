#ifndef MADBACTERIUM_HPP
#define MADBACTERIUM_HPP

#include "Bacterium.hpp"
#include <Utility/DiffEqSolver.hpp>

class MadBacterium : public Bacterium, public DiffEqFunction
{
public:
    //Constructeurs et destructeurs:
    MadBacterium(const Vec2d& poscenter);
    ~MadBacterium() override;
    MadBacterium(const MadBacterium& other);
    //fonction à polymorphisme induit permettant de mettre les statistiques
    //à jour après que la mutation soit effectuée
    virtual void updateStats() override;

    //Getters et setters:
    //permet de simplifier l'accès aux configurations
    virtual j::Value& getConfig() const override;
    //Retourne le vecteur de vitesse
    Vec2d getSpeedVector() const;
    //Facilite l'accès aux configuration better et worse pour le basculement
    j::Value& getWorseConfig() const;
    j::Value& getBetterConfig() const;
    //renvoie le nombre d'instances existantes
    static int getCompteur();
    //renvoie la moyenne des tumbles better des bactéries existantes
    static double getAverageBetter();
    //renvoie la moyenne des tumbles better des bactéries existantes
    static double getAverageWorse();
    //renvoie la somme des vitesses des bactéries existantes
    static double getTotalSpeed();

    //Autres méthodes:
    //dessine les bactéries dans la boîte de petri
    virtual void drawOn(sf::RenderTarget& target) const override;
    //Permet à la bactérie de se nourrir d'autres bactéries si possible
    virtual void eat() override;
    //Permet de faire déplacer la bactérie en fonction du gradient de bactéries
    virtual void move(sf::Time dt) override;
    //Met à jour le score de bactéries
    void updateBacteriaScore();
    //Permet de copier une bactérie
    virtual Bacterium* copie() override;
    //Méthodes retournant 0 est indifférente aux nutriments
    virtual Quantity eatableQuantity(NutrimentA& nutriment) override;
    virtual Quantity eatableQuantity(NutrimentB& nutriment) override;
    virtual Vec2d f(Vec2d position, Vec2d speed) const override;
    //Permet de mettre à jour la bactérie et son gradient de bactérie
    virtual void update(sf::Time dt) override;
    //Redefinition polymorphique de bestOfN par rapport au gradient
    //de bactéries à présent
    virtual void bestOfN(int n) override;
    //Permet un comportement différencié d'attaque des MadBacteria vis-à-vis
    //des MadBacteria elles-mêmes
    virtual Quantity attackedBy(MadBacterium& madbact) override;
    //Renvoie les effets du poison sur les bactéries selon leur type
    virtual Quantity eatablePoison(Poison& poison) override;

private:

    //Attributs:
    double probability_;
    sf::Time tumbleClock_;
    double bacteriaScore_; //représente le gradient de bactéries
    static int compteur_;
    static double totalBetter_;
    static double totalWorse_;
    static double totalSpeed_;

    //Méthodes:
    //retourne le booléen indiquant s'il y a basculement ou non
    bool tumbleAttempt(sf::Time dt);
    //fait basculer la bactérie
    void tumble();
};

#endif // MADBACTERIUM_HPP
