#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "OpenSSD.h"
#include "OpenSSD_API.h"

int flag = 0;

using namespace std;
extern "C"
{
    #include "nvme_low_lib.h"
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() //weight data map
{
        ui->label_7->clear();
        int aa =3;
        char dev[] = "/dev/nvme0n60124672p1";
        //char weight_file[20];
        //char image_file[20];
        //char weight_file[] = "/home/nvme/input.bin";
        //char image_file[] = "/home/nvme/image_data/07.bin";
        char input;
        int image_flag=1;
        //image_flag = Run_OpenSSD(dev,weight_file,image_file,image_flag);
        QString weightfile = ui->textEdit->toPlainText();
        QString imagefile = ui->textEdit_2->toPlainText();
        if(weightfile.isEmpty()||weightfile.isNull()||imagefile.isEmpty()||imagefile.isNull())
        {
            ui->label_7->setStyleSheet("color:red;");
            ui->label_7->setText("please input weight/image data file path!!!");
        }
        else
        {
            //ui->textEdit->setText("/home/nvme/input.bin");
           // ui->textEdit_2->setText("/home/nvme/image_data/07.bin");
            char *weight_file = weightfile.toLocal8Bit().data();
            char *image_file = imagefile.toLocal8Bit().data();
            if(move_weight_data(dev,weight_file))
            {
                 ui->textBrowser->setText("weight map finish");
            }
            else
            {
                 ui->textBrowser->setText("weight map finish");
            }
            /*std::vector<sortclass> result;
            result = run_image_result(dev, image_file);
            cout<<"results:";
            for(int i=0;i<5;i++) printf("(%3d,%02x) ", result[i].index,result[i].data);
            cout<<endl;
            QString temp;
            temp.sprintf("top1 =%d , top2 = %d , top3 = %d , top4 = %d, top5 = %d",result[0].index,result[1].index,result[2].index,result[3].index,result[4].index);
            ui->textBrowser_2->append(temp);*/
            flag = 1;
        }
}



void MainWindow::on_pushButton_2_clicked() //run
{
    ui->label_7->clear();
    int aa =3;
    char dev[] = "/dev/nvme0n60124672p1";
    //char weight_file[20];
    //char image_file[20];
    //char weight_file[] = "/home/nvme/input.bin";
    //char image_file[] = "/home/nvme/image_data/07.bin";
    char input;
    int image_flag=1;
    //image_flag = Run_OpenSSD(dev,weight_file,image_file,image_flag);
    QString weightfile = ui->textEdit->toPlainText();
    QString imagefile = ui->textEdit_2->toPlainText();
    //ui->textEdit->setText("/home/nvme/input.bin");
    //ui->textEdit_2->setText("/home/nvme/image_data/07.bin");
    if(weightfile.isEmpty()||weightfile.isNull()||imagefile.isEmpty()||imagefile.isNull())
    {
        ui->label_7->setStyleSheet("color:red;");
        ui->label_7->setText("please input weight/image data file path!!!");
    }
    else
    {
        char *weight_file = weightfile.toLocal8Bit().data();
        char *image_file = imagefile.toLocal8Bit().data();
        /*if(move_weight_data(dev,weight_file))
        {
             ui->textBrowser->setText("weight map successfully");
        }
        else
        {
             ui->textBrowser->setText("weight map failed");
        }*/
        std::vector<sortclass> result;
        result = run_image_result(dev, image_file);
        cout<<"results:";
        for(int i=0;i<15;i++) printf("(%3d,%02x) ", result[i].index,result[i].data);
        cout<<endl;
        QString temp;
        temp.sprintf("top1 =%d , top2 = %d , top3 = %d , top4 = %d, top5 = %d",result[0].index,result[1].index,result[2].index,result[3].index,result[4].index);
        ui->textBrowser_2->append(temp);
        QString hashcode;
        for(int i=0;i<15;i++)
        {
            temp.sprintf("%02x",result[i].data);
            hashcode.append(temp);
        }
        ui->textBrowser_3->append(hashcode);
    }



}

void MainWindow::on_pushButton_3_clicked() //image data map
{
    ui->label_7->clear();
    int aa =3;
    char dev[] = "/dev/nvme0n60124672p1";
    //char weight_file[20];
    //char image_file[20];
    //char weight_file[] = "/home/nvme/input.bin";
    //char image_file[] = "/home/nvme/image_data/07.bin";
    //char input;
    //int image_flag=1;
    //image_flag = Run_OpenSSD(dev,weight_file,image_file,image_flag);
    QString weightfile = ui->textEdit->toPlainText();
    QString imagefile = ui->textEdit_2->toPlainText();
    //ui->textEdit->setText("/home/nvme/input.bin");
    //ui->textEdit_2->setText("/home/nvme/image_data/07.bin");
    if(weightfile.isEmpty()||weightfile.isNull()||imagefile.isEmpty()||imagefile.isNull())
    {
        ui->label_7->setStyleSheet("color:red;");
        ui->label_7->setText("please input weight/image data file path!!!");
    }
    else
    {
        char *weight_file = weightfile.toLocal8Bit().data();
        char *image_file = imagefile.toLocal8Bit().data();
        /*if(move_weight_data(dev,weight_file))
        {
             ui->textBrowser->setText("weight map successfully");
        }
        else
        {
             ui->textBrowser->setText("weight map failed");
        }*/
        std::vector<sortclass> result;
        run_image_data(dev, image_file);
        ui->textBrowser_4->setText("image data map done!");
    }

}

void MainWindow::on_pushButton_4_clicked() //test weight data
{
    ui->label_7->clear();
    int aa =3;
    char dev[] = "/dev/nvme0n60124672p1";
    //char weight_file[20];
    //char image_file[20];
    //char weight_file[] = "/home/nvme/input.bin";
    //char image_file[] = "/home/nvme/image_data/07.bin";
    char input;
    int image_flag=1;
    //image_flag = Run_OpenSSD(dev,weight_file,image_file,image_flag);
    QString weightfile = ui->textEdit->toPlainText();
    QString imagefile = ui->textEdit_2->toPlainText();
    if(weightfile.isEmpty()||weightfile.isNull()||imagefile.isEmpty()||imagefile.isNull())
    {
        ui->label_7->setStyleSheet("color:red;");
        ui->label_7->setText("please input weight/image data file path!!!");
    }
    else
    {
        //ui->textEdit->setText("/home/nvme/input.bin");
        //ui->textEdit_2->setText("/home/nvme/image_data/07.bin");
        char *weight_file = weightfile.toLocal8Bit().data();
        char *image_file = imagefile.toLocal8Bit().data();
        if(run_weight_data(dev,weight_file))
        {
             ui->textBrowser->setText("weight map successfully");
        }
        else
        {
             ui->textBrowser->setText("weight map failed");
        }
    }

}
