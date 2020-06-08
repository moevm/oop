#include <typeinfo>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifndef LOG
#define LOG
#include "log.cpp"
#endif

#ifndef TERRAIN
#define TERRAIN
#include "terrain.cpp"
#endif

#ifndef PLAYER
#define PLAYER
#include "player.cpp"
#endif
using std::cin;
using std::cout;
using std::endl;
class Game
{
public:
    Logger gameLog;
    Terrain terrain;
    int playerCount = 2;
    Player lobby[2];
    int turns = 0;

    int percentRoll( int percent )
    {
    srand(time(0));
    return (rand() % 100) < percent ? 1 : 0;
    }

    void moveUnit( UnitBase* u, int dx, int dy)
    {
        if(int(sqrt(dx*dx + dy*dy)) > u->movementRange)
        {
            cout << "This unit can\'t move so far away!";
            return;
        }
        int X = u->x + dx;
        int Y = u->y + dy;
        if( terrain.isOutOfBounds(X, Y))
        {
            cout << "Out of bounds!";
            return;
        }
        if( terrain.isOccupied(X, Y))
        {
            cout << "There is another unit!";
            return;
        }
        u->x = X;
        u->y = Y;

        gameLog.moveLog( u->name, u->faction, dx, dy);
    };

    void attack( UnitBase* attacker, UnitBase* target)
    {
        gameLog.attackLog(attacker->name, attacker->faction, target->name, target->faction);

        int dx = target->x - attacker->x;
        int dy = target->y - attacker->y;
        if(int(sqrt(dx*dx + dy*dy)) > attacker->attackRange)
        {
            cout << "Target is too far!";
            return;
        }
        target->HP -= attacker->damage * percentRoll( int( 50 + attacker->pierce / (100 + attacker->pierce) - target->armor / (100 + attacker->armor) ) );
        if(target->HP < 0)  target->HP = 0;
        if (target->HP == 0)
        {
            if(target->name == "Headquarters")
                return;
            terrain.removeUnit( target );
            for(int i = 0; i < terrain.unitCount; i++)
            {
                if(typeid(terrain.unitList[i]) == typeid(UnitHQ*))
                    ((UnitHQ*) terrain.unitList[i])->onUnitDie( target );
            };
            delete target;
        }
    };

    void attack( UnitBase* attacker, EntityArmor* target)
    {
        gameLog.attackLog(attacker->name, attacker->faction, target->name, target->faction);

        int dx = target->x - attacker->x;
        int dy = target->y - attacker->y;
        if(int(sqrt(dx*dx + dy*dy)) > attacker->attackRange)
        {
            cout << "Target is too far!";
            return;
        }
        attacker->armor += attacker->armor <= 95 ? 5 : 100 - attacker->armor;
        terrain.removeUnit( target );
        delete target;
    }
    void attack( UnitBase* attacker, EntityAmmo* target)
    {
        gameLog.attackLog(attacker->name, attacker->faction, target->name, target->faction);

        int dx = target->x - attacker->x;
        int dy = target->y - attacker->y;
        if(int(sqrt(dx*dx + dy*dy)) > attacker->attackRange)
        {
            cout << "Target is too far!";
            return;
        }
        attacker->pierce += attacker->pierce <= 95 ? 5 : 100 - attacker->pierce;
        terrain.removeUnit( target );
        delete target;
    }
    void attack( UnitBase* attacker, EntityOptics* target)
    {
        gameLog.attackLog(attacker->name, attacker->faction, target->name, target->faction);

        int dx = target->x - attacker->x;
        int dy = target->y - attacker->y;
        if(int(sqrt(dx*dx + dy*dy)) > attacker->attackRange)
        {
            cout << "Target is too far!";
            return;
        }
        attacker->attackRange++;
        terrain.removeUnit( target );
        delete target;
    }
    void attack( UnitBase* attacker, EntityMedkit* target)
    {
        gameLog.attackLog(attacker->name, attacker->faction, target->name, target->faction);

        int dx = target->x - attacker->x;
        int dy = target->y - attacker->y;
        if(int(sqrt(dx*dx + dy*dy)) > attacker->attackRange)
        {
            cout << "Target is too far!";
            return;
        }
        attacker->HP += 10;
        terrain.removeUnit( target );
        delete target;
    }

    void placeBonus( std::string entityType, int x, int y )
    {
        if(terrain.isOccupied(x, y) || terrain.isOutOfBounds(x, y)) return;

        if( entityType == "Armor" )   terrain.addUnit( new EntityArmor  (x, y) ); else
        if( entityType == "Ammo" )    terrain.addUnit( new EntityAmmo   (x, y) ); else
        if( entityType == "Optics" )  terrain.addUnit( new EntityOptics (x, y) ); else
        if( entityType == "Medkit" )  terrain.addUnit( new EntityMedkit (x, y) ); else
            throw "There are no " + entityType + "s today. Come tomorrow :3";

    }

