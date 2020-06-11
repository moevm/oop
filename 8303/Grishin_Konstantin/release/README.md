# John C. Alastor project  
## EdGame
### University term project
So, this is a project which made only for education purposes  
It means there too many things which don't work or work wrong

---

### Settings
To change some rules of game you should change couple of lines in the *main.cpp*  
```C++
52    TGame<Easy> *game = nullptr;
53    Easy rule(Team::Neutral);
```
You can change *Easy* to *Normal*. It affects on game:  
Normal - You get default points for various events. At start you have 1 point for 1 worker. You lose, when you are have not units and points.
Easy - You get double multiplicated points for varioius events. At starts you have 10 points. You lose, when your base is destroyed.
To change initial map you should change *Level* variable in
```C++
143   game = new TGame(*window, Level::default_level_1(), rule);
```
I set it as `Level::default_level_1()`, but you can set it either as `Level::default_level_2()`, or create your own.  

### How to play this weird thing.
1. When you run this, there is the main menu. Press **New Game** to start.  
2. There is game field, in the botton-right corner you can see which player turn and his points.  
As the first thing you should create worker. Press on base, then on the icon on interface.  
3. Now you can see your worker. To leave interface, either tap on the object you have selectedor press ESC.
Now you can press on your worker (if you hold right mouse on the object or interface element
you can see various information) and try to interract with it. I recommen go to the tree or stone,
then press on the work button (with hammer on it), then on the near tree or object.  
Now your worker treating the object and you can't do anything.  
4. Pass the move to the next player, big white button in the top-right corner.
So, for the first turn second player should do the same.
5. When the moves of the two players have passed, the glopal step of field is made.
Workers reduced durability of their objects. When an object is broken, a points is awarded to the players.
Also, during a global step of field, the victory of player is checked.
6. When player when a player gets enough points. His workers can built battle structures.
Magic tower and barrack, they can create units, which can deal damage.  
7. You can save your game. Just press 'P' button, then click on "save and exit" line, or press ESC to quit menu.  
  
Now you now how to create and use units. All other mechanics are more or less intuative (It seems to me).  
Experement with them.  

After exiting the game, you can viev logs in *game_log.log* file near the *.exe*.  

---
### Building
The main thing - you should include SFML-2.5.1.
Put all files from resources to directory of .exe after building.
Project built with Qt Creator Community 4.12.0 IDE. Qt libs were not used.
link to *Easy* build: https://drive.google.com/drive/folders/1ioYNHGB7F2fvnp0ysvp7F_hyrmqddeXA?usp=sharing 

