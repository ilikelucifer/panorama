#include "folderimgs.h"
#include "ui_folderimgs.h"
#include <QDebug>
#include <QPushButton>
#include <QTextCodec>
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractButton>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

FolderImgs::FolderImgs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FolderImgs)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    QStringList header;
    header.append("Select"); header.append("File Name");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
}

void FolderImgs::Init()
{
    state.resize(imgCount); ui->tableWidget->setRowCount(imgCount);
    for(int i=0; i<imgCount; i++)
    {
        state[i]= new QCheckBox();
        if(i<1)
        {
            state[i]->setCheckState(Qt::Checked);
        }
        ui->tableWidget->setCellWidget(i,0,state[i]);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(m_filename[i]));
    }
}

void FolderImgs::showEvent(QShowEvent *showEvent)
{
     AdjustColWidth();
}

FolderImgs::~FolderImgs()
{
    delete ui;
}

void FolderImgs::AdjustColWidth()
{
     int Twidth= ui->tableWidget->width()-ui->tableWidget->verticalHeader()->width();
     int Cwidth=0;
     ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
     for(int i=0; i<ui->tableWidget->columnCount(); i++)
     {
         Cwidth+= ui->tableWidget->columnWidth(i);
     }
     double scale=double(Twidth)/double(Cwidth);
     int left= Twidth;
     ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
     if(Cwidth<Twidth)
     {
         for(int i=0; i<ui->tableWidget->columnCount()-1; i++)
         {
             ui->tableWidget->setColumnWidth(i,int(scale*ui->tableWidget->columnWidth(i)));
             left-= ui->tableWidget->columnWidth(i);
         }
         ui->tableWidget->setColumnWidth(ui->tableWidget->columnCount()-1,left);
     }
}

void FolderImgs::setInfo(vector<QString> abPath, vector<QString> filename, int count)
{
      m_abPath=abPath; m_filename=filename; imgCount=count;
}


void FolderImgs::returnMain(QAbstractButton*button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        int count=0;
        for(int i=0; i<imgCount; i++)
        {
           if(state[i]->isChecked())   count+=1;
        }
        if(count!=1)
        {
			QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("只能选择一副图像！"), QMessageBox::NoButton, QMessageBox::NoButton);
            return;
        }
        else
        {
            count=0;
            for(int i=0; i<imgCount; i++)
            {
               if(state[i]->isChecked())
               {
                   QTextCodec *code = QTextCodec::codecForName("GB2312");
                   string abName = code->fromUnicode(m_abPath[i]).data();
                   path[count]=abName; sPath[count]=m_abPath[i];
                   count+=1;
               }
            }
            accept();
        }
    }
    else
    {
        reject();
    }
}

