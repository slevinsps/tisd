#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"

#include "QStandardItemModel"
#include "QStandardItem"
#include <QMessageBox>


#include <stdio.h>    // Заголовочный файл для стандартной библиотеки ввода/вывода
#include <gl\gl.h>    // Заголовочный файл для библиотеки OpenGL32
#include <gl\glu.h>   // Заголовочный файл для библиотеки GLu32
#include <gl\glaux.h> // Заголовочный файл для библиотеки GLaux
#include <math.h>     // Заголовочный файл для математической библиотеки ( НОВОЕ )
#include <stdarg.h>   // Заголовочный файл для функций для работы с переменным


float arra[10][2];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    static float arra[10][2];
//    QStandardItemModel *model = new QStandardItemModel;
//        //QStandardItem *item;
//    //Заголовки столбцов
//        QStringList horizontalHeader;
//        horizontalHeader.append("X");
//        horizontalHeader.append("Y");
//        //horizontalHeader.append("Третий");
//        //horizontalHeader.append("Четвертый");

//        //Заголовки строк
//        QStringList verticalHeader;
//        verticalHeader.append("1");
//        //verticalHeader.append("Ряд 2");

//        model->setHorizontalHeaderLabels(horizontalHeader);
//        model->setVerticalHeaderLabels(verticalHeader);


//        ui->tableView->setModel(model);

//            ui->tableView->resizeRowsToContents();
//            ui->tableView->resizeColumnsToContents();
//            //ui->tableView->verticalHeader()->hide();
//            ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableWidget->setColumnCount(2);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainScene::initializeGL()
{
     glClearColor(1.0, 1.0, 1.0, 1.0);
}

void MainScene::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

HDC        hDC=NULL;  // Приватный контекст устройства GDI
HGLRC      hRC=NULL;  // Постоянный контекст рендеринга
HWND       hWnd=NULL; // Сохраняет дескриптор окна
HINSTANCE  hInstance; // Сохраняет экземпляр приложения

GLuint  base = glGenLists(96);       // База списка отображения для фонта
//GLfloat  cnt1;     // Первый счетчик для передвижения и закрашивания текста
//GLfloat  cnt2;     // Второй счетчик для передвижения и закрашивания текста

//bool  keys[256];      // Массив для работы с клавиатурой
//bool  active=TRUE;    // Флаг активации окна, по умолчанию = TRUE
//bool  fullscreen=TRUE;// Флаг полноэкранного режима

//LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);  // Объявление WndProc
//GLvoid BuildFont(GLvoid)  // Построение нашего растрового шрифта
//{
//  HFONT  font;            // Идентификатор фонта

//  base = glGenLists(96);  // Выделим место для 96 символов ( НОВОЕ )
//font = CreateFont(  -24,        // Высота фонта ( НОВОЕ )
//                      0,        // Ширина фонта
//                    0,        // Угол отношения
//                           0,        // Угол наклона
//                    FW_BOLD,      // Ширина шрифта
//                    FALSE,        // Курсив
//                            FALSE,        // Подчеркивание
//                            FALSE,        // Перечеркивание
//                    ANSI_CHARSET,      // Идентификатор набора символов
//                     OUT_TT_PRECIS,      // Точность вывода
//                    CLIP_DEFAULT_PRECIS,    // Точность отсечения
//                    ANTIALIASED_QUALITY,    // Качество вывода

//GLvoid KillFont(GLvoid)            // Удаление шрифта
//{
//   glDeleteLists(base, 96);        // Удаление всех 96 списков отображения ( НОВОЕ )
//}


GLvoid glPrint(const char *fmt, ...)        // Заказная функция «Печати» GL
{
    char    text[256];      // Место для нашей строки
    va_list    ap;          // Указатель на список аргументов
    if (fmt == NULL)     // Если нет текста
        return;            // Ничего не делать

      va_start(ap, fmt);           // Разбор строки переменных
          vsprintf(text, fmt, ap); // И конвертирование символов в реальные коды
      va_end(ap);                  // Результат помещается в строку
      glPushAttrib(GL_LIST_BIT);      // Протолкнуть биты списка отображения ( НОВОЕ )
        glListBase(base - 32);          // Задать базу символа в 32 ( НОВОЕ )
        glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);// Текст списками отображения(НОВОЕ)
        glPopAttrib(); // Возврат битов списка отображения ( НОВОЕ )

}

void MainScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.25, 0.87, 0.81);
    glBegin(GL_TRIANGLES);

    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, 0.0);

    glEnd();

    glColor3f(0.13, 0.56, 0.13);
    glBegin(GL_QUADS);

    glVertex2f(0.0, 0.5);
    glVertex2f(0.0, 1.0);
    glVertex2f(0.5, 1.0);
    glVertex2f(0.5, 0.5);

    glEnd();

    glLineWidth(2.0);
    glColor3f(0.65, 0.16, 0.16);
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.0, 0.5);
    glVertex2f(0.5, 1.0);
    glVertex2f(1.0, 0.5);
    glVertex2f(0.5, 0);
    glVertex2f(0.0, 0.5);

    glEnd();

    glPointSize(5.0); // размер точки
    glBegin(GL_POINTS);
    glVertex3f(0 , 0.4, 0);
    glEnd();

    QFont font;
        font.setPointSize(10);
        renderText(0,0,0,"some text",font);

    //glDisable(GL_DEPTH_TEST);
    //glDisable(GL_ALPHA_TEST);
    //glColor3f(1.0f, 0.35f, 1.0f);
    //glRasterPos2f(0 , 0);
    //glPrint("Z=%5.3f",  1000);  // Печать текста GL на экран
    //glEnable(GL_DEPTH_TEST);
    //glDisable(GL_ALPHA_TEST);
}


void MainWindow::on_pushButton_clicked()
{
    //ui->tableWidget->insertRow(0);
    QString x_s = ui->lineEdit->text();
    QString y_s = ui->lineEdit_2->text();

    bool ok;
    float x = x_s.toFloat(&ok);
    if (!ok)
    {
        QMessageBox::information(this, "Ошибка", "Неверно введен x!");
        return;
    }
    float y = y_s.toFloat(&ok);
    if (!ok)
    {
        QMessageBox::information(this, "Ошибка", "Неверно введен y!");
        return;
    }

    QTableWidgetItem *item1, *item2;
    item1 = new QTableWidgetItem(ui->lineEdit->text());
    item2 = new QTableWidgetItem(ui->lineEdit_2->text());

    ui->tableWidget->insertRow ( ui->tableWidget->rowCount() );
    ui->tableWidget->setItem   ( ui->tableWidget->rowCount()-1, 0, item1);
    ui->tableWidget->setItem   ( ui->tableWidget->rowCount()-1, 1, item2);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
    arra[ui->tableWidget->rowCount()-1][0] = x;
    arra[ui->tableWidget->rowCount()-1][1] = y;

    if (ui->tableWidget->rowCount()-1 == 5)
    {
        if (arra[5][0] == 12)
            QMessageBox::information(this, "Ошибка", "Ура!");
    }




    /*
  QStandardItemModel *model = new QStandardItemModel;
  QStandardItem *item;
  item = new QStandardItem(ui->lineEdit->text());
  model->setItem(0, 0, item);
  ui->tableView->setModel(model);
   */


}




void MainWindow::on_pushButton_2_clicked()
{
    MainScene *scene = new MainScene;
    scene->resize(600, 900);
    scene->show();
}

void MainWindow::on_pushButton_3_clicked()
{
     int i= ui->tableWidget->currentRow();
     ui->tableWidget->removeRow(i-1);
}
