#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QtCore/qmath.h>
#include <QDebug>
#include <math.h>
#include <QBuffer>
#include <qmessagebox.h>
#include <qapplication.h>
#include <QPainter>
#include <QLinearGradient>
#include "QXmlStreamReader"
#include <QDomDocument>
#include <qmath.h>

#define FILTER_COUNT 10
#define XML_FILE_NAME "1.xml"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),m_Pixmap(),m_Image()
{
    ui->setupUi(this);
    m_Scena = new QGraphicsScene();
    m_Scena->setSceneRect(0,0,400,400);
    ui->graphicsView->setScene(m_Scena);
    
	
    
	readOptionsFilterFromXml();

	
	foreach(OptionsFilter row, m_Filters)
	{
		ui->listFilter->addItem(row.NameFilter);
	}

    m_FiltersClass = 0;
	connect(ui->ButtonTexture,SIGNAL(clicked()),this,SLOT(onTexture()));
	connect(ui->listFilter,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onItemClicked(QListWidgetItem*)));
}



Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onTexture()
{
	QString file = QFileDialog::getOpenFileName(this,"","");
	m_Texture.load(file);
	m_Texture = m_Texture.convertToFormat(QImage::Format_ARGB32);
	m_Texture = m_Texture.scaled(m_Image.width(),m_Image.height());
	m_listTexture = m_Texture.bits();

	m_Scena->removeItem(m_GraphicsItem);
    delete m_GraphicsItem;

    m_Scena->setSceneRect(0,0,m_Image.width(),m_Image.height());
    ui->graphicsView->fitInView(m_Scena->sceneRect(),Qt::KeepAspectRatio);
	m_GraphicsItem = m_Scena->addPixmap(QPixmap::fromImage(m_FiltersClass->addTexture(m_listImageIn,m_listTexture)));
}

void Dialog::on_pushButton_2_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,"","");
    m_Image.load(file);
    m_Image  = m_Image.convertToFormat(QImage::Format_ARGB32);
	sizeImage = QSize(m_Image.width(),m_Image.height());
    m_listImageIn = m_Image.bits();
    m_listImageOut = new unsigned char[m_Image.byteCount()];
	
	if(m_FiltersClass != 0) delete m_FiltersClass;
	m_FiltersClass = new Filters(sizeImage);

	int countItem = sizeImage.width()*sizeImage.height()*4;
	
	for(int i=0; i<countItem;i+=4)
    {
		m_listImageOut[i] = m_listImageIn[i];
        m_listImageOut[i+1] = m_listImageIn[i+1];
        m_listImageOut[i+2] = m_listImageIn[i+2];
		m_listImageOut[i+3] = m_listImageIn[i+3];
	}


    m_Pixmap = m_Pixmap.fromImage(m_Image);
    m_Scena->setSceneRect(0,0,m_Image.width(),m_Image.height());
    ui->graphicsView->fitInView(m_Scena->sceneRect(),Qt::KeepAspectRatio);
    m_GraphicsItem = m_Scena->addPixmap(m_Pixmap);
    m_Scena->update();

}



void Dialog::onItemClicked(QListWidgetItem* value)
{
	
	if(m_Pixmap.size() == QSize(0,0)) return;
	
	OptionsFilter* temp = findOptionsFilterFromName(value->text());
	
	int countItem = sizeImage.width()*sizeImage.height()*4;
	for(int i=0; i<countItem;i+=4)
    {
		m_listImageOut[i] = m_listImageIn[i];
        m_listImageOut[i+1] = m_listImageIn[i+1];
        m_listImageOut[i+2] = m_listImageIn[i+2];
		m_listImageOut[i+3] = m_listImageIn[i+3];
	}

	for(int i=0;i<FILTER_COUNT;i++)
	{
		setFilterToImage(&temp->filter[i]);
	}

	
	m_Scena->removeItem(m_GraphicsItem);
    delete m_GraphicsItem;

    m_Scena->setSceneRect(0,0,m_Image.width(),m_Image.height());
    ui->graphicsView->fitInView(m_Scena->sceneRect(),Qt::KeepAspectRatio);
	m_GraphicsItem = m_Scena->addPixmap(QPixmap::fromImage(m_outImage));
}


