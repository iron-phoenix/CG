#include "glwidget.h"

#include <QGLBuffer>
#include <QtCore/qmath.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    shader(new QGLShaderProgram()),
    xoffset(0.0),
    yoffset(0.0),
    fscale(1.0)
{
    projection.ortho(-1, 1, 1, -1, 0.1, 10);
    view.lookAt(QVector3D(0.0f, 0.0f, 9.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
}

void GLWidget::initializeGL() {
    loadShader(shader, ":/v1.vert", QGLShader::Vertex);
    loadShader(shader, ":/f1.frag", QGLShader::Fragment);
    shader->link();
    shader->bind();
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    shader->setUniformValue("model", model);
    shader->setUniformValue("view", view);
    shader->setUniformValue("projection", projection);

    shader->setUniformValue("fscale", fscale);
    shader->setUniformValue("xoffset", xoffset);
    shader->setUniformValue("yoffset", yoffset);


    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);
    glTexCoord2f(1, 0);
    glVertex2f(1, -1);
    glTexCoord2f(1, 1);
    glVertex2f(1, 1);
    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);
    glEnd();
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
    oldMousePos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
    if(!(event->buttons() & Qt::LeftButton)) return;
    xoffset -= 2.0 * (event->x() - oldMousePos.x()) / float(width());
    yoffset -= 2.0 * (event->y() - oldMousePos.y()) / float(height());
    oldMousePos = event->pos();
    updateGL();
}

void GLWidget::wheelEvent(QWheelEvent* event) {
    float sf = event->delta() > 0 ? 1.1 : 0.9;
    fscale *= sf;
    xoffset = (sf - 1.0) * ((event->x() - float(width()) / 2.0) / float(width()) * 2.0) + sf * xoffset;
    yoffset = (sf - 1.0) * ((event->y() - float(height()) / 2.0) / float(height()) * 2.0) + sf * yoffset;
    updateGL();
}
