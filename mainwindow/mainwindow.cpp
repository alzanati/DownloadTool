#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _myLabel = new QLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DownloadButton_clicked()
{
    QString url = ui->myUrl->text();
    const QByteArray byteArray = ui->myUrl->text().toUtf8();
    const char* parsedUrl = byteArray.constData();
    CURLcode downloadCode = Download(parsedUrl);
    switch (downloadCode)
    {
        case CURLcode::CURLE_OK :
        _myLabel->setText("\n\tDownload Has Been Complete\t\t\n");
        _myLabel->show();
        case CURLcode::CURLE_COULDNT_RESOLVE_HOST :
        _myLabel->setText("\n\tHost Not Resolved\t\t\n");
        _myLabel->show();
    }
}

size_t MainWindow::write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

CURLcode MainWindow::Download(const char* url) const {
    CURLcode returnCode;
    CURL *curl_handle;
    static const char *pagefilename = "/home/prof/download.out";
    FILE *file;

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* set URL to get here */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);

    /* Switch on full protocol/debug output while testing */
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

    /* disable progress meter, set to 0L to enable and disable debug output */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    /* open the file */
    file = fopen(pagefilename, "wb");
    if(file) {
        /* write the page body to this file handle */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, file);

        /* get it! */
        returnCode = curl_easy_perform(curl_handle);

        /* close the header file */
        fclose(file);
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    /* return result */
    return returnCode;
}
