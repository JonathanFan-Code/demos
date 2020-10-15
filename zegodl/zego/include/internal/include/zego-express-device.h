
#ifndef __ZEGO_EXPRESS_DEVICE_H__
#define __ZEGO_EXPRESS_DEVICE_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/**
 * Mutes or unmutes the microphone.
 *
 * This api is used to control whether the collected audio data is used. When the microphone is muted (disabled), the data is collected and discarded, and the microphone is still occupied.
 * The microphone is still occupied because closing or opening the microphone on the hardware is a relatively heavy operation, and real users may have frequent operations. For trade-off reasons, this api simply discards the collected data.
 * If you really want SDK to give up occupy the microphone, you can call the [enableAudioCaptureDevice] interface.
 * Developers who want to control whether to use microphone on the UI should use this interface to avoid unnecessary performance overhead by using the [enableAudioCaptureDevice].
 *
 * @param mute Whether to mute (disable) the microphone, true: mute (disable) microphone, false: enable microphone. The default is false.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_microphone(bool mute);


/**
 * Checks whether the microphone is muted.
 *
 * Can be used with [muteMicrophone], determine whether the microphone is muted.
 *
 * @return Whether the microphone is muted; true: the microphone is muted; false: the microphone is enable (not muted)
 */
ZEGOEXP_API bool EXP_CALL zego_express_is_microphone_muted();


/**
 * Mutes or unmutes the audio output speaker.
 *
 * After mute speaker, all the SDK sounds will not play, including playing stream, mediaplayer, etc. But the SDK will still occupy the output device.
 *
 * @param mute Whether to mute (disable) speaker audio output, true: mute (disable) speaker audio output, false: enable speaker audio output. The default value is false
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_speaker(bool mute);


/**
 * Checks whether the audio output speaker is muted.
 *
 * Can be used with [muteSpeaker], determine whether the speaker audio output is muted.
 *
 * @return Whether the speaker is muted; true: the speaker is muted; false: the speaker is enable (not muted)
 */
ZEGOEXP_API bool EXP_CALL zego_express_is_speaker_muted();


/**
 * Chooses to use the specified audio device.
 *
 * @param device_type Audio device type
 * @param device_id ID of a device obtained by getAudioDeviceList
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_use_audio_device(enum zego_audio_device_type device_type, const char * device_id);


/**
 * Gets a list of audio devices.
 *
 * @param device_type Audio device type
 * @param device_count Count of device.
 * @return Audo device List
 */
ZEGOEXP_API struct zego_device_info *EXP_CALL zego_express_get_audio_device_list(enum zego_audio_device_type device_type, int * device_count);


/**
 * Release a list of audio devices, only supported in Windows/macOS.
 *
 * @param device_list Audio device type
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_free_audio_device_list(struct zego_device_info* device_list);


/**
 * Enables or disables the audio capture device.
 *
 * This api is used to control whether to release the audio collection device. When the audio collection device is turned off, the SDK will no longer occupy the audio device. Of course, if the stream is being published at this time, there is no audio data.
 * Occupying the audio capture device and giving up Occupying the audio device is a relatively heavy operation, and the [muteMicrophone] interface is generally recommended.
 *
 * @param enable Whether to enable the audio capture device, true: disable audio capture device, false: enable audio capture device
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_audio_capture_device(bool enable);


/**
 * Whether to use the built-in speaker to play audio.
 *
 * When you choose not to use the built-in speaker to play sound, that is, set to false, the SDK will select the currently highest priority audio output device to play the sound according to the system schedule
 *
 * @param enable Whether to use the built-in speaker to play sound, true: use the built-in speaker to play sound, false: use the highest priority audio output device scheduled by the current system to play sound
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_set_built_in_speaker_on(bool enable);


/**
 * Turns on/off the camera (for the specified channel).
 *
 * This interface is used to control whether to start the camera acquisition. After the camera is turned off, video capture will not be performed. At this time, the publish stream will also have no video data.
 * In the case of using a custom video capture function, because the developer has taken over the video data capturing, the SDK is no longer responsible for the video data capturing, this api is no longer valid.
 *
 * @param enable Whether to turn on the camera, true: turn on camera, false: turn off camera
 * @param channel Publishing stream channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_camera(bool enable, enum zego_publish_channel channel);


/**
 * Switches to the front or the rear camera (for the specified channel).
 *
 * This interface is used to control the front or rear camera
 * In the case of using a custom video capture function, because the developer has taken over the video data capturing, the SDK is no longer responsible for the video data capturing, this api is no longer valid.
 *
 * @param enable Whether to use the front camera, true: use the front camera, false: use the the rear camera. The default value is true
 * @param channel Publishing stream channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_use_front_camera(bool enable, enum zego_publish_channel channel);


/**
 * Chooses to use the specified video device (for the specified channel).
 *
 * @param device_id ID of a device obtained by getVideoDeviceList
 * @param channel Publishing stream channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_use_video_device(const char * device_id, enum zego_publish_channel channel);


/**
 * Gets a list of video devices.
 *
 * @return Video device List
 */
