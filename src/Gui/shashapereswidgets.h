#ifndef SHASHAPERESWIDGETS_H
#define SHASHAPERESWIDGETS_H
#include "./shadefinitions.h"

#include <QtGlobal>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

class ShaShapeResWidget : public QWidget {
   Q_OBJECT
public:
   ShaShapeResWidget(QWidget *parent = 0) : QWidget(parent){
      shapeLay = new QGridLayout(this);
      QLabel *label = new QLabel(tr("<b>Sizes:</b>"), this);
      shapeLay->addWidget(label, 0, 4, 1, 3, Qt::AlignCenter);
   }
   virtual ~ShaShapeResWidget(){}
   ShaShapeResWidget(const ShaShapeResWidget& src) = delete;
   ShaShapeResWidget& operator= (ShaShapeResWidget& src) = delete;
   ShaShapeResWidget(ShaShapeResWidget&& src) = delete;
   ShaShapeResWidget& operator= (ShaShapeResWidget&& src) = delete;
protected:
   QGridLayout *shapeLay;
private:
   //virtual ~ShaShapeResWidget(){}
};

class ShaNonSphereResWidget : public ShaShapeResWidget {
public:
   ShaNonSphereResWidget(QWidget *parent) : ShaShapeResWidget(parent){}
   virtual ~ShaNonSphereResWidget(){}
   ShaNonSphereResWidget(const ShaNonSphereResWidget& src) = delete;
   ShaNonSphereResWidget& operator= (ShaNonSphereResWidget& src) = delete;
   ShaNonSphereResWidget(ShaNonSphereResWidget&& src) = delete;
   ShaNonSphereResWidget& operator= (ShaNonSphereResWidget&& src) = delete;

   virtual ldouble getAxAlphaCore(bool *ok = nullptr) const = 0;
   virtual void setAxAlphaCore(ldouble value)  = 0;
   virtual ldouble getAxAlphaTot(bool *ok = nullptr) const = 0;
   virtual void setAxAlphaTot(ldouble value) = 0;
   virtual ldouble getAxBetaCore(bool *ok = nullptr) const = 0;
   virtual void setAxBetaCore(ldouble value) = 0;
   virtual ldouble getAxBetaTot(bool *ok = nullptr) const = 0;
   virtual void setAxBetaTot(ldouble value) = 0;
private:

};
/*
class ShaSphereResWidget : public ShaShapeResWidget {
   Q_OBJECT
public:
   ShaSphereResWidget(QWidget *parent = 0);
   ~ShaSphereResWidget(){}
   ShaSphereResWidget(const ShaSphereResWidget& src) = delete;
   ShaSphereResWidget& operator= (ShaSphereResWidget& src) = delete;
   ShaSphereResWidget(ShaSphereResWidget&& src) = delete;
   ShaSphereResWidget& operator= (ShaSphereResWidget&& src) = delete;


   inline ldouble getRadCore(bool *ok = nullptr) const {return radCoreBox->text().toDouble(ok);}
   inline void setRadCore(ldouble value) {radCoreBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getRadTot(bool *ok = nullptr) const {return radTotBox->text().toDouble(ok);}
   inline void setRadTot(ldouble value) {radTotBox->setText(QString::number(value, 'f', 2));}

protected:
   QLineEdit *radCoreBox;
   QLineEdit *radTotBox;
};
*/

class ShaProlateResWidget : public ShaNonSphereResWidget {
   Q_OBJECT
public:
   ShaProlateResWidget(QWidget *parent = 0);

   ShaProlateResWidget(const ShaProlateResWidget& src) = delete;
   ShaProlateResWidget& operator= (ShaProlateResWidget& src) = delete;
   ShaProlateResWidget(ShaProlateResWidget&& src) = delete;
   ShaProlateResWidget& operator= (ShaProlateResWidget&& src) = delete;

