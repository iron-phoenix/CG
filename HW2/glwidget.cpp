#include "glwidget.h"

#include <QGLBuffer>
#include <QSlider>
#include <math.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    simpleShader(new QGLShaderProgram()),
    wavesShader(new QGLShaderProgram()),
    timer(this),
    distance(30.0),
    time(0.0)
{
    projection.perspective(30.0f, 4.0f / 3.0f, 0.1f, 100.f);

    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    timer.setSingleShot(false);

    setMouseTracking(false);
}

void GLWidget::initializeGL()
{
    loadObjModel(":/model.obj");

    initializeGLFunctions();
    glGenBuffers(2, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(float) * 3, triangles.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, norms.size() * sizeof(float) * 3, norms.data(), GL_STATIC_DRAW);

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    loadShader(simpleShader, ":/v1.vert", QGLShader::Vertex);
    loadShader(simpleShader, ":/f1.frag", QGLShader::Fragment);
    simpleShader->link();

    loadShader(wavesShader, ":/v2.vert", QGLShader::Vertex);
    loadShader(wavesShader, ":/f2.frag", QGLShader::Fragment);
    wavesShader->link();

    QVector3D center;
    max_distance = 0.0;
    for(vector<QVector3D>::iterator it = triangles.begin(); it != triangles.end(); ++it){
        center += (*it);
    }
    center /= triangles.size();

    for(vector<QVector3D>::iterator it = triangles.begin(); it != triangles.end(); ++it){
        max_distance = std::max(max_distance, ((*it) - center).length());
    }

    wavesShader->bind();
    wavesShader->setUniformValue("v", (float) 0);
    wavesShader->setUniformValue("center", center);
    wavesShader->setUniformValue("k", (float) M_2_PI / max_distance);

    currentShader = simpleShader;
    currentShader->bind();

    timer.start(15);
}

void GLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, -distance), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));

    currentShader->setUniformValue("model", model);
    currentShader->setUniformValue("view", view);
    currentShader->setUniformValue("projection", projection);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    currentShader->setAttributeBuffer( "vertex", GL_FLOAT, 0, 3 );
    currentShader->enableAttributeArray( "vertex" );

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    currentShader->setAttributeBuffer( "norm", GL_FLOAT, 0, 3 );
    currentShader->enableAttributeArray( "norm" );

    currentShader->setUniformValue("color", QVector3D(1,1,1));
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, triangles.size());

    if(grid){
        currentShader->setUniformValue("color", QVector3D(0.0,0.0,1.0));
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_POLYGON_OFFSET_LINE);
        glPolygonOffset(-1, -1);
        glDrawArrays(GL_TRIANGLES, 0, triangles.size());
    }
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
    model.rotate( -(event->y() - mouseY), 1, 0);
    model.rotate( -(event->x() - mouseX), 0, 1);
    mouseX = event->x();
    mouseY = event->y();
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
    mouseX = event->x();
    mouseY = event->y();
}

void GLWidget::wheelEvent(QWheelEvent* event) {
    distance -= event->delta() / 120;
    distance = std::max(distance, 0.0f);
}

void GLWidget::changeModel(int index)
{
    QSlider* kSlider = this->parentWidget()->findChild<QSlider*>("kSlider");
    QSlider* vSlider = this->parentWidget()->findChild<QSlider*>("vSlider");
    switch (index) {
    case 1:
        currentShader = simpleShader;
        currentShader->bind();
        currentShader->setUniformValue("norm_color", true);
        kSlider->setEnabled(false);
        vSlider->setEnabled(false);
        break;
    case 2:
        currentShader = wavesShader;
        currentShader->bind();
        kSlider->setEnabled(true);
        vSlider->setEnabled(true);
        break;
    case 0:
    default:
        currentShader = simpleShader;
        currentShader->bind();
        currentShader->setUniformValue("norm_color", false);
        kSlider->setEnabled(false);
        vSlider->setEnabled(false);
    }
}

void GLWidget::setGrid(bool new_value)
{
    grid = new_value;
}

void GLWidget::setV(int v)
{
    wavesShader->bind();
    wavesShader->setUniformValue("v", (float) (2 * M_PI * v));
}

void GLWidget::setK(int k)
{
    wavesShader->bind();
    wavesShader->setUniformValue("k", (float) (2 * M_PI * k / max_distance));
}

void GLWidget::update()
{
    time += ((float) timer.interval()) / 1000.0;
    wavesShader->setUniformValue("time", time);
    updateGL();
}
