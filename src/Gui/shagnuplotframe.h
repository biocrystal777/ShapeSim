#ifndef SHAGNUPLOTFRAME_H
#define SHAGNUPLOTFRAME_H

#include <QDebug>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QCheckBox>
#include <QToolButton>
#include <QLineEdit>
#include <QSettings>
#include <QFileDialog>

class ShaGnuplotFrame final : public QFrame {
   Q_OBJECT
public:

   ShaGnuplotFrame(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
   ~ShaGnuplotFrame();
   ShaGnuplotFrame(const ShaGnuplotFrame& src) = delete;
   ShaGnuplotFrame& operator= (ShaGnuplotFrame& src) = delete;
   ShaGnuplotFrame(ShaGnuplotFrame&& src) = delete;
   ShaGnuplotFrame& operator= (ShaGnuplotFrame&& src) = delete;

   inline bool useGnuplot() const { return useGnuplotBox->isChecked(); }
   inline QString gnuplotPath() const { return gnuplotPathChooser->text(); }

private:

   QGridLayout *lay                = nullptr;
   QCheckBox   *useGnuplotBox      = nullptr;
   QToolButton *gnuplotPathChooser = nullptr;
   QLineEdit   *gnuplotPathName    = nullptr;

  void loadSettings();

private slots:

  void writeSettings();
  void choosegnuplotPath();
};

#endif // SHAGNUPLOTFRAME_H
