#ifndef __UILAYER_H__
#define __UILAYER_H__

#include <Geode/Geode.hpp>
#include <Geode/modify/UILayer.hpp>

namespace startpos_switcher {

struct SwitchUILayer : geode::Modify<SwitchUILayer, UILayer> {
    struct Fields {
        cocos2d::CCMenu* m_menu = nullptr;
        cocos2d::CCLabelBMFont* m_label = nullptr;
    };

    bool init();
    void updateSwitcher();

    void keyDown(cocos2d::enumKeyCodes key);
};

}

#endif /* __UILAYER_H__ */
