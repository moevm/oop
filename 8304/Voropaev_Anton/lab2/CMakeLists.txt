cmake_minimum_required(VERSION 3.15)
project(OOP)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP main.cpp Field.cpp Unit.cpp FieldIterator.cpp Field.h Unit.h FieldIterator.h
        Base.cpp Base.h "Unit Attributes/Location.cpp" "Unit Attributes/Location.h" "Unit Attributes/Health.cpp"
        "Unit Attributes/Health.h" "Unit Attributes/Damage.cpp" "Unit Attributes/Damage.h" "Unit Attributes/Armor.cpp"
        "Unit Attributes/Armor.h" Object.h "Neutral objects/HealingFountain.cpp" "Neutral objects/HealingFountain.h" "Neutral objects/HealingFountain.cpp" "Neutral objects/HealingFountain.h" "Neutral objects/Neutral.h" "Neutral objects/MaradeursCamp.cpp" "Neutral objects/MaradeursCamp.h" "Neutral objects/TrainingCamp.cpp" "Neutral objects/TrainingCamp.h" "Neutral objects/Forge.cpp" "Neutral objects/Forge.h" "Neutral objects/Stretegy.cpp" "Neutral objects/Stretegy.h" Cell.h Landscapes/Landscape.h Landscapes/Fog.cpp Landscapes/Fog.h Landscapes/Desert.cpp Landscapes/Desert.h Landscapes/Mountains.cpp Landscapes/Mountains.h Landscapes/LandscapeProxy.cpp Landscapes/LandscapeProxy.h)