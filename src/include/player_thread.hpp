#include "player.hpp"
class PlayerThread
{
private:
    Player player_;
    
public:
    void operator () (Player&& player) {
        player_ = std::move(player); //Move player into thread
        while (true)
        {
            
        }
    }
};