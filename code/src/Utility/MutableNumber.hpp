#ifndef MUTABLENUMBER_HPP
#define MUTABLENUMBER_HPP

#include <JSON/JSON.hpp>

class MutableNumber
{
public:
    //Constructeurs:
    MutableNumber(double value, double probability, double sigma,
                  bool inf = false,double infval = 0,
                  bool sup = false, double supval= 0);
    MutableNumber(j::Value const& config);
    MutableNumber() = default;

    //Gettter et setter:

    //renvoie la valeur du nb
    double get() const;
    //permet d'attribuer une valeur au nombre
    void set(double value);

    //Autres méthodes:
    // modifie la valeur du nombre de façon aléatoire
    void mutate();

    //Méthodes statiques:
    //créé un MutableNumber à partir de ces valeurs (Named constructor)
    static MutableNumber probability(double initialValue, double mutationProbability, double sigma);
    //même fonction que précédante mais puise la valeur init,
    //la proba de mut. et l'écart type dans config
    static MutableNumber probability(j::Value const& config);
    //créé un MutableNumber dont la valeur minimale est plafonnée à 0
    static MutableNumber positive(double initialValue, double mutationProbability,
             double sigma, bool hasMax=false, double max=0.);
    //fait la même chose que la précédente mais en tirant les autres valeur de Config
    static MutableNumber positive(j::Value const& config, bool hasMax=false, double max=0.);

private:
    //Attribut:
    double value_;
    double probability_;
    bool inf_; //indique si le nombre a une valeur inférieure
    bool sup_;
    double infval_; //indique quelle est la borne inférieure
    double supval_;
    double sigma_; //écart type (pour la modif. aléatoire)

    //Autre méthode:

    //controle si value est dans les bornes et renvoie la bonne valeur à affecter
    //(value si ok, borne inf si plus petit, borne sup si plus grand)
    double controlvalue(double value);

};

#endif // MUTABLENUMBER_HPP
