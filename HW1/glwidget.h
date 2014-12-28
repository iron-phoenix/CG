#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShader>
#include <QFileInfo>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

protected slots:
    void rotate();
    void changeShader(int index);

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

    QGLShaderProgram* currentShader;
    QGLShaderProgram* triangleShader;
    QGLShaderProgram* triangleDisplayShader;
    QGLShaderProgram* triangleNonDisplayShader;

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    QTimer timer;
};

#endif // GLWIDGET_H
