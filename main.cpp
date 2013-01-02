#include <QtGui/QApplication>
#include <QtGui/qwidget.h>
#include "VoiceChatForm.h"

int main(int argc, char *argv[]) {
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);

	// create and show your widgets here
	VoiceChatForm chatForm;
	chatForm.show();
	return app.exec();
}
