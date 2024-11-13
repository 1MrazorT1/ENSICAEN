#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle{
public:
    virtual void reçoitPalet() = 0;
    void setSuccesseur(Obstacle* succ);
    virtual ~Obstacle() {};
protected:
    Obstacle* successeur = nullptr;
};

#endif