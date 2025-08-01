#include "PlayLayer.h"

#include "UILayer.h"

namespace startpos_switcher {

void SwitchPlayLayer::addToSection(GameObject* obj) {
    if (obj->m_objectID == 31) m_fields->m_switchers.push_back(static_cast<StartPosObject*>(obj));
    PlayLayer::addToSection(obj);
}

void SwitchPlayLayer::createObjectsFromSetup(gd::string str) {
    PlayLayer::createObjectsFromSetup(str);

    auto fields = m_fields.self();
    std::sort(fields->m_switchers.begin(), fields->m_switchers.end(), [](auto* a, auto* b) {
        return a->getPositionX() < b->getPositionX();
    });

    if (this->m_startPosObject) {
        auto currentIdx =
            find(fields->m_switchers.begin(), fields->m_switchers.end(), this->m_startPosObject) -
            fields->m_switchers.begin();
        fields->m_currIdx = currentIdx + 1;
    }
}

void SwitchPlayLayer::updateStartpos(int idx) {
    auto fields = m_fields.self();

    if (fields->m_switchers.size() == 0) return;

    if (idx < 0) idx = fields->m_switchers.size();
    if (idx > m_fields->m_switchers.size()) idx = 0;

    m_testMode = idx != 0;

    fields->m_currIdx = idx;

    StartPosObject* obj = idx > 0 ? fields->m_switchers[idx - 1] : nullptr;

    setPosObject(obj);
    if (obj) m_startPos = obj->getOrientedBox()->m_center;
    else m_startPos = ccp(0, 105);

    resetLevel();

    static_cast<SwitchUILayer*>(m_uiLayer)->updateSwitcher();
}

void SwitchPlayLayer::setPosObject(StartPosObject* obj) {
    if (obj == m_startPosObject) return;

    if (obj) obj->retain();

    if (m_startPosObject) m_startPosObject->release();

    m_startPosObject = obj;
}

}
