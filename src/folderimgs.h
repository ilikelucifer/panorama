#ifndef FOLDERIMGS_H
#define FOLDERIMGS_H

#include <QDialog>
#include <Qcheckbox>
#include <vector>
using namespace std;

namespace Ui {
class FolderImgs;
}

class FolderImgs : public QDialog
{
    Q_OBJECT

public:
    explicit FolderImgs(QWidget *parent = 0);
    ~FolderImgs();
    virtual void showEvent(QShowEvent *showEvent);

    void setInfo(vector<QString> abPath, vector<QString> filename, int count);
    void Init();
    string path[3];//´æ´¢Í¼ÏñÃû³Æ£¨±ê×¼string£©
    QString sPath[3];//´æ´¢Í¼ÏñÃû³Æ£¨QString£©

public:
    Ui::FolderImgs *ui;

    vector<QCheckBox*> state;
    vector<QString> m_abPath, m_filename;

    int imgCount;

    void AdjustColWidth();

private slots:

    void returnMain(QAbstractButton*button);

};

#endif // FOLDERIMGS_H
