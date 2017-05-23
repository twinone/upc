#include "AnimateVertices.h"
#include "glwidget.h"
#include <QPainter>

void AnimateVertices::onPluginLoad() {
  glwidget()->makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("plugins/AnimateVertices/AnimateVertices.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;


    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("plugins/AnimateVertices/AnimateVertices.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    
    
    cout << "Link log:" << program->log().toStdString() << endl;
    elapsedTimer.start();
    // keep repainting
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), glwidget(), SLOT(updateGL()));
    timer->start();
    
    std::cout << "Loaded AnimateVertices plugin!" << std::endl;
    
    
}

void AnimateVertices::preFrame() {
      glwidget()->makeCurrent();

    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    QMatrix3x3 NM=camera()->viewMatrix().normalMatrix();

    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", NM);
    program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0f));

    
    
}
void AnimateVertices::postFrame() {  
    glwidget()->makeCurrent();

    program->release();
}
void AnimateVertices::onObjectAdd() {}
void AnimateVertices::onSceneClear() {}
void AnimateVertices::keyPressEvent() {}
void AnimateVertices::mouseMoveEvent() {}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(AnimateVertices, AnimateVertices)   // plugin name, plugin class
#endif