ZEGOEXP_API struct zego_device_info *EXP_CALL zego_express_get_video_device_list(int * device_count);


/**
 * Release a list of video devices, only supported in Windows/macOS.
 *
 * @param device_list Video device type
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_free_video_device_list(struct zego_device_info* device_list);


/**
 * Starts sound level monitoring.
 *
 * After starting monitoring, you can receive local audio sound level via [onCapturedSoundLevelUpdate] callback, and receive remote audio sound level via [onRemoteSoundLevelUpdate] callback.
 * Before entering the room, you can call [startPreview] with this api and combine it with [onCapturedSoundLevelUpdate] callback to determine whether the audio device is working properly.
 * [onCapturedSoundLevelUpdate] and [onRemoteSoundLevelUpdate] callback notification period is 100 ms.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_start_sound_level_monitor();


/**
 * Stops sound level monitoring.
 *
 * After the monitoring is stopped, the callback of the local/remote audio sound level will be stopped.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_sound_level_monitor();


/**
 * Starts audio spectrum monitoring.
 *
 * After starting monitoring, you can receive local audio spectrum via [onCapturedAudioSpectrumUpdate] callback, and receive remote audio spectrum via [onRemoteAudioSpectrumUpdate] callback.
 * [onCapturedAudioSpectrumUpdate] and [onRemoteAudioSpectrumUpdate] callback notification period is 100 ms.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_start_audio_spectrum_monitor();


/**
 * Stops audio spectrum monitoring.
 *
 * After the monitoring is stopped, the callback of the local/remote audio spectrum will be stopped.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_audio_spectrum_monitor();


/**
 * Enables or disables headphone monitoring.
 *
 * enable/disable headphone monitor, this setting takes effect when the headset is connected.
 *
 * @param enable Whether to use headphone monitor, true: enable, false: disable
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_headphone_monitor(bool enable);


/**
 * Sets the headphone monitor volume.
 *
 * set headphone monitor volume, this setting takes effect when the headset is connected.
 *
 * @param volume headphone monitor volume, range from 0 to 100, 80 as default
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_set_headphone_monitor_volume(int volume);


/**
 * Enables or disables system audio capture.
 *
 * Enable sound card capture to mix sounds played by the system into the push stream, such as sounds played by the browser, sounds played by other software, etc.
 *
 * @param enable Whether to mix system playout
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_mix_system_playout(bool enable);


/**
 * The callback triggered when there is a change to audio devices (i.e. new device added or existing device deleted).
 *
 * This callback is triggered when an audio device is added or removed from the system. By listening to this callback, users can update the sound collection or output using a specific device when necessary.
 *
 * @param update_type Update type (add/delete)
 * @param device_type Audio device type
 * @param device_info Audio device information
 * @param user_context Context of user.
 */
