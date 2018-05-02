//
//  Entity–component–system is a system which will allow
//  easy management of game objects and all of the information they hold about themselves
//

#ifndef ECS_hpp
#define ECS_hpp

#include <stdio.h>
#include "ECS.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <array>

class Component; //an attribute of a game object, essentially
class Entity; //a game object
class Manager;

using ComponentID = std::size_t; //like an int, but actual size is platform dependant. Also can maybe hold more than numbers?
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() //inline is a size-exectution time tradeoff - faster but code is bigger https://www.youtube.com/watch?v=Yh1mJlip3hw
{
    static ComponentID lastID = 0; //how does this increment?? - it works like a janky closure, where the variable only exists inside this scope, but the static variable can
    return lastID++;               //only be initalized once, so every time after the first that part of the code is ignored and it only increments - pretty hype
}

template <typename T> inline ComponentID getComponentTypeID() noexcept //template to create a new type of component and get the id of new component
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID; //()
}

constexpr std::size_t maxComponents = 32; //max number of components is 32 - this is declared at compile time to save runtime
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>; //bitset is essentially an array that holds booleans - 32 bits in this case.
using GroupBitset = std::bitset<maxGroups>;
using ComponentArray = std::array<Component *, maxComponents>; //array of components which is 32 components long

class Component //component is an attribute of an entity which can hold all sorts of different data
{
public:
    Entity *entity;  //points to the entity which owns it
    
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
    
    virtual ~Component() {}
};

class Entity //some sort of game object which will hold components
{
private:
    Manager &manager;
    bool active = true; //a flag to let the game know that it should not be destroyed
    std::vector<std::unique_ptr<Component>> components; //a dynamic-sized array of components of this entity
    bool clicked = false;
    
    ComponentArray componentArray; //see line 37
    ComponentBitSet componentBitSet; //see line 36
    GroupBitset groupBitset;
    
public:
    
    Entity(Manager &mManager) : manager(mManager) {}
    
    void update()
    {
        for(auto& c : components) c->update(); //loop through all of the components of the entity and update them
    }
    
    void draw() {
        for(auto& c : components) c->draw(); //loop through all of the components of the entity and draw them
    }
    bool isActive() const { return active; }
    void destroy() {active = false;}
    
    bool hasGroup(Group mGroup)
    {
        return groupBitset[mGroup];
    }
    
    void addGroup(Group mGroup);
    void delGroup(Group mGroup)
    {
        groupBitset[mGroup] = false;
    }
    
    template <typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>]; //checks for 1 in the bitset to see if the component exists
    }
    
    template <typename T, typename... TArgs> T &addComponent(TArgs&&... mArgs) //wrapper for adding a component of variable type - https://www.youtube.com/watch?v=srdwFMZY3Hg
    {
        T *c(new T(std::forward<TArgs>(mArgs)...)); //c is the new component of type T, with type args TArgs and constructor arguments mArgs
        c->entity = this;  //c's entity variable points back to the Entity that called addComponent
        std::unique_ptr<Component> uPtr{ c }; //create a smart pointer pointing to c
        components.emplace_back(std::move(uPtr)); //put that pointer on the vector the holds pointers to all the components - guessing this is used for garbage memory management
        
        componentArray[getComponentTypeID<T>()] = c; //put the component in the component array in accordance to its unique ID
        componentBitSet[getComponentTypeID<T>()] = true; //flip the corresponding bitset value
        
        c->init(); //initialize the component
        return *c; //return a pointer to said component
    }
    
    template<typename T> T &getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]); //gets the component from the component array - more of a dict, really
        return *static_cast<T*>(ptr); //returns a static pointer to the component
    }
    
    bool isClicked(){ return clicked; }
    
    void setClick(bool c) { clicked = c; }
    
//    gameobject.getComponent<PositionComponent>().setXpos(25); --- example of how to use the entity class
    
};

class Manager  //manager of all of the entities
{
private:
    
    std::vector<std::unique_ptr<Entity>> entities; //vector of ptrs to all the entities
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
    
    void update()
    {
        for (auto &e : entities) e->update(); //update all of the entities
    }
    
    void draw()
    {
        for (auto &e : entities) e->draw(); //draw all the entities
    }
    
 
    void refresh()
    {
        
        for(auto i(0u); i < maxGroups; i++)
        {
            auto &v(groupedEntities[i]);
            v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity *mEntity){return !mEntity->isActive() || !mEntity->hasGroup(1);}), std::end(v));
        }
        
        entities.erase(std::remove_if(begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity){ return !mEntity->isActive();}), std::end(entities));
        
        //seriously wtf is this - vector.erase take (iterator first, iterator last - this is the std::end(entities) part;
        //the iterator first madness is std::remove_if(begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity){ return !mEntity->isActive();})
        
        /*std::remove_if takes in (ForwardIt first, ForwardIt last, UnaryPredicate p) - the start and end are self-explanatory. The unary predicate starts
         with the square brackets- it is a labda that returns a boolean value of  whether the entity being iterated over is active or not.
         the [] is for passing in vars but not as arguments (idk why you would do this?), which we arent doing - we just pass in a reference to the
         current entity as an arg. It also returns opposite of isActive. I assume thats becuase 1 = delete in remove_if*/
    }
    
    void AddToGroup(Entity *mEntity, Group mGroup)
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }
    
    std::vector<Entity*>& getGroup(Group mGroup)
    {
        return groupedEntities[mGroup];
    }
    
    Entity &addEntity()
    {
        Entity *e = new Entity(*this); //create new entity
        std::unique_ptr<Entity> uPtr{ e }; //create a smart pointer for it
        entities.emplace_back(std::move(uPtr)); //add smart pointer to back of the vector of all entities
        return *e; //return regular pointer to entity
    }
    
};

#endif /* ECS_hpp */
