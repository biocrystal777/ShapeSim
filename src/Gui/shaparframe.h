#ifndef SHAPARFRAME_H
#define SHAPARFRAME_H

#include "./shadefinitions.h"
#include <QFrame>
#include <QToolButton>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QSettings>
#include "./shatwoboxwidget.h"
#include "../Core/shaparamstructs.h"
#include <QRadioButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>

class ShaSingleSDPairWidget final : public QWidget {
   Q_OBJECT
public:
   ShaSingleSDPairWidget(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
   ~ShaSingleSDPairWidget();
   ShaSingleSDPairWidget(const ShaSingleSDPairWidget& src) = delete;
   ShaSingleSDPairWidget& operator= (ShaSingleSDPairWidget& src) = delete;
   ShaSingleSDPairWidget(ShaSingleSDPairWidget&& src) = delete;
   ShaSingleSDPairWidget& operator= (ShaSingleSDPairWidget&& src) = delete;

   MeasurementParamaters getMeasurementParameters() const {
      return MeasurementParamaters {
         useDBox->isChecked(),
               useSBox->isChecked(),
               useLamBox->isChecked(),
               useDDevBox->isChecked(),
               useSDevBox->isChecked(),
               useLamDevBox->isChecked(),
               trackDensityBox->isChecked(),
               static_cast<ldouble>(diffCoeffBox->value()),
               static_cast<ldouble>(sedCoeffBox->value()),
               static_cast<ldouble>(waveLengthBox->value()),
               static_cast<ldouble>(diffCoeffDevBox->value()),
               static_cast<ldouble>(sedCoeffDevBox->value()),
               static_cast<ldouble>(waveLengthDevBox->value())
      };
   }

//   inline ldouble getDiffCoeff()     const { return static_cast<ldouble>(diffCoeffBox->value());     }
   inline ldouble getSedCoeff()      const { return static_cast<ldouble>(sedCoeffBox->value());      }
   inline ldouble getLSPRLambda()    const { return static_cast<ldouble>(waveLengthBox->value());    }
   inline bool    useDiffCoeff()     const { return useDBox->isChecked();                            }
   inline bool    useSedCoeff()      const { return useSBox->isChecked();                            }
   inline bool    useLSPRLambda()    const { return useLamBox->isChecked();                          }
   inline ldouble getDiffCoeffDev()  const { return static_cast<ldouble>(diffCoeffDevBox->value());  }
   inline ldouble getSedCoeffDev()   const { return static_cast<ldouble>(sedCoeffDevBox->value());   }
   inline ldouble getLSPRLambdaDev() const { return static_cast<ldouble>(waveLengthDevBox->value()); }
   inline bool    useDiffCoeffDev()  const { return useDBox->isChecked();                            }
   inline bool    useSedCoeffDev()   const { return useSBox->isChecked();                            }
   inline bool    useLSPRLambaDev()  const { return useLamBox->isChecked();                          }
   inline bool    useTrackDensity()  const { return trackDensityBox->isChecked();                    }

   void loadParameters();
private:

   QGridLayout* lay                 = nullptr;
   FFFTwoBoxWidget *diffCoeffBox    = nullptr;
   FFFTwoBoxWidget *sedCoeffBox     = nullptr;
   QDoubleSpinBox *waveLengthBox    = nullptr;
   QCheckBox *useDBox               = nullptr;
   QCheckBox *useSBox               = nullptr;
   QCheckBox *useLamBox             = nullptr;
   FFFTwoBoxWidget *diffCoeffDevBox = nullptr;
   FFFTwoBoxWidget *sedCoeffDevBox  = nullptr;
   QDoubleSpinBox *waveLengthDevBox = nullptr;
   QCheckBox *useDDevBox            = nullptr;
   QCheckBox *useSDevBox            = nullptr;
   QCheckBox *useLamDevBox          = nullptr;
   QCheckBox *trackDensityBox       = nullptr;


public slots:
   void saveParameters() const;
private slots:
   void toggleD(bool on);
   void toggleS(bool on);
   void toggleLam(bool on);
   void toggleDevD(bool on);
   void toggleDevS(bool on);
   void toggleDevLam(bool on);

};

class ShaDistrSDPairWidget final : public QWidget {
   Q_OBJECT
public:
   ShaDistrSDPairWidget(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
   ~ShaDistrSDPairWidget();
   ShaDistrSDPairWidget(const ShaDistrSDPairWidget& src) = delete;
   ShaDistrSDPairWidget& operator= (ShaDistrSDPairWidget& src) = delete;
   ShaDistrSDPairWidget(ShaDistrSDPairWidget&& src) = delete;
   ShaDistrSDPairWidget& operator= (ShaDistrSDPairWidget&& src) = delete;

   QString getDistrFilePath(bool quoted = false) const;
   QToolButton *filePathChooser;

private:

   QGridLayout* lay                 = nullptr;
   QLineEdit *filePath              = nullptr;

   void loadParameters();
   bool setInputFilePath(QString path, bool quoted = true);

   /*!
    * \brief chopStringsQuotMarksToOne if a string has more than one Quotation mark, they are merged
    * \example """this string"""   =>    "this string"
    * \param string to be processed
    * \return processed string
    */
   QString chopStringsQuotMarksToOne(QString &string) const;

   /*!
    * \brief chopStringsQuotMarksEntirely removes quotation marks of strings
    * \example """this string"""   =>    this string
    * \param string to be processed
    * \return processed string
    */
   QString chopStringsQuotMarksEntirely(QString &string) const;

private slots:
   void saveParameters();
   void chooseFilePath();
};


class ShaParFrame final : public QFrame
{
   Q_OBJECT
public:
   ShaParFrame(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
   ~ShaParFrame();
   ShaParFrame(const ShaParFrame& src) = delete;
   ShaParFrame& operator= (ShaParFrame& src) = delete;
   ShaParFrame(ShaParFrame&& src) = delete;
   ShaParFrame& operator= (ShaParFrame&& src) = delete;

   inline bool    calcSinglePair()       const { return singleSwitcher->isChecked(); }
   inline bool    calcPairDistr()        const { return distrSwitcher->isChecked(); }

   PhysicalParameters getPhysicalParameters() const {
      return PhysicalParameters {
         static_cast<ldouble>(coreDensityBox->value()),
               static_cast<ldouble>(surfDensityBox->value()),
               static_cast<ldouble>(solvDensityBox->value()),
               static_cast<ldouble>(viscSolvBox->value()),
               static_cast<ldouble>(temperatureBox->value()),
               static_cast<ldouble>(surfLayerThicknessBox->value()),
               static_cast<ldouble>(solvLayerThicknessBox->value())
      };
   }



   inline MeasurementParamaters getMeasurementParameters() const { return singleSDPairWidget->getMeasurementParameters();}
   inline QString getDistrFile()     const { return this->distSDPairWidget->getDistrFilePath();      }

private:
   QGridLayout *lay                 = nullptr;
   QDoubleSpinBox *coreDensityBox   = nullptr;
   QDoubleSpinBox *surfDensityBox   = nullptr;
   QDoubleSpinBox *solvDensityBox   = nullptr;
   QDoubleSpinBox *viscSolvBox      = nullptr;
   QDoubleSpinBox *temperatureBox   = nullptr;
   QDoubleSpinBox* surfLayerThicknessBox = nullptr;
   QDoubleSpinBox* solvLayerThicknessBox = nullptr;
   QComboBox      *strideBox        = nullptr;

   QGroupBox *singDistSwitchBox              = nullptr;
   QHBoxLayout *singDistLay                  = nullptr;
   QRadioButton *singleSwitcher              = nullptr;
   QRadioButton *distrSwitcher               = nullptr;
   ShaSingleSDPairWidget* singleSDPairWidget = nullptr;
   ShaDistrSDPairWidget* distSDPairWidget    = nullptr;

   void loadParameters();

public slots:
   void saveParameters() const;

private slots:
   void switchToSing(bool chosen);
   void switchToDist(bool chosen);
};

#endif // SHAPARFRAME_H