typedef void(*zego_on_audio_device_state_changed)(enum zego_update_type update_type, enum zego_audio_device_type device_type, struct zego_device_info device_info, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_audio_device_state_changed_callback(zego_on_audio_device_state_changed callback_func, void * user_context);


/**
 * The callback triggered when there is a change to video devices (i.e. new device added or existing device deleted).
 *
 * This callback is triggered when a video device is added or removed from the system. By listening to this callback, users can update the video capture using a specific device when necessary.
 *
 * @param update_type Update type (add/delete)
 * @param device_info Audio device information
 * @param user_context Context of user.
 */
typedef void(*zego_on_video_device_state_changed)(enum zego_update_type update_type, struct zego_device_info device_info, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_video_device_state_changed_callback(zego_on_video_device_state_changed callback_func, void * user_context);


/**
 * The callback triggered every 100ms to report the sound level of the locally captured audio.
 *
 * Callback notification period is 100 ms'. To trigger this callback API, the [startSoundLevelMonitor] interface must be called to start the sound level monitor and you must be in a state where it is publishing the audio and video stream or be in [startPreview] state.
 *
 * @param sound_level Locally captured sound level value, ranging from 0.0 to 100.0
 * @param user_context Context of user.
 */
typedef void(*zego_on_captured_sound_level_update)(const struct zego_sound_level_info* sound_level, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_captured_sound_level_update_callback(zego_on_captured_sound_level_update callback_func, void * user_context);


/**
 * The callback triggered every 100ms to report the sound level of the remote stream.
 *
 * Callback notification period is 100 ms'. To trigger this callback API, the [startSoundLevelMonitor] interface must be called to start the sound level monitor and you must be in a state where it is playing the audio and video stream.
 *
 * @param sound_levels Remote sound level hash map, key is the streamID, value is the sound level value of the corresponding streamID, value ranging from 0.0 to 100.0
 * @param info_count Count of sound level info.
 * @param user_context Context of user.
 */
typedef void(*zego_on_remote_sound_level_update)(const struct zego_sound_level_info* sound_levels, unsigned int info_count, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_sound_level_update_callback(zego_on_remote_sound_level_update callback_func, void * user_context);


/**
 * The callback triggered every 100ms to report the audio spectrum of the locally captured audio.
 *
 * Callback notification period is 100 ms'. To trigger this callback API, the [startAudioSpectrumMonitor] interface must be called to start the audio spectrum monitor and you must be in a state where it is publishing the audio and video stream or be in [startPreview] state.
 *
 * @param audio_spectrum Locally captured audio spectrum value list. Spectrum value range is [0-2^30]
 * @param user_context Context of user.
 */
typedef void(*zego_on_captured_audio_spectrum_update)(const struct zego_audio_spectrum_info* audio_spectrum, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_captured_audio_spectrum_update_callback(zego_on_captured_audio_spectrum_update callback_func, void * user_context);


/**
 * The callback triggered every 100ms to report the audio spectrum of the remote stream.
 *
 * Callback notification period is 100 ms'. To trigger this callback API, the [startAudioSpectrumMonitor] interface must be called to start the audio spectrum monitor and you must be in a state where it is playing the audio and video stream.
 *
 * @param audio_spectrums Remote audio spectrum hash map, key is the streamID, value is the audio spectrum list of the corresponding streamID. Spectrum value range is [0-2^30]
 * @param info_count Count of audio spectrum.
 * @param user_context Context of user.
 */
typedef void(*zego_on_remote_audio_spectrum_update)(const struct zego_audio_spectrum_info* audio_spectrums, unsigned int info_count, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_audio_spectrum_update_callback(zego_on_remote_audio_spectrum_update callback_func, void * user_context);


/**
 * The callback triggered when a device exception occurs.
 *
 * This callback is triggered when an exception occurs when reading or writing the audio and video device.
 *
 * @param error_code The error code corresponding to the status change of the playing stream. Please refer to the common error code documentation [https://doc-en.zego.im/en/308.html] for details
 * @param device_name device name
 * @param user_context Context of user.
 */
typedef void(*zego_on_device_error)(zego_error error_code, const char * device_name, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_device_error_callback(zego_on_device_error callback_func, void * user_context);


/**
 * The callback triggered when the state of the remote camera changes.
 *
 * When the state of the remote camera device changes, such as switching the camera, by monitoring this callback, it is possible to obtain an event related to the far-end camera, which can be used to prompt the user that the video may be abnormal.
 * Developers of 1v1 education scenarios or education small class scenarios and similar scenarios can use this callback notification to determine whether the camera device of the remote publishing stream device is working normally, and preliminary understand the cause of the device problem according to the corresponding state.
 *
 * @param stream_id Stream ID
 * @param state Remote camera status
 * @param user_context Context of user.
 */
typedef void(*zego_on_remote_camera_state_update)(const char * stream_id, enum zego_remote_device_state state, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_camera_state_update_callback(zego_on_remote_camera_state_update callback_func, void * user_context);


/**
 * The callback triggered when the state of the remote microphone changes.
 *
 * When the state of the remote microphone device is changed, such as switching a microphone, etc., by listening to the callback, it is possible to obtain an event related to the remote microphone, which can be used to prompt the user that the audio may be abnormal.
 * Developers of 1v1 education scenarios or education small class scenarios and similar scenarios can use this callback notification to determine whether the microphone device of the remote publishing stream device is working normally, and preliminary understand the cause of the device problem according to the corresponding state.
 *
 * @param stream_id Stream ID
 * @param state Remote microphone status
 * @param user_context Context of user.
 */
typedef void(*zego_on_remote_mic_state_update)(const char * stream_id, enum zego_remote_device_state state, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_mic_state_update_callback(zego_on_remote_mic_state_update callback_func, void * user_context);



ZEGO_END_DECLS

#endif