    void createUnit(std::string unitType, UnitHQ* hq)
    {
        int destX = hq->x, destY = hq->y;
        if(!terrain.isOccupied(destX-1, destY-1) && !terrain.isOutOfBounds(destX-1, destY-1)) {destX = hq->x-1; destY = hq->y-1;} else
        if(!terrain.isOccupied(destX+0, destY-1) && !terrain.isOutOfBounds(destX+0, destY-1)) {destX = hq->x+0; destY = hq->y-1;} else
        if(!terrain.isOccupied(destX+1, destY-1) && !terrain.isOutOfBounds(destX+1, destY-1)) {destX = hq->x+1; destY = hq->y-1;} else
        if(!terrain.isOccupied(destX-1, destY+0) && !terrain.isOutOfBounds(destX-1, destY+0)) {destX = hq->x-1; destY = hq->y+0;} else
        if(!terrain.isOccupied(destX+1, destY+0) && !terrain.isOutOfBounds(destX+1, destY+0)) {destX = hq->x+1; destY = hq->y+0;} else
        if(!terrain.isOccupied(destX-1, destY+1) && !terrain.isOutOfBounds(destX-1, destY+1)) {destX = hq->x-1; destY = hq->y+1;} else
        if(!terrain.isOccupied(destX+0, destY+1) && !terrain.isOutOfBounds(destX+0, destY+1)) {destX = hq->x+0; destY = hq->y+1;} else
        if(!terrain.isOccupied(destX+1, destY+1) && !terrain.isOutOfBounds(destX+1, destY+1)) {destX = hq->x+1; destY = hq->y+1;} else
            throw "The HQ is a bit crowded :c";

        if( unitType == "Sniper" )      terrain.addUnit( hq->makeSniper     ( destX, destY ) ); else
        if( unitType == "AntiTank" )    terrain.addUnit( hq->makeAntiTank   ( destX, destY ) ); else
        if( unitType == "IFV" )         terrain.addUnit( hq->makeIFV        ( destX, destY ) ); else
        if( unitType == "Tank" )        terrain.addUnit( hq->makeTank       ( destX, destY ) ); else
        if( unitType == "Bomber" )      terrain.addUnit( hq->makeBomber     ( destX, destY ) ); else
        if( unitType == "Interceptor" ) terrain.addUnit( hq->makeInterceptor( destX, destY ) ); else
            throw "There are no " + unitType + "s today. Come tomorrow :3";
        };

    void loginPlayers()
    {
        for(int p = 0; p < playerCount; p++)
        {
            cout << "\nPlayer " << p+1 << " name: ";
            cin >> lobby[p].faction;
            lobby[p].money = 3000;
        }
    }

    void placeHQs()
    {
        for(int p = 0; p < playerCount; p++)
        {
            cout << "\nEnter coordinates for your base, " << lobby[p].faction <<" [\"x y\"]: ";
            int x, y;
            cin >> x >> y;
            if(terrain.isOccupied(x, y) || terrain.isOutOfBounds(x, y)) throw "Unable to place HQ here";
            UnitHQ* tmp = new UnitHQ( lobby[p].faction, x, y, terrain.unitCap);
            lobby[p].hq = tmp;
            terrain.addUnit( tmp );

            gameLog.placeHQLog( lobby[p].faction, x, y);
        }
    }

    void update()
    {
        for(int p = 0; p < playerCount; p++)
        {
            terrain.render();
            cout << lobby[p].faction << " turn:\n";
            turn(&(lobby[p]));
            Sleep(750);
            cout << "\nPress enter for next turn.";
            cin.get();
            cin.get();
        }
    };

