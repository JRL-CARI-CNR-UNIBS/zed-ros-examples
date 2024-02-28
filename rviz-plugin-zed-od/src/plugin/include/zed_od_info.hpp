/*
 * MIT License
 * 
 * Copyright (c) 2023 Stereolabs
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef ZED_OD_INFO_HPP
#define ZED_OD_INFO_HPP

#include <string>
#include <QObject>

#include <zed_msgs/ObjectsStamped.h>

#include <rviz/ogre_helpers/shape.h>
#include <rviz/ogre_helpers/billboard_line.h>
#include <rviz/ogre_helpers/movable_text.h>
#include <rviz/ogre_helpers/object.h>

namespace Ogre {
    class SceneManager;
    class SceneNode;
}

namespace rviz_plugin_zed_od
{
namespace displays
{


typedef std::shared_ptr<rviz::Shape> shapePtr;
typedef std::shared_ptr<rviz::BillboardLine> linePtr;

class ZedOdInfo : public QObject {
    Q_OBJECT

public:
    explicit ZedOdInfo(zed_msgs::Object &obj,
                       Ogre::SceneManager *scene_manager, Ogre::SceneNode *parent_node=NULL);
    virtual ~ZedOdInfo();

    void updateShowLabel(bool show);
    void updateAlpha(float alpha);
    void updateInfo(zed_msgs::Object& obj);
    void updateShowBBox(bool show);
    void updateShowSkeleton(bool show);
    void updateLinkSize(float newval);
    void updateJointRadius(float newval);
    void updateLabelScale(float newval);

protected:
    void calculateColor();

private:
    std::string mObjName;

    //shapePtr mBBox;
    std::shared_ptr<rviz::MovableText> mLabel;

    std::vector<shapePtr> mBBoxCorners;
    std::vector<linePtr> mBBoxLines;

    std::vector<shapePtr> mSkelJoints;
    std::vector<linePtr> mSkelLinks;

    float mAlpha = 0.75f;
    Ogre::ColourValue mColorBBox;
    Ogre::ColourValue mColorSkel;

    Ogre::SceneManager* mSceneManager=nullptr;
    Ogre::SceneNode* mParentNode=nullptr;
    Ogre::SceneNode* mSceneNode=nullptr;
    Ogre::SceneNode* mSkelSceneNode=nullptr;
    Ogre::SceneNode* mBBoxSceneNode=nullptr;
    Ogre::SceneNode* mPivotSceneNode=nullptr;

    bool mShowLabel=true;
    bool mShowBBox=true;
    bool mShowSkel=true;

    shapePtr mPivot;

    int16_t mLabelId;

    float mLabelScale = 2.5;
    float mJointRadius = 0.1;
    float mLinkSize = 0.05;

    const float mSkelScale = 0.4f;
    const int mSkelColOffset = 50;

    // Unique identifier for each object
    static uint64_t mObjIdx;
};

} // namespace displays
} // namespace rviz_plugin_zed_od

#endif // #ifndef ZED_OD_INFO_HPP
