#pragma once

#include <Utility/Vec2d.hpp>
#include <iostream>

class CircularBody
{
public:
    //Getters:
    Vec2d getPosition() const;
    //retourne la position du centre du Circularbody
    double getRadius() const;
    //retourne le rayon

    //Autres méthodes:
    bool contains(const CircularBody& other) const;
    //retourne true si other est dans le cercle, false autrement
    bool contains(const Vec2d& v) const;
    //retourne true si le point v est dans le cercle, false autrement
    bool isColliding(const CircularBody& other) const;
    //retourne true si other est en collision avec le cercle

    //Surcharge d'opérateurs:
    CircularBody& operator=(const CircularBody& circle);
    //dans la classe car il travaille sur l'objet

    void afficher(std::ostream& out) const; //pour simplifier la surcharge <<

protected:
    //Constructeurs:
    CircularBody(const Vec2d& poscenter, const double radius);
    CircularBody(const CircularBody& other);

    //Setters:
    void setPosition(const Vec2d& poscenter);
    void setRadius(const double radius);

    //Autre méthode:
    void move(const Vec2d& v);
    //déplace le centre du cercle de la "distance" v

private:
    //Attributs:
    Vec2d poscenter_;
    double radius_;

};

bool operator>(const CircularBody& c1, const CircularBody& c2); // 2 cercles
bool operator>(const CircularBody& c, const Vec2d& v); //point - cercle
bool operator&(const CircularBody& c1, const CircularBody& c2);
std::ostream& operator<<(std::ostream& out, const CircularBody& c);
