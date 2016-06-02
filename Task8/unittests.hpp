#include "target.hpp"
#include <iostream>
#include <fstream>

/*
template <typename BaseClass, typename DerivedClass>
bool testInheritance(BaseClass b, DerivedClass d){
    return dynamic_cast<BaseClass*>(&d) != nullptr;
}*/

void fail(std::string msg){
    std::cerr << "fail: " << msg << std::endl;
}

void log(std::string msg){
    std::clog << "ok: " << msg << std::endl;
}

/*
*
*
*
* * * * * * * * * * * * * * * * * * * * * * TARGET TESTING
*
*
*
*/

bool testTargets(){
    bool success = true;
    // i cannot test these??
    
    // Every Target has a position and name. 
    // Each target can be attacked and can explode
    // Exploding cannot be triggered from outside the class. (only through receiving damage)
    // Should have a stream out operator. 
    // Can be purely virtual (abstract).
    return success;
}

/*
*
*
*
* * * * * * * * * * * * * * * * * * * * * * PLANET TESTING
*
*
*
*/

// Can only be destroyed be DeathStars.
bool testPlanetDestroyability(){
    Planet p("planet destroyabilty planet");
    Spaceship s("planet destroyabilty spaceship");
    DeathStar d;
    
    // normal spaceships must not make damage
    if(s.attack(p) > 0){
        fail("spaceship damaged planet!");
        return false;
    }
    else
        log("normal spaceships do not do damage to planets");
    
    // do deathstars do damage?
    if(d.attack(p) == 0){
        fail("deathstar did not damage planet");
        return false;
    }
    else
        log("deathstar dealt damage to planet");
    return true;
}

bool testPlanetAttackPower(){
    Planet t("planet attack power target");
    Planet p("planet attack power planet");
    
    // the planet must not generate damage
    //if(p.attack(t) > 0)
    //    return false;
    return true;
}

bool testPlanets(){
    bool success = true;
    //if(!testInheritance<Target, Planet>())
    //    success = false;
    if(!testPlanetDestroyability())
        success = false;
    if(!testPlanetAttackPower())
        success = false;
    return success;
}

/*
*
*
*
* * * * * * * * * * * * * * * * * * * * * * SPACESHIP TESTING
*
*
*
*/

// Can attack other targets
bool testSpaceshipAttackAbility(){
    Spaceship t("spaceship attack target");
    Spaceship p("spaceship attack aggressor");
    
    // the spaceship must generate damage
    if(p.attack(t) > 0){
        log("spaceship could damage other spaceship");
        return true;
    }
    else{
        fail("spaceship generated no damage");
        return false;
    }
}

// CHANGED: When attacked, shields are damaged. When shields <= 0, it explodes.
// when attacked, shields are damaged. if the shields are < 0, the hull is damaged. if the hull is <= 0, it explodes
bool testSpaceshipDamageAbility(){
    Spaceship sAttack("spaceship damage ability attackship"), s("spaceship damage ability targetship");
    int shield = s.getShields(), hull = s.getHull();
    
    sAttack.attack(s);
    
    // does the shield even get damaged
    if(s.getShields() >= shield){
        fail("no shield damage");
        return false;
    }
    else
        log("shield damage ok");
        
    while(s.getShields() > 0)
        sAttack.attack(s);
    
    // does the hull even get damage
    if(s.getHull() >= hull){
        fail("no hull damage");
        return false;
    }
    else
        log("hull damage ok");
        
    while(s.getHull() > 0)
        sAttack.attack(s);
        
    // successfully destroyed
    if(!s.isDestroyed()){
        fail("not destroyed");
        return false;
    }
    else
        log("ship destroyed");
    return true;
}

bool testSpaceships(){
    bool success = true;
    //if(!testInheritance<Target, Spaceship>())
    //    success = false;
    if(!testSpaceshipAttackAbility())
        success = false;
    if(!testSpaceshipDamageAbility())
        success = false;
    return success;
}

/*
*
*
*
* * * * * * * * * * * * * * * * * * * * * * DEATHSTAR TESTING
*
*
*
*/

bool testDeathStarShieldScaleOk(){
    Spaceship s("deathstar shield scale test ship");
    DeathStar d;
    
    // shields too small
    if(d.getShields() / 10 < s.getShields())
        return false;
    return true;
}

bool testDeathStarSometimesExplodes(){
    Spaceship s("deathstar sometimes explodes test ship");
    DeathStar d;
    size_t tries = 0;
    
    // does the deathstar ever explode?
    while(!d.isDestroyed() && tries < 1000){
        s.attack(d);
        tries++;
        // random chance kicked in, restart
        if(d.isDestroyed()){
            if(d.getHealth() > 0){
                d = DeathStar();
            }
            else{
                break;
            }
        }
    }
    
    // something is fishy here, took an extreme amount of tries
    if(tries == 1000){
        fail("deathstar never exploded with health down");
        return false;
    }
    else
        log("deathstar exploded with health down");
    
    
    // reset for random chance testing
    tries = 0;
    d = DeathStar();
    
    while(!d.isDestroyed() || tries < 1000){
        s.attack(d);
        tries++;
        // random chance kicked in, ok
        if(d.isDestroyed() && d.getShields() > 0)
            break;
        // shields are down, restart
        else if (d.isDestroyed() && d.getShields() <= 0)
            d = DeathStar();
    }
    
    // something is fishy here, took an extreme amount of tries
    if(tries == 1000){
        fail("deathstar never random exploded");
        return false;
    }
    else
        log("deathstar random exploded kicked in");
    return true;
}

bool testDeathStar(){
    bool success = true;
    //if(!testInheritance<Spaceship, DeathStar>())
    //    success = false;
    if(!testDeathStarShieldScaleOk())
        success = false;
    if(!testDeathStarSometimesExplodes())
        success = false;
    return success;
}

/*
*
*
*
* * * * * * * * * * * * * * * * * * * * * * OVERALL TESTING
*
*
*
*/

void testAll(){
    std::ofstream out("log.txt");
    auto cerrbuf = std::cerr.rdbuf(out.rdbuf());
    auto clogbuf = std::clog.rdbuf(out.rdbuf());
    if(testTargets())
        std::clog << "targets ok\n########################\n"<< std::endl;
    else
        std::cerr << "targets failed\n########################\n" << std::endl;

    if(testPlanets())
        std::clog << "planets ok\n########################\n"<< std::endl;
    else
        std::cerr << "planets failed\n########################\n" << std::endl;

    if(testSpaceships())
        std::clog << "spaceships ok\n########################\n"<< std::endl;
    else
        std::cerr << "spaceships failed\n########################\n" << std::endl;
        
    if(testDeathStar())
        std::clog << "deathstar ok\n########################\n"<< std::endl;
    else
        std::cerr << "deathstar failed\n########################\n" << std::endl;
        
    std::clog.rdbuf(clogbuf);
    std::cerr.rdbuf(cerrbuf);
}
