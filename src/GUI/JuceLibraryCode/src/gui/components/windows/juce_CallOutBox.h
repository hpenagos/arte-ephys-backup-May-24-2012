/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-10 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_CALLOUTBOX_JUCEHEADER__
#define __JUCE_CALLOUTBOX_JUCEHEADER__

#include "../juce_Component.h"


//==============================================================================
/**
    A box with a small arrow that can be used as a temporary pop-up window to show
    extra controls when a button or other component is clicked.

    Using one of these is similar to having a popup menu attached to a button or
    other component - but it looks fancier, and has an arrow that can indicate the
    object that it applies to.

    Normally, you'd create one of these on the stack and run it modally, e.g.

    @code
    void mouseUp (const MouseEvent& e)
    {
        MyContentComponent content;
        content.setSize (300, 300);

        CallOutBox callOut (content, *this, 0);
        callOut.runModalLoop();
    }
    @endcode

    The call-out will resize and position itself when the content changes size.
*/
class JUCE_API  CallOutBox    : public Component
{
public:
    //==============================================================================
    /** Creates a CallOutBox.

        @param contentComponent     the component to display inside the call-out. This should
                                    already have a size set (although the call-out will also
                                    update itself when the component's size is changed later).
                                    Obviously this component must not be deleted until the
                                    call-out box has been deleted.
        @param componentToPointTo   the component that the call-out's arrow should point towards
        @param parentComponent      if non-zero, this is the component to add the call-out to. If
                                    this is zero, the call-out will be added to the desktop.
    */
    CallOutBox (Component& contentComponent,
                Component& componentToPointTo,
                Component* parentComponent);

    /** Destructor. */
    ~CallOutBox();

    //==============================================================================
    /** Changes the length of the arrow. */
    void setArrowSize (float newSize);

    /** Updates the position and size of the box.

        You shouldn't normally need to call this, unless you need more precise control over the
        layout.

        @param newAreaToPointTo     the rectangle to make the box's arrow point to
        @param newAreaToFitIn       the area within which the box's position should be constrained
    */
    void updatePosition (const Rectangle<int>& newAreaToPointTo,
                         const Rectangle<int>& newAreaToFitIn);

    //==============================================================================
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    void resized();
    /** @internal */
    void moved();
    /** @internal */
    void childBoundsChanged (Component*);
    /** @internal */
    bool hitTest (int x, int y);
    /** @internal */
    void inputAttemptWhenModal();
    /** @internal */
    bool keyPressed (const KeyPress& key);
    /** @internal */
    void handleCommandMessage (int commandId);

private:
    //==============================================================================
    int borderSpace;
    float arrowSize;
    Component& content;
    Path outline;
    Point<float> targetPoint;
    Rectangle<int> availableArea, targetArea;
    Image background;

    void refreshPath();
    void drawCallOutBoxBackground (Graphics& g, const Path& outline, int width, int height);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CallOutBox);
};


#endif   // __JUCE_CALLOUTBOX_JUCEHEADER__
