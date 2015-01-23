#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShader>
#include <QFileInfo>
#include <QTimer>
#include <QGLFunctions>
#include <QMouseEvent>
#include <QWheelEvent>

#include <vector>

using std::vector;

class GLWidget : public QGLWidget, public QGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

protected slots:
    void changeModel(int index);
    void setFiltering(bool is_set);
    void setMultiplier(double multiplier);

    void noFiltering();
    void bilinearFiltering();
    void bicubicFiltering();

private:
    struct Face {
        int vtx[3];
        int uv[3];
        int norm[3];
    };

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

    void loadObjModel(QString name) {
        QFile model_file(name);

        vector<QVector3D> vertices;
        vector<QVector2D> textures;
        vector<Face> faces;

        if (!model_file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "Can't open " << name << endl;
            return;
        }

        QTextStream in(&model_file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList elements = line.split(QRegExp("\\s+"));
            if (elements[0] == "v") vertices.push_back(QVector3D(elements[1].toFloat(), elements[2].toFloat(), elements[3].toFloat()));
            else if(elements[0] == "vt") textures.push_back(QVector2D(elements[1].toFloat(), elements[2].toFloat()));
            else if (elements[0] == "f") {
                Face face;
                for(int i = 0 ; i != 3; ++i){
                    QStringList numbers = elements[i+1].split("/");
                    face.vtx[i] = numbers[0].toInt();
                    face.uv[i] = numbers[1].toInt();
                    face.norm[i] = numbers[2].toInt();
                }
                faces.push_back(face);
            }
        }

        for (vector<Face>::iterator it = faces.begin(); it != faces.end(); ++it) {
            for (int i = 0; i != 3; ++i) {
                this->vertices.push_back(vertices[it->vtx[i] - 1]);
                this->tex_coords.push_back(textures[it->uv[i] - 1]);
            }
        }
    }

    void loadModel(QString file_name) {
        vertices.clear();
        tex_coords.clear();

        loadObjModel(":/" + file_name);
    }

    QGLShaderProgram* shader;
    QGLShaderProgram* simpleShader;
    QGLShaderProgram* bicubicShader;

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    vector<QVector3D> vertices;
    vector<QVector2D> tex_coords;

    GLuint texture;

    float distance;

    int mouseX;
    int mouseY;

    int hAngle;
    int vAngle;

    float multiplier;
};

#endif // GLWIDGET_H
