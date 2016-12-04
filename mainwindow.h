#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <curl/curl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    CURLcode Download(const char* url) const;

    static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);

private slots:
    void on_DownloadButton_clicked();

private:
    Ui::MainWindow *ui;
    QLabel* _myLabel;
};

#endif // MAINWINDOW_H
