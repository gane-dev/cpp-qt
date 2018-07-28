#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbBrowse_clicked();

    void on_pbBrowse_pressed();

    void on_pbOutput_pressed();

private:
    Ui::MainWindow *ui;
    void loadSettings();
        void saveSettings();

protected:
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
