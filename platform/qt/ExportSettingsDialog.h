/*!
 * \file ExportSettingsDialog.h
 * \author masc4ii
 * \copyright 2017
 * \brief Select codec
 */

#ifndef EXPORTSETTINGSDIALOG_H
#define EXPORTSETTINGSDIALOG_H

#include <QDialog>

#define CODEC_PRORES422PROXY 0
#define CODEC_PRORES422LT    1
#define CODEC_PRORES422ST    2
#define CODEC_PRORES422HQ    3
#define CODEC_PRORES4444     4
#define CODEC_AVIRAW         5

namespace Ui {
class ExportSettingsDialog;
}

class ExportSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportSettingsDialog(QWidget *parent = 0, uint8_t currentCodecProfile = 0, uint8_t previewMode = 0);
    ~ExportSettingsDialog();
    uint8_t encoderSetting(void);
    bool isExportAudioEnabled(void);
    uint8_t previewMode(void);

private:
    Ui::ExportSettingsDialog *ui;
};

#endif // EXPORTSETTINGSDIALOG_H
