#pragma once

#include <Utility/Vec2d.hpp>
#include <iostream>

class CircularBody
{
public:
    //Getters:

    //retourne la position du centre du Circularbody
    Vec2d getPosition() const;
    //retourne le rayon
    double getRadius() const;

    //Autres méthodes:

    //retourne true si other est dans le cercle, false autrement
    bool contains(const CircularBody& other) const;
    //retourne true si le point v est dans le cercle, false autrement
    bool contains(const Vec2d& v) const;
    //retourne true si other est en collision avec le cercle
    bool isColliding(const CircularBody& other) const;

    //Surcharge d'opérateurs:

    //dans la classe car il travaille sur l'objet
    CircularBody& operator=(const CircularBody& circle);
    //pour simplifier la surcharge <<
    void afficher(std::ostream& out) const;

protected:
    //Constructeurs:
    CircularBody(const Vec2d& poscenter, const double radius);
    CircularBody(const CircularBody& other);

    //Setters:
    void setPosition(const Vec2d& poscenter);
    void setRadius(const double radius);

    //Autre méthode:
    //déplace le centre du vecteur v
    void move(const Vec2d& v);

private:
    //Attributs:
    Vec2d poscenter_;
    double radius_;

};

//Surchage d'opérateurs hors classe:

bool operator>(const CircularBody& c1, const CircularBody& c2); // 2 cercles
bool operator>(const CircularBody& c, const Vec2d& v); //point - cercle
bool operator&(const CircularBody& c1, const CircularBody& c2);
std::ostream& operator<<(std::ostream& out, const CircularBody& c);
