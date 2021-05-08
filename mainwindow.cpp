#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QChar"
#include "QVector"
#include <map>
#include <type_traits>
std::map<QChar, int> PriorityOrder{ {'(', 1}, {')', 1},
                                         {'/', 2}, {'*', 2},
                                         {'%', 2}, {'+', 3},
                                         {'-', 3}
                                       };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //numbers
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(number_button_clicked()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(number_button_clicked()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(number_button_clicked()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(number_button_clicked()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(number_button_clicked()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(number_button_clicked()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(number_button_clicked()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(number_button_clicked()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(number_button_clicked()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(number_button_clicked()));

    //operators
    connect(ui->pushButton_plus,SIGNAL(released()),this,SLOT(operators_clicked()));
    connect(ui->pushButton_minus,SIGNAL(released()),this,SLOT(operators_clicked()));
    connect(ui->pushButton_multiply,SIGNAL(released()),this,SLOT(operators_clicked()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(operators_clicked()));
    connect(ui->pushButton_per,SIGNAL(released()),this,SLOT(operators_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::number_button_clicked(){
    QPushButton *button=(QPushButton*)sender();
    QString str;
    str=ui->label->text()+button->text();
    ui->label->setText(str);
}

void MainWindow::on_pushButton_Del_clicked()
{
    QString str=ui->label->text();
    str.resize(str.size()-1);
    ui->label->setText(str);
}

void MainWindow::on_pushButton_AC_clicked()
{
    ui->label->setText("");
}

void MainWindow::on_pushButton_dec_clicked()
{
    ui->label->setText(ui->label->text()+".");
}

void MainWindow::operators_clicked()
{
    QPushButton *button=(QPushButton*)sender();
    QString str;
    str=ui->label->text()+button->text();
    ui->label->setText(str);
}

bool checkParantheses(QString& str){
      QStringList parantheses;
      for(int i=0; i<str.length(); i++)
      {
          if( str[i] == '(' ) parantheses.append(str[i]);
          if ( str[i] == ')' && parantheses.size()!=0 ) parantheses.pop_back();
          else return false;
      }
    if(parantheses.size()==0) return true;
    else return false;
}

void changeOrder(QStringList& precedence, QStringList& postfix, QChar ch)
{
    for(int i=precedence.size()-1; i>=0;i--)
    {
        if(PriorityOrder[precedence[i][0]] <= PriorityOrder[ch]){
            postfix.append(precedence[i]);
            precedence.pop_back();
        }
        else if(ch == ')')
        {
            do
            {
                if( precedence[i][0] != '(' || precedence[i][0]!=')') continue;
                postfix.append(precedence[i]);
                precedence.pop_back();
                i--;
            }while(precedence[i][0]!= '(');
        }
        else{
                break;
        }
    }
    precedence.push_back(ch);
}

QStringList parseElements(QString &str)
{
    QStringList precedence;
    QStringList postfix;

    QString operand;
    std::pair<QChar, int> operators;
    for(int i=0; i<str.size(); i++)
    {
        auto temp = PriorityOrder.find(str[i]);
        operators = (temp != PriorityOrder.end()) ?
                    std::make_pair(temp->first,temp->second):std::make_pair('`',0);
        if( operators.first=='`')
        {
            operand += str[i];
        }
        else
        {
            postfix.append(operand);
            changeOrder(precedence, postfix, operators.first);
            operand = "";
        }
    }

    if (operand.size()!=0){
       postfix.append(operand);
    }

    int i;
    while(precedence.size()!=0){
        i = precedence.size() - 1;
        if(precedence[i][0] != '(' || precedence[i][0] != ')' )
            postfix.append(precedence[i]);
        precedence.pop_back();
    }
    return postfix;
}

void getOperands(QStringList& str, int i, double(&arr)[2])
{
    arr[0] = str[i-2].toDouble();
    arr[1] = str[i-1].toDouble();
    str.erase(str.begin()+i-1,str.begin()+i+1);
}

QString calculate(QStringList& str)
{
    QChar op;
    int i = 0;
    double operands[2];
    double answer;
    while( str.size()!=1 ){
        if(str[i].size() == 1 && PriorityOrder.find(str[i][0]) != PriorityOrder.end() )
        {
            op = str[i][0];
            getOperands(str, i, operands);
            if (op == '/'){
               answer = operands[0] / operands[1];
            }
            else if (op == '*'){
               answer = operands[0] * operands[1];
            }
            else if (op == '%'){
               answer = (operands[0] / operands[1]) * 100;
            }
            else if (op == '+'){
               answer = operands[0] + operands[1];
            }
            else if (op == '-'){
               answer = operands[0] - operands[1];
            }
            i = i - 2;
            str[i] = QString::number(answer,'f',8);
        }
        i++ ;
    }
    return str[0];
}

void MainWindow::on_pushButton_calc_clicked()
{
    QString str=ui->label->text();
    checkParantheses(str);
    QStringList postfix = parseElements(str);
    QString result = calculate(postfix);
    ui->label->setText(result);
}
