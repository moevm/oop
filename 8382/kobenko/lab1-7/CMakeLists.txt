cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp LightArmy.cpp LightArmy.h Units.cpp Units.h DarkArmy.cpp DarkArmy.h Infantry.cpp Infantry.h Cavalry.cpp Cavalry.h Archers.cpp Archers.h Field.cpp Field.h game.cpp game.h Landshaft.cpp Landshaft.h LightBase.cpp LightBase.h DarkBase.cpp DarkBase.h defaultCeil.cpp defaultCeil.h deathCeil.cpp deathCeil.h AwesomeCeil.cpp AwesomeCeil.h Neutral.cpp Neutral.h DeathItem.cpp DeathItem.h AwesomeItem.cpp AwesomeItem.h Heal.cpp Heal.h BigHeal.cpp BigHeal.h Logg.cpp Logg.h LogF.cpp LogF.h Rules.cpp Rules.h templates.cpp)