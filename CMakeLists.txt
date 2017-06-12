#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/
cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 3.1)

set(APP_NAME KingdomRush)
project (${APP_NAME})

set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosBuildHelpers)


# Some macro definitions
if(WINDOWS)
  if(BUILD_SHARED_LIBS)
    ADD_DEFINITIONS (-D_USRDLL -D_EXPORT_DLL_ -D_USEGUIDLL -D_USREXDLL -D_USRSTUDIODLL)
  else()
    ADD_DEFINITIONS (-DCC_STATIC)
  endif()

  ADD_DEFINITIONS (-DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32 -D_WIN32)
  set(PLATFORM_FOLDER win32)
elseif(MACOSX OR APPLE)
  ADD_DEFINITIONS (-DCC_TARGET_OS_MAC)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER mac)
elseif(LINUX)
  ADD_DEFINITIONS(-DLINUX)
  set(PLATFORM_FOLDER linux)
elseif(ANDROID)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER android)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()


# Compiler options
if(MSVC)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt /NODEFAULTLIB:libcmt")
  else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt")
  endif()
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
                  -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
                  -wd4514 -wd4056 -wd4996 -wd4099)
else()
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    ADD_DEFINITIONS(-DCOCOS2D_DEBUG=1)
  endif()
  set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
  if(CLANG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif()
endif(MSVC)

set(PLATFORM_SPECIFIC_SRC)
set(PLATFORM_SPECIFIC_HEADERS)

if(MACOSX OR APPLE)
    set(PLATFORM_SPECIFIC_SRC
      proj.ios_mac/mac/main.cpp
    )
elseif(LINUX)
    set(PLATFORM_SPECIFIC_SRC
      proj.linux/main.cpp
    )
elseif ( WIN32 )
    set(PLATFORM_SPECIFIC_SRC
      proj.win32/main.cpp
    )
    set(PLATFORM_SPECIFIC_HEADERS
      proj.win32/main.h
      proj.win32/resource.h
    )
elseif(ANDROID)
    set(PLATFORM_SPECIFIC_SRC
      proj.android-studio/app/jni/hellocpp/main.cpp
    )
endif()

include_directories(
  /usr/local/include/GLFW
  /usr/include/GLFW
  ${COCOS2D_ROOT}
  ${COCOS2D_ROOT}/cocos
  ${COCOS2D_ROOT}/external
  ${COCOS2D_ROOT}/cocos/platform
  ${COCOS2D_ROOT}/cocos/audio/include/
  Classes
  Classes/Bullet
  Classes/Data
  Classes/Layer
  Classes/Layer/Menu
  Classes/Map
  Classes/Monster
  Classes/Monster/Boss
  Classes/Monster/Desert
  Classes/Monster/Jungle
  Classes/Monster/Underground
  Classes/Road
  Classes/Scene
  Classes/Scene/Introduction
  Classes/Scene/Story
  Classes/Scene/UpdateTowerScene
  Classes/Soldier
  Classes/Sprite
  Classes/Sprite/Circle
  Classes/Sprite/TowerIcon
  Classes/Tower
)
if ( WIN32 )
  include_directories(
  ${COCOS2D_ROOT}/external/glfw3/include/win32
  ${COCOS2D_ROOT}/external/win32-specific/gles/include/OGLES
)
endif( WIN32 )

set(GAME_SRC
  Classes/AppDelegate.cpp
  Classes/Bullet/ArchMageBolt.cpp
  Classes/Bullet/Arrow.cpp
  Classes/Bullet/Bomb.cpp
  Classes/Bullet/Bullet.cpp
  Classes/Bullet/Drill.cpp
  Classes/Bullet/Dynamite.cpp
  Classes/Bullet/EarthquakeSmoke.cpp
  Classes/Bullet/FireBall.cpp
  Classes/Bullet/Freeze.cpp
  Classes/Bullet/Lava.cpp
  Classes/Bullet/MageBolt.cpp
  Classes/Bullet/MechaBomb.cpp
  Classes/Bullet/Missile.cpp
  Classes/Bullet/NecrBolt.cpp
  Classes/Bullet/RedTotem.cpp
  Classes/Bullet/Shit.cpp
  Classes/Bullet/TotemAxe.cpp
  Classes/Bullet/Twister.cpp
  Classes/Bullet/VioletTotem.cpp
  Classes/Data/GameManager.cpp
  Classes/Data/MyAnimation.cpp
  Classes/Data/SoundManager.cpp
  Classes/Layer/Failure.cpp
  Classes/Layer/GameOption.cpp
  Classes/Layer/GameViewMenu.cpp
  Classes/Layer/Menu/SimplePanleLayer.cpp
  Classes/Layer/Menu/SimplePanleLayerWithFlag.cpp
  Classes/Layer/Menu/TowerPanleLayer.cpp
  Classes/Layer/Menu/UpdatePanleLayer2.cpp
  Classes/Layer/Menu/UpdatePanleLayer2WithFlag.cpp
  Classes/Layer/Menu/UpdatePanleLayer.cpp
  Classes/Layer/Menu/UpdatePanleLayerWithFlag.cpp
  Classes/Layer/PlayerStateMenu.cpp
  Classes/Layer/TouchLayer.cpp
  Classes/Layer/Victory.cpp
  Classes/Map/BaseMap.cpp
  Classes/Map/Level0.cpp
  Classes/Map/Level10.cpp
  Classes/Map/Level11.cpp
  Classes/Map/Level12.cpp
  Classes/Map/Level13.cpp
  Classes/Map/Level1.cpp
  Classes/Map/Level2.cpp
  Classes/Map/Level3.cpp
  Classes/Map/Level4.cpp
  Classes/Map/Level5.cpp
  Classes/Map/Level6.cpp
  Classes/Map/Level7.cpp
  Classes/Map/Level8.cpp
  Classes/Map/Level9.cpp
  Classes/Monster/BaseMonster.cpp
  Classes/Monster/Boss/Boss_Canibal.cpp
  Classes/Monster/Boss/Boss_Efreeti.cpp
  Classes/Monster/Boss/CanibalOffspring.cpp
  Classes/Monster/Boss/Efreeti.cpp
  Classes/Monster/Desert/Executioner.cpp
  Classes/Monster/Desert/Fallen.cpp
  Classes/Monster/Desert/Immortal.cpp
  Classes/Monster/Desert/Munra.cpp
  Classes/Monster/Desert/Raider.cpp
  Classes/Monster/Desert/Scorpion.cpp
  Classes/Monster/Desert/Thug.cpp
  Classes/Monster/Desert/Tremor.cpp
  Classes/Monster/Desert/WaspHornet.cpp
  Classes/Monster/Desert/WaspQueen.cpp
  Classes/Monster/Desert/Wolf.cpp
  Classes/Monster/GroupMonster.cpp
  Classes/Monster/Jungle/Canibal.cpp
  Classes/Monster/Jungle/Gorilla.cpp
  Classes/Monster/Jungle/Hunter.cpp
  Classes/Monster/Jungle/Priest.cpp
  Classes/Monster/Jungle/Shaman.cpp
  Classes/Monster/Jungle/Shield.cpp
  Classes/Monster/Jungle/WingRider.cpp
  Classes/Monster/Underground/Blazefang.cpp
  Classes/Monster/Underground/Broodguard.cpp
  Classes/Monster/Underground/Elite.cpp
  Classes/Monster/Underground/Myrmidon.cpp
  Classes/Monster/Underground/Nightscale.cpp
  Classes/Monster/Underground/Quetzal.cpp
  Classes/Road/Road.cpp
  Classes/Scene/ChooseDifficulty.cpp
  Classes/Scene/GameScene.cpp
  Classes/Scene/GameView.cpp
  Classes/Scene/Introduction/EncyclopaediaTips.cpp
  Classes/Scene/Introduction/EncyclopediaScene.cpp
  Classes/Scene/Introduction/EnemyDesc.cpp
  Classes/Scene/Introduction/EnemyScene.cpp
  Classes/Scene/Introduction/Information.cpp
  Classes/Scene/Introduction/TowerDesc.cpp
  Classes/Scene/Introduction/TowerScene.cpp
  Classes/Scene/LoadingScene.cpp
  Classes/Scene/ShopScene.cpp
  Classes/Scene/Story/BeginAnimation.cpp
  Classes/Scene/TransitionGame.cpp
  Classes/Scene/UpdateTowerScene/Icons.cpp
  Classes/Scene/UpdateTowerScene/Upgrades.cpp
  Classes/Scene/WelcomeScene.cpp
  Classes/Soldier/Assassin.cpp
  Classes/Soldier/BarrackSoldier.cpp
  Classes/Soldier/BaseSoldier.cpp
  Classes/Soldier/DeathKnight.cpp
  Classes/Soldier/Mecha.cpp
  Classes/Soldier/ReinforceSoldier1.cpp
  Classes/Soldier/ReinforceSoldier2.cpp
  Classes/Soldier/Skeleton.cpp
  Classes/Soldier/Templar.cpp
  Classes/Sprite/Circle/Circle.cpp
  Classes/Sprite/Circle/RallyCircle.cpp
  Classes/Sprite/MagicIcon.cpp
  Classes/Sprite/MapFlag.cpp
  Classes/Sprite/MonsterInfoLayer.cpp
  Classes/Sprite/RespirationSprite.cpp
  Classes/Sprite/ShopIcon.cpp
  Classes/Sprite/SlotMenu.cpp
  Classes/Sprite/Smoke.cpp
  Classes/Sprite/TowerIcon/BaseBuildIcon.cpp
  Classes/Sprite/TowerIcon/SellIcon.cpp
  Classes/Sprite/TowerInfoLayer.cpp
  Classes/Sprite/UpdateIcon.cpp
  Classes/Sprite/WaveFlag.cpp
  Classes/Tower/ArchMageTower.cpp
  Classes/Tower/BaseArrowTower.cpp
  Classes/Tower/BaseArtilleryTower.cpp
  Classes/Tower/BaseBarracksTower.cpp
  Classes/Tower/BaseMageTower.cpp
  Classes/Tower/BaseTower.cpp
  Classes/Tower/CossbowHunterTower.cpp
  Classes/Tower/EarthquakeTower.cpp
  Classes/Tower/MechsTower.cpp
  Classes/Tower/NecromancerTower.cpp
  Classes/Tower/SimpleArrowTowerlvl1.cpp
  Classes/Tower/SimpleArrowTowerlvl2.cpp
  Classes/Tower/SimpleArrowTowerlvl3.cpp
  Classes/Tower/SimpleArtilleryTowerlvl1.cpp
  Classes/Tower/SimpleArtilleryTowerlvl2.cpp
  Classes/Tower/SimpleArtilleryTowerlvl3.cpp
  Classes/Tower/SimpleMageTowerlvl1.cpp
  Classes/Tower/SimpleMageTowerlvl2.cpp
  Classes/Tower/SimpleMageTowerlvl3.cpp
  Classes/Tower/KRTerrain.cpp
  Classes/Tower/TotemTower.cpp
  ${PLATFORM_SPECIFIC_SRC}
)

set(GAME_HEADERS
  Classes/AppDelegate.h
  Classes/Bullet/ArchMageBolt.h
  Classes/Bullet/Arrow.h
  Classes/Bullet/Bomb.h
  Classes/Bullet/Bullet.h
  Classes/Bullet/Drill.h
  Classes/Bullet/Dynamite.h
  Classes/Bullet/EarthquakeSmoke.h
  Classes/Bullet/FireBall.h
  Classes/Bullet/Freeze.h
  Classes/Bullet/Lava.h
  Classes/Bullet/MageBolt.h
  Classes/Bullet/MechaBomb.h
  Classes/Bullet/Missile.h
  Classes/Bullet/NecrBolt.h
  Classes/Bullet/RedTotem.h
  Classes/Bullet/Shit.h
  Classes/Bullet/Smoke.h
  Classes/Bullet/TotemAxe.h
  Classes/Bullet/Twister.h
  Classes/Bullet/VioletTotem.h
  Classes/Data/GameManager.h
  Classes/Data/MyAnimation.h
  Classes/Data/SoundManager.h
  Classes/Layer/Failure.h
  Classes/Layer/GameOption.h
  Classes/Layer/GameViewMenu.h
  Classes/Layer/Menu/SimplePanleLayer.h
  Classes/Layer/Menu/SimplePanleLayerWithFlag.h
  Classes/Layer/Menu/TowerPanleLayer.h
  Classes/Layer/Menu/UpdatePanleLayer2.h
  Classes/Layer/Menu/UpdatePanleLayer2WithFlag.h
  Classes/Layer/Menu/UpdatePanleLayer.h
  Classes/Layer/Menu/UpdatePanleLayerWithFlag.h
  Classes/Layer/PlayerStateMenu.h
  Classes/Layer/TouchLayer.h
  Classes/Layer/Victory.h
  Classes/Map/BaseMap.h
  Classes/Map/Level0.h
  Classes/Map/Level10.h
  Classes/Map/Level11.h
  Classes/Map/Level12.h
  Classes/Map/Level13.h
  Classes/Map/Level1.h
  Classes/Map/Level2.h
  Classes/Map/Level3.h
  Classes/Map/Level4.h
  Classes/Map/Level5.h
  Classes/Map/Level6.h
  Classes/Map/Level7.h
  Classes/Map/Level8.h
  Classes/Map/Level9.h
  Classes/Monster/BaseMonster.h
  Classes/Monster/Boss/Boss_Canibal.h
  Classes/Monster/Boss/Boss_Efreeti.h
  Classes/Monster/Boss/CanibalOffspring.h
  Classes/Monster/Boss/Efreeti.h
  Classes/Monster/Desert/Executioner.h
  Classes/Monster/Desert/Fallen.h
  Classes/Monster/Desert/Immortal.h
  Classes/Monster/Desert/Munra.h
  Classes/Monster/Desert/Raider.h
  Classes/Monster/Desert/Scorpion.h
  Classes/Monster/Desert/Thug.h
  Classes/Monster/Desert/Tremor.h
  Classes/Monster/Desert/WaspHornet.h
  Classes/Monster/Desert/WaspQueen.h
  Classes/Monster/Desert/Wolf.h
  Classes/Monster/GroupMonster.h
  Classes/Monster/Jungle/Canibal.h
  Classes/Monster/Jungle/Gorilla.h
  Classes/Monster/Jungle/Hunter.h
  Classes/Monster/Jungle/Priest.h
  Classes/Monster/Jungle/Shaman.h
  Classes/Monster/Jungle/Shield.h
  Classes/Monster/Jungle/WingRider.h
  Classes/Monster/Underground/Blazefang.h
  Classes/Monster/Underground/Broodguard.h
  Classes/Monster/Underground/Elite.h
  Classes/Monster/Underground/Myrmidon.h
  Classes/Monster/Underground/Nightscale.h
  Classes/Monster/Underground/Quetzal.h
  Classes/Road/Road.h
  Classes/Scene/ChooseDifficulty.h
  Classes/Scene/GameScene.h
  Classes/Scene/GameView.h
  Classes/Scene/Introduction/EncyclopaediaTips.h
  Classes/Scene/Introduction/EncyclopediaScene.h
  Classes/Scene/Introduction/EnemyDesc.h
  Classes/Scene/Introduction/EnemyScene.h
  Classes/Scene/Introduction/Information.h
  Classes/Scene/Introduction/TowerDesc.h
  Classes/Scene/Introduction/TowerScene.h
  Classes/Scene/LoadingScene.h
  Classes/Scene/ShopScene.h
  Classes/Scene/Story/BeginAnimation.h
  Classes/Scene/TransitionGame.h
  Classes/Scene/UpdateTowerScene/Icons.h
  Classes/Scene/UpdateTowerScene/Upgrades.h
  Classes/Scene/WelcomeScene.h
  Classes/Soldier/Assassin.h
  Classes/Soldier/BarrackSoldier.h
  Classes/Soldier/BaseSoldier.h
  Classes/Soldier/DeathKnight.h
  Classes/Soldier/Mecha.h
  Classes/Soldier/ReinforceSoldier1.h
  Classes/Soldier/ReinforceSoldier2.h
  Classes/Soldier/Skeleton.h
  Classes/Soldier/Templar.h
  Classes/Sprite/Circle/Circle.h
  Classes/Sprite/Circle/RallyCircle.h
  Classes/Sprite/MagicIcon.h
  Classes/Sprite/MapFlag.h
  Classes/Sprite/MonsterInfoLayer.h
  Classes/Sprite/RespirationSprite.h
  Classes/Sprite/ShopIcon.h
  Classes/Sprite/SlotMenu.h
  Classes/Sprite/TowerIcon/BaseBuildIcon.h
  Classes/Sprite/TowerIcon/SellIcon.h
  Classes/Sprite/TowerInfoLayer.h
  Classes/Sprite/UpdateIcon.h
  Classes/Sprite/WaveFlag.h
  Classes/Tower/ArchMageTower.h
  Classes/Tower/BaseArrowTower.h
  Classes/Tower/BaseArtilleryTower.h
  Classes/Tower/BaseBarracksTower.h
  Classes/Tower/BaseMageTower.h
  Classes/Tower/BaseTower.h
  Classes/Tower/CossbowHunterTower.h
  Classes/Tower/EarthquakeTower.h
  Classes/Tower/MechsTower.h
  Classes/Tower/NecromancerTower.h
  Classes/Tower/SimpleArrowTowerlvl1.h
  Classes/Tower/SimpleArrowTowerlvl2.h
  Classes/Tower/SimpleArrowTowerlvl3.h
  Classes/Tower/SimpleArtilleryTowerlvl1.h
  Classes/Tower/SimpleArtilleryTowerlvl2.h
  Classes/Tower/SimpleArtilleryTowerlvl3.h
  Classes/Tower/SimpleMageTowerlvl1.h
  Classes/Tower/SimpleMageTowerlvl2.h
  Classes/Tower/SimpleMageTowerlvl3.h
  Classes/Tower/KRTerrain.h
  Classes/Tower/TotemTower.h
  ${PLATFORM_SPECIFIC_HEADERS}
)


# Configure libcocos2d
set(BUILD_CPP_EMPTY_TEST OFF CACHE BOOL "turn off build cpp-empty-test")
set(BUILD_CPP_TESTS OFF CACHE BOOL "turn off build cpp-tests")
set(BUILD_LUA_LIBS OFF CACHE BOOL "turn off build lua related targets")
set(BUILD_JS_LIBS OFF CACHE BOOL "turn off build js related targets")
add_subdirectory(${COCOS2D_ROOT})


# MyGame
if( ANDROID )
    add_library(${APP_NAME} SHARED ${GAME_SRC} ${GAME_HEADERS})
    IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF()
else()
    add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS})
endif()

target_link_libraries(${APP_NAME} cocos2d)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

if ( WIN32 )
  #also copying dlls to binary directory for the executable to run
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
	COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt/zlib1.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
	)
elseif( ANDROID )

else()
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    )

endif()
