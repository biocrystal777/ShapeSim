#include "shagnuplotframe.h"


ShaGnuplotFrame::ShaGnuplotFrame(QWidget *parent, Qt::WindowFlags f) : QFrame(parent, f){

   this->setFrameStyle(0x1011);

   lay = new QGridLayout(this);

   this->setFrameStyle(0x1011);
   //lay = new QGridLayout(this);
   lay->addWidget(new QLabel("<b>Path to Gnuplot</b>", this), 0, 1, 1, 3, Qt::AlignBottom);
   useGnuplotBox = new QCheckBox("use",this);
   lay->addWidget(useGnuplotBox, 1,0,1,2);
   gnuplotPathChooser = new QToolButton(this);
   gnuplotPathChooser->setText("..");
   gnuplotPathChooser->setToolTip("Browse Files");
   QObject::connect(gnuplotPathChooser, SIGNAL(clicked()), this, SLOT(choosegnuplotPath()));
   lay->addWidget(gnuplotPathChooser, 1, 2, 1, 1);
   gnuplotPathName = new QLineEdit(this);
   lay->addWidget(gnuplotPathName, 1, 3, 1, 12);https://www.youtube.com/watch?v=dFamObMUu2k
   QObject::connect(useGnuplotBox, SIGNAL(toggled(bool)), gnuplotPathChooser, SLOT(setEnabled(bool)));
   QObject::connect(useGnuplotBox, SIGNAL(toggled(bool)), gnuplotPathName, SLOT(setEnabled(bool)));
   loadSettings();

}

ShaGnuplotFrame::~ShaGnuplotFrame(){
    writeSettings();
}

void ShaGnuplotFrame::loadSettings()
{
    QSettings settings("AgCoelfen", "ShapeSim");
    settings.setIniCodec("UTF-8");

    useGnuplotBox->setChecked(settings.value(tr("usegnuplot"), false ).toBool());
    gnuplotPathName->setText(settings.value(tr("gnuplotpath"), QString("<Specify path>")).toString());
    gnuplotPathChooser->setEnabled(useGnuplot());
    gnuplotPathName->setEnabled(useGnuplot());

}

void ShaGnuplotFrame::writeSettings()
{
    QSettings settings("AgCoelfen", "ShapeSim");
    settings.setIniCodec("UTF-8");
    settings.setValue(tr("usegnuplot"), useGnuplotBox->isChecked());
    settings.setValue(tr("gnuplotpath"), gnuplotPathName->text());
}

void ShaGnuplotFrame::choosegnuplotPath()
{
    QString oldGnuplotPath = this->gnuplotPath();
    if(!QFile::exists(oldGnuplotPath) || QFileInfo( oldGnuplotPath ).isDir() ) oldGnuplotPath = QFileInfo( gnuplotPathName->text() ).path();
    QFileDialog dialog(this, tr("Choose an file Name for your results,"), oldGnuplotPath);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setOption(QFileDialog::DontConfirmOverwrite, false);
    QObject::connect(&dialog, SIGNAL(fileSelected(QString)), gnuplotPathName, SLOT(setText(QString)));
    dialog.exec();
    QString s = gnuplotPathName->text();
    gnuplotPathName->setText(s);
}























































