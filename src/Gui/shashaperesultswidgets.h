#ifndef SHASHAPERESULTSWIDGETS_H
#define SHASHAPERESULTSWIDGETS_H
#include "./shadefinitions.h"

#include <QDebug>
#include <QtGlobal>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

class ShaShapeResultsWidget : public QWidget {
   Q_OBJECT
public:
   ShaShapeResultsWidget(QWidget *parent = nullptr) : QWidget(parent){
      qDebug() << "1";
      shapeLay = new QGridLayout(this);
      QLabel *label = new QLabel(tr("<b>Sizes:</b>"), this);
      shapeLay->addWidget(label, 0, 4, 1, 3, Qt::AlignCenter);
   }
   ~ShaShapeResultsWidget(){}

   NO_COPY_ASSIGNMENT_CTORS(ShaShapeResultsWidget)

protected:
   QGridLayout *shapeLay = nullptr;
private:
   //virtual ~ShaShapeResWidget(){}
};

class ShaStandardShapeResWidget : public ShaShapeResultsWidget {
public:
   ShaStandardShapeResWidget(QWidget *parent);
   ~ShaStandardShapeResWidget(){}

   inline ldouble getAxAlphaCore(bool *ok = nullptr) const {return axAlphaCoreBox->text().toDouble(ok);}
   inline void setAxAlphaCore(ldouble value) {axAlphaCoreBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxAlphaTot(bool *ok = nullptr) const {return axAlphaTotBox->text().toDouble(ok);}
   inline void setAxAlphaTot(ldouble value) {axAlphaTotBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxBetaCore(bool *ok = nullptr) const {return axBetaCoreBox->text().toDouble(ok);}
   inline void setAxBetaCore(ldouble value) {axBetaCoreBox->setText(QString::number(value, 'f', 2));}
   inline ldouble getAxBetaTot(bool *ok = nullptr) const {return axBetaTotBox->text().toDouble(ok);}
   inline void setAxBetaTot(ldouble value) {axBetaTotBox->setText(QString::number(value, 'f', 2));}

protected:
   QLineEdit *axAlphaCoreBox = nullptr;
   QLineEdit *axAlphaTotBox = nullptr;
   QLineEdit *axBetaCoreBox = nullptr;
   QLineEdit *axBetaTotBox = nullptr;
private:
   NO_COPY_ASSIGNMENT_CTORS(ShaStandardShapeResWidget)
};


class ShaProlateResWidget : public ShaStandardShapeResWidget {
   Q_OBJECT
public:
   ShaProlateResWidget(QWidget *parent = nullptr);
   ~ShaProlateResWidget(){}
   NO_COPY_ASSIGNMENT_CTORS(ShaProlateResWidget)

};

class ShaOblateResWidget : public ShaStandardShapeResWidget {
   Q_OBJECT
public:
   ShaOblateResWidget(QWidget *parent = nullptr);
   ~ShaOblateResWidget(){}
   NO_COPY_ASSIGNMENT_CTORS(ShaOblateResWidget)
};

class ShaLongRodResWidget : public ShaStandardShapeResWidget {
   Q_OBJECT
public:
   ShaLongRodResWidget(QWidget *parent = nullptr);
   ~ShaLongRodResWidget(){}

   NO_COPY_ASSIGNMENT_CTORS(ShaLongRodResWidget)
};
#endif // SHASHAPERESULTSWIDGETS_H
