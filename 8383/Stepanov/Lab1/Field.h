#ifndef Field_h
#define Field_h




class Cell {
  
    bool isUsed = false;
    char nameUnit[3] = "  ";
public:
    void cellUsed(){
        isUsed = true;
    }
    
    void cellNotUsed(){
        isUsed = false;
    }
    
    bool getIsUsed(){
        return isUsed;
    }
    
    void setUnitName(char name[]){
        nameUnit[0] = name[0];
        nameUnit[1] = name[1];
        nameUnit[2] = name[2];
        
        
        isUsed = true;
    }
    
    void clearCell(){
        isUsed = false;
        nameUnit[0] = ' ';
        nameUnit[1] = ' ';
        nameUnit[2] = '\0';
    }
    
    
    char* getUnitName(){
        return nameUnit;
    }
};


class Iterator {
    
    int x, y;
    Cell** place;
    int maxX, maxY;
    bool isEnd;
    
public:
    
    
    Iterator (Cell **place, int x, int y){
        this->place = place;
        this->x = 0;
        this->y = 0;
        maxX =  x-1;
        maxY = y-1;
        isEnd = false;
    }
    
    void first (){
        x = 0;
        y = 0;
        std::cout << x <<" " << y << std::endl;
    }
    
    void next () {
        if (x == maxX && y == maxY){
            isEnd = true;
        } else if (x == maxX) {
            
            x = 0;
            y++;
            std::cout << x <<" " << y << std::endl;
           
        } else {
            x++;
             std::cout << x <<" " << y << std::endl;
        }
    }
    
    Cell *getCell () {
        if (isEnd) return NULL;
        return &place[x][y];
    }
    






class Field {
    
    friend class Iterator;
    
    int x, y;
    Cell** place;
    
    int busyCells = 0;
    int maxBusyCells;
    
public:
    
    Field () {
        x = 0;
        y = 0;
        place = NULL;
        maxBusyCells = 0;
    }
    
    
    Field ( Iterator::Field &copyedField){ // конструктор копирования
        x = copyedField.getX();
        y = copyedField.getY();
        
        place = copyedField.getCopyField();
        busyCells = copyedField.getBusyCells();
        
    }
    
    Field (Iterator::Field &&copyedField){ // конструктор перемещения
        x = copyedField.x;
        y = copyedField.y;
        
        place = copyedField.place;
        busyCells = copyedField.busyCells;
        maxBusyCells = copyedField.maxBusyCells;
        
        
        std::cout << "я работаю" << std::endl;
        copyedField.place = nullptr;
     
        
    }

        
    
 
    ~Field () {
        for (int i = 0; i < x; i++){
     
            delete [] place[i];
        }
        
        delete [] place;
    }
    
 
    bool createField(int x, int y){
        if (x < 6){
            std::cout << "X не может быть меньше 6 клеток" << std::endl;
            return false;
        } else {
            this->x = x;
        }
               
            if (y < 6){
                   std::cout << "Y не может быть меньше 6 клеток" << std::endl;
                return false;
            } else {
                this->y = y;
            }
               
               printXY();
               
               this->place = new Cell*[this->x];
              
               
               for (int i = 0; i < this->x; i++){
                   place[i] = new Cell[this->y];
                   
               }
        
        maxBusyCells = x*y;
        return true;
    }

    
    
    void printXY(){
        std::cout << "x = " << x << " " << "y = " << y << std::endl;
    }
    
    void printField () {

        for (int i = -1; i <= y; i++){
            for (int j = -1; j <= x; j++){

                if ((i == -1 && j == -1) || (i == -1 && j == x) ||
                    (i == y && j == -1) || (i == y && j == x)){

                    std::cout << " ";

                } else if (i == -1 || i == y) {

                    std::cout << "--";

                } else if (j == -1 || j == x) {

                    std::cout << "|";

                } else {
                    std::cout << place[j][i].getUnitName();

                }

            }
            std::cout << std::endl;
        }
    }
    
    bool cellIsUsed(int x, int y){
        return place[x][y].getIsUsed();
    }
    
    bool replaceUnit(int x, int y, int toX, int toY){ // a to b
        if(place[toX][toY].getIsUsed()) return false;
        
        Cell &a = place[x][y];
        Cell &b = place[toX][toY];
        
        b.setUnitName(a.getUnitName());
        a.clearCell();
        return true;
        
    }
    
    bool takeUnit(char name[], int x, int y){
        
        if (maxBusyCells == busyCells){
            std::cout << "Все клетки заняты" << std::endl;
            return false;
        }
        
        place[x][y].setUnitName(name);
        busyCells++;
        return true;
    }
    
    Cell** getCopyField (){
        
        Cell** cField;
        
        cField = new Cell*[this->x];
         
         for (int i = 0; i < this->x; i++){
             cField[i] = new Cell[this->y];
             
             for (int j = 0; j < y; j++){
                 if (place[i][j].getIsUsed()){
                     cField[i][j].setUnitName(place[i][j].getUnitName());
                 }
             }
         }
        
        return cField;
    }
    
    Iterator* getIterator (){
        
        return new Iterator (place,x ,y);
     
        
    }
    
    int getX (){ return x;}
    int getY (){ return y;}
    int getBusyCells (){ return busyCells;}
    
};



    
};

#endif
