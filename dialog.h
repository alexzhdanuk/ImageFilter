#ifndef DIALOG_H
#define DIALOG_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDialog>
#include "Structs.h"
#include "OptionsFilter.h"
#include <qlistwidget.h>
#include <QListWidgetItem>
#include "RealizationFilters.h"

namespace Ui {
class Dialog;
}



class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
	OptionsFilter* findOptionsFilterFromName(const QString &name);
	bool setFilterToImage(InstallationFilter* filter);
	void readOptionsFilterFromXml();
	
private slots:
    void on_pushButton_2_clicked();
    
	void onTexture();
	
	void onItemClicked(QListWidgetItem* value);

	
private:
    Ui::Dialog *ui;
    QGraphicsScene* m_Scena;
    QGraphicsItem* m_GraphicsItem;
    QPixmap m_Pixmap;
    QImage m_Image;
    QImage m_outImage;
	QImage m_Texture;
	QSize sizeImage;
    unsigned char *m_listImageIn;
    unsigned char *m_listImageOut;
	unsigned char *m_listTexture;
	QList<OptionsFilter> m_Filters;
	Filters* m_FiltersClass;
};

#endif // DIALOG_H
