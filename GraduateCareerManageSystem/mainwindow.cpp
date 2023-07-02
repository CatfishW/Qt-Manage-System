#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QString QSS = "QHeaderView::section,QTableCornerButton:section{ \
                                                        padding:3px; margin:0px; color:#DCDCDC;  border:1px solid #242424; \
                                                border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
                                            background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252); }";
//    db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("nj-cynosdbmysql-grp-mu5omonl.sql.tencentcdb.com");
//    db.setPort(27491);
//    db.setDatabaseName("qt");
//    db.setUserName("root");
//    db.setPassword("Wyl132161366");

    student_count = 0;
    post_graduate_count = 0;
    graduate_count = 0;
    ui->setupUi(this);
    QSqlQuery query_sql("SELECT company_name, recruitment_count, education_requirement, publisher, company_type,student_name,student_id,is_postgraduate_study,is_employed,major FROM company_student_table");
    int row_1 = 0;
    int row_2 = 0;
    while (query_sql.next()) {
        qDebug()<<"query finished";
        QString company_name = query_sql.value(0).toString();
        int recruitment_count = query_sql.value(1).toInt();
        QString education_requirement = query_sql.value(2).toString();
        QString publisher = query_sql.value(3).toString();
        QString company_type = query_sql.value(4).toString();
        QString student_name = query_sql.value(5).toString();
        QString student_id = query_sql.value(6).toString();
        QString is_postgraduate_study = query_sql.value(7).toString();
        QString is_employed = query_sql.value(8).toString();
        QString major = query_sql.value(9).toString();
        // 将数据插入到TableWidget的对应单元格
        if (company_name !=""){
        ui->tableWidget->setItem(row_1, 0, new QTableWidgetItem(company_name));
        ui->tableWidget->setItem(row_1, 1, new QTableWidgetItem(QString::number(recruitment_count)));
        ui->tableWidget->setItem(row_1, 2, new QTableWidgetItem(education_requirement));
        ui->tableWidget->setItem(row_1, 3, new QTableWidgetItem(publisher));
        ui->tableWidget->setItem(row_1, 4, new QTableWidgetItem(company_type));
        row_1++;
        }
        if (student_name !=""){
        ui->tableWidget_2->setItem(row_2,0,new QTableWidgetItem(student_name));
        ui->tableWidget_2->setItem(row_2,1,new QTableWidgetItem(student_id));
        ui->tableWidget_2->setItem(row_2,2,new QTableWidgetItem(is_postgraduate_study));
        ui->tableWidget_2->setItem(row_2,3,new QTableWidgetItem(is_employed));
        ui->tableWidget_2->setItem(row_2,4,new QTableWidgetItem(major));
        row_2++;
        }

    }
    ui->tableWidget->horizontalHeader()->setStyleSheet(QSS);
    ui->tableWidget_2->horizontalHeader()->setStyleSheet(QSS);
    ui->tableWidget->verticalHeader()->setStyleSheet(QSS);
    ui->tableWidget_2->verticalHeader()->setStyleSheet(QSS);
    info_win = new addinfo();
    query_win1 = new query();
    query_win2 = new query();
    delete_win = new delete_dia();
    connect(info_win,&addinfo::datasignal,this,&MainWindow::AddData);
    connect(delete_win,&delete_dia::deletedata,this,&MainWindow::deletedata_receive);
    connect(this,&MainWindow::querydata,query_win1,&query::querydata_receive);
    connect(this,&MainWindow::querydata,query_win2,&query::querydata_receive);
    // 创建定时器用于定期刷新图表
    QTimer *timer = new QTimer(this);
    if(timer_stop){
    timer->start(50);  // 每50ms刷新一次
    connect(timer, &QTimer::timeout, this, &MainWindow::updatechart);
    }
    series_postgraduate = new QLineSeries();
    series_student = new QLineSeries();
    series_postgraduate->append(0,0);
    series_student->append(0,0);
    //connect(info, &addinfo::hideWindow, this, &MainWindow::onChildWindowHidden);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget_2->setColumnCount(5);
    QStringList header,header2;
    header <<"企业名" << "招聘人数" << "学历要求" << "发布人"<<"企业类型";
    header2 <<"学生姓名" << "学号" << "是否考研" <<"是否就业" <<"专业";
    QHeaderView *header_first = ui->tableWidget->verticalHeader();
    header_first->setHidden(true);
    QHeaderView *header_first_2 = ui->tableWidget_2->verticalHeader();
    header_first_2->setHidden(true);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->setHorizontalHeaderLabels(header2);
    //设置表头显示模式,这里设置的是拉伸模式
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //表格数据初始化
    int i;
    for(i = 0;i<ui->tableWidget->rowCount();i++){
        QTableWidgetItem *null_str1=new QTableWidgetItem();
        null_str1->setText("");
        QTableWidgetItem *null_str2=new QTableWidgetItem();
        null_str2->setText("");
        QTableWidgetItem *null_str3=new QTableWidgetItem();
        null_str3->setText("");
        QTableWidgetItem *null_str4=new QTableWidgetItem();
        null_str4->setText("");
        QTableWidgetItem *null_str5=new QTableWidgetItem();
        null_str5->setText("");
        if(ui->tableWidget->item(i,0)==nullptr)
        ui->tableWidget->setItem(i,0,null_str1);
        if(ui->tableWidget->item(i,1)==nullptr)
        ui->tableWidget->setItem(i,1,null_str2);
        if(ui->tableWidget->item(i,2)==nullptr)
        ui->tableWidget->setItem(i,2,null_str3);
        if(ui->tableWidget->item(i,3)==nullptr)
        ui->tableWidget->setItem(i,3,null_str4);
        if(ui->tableWidget->item(i,4)==nullptr)
        ui->tableWidget->setItem(i,4,null_str5);
        delete null_str1;
        delete null_str2;
        delete null_str3;
        delete null_str4;
        delete null_str5;
    }
    int j;
    for(j = 0;j<ui->tableWidget_2->rowCount();j++){
        QTableWidgetItem *null_str1=new QTableWidgetItem();
        null_str1->setText("");
        QTableWidgetItem *null_str2=new QTableWidgetItem();
        null_str2->setText("");
        QTableWidgetItem *null_str3=new QTableWidgetItem();
        null_str3->setText("");
        QTableWidgetItem *null_str4=new QTableWidgetItem();
        null_str4->setText("");
        QTableWidgetItem *null_str5=new QTableWidgetItem();
        null_str5->setText("");
        if(ui->tableWidget_2->item(j,0)==nullptr)
        ui->tableWidget_2->setItem(j,0,null_str1);
        else if(ui->tableWidget_2->item(j,1)==nullptr)
        ui->tableWidget_2->setItem(j,1,null_str2);
        else if(ui->tableWidget_2->item(j,2)==nullptr)
        ui->tableWidget_2->setItem(j,2,null_str3);
        else if(ui->tableWidget_2->item(j,3)==nullptr)
        ui->tableWidget_2->setItem(j,3,null_str4);
        else if(ui->tableWidget_2->item(j,4)==nullptr)
        ui->tableWidget_2->setItem(j,4,null_str5);
        else{
        student_count++;
        if(ui->tableWidget_2->item(j,2)->text()=="是"){
            post_graduate_count++;
            series_postgraduate->append(student_count,post_graduate_count);
        }
        if(ui->tableWidget_2->item(j,3)->text()=="是"){
            graduate_count++;
            series_student->append(student_count,graduate_count);
        }
        else{
            series_postgraduate->append(student_count,post_graduate_count);
            series_student->append(student_count,graduate_count);
        }

        }
        delete null_str1;
        delete null_str2;
        delete null_str3;
        delete null_str4;
        delete null_str5;
    }
