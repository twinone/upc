#include "ModelInfo.h"
#include <cstdlib>

// Documentation: http://www.cs.upc.edu/~virtual/Gdocs/interfaces/html/class_basic_plugin.html

void ModelInfo::onPluginLoad()
{
    // Load & compile VS 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(QString(getenv ("VIEWER"))+"/plugins/ModelInfo/ModelInfo.vert");
    qDebug() << vs->log() << endl;

    // Load & compile FS 
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(QString(getenv ("VIEWER"))+"/plugins/ModelInfo/ModelInfo.frag");
    qDebug() << fs->log() << endl;

    // Link program
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    qDebug() << program->log() << endl;

    // Timers
    connect(&timer, SIGNAL(timeout()), glwidget(), SLOT(updateGL()));
    timer.start();
    elapsedTimer.start();
}


void ModelInfo::onObjectAdd()
{
    unsigned int numObjects = scene()->objects().size();
    qDebug() << "Added new object " << endl;
    qDebug() << " Current scene has " << numObjects << " objects" << endl;
    unsigned int numFaces = scene()->objects()[numObjects-1].faces().size();
    unsigned int numVertices = scene()->objects()[numObjects-1].vertices().size();
    qDebug() << " Last object has " << numFaces << " faces and " << numVertices << " vertices" << endl;
}

void ModelInfo::preFrame()
{
}

void ModelInfo::postFrame()
{
    glColor3f(0.0, 0.0, 0.0);
	int x = 5;
	int y = 15;
	glwidget()->renderText(x,y, QString("[ModelInfo plugin] "));
    
}

bool ModelInfo::drawScene()
{
    // See example DrawImmediate and DrawVBO examples
    // If you draw the scene here, you should return true
    return false;
}
	
void ModelInfo::keyPressEvent (QKeyEvent *e)
{
    // if (e->key() == Qt::Key_C) ...
    qDebug() << "User pressed key " << e->key() << endl; 
    glwidget()->updateGL();
}

void ModelInfo::keyReleaseEvent (QKeyEvent *)
{}

void ModelInfo::mouseMoveEvent (QMouseEvent *) 
{}

void ModelInfo::mousePressEvent (QMouseEvent *e)
{   
    qDebug() << "Mouse (x,y) = " << e->x() << ", " << e->y() << endl;
}

void ModelInfo::mouseReleaseEvent (QMouseEvent *)
{}

void ModelInfo::wheelEvent (QWheelEvent *)
{}


bool ModelInfo::paintGL()
{
    // clear buffers
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // setup matrices
    camera()->setOpenGLModelviewMatrix();
    camera()->setOpenGLProjectionMatrix();
    // draw axes
    glwidget()->drawAxes();
    // draw scene with shaders
    program->bind();
    program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.));
    drawPlugin()->drawScene();
    program->release();

    return true;
}

Q_EXPORT_PLUGIN2(ModelInfop, ModelInfo)   // plugin name, plugin class

