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
    xoffset -= (event->x() - oldMousePos.x()) / 150.0;
    yoffset -= (event->y() - oldMousePos.y()) / 150.0;
    oldMousePos = event->pos();
    updateGL();
}

void GLWidget::wheelEvent(QWheelEvent* event) {
    fscale = qMax(0.1, qMin(100.0, fscale + 0.0005 * (float)event->delta()));
    updateGL();
}