//    int i,j;
//    for (i = 0; i < ui->tableWidget->rowCount()-1; i++) {
//        ui->tableWidget->item(i, 0)->setBackground(brush);  // 设置第一列的背景颜色
//    }
//    for (j = 0; j < ui->tableWidget->columnCount(); j++) {
//        ui->tableWidget->item(0, j)->setBackground(brush);  // 设置第一行的背景颜色
//    }
//    for (i = 0; i < ui->tableWidget->rowCount(); i++) {
//        ui->tableWidget_2->item(i, 0)->setBackground(brush);  // 设置第一列的背景颜色
//    }
//    for (j = 0; j < ui->tableWidget->columnCount(); j++) {
//        ui->tableWidget_2->item(0, j)->setBackground(brush);  // 设置第一行的背景颜色
//    }
    this->setWindowFlags(Qt::FramelessWindowHint);
    //数据分析


//    series_postgraduate->append(0, 6);
//    series_postgraduate->append(2, 4);
//    series_postgraduate->append(3, 8);
//    series_postgraduate->append(7, 4);
//    series_postgraduate->append(10, 5);
//    series_postgraduate->append(13, 5);
//    series_postgraduate->append(20, 5);
//    series_postgraduate->append(30, 5);
//    series_postgraduate->append(23, 5);
//    series_postgraduate->append(5, 5);

