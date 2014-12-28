#include "glwidget.h"

#include <QGLBuffer>
#include <math.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    timer(this)
{
    triangleShader = new QGLShaderProgram();
    triangleDisplayShader = new QGLShaderProgram();
    triangleNonDisplayShader = new QGLShaderProgram();

    projection.perspective(15.0f, 4.0f / 3.0f, 0.1f, 100.f);
    view.lookAt(QVector3D(0.0f, 0.0f, 9.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));

    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(rotate()));
    timer.setSingleShot(false);
}

void GLWidget::initializeGL()
{
    loadShader(triangleShader, ":/v1.vert", QGLShader::Vertex);
    loadShader(triangleShader, ":/f1.frag", QGLShader::Fragment);
    triangleShader->link();

    loadShader(triangleDisplayShader, ":/v2.vert", QGLShader::Vertex);
    loadShader(triangleDisplayShader, ":/f2.frag", QGLShader::Fragment);
    triangleDisplayShader->link();

    loadShader(triangleNonDisplayShader, ":/v3.vert", QGLShader::Vertex);
    loadShader(triangleNonDisplayShader, ":/f3.frag", QGLShader::Fragment);
    triangleNonDisplayShader->link();

    currentShader = triangleShader;
    currentShader->bind();

    timer.start(15);
}

void GLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    currentShader->setUniformValue("model", model);
    currentShader->setUniformValue("view", view);
    currentShader->setUniformValue("projection", projection);

    QGLBuffer buffer(QGLBuffer::VertexBuffer);
    float vertices[9] = {
        0.5f, -0.3f, 0.0f,
        -0.5f, -0.3f, 0.0f,
        0.0f, 0.7f, 0.0f
    };

    buffer.create();
    buffer.setUsagePattern(QGLBuffer::StaticDraw);
    buffer.bind();
    buffer.allocate(vertices, 3 * 3 * sizeof(float));
    currentShader->setAttributeBuffer("vert", GL_FLOAT, 0, 3);
    currentShader->enableAttributeArray("vert");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    buffer.release();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::rotate()
{
    model.rotate(1, QVector3D(0,0,1));
    updateGL();
}

void GLWidget::changeShader(int index)
{
    switch (index) {
    case 1:
        currentShader = triangleDisplayShader;
        break;
    case 2:
        currentShader = triangleNonDisplayShader;
        break;
    case 0:
    default:
        currentShader = triangleShader;
    }
    currentShader->bind();
}
