#include "timeshift.h"
#include "macros.h"
#include "magprofile.h"
#include "webpage.h"

using namespace yasem;

TimeShift::TimeShift(MagProfile *profile, SDK::WebPage* page):
    m_profile(profile),
    m_page(page),
    m_sliding_mode(false),
    m_timeshift_folder(""),
    m_max_duration(0),
    m_entered_timeshift(false)
{

}

TimeShift::~TimeShift()
{
    STUB();
}

/**
 * @brief TimeShift::SetSlidingMode
 * @param enable
 *
 * true: Slide TimeShift buffer after overflow in paused mode.
 * Event 36 (0x24) will appear with code 3 in arguments. After that buffer continues
 * writing to right boundary and drop all data from left boundary in paused mode.
 *
 * false: Do not slide after buffer overflow in pause mode.
 * Event 36 (0x24) will appear with code 4 in arguments. From this point we can play
 * or seek inside current TimeShift buffer but right boundary will never grow until
 * we switch into real-time mode.
 *
 * Set sliding TimeShift mode which defines what happens after reaching the left
 * boundary of TimeShift buffer in paused mode.
 * By default sliding mode is disabled on start of each playback.
 */
void TimeShift::SetSlidingMode(bool enabled)
{
    STUB() << enabled;
    m_sliding_mode = enabled;
}

/**
 * @brief TimeShift::SetTimeShiftFolder
 * @param folderName Path to timeShift working folder
 *
 * Set path to folder where TimeShift files will be located.
 */
void TimeShift::SetTimeShiftFolder(const QString &folderName)
{
    STUB() << folderName;
    m_timeshift_folder = folderName;
}

/**
 * @brief TimeShift::SetMaxDuration
 * @param maxDuration Duration in seconds
 *
 * Set maximum size of TimeShift window in seconds.
 */
void TimeShift::SetMaxDuration(qint64 maxDuration)
{
    STUB() << maxDuration;
    m_max_duration = maxDuration;
}

/**
 * @brief TimeShift::EnterTimeShift
 * Enter TimeShift mode.
 * In this mode trick mode commands like pause, resume, seek is allowed.
 */
void TimeShift::EnterTimeShift()
{
    m_entered_timeshift = true;
}

/**
 * @brief TimeShift::ExitTimeShift
 * Exit from TimeShift mode and return to real-time mode.
 * All temporary files will be removed.
 */
void TimeShift::ExitTimeShift()
{
    STUB();
    m_entered_timeshift = false;
}

/**
 * @brief TimeShift::ExitTimeShiftAndSave
 * @param path Path to location where recording will be saved
 * @param name Name of the recording
 *
 * Exit from TimeShift mode and save current TimeShift buffer via PVR.
 */
void TimeShift::ExitTimeShiftAndSave(const QString &path, const QString &name)
{
    STUB();
    m_entered_timeshift = false;
}

/**
 * @brief TimeShift::ExitTimeShiftAndSaveDuration
 * @param path Path to location where recording will be saved
 * @param name Name of the recording
 * @param duration In seconds for how log PVR should continue to save stream into specified recording task
 *
 * Exit from TimeShift, stop playback and save TimeShift buffer via PVR with possibility to continue recording.

 */
void TimeShift::ExitTimeShiftAndSaveDuration(const QString &path, const QString &name, qint64 duration)
{
    STUB();
    m_entered_timeshift = false;
}