//    series_student->append(0, 6);
//    series_student->append(2, 4);
//    series_student->append(3, 8);
//    series_student->append(7, 4);
//    series_student->append(10, 5);
//    series_student->append(5, 8);
//    series_student->append(7, 40);
//    series_student->append(10, 5);
//    series_student->append(40, 6);
//    series_student->append(15, 4);
//    series_student->append(10, 7);

    QChart *chart_postgraduate = new QChart();
    QPen gridPen(Qt::blue);  // 表格线的颜色和样式
    gridPen.setWidth(11);    // 初始表格线的宽度
    chart_postgraduate->addSeries(series_postgraduate);
    chart_postgraduate->setTitle("考研数据可视化");
    axisX_postgraduate = new QValueAxis();
    axisX_postgraduate->setRange(0, 4);
    axisX_postgraduate->setGridLinePen(gridPen);
    axisX_postgraduate->setTitleText("学生人数");
    axisX_postgraduate->setLabelFormat("%d");
    axisY_postgraduate = new QValueAxis();
    axisY_postgraduate->setRange(0, 4);
    axisY_postgraduate->setGridLinePen(gridPen);

    axisY_postgraduate->setTitleText("考研人数");
    axisY_postgraduate->setLabelFormat("%d");
    chart_postgraduate->addAxis(axisX_postgraduate, Qt::AlignBottom);
    chart_postgraduate->addAxis(axisY_postgraduate, Qt::AlignLeft);
    series_postgraduate->attachAxis(axisX_postgraduate);
    series_postgraduate->attachAxis(axisY_postgraduate);


    QChart *chart_student = new QChart();
    chart_student->addSeries(series_student);
    chart_student->setTitle("就业数据可视化");

    axisX_student = new QValueAxis();
    axisX_student->setRange(0, 4);
    axisX_student->setGridLinePen(gridPen);
    axisX_student->setTitleText("学生人数");
    axisX_student->setLabelFormat("%d");
    axisY_student = new QValueAxis();
    axisY_student->setRange(0, 4);
    axisY_student->setTitleText("就业人数");
    axisY_student->setGridLinePen(gridPen);
    axisY_student->setLabelFormat("%d");
    chart_student->addAxis(axisX_student, Qt::AlignBottom);
    chart_student->addAxis(axisY_student, Qt::AlignLeft);
    series_student->attachAxis(axisX_student);
    series_student->attachAxis(axisY_student);

    chart_postgraduate->setTheme(QChart::ChartThemeDark);
    chart_student->setTheme(QChart::ChartThemeDark);
    chart_postgraduate->layout()->setContentsMargins(0,0,0,0);
    chart_student->layout()->setContentsMargins(0,0,0,0);
    QChartView *chartView_company = new QChartView(chart_postgraduate);
    QChartView *chartView_student = new QChartView(chart_student);
    chartView_company->setRenderHint(QPainter::Antialiasing);
    chartView_student->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_6->addWidget(chartView_company);
    ui->horizontalLayout_6->addWidget(chartView_student);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updatechart(){
    int x = student_count;
    int y1 = post_graduate_count;
    int y2 = graduate_count;
    int cur_max_x = axisX_postgraduate->max();
    int cur_max_y = axisY_postgraduate->max();
    int cur_max_x_2 = axisX_student->max();
    int cur_max_y_2 = axisY_student->max();
    if(cur_max_x-x<0)
        axisX_postgraduate->setRange(0,cur_max_x+1);
    if(cur_max_y-y1<0)
        axisY_postgraduate->setRange(0,cur_max_y+1);
    if(cur_max_x_2-x<0)
        axisX_student->setRange(0,cur_max_x_2+1);
    if(cur_max_y_2-x<0)
        axisY_student->setRange(0,cur_max_y_2+1);
//    qDebug()<<"x: "<<x<<" "<<"y1: "<<y1<<" "<<"y2: "<<y2;
    series_postgraduate->append(x, y1);
    series_student->append(x, y2);

}
void MainWindow::AddData(QString data1,QString data2,QString data3,QString data4,QString data5,QString type)
{
    timer_stop =true;
    QTableWidgetItem *d1=new QTableWidgetItem();//创建一个Item
    d1->setText(data1);//设置内容
    QTableWidgetItem *d2=new QTableWidgetItem();//创建一个Item
    d2->setText(data2);//设置内容
    QTableWidgetItem *d3=new QTableWidgetItem();//创建一个Item
    d3->setText(data3);//设置内容
    QTableWidgetItem *d4=new QTableWidgetItem();//创建一个Item
    d4->setText(data4);//设置内容
    QTableWidgetItem *d5=new QTableWidgetItem();//创建一个Item
    d5->setText(data5);//设置内容
    delete d1;
    delete d2;
    delete d3;
    delete d4;
    delete d5;
//    QString data1 = ui->company_or_student_name->toPlainText();
//    QString data2 = ui->companytype_or_major->toPlainText();
//    QString data3 = ui->admitreq_or_exam->toPlainText();
//    QString data4 = ui->hirenum_or_stuid->toPlainText();
//    QString data5 = ui->publisher_or_ifjob->toPlainText();
    for(int i = 0;i<ui->tableWidget->rowCount();i++){
    QString s1 = ui->tableWidget->item(i,0)->text();
    QString s2 = ui->tableWidget_2->item(i,0)->text();
    if (s1 == "" and type == "company"){
        ui->tableWidget->setItem(i,0,d1);
        ui->tableWidget->setItem(i,1,d4);
        ui->tableWidget->setItem(i,2,d3);
        ui->tableWidget->setItem(i,3,d5);
        ui->tableWidget->setItem(i,4,d2);
        QString insertQuery = QString("INSERT INTO company_student_table (company_name, recruitment_count, education_requirement, publisher, company_type)"
                                      "VALUES ('%1', '%2', '%3', '%4', '%5')")
                                      .arg(data1).arg(data4).arg(data3).arg(data5).arg(data2);
        QSqlQuery query;
        bool query_check = query.exec(insertQuery);
        if(!query_check)
            QMessageBox::warning(this,"警告","数据上传数据库失败！");

        break;}
    else if (s2 == "" and type == "student"){
        ui->tableWidget_2->setItem(i,0,d1);
        ui->tableWidget_2->setItem(i,1,d4);
        ui->tableWidget_2->setItem(i,2,d3);
        ui->tableWidget_2->setItem(i,3,d5);
        ui->tableWidget_2->setItem(i,4,d2);
        QString insertQuery = QString("INSERT INTO company_student_table (student_name, student_id, is_postgraduate_study, is_employed, major)"
                                      "VALUES ('%1', '%2', '%3', '%4', '%5')")
                                      .arg(data1).arg(data4).arg(data3).arg(data5).arg(data2);
        QSqlQuery query;
        bool query_check = query.exec(insertQuery);
        if(!query_check)
            QMessageBox::warning(this,"警告","数据上传数据库失败！");
        student_count++;
        if(data3 == "是")post_graduate_count++;
        if(data5 == "是")graduate_count++;
        break;}
    }


}