   inline ldouble getAxAlphaCore(bool *ok = nullptr) const {return axAlphaCoreBox->text().toDouble(ok);}
   inline void setAxAlphaCore(ldouble value) {axAlphaCoreBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxAlphaTot(bool *ok = nullptr) const {return axAlphaTotBox->text().toDouble(ok);}
   inline void setAxAlphaTot(ldouble value) {axAlphaTotBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxBetaCore(bool *ok = nullptr) const {return axBetaCoreBox->text().toDouble(ok);}
   inline void setAxBetaCore(ldouble value) {axBetaCoreBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxBetaTot(bool *ok = nullptr) const {return axBetaTotBox->text().toDouble(ok);}
   inline void setAxBetaTot(ldouble value) {axBetaTotBox->setText(QString::number(value, 'f', 2));}

protected:
   QLineEdit *axAlphaCoreBox;
   QLineEdit *axAlphaTotBox;
   QLineEdit *axBetaCoreBox;
   QLineEdit *axBetaTotBox;
};

class ShaOblateResWidget : public ShaNonSphereResWidget {
   Q_OBJECT
public:
   ShaOblateResWidget(QWidget *parent = 0);
   ~ShaOblateResWidget(){}
   ShaOblateResWidget(const ShaOblateResWidget& src) = delete;
   ShaOblateResWidget& operator= (ShaOblateResWidget& src) = delete;
   ShaOblateResWidget(ShaOblateResWidget&& src) = delete;
   ShaOblateResWidget& operator= (ShaOblateResWidget&& src) = delete;

   inline ldouble getAxAlphaCore(bool *ok = nullptr) const {return axAlphaCoreBox->text().toDouble(ok);}
   inline void setAxAlphaCore(ldouble value) {axAlphaCoreBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxAlphaTot(bool *ok = nullptr) const {return axAlphaTotBox->text().toDouble(ok);}
   inline void setAxAlphaTot(ldouble value) {axAlphaTotBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxBetaCore(bool *ok = nullptr) const {return axBetaCoreBox->text().toDouble(ok);}
   inline void setAxBetaCore(ldouble value) {axBetaCoreBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxBetaTot(bool *ok = nullptr) const {return axBetaTotBox->text().toDouble(ok);}
   inline void setAxBetaTot(ldouble value) {axBetaTotBox->setText(QString::number(value, 'f', 2));}

protected:
   QLineEdit *axAlphaCoreBox;
   QLineEdit *axAlphaTotBox;
   QLineEdit *axBetaCoreBox;
   QLineEdit *axBetaTotBox;
};

class ShaLongRodResWidget : public ShaNonSphereResWidget {
   Q_OBJECT
public:
   ShaLongRodResWidget(QWidget *parent = 0);
   ~ShaLongRodResWidget(){}
   ShaLongRodResWidget(const ShaLongRodResWidget& src) = delete;
   ShaLongRodResWidget& operator= (ShaLongRodResWidget& src) = delete;
   ShaLongRodResWidget(ShaLongRodResWidget&& src) = delete;
   ShaLongRodResWidget& operator= (ShaLongRodResWidget&& src) = delete;

   inline ldouble getAxAlphaCore(bool *ok = nullptr) const {return axAlphaCoreBox->text().toDouble(ok);}
   inline void setAxAlphaCore(ldouble value) {axAlphaCoreBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxAlphaTot(bool *ok = nullptr) const {return axAlphaTotBox->text().toDouble(ok);}
   inline void setAxAlphaTot(ldouble value) {axAlphaTotBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxBetaCore(bool *ok = nullptr) const {return axBetaCoreBox->text().toDouble(ok);}
   inline void setAxBetaCore(ldouble value) {axBetaCoreBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxBetaTot(bool *ok = nullptr) const {return axBetaTotBox->text().toDouble(ok);}
   inline void setAxBetaTot(ldouble value) {axBetaTotBox->setText(QString::number(value, 'f', 2));}

protected:
   QLineEdit *axAlphaCoreBox;
   QLineEdit *axAlphaTotBox;
   QLineEdit *axBetaCoreBox;
   QLineEdit *axBetaTotBox;
};
#endif // SHASHAPERESWIDGETS_H
