#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);

	MainWindow w;
	w.setWindowTitle(QString::fromLocal8Bit("速腾聚创IPANO全景相机标定软件"));
	w.show();

	return a.exec();

// 	int hours = 15, minites = 45, seconds = 36;
// 
// 	QTime time(hours, minites, seconds);
// 
// 	cout << "before: " << time.toString("hhmmss").toStdString() << endl;
// 
// 	QTime time1 = time.addSecs(-1);
// 
// 	cout << "after: " << time1.toString("hhmmss").toStdString() << endl;
// 
// 	waitKey(0);

// 	return 0;
}