#ifndef MUTABLENUMBER_HPP
#define MUTABLENUMBER_HPP
#include "JSON/JSON.hpp"

class MutableNumber
{
public:
    //constructeurs:
    MutableNumber(double value, double probability, double sigma,
                  bool inf = false,double infval = 0,
                  bool sup = false, double supval= 0);
    MutableNumber(j::Value const& config);
    MutableNumber() = default;
    //getters & setters:
    double get() const;
    //renvoie la valeur du nb
    void set(double value);
    //permet d'attribuer une valeur au nombre
    void mutate();
    // modifie la valeur du nombre de façon aléatoire
    static MutableNumber probability(double initialValue, double mutationProbability, double sigma);
    //créé un MutableNumber à partir de ces valeurs (Named constructor)
    static MutableNumber probability(j::Value const& config);
    //même fonction que précédante mais puise la valeur init,
    //la proba de mut. et l'écart type dans config
    static MutableNumber positive(double initialValue, double mutationProbability,
                                  double sigma, bool hasMax=false, double max=0.);
    //créé un MutableNumber dont la valeur minimale est plafonnée à 0
    static MutableNumber positive(j::Value const& config, bool hasMax=false, double max=0.);
    //fait la même chose que la précédente mais en tirant les autres valeur de Config

private:
    double value_;
    double probability_;
    bool inf_; //indique si le nombre a une valeur inférieure
    bool sup_;
    double infval_; //indique quelle est la borne inférieure
    double supval_;
    double sigma_; //écart type (pour la modif. aléatoire)

    //méthodes:
    double controlvalue(double value);
    //controle si value est dans les bornes et renvoie la bonne valeur à affecter
    //(value si ok, borne inf si plus petit, borne sup si plus grand)
};

#endif // MUTABLENUMBER_HPP
