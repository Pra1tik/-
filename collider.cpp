#include "collider.h"

bool collider::checkCollision(collider& other, float push)
{
    vec otherPosition = other.GetPosition();
    vec otherHalfSize = other.GetHalfSize();
    vec thisPosition = GetPosition();
    vec thisHalfSize = GetHalfSize();

    float deltaX= otherPosition.x - thisPosition.x;
    float deltaY= otherPosition.y - thisPosition.y;

    intersect.x = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    intersect.y = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersect.x < 0.0f && intersect.y < 0.0f)
    {
        push = std::min(std::max(push,0.0f),1.0f);
        if (intersect.x > intersect.y)
        {
            if (deltaX>0.0f)
            {
                // move(intersect.x * (1.0f-push),0.0f);
                // other.move(-intersect.x * push,0.0f);
                offset.x=intersect.x * (1.0f-push);
                other.offset.x=-intersect.x*push;
            }
            else
            {
                offset.x=(-intersect.x * (1.0f-push));
                other.offset.x=(+intersect.x * push);
            }
        }
        else 
        {
            if(deltaY > 0.0f)
            {
                // move(0.0f,intersect.x * (1.0f-push));
                // other.move(0.0f,-intersect.x * push);
                offset.y=intersect.y*(1.0f-push);
                other.offset.y=-intersect.y * push;
            }
            else
            {
                offset.y=(-intersect.x * (1.0f-push));
                other.offset.y=(intersect.x * push);
            }
        }
        return true;
    }

    return false;
}
