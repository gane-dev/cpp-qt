#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include "opencv2/opencv.hpp"
#include <QMessageBox>
#include <QCloseEvent>
#include <QSettings>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbBrowse_clicked()
{

}

void MainWindow::on_pbBrowse_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open Input Image",QDir::currentPath(),"Image(*.jpg *.png *.bmp) ");
    if(QFile::exists(fileName))
    {
        ui->txtInputImage->setText(fileName);
    }
}

void MainWindow::on_pbOutput_pressed()
{
QString fileName = QFileDialog::getSaveFileName(this,"Select Output Image",QDir::currentPath(),"*.jpg;;*.png;;*.bmp");
if (!fileName.isEmpty())
{
    ui->txtOutputImage->setText(fileName);
    using namespace  cv;
    Mat inpImg, outImg;
    inpImg = imread(ui->txtInputImage->text().toStdString());
    if (ui->rdMedian->isChecked())
        medianBlur(inpImg,outImg,5);
    else if (ui->rdGaussian->isChecked())
        GaussianBlur(inpImg,outImg,Size(5,5),1.25);
    imwrite(fileName.toStdString(),outImg);
    if(ui->chkDisplayImage->isChecked())
        cv::imshow("Output Image",outImg);
    }
}

void MainWindow:: closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::warning(this,"Exit","Are you sure you want to close this program?",
                                      QMessageBox::Yes,
                                      QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
void MainWindow::loadSettings()
{
  QSettings settings("Packt",
    "Hello_OpenCV_Qt",
     this);
  ui->txtInputImage->setText(settings.value("inputLineEdit",
    "").toString());
  ui->txtOutputImage->setText(settings.value("outputLineEdit",
    "").toString());
  ui->rdMedian
    ->setChecked(settings.value("medianBlurRadioButton",
    true).toBool());
  ui->rdGaussian
    ->setChecked(settings.value("gaussianBlurRadioButton",
    false).toBool());
  ui->chkDisplayImage->setChecked(settings.value("displayImageCheckBox",
    false).toBool());
}
