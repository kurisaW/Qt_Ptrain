#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QHostAddress> //client

#include <QSqlQuery> //SQL
#include <QVariant>
#include <QSqlRecord>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //client
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any,45);
    connect(server,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
    //

    //SQL
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("hxx");
    db.setDatabaseName("hxx.db");
    db.open();

    QSqlQuery query;//QSqlQuery对象必须在打开数据库之后创建，所以QSqlQuery对象一般都定义成局部对象
    query.exec("create table if not exists user(\
               userid integer primary key autoincrement,\
               password char(20),\
               nickname char(20),\
               headid integer\
               )");
    query.exec("insert into user values(100000,'abc123','admin',0)");
    //

}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

//Client
void MainWindow::onNewConnection()
{
    client = server->nextPendingConnection();//获得与客户通信的socket对象
    connect(client,SIGNAL(disconnected()),this,SLOT(onDisConnection()));
    connect(client,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

void MainWindow::onDisConnection()
{
    ui->label_info->setText("断开连接");
}

void MainWindow::onReadyRead()
{
    QByteArray bdata = client->readAll();
    QString data = QString::fromLocal8Bit(bdata);
    ui->label_info->setText(data);
}
//


//SQL
void MainWindow::on_pushButton_insert_clicked()
{
    QString nickName = ui->lineEdit_nickname->text();
    QString passwd = ui->lineEdit_passwd->text();
    int headId = ui->lineEdit_headid->text().toInt();//.toInt将QString对象转换成int
    QSqlQuery query;
    query.prepare("insert into user(nickname, password, headid) values(?,?,?)");
    query.bindValue(0, nickName);
    query.bindValue(1, passwd);
    query.bindValue(2, headId);
    query.exec();

    //此处加入返回ID的效果
    query.exec("SELECT LAST_INSERT_ROWID()");//查询插入的最后一条数据的id，就是刚刚注册的账号
    QString id;
    if(query.next())
    {
        id = query.record().value(0).toString();//value(0)因为我们不是按照字段查找，0代表record对象中的第一个数据
    }
    QMessageBox::information(this, "账号", id);
}
//

void MainWindow::on_pushButton_query_clicked()//查询所有数据库中的用户信息
{
    QSqlQuery query;
    query.exec("select * from user");
    //查询结果在QSqlQuery对象中，被存在一个线性结构（链表，带有空头的链表）中。
    while(query.next())//移动到链表的下一个节点，如果移动成功返回true
    {
        QSqlRecord record = query.record();//获得节点中的数据，record对象中包含了一行中所有字段的数据
        QVariant userId = record.value("userid");//获得userid字段的数据，QVariant是QT给我们提供的泛型，它可以存放任何类型数据，也可以转换成任何类型数据
        QString userIdStr = userId.toString();//将QVariant对象转换成QString对象

        QString name = query.record().value("nickname").toString();

        int headId = query.record().value("headid").toInt();

        //QString格式化字符串的方式 %1 %2 %3代表占位符，要使用实际的数据替换他们
        QString item = QString("昵称:%1 账号:%2 头像:%3").arg(name).arg(userIdStr).arg(headId);
        ui->listWidget_users->addItem(item);
    }
}

void MainWindow::on_pushButton_login_clicked()//有条件查询
{
    QString userId = ui->lineEdit_loginid->text();
    QString passwd = ui->lineEdit_loginpw->text();

    QSqlQuery query;
    query.prepare("select * from user where userid = ? and password = ?");
    query.bindValue(0, userId);
    query.bindValue(1, passwd);
    query.exec();
    /*bool exist = false;
    //如果账号密码查询失败，则不会有结果，所以下面的循环不会执行，所以循环下面exist值是false
    while(query.next())
    {
        e.nickname = query.record().value("nickname").toString();
        exist = true;
    }
    cout<<exist;*/
    if(query.next())
    {
        //登录成功
        QMessageBox::information(this,"提示","登录成功");
    }
    else
    {
        //登录失败
        QMessageBox::information(this,"提示","登录失败");
    }
}
