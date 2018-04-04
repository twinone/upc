#include "Template.h"
#include "glwidget.h"
#include <QPainter>

void Template::onPluginLoad() {
    glwidget()->makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("plugins/Template/Template.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;


    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("plugins/Template/Template.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();


    cout << "Link log:" << program->log().toStdString() << endl;
    std::cout << "Loaded Template plugin!" << std::endl;
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
