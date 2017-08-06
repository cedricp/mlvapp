/*!
 * \file MainWindow.h
 * \author masc4ii
 * \copyright 2017
 * \brief The main window
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include <QTimerEvent>
#include <QResizeEvent>
#include <QFileOpenEvent>
#include <QThreadPool>
#include <QProcess>
#include "../../src/mlv_include.h"
#include "InfoDialog.h"
#include "StatusDialog.h"
#include "Histogram.h"
#include "WaveFormMonitor.h"
#include "ReceiptSettings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int &argc, char **argv, QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent( QTimerEvent *t );
    void resizeEvent( QResizeEvent *event );
    bool event( QEvent *event );

private slots:
    void on_actionOpen_triggered();
    void on_actionAbout_triggered();
    void on_horizontalSliderPosition_valueChanged(void);
    void on_actionClip_Information_triggered();
    void on_horizontalSliderExposure_valueChanged(int position);
    void on_horizontalSliderTemperature_valueChanged(int position);
    void on_horizontalSliderTint_valueChanged(int position);
    void on_horizontalSliderSaturation_valueChanged(int position);
    void on_horizontalSliderDS_valueChanged(int position);
    void on_horizontalSliderDR_valueChanged(int position);
    void on_horizontalSliderLS_valueChanged(int position);
    void on_horizontalSliderLR_valueChanged(int position);
    void on_horizontalSliderLighten_valueChanged(int position);
    void on_actionGoto_First_Frame_triggered();
    void on_actionExport_triggered();
    void on_checkBoxHighLightReconstruction_toggled(bool checked);
    void on_checkBoxReinhardTonemapping_toggled(bool checked);
    void on_actionZoomFit_triggered();
    void on_actionZoom100_triggered();
    void on_actionShowHistogram_triggered(bool checked);
    void on_actionShowWaveFormMonitor_triggered(bool checked);
    void on_actionAlwaysUseAMaZE_triggered(bool checked);
    void on_actionExportSettings_triggered();
    void on_actionResetReceipt_triggered();
    void on_actionCopyRecept_triggered();
    void on_actionPasteReceipt_triggered();
    void readFFmpegOutput( void );
    void endExport( void );
    void on_listWidgetSession_doubleClicked(const QModelIndex &index);
    void on_dockWidgetSession_visibilityChanged(bool visible);
    void on_dockWidgetEdit_visibilityChanged(bool visible);

private:
    Ui::MainWindow *ui;
    InfoDialog *m_pInfoDialog;
    StatusDialog *m_pStatusDialog;
    Histogram *m_pHistogram;
    WaveFormMonitor *m_pWaveFormMonitor;
    mlvObject_t *m_pMlvObject;
    processingObject_t *m_pProcessingObject;
    QLabel *m_pRawImageLabel;
    QLabel *m_pCachingStatus;
    QLabel *m_pFpsStatus;
    uint8_t *m_pRawImage;
    uint32_t m_cacheSizeMB;
    uint8_t m_codecProfile;
    bool m_frameChanged;
    int m_currentFrameIndex;
    double m_newPosDropMode;
    bool m_dontDraw;
    bool m_frameStillDrawing;
    bool m_fileLoaded;
    int m_timerId;
    int m_timerCacheId;
    QString m_lastSaveFileName;
    QString m_lastMovFileName;
    QProcess *m_pFFmpeg;
    ReceiptSettings *m_pReceiptClipboard;
    void drawFrame( void );
    void openMlv( QString fileName );
    void playbackHandling( int timeDiff );
    void initGui( void );
    void initLib( void );
    void readSettings( void );
    void writeSettings( void );
    void startExport( QString fileName );
    void addFileToSession( QString fileName );
    void deleteFileFromSession( int index );
    bool isFileInSession( QString fileName );
    void editFileInSession( int index );
    void setSliders( ReceiptSettings *sliders );
    void setReceipt( ReceiptSettings *sliders );
};

class RenderPngTask : public QRunnable
{
public:
    RenderPngTask( mlvObject_t *pMlvObject, QString fileName, int frame = 0 )
    {
        m_frame = frame;
        m_pMlvObject = pMlvObject;
        m_fileName = fileName;
    }
private:
    void run();

    int m_frame;
    QString m_fileName;
    mlvObject_t *m_pMlvObject;
};

#endif // MAINWINDOW_H
