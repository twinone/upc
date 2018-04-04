#ifndef _SHOWHELP_H
#define _SHOWHELP_H

#include "basicplugin.h"

class ModelInfo2 : public QObject, BasicPlugin
 {
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif     
     Q_INTERFACES(BasicPlugin)

 public:
    void preFrame() Q_DECL_OVERRIDE;
    void postFrame() Q_DECL_OVERRIDE;
    void onPluginLoad() Q_DECL_OVERRIDE;
    void onObjectAdd() Q_DECL_OVERRIDE;
    void onSceneClear() Q_DECL_OVERRIDE;
    void keyPressEvent();
    void mouseMoveEvent();
    
    
    // void paintGL() Q_DECL_OVERRIDE;
    
 private:
    GLuint textureID;
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;

 };
 
 #endif
