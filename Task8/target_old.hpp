template <typename P>
struct Vec<P> {
    Vector(){
        x = 0;
        y = 0;
    }
    
    Vector(double _x, double _y) : x(_x), y(_y) {
    }
    
    double x, y;
}
class Target {
public:
    Target(std::string name, int health, double x, double y) : mHealth(health), mName(name) {
        mPosition.x = x;
        mPosition.y = y;
    }
    
    virtual int attacked(const Spaceship& s){
        mHealth -= 34;
        if(mHealth <= 0)
            explode();
        return mHealth;
    }
    
    friend std::ostream &operator<<(std::ostream &lhs, const Target &rhs){
        lhs << mName << " mit " << mHealth << " Leben an Position " << mPosition.x << ":" << mPosition.y;
    }
    
protected:
    virtual void explode() = 0;
    int mHealth;
    Vec2d mPosition;
    std::string mName;
}

class Planet : public Target {
public:
    Planet(std::string name, double x, double y) : Target(name, 3000, x, y){
    
    }

    int attacked(const Spaceship& s) override {
        return mHealth;
    }
    
    int attacked(const DeathStar& s) override {
        mHealth = 0;
        if(mHealth <= 0)
            explode();
        return mHealth;
    }
protected:

}

class Spaceship : public Target {
public:
    Spaceship(std::string name, double x, double y, size_t laserCount) : Target(name, x, y), mNumberOfLasers(laserCount) {
        
    }
    
    int attacked(const Spaceship& s) override {
        mShields -= 12;
        if(mShields <= 0)
            mHealth -= 32;
        if(mHealth <= 0 && mShields <= 0)
            explode();
        return mHealth;
    }
    
    void attack(Target& t){
        t.attacked(*this);
    }
    
protected:
    size_t mNumberOfLasers;
    double mShields = 100;
}

class DeathStar : public Spaceship {
    DeathStar(double x, double y, size_t laserCount) :
    Spaceship("Todesstern x", x, y, laserCount){
        mShields = 3000;
    }
    
    int attacked(const Spaceship& s) override {
        mShields -= 12;
        if(!(rand() % 4))
            mHealth = 0;
        if(mShields <= 0)
            mHealth -= 32;
        if(mHealth <= 0 && mShields <= 0)
            explode();
        return mHealth;
    }
}
