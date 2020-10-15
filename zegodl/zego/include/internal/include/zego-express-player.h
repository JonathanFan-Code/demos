
#ifndef __ZEGO_EXPRESS_PLAYER_H__
#define __ZEGO_EXPRESS_PLAYER_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/**
 * Starts playing a stream from ZEGO's streaming cloud.
 *
 * This interface allows users to play audio and video streams from the ZEGO audio and video cloud.
 * Before starting to play the stream, you need to join the room first, you can get the new streamID in the room by listening to the [onRoomStreamUpdate] event callback.
 * In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event.
 * Playing the stream ID that does not exist, the SDK continues to try to play after executing this interface. After the stream ID is successfully published, the audio and video stream can be actually played.
 * The developer can update the player canvas by calling this interface again (the streamID must be the same).
 *
 * @param stream_id Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
 * @param canvas The view used to display the play audio and video stream's image. If the view is set to [NULL], it will not be displayed.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_start_playing_stream(const char * stream_id, struct zego_canvas* canvas);


/**
 * Starts playing a stream from ZEGO's streaming cloud or from third-party CDN.
 *
 * This interface allows users to play audio and video streams both from the ZEGO real-time audio and video cloud and from third-party cdn.
 * Before starting to play the stream, you need to join the room first, you can get the new streamID in the room by listening to the [onRoomStreamUpdate] event callback.
 * In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event.
 * Playing the stream ID that does not exist, the SDK continues to try to play after executing this interface. After the stream ID is successfully published, the audio and video stream can be actually played.
 * The developer can update the player canvas by calling this interface again (the streamID must be the same).
 *
 * @param stream_id Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
 * @param canvas The view used to display the play audio and video stream's image. If the view is set to [NULL], it will not be displayed.
 * @param config Advanced player configuration
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_start_playing_stream_with_config(const char * stream_id, struct zego_canvas* canvas, struct zego_player_config config);


/**
 * Stops playing a stream.
 *
 * This interface allows the user to stop playing the stream. When stopped, the attributes set for this stream previously, such as [setPlayVolume], [mutePlayStreamAudio], [mutePlayStreamVideo], etc., will be invalid and need to be reset when playing the the stream next time.
 *
 * @param stream_id Stream ID
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_playing_stream(const char * stream_id);


/**
 * Sets the stream playback volume.
 *
 * This interface is used to set the playback volume of the stream. Need to be called after calling startPlayingStream.
 * You need to reset after [stopPlayingStream] and [startPlayingStream].
 *
 * @param stream_id Stream ID
 * @param volume Volume percentage. The value ranges from 0 to 200, and the default value is 100.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_set_play_volume(const char * stream_id, int volume);


/**
 * Stops or resumes playing the audio part of a stream.
 *
 * This api can be used to stop playing/retrieving the audio data of the stream. Need to be called after calling startPlayingStream.
 *
 * @param stream_id Stream ID
 * @param mute mute flag, true: mute play stream video, false: resume play stream video
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_play_stream_audio(const char * stream_id, bool mute);


/**
 * Stops or resumes playing the video part of a stream.
 *
 * This interface can be used to stop playing/retrieving the video data of the stream. Need to be called after calling startPlayingStream.
 * This api is only effective for playing stream from ZEGO real-time audio and video cloud (not ZEGO CDN or third-party CDN).
 *
 * @param stream_id Stream ID
 * @param mute mute flag, true: mute play stream video, false: resume play stream video
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_play_stream_video(const char * stream_id, bool mute);


/**
 * Enables or disables hardware decoding.
 *
 * Turn on hardware decoding and use hardware to improve decoding efficiency. Need to be called before calling startPlayingStream.
 * Because hard-decoded support is not particularly good for a few models, SDK uses software decoding by default. If the developer finds that the device is hot when playing a high-resolution audio and video stream during testing of some models, you can consider calling this interface to enable hard decoding.
 *
 * @param enable Whether to turn on hardware decoding switch, true: enable hardware decoding, false: disable hardware decoding. The default is false
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_hardware_decoder(bool enable);


/**
 * Enables or disables frame order detection.
 *
 * @param enable Whether to turn on frame order detection, true: enable check poc,not support B frames, false: disable check poc, support B frames but the screen may temporary splash. The default is true
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_check_poc(bool enable);


/**
 * The callback triggered when the state of stream playing changes.
 *
 * After publishing the stream successfully, the notification of the publish stream state change can be obtained through the callback interface.
 * You can roughly judge the user's downlink network status based on whether the state parameter is in [PLAY_REQUESTING].
 *
 * @param stream_id stream ID
 * @param state Current play state
 * @param error_code The error code corresponding to the status change of the playing stream. Please refer to the common error code documentation [https://doc-en.zego.im/en/308.html] for details.
 * @param extended_data Extended Information with state updates. As the standby, only an empty json table is currently returned
 * @param user_context Context of user.
 */
