#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>
#include <QJsonObject>
#include <QDateTime>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QFile>
#include <QNetworkReply>

namespace yasem {

class TaskInfo: public QObject
{
    Q_OBJECT
public:
    TaskInfo(int id, const QString& url, const QString& fileName, const QDateTime& startTime, const QDateTime& endTime, QObject* parent);
    virtual ~TaskInfo();

    enum ErrorCode {
        /**
        * Operation successful.
        **/
        ERROR_SUCCESSFUL = 0,
        /**
         * Bad argument.
        **/
        ERROR_BAD_ARGUMENT = -1,
        /**
         * Not enough memory.
        **/
        ERROR_NO_ENOUGH_MEMORY = -2,
        /**
         * Wrong recording range (start or end time). e.i. recording duration
         * must be less or equal than 24 hours.
        **/
        ERROR_WRONG_RANGE = -3,
        /**
         * Task with specified ID was not found.
        **/
        ERROR_TASK_NOT_FOUND = -4,
        /**
         * Wrong file name. Folder where you want to save recording must exist
         * and begin with /media/USB-... or /ram/media/USB-....
        **/
        ERROR_WRONG_FILE_NAME = -5,
        /**
         * Duplicate tasks. Recording with that file name already exists.
        **/
        ERROR_DUPLICATE_TASKS = -6,
        /**
         * Error opening stream URL.
        **/
        ERROR_STREAM_OPENING_ERROR = -7,
        /**
         * Error opening output file.
        **/
        ERROR_CANNOT_OPEN_OUTPUT_FILE = -8,
        /**
         * Maximum number of simultaneous recording is exceeded.
         * It does not mean task number but number of simultaneous recording.
         * See also pvrManager.SetMaxRecordingCnt.
        **/
        ERROR_MAX_SIMULTANEOUS_RECORDS = -9,
        /**
         * Manager got end of stream and recording has finished earlier keeping
         * the recorded file.
        **/
        ERROR_END_OF_STREAM = -10,
        /**
         * Error writing output file. E.i. disk is full or has been disconnected
         * during recording.
        **/
        ERROR_CANNOT_WRITE_FILE = -11,
    };

    enum TaskState {
        /**
         * Waiting for a start of actual recording.
        **/
        STATE_WAITING_FOR_START = 1,
        /**
         * Recording.
        **/
        STATE_RECORDING = 2,
        /**
         * Error occurred. Recording is stopped.
        **/
        STATE_ERROR = 3,
        /**
         * Recording completed.
        **/
        STATE_COMPLETED = 4
    };

    int m_id;               /// unique task identifier
    QString m_url;          /// recorded stream address
    QString m_file_name;    /// requested recording file name
    QDateTime m_start_time;   /// recording start time
    QDateTime m_end_time;     /// recording end time

    TaskState m_state;      /// current task state (see task state table)
    ErrorCode m_error_code; /// error code (see error codes table)

    QJsonObject toJson() const;
    TaskInfo::ErrorCode scheduleStart();
    TaskInfo::ErrorCode scheduleStop();

    static TaskInfo* fromJson(const QJsonObject& json, QObject* parent);

public slots:
    ErrorCode startRecord();
    ErrorCode stopRecord();

protected slots:
    void httpReadyRead();
    void onNetworkError(QNetworkReply::NetworkError error);
    void onError(ErrorCode code);
    void stopDownloading();

signals:
    void errorHappened(ErrorCode code);

protected:
    QTimer m_task_timer;
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;
    QFile* m_file;
    bool m_request_aborted;
};

}

#endif // TASKINFO_H
