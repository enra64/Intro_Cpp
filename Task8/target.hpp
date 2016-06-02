#include <random>
#include <string>
#include <iostream>

#ifndef _TARGET
#define _TARGET

struct Vec2d {
    double x, y;
};

class Target {
public:
    Target(std::string name, int health = 100, double x = 0, double y = 0) : 
        mHull(health), 
        mName(name) {
        mPosition.x = x;
        mPosition.y = y;
    }
    
    friend std::ostream &operator<<(std::ostream &lhs, const Target &t){
        lhs << t.mName << " mit " << t.mHull << " Leben an Position " << t.mPosition.x << ":" << t.mPosition.y;
        return lhs;
    }
    
    virtual int getHealth() const {
        return mHull;
    }
    
    inline int getHull() const {
        return mHull;
    }
    
    inline bool isDestroyed() const {
        return mIsExploded;
    }
    
    inline const std::string& getName() const {
        return mName;
    }
    
    virtual int receiveDamage(const Target& t) = 0;

protected:
    inline void explode() {
        std::cout << mName << " exploded" << std::endl;
        mIsExploded = true;
    }
    
    int mHull;
    bool mIsExploded = false;
    Vec2d mPosition;
    std::string mName;
};

class Spaceship : public Target {
public:
    Spaceship(std::string name, double x = 0, double y = 0, size_t lasers = 100, int health = 100) : 
    Target(name, health, x, y), 
    mNumberOfLasers(lasers) {
        
    }
    
    int getHealth() const override {
        return (mShields < 0 ? 0 : mShields) + (mHull < 0 ? 0 : mHull);
    }
    
    /// return damage made
    int attack(Target& t) const {
        std::cout << mName << " attacked " << t.getName() << std::endl;
        int oldHealth = t.getHealth();
        return oldHealth - t.receiveDamage(*this);
    }
    
    inline int getShields() const {
        return mShields;
    }
    
    int receiveDamage(const Target& s) override {
        if(nullptr != dynamic_cast<const Spaceship*>(&s)){
            mShields -= 12;
            if(mShields <= 0)
                mHull -= 32;
            if(mHull <= 0 && mShields <= 0)
                explode();
        }
        return getHealth();
    }
protected:
    size_t mNumberOfLasers;
    double mShields = 10;
};

class DeathStar : public Spaceship {
public:
    DeathStar(double x = 0, double y = 0, size_t laserCount = 380000) :
    Spaceship("Todesstern x", x, y, laserCount){
        mShields = 100;
    }
    
    int receiveDamage(const Target& s) override {
        if(nullptr != dynamic_cast<const Spaceship*>(&s)){
            mShields -= 12;
            if(mShields <= 0)
                mHull -= 32;
            bool explodeNow = (rand() % 4) == 1;
            if(explodeNow)
                explode();
            if(mHull <= 0 && mShields <= 0)
                explode();
        }
        return mHull;
    }
};

class Planet : public Target {
public:
    Planet(std::string name, double x = 0, double y = 0) : Target(name, 3000, x, y){
    
    }
    
    int receiveDamage(const Target& s) override {
        if(nullptr == dynamic_cast<const DeathStar*>(&s))
            return mHull;
        mHull = 0;
        if(mHull <= 0)
            explode();
        return mHull;
    }
};

#endif
