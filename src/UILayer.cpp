#include "UILayer.h"

#include "Geode/binding/GameManager.hpp"
#include "Geode/utils/cocos.hpp"
#include "PlayLayer.h"

using namespace geode::prelude;

namespace startpos_switcher {

bool SwitchUILayer::init() {
    if (!UILayer::init()) return false;

    auto playLayer = static_cast<SwitchPlayLayer*>(GameManager::get()->m_playLayer);
    if (!playLayer) return true;

    auto director = CCDirector::get();
    auto winSize = director->getWinSize();

    auto fields = m_fields.self();

    auto menu = CCMenu::create();
    menu->setPosition(ccp(winSize.width * 0.5f, director->getScreenBottom() + 17.f));
    menu->setID("menu"_spr);

    auto label = CCLabelBMFont::create("0/0", "bigFont.fnt");
    label->setScale(0.6f);
    label->setID("label");

    fields->m_label = label;

    auto nextSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
    auto prevSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
    nextSpr->setScale(0.6f);
    prevSpr->setScale(0.6f);

    nextSpr->setFlipX(true);

    auto nextBtn = CCMenuItemExt::createSpriteExtra(nextSpr, [this, playLayer](auto sender) {
        playLayer->updateStartpos(playLayer->m_fields->m_currIdx + 1);
    });
    nextBtn->setID("next-btn");

    auto prevBtn = CCMenuItemExt::createSpriteExtra(prevSpr, [this, playLayer](auto sender) {
        playLayer->updateStartpos(playLayer->m_fields->m_currIdx - 1);
    });
    prevBtn->setID("prev-btn");

    menu->addChild(prevBtn);
    menu->addChild(label);
    menu->addChild(nextBtn);

    menu->setLayout(AxisLayout::create()->setAutoScale(false)->setGap(10));
    this->addChild(menu);

    fields->m_menu = menu;

    updateSwitcher();

    return true;
}

void SwitchUILayer::updateSwitcher() {
    auto playLayer = static_cast<SwitchPlayLayer*>(GameManager::get()->m_playLayer);
    auto fields = m_fields.self();

    if (playLayer->m_fields->m_switchers.size() == 0) fields->m_menu->setVisible(false);

    fields->m_label->setString(
        fmt::format("{}/{}", playLayer->m_fields->m_currIdx, playLayer->m_fields->m_switchers.size())
            .c_str()
    );
    fields->m_label->limitLabelWidth(40, 0.6f, 0);

    fields->m_menu->stopActionByTag(799);
    auto action = CCSequence::create(
        CCEaseInOut::create(CCFadeTo::create(0.3f, 255), 2),
        CCDelayTime::create(0.5f),
        CCEaseInOut::create(CCFadeTo::create(0.3f, 50), 2),
        0
    );
    action->setTag(799);
    fields->m_menu->runAction(action);
}

void SwitchUILayer::keyDown(enumKeyCodes key) {
    auto playLayer = static_cast<SwitchPlayLayer*>(GameManager::get()->m_playLayer);

    if (key == KEY_E) playLayer->updateStartpos(playLayer->m_fields->m_currIdx + 1);
    else if (key == KEY_Q) playLayer->updateStartpos(playLayer->m_fields->m_currIdx - 1);

    UILayer::keyDown(key);
}

}
