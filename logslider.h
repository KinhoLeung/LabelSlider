#ifndef LOGSLIDER_H
#define LOGSLIDER_H

#include <QSlider>

class LogSlider : public QSlider
{
    Q_OBJECT

public:
    explicit LogSlider(QWidget *parent = nullptr);
    explicit LogSlider(Qt::Orientation orientation, QWidget *parent = nullptr);

    // 设置对数范围
    void setLogRange(double minVal, double maxVal);
    
    // 获取/设置对数值
    double logValue() const;
    void setLogValue(double value);
    
    // 获取对数范围
    double logMinimum() const { return m_logMin; }
    double logMaximum() const { return m_logMax; }

signals:
    void logValueChanged(double value);

private slots:
    void handleValueChanged(int value);

private:
    double m_logMin;
    double m_logMax;
    
    // 线性值到对数值的转换
    double linearToLog(int linearValue) const;
    int logToLinear(double logValue) const;
    
    void updateRange();
};

#endif // LOGSLIDER_H