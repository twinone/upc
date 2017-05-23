#include "Template.h"
#include "glwidget.h"
#include <QPainter>

void Template::onPluginLoad() {

}


void Template::preFrame() {}
void Template::postFrame() {}
void Template::onObjectAdd() {}
void Template::onSceneClear() {}
void Template::keyPressEvent() {}
void Template::mouseMoveEvent() {}



#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(Template, Template)   // plugin name, plugin class
#endif
