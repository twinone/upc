#include "ShowDegree.h"
#include "glwidget.h"
#include <QPainter>

#include <sstream>
#include <string>

void ShowDegree::onPluginLoad() {
    glwidget()->makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("plugins/ShowDegree/ShowDegree.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;


    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("plugins/ShowDegree/ShowDegree.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    
    
    cout << "Link log:" << program->log().toStdString() << endl;
  
    std::cout << "Loaded ShowDegree plugin!" << std::endl;
}

void drawRect(GLWidget &g)
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;
        
        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        float z = -0.99999;
        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, z, 
                            1, -1, z, 
                           -1,  1, z, 
                            1,  1, z};

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}

void ShowDegree::postFrame() 
{
    
    
    // WRITE TEXT STRING
  GLWidget &g=*glwidget();
  g.makeCurrent();
  
  /** Get the data */
   Scene *s = scene();
        int uniqueV = 0;
        int repV = 0;
        for (uint i = 0; i < s->objects().size(); i++) {
            auto o = s->objects()[i];
            for (uint j = 0; j < o.faces().size(); j++) {
                repV += o.faces()[j].numVertices();
            }
            uniqueV += o.vertices().size();
        }
        
        stringstream ss;
        ss << "..unique:" << uniqueV;
        ss << "..rep:" << repV;
        ss << "..degree=:" << ((float)repV/uniqueV);
        
        
        string out;
        ss>>out;
        /** write on screen */
  
  
    const int SIZE = 1024;
    // 1. Create image with text
    QImage image(SIZE,SIZE,QImage::Format_RGB32);
    image.fill(Qt::white);    
    QPainter painter;
    painter.begin(&image);
    QFont font;
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen(QColor(50,50,50));
    int x = 15;
    int y = 50;
    painter.drawText(x, y, QString(out.c_str()));    
    painter.end();

    // 2. Create texture
    const int textureUnit = 5;
    g.glActiveTexture(GL_TEXTURE0+textureUnit);
    QImage im0 = image.mirrored(false, true).convertToFormat(QImage::Format_RGBA8888, Qt::ColorOnly);
	g.glGenTextures( 1, &textureID);
	g.glBindTexture(GL_TEXTURE_2D, textureID);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	
    // Pass 2. Draw quad using texture
    program->bind();
    program->setUniformValue("colorMap", textureUnit);
    program->setUniformValue("WIDTH", float(glwidget()->width()));
    program->setUniformValue("HEIGHT", float(glwidget()->height()));    
 
    // quad covering viewport 
    drawRect(g);
    program->release();
    g.glBindTexture(GL_TEXTURE_2D, 0);

    
    g.glDeleteTextures(1, &textureID);


}



void ShowDegree::preFrame() {}
void ShowDegree::onObjectAdd() {}
void ShowDegree::onSceneClear() {}
void ShowDegree::keyPressEvent() {}
void ShowDegree::mouseMoveEvent() {}



#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ShowDegree, ShowDegree)   // plugin name, plugin class
#endif
