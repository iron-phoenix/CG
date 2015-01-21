#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShader>
#include <QFileInfo>
#include <QMouseEvent>
#include <QWheelEvent>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    void loadShader(QGLShaderProgram* program, QString name, QGLShader::ShaderTypeBit shader_type) {
        QFileInfo shader_file(name);
        if(shader_file.exists()){
            if(!program->addShaderFromSourceFile(shader_type, name)){
                qDebug() << "Can't load shader " + name;
                close();
            }
        } else{
            qDebug() << "File not found " + name;
            close();
        }
    }

    QGLShaderProgram* shader;

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    float xoffset;
    float yoffset;
    float fscale;

    QPoint oldMousePos;
};

#endif // GLWIDGET_H