    void turn(Player* p)
    {
        cout << "\nBase HP: " << p->hq->HP << "\nFunds: " << p->money << "$\nUnit list:\n";
        for(int i = 0; i < p->hq->unitCount; i++)
        cout << p->hq->unitList[i]->name << "(" << p->hq->unitList[i]->HP << "% HP)"<<" at [ " << p->hq->unitList[i]->x << ", " << p->hq->unitList[i]->y << " ]" << endl;
        string buyOrder;
        //BUY PHASE
        cout << "BUY PHASE [use \"buy X\" to buy X or anything else to skip]:\n";
        cout << " 1 - [INF] Sniper (200$)\n";
        cout << " 2 - [INF] AntiTank (300$)\n";
        cout << " 3 - [VEH] IFV (500$)\n";
        cout << " 4 - [VEH] Tank (800$)\n";
        cout << " 5 - [AIR] Bomber (1500$)\n";
        cout << " 6 - [AIR] Interceptor (1200$)\n";
        cin >> buyOrder;
        if (buyOrder == "buy")
        {
            int pos;
            cin >> pos;
            switch(pos)
            {
                case 1:
                    {
                        if( p->money >= 200)
                        {
                            cout << "Building...";
                            p->money -= 200;
                            createUnit("Sniper", p->hq);
                            gameLog.buyLog( p->faction, "Sniper", 200);
                        } else
                        {
                            cout << "Insufficient funds.";
                        }
                    }
                break;
                case 2:
                    {
                        if( p->money >= 300)
                        {
                            cout << "Building...";
                            p->money -= 300;
                            createUnit("AntiTank", p->hq);
                            gameLog.buyLog( p->faction, "AntiTank", 300);
                        } else
                        {
                            cout << "Insufficient funds.";
                        }
                    }
                break;
                case 3:
                    {
                        if( p->money >= 500)
                        {
                            cout << "Building...";
                            p->money -= 500;
                            createUnit("IFV", p->hq);
                            gameLog.buyLog( p->faction, "IFV", 500);
                        } else
                        {
                            cout << "Insufficient funds.";
                        }
                    }
                break;
                case 4:
                    {
                        if( p->money >= 800)
                        {
                            cout << "Building...";
                            p->money -= 800;
                            createUnit("Tank", p->hq);
                            gameLog.buyLog( p->faction, "Tank", 800);
                        } else
                        {
                            cout << "Insufficient funds.";
                        }
                    }
                break;
                case 5:
                    {
                        if( p->money >= 1500)
                        {
                            cout << "Building...";
                            p->money -= 1500;
                            createUnit("Bomber", p->hq);
                            gameLog.buyLog( p->faction, "Bomber", 1500);
                        } else
                        {
                            cout << "Insufficient funds.";
                        }
                    }
                break;
                case 6:
                    {
                        if( p->money >= 1200)
                        {
                            cout << "Building...";
                            p->money -= 1200;
                            createUnit("Interceptor", p->hq);
                            gameLog.buyLog( p->faction, "Interceptor", 1200);
                        } else
                        {
                            cout << "Insufficient funds.";
                        }
                    }
                break;
                default: {cout << "There are no position #" << pos << ", skipping...\n";} break;
            }
        }
        //MOVE PHASE
        cin.get();
        cout << "\nMOVE PHASE: ";
        cout << "\nFor each unit, type \"move X Y\" to move it by X Y or anything else to skip: ";
        for( int unit = 0; unit < p->hq->unitCount; unit++)
        {
            cout << endl << p->hq->unitList[unit]->name << " at [" << p->hq->unitList[unit]->x << ", " << p->hq->unitList[unit]->y <<"]: ";
            string order;
            cin >> order;
            if(order == "move")
            {
                int dx, dy;
                cin >> dx >> dy;
                moveUnit( p->hq->unitList[unit], dx, dy);
            }
        }
        //ATTACK PHASE
        cin.get();
        cout << "\nATTACK PHASE: ";
        cout << "\nFor each unit, type \"attack X Y\" to attack position X Y or anything else to skip: ";
        for( int unit = 0; unit < p->hq->unitCount; unit++)
        {
            cout << endl << p->hq->unitList[unit]->name << " at [" << p->hq->unitList[unit]->x << ", " << p->hq->unitList[unit]->y <<"]: ";
            string order;
            cin >> order;
            if(order == "attack")
            {
                int x, y;
                cin >> x >> y;
                if(terrain.isOccupied(x, y))
                {
                    int tgt = 0;
                    while(!(x == terrain.unitList[tgt]->x && y == terrain.unitList[tgt]->y))
                        tgt++;
                    attack(p->hq->unitList[unit], terrain.unitList[tgt]);
                } else cout << "\nNothing to shoot here.";
            }
        }
    }

    int checkWinConditions() // returns id of winner, -1 if game is still running, -2 if draw
    {
        if(  turns >= 64 ) return -2;
        if(lobby[0].hq->HP == 0) return 1;
        if(lobby[1].hq->HP == 0) return 0;
        return -1;
    }

    Game( int X, int Y, int UnitCap) : terrain(X, Y, UnitCap), gameLog("game.log")
    {
        loginPlayers();
        placeBonus( "Armor", 0, 4 );
        placeBonus( "Ammo", 5, 6 );
        placeBonus( "Optics", 2, 7 );
        placeBonus( "Medkit", 8, 3 );
        terrain.render();
        placeHQs();
        while(checkWinConditions() == -1) update();
        switch(checkWinConditions())
        {
            case -2: cout << "DRAW"; break;
            case 0: cout << lobby[0].faction <<" WINS"; break;
            case 1: cout << lobby[1].faction <<" WINS"; break;
            default: break;
        }
    };

    ~Game()
    {
        delete[] lobby;
    }
};