typedef void(*zego_on_player_state_update)(const char * stream_id, enum zego_player_state state, zego_error error_code, const char * extended_data, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_state_update_callback(zego_on_player_state_update callback_func, void * user_context);


/**
 * The callback triggered every 3 seconds to report the current stream playing quality.
 *
 * After calling the startPlayingStream successfully, this callback will be triggered every 3 seconds. The collection frame rate, bit rate, RTT, packet loss rate and other quality data  can be obtained, such the health of the publish stream can be monitored in real time.
 * You can monitor the health of the played audio and video streams in real time according to the quality parameters of the callback api, in order to show the downlink network status on the device UI interface in real time.
 * If you does not know how to use the various parameters of the callback api, you can only focus on the level field of the quality parameter, which is a comprehensive value describing the downlink network calculated by SDK based on the quality parameters.
 *
 * @param stream_id Stream ID
 * @param quality Playing stream quality, including audio and video frame rate, bit rate, resolution, RTT, etc.
 * @param user_context Context of user.
 */
typedef void(*zego_on_player_quality_update)(const char * stream_id, struct zego_play_stream_quality quality, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_quality_update_callback(zego_on_player_quality_update callback_func, void * user_context);


/**
 * The callback triggered when a media event occurs during streaming playing.
 *
 * This callback is triggered when an event such as audio and video jamming and recovery occurs in the playing stream.
 * You can use this callback to make statistics on stutters or to make friendly displays in the UI interface of the app.
 *
 * @param stream_id Stream ID
 * @param event Play media event callback
 * @param user_context Context of user.
 */
typedef void(*zego_on_player_media_event)(const char * stream_id, enum zego_player_media_event event, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_media_event_callback(zego_on_player_media_event callback_func, void * user_context);


/**
 * The callback triggered when the first audio frame is received.
 *
 * After the startPlayingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of audio data.
 *
 * @param stream_id Stream ID
 * @param user_context Context of user.
 */
typedef void(*zego_on_player_recv_audio_first_frame)(const char * stream_id, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_recv_audio_first_frame_callback(zego_on_player_recv_audio_first_frame callback_func, void * user_context);


/**
 * The callback triggered when the first video frame is received.
 *
 * After the startPlayingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of video  data.
 *
 * @param stream_id Stream ID
 * @param user_context Context of user.
 */
typedef void(*zego_on_player_recv_video_first_frame)(const char * stream_id, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_recv_video_first_frame_callback(zego_on_player_recv_video_first_frame callback_func, void * user_context);


/**
 * The callback triggered when the first video frame is rendered.
 *
 * After the startPlayingStream interface is called successfully, the SDK will receive this callback notification when it rendered the first frame of video  data.
 * You can use this callback to count time consuming that take the first frame time or update the playback stream.
 *
 * @param stream_id Stream ID
 * @param user_context Context of user.
 */
typedef void(*zego_on_player_render_video_first_frame)(const char * stream_id, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_render_video_first_frame_callback(zego_on_player_render_video_first_frame callback_func, void * user_context);


/**
 * The callback triggered when the stream playback resolution changes.
 *
 * If there is a change in the video resolution of the playing stream, the callback will be triggered, and the user can adjust the display for that stream dynamically.
 * If the publishing stream end triggers the internal stream flow control of SDK due to a network problem, the encoding resolution of the streaming end may be dynamically reduced, and this callback will also be received at this time.
 * If the stream is only audio data, the callback will not be received.
 * This callback will be triggered when the played audio and video stream is actually rendered to the set UI play canvas. You can use this callback notification to update or switch UI components that actually play the stream.
 *
 * @param stream_id Stream ID
 * @param width The width of the video
 * @param height The height of the video
 * @param user_context Context of user.
 */
typedef void(*zego_on_player_video_size_changed)(const char * stream_id, int width, int height, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_video_size_changed_callback(zego_on_player_video_size_changed callback_func, void * user_context);


/**
 * The callback triggered when Supplemental Enhancement Information is received.
 *
 * After the remote stream is successfully played, when the remote stream sends SEI (such as directly calling [sendSEI], audio mixing with SEI data, and sending custom video capture encoded data with SEI, etc.), the local end will receive this callback.
 *
 * @param stream_id Stream ID
 * @param data SEI content
 * @param data_length Length of SEI constants/ZegoMixerInputContentType.java
 * @param user_context Context of user.
 */
typedef void(*zego_on_player_recv_sei)(const char * stream_id, const unsigned char* data, unsigned int data_length, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_recv_sei_callback(zego_on_player_recv_sei callback_func, void * user_context);



ZEGO_END_DECLS

#endif
