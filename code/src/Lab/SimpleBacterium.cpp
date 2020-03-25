#include "SimpleBacterium.hpp"

SimpleBacterium::SimpleBacterium()
{

}

virtual j::Value& getConfig() override
{
    return getAppConfig()["simple bacterium"];
}


