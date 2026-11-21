#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "UI.hpp"

using namespace geode::prelude;

class $modify(DecoEditorUI, EditorUI) {
    struct Fields {
        CCMenu* menu = nullptr;
    };

    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel)) return false;

        auto win = CCDirector::get()->getWinSize();
        auto menu = CCMenu::create();
        menu->setID("deco-menu"_spr);
        menu->setPosition({ 0, 0 });
        menu->setContentSize(win);

        auto spr = ButtonSprite::create("Deco", "bigFont.fnt", "GJ_button_04.png", 0.8f);
        spr->setScale(0.55f);
        auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(DecoEditorUI::onAutoDecorate));
        btn->setID("deco-button"_spr);
        float ox = (float)Mod::get()->getSettingValue<double>("button-x");
        float oy = (float)Mod::get()->getSettingValue<double>("button-y");
        btn->setPosition({ win.width - 120.f + ox, win.height - 22.f + oy });
        menu->addChild(btn);
        this->addChild(menu, 50);
        m_fields->menu = menu;
        return true;
    }

    void showUI(bool show) {
        EditorUI::showUI(show);
        if (m_fields->menu) m_fields->menu->setVisible(show);
        if (auto p = PreviewPanel::current(this)) p->setVisible(show);
    }

    void onAutoDecorate(CCObject*) {
        openDecorator(this);
    }
};
