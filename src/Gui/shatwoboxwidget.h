#ifndef FFFTWOBOXWIDGET_H
#define FFFTWOBOXWIDGET_H

#include <QtGlobal>

#include <QtWidgets/QWidget>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLabel>

#include <cmath>
#include "./shalog_omp.h"
#include "./shadefinitions.h"

/**************************************************************
***
***  FFFTwoBoxWidget
***  \todo -----> exchange by newer Widget from AF4Eval project
***
**************************************************************/

/*!
 * \brief The FFFTwoBoxWidget class Provides user input of real parameters using scientific notation
 * \details The FFFTwoBoxWidget consist of a ng doubleSpinBox to display a signifand and a QSpinBox to
 *          display an exponent.
 * \author Benedikt Haeusele
 * \version 1.0
 * \date March 2013
 * \copyright GNU General Public License version 3.0
 */

class FFFTwoBoxWidget : public QWidget
{
   Q_OBJECT
public:

   /*!
     * \brief FFFTwoBoxWidget constructor of this class
     * \param toolTipString toolTip that shall be displayed for this widget
     * \param parent parent widget
     */
   explicit FFFTwoBoxWidget(const QString &toolTipString, QWidget *parent = nullptr);
   explicit FFFTwoBoxWidget(QWidget *parent = nullptr);

    FFFTwoBoxWidget(const FFFTwoBoxWidget& src) = delete;
    FFFTwoBoxWidget& operator= (FFFTwoBoxWidget& src) = delete;
    FFFTwoBoxWidget(FFFTwoBoxWidget&& src) = delete;
    FFFTwoBoxWidget& operator= (FFFTwoBoxWidget&& src) = delete;


   /*!
    * \brief ~FFFTwoBoxWidget destructor of this class
    */
   ~FFFTwoBoxWidget();


   /*!
     * \brief value returns the current value of the widgetFFFTwoBoxWidget
     * \return value of the box
     */

   ldouble value() const;

   /*!
     * \brief setValue sets the widget to a value.
     * \param signif significand value for the QoubleSpinBox
     * \param exp exponent for the QSpinBox
     * \param callID Debugging parameter, can be passed to
     *        identify from where the function has been called
     */
   void setValue(ldouble signif, int exp, int callID = 0);

   void setValue(ldouble value);


   /*!
     * \brief setMaximum set the maximum value of the function
     *        Be careful to find the right combination
     *        of significand and exponent when determing the range
     *        of the box system
     * \param sign significand
     * \param exp exponent
     */
   void setMaximum(ldouble sign, int exp);

   /*!
     * \brief setMinimum set the minimum value of the function
     *        Be careful to find the right combination
     *        of significand and exponent when determing the range
     *        of the box system
     * \param sign significand
     * \param exp exponent
     */
   void setMinimum(ldouble sign, int exp);

   /*!
     * \brief setSignifandStep set the stepsize of the significand box.
     *        The exponent box step size is always 1.
     * \param stepSize
     */
   void setSignifandStep(ldouble stepSize);

   void setSignifandDecimals(uint number);
   /*!
     * \brief Calculates the signifand of a ldouble p.e. 345.789 results 3.45789
     *        with an exponent of 2.
     *        The exponent can be obtained by passing a pointer to this result
     * \param number the ldouble to be processed
     * \param exponent pass a pointer to the method to obtain the exponent of the number
     * \return the significand of the number
     **/
   static ldouble calcSignificand(ldouble number, int *exponent = NULL);

   //void setMaximumHeight(int max);
   //void setMinimumHeight(int min);


signals:

   /*!
     * \brief valueChanged Signal is emitted when either the
     *        significand of exponent has been changed
     */
   void valueChanged();

public slots:

   /*!
     * \brief setReadOnly set the readOnly flag of both boxes
     * \param r flag
     */
   void setReadOnly(bool r);

protected:
   QHBoxLayout *layout;
   QDoubleSpinBox* significand;
   QSpinBox *exponent;

   ldouble minimumSign;
   int minimumExp;
   ldouble maximumSign;
   int maximumExp;

protected slots:

   /*!
     * \brief callValueChanged slot is called when either the
     *        significand of exponent has been changed and throws
     *        the signal via valueChanged()
     * \param dummyArgument
     */
   void callValueChanged(QString dummyArgument);

   /*!
     * \brief reNormValues takes values with significand <1.0 or >=10.0 (>-1.0 or <=-10.0)
     *        and brings them to scientific format
     * \param signInput
     */
   void reNormValues(ldouble signInput);
};

#endif // FFFTWOBOXWIDGET_H
