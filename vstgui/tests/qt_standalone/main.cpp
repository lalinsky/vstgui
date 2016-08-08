#include <QApplication>
#include <QWidget>
#include <QDebug>
#include "vstgui.h"
#include "vstgui_uidescription.h"

using namespace VSTGUI;

int main(int argc, char * argv[]) {
	QApplication app (argc, argv);

	//SharedPointer<UIDescription> uiDesc;
	//uiDesc = owned (new UIDescription (CResourceDescription ("qt_test.uidesc")));

	CBitmap* background = new CBitmap ("./tutorial/resource/KnobBackground.png");
	CBitmap* handle = new CBitmap ("./tutorial/resource/KnobHandle.png");
	CRect r (0, 0, background->getWidth (), background->getHeight ());
	CKnob* knob = new CKnob (r, 0, 0, background, handle, CPoint (0, 0));
	background->forget ();
	handle->forget ();

	CRect frameSize (0, 0, 300, 300);
	CFrame* frame = new CFrame (frameSize, NULL);
	frame->addView (knob);

	QWidget main;
	frame->open (&main, kQWidget);
	main.show ();

	qDebug() << "frame is " << frame;
	qDebug() << "knob is " << knob;
	frame->dumpHierarchy ();

	return app.exec ();
}
