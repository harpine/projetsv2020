/*
#ifndef MADBACTERIUM_HPP
#define MADBACTERIUM_HPP


#include "Bacterium.hpp"

class MadBacterium : public Bacterium
{
public:
    //Constructeurs et destructeurs:
    MadBacterium(const Vec2d& poscenter);
    ~MadBacterium() override;
    MadBacterium(const MadBacterium& other);
    //fonction à polymorphisme induit permettant de mettre les statistiques
    //à jour après que la mutation soit effectuée
    void updateStats() override;

    //Getters et setters:
    //permet de simplifier l'accès aux configurations
    virtual j::Value& getConfig() const override;

    //Autres méthodes:
    //dessine les bactéries dans la boîte de petri
    virtual void drawOn(sf::RenderTarget& target) const override;
    //Permet à la bactérie de se nourrir d'autres bactéries si possible
    virtual void eat() override;




private:
    double probability_;
    sf::Time tumbleClock_;
    static int compteur_;
    static double totalBetter_;
    static double totalWorse_;
    static double totalSpeed_;
};

#endif // MADBACTERIUM_HPP */

//Renvoie les effets du poison sur les bactéries selon leur type
//virtual Quantity eatablePoison(Poison& poison);
