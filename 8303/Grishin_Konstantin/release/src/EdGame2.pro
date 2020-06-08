QT -= gui


CONFIG += c++17
CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += SFML_STATIC

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


LIBS += -L"C:\SFML-2.5.1\lib"
LIBS += -L"C:\SFML-2.5.1\bin"

CONFIG(release, debug|release):
{
#audio libs
LIBS += -lsfml-audio
LIBS += -lopenal32
LIBS += -lFlac
LIBS += -lvorbisenc
LIBS += -lvorbisfile
LIBS += -lvorbis
LIBS += -logg

#SFML-Graphics Libs
LIBS += -lsfml-graphics
LIBS += -lfreetype

#SFML-Network libs
LIBS += -lsfml-network
LIBS += -lws2_32

#SFML-Window libs
LIBS += -lsfml-window
LIBS += -lopengl32
LIBS += -lgdi32

#SFML-system libs
LIBS += -lsfml-system
LIBS += -lwinmm
}

CONFIG(debug, debug|release):
{
#audio libs
LIBS += -lsfml-audio-d
LIBS += -lopenal32
LIBS += -lFlac
LIBS += -lvorbisenc
LIBS += -lvorbisfile
LIBS += -lvorbis
LIBS += -logg

#SFML-Graphics Libs
LIBS += -lsfml-graphics-d
LIBS += -lfreetype

#SFML-Network libs
LIBS += -lsfml-network-d
LIBS += -lws2_32

#SFML-Window libs
LIBS += -lsfml-window-d
LIBS += -lopengl32
LIBS += -lgdi32

#SFML-system libs
LIBS += -lsfml-system-d
LIBS += -lwinmm
}

#WINDOWS
INCLUDEPATH += "C:\SFML-2.5.1\include"
DEPENDPATH += "C:\SFML-2.5.1\include"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/animation.cpp \
    GUI/game_info_window.cpp \
    GUI/game_interface.cpp \
    GUI/game_interface_button.cpp \
    GUI/game_interface_manager.cpp \
    GUI/menu.cpp \
    GUI/menu_element.cpp \
    GUI/pause_screen.cpp \
    GUI/resource_manager.cpp \
    GUI/splash_messages.cpp \
    Rules/easy.cpp \
    Rules/normal.cpp \
    game.cpp \
    game_elements/buildings/barrack.cpp \
    game_elements/buildings/base.cpp \
    game_elements/buildings/tower.cpp \
    game_elements/cell.cpp \
    game_elements/cell_grid.cpp \
    game_elements/commands/cmd_attack.cpp \
    game_elements/commands/cmd_build.cpp \
    game_elements/commands/cmd_create_unit.cpp \
    game_elements/commands/cmd_destroy_object.cpp \
    game_elements/commands/cmd_move.cpp \
    game_elements/commands/cmd_use_item.cpp \
    game_elements/commands/cmd_work.cpp \
    game_elements/commands/commands_queue.cpp \
    game_elements/entity_constructor.cpp \
    game_elements/entity_container.cpp \
    game_elements/field.cpp \
    game_elements/field_iterator.cpp \
    game_elements/interface/cell_interface.cpp \
    game_elements/interface/entity_interface.cpp \
    game_elements/landscape/canyon_ls.cpp \
    game_elements/landscape/landscape.cpp \
    game_elements/landscape/landscape_library.cpp \
    game_elements/landscape/plain_ls.cpp \
    game_elements/landscape/rough_ls.cpp \
    game_elements/level.cpp \
    game_elements/master.cpp \
    game_elements/neutral_objects/concrete_objects/barrel.cpp \
    game_elements/neutral_objects/concrete_objects/healing_poition.cpp \
    game_elements/neutral_objects/concrete_objects/rock.cpp \
    game_elements/neutral_objects/concrete_objects/stamina_poition.cpp \
    game_elements/neutral_objects/concrete_objects/strength_poition.cpp \
    game_elements/neutral_objects/concrete_objects/tree.cpp \
    game_elements/units/common_unit_factory.cpp \
    game_elements/units/concrete_units/archer.cpp \
    game_elements/units/concrete_units/atrons.cpp \
    game_elements/units/concrete_units/berserk.cpp \
    game_elements/units/concrete_units/knight.cpp \
    game_elements/units/concrete_units/troll.cpp \
    game_elements/units/concrete_units/wizard.cpp \
    game_elements/units/concrete_units/worker.cpp \
    game_elements/units/magic_unit_factory.cpp \
    game_elements/units/melee.cpp \
    game_elements/units/nuker.cpp \
    game_elements/units/range.cpp \
    game_elements/units/stats_flyweight.cpp \
    game_elements/units/unit.cpp \
    game_elements/units/unit_action.cpp \
    game_elements/units/worker_unit_factory.cpp \
    logger.cpp \
    main.cpp \
    printer.cpp

