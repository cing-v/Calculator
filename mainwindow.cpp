#include "mainwindow.h"

#include "./ui_mainwindow.h"

bool check_point = false;
bool check_start = true;
bool waiting_symbols = false;
int open_close_buttons = 0;
QString symbols = "+-*/%^";
QString numbers = "123456789";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->setWindowTitle("SmartCalc_v1.0");

  ui->setupUi(this);
  validators();
  ui->tabWidget->setCurrentIndex(0);

  connect(ui->button_0, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->button_1, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->button_2, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->button_3, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->button_4, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->button_5, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->button_6, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->button_7, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->button_8, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->button_9, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->point_button, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui->plus_button, SIGNAL(clicked()), this, SLOT(input_symbols()));
  connect(ui->minus_button, SIGNAL(clicked()), this, SLOT(input_symbols()));
  connect(ui->multy_button, SIGNAL(clicked()), this, SLOT(input_symbols()));
  connect(ui->div_button, SIGNAL(clicked()), this, SLOT(input_symbols()));
  connect(ui->open_button, SIGNAL(clicked()), this, SLOT(input_symbols()));
  connect(ui->close_button, SIGNAL(clicked()), this, SLOT(input_symbols()));
  connect(ui->mod_button, SIGNAL(clicked()), this, SLOT(input_symbols()));
  connect(ui->sqr_button, SIGNAL(clicked()), this, SLOT(input_symbols()));
  connect(ui->sin_button, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->cos_button, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->tan_button, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->asin_button, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->acos_button, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->atan_button, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->ln_button, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->log_button, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->sqrt_button, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->x_button, SIGNAL(clicked()), this, SLOT(input_functions()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::validators() {
  QDoubleValidator *qdv =
      new QDoubleValidator(-(__DBL_MAX__), __DBL_MAX__, 7, this);
  qdv->setNotation(QDoubleValidator::StandardNotation);
  ui->line_x->setValidator(qdv);
  QDoubleValidator *for_bank = new QDoubleValidator(0, __DBL_MAX__, 7, this);
  for_bank->setNotation(QDoubleValidator::StandardNotation);
  QIntValidator *for_bank_term = new QIntValidator(0, INT_MAX, this);
  ui->sum_of_credit->setValidator(for_bank);
  ui->term_of_credit->setValidator(for_bank_term);
  ui->rate_of_credit->setValidator(for_bank);

  ui->sum_of_deposit->setValidator(for_bank);
  ui->term_of_deposit->setValidator(for_bank_term);
  ui->rate_of_deposit->setValidator(for_bank);
  ui->tax_rate_of_deposit->setValidator(for_bank);
  ui->replenish_of_deposit->setValidator(for_bank);
  ui->withdrawl_of_deposit->setValidator(for_bank);
}

void MainWindow::input() {
  // take value of button
  QPushButton *button = (QPushButton *)sender();

  QString str = "";

  if (numbers.contains(button->text()) && !waiting_symbols) {
    if (ui->label->text() == "0") ui->label->setText("");
    str = ui->label->text() + button->text();
    check_start = false;
    ui->label->setText(str);
  } else if (button->text() == "." && !check_point && !check_start &&
             !symbols.contains(ui->label->text().back()) && !waiting_symbols) {
    str = ui->label->text() + button->text();
    check_point = true;
    ui->label->setText(str);
  } else if (button->text() == "0" && !waiting_symbols &&
             ui->label->text() != "0") {
    if (ui->label->text() != "") {
      if (symbols.contains(ui->label->text().back()) || check_start) {
        str = ui->label->text() + button->text() + ".";
        check_point = true;
      } else
        str = ui->label->text() + button->text();
    } else {
      str = button->text() + ".";
      check_point = true;
    }
    check_start = false;
    ui->label->setText(str);
  }
}

void MainWindow::input_symbols() {
  QString str = "";
  QPushButton *button = (QPushButton *)sender();
  if (symbols.contains(button->text()) && !check_start) {
    if (symbols.contains(ui->label->text().back()) ||
        ui->label->text().back() == '.') {
      str = ui->label->text();
      str.chop(1);
      str += button->text();
    } else
      str = ui->label->text() + button->text();
    waiting_symbols = false;
    check_point = false;
    ui->label->setText(str);
  } else if ((button->text() == "+" || button->text() == "-") && check_start) {
    str = ui->label->text();
    if (str.length() > 0)
      if (str.back() == '+' || str.back() == '-') str.chop(1);
    str = str + button->text();
    ui->label->setText(str);
  } else if (button->text() == "(") {
    if (ui->label->text() == "0") ui->label->setText("");
    if (ui->label->text() != "") {
      if (symbols.contains(ui->label->text().back()) ||
          ui->label->text().back() == '(') {
        str = ui->label->text() + button->text();
        ui->label->setText(str);
        check_start = true;
        open_close_buttons++;
      }
    } else {
      str = button->text();
      ui->label->setText(str);
      check_start = true;
      open_close_buttons++;
    }
  } else if (button->text() == ")" && open_close_buttons > 0) {
    str = ui->label->text();
    if (symbols.contains(str.back()) || str.back() == '.') str.chop(1);
    if (str.back() == '(') str += "0";
    str += button->text();
    ui->label->setText(str);
    waiting_symbols = true;
    check_start = false;
    open_close_buttons--;
  }
}

void MainWindow::input_functions() {
  QString str = "";
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "sin" || button->text() == "cos" ||
      button->text() == "tan" || button->text() == "acos" ||
      button->text() == "asin" || button->text() == "atan" ||
      button->text() == "log" || button->text() == "ln" ||
      button->text() == "sqrt") {
    if (ui->label->text() == "0") ui->label->setText("");
    if (ui->label->text() != "") {
      if (symbols.contains(ui->label->text().back()) || check_start) {
        str = ui->label->text() + button->text() + "(";
        ui->label->setText(str);
        check_start = true;
        open_close_buttons++;
      }
    } else {
      str = button->text() + "(";
      ui->label->setText(str);
      check_start = true;
      open_close_buttons++;
    }
  } else if (button->text() == "x" && !waiting_symbols) {
    if (ui->label->text() == "0") ui->label->setText("");
    if (ui->label->text() != "") {
      if (symbols.contains(ui->label->text().back()) || check_start) {
        str = ui->label->text() + "(" + button->text() + ")";
        ui->label->setText(str);
      }
    } else {
      str = button->text();
      ui->label->setText(str);
    }
    check_start = false;
    waiting_symbols = true;
  }
}

void MainWindow::on_all_clean_button_clicked() {
  check_point = false;
  check_start = true;
  waiting_symbols = false;
  open_close_buttons = 0;
  ui->label->setText("");
  ui->line_x->clear();
}

void MainWindow::on_result_button_clicked() {
  QString line = ui->label->text();
  bool err = false;

  if (line.length() > 0) {
    if (symbols.contains(line.back())) {
      line.chop(1);
    }

    if (line.contains('x')) {
      if (ui->line_x->text().length() > 0) {
        double term = 0;
        term = ui->line_x->text().toDouble();
        line.replace('x', QString::number(term));
        ui->label->setText(line);
      } else {
        QMessageBox::critical(0, "Error in input line",
                              QString("No x value entered"));
        err = true;
      }
    }

    if (open_close_buttons > 0 && !err) {
      QMessageBox::critical(
          0, "Error in input line",
          QString("Not all open parentheses are closed.\nPlease insert the "
                  "missing closing parentheses."));
    } else if (!err) {
      QByteArray array = line.toLatin1();
      char *str = array.data();
      double res = calc(str);
      ui->label->setText(QString::number(res));
      check_point = false;
      waiting_symbols = false;
      open_close_buttons = 0;
    }
  }
}

void MainWindow::on_graphics_button_clicked() {
  QString str = ui->label->text();
  double res = 0;
  QSplineSeries *series = new QSplineSeries(this);
  if (open_close_buttons > 0) {
    QMessageBox::warning(
        0, "Error in input line",
        QString("Not all open parentheses are closed.\nPlease insert the "
                "missing closing parentheses."));
  } else if (str.contains("x")) {
    for (int i = ui->spinBox_xmin->text().toInt();
         i <= ui->spinBox_xmax->text().toInt(); i++) {
      QString copy_str = str;
      copy_str.replace('x', QString::number(i));
      QByteArray array = copy_str.toLatin1();
      char *char_str = array.data();
      res = calc(char_str);
      if (res >= ui->spinBox_ymin->text().toDouble() &&
          res <= ui->spinBox_ymax->text().toDouble())
        series->append(i, res);
    }
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setGeometry(-40, -40, 380, 380);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(chart);
    ui->graphicsView->setSceneRect(0, 0, 300, 300);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    ui->tabWidget->setCurrentIndex(1);
  }
}

void MainWindow::on_calculate_credit_button_clicked() {
  double overpayment = 0;
  double total_payout = 0;

  double total_amount = ui->sum_of_credit->text().toDouble();
  double term = ui->term_of_credit->text().toDouble();
  double rate = ui->rate_of_credit->text().toDouble();

  ui->monpayment_box->clear();

  if (ui->type_of_credit->currentText() == "Аннуитетный") {
    double month_payment = annuity(total_amount, rate, term);
    total_payout = month_payment * term;
    overpayment = total_payout - total_amount;

    ui->overpayment_credit->setText(QString::number(overpayment, 'f', 2));
    ui->total_payout_credit->setText(QString::number(total_payout, 'f', 2));

    for (int i = 0; i < term; i++) {
      ui->monpayment_box->addItem(QString::number(i + 1) + " мес. = " +
                                  QString::number(month_payment, 'f', 2));
    }

  } else {
    double *month_payment = (double *)malloc(term * sizeof(double));

    overpayment = differentiated(total_amount, rate, term, month_payment);
    total_payout = total_amount + overpayment;

    ui->overpayment_credit->setText(QString::number(overpayment, 'f', 2));
    ui->total_payout_credit->setText(QString::number(total_payout, 'f', 2));
    for (int i = 0; i < term; i++) {
      ui->monpayment_box->addItem(QString::number(i + 1) + " мес. = " +
                                  QString::number(month_payment[i], 'f', 2));
    }
    free(month_payment);
  }
}

void MainWindow::on_calculate_deposit_clicked() {
  double amount = ui->sum_of_deposit->text().toDouble();    // Сумма
  double term = ui->term_of_deposit->text().toDouble();     // Срок
  double rate = ui->rate_of_deposit->text().toDouble();     // Ставка
  double tax = ui->tax_rate_of_deposit->text().toDouble();  // Налог
  int interest = ui->accured_interest_box->currentIndex();  // Куда начислять
  int interest_term = ui->accur_inter_term_box_2->currentIndex();  // Как часто

  double replenish = ui->replenish_of_deposit->text().toDouble();
  double withdrawl = ui->withdrawl_of_deposit->text().toDouble();

  double total_payout = deposit(amount, term, rate, replenish - withdrawl,
                                interest, interest_term);
  double total_interest = total_payout - amount;
  double total_tax = total_interest * (tax / 100);

  ui->total_interest->setText(QString::number(total_interest, 'f', 2));
  ui->total_payout->setText(QString::number(total_payout - total_tax, 'f', 2));
  ui->total_tax->setText(QString::number(total_tax, 'f', 2));
}
