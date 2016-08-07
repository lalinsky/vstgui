#include <QApplication>
#include <QWidget>
#include "vstgui.h"
#include "vstgui_uidescription.h"

using namespace VSTGUI;

int main(int argc, char * argv[]) {
    QApplication app (argc, argv);

	//SharedPointer<UIDescription> uiDesc;
    //uiDesc = owned (new UIDescription (CResourceDescription ("qt_test.uidesc")));

    CRect frameSize (0, 0, 300, 300);
    CFrame* frame = new CFrame (frameSize, NULL);
    CBitmap* background = new CBitmap ("./tutorial/resource/KnobBackground.png");
    CBitmap* handle = new CBitmap ("./tutorial/resource/KnobHandle.png");
    CRect r (0, 0, background->getWidth (), background->getHeight ());
    CKnob* knob = new CKnob (r, 0, 0, background, handle, CPoint (0, 0));
    background->forget ();
    handle->forget ();
    frame->addView (knob);
    
    //CRect frameSize (0, 0, 300, 300);
    //CFrame* frame = new CFrame (frameSize, NULL);

    QWidget main;
    frame->open (&main, kQWidget);
    main.show ();

    return app.exec ();
}
