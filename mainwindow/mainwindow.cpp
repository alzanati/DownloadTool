#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _myLabel = new QLabel(this);
    _messageBox = new QMessageBox(this);
    _ok = QMessageBox::Yes ;
    _no = QMessageBox::No;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DownloadButton_clicked()
{
    const QByteArray byteArray = ui->myUrl->text().toUtf8();
    const char* parsedUrl = byteArray.constData();
    CURLcode downloadCode = Download(parsedUrl);
    int result = 0;

    switch (downloadCode)
    {
        case CURLcode::CURLE_OK :
        result = _messageBox->question(this, "Download Complete",
                                       "Do You Want To Open ?", _ok, _no);
        if (result == QMessageBox::Yes)
        {

        }

        case CURLcode::CURLE_COULDNT_RESOLVE_HOST :
        result = _messageBox->question(this, "Host Not Resolved",
                                       "Do You Want To Exit ?", _ok, _no);
        if (result == QMessageBox::Yes)
        {
            exit(-1);
        }
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