HEADERS += \
    GUI/animation.h \
    GUI/game_info_window.h \
    GUI/game_interface.h \
    GUI/game_interface_button.h \
    GUI/game_interface_manager.h \
    GUI/menu.h \
    GUI/menu_element.h \
    GUI/menu_state.h \
    GUI/pause_screen.h \
    GUI/resource_manager.h \
    GUI/splash_messages.h \
    Rules/easy.h \
    Rules/normal.h \
    game.h \
    game_elements/buildings/barrack.h \
    game_elements/buildings/base.h \
    game_elements/buildings/building.h \
    game_elements/buildings/tower.h \
    game_elements/cell.h \
    game_elements/cell_grid.h \
    game_elements/commands/cmd_attack.h \
    game_elements/commands/cmd_build.h \
    game_elements/commands/cmd_create_unit.h \
    game_elements/commands/cmd_destroy_object.h \
    game_elements/commands/cmd_move.h \
    game_elements/commands/cmd_use_item.h \
    game_elements/commands/cmd_work.h \
    game_elements/commands/command.h \
    game_elements/commands/commands_queue.h \
    game_elements/commands/concrete_commands.h \
    game_elements/entity.h \
    game_elements/entity_constructor.h \
    game_elements/entity_container.h \
    game_elements/field.h \
    game_elements/field_iterator.h \
    game_elements/interface/cell_interface.h \
    game_elements/interface/entity_interface.h \
    game_elements/landscape/canyon_ls.h \
    game_elements/landscape/landscape.h \
    game_elements/landscape/landscape_library.h \
    game_elements/landscape/plain_ls.h \
    game_elements/landscape/rough_ls.h \
    game_elements/level.h \
    game_elements/master.h \
    game_elements/neutral_objects/concrete_objects.h \
    game_elements/neutral_objects/concrete_objects/barrel.h \
    game_elements/neutral_objects/concrete_objects/healing_poition.h \
    game_elements/neutral_objects/concrete_objects/rock.h \
    game_elements/neutral_objects/concrete_objects/stamina_poition.h \
    game_elements/neutral_objects/concrete_objects/strength_poition.h \
    game_elements/neutral_objects/concrete_objects/tree.h \
    game_elements/neutral_objects/object.h \
    game_elements/neutral_objects/usable.h \
    game_elements/team.h \
    game_elements/units/battle_unit_factory.h \
    game_elements/units/common_unit_factory.h \
    game_elements/units/concrete_units.h \
    game_elements/units/concrete_units/archer.h \
    game_elements/units/concrete_units/atrons.h \
    game_elements/units/concrete_units/berserk.h \
    game_elements/units/concrete_units/knight.h \
    game_elements/units/concrete_units/troll.h \
    game_elements/units/concrete_units/wizard.h \
    game_elements/units/concrete_units/worker.h \
    game_elements/units/magic_unit_factory.h \
    game_elements/units/melee.h \
    game_elements/units/nuker.h \
    game_elements/units/range.h \
    game_elements/units/stats_flyweight.h \
    game_elements/units/unit.h \ \
    game_elements/units/unit_action.h \
    game_elements/units/unit_stats.h \
    game_elements/units/worker_unit_factory.h \
    logger.h \
    printer.h \
    rand_int.h \
    t_game.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
