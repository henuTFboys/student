#include "addstugrades.h"
#include "ui_addstugrades.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
AddStuGrades::AddStuGrades(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStuGrades)
{
    ui->setupUi(this);
    initScreen();

}

AddStuGrades::~AddStuGrades()
{
    delete ui;
}

void AddStuGrades::initScreen()
{
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setFixedSize(500,333);
    setWindowTitle("添加学生成绩");

}

void AddStuGrades::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background4.jpg"));
}

bool AddStuGrades::checkStuId(QString stid)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(dbHostName);       //选择本地主机
    db.setDatabaseName("custom2.db");                            //设置数据源名称
    db.setUserName(dbusername);                         //登录用户
    db.setPassword(dbpassword);                         //密码
    bool isOpen=db.open();
    if(isOpen)
    {
        QSqlQuery query(db);
        query.exec("select COUNT(stid) from studentpasstable where stid='"+stid+"'");
        query.next();
        int num;

        num=query.value(0).toInt();
        qDebug()<<"num="<<num;
        if(num)
            return true;
        else false;
    }
}

void AddStuGrades::setGrades()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(dbHostName);       //选择本地主机
    db.setDatabaseName("custom2.db");                            //设置数据源名称
    db.setUserName(dbusername);                         //登录用户
    db.setPassword(dbpassword);                         //密码
    db.open();
    QSqlQuery query(db);
    query.exec("insert into gradetable(stid,grademath,gradeen,gradec) values ('"+stid+"','"+math+"','"+english+"','"+cpp+"')");
    query.next();

    QMessageBox::information(this,"提示","添加成绩成功");
}

void AddStuGrades::on_pushButton_back_clicked()
{
    emit this->backToAdminScreen();
}

void AddStuGrades::on_lineEdit_stid_editingFinished()
{
    stid=removeSpace(ui->lineEdit_stid->text());
    if(!checkStuId(stid) || !isProperId(stid))
    {
        QMessageBox::critical(this,"警告","此账号输入错误！");
        qDebug()<<"账号有问题";
        ui->lineEdit_stid->setText("");
    }
}

void AddStuGrades::on_pushButton_submit_clicked()
{
    english=removeSpace(ui->lineEdit_english->text());
    math=removeSpace(ui->lineEdit_math->text());
    cpp=removeSpace(ui->lineEdit_c->text());
    setGrades();

}
