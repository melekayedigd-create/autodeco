#pragma once
#include <Geode/Geode.hpp>
#include "core/Deco.hpp"

// Everything that talks to Geometry Dash's editor lives here.
namespace bridge {

struct Selection {
    deco::Grid grid;
    std::vector<GameObject*> decoObjects; // non-solid objects in the selection (used by "Save as template")
    int solids = 0;
    int skipped = 0;                      // triggers, portals, orbs... (never touched)
};

Selection readSelection(LevelEditorLayer* lel, cocos2d::CCArray* selected);
void addNearbyHazards(LevelEditorLayer* lel, deco::Grid& grid);

// colour channels: reuse a channel that already has the exact colour, otherwise take a free one
std::vector<int> channelsFor(LevelEditorLayer* lel, deco::Template const& t);

// a group ID that no object uses yet
int freeGroup(LevelEditorLayer* lel);

struct Placed {
    geode::Ref<cocos2d::CCArray> objects;
    int count = 0;
    int removedUnsafe = 0;
};

// creates the objects in the editor (not added to undo yet)
Placed place(LevelEditorLayer* lel, std::vector<deco::Obj> const& objs, std::vector<int> const& channels,
             bool animate, deco::Grid const& grid);
void removeAll(LevelEditorLayer* lel, cocos2d::CCArray* objects);
void commitUndo(LevelEditorLayer* lel, cocos2d::CCArray* objects);

// "Save as template"
bool learnFromSelection(LevelEditorLayer* lel, Selection const& sel, std::string const& name, deco::Template& out);

std::string levelKey(LevelEditorLayer* lel);

} // namespace bridge