OptionsFilter* Dialog::findOptionsFilterFromName(const QString &name)
{
	for(int i=0;i<m_Filters.count();i++)
	{
		if(m_Filters[i].NameFilter == name)
			return &m_Filters[i];
	}
}


bool Dialog::setFilterToImage(InstallationFilter* filter)
{
	switch(filter->getName())
	{
	case Sepia:
		if(filter->getState()) m_outImage = m_FiltersClass->addSepia(m_listImageOut,filter->getValue()==0 ? 80 : filter->getValue()/5+80);
		break;
	case Saturation:
		if(filter->getState())  m_outImage = m_FiltersClass->addSaturation(m_listImageOut,filter->getValue());
		break;
	case Shine:
		if(filter->getState()) m_outImage = m_FiltersClass->addShine(m_listImageOut,filter->getValue());
		break;
	case Blur:
		if(filter->getState()) m_outImage = m_FiltersClass->addBlur(m_listImageOut,filter->getValue());
		break;
	case Colour:
		if(filter->getState()) m_outImage = m_FiltersClass->addColour(m_listImageOut,filter->GetColour()); 
		break;	
	case Contrast:
		if(filter->getState()) m_outImage = m_FiltersClass->addContrast(m_listImageOut,filter->getValue()); 
		break;
	case Brightnes:
		if(filter->getState())  m_outImage = m_FiltersClass->addBrightnes(m_listImageOut,filter->getValue()); 
		break;
	case Opacity:
		if(filter->getState())  m_outImage = m_FiltersClass->addOpacity(m_listImageOut,filter->getValue()); 
		break;
	case Gradient:
		if(filter->getState())  m_outImage = m_FiltersClass->addGradient(m_listImageOut,filter->getGradientColourNach(),filter->getGradientColourKon()); 
		break;
	default:
		break;
	}
	
	return false;
}



void Dialog::readOptionsFilterFromXml()
{

	QFile file(XML_FILE_NAME);
    QDomDocument doc;

    if(file.open(QIODevice::ReadOnly))
    {
        doc.setContent(&file);
        QDomNodeList groups = doc.elementsByTagName("Filters").at(0).childNodes();

        for(int i = 0;i<groups.count();i++)
        {
			qDebug()<<groups.count();
			OptionsFilter filterOpt(groups.at(i).toElement().attribute("name"));

            for(int j = 0;j<groups.at(i).childNodes().count();j++)
            {
				qDebug()<<groups.at(i).childNodes().count();
                QDomNode value = groups.at(i).childNodes().at(j);
				filterOpt.filter[j].setName(value.toElement().attribute("name").toInt());
				filterOpt.filter[j].setActive(value.toElement().attribute("isActive").toInt() == 1 ? true : false);
				filterOpt.filter[j].setRgbColour(rgb(value.toElement().attribute("r").toInt(),value.toElement().attribute("g").toInt(),value.toElement().attribute("b").toInt()));
				filterOpt.filter[j].setGradientColorKon(QColor(value.toElement().attribute("r").toInt(),value.toElement().attribute("g").toInt(),value.toElement().attribute("b").toInt(),value.toElement().attribute("a").toInt()));
				filterOpt.filter[j].setGradientColorNach(QColor(value.toElement().attribute("R").toInt(),value.toElement().attribute("G").toInt(),value.toElement().attribute("B").toInt(),value.toElement().attribute("a").toInt()));
				filterOpt.filter[j].setValue(value.toElement().attribute("value").toInt());
				qDebug()<<value.toElement().attribute("a").toInt();
			}
			m_Filters << filterOpt;
          }
        file.close();
    }
    

}

