#ifndef SIMPLEBACTERIUM_HPP
#define SIMPLEBACTERIUM_HPP

#include "Bacterium.hpp"
#include "JSON/JSON.hpp"

class SimpleBacterium : public Bacterium
{
public:
    virtual j::Value& getConfig() const override;
};

#endif // SIMPLEBACTERIUM_HPP
