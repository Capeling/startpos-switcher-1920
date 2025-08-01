#ifndef __PLAYLAYER_H__
#define __PLAYLAYER_H__

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

namespace startpos_switcher {

struct SwitchPlayLayer : geode::Modify<SwitchPlayLayer, PlayLayer> {
    struct Fields {
        std::vector<StartPosObject*> m_switchers{};
        int m_currIdx = 0;
    };

    void addToSection(GameObject* obj);
    void createObjectsFromSetup(gd::string str);
    void updateStartpos(int idx);

    void setPosObject(StartPosObject* obj);
};

} // namespace startpos_switcher

#endif /* __PLAYLAYER_H__ */