void MainWindow::on_close_btn_clicked()
{
    this->close();
}

void MainWindow::on_maxmize_btn_clicked()
{
    if (isFullScreen()) {
            showNormal();
        } else {
            showFullScreen();
        }
}


void MainWindow::on_minimize_btn_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}
//拖拽操作
void MainWindow::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

void MainWindow::mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPos);
            event->accept();
        }
    }

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = QPoint();
            event->accept();
        }
    }

void MainWindow::on_menu_btn_clicked()
{
   qint64 standard = 48, maxExtend = 180;
   qint64 width = ui->left_menu_bar_frame->width();
   qint64 widthExtended = (width==48)?maxExtend:standard;
   QPropertyAnimation *animation = new QPropertyAnimation(ui->left_menu_bar_frame,"minimumWidth");
   animation->setDuration(1000);
   animation->setStartValue(width);
   animation->setEndValue(widthExtended);
   animation->setEasingCurve(QEasingCurve::InOutQuint);
   animation->start();
   if(animation->Stopped){
       delete animation;
   }
}
void MainWindow::on_add_btn_clicked()
{
    info_win->show();
    //this->hide();
}




void MainWindow::on_query_btn_company_clicked()
{
    QString company_name = ui->textEdit->toPlainText();
    QString publisher = ui->textEdit_2->toPlainText();
    QString type = "company";
    if (company_name == "" or publisher == "")
        QMessageBox::warning(this,"警告","查询内容不能为空");
    else{
        for(int row=0;row<ui->tableWidget->rowCount();row++)
            if(ui->tableWidget->item(row,0)->text() == company_name and ui->tableWidget->item(row,3)->text() == publisher){
                QString hire_num = ui->tableWidget->item(row,1)->text();
                QString req = ui->tableWidget->item(row,2)->text();
                QString company_type = ui->tableWidget->item(row,4)->text();
                emit querydata(company_name,publisher,hire_num,req,company_type,type);
                query_win1->show();
                break;
            }
            else if (row == ui->tableWidget->rowCount()-1){
                QMessageBox::information(this," 提示","未查询到相关企业信息");
                break;
            }
    }
}



