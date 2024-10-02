#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMessageBox>
// #include <QGraphicsView>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <climits>

extern "C" {
#include "s21_calculate.h"
#include "s21_credit.h"
#include "s21_deposit.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void input();

  void input_symbols();

  void input_functions();

  void on_all_clean_button_clicked();

  void on_result_button_clicked();

  void on_graphics_button_clicked();

  void validators();

  void on_calculate_credit_button_clicked();

  void on_calculate_deposit_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
