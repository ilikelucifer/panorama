#include "query.h"
#include "ui_query.h"
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <QMessageBox>

using namespace cv;

QueryDialog::QueryDialog(QWidget *parent)
	:QDialog(parent), ui(new Ui::QueryDialog)
{
	ui->setupUi(this);
	setFixedSize(this->width(), this->height());
	open_success = false;
}


QueryDialog::~QueryDialog()
{
	delete ui;
}


void QueryDialog::on_pushButton_clicked()
{
	QxmlPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "../param",
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (QxmlPath != "")
	{
		ui->textEdit->setText(QxmlPath);
		//ÔØÈëcalibration²ÎÊý
		FileStorage fc;
		fc.open(QxmlPath.toStdString() + "/common.xml", cv::FileStorage::READ);

		if (fc.isOpened())
		{
			open_success = true;

			fc["correctCurve"] >> mapCurve;
			fc["correctRatio"] >> fovRatio;
			fc["halfFov"] >> halfFov;
			fc["caliScale"] >> caliScale;
			fc["fuseBand"] >> fuseBand;
			fc["cropRatio"] >> cropRatio;

			fc["caliSize"] >> caliSize;
			fc["stitchRoiW"] >> stitchRoiW;
			fc["stitchRoiH"] >> stitchRoiH;
		
			fc.release();

			close();
		}
		else
		{
			QMessageBox::information(this, "Error", "Can not find the common xml file !");
			open_success = false;
		}

	}
}


bool QueryDialog::isOpen()
{
	return open_success;
}


void QueryDialog::showEvent(QShowEvent *e)
{

}