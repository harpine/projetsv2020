#include "MutableNumber.hpp"
#include <Random/Random.hpp>

//Constructeurs:
MutableNumber::MutableNumber(double value, double probability, double sigma,
                                 bool inf, double infval, bool sup, double supval)
    :probability_(probability), inf_(inf), sup_(sup),
      infval_(infval), supval_(supval), sigma_(sigma)
{
    value_ = controlvalue(value);
}

MutableNumber::MutableNumber(j::Value const& config)
    : probability_(config["rate"].toDouble()), inf_(config["clamp min"].toBool()),
      sup_(config["clamp max"].toBool()), infval_(config["min"].toDouble()),
      supval_(config["max"].toDouble()), sigma_(config["sigma"].toDouble())
{
    value_ = controlvalue(config["initial"].toDouble());
}

//Getter et setter:
double MutableNumber::get() const
{
    return value_;
}

void MutableNumber::set(double value)
{
    value_ = controlvalue(value);
}

//Autres méthodes:
void MutableNumber::mutate()
{
    if (bernoulli(probability_))
    {
        value_ = controlvalue(value_ + normal(0, sigma_*sigma_));
    }
}

//Méthodes statiques:
MutableNumber MutableNumber::probability(double initialValue, double mutationProbability,double sigma)
{
    MutableNumber mutablenumber(initialValue, mutationProbability,
                                sigma, true, 0.,true, 1.);
    return mutablenumber;
}

MutableNumber MutableNumber::probability(j::Value const& config)
{
    MutableNumber mutablenumber(config["initial"].toDouble(), config["rate"].toDouble(),
            config["sigma"].toDouble(), true, 0.,true, 1.);
    return mutablenumber;
}

MutableNumber MutableNumber::positive(double initialValue, double mutationProbability,
         double sigma, bool hasMax, double max)
{
    MutableNumber mutablenumber(initialValue, mutationProbability,
         sigma, true, 0.,hasMax, max);
    return mutablenumber;
}

MutableNumber MutableNumber::positive(j::Value const& config, bool hasMax, double max)
{
    MutableNumber mutablenumber(config["initial"].toDouble(), config["rate"].toDouble(),
        config["sigma"].toDouble(), true, 0., hasMax, max);
    return mutablenumber;
}

//Méthode privée:
double MutableNumber::controlvalue(double value)
{
    if (inf_ and value<infval_)
    {
        value= infval_;
    }
    else if (sup_ and value > supval_)
    {
        value = supval_;
    }
    return value;
}