void MainWindow::on_query_btn_student_clicked()
{
    QString student_name = ui->textEdit_3->toPlainText();
    QString student_id = ui->textEdit_4->toPlainText();
    QString type = "student";
    if (student_name == "" or student_id == "")
        QMessageBox::warning(this,"警告","查询内容不能为空");
    else{
        for(int row=0;row<ui->tableWidget_2->rowCount();row++)
            if(ui->tableWidget_2->item(row,0)->text() == student_name and ui->tableWidget_2->item(row,1)->text() == student_id){
                QString data2 = ui->tableWidget_2->item(row,2)->text();
                QString data3 = ui->tableWidget_2->item(row,3)->text();
                QString data4 = ui->tableWidget_2->item(row,4)->text();
                emit querydata(student_name,student_id,data2,data3,data4,type);
                query_win2->show();
                break;
            }
            else if (row == ui->tableWidget_2->rowCount()-1){
                QMessageBox::information(this," 提示","未查询到相关学生信息");
                break;
            }
    }
}



void MainWindow::on_delete_file_btn_clicked()
{
    delete_win->show();
}
void MainWindow::deletedata_receive(QString data1,QString data2)
{
    bool check = false;
    if(data1 == "" and data2=="")
        return;
    else
    {
        for(int row=0;row<ui->tableWidget_2->rowCount();row++){
            //公司名与学生ID
            if(ui->tableWidget->item(row,0)->text() == data1 and ui->tableWidget_2->item(row,1)->text() == data2 and data1!="" and data2!=""){
                student_count--;
                if(ui->tableWidget_2->item(row,2)->text() == "是"){post_graduate_count--;series_postgraduate->remove(series_postgraduate->count()-1);series_postgraduate->clear();}
                if(ui->tableWidget_2->item(row,3)->text() == "是"){graduate_count--;series_student->remove(series_student->count()-1);series_student->clear();}
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(""));
                ui->tableWidget->setItem(row,1,new QTableWidgetItem(""));
                ui->tableWidget->setItem(row,2,new QTableWidgetItem(""));
                ui->tableWidget->setItem(row,3,new QTableWidgetItem(""));
                ui->tableWidget->setItem(row,4,new QTableWidgetItem(""));
                ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(""));
                ui->tableWidget_2->setItem(row,1,new QTableWidgetItem(""));
                ui->tableWidget_2->setItem(row,2,new QTableWidgetItem(""));
                ui->tableWidget_2->setItem(row,3,new QTableWidgetItem(""));
                ui->tableWidget_2->setItem(row,4,new QTableWidgetItem(""));
                QString deleteQuery3 = QString("DELETE FROM company_student_table WHERE company_name = '%1'").arg(data1);
                QSqlQuery query_sql;
                if (!query_sql.exec(deleteQuery3))
                    QMessageBox::warning(this,"失败","企业信息删除失败");
                QString deleteQuery4 = QString("DELETE FROM company_student_table WHERE student_id = '%1'").arg(data2);
                if (!query_sql.exec(deleteQuery4))
                    QMessageBox::warning(this,"失败","学生信息删除失败");
                check = true;
                break;

            }
            if(ui->tableWidget->item(row,0)->text() == data1 and data1!=""){
                student_count--;
                if(ui->tableWidget_2->item(row,2)->text() == "是"){post_graduate_count--;series_postgraduate->remove(series_postgraduate->count()-1);series_postgraduate->clear();}
                if(ui->tableWidget_2->item(row,3)->text() == "是"){graduate_count--;series_student->remove(series_student->count()-1);series_student->clear();}
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(""));
                ui->tableWidget->setItem(row,1,new QTableWidgetItem(""));
                ui->tableWidget->setItem(row,2,new QTableWidgetItem(""));
                ui->tableWidget->setItem(row,3,new QTableWidgetItem(""));
                ui->tableWidget->setItem(row,4,new QTableWidgetItem(""));
                //qDebug()<<data1;
                QString deleteQuery = QString("DELETE FROM company_student_table WHERE company_name = '%1'").arg(data1);
                QSqlQuery query_sql;
                bool query_check = query_sql.exec(deleteQuery);
                if(!query_check)
                QMessageBox::warning(this,"失败","企业信息删除失败");
                check = true;
                break;
            }
            if(ui->tableWidget_2->item(row,1)->text() == data2 and data2!=""){
                student_count--;
                if(ui->tableWidget_2->item(row,2)->text() == "是"){post_graduate_count--;series_postgraduate->remove(series_postgraduate->count()-1);series_postgraduate->clear();}
                if(ui->tableWidget_2->item(row,3)->text() == "是"){graduate_count--;series_student->remove(series_student->count()-1);series_student->clear();}
                ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(""));
                ui->tableWidget_2->setItem(row,1,new QTableWidgetItem(""));
                ui->tableWidget_2->setItem(row,2,new QTableWidgetItem(""));
                ui->tableWidget_2->setItem(row,3,new QTableWidgetItem(""));
                ui->tableWidget_2->setItem(row,4,new QTableWidgetItem(""));
                //qDebug()<<data2;
                QString deleteQuery2 = QString("DELETE FROM company_student_table WHERE student_id = '%1'").arg(data2);
                QSqlQuery query_sql;
                if (!query_sql.exec(deleteQuery2))
                    QMessageBox::warning(this,"失败","学生信息删除失败");
                check = true;
                break;
            }

            else if (row == ui->tableWidget_2->rowCount()-1){
                QMessageBox::information(this,"失败","相关信息不存在，无法删除");
                return;
            }
        }
    }
    if(check)QMessageBox::information(this,"提示","信息删除成功！");
}

void MainWindow::datapredict()
{
//    predchart = new PredictedChart();
//    predchart->show();
    double* x = new double[10];
    double* y = new double[10];
    int m = student_count;
    for(int i = 0;i<m;i++){
        QPointF point = series_postgraduate->at(i);
        x[i] = point.x();
    }
    for(int i = 0;i<m;i++){
        QPointF point = series_postgraduate->at(i);
        y[i] = point.y();
    }
    double learningrate = 0.01;int iter = 1000;
    LR = new LinearRegression(x,y,m);
    LR->train(learningrate,iter);
    double prediction;
    int *value_to_be_predicted = new int[50];
    for(int i = 0;i<50;i++){
        value_to_be_predicted[i] = x[m-1]+i+1;
        prediction = LR->predict(value_to_be_predicted[i]);
        qDebug()<<prediction<<endl;
    }
}

void MainWindow::on_data_btn_clicked()
{
    datapredict();
}

