
#ifndef __ZEGO_EXPRESS_CUSTOM_AUDIO_IO_H__
#define __ZEGO_EXPRESS_CUSTOM_AUDIO_IO_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/**
 * Enable local capture custom audio processing.
 *
 * When enabled, developers can receive local captured audio frame through [onProcessCapturedAudioData], and can modify the audio data.
 * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
 *
 * @param enable Whether to enable local capture custom audio processing.
 * @param config Custom audio processing configuration.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_audio_capture_processing(bool enable, struct zego_custom_audio_process_config* config);


/**
 * Enable custom audio processing for remote playing stream.
 *
 * When enabled, developers can receive audio frame from remote playing stream through [onProcessRemoteAudioData], and can modify the audio data.
 * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
 *
 * @param enable Whether to enable custom audio processing for remote playing stream.
 * @param config Custom audio processing configuration.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_audio_remote_processing(bool enable, struct zego_custom_audio_process_config* config);


/**
 * Enables the callback for receiving audio data.
 *
 * The callback to the corresponding setting of [setAudioDataHandler] is triggered when this interface is called and at publishing stream state or playing stream state.
 *
 * @param enable Whether to enable audio data callback
 * @param callback_bit_mask The callback api bitmask marker for receive audio data, refer to enum [ZegoAudioDataCallbackBitMask], when this param converted to binary, 0x01 for triggering [onCapturedAudioData], 0x10 for triggering [onRemoteAudioData], 0x100 for triggering [onMixedAudioData].The masks can be combined to allow different callbacks to be triggered simultaneously.
 * @param param param of audio frame
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_audio_data_callback(bool enable, unsigned int callback_bit_mask, struct zego_audio_frame_param param);


/**
 * Enables the custom audio I/O function (for the specified channel).
 *
 * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
 *
 * @param enable Whether to enable custom audio IO, default is false
 * @param config Custom audio IO config
 * @param channel Specify the publish channel to enable custom audio IO
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_audio_io(bool enable, struct zego_custom_audio_config * config, enum zego_publish_channel channel);


/**
 * Sends AAC audio data produced by custom audio capture to the SDK (for the specified channel).
 *
 * @param data AAC buffer data
 * @param data_length The total length of the buffer data
 * @param config_length The length of AAC specific config (Note: The AAC encoded data length is 'encodedLength = dataLength - configLength')
 * @param reference_time_millisecond The UNIX timestamp of this AAC audio frame in millisecond.
 * @param param The param of this AAC audio frame
 * @param channel Publish channel for capturing audio frames
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_audio_capture_aac_data(unsigned char * data, unsigned int data_length, unsigned int config_length, unsigned long long reference_time_millisecond, struct zego_audio_frame_param param, enum zego_publish_channel channel);


/**
 * Sends PCM audio data produced by custom audio capture to the SDK (for the specified channel).
 *
 * @param data PCM buffer data
 * @param data_length The total length of the buffer data
 * @param param The param of this PCM audio frame
 * @param channel Publish channel for capturing audio frames
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_audio_capture_pcm_data(unsigned char * data, unsigned int data_length, struct zego_audio_frame_param param, enum zego_publish_channel channel);


/**
 * Fetches PCM audio data of the remote stream for custom audio rendering.
 *
 * It is recommended to use the system framework to periodically invoke this API to drive audio data rendering
 *
 * @param data A block of memory for storing audio PCM data that requires user to manage the memory block's lifecycle, the SDK will copy the audio frame rendering data to this memory block
 * @param data_length The length of the audio data to be fetch this time (dataLength = duration * sampleRate * channels * 2(16 bit depth i.e. 2 Btye))
 * @param param Specify the parameters of the fetched audio frame
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_fetch_custom_audio_render_pcm_data(unsigned char * data, unsigned int data_length, struct zego_audio_frame_param param);


/**
 * Custom audio processing local captured PCM audio frame callback.
 *
 * @param data Audio frame data.
 * @param data_length Audio framw data length.
 * @param param Audio frame parameters.
 * @param user_context Context of user.
 */
typedef void(*zego_on_process_captured_audio_data)(unsigned char* data, unsigned int data_length, struct zego_audio_frame_param* param, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_process_captured_audio_data_callback(zego_on_process_captured_audio_data callback_func, void * user_context);


/**
 * Custom audio processing remote playing stream PCM audio frame callback.
 *
 * @param data Audio frame data.
 * @param data_length Audio frame data length.
 * @param param Audio frame parameters.
 * @param stream_id Stream ID
 * @param user_context Context of user.
 */
typedef void(*zego_on_process_remote_audio_data)(unsigned char* data, unsigned int data_length, struct zego_audio_frame_param* param, const char * stream_id, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_process_remote_audio_data_callback(zego_on_process_remote_audio_data callback_func, void * user_context);


/**
 * The callback for obtaining the audio data captured by the local microphone.
 *
 * In non-custom audio capture mode, the SDK capture the microphone's sound, but the developer may also need to get a copy of the The audio data captured by the SDK SDK is available through this callback.
 * On the premise of calling [setAudioDataHandler] to set the listener callback, after calling [enableAudioDataCallback] to set the mask 0x01, this callback will be triggered only when it is in the publishing stream state.
 *
 * @param data audio data of pcm format
 * @param data_length length of data
 * @param param param of audio frame
 * @param user_context Context of user.
 */
typedef void(*zego_on_captured_audio_data)(const unsigned char* data, unsigned int data_length, struct zego_audio_frame_param param, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_captured_audio_data_callback(zego_on_captured_audio_data callback_func, void * user_context);


/**
 * The callback for obtaining the audio data of all the remote streams pulled.
 *
 * This method will callback all of the remote user's audio mix data. This callback can be used for that you needs to fetch all the playing streams to proccess.
 * On the premise of calling [setAudioDataHandler] to set the listener callback, after calling [enableAudioDataCallback] to set the mask 0x02, this callback will be triggered only when it is in the playing stream state.
 *
 * @param data audio data of pcm format
 * @param data_length length of data
 * @param param param of audio frame
 * @param user_context Context of user.
 */
typedef void(*zego_on_remote_audio_data)(const unsigned char* data, unsigned int data_length, struct zego_audio_frame_param param, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_audio_data_callback(zego_on_remote_audio_data callback_func, void * user_context);


/**
 * The callback for obtaining the mixed audio data. Such mixed auido data are generated by the SDK by mixing the audio data of all the remote streams pulled and the auido data captured locally.
 *
 * The audio data of all playing data is mixed with the data captured by the local microphone before it is sent to the loudspeaker, and calleback out in this way.
 * On the premise of calling [setAudioDataHandler] to set the listener callback, after calling [enableAudioDataCallback] to set the mask 0x04, this callback will be triggered only when it is in the publishing stream state or playing stream state.
 *
 * @param data audio data of pcm format
 * @param data_length length of data
 * @param param param of audio frame
 * @param user_context Context of user.
 */
typedef void(*zego_on_mixed_audio_data)(const unsigned char* data, unsigned int data_length, struct zego_audio_frame_param param, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_mixed_audio_data_callback(zego_on_mixed_audio_data callback_func, void * user_context);



ZEGO_END_DECLS

#endif
