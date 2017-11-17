#ifndef _DMR_MPV_GLWIDGET_H
#define _DMR_MPV_GLWIDGET_H 

#include <QtWidgets>
#include <mpv/opengl_cb.h>
#undef Bool
#include <mpv/qthelper.hpp>

namespace dmr {
class MpvGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    friend class MpvProxy;

    MpvGLWidget(QWidget *parent, mpv::qt::Handle h);
    virtual ~MpvGLWidget();

    /*
     * rounded clipping consumes a lot of resources, and performs bad on 4K video
     */
    void toggleRoundedClip(bool val);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void setPlaying(bool);
    void setMiniMode(bool);

protected slots:
    void onNewFrame();
    void onFrameSwapped();

private:
    mpv::qt::Handle _handle;
    mpv_opengl_cb_context *_gl_ctx {nullptr};
    bool _playing {false};
    bool _inMiniMode {false};
    bool _doRoundedClipping {true};

    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer _vbo;
    QOpenGLTexture *_darkTex {nullptr};
    QOpenGLTexture *_lightTex {nullptr};
    QOpenGLShaderProgram *_glProg {nullptr};

    QOpenGLVertexArrayObject _vaoBlend;
    QOpenGLBuffer _vboBlend;
    QOpenGLShaderProgram *_glProgBlend {nullptr};
    QOpenGLFramebufferObject *_fbo {nullptr};
    QOpenGLShaderProgram *_glProgBlendCorners {nullptr};

    //textures for corner
    QOpenGLVertexArrayObject _vaoCorner;
    QOpenGLTexture *_cornerMasks[4] {nullptr,};
    QOpenGLBuffer _vboCorners[4];
    QOpenGLShaderProgram *_glProgCorner {nullptr};

    QImage bg_dark;
    QImage bg_light;

    void updateVbo();
    void updateVboCorners();
    void updateVboBlend();

    void updateMovieFbo();
    void updateCornerMasks();

    void setupBlendPipe();
    void setupIdlePipe();

    void prepareSplashImages();

};

}

#endif /* ifndef _DMR_MPV_GLWIDGET_H */

