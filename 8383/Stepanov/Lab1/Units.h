
#ifndef Units_h
#define Units_h


class Unit {

 public:
    char name[3];
    int helth;
    int armor;
    int attack;
    int x;
    int y;
    
 
    void virtual hit () = 0;
    void virtual motion () = 0;
    void virtual setName (char unitNumber) = 0;
    char virtual *getName () = 0;
    void virtual setXY(int x, int y) = 0;
    int virtual getX() = 0;
    int virtual getY() = 0;
};

//------------------------------------------------------------------------------

class Smoker: public Unit {
public:
    void hit () override {
        std::cout << "I'm smoking" << std::endl;
    }
    
    void motion () override {
        std::cout << "I'm going and smoking" << std::endl;
    }
    
    void setName (char unitNumber) override{
        if (unitNumber % 2 == 0) {
            name[0] = unitNumber;
            name[1] = '$';
        } else {
            name[0] = '$';
            name[1] = unitNumber;
        }
        name[2] = '\0';
    }
    
    char* getName () override {
        return name;
    }
    
    void setXY(int x, int y) override {
        this->x = x;
        this->y = y;
    }
   
    int getX () override {
        return x;
    }
    int getY () override {
        return y;
    }
    
};

class ProtectedSmoker: public Smoker {
    
public:
    ProtectedSmoker (char num) {
        helth = 15;
        armor = 15;
        attack = 1;
        setName(num);
        
    }
};

class StrongSmoker: public Smoker {
    
public:
    StrongSmoker (char num) {
        helth = 10;
        armor = 10;
        attack = 3;
        setName(num);
    }
};

//------------------------------------------------------------------------------

class Runner: public Unit {
public:
    void hit () override {
        std::cout << "I'm hit and you're losing your points" << std::endl;
    }
    
    void motion () override {
        std::cout << "I'm going very fast" << std::endl;
    }
    
   void setName (char unitNumber) override{
        if (unitNumber % 2 == 0) {
            name[0] = unitNumber;
            name[1] = '!';
        } else {
            name[0] = '!';
            name[1] = unitNumber;
        }
        name[2] = '\0';
    }
    
    char* getName () override {
        return name;
    }
    
    void setXY(int x, int y) override {
        this->x = x;
        this->y = y;
    }
    
    int getX () override {
        return x;
    }
    int getY () override {
        return y;
    }
   
    
};


class ProtectedRunner: public Runner {
public:
    
    ProtectedRunner (char num){
        helth = 8;
        armor = 13;
        attack = 5;
    
        setName(num);
    }
};


class StrongRunner: public Runner {
public:
    
    StrongRunner (char num){
        helth = 8;
        armor = 8;
        attack = 7;

        setName(num);
    }
};

//------------------------------------------------------------------------------

class Shooter: public Unit {
public:
    void hit () override {
          std::cout << "I'm shooting at you" << std::endl;
      }
      
      void motion () override {
          std::cout << "I'm going and wathching you" << std::endl;
      }
    
    void setName (char unitNumber) override{
        if (unitNumber % 2 == 0) {
            name[0] = unitNumber;
            name[1] = '>';
        } else {
            name[0] = '<';
            name[1] = unitNumber;
        }
        name[2] = '\0';
    }
    
    char* getName () override {
        return name;
    }
    
    void setXY(int x, int y) override {
        this->x = x;
        this->y = y;
    }
    
    int getX () override {
        return x;
    }
    int getY () override {
        return y;
    }
   
};

class ProtectedShooter: public Shooter {
    
public:
    ProtectedShooter (char num) {
        helth = 5;
        armor = 10;
        attack = 4;

        
        setName(num);
        
    }
};


class StrongShooter: public Shooter {
    
public:
    StrongShooter (char num) {
        helth = 5;
        armor = 5;
        attack = 6;


        setName(num);
        
        
    }
};

//------------------------------------------------------------------------------

class UnitsFactory {
public:
    
    
    virtual Unit* CreateUnit (char name, bool isProtected) = 0;

};

class ConcreteUnitShooter: public UnitsFactory {
public:
    
    Unit* CreateUnit (char num, bool isProtected) override {
        if (isProtected){
            return new ProtectedShooter(num);
        }
        
        return new StrongShooter( num);
        
    }
    
};


class ConcreteUnitSmoker: public UnitsFactory {
public:
    
    Unit* CreateUnit (char num, bool isProtected) override {
        if (isProtected){
            return new ProtectedSmoker(num);
        }
        
        return new StrongSmoker( num);
        
    }
    
};


class ConcreteUnitRunner: public UnitsFactory {
public:
    
    Unit* CreateUnit (char num, bool isProtected) override {
        if (isProtected){
            return new ProtectedRunner( num);
        }
        
        return new StrongRunner( num);
        
    }
    
};


#endif /* Units_h */
