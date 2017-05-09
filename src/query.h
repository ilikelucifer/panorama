#ifndef QUERY_H
#define QUERY_H

#include <QDialog>

using namespace std;


namespace Ui {
	class QueryDialog;
}


class QueryDialog: public QDialog
{
	Q_OBJECT

public:
	explicit QueryDialog(QWidget *parent = 0);
	~QueryDialog();

	virtual void showEvent(QShowEvent *e);

public:

	bool isOpen();

	int caliSize;
	double halfFov;
	double cropRatio;
	double mapCurve;
	double fovRatio;
	double stitchRoiW;
	double stitchRoiH;
	int fuseBand;
	double caliScale;

	QString QxmlPath;

	bool open_success;

private slots:

void on_pushButton_clicked();


private:

	Ui::QueryDialog *ui;
};



#endif