
#ifndef __ZEGO_EXPRESS_DEFINE_H__
#define __ZEGO_EXPRESS_DEFINE_H__

#ifndef ZEGOEXP_API
    #ifdef ZEGO_C_INTERFACE

        #ifdef WIN32
            #ifdef ZEGO_EXPRESS_EXPORTS
                #define ZEGOEXP_API __declspec(dllexport)
                #define EXP_CALL __cdecl
            #else
                #define ZEGOEXP_API __declspec(dllimport)
                #define EXP_CALL __cdecl
            #endif
        #else
            #define ZEGOEXP_API __attribute__((visibility("default")))
            #define EXP_CALL
        #endif

    #else

        #define ZEGOEXP_API //nothing if not build c-interface
        #ifdef WIN32
            #define EXP_CALL __cdecl
        #else
            #define EXP_CALL
        #endif

    #endif

#endif



#ifdef __cplusplus
#define ZEGO_BEGIN_DECLS    extern "C" {
#define ZEGO_END_DECLS      }
#else
#define ZEGO_BEGIN_DECLS
#define ZEGO_END_DECLS
#endif

#ifndef __cplusplus
#define bool _Bool
#define false 0
#define true 1
#endif

#if defined(__APPLE_OS__) || defined(__APPLE__)
#include "TargetConditionals.h"
#endif

#define ZEGO_EXPRESS_DEFAULT_LOG_SIZE       (5242880)       // 5 * 1024 * 1024 bytes
#define ZEGO_EXPRESS_MAX_LOG_SIZE           (104857600)     // 100 * 1024 * 1024 bytes


/* 定义调试信息级别 */
#define DEBUG_LEVEL_DEBUG		0x01
#define DEBUG_LEVEL_INFO        0x02
#define DEBUG_LEVEL_WARNING     0x03
#define DEBUG_LEVEL_ERROR       0x04


#define DEF_ML(module, level, subno, idx)  ((module<<27)+(level<<24)+(subno<<20)+(idx))

#define ML_SYSTEM_INFO_INIT_SDK DEF_ML(ZEGO_EXPRESS_MODULE_SYSTEM, DEBUG_LEVEL_INFO, 0x01, 0x0);

#define zego_error int
#define zego_seq int
#define zego_instance int

#define ZEGO_EXPRESS_MAX_COMMON_LEN                         (512)
#define ZEGO_EXPRESS_MAX_APPSIGN_LEN                        (64)
#define ZEGO_EXPRESS_MAX_USERID_LEN                         (64)
#define ZEGO_EXPRESS_MAX_USERNAME_LEN                       (256)
#define ZEGO_EXPRESS_MAX_ROOMID_LEN                         (128)
#define ZEGO_EXPRESS_MAX_TOKEN_LEN                          (512)
#define ZEGO_EXPRESS_MAX_MIX_INPUT_COUNT                    (12)
#define ZEGO_EXPRESS_MAX_STREAM_LEN                         (256)
#define ZEGO_EXPRESS_MAX_MIXER_TASK_LEN                     (256)
#define ZEGO_EXPRESS_MAX_EXTRA_INFO_LEN                     (1024)
#define ZEGO_EXPRESS_MAX_DEVICE_ID_LEN                      (256)
#define ZEGO_EXPRESS_MAX_URL_COUNT                          (10)
#define ZEGO_EXPRESS_MAX_URL_LEN                            (1024)
#define ZEGO_EXPRESS_MAX_IMAGE_PATH                         (512)
#define ZEGO_EXPRESS_MAX_MESSAGE_LEN                        (1024)
#define ZEGO_EXPRESS_MAX_CUSTOM_CMD_LEN                     (1024)
#define ZEGO_EXPRESS_MAX_MEDIAPLAYER_INSTANCE_COUNT         (4)
#define ZEGO_EXPRESS_MAX_CAMERA_CAPTURE_INSTANCE_COUNT      (1)
#define ZEGO_EXPRESS_MAX_MEDIA_RECORD_TASK_ID_LEN           (64)
#define ZEGO_EXPRESS_MAX_ROOM_EXTRA_INFO_KEY_LEN            (128)
#define ZEGO_EXPRESS_MAX_ROOM_EXTRA_INFO_VALUE_LEN          (4096)

/** Application scenario */
enum zego_scenario
{
    /** General scenario */
    zego_scenario_general = 0,

    /** Communication scenario */
    zego_scenario_communication = 1,

    /** Live scenario */
    zego_scenario_live = 2

};

/** Language */
enum zego_language
{
    /** English */
    zego_language_english = 0,

    /** Chinese */
    zego_language_chinese = 1

};

/** engine state */
enum zego_engine_state
{
    /** The engine has started */
    zego_engine_state_start = 0,

    /** The engine has stoped */
    zego_engine_state_stop = 1

};

/** Room state */
enum zego_room_state
{
    /** Unconnected state, enter this state before logging in and after exiting the room. If there is a steady state abnormality in the process of logging in to the room, such as AppID and AppSign are incorrect, or if the same user name is logged in elsewhere and the local end is KickOut, it will enter this state. */
    zego_room_state_disconnected = 0,

    /** The state that the connection is being requested. It will enter this state after successful execution login room function. The display of the application interface is usually performed using this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting connection status. */
    zego_room_state_connecting = 1,

    /** The status that is successfully connected. Entering this status indicates that the login to the room has been successful. The user can receive the callback notification of the user and the stream information in the room. */
    zego_room_state_connected = 2

};

/** Publish channel */
enum zego_publish_channel
{
    /** Main publish channel */
    zego_publish_channel_main = 0,

    /** Auxiliary publish channel */
    zego_publish_channel_aux = 1

};

/** Video rendering fill mode */
enum zego_view_mode
{
    /** The proportional scaling up, there may be black borders */
    zego_view_mode_aspect_fit = 0,

    /** The proportional zoom fills the entire View and may be partially cut */
    zego_view_mode_aspect_fill = 1,

    /** Fill the entire view, the image may be stretched */
    zego_view_mode_scale_to_fill = 2

};

/** Mirror mode for previewing or playing the  of the stream */
enum zego_video_mirror_mode
{
    /** The mirror image only for previewing locally. This mode is used by default. */
    zego_video_mirror_mode_only_preview_mirror = 0,

    /** Both the video previewed locally and the far end playing the stream will see mirror image. */
    zego_video_mirror_mode_both_mirror = 1,

    /** Both the video previewed locally and the far end playing the stream will not see mirror image. */
    zego_video_mirror_mode_no_mirror = 2,

    /** The mirror image only for far end playing the stream. */
    zego_video_mirror_mode_only_publish_mirror = 3

};

/** Publish stream status */
enum zego_publisher_state
{
    /** The state is not published, and it is in this state before publishing the stream. If a steady-state exception occurs in the publish process, such as AppID and AppSign are incorrect, or if other users are already publishing the stream, there will be a failure and enter this state. */
    zego_publisher_state_no_publish = 0,

    /** The state that it is requesting to publish the stream. After the publish stream interface is successfully called, and the application interface is usually displayed using the state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state. */
    zego_publisher_state_publish_requesting = 1,

    /** The state that the stream is being published, entering the state indicates that the stream has been successfully published, and the user can communicate normally. */
    zego_publisher_state_publishing = 2

};

/** Stream quality level */
enum zego_stream_quality_level
{
    /** Excellent */
    zego_stream_quality_level_excellent = 0,

    /** Good */
    zego_stream_quality_level_good = 1,

    /** Normal */
    zego_stream_quality_level_medium = 2,

    /** Bad */
    zego_stream_quality_level_bad = 3,

    /** Failed */
    zego_stream_quality_level_die = 4

};

/** Audio channel type */
enum zego_audio_channel
{
    /** Unknown */
    zego_audio_channel_unknown = 0,

    /** Mono */
    zego_audio_channel_mono = 1,

    /** Stereo */
    zego_audio_channel_stereo = 2

};

/** Audio Codec ID */
enum zego_audio_codec_id
{
    /** default */
    zego_audio_codec_id_default = 0,

    /** Normal */
    zego_audio_codec_id_normal = 1,

    /** Normal2 */
    zego_audio_codec_id_normal2 = 2,

    /** Normal3 */
    zego_audio_codec_id_normal3 = 3,

    /** Low */
    zego_audio_codec_id_low = 4,

    /** Low2 */
    zego_audio_codec_id_low2 = 5,

    /** Low3 */
    zego_audio_codec_id_low3 = 6

};

/** Video Codec ID */
enum zego_video_codec_id
{
    /** default */
    zego_video_codec_id_default = 0,

    /** SVC */
    zego_video_codec_id_svc = 1,

    /** VP8 */
    zego_video_codec_id_vp8 = 2

};

/** Video screen rotation direction */
enum zego_orientation
{
    /** Not rotate */
    zego_orientation_0 = 0,

    /** Rotate 90 degrees counterclockwise */
    zego_orientation_90 = 1,

    /** Rotate 180 degrees counterclockwise */
    zego_orientation_180 = 2,

    /** Rotate 270 degrees counterclockwise */
    zego_orientation_270 = 3

};

/** Player video layer */
enum zego_player_video_layer
{
    /** The layer to be played depends on the network status */
    zego_player_video_layer_auto = 0,

    /** Play the base layer (small resolution) */
    zego_player_video_layer_base = 1,

    /** Play the extend layer (big resolution) */
    zego_player_video_layer_base_extend = 2

};

/** Audio echo cancellation mode */
enum zego_aec_mode
{
    /** Aggressive echo cancellation may affect the sound quality slightly, but the echo will be very clean */
    zego_aec_mode_aggressive = 0,

    /** Moderate echo cancellation, which may slightly affect a little bit of sound, but the residual echo will be less */
    zego_aec_mode_medium = 1,

    /** Comfortable echo cancellation, that is, echo cancellation does not affect the sound quality of the sound, and sometimes there may be a little echo, but it will not affect the normal listening. */
    zego_aec_mode_soft = 2

};

/** Audio Noise Suppression mode */
enum zego_ans_mode
{
    /** Soft ANS */
    zego_ans_mode_soft = 0,

    /** Medium ANS */
    zego_ans_mode_medium = 1,

    /** Aggressive ANS */
    zego_ans_mode_aggressive = 2

};

/** Traffic control property (bitmask enumeration) */
enum zego_traffic_control_property
{
    /** Basic */
    zego_traffic_control_property_basic = 0,

    /** Adaptive FPS */
    zego_traffic_control_property_adaptive_fps = 1,

    /** Adaptive resolution */
    zego_traffic_control_property_adaptive_resolution = 1 << 1,

    /** Adaptive Audio bitrate */
    zego_traffic_control_property_adaptive_audio_bitrate = 1 << 2

};

/** Video transmission mode when current bitrate is lower than the set minimum bitrate */
enum zego_traffic_control_min_video_bitrate_mode
{
    /** Stop video transmission when current bitrate is lower than the set minimum bitrate */
    zego_traffic_control_min_video_bitrate_mode_no_video = 0,

    /** Video is sent at a very low frequency (no more than 2fps) which is lower than the set minimum bitrate */
    zego_traffic_control_min_video_bitrate_mode_ultra_low_fps = 1

};

/** Playing stream status */
enum zego_player_state
{
    /** The state of the flow is not played, and it is in this state before the stream is played. If the steady flow anomaly occurs during the playing process, such as AppID and AppSign are incorrect, it will enter this state. */
    zego_player_state_no_play = 0,

    /** The state that the stream is being requested for playing. After the stream playing interface is successfully called, it will enter the state, and the application interface is usually displayed using this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state. */
    zego_player_state_play_requesting = 1,

    /** The state that the stream is being playing, entering the state indicates that the stream has been successfully played, and the user can communicate normally. */
    zego_player_state_playing = 2

};

/** Media event when playing */
enum zego_player_media_event
{
    /** Audio stuck event when playing */
    zego_player_media_event_audio_break_occur = 0,

    /** Audio stuck event recovery when playing */
    zego_player_media_event_audio_break_resume = 1,

    /** Video stuck event when playing */
    zego_player_media_event_video_break_occur = 2,

    /** Video stuck event recovery when playing */
    zego_player_media_event_video_break_resume = 3

};

/** Update type */
enum zego_update_type
{
    /** Add */
    zego_update_type_add = 0,

    /** Delete */
    zego_update_type_delete = 1

};

/** State of CDN relay */
enum zego_stream_relay_cdn_state
{
    /** The state indicates that there is no CDN relay */
    zego_stream_relay_cdn_state_no_relay = 0,

    /** The CDN relay is being requested */
    zego_stream_relay_cdn_state_relay_requesting = 1,

    /** Entering this status indicates that the CDN relay has been successful */
    zego_stream_relay_cdn_state_relaying = 2

};

/** Reason for state of CDN relay changed */
enum zego_stream_relay_cdn_update_reason
{
    /** No error */
    zego_stream_relay_cdn_update_reason_none = 0,

    /** Server error */
    zego_stream_relay_cdn_update_reason_server_error = 1,

    /** Handshake error */
    zego_stream_relay_cdn_update_reason_handshake_failed = 2,

    /** Access point error */
    zego_stream_relay_cdn_update_reason_access_point_error = 3,

    /** Stream create failure */
    zego_stream_relay_cdn_update_reason_create_stream_failed = 4,

    /** Bad name */
    zego_stream_relay_cdn_update_reason_bad_name = 5,

    /** CDN server actively disconnected */
    zego_stream_relay_cdn_update_reason_cdn_server_disconnected = 6,

    /** Active disconnect */
    zego_stream_relay_cdn_update_reason_disconnected = 7

};

/** Beauty feature (bitmask enumeration) */
enum zego_beautify_feature
{
    /** No beautifying */
    zego_beautify_feature_none = 0,

    /** Polish */
    zego_beautify_feature_polish = 1 << 0,

    /** Sharpen */
    zego_beautify_feature_whiten = 1 << 1,

    /** Skin whiten */
    zego_beautify_feature_skin_whiten = 1 << 2,

    /** Whiten */
    zego_beautify_feature_sharpen = 1 << 3

};

/** Remote device status */
enum zego_remote_device_state
{
    /** Device on */
    zego_remote_device_state_open = 0,

    /** General device error */
    zego_remote_device_state_generic_error = 1,

    /** Invalid device ID */
    zego_remote_device_state_invalid_id = 2,

    /** No permission */
    zego_remote_device_state_no_authorization = 3,

    /** Captured frame rate is 0 */
    zego_remote_device_state_zero_fps = 4,

    /** The device is occupied */
    zego_remote_device_state_in_use_by_other = 5,

    /** The device is not plugged in or unplugged */
    zego_remote_device_state_unplugged = 6,

    /** The system needs to be restarted */
    zego_remote_device_state_reboot_required = 7,

    /** System media services stop, such as under the iOS platform, when the system detects that the current pressure is huge (such as playing a lot of animation), it is possible to disable all media related services. */
    zego_remote_device_state_system_media_services_lost = 8,

    /** Capturing disabled */
    zego_remote_device_state_disable = 9,

    /** The remote device is muted */
    zego_remote_device_state_mute = 10,

    /** The device is interrupted, such as a phone call interruption, etc. */
    zego_remote_device_state_interruption = 11,

    /** There are multiple apps at the same time in the foreground, such as the iPad app split screen, the system will prohibit all apps from using the camera. */
    zego_remote_device_state_in_background = 12,

    /** CDN server actively disconnected */
    zego_remote_device_state_multi_foreground_app = 13,

    /** The system is under high load pressure and may cause abnormal equipment. */
    zego_remote_device_state_by_system_pressure = 14

};

/** Audio device type */
enum zego_audio_device_type
{
    /** Audio input type */
    zego_audio_device_type_input = 0,

    /** Audio output type */
    zego_audio_device_type_output = 1

};

/** Mix stream content type */
enum zego_mixer_input_content_type
{
    /** Mix stream for audio only */
    zego_mixer_input_content_type_audio = 0,

    /** Mix stream for both audio and video */
    zego_mixer_input_content_type_video = 1

};

/** Capture pipeline scale mode */
enum zego_capture_pipeline_scale_mode
{
    /** Zoom immediately after acquisition, default */
    zego_capture_pipeline_scale_mode_pre = 0,

    /** Scaling while encoding */
    zego_capture_pipeline_scale_mode_post = 1

};

/** Video frame format */
enum zego_video_frame_format
{
    /** Unknown format, will take platform default */
    zego_video_frame_format_unknown = 0,

    /** I420 (YUV420Planar) format */
    zego_video_frame_format_i420 = 1,

    /** NV12 (YUV420SemiPlanar) format */
    zego_video_frame_format_nv12 = 2,

    /** NV21 (YUV420SemiPlanar) format */
    zego_video_frame_format_nv21 = 3,

    /** BGRA32 format */
    zego_video_frame_format_bgra32 = 4,

    /** RGBA32 format */
    zego_video_frame_format_rgba32 = 5,

    /** ARGB32 format */
    zego_video_frame_format_argb32 = 6,

    /** ABGR32 format */
    zego_video_frame_format_abgr32 = 7,

    /** I422 (YUV422Planar) format */
    zego_video_frame_format_i422 = 8

};

/** Video encoded frame format */
enum zego_video_encoded_frame_format
{
    /** AVC AVCC format */
    zego_video_encoded_frame_format_avc_avcc = 0,

    /** AVC Annex-B format */
    zego_video_encoded_frame_format_avc_annexb = 1

};

/** Video frame buffer type */
enum zego_video_buffer_type
{
    /** Raw data type video frame */
    zego_video_buffer_type_unknown = 0,

    /** Raw data type video frame */
    zego_video_buffer_type_raw_data = 1,

    /** Encoded data type video frame */
    zego_video_buffer_type_encoded_data = 2,

    /** Texture 2D type video frame */
    zego_video_buffer_type_gl_texture_2d = 3,

    /** CVPixelBuffer type video frame */
    zego_video_buffer_type_cv_pixel_buffer = 4,

    /** Surface Texture type video frame */
    zego_video_buffer_type_surface_texture = 5

};

/** Video frame format series */
enum zego_video_frame_format_series
{
    /** RGB series */
    zego_video_frame_format_series_rgb = 0,

    /** YUV series */
    zego_video_frame_format_series_yuv = 1

};

/** Video frame flip mode */
enum zego_video_flip_mode
{
    /** No flip */
    zego_video_flip_mode_none = 0,

    /** X-axis flip */
    zego_video_flip_mode_x = 1,

    /** Y-axis flip */
    zego_video_flip_mode_y = 2,

    /** X-Y-axis flip */
    zego_video_flip_mode_xy = 3

};

/** Customize the audio processing configuration type */
enum zego_custom_audio_process_type
{
    /** Remote audio processing */
    zego_custom_audio_process_type_remote = 0,

    /** Capture audio processing */
    zego_custom_audio_process_type_capture = 1,

    /** Remote audio and capture audio processing */
    zego_custom_audio_process_type_capture_and_remote = 2

};

/** Player state */
enum zego_media_player_state
{
    /** Not playing */
    zego_media_player_state_no_play = 0,

    /** Playing */
    zego_media_player_state_playing = 1,

    /** Pausing */
    zego_media_player_state_pausing = 2,

    /** End of play */
    zego_media_player_state_play_ended = 3

};

/** Player network event */
enum zego_media_player_network_event
{
    /** Network resources are not playing well, and start trying to cache data */
    zego_media_player_network_event_buffer_begin = 0,

    /** Network resources can be played smoothly */
    zego_media_player_network_event_buffer_ended = 1

};

/** volume type */
enum zego_volume_type
{
    /** volume local */
    zego_volume_type_local = 0,

    /** volume remote */
    zego_volume_type_remote = 1

};

/** audio sample rate */
enum zego_audio_sample_rate
{
    /** Unknown */
    zego_audio_sample_rate_unknown = 0,

    /** 8K */
    zego_audio_sample_rate_8k = 8000,

    /** 16K */
    zego_audio_sample_rate_16k = 16000,

    /** 22.05K */
    zego_audio_sample_rate_22k = 22050,

    /** 24K */
    zego_audio_sample_rate_24k = 24000,

    /** 32K */
    zego_audio_sample_rate_32k = 32000,

    /** 44.1K */
    zego_audio_sample_rate_44k = 44100,

    /** 48K */
    zego_audio_sample_rate_48k = 48000

};

/** Audio capture source type */
enum zego_audio_source_type
{
    /** Default audio capture source (the main channel uses custom audio capture by default; the aux channel uses the same sound as main channel by default) */
    zego_audio_source_type_default = 0,

    /** Use custom audio capture, refer to [enableCustomAudioIO] */
    zego_audio_source_type_custom = 1,

    /** Use media player as audio source, only support aux channel */
    zego_audio_source_type_media_player = 2

};

/** Record type */
enum zego_data_record_type
{
    /** This field indicates that the audio-only SDK records audio by default, and the audio and video SDK records audio and video by default. */
    zego_data_record_type_default = 0,

    /** only record audio */
    zego_data_record_type_only_audio = 1,

    /** only record video, Audio-only SDK is invalid. */
    zego_data_record_type_only_video = 2,

    /** record audio and video, Audio-only SDK will be recorded only audio. */
    zego_data_record_type_audio_and_video = 3

};

/** Record state */
enum zego_data_record_state
{
    /** Unrecorded state, which is the state when a recording error occurs or before recording starts. */
    zego_data_record_state_no_record = 0,

    /** Recording in progress, in this state after successfully call [startCapturedMediaRecord] */
    zego_data_record_state_recording = 1,

    /** Record successs */
    zego_data_record_state_success = 2

};

/** Audio data callback interface enable bitmask enumeration */
enum zego_audio_data_callback_bit_mask
{
    /** The mask bit of this field corresponds to the enable [onCapturedAudioData] callback interface */
    zego_audio_data_callback_bit_mask_captured = 1 << 0,

    /** The mask bit of this field corresponds to the enable [onRemoteAudioData] callback interface */
    zego_audio_data_callback_bit_mask_remote = 1 << 1,

    /** The mask bit of this field corresponds to the enable [onMixedAudioData] callback interface */
    zego_audio_data_callback_bit_mask_mixed = 1 << 2

};

/** Enumeration of iOS screen orientation */
enum zego_ios_orientation
{
    /** Unknown value */
    zego_ios_orientation_unknown = 0,

    /** Portrait */
    zego_ios_orientation_portrait = 1,

    /** Portrait upsidedown */
    zego_ios_orientation_portrait_upsidedown = 2,

    /** Landscape right */
    zego_ios_orientation_landscape_right = 3,

    /** Landscape left */
    zego_ios_orientation_landscape_left = 4

};

/** MediaPlayer instance index */
enum zego_media_player_instance_index
{
    /** Unknown value */
    zego_media_player_instance_index_null = -1,

    /** The first mediaplayer instance index */
    zego_media_player_instance_index_first = 0,

    /** The second mediaplayer instance index */
    zego_media_player_instance_index_second = 1,

    /** The third mediaplayer instance index */
    zego_media_player_instance_index_third = 2,

    /** The forth mediaplayer instance index */
    zego_media_player_instance_index_forth = 3

};

/** Platform language. */
enum zego_platform_language
{
    /** C language. */
    zego_platform_language_c = 0,

    /** Objective-C language. */
    zego_platform_language_oc = 1,

    /** Java language. */
    zego_platform_language_java = 2,

    /** Cpp language. */
    zego_platform_language_cpp = 3,

    /** Dart language. */
    zego_platform_language_dart = 4,

    /** JS language. */
    zego_platform_language_js = 5,

    /** CS language. */
    zego_platform_language_cs = 6

};

/**
 * Log config
 *
 * Configure the log file save path and the maximum log file size
 */
struct zego_log_config
{
    /** Log file save path */
    char log_path[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /** The maximum log file size (Bytes). The default maximum size is 5MB (5 * 1024 * 1024 Bytes) */
    unsigned long long log_size;

};

/**
 * Custom video capture configuration
 *
 * Custom video capture, that is, the developer is responsible for collecting video data and sending the collected video data to SDK for video data encoding and publishing to the ZEGO audio and video cloud.This feature is generally used by developers who use third-party beauty features or record game screen living.
 * When you need to use the custom video capture function, you need to set an instance of this class as a parameter to the corresponding parameter of the [ZegoEngineConfig] instance.
 * Because when using custom video capture, SDK will no longer start the camera to capture video data. You need to collect video data from video sources by yourself.
 */
struct zego_custom_video_capture_config
{
    /** Custom video capture video frame data type */
    enum zego_video_buffer_type buffer_type;

};

/**
 * Custom video render configuration
 *
 * When you need to use the custom video render function, you need to set an instance of this class as a parameter to the corresponding parameter of the [ZegoEngineConfig] instance.
 */
struct zego_custom_video_render_config
{
    /** Custom video capture video frame data type */
    enum zego_video_buffer_type buffer_type;

    /** Custom video rendering video frame data format。Useless when set bufferType as [EncodedData] */
    enum zego_video_frame_format_series frame_format_series;

    /** Whether the engine also renders while customizing video rendering. The default value is [false]. Useless when set bufferType as [EncodedData] */
    bool enable_engine_render;

};

/**
 * Custom audio configuration
 */
struct zego_custom_audio_config
{
    /** Audio capture source type */
    enum zego_audio_source_type source_type;

};

/**
 * Advanced engine configuration
 *
 * When you need to use the advanced functions of SDK, such as custom video capture, custom video rendering and other advanced functions, you need to set the instance corresponding to the advanced function configuration to the corresponding field of this type of instance to achieve the purpose of enabling the corresponding advanced functions of ZegoExpressEngine.
 * The configuration of the corresponding advanced functions needs to be set before [createEngine], and it is invalid to set after [createEngine].
 */
struct zego_engine_config
{
    /** Log configuration, if not set, use the default configuration. It must be valid before [createEngine], if it is set after SDK initialization, it will take effect the next time [createEngine]. */
    struct zego_log_config* log_config;

/** @deprecated This configuration is deprecated after 1.9.0. Please use the ZegoExpressEngine's [enableCustomVideoCapture] method instead */
    struct zego_custom_video_capture_config* custom_video_capture_main_config;

/** @deprecated This configuration is deprecated after 1.9.0. Please use the ZegoExpressEngine's [enableCustomVideoCapture] method instead */
    struct zego_custom_video_capture_config* custom_video_capture_aux_config;

/** @deprecated This configuration is deprecated after 1.9.0. Please use the ZegoExpressEngine's [enableCustomVideoRender] method instead */
    struct zego_custom_video_render_config* custom_video_render_config;

    /** Other special function switches, if not set, no other special functions are used by default. Please contact ZEGO technical support before use. */
    char advanced_config[ZEGO_EXPRESS_MAX_COMMON_LEN];

};

/**
 * Advanced room configuration
 *
 * Configure maximum number of users in the room and authentication token, etc.
 */
struct zego_room_config
{
    /** The maximum number of users in the room, Passing 0 means unlimited, the default is unlimited. */
    unsigned int max_member_count;

    /** Whether to enable the user in and out of the room callback notification [onRoomUserUpdate], the default is off. If developers need to use ZEGO Room user notifications, make sure that each user who login sets this flag to true */
    bool is_user_status_notify;

    /** The token issued by the developer's business server is used to ensure security. The generation rules are detailed in [https://doc.zego.im/CN/565.html](https://doc.zego.im/CN/565.html). Default is empty string, that is, no authentication */
    char token[ZEGO_EXPRESS_MAX_COMMON_LEN];

};

/**
 * Video config
 *
 * Configure parameters used for publishing stream, such as bitrate, frame rate, and resolution.
 * Developers should note that the width and height resolution of the mobile and desktop are opposite. For example, 360p, the resolution of the mobile is 360x640, and the desktop is 640x360.
 */
struct zego_video_config
{
    /** Capture resolution width, control the width of camera image acquisition. Only the camera is not started and the custom video capture is not used, the setting is effective */
    int capture_width;

    /** Capture resolution height, control the height of camera image acquisition. Only the camera is not started and the custom video capture is not used, the setting is effective */
    int capture_height;

    /** Encode resolution width, control the image width of the encoder when publishing stream. The settings before and after publishing stream can be effective */
    int encode_width;

    /** Encode resolution height, control the image height of the encoder when publishing stream. The settings before and after publishing stream can be effective */
    int encode_height;

    /** frame rate, control the frame rate of the camera and the frame rate of the encoder. Only the camera is not started, the setting is effective */
    int fps;

    /** Bit rate in kbps. The settings before and after publishing stream can be effective */
    int bitrate;

    /** The codec id to be used, the default value is [default]. Settings only take effect before publishing stream */
    enum zego_video_codec_id codec_id;

};

/**
 * Audio reverberation parameters
 *
 * Developers can use the SDK's built-in presets to change the parameters of the reverb.
 */
struct zego_reverb_param
{
    /** Reverb Damping, range [0.0, 2.0], controls the attenuation of the reverb, the higher the damping, the higher the attenuation. */
    float damping;

    /** Dry/wet ratio, the range is greater than or equal to 0.0, to control the ratio between reverberation, direct sound and early reflections; dry part is set to 1 by default; the smaller the dry/wet ratio, the larger the wet ratio, the stronger the reverberation effect. */
    float dry_wet_ratio;

    /** Echo, in the range [0.0, 0.5], to control the trailing length of the reverb. */
    float reverberance;

    /** Room size, in the range [0.0, 1.0], to control the size of the "room" in which the reverb is generated, the larger the room, the stronger the reverb. */
    float room_size;

};

/**
 * User object
 *
 * Configure user ID and username to identify users in the room.
 * Note that the userID must be unique under the same appID, otherwise mutual kicks out will occur.
 * It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
 */
struct zego_user
{
    /** User ID, a string with a maximum length of 64 bytes or less. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
    char user_id[ZEGO_EXPRESS_MAX_USERID_LEN];

    /** User Name, a string with a maximum length of 256 bytes or less */
    char user_name[ZEGO_EXPRESS_MAX_USERNAME_LEN];

};

/**
 * Stream object
 *
 * Identify an stream object
 */
struct zego_stream
{
    /** User object instance */
    struct zego_user user;

    /** Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
    char stream_id[ZEGO_EXPRESS_MAX_STREAM_LEN];

    /** Stream extra info */
    char extra_info[ZEGO_EXPRESS_MAX_EXTRA_INFO_LEN];

};

/**
 * Room extra information
 */
struct zego_room_extra_info
{
    /** The key of the room extra information. */
    char key[ZEGO_EXPRESS_MAX_ROOM_EXTRA_INFO_KEY_LEN];

    /** The value of the room extra information. */
    char value[ZEGO_EXPRESS_MAX_ROOM_EXTRA_INFO_VALUE_LEN];

    /** The user who update the room extra information. */
    struct zego_user update_user;

    /** Update time of the room extra information, UNIX timestamp, in milliseconds. */
    unsigned long long update_time;

};

/**
 * View related coordinates
 */
struct zego_rect
{
    /** The value at the left of the horizontal axis of the rectangle */
    int left;

    /** The value at the top of the vertical axis of the rectangle */
    int top;

    /** The value at the right of the horizontal axis of the rectangle */
    int right;

    /** The value at the bottom of the vertical axis of the rectangle */
    int bottom;

};

/**
 * View object
 *
 * Configure view object, view Mode, background color
 */
struct zego_canvas
{
    /** View object */
    void* view;

    /** View mode, default is ZegoViewModeAspectFit */
    enum zego_view_mode view_mode;

    /** Background color, the format is 0xRRGGBB, default is black, which is 0x000000 */
    int background_color;

};

/**
 * Published stream quality information
 *
 * Audio and video parameters and network quality, etc.
 */
struct zego_publish_stream_quality
{
    /** Video capture frame rate. The unit of frame rate is f/s */
    double video_capture_fps;

    /** Video encoding frame rate. The unit of frame rate is f/s */
    double video_encode_fps;

    /** Video transmission frame rate. The unit of frame rate is f/s */
    double video_send_fps;

    /** Video bit rate in kbps */
    double video_kbps;

    /** Audio capture frame rate. The unit of frame rate is f/s */
    double audio_capture_fps;

    /** Audio transmission frame rate. The unit of frame rate is f/s */
    double audio_send_fps;

    /** Audio bit rate in kbps */
    double audio_kbps;

    /** Local to server delay, in milliseconds */
    int rtt;

    /** Packet loss rate, in percentage, 0.0 ~ 1.0 */
    double packet_lost_rate;

    /** Published stream quality level */
    enum zego_stream_quality_level level;

    /** Whether to enable hardware encoding */
    bool is_hardware_encode;

    /** Total number of bytes sent, including audio, video, SEI */
    double total_send_bytes;

    /** Number of audio bytes sent */
    double audio_send_bytes;

    /** Number of video bytes sent */
    double video_send_bytes;

};

/**
 * CDN config object
 *
 * Includes CDN URL and authentication parameter string
 */
struct zego_cdn_config
{
    /** CDN URL */
    char url[ZEGO_EXPRESS_MAX_URL_LEN];

    /** Auth param of URL */
    char auth_param[ZEGO_EXPRESS_MAX_COMMON_LEN];

};

/**
 * Relay to CDN info
 *
 * Including the URL of the relaying CDN, relaying state, etc.
 */
struct zego_stream_relay_cdn_info
{
    /** URL of publishing stream to CDN */
    char url[ZEGO_EXPRESS_MAX_URL_LEN];

    /** State of relaying to CDN */
    enum zego_stream_relay_cdn_state state;

    /** Reason for relay state changed */
    enum zego_stream_relay_cdn_update_reason update_reason;

    /** The timestamp when the state changed, UNIX timestamp, in milliseconds. */
    unsigned long long state_time;

};

/**
 * Advanced player configuration
 *
 * Configure playing stream CDN configuration, video layer
 */
struct zego_player_config
{
    /** The CDN configuration for playing stream. If set, the stream is play according to the URL instead of the streamID. After that, the streamID is only used as the ID of SDK internal callback. */
    struct zego_cdn_config* cdn_config;

    /** Set the video layer for playing the stream */
    enum zego_player_video_layer video_layer;

};

/**
 * Played stream quality information
 *
 * Audio and video parameters and network quality, etc.
 */
struct zego_play_stream_quality
{
    /** Video reception frame rate. The unit of frame rate is f/s */
    double video_recv_fps;

    /** Video decoding frame rate. The unit of frame rate is f/s */
    double video_decode_fps;

    /** Video rendering frame rate. The unit of frame rate is f/s */
    double video_render_fps;

    /** Video bit rate in kbps */
    double video_kbps;

    /** Audio reception frame rate. The unit of frame rate is f/s */
    double audio_recv_fps;

    /** Audio decoding frame rate. The unit of frame rate is f/s */
    double audio_decode_fps;

    /** Audio rendering frame rate. The unit of frame rate is f/s */
    double audio_render_fps;

    /** Audio bit rate in kbps */
    double audio_kbps;

    /** Server to local delay, in milliseconds */
    int rtt;

    /** Packet loss rate, in percentage, 0.0 ~ 1.0 */
    double packet_lost_rate;

    /** Delay from peer to peer, in milliseconds */
    int peer_to_peer_delay;

    /** Packet loss rate from peer to peer, in percentage, 0.0 ~ 1.0 */
    double peer_to_peer_packet_lost_rate;

    /** Published stream quality level */
    enum zego_stream_quality_level level;

    /** Delay after the data is received by the local end, in milliseconds */
    int delay;

    /** Whether to enable hardware decoding */
    bool is_hardware_decode;

    /** Total number of bytes received, including audio, video, SEI */
    double total_recv_bytes;

    /** Number of audio bytes received */
    double audio_recv_bytes;

    /** Number of video bytes received */
    double video_recv_bytes;

};

/**
 * Device Info
 *
 * Including device ID and name
 */
struct zego_device_info
{
    /** Device ID */
    char device_id[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /** Device name */
    char device_name[ZEGO_EXPRESS_MAX_COMMON_LEN];

};

/**
 * Beauty configuration options
 *
 * Configure the parameters of skin peeling, whitening and sharpening
 */
struct zego_beautify_option
{
    /** The sample step size of beauty peeling, the value range is [0,1], default 0.2 */
    double polish_step;

    /** Brightness parameter for beauty and whitening, the larger the value, the brighter the brightness, ranging from [0,1], default 0.5 */
    double whiten_factor;

    /** Beauty sharpening parameter, the larger the value, the stronger the sharpening, value range [0,1], default 0.1 */
    double sharpen_factor;

};

/**
 * Mix stream audio configuration
 *
 * Configure video frame rate, bitrate, and resolution for mixer task
 */
struct zego_mixer_audio_config
{
    /** Audio bitrate in kbps, default is 48 kbps, cannot be modified after starting a mixer task */
    int bitrate;

    /** Audio channel, default is Mono */
    enum zego_audio_channel channel;

    /** codec ID, default is ZegoAudioCodecIDDefault */
    enum zego_audio_codec_id codec_id;

};

/**
 * Mix stream video config object
 *
 * Configure video frame rate, bitrate, and resolution for mixer task
 */
struct zego_mixer_video_config
{
    /** Video resolution width */
    int width;

    /** Video resolution height */
    int height;

    /** Video FPS, cannot be modified after starting a mixer task */
    int fps;

    /** Video bitrate in kbps */
    int bitrate;

};

/**
 * Mixer input
 *
 * Configure the mix stream input stream ID, type, and the layout
 */
struct zego_mixer_input
{
    /** Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
    char stream_id[ZEGO_EXPRESS_MAX_STREAM_LEN];

    /** Mix stream content type */
    enum zego_mixer_input_content_type content_type;

    /** Stream layout */
    struct zego_rect layout;

    /** If enable soundLevel in mix stream task, an unique soundLevelID is need for every stream */
    unsigned int sound_level_id;

};

/**
 * Mixer output object
 *
 * Configure mix stream output target URL or stream ID
 */
struct zego_mixer_output
{
    /** Mix stream output target, URL or stream ID, if set to be URL format, only RTMP URL surpported, for example rtmp://xxxxxxxx */
    char target[ZEGO_EXPRESS_MAX_URL_LEN];

};

/**
 * Watermark object
 *
 * Configure a watermark image URL and the layout of the watermark in the screen
 */
struct zego_watermark
{
    /** Watermark image URL, only png or jpg format surpport. */
    char image_url[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /** Watermark image layout */
    struct zego_rect layout;

};

/**
 * Mix stream task object
 *
 * This class is the configuration class of the mixing stream task. When a mixing stream task is requested to the ZEGO audio and video cloud, the configuration of the mixing task is required.
 * This class describes the detailed configuration information of this mixed task.
 */
struct zego_mixer_task
{
    char task_id[ZEGO_EXPRESS_MAX_MIXER_TASK_LEN];

    struct zego_mixer_input* input_list;

    unsigned int input_list_count;

    struct zego_mixer_output* output_list;

    unsigned int output_list_count;

    struct zego_mixer_video_config video_config;

    struct zego_mixer_audio_config audio_config;

    struct zego_watermark* watermark;

    char background_image_url[ZEGO_EXPRESS_MAX_URL_LEN];

    bool enable_sound_level;

};

/**
 * Mix stream sound level info object
 */
struct zego_mixer_sound_level_info
{
    /** Sound level ID. */
    unsigned int sound_level_id;

    /** Sound level value. */
    float sound_level;

};

/**
 * Sound level info object
 */
struct zego_sound_level_info
{
    /** Stream ID. */
    char stream_id[ZEGO_EXPRESS_MAX_STREAM_LEN];

    /** Sound level value. */
    float sound_level;

};

/**
 * Audio spectrum info object
 */
struct zego_audio_spectrum_info
{
    /** Stream ID. */
    char stream_id[ZEGO_EXPRESS_MAX_STREAM_LEN];

    /** Spectrum values list. */
    float* spectrum_list;

    /** Spectrum values list of count. */
    unsigned int spectrum_count;

};

/**
 * Auto mix stream task object
 */
struct zego_auto_mixer_task
{
    /** The taskID of the auto mixer task */
    char task_id[ZEGO_EXPRESS_MAX_MIXER_TASK_LEN];

    /** The roomID of the auto mixer task */
    char room_id[ZEGO_EXPRESS_MAX_ROOMID_LEN];

    /** The output list of the auto mixer task */
    struct zego_mixer_output* output_list;

    /** Enable or disable sound level callback for the task. If enabled, then the remote player can get the soundLevel of every stream in the inputlist by onAutoMixerSoundLevelUpdate callback. */
    bool enable_sound_level;

    /** The output list count of the auto mixer task */
    unsigned int output_list_count;

};

/**
 * Broadcast message info
 *
 * The received object of the room broadcast message, including the message content, message ID, sender, sending time
 */
struct zego_broadcast_message_info
{
    /** message content */
    char message[ZEGO_EXPRESS_MAX_MESSAGE_LEN];

    /** message id */
    unsigned long long message_id;

    /** Message send time, UNIX timestamp, in milliseconds. */
    unsigned long long send_time;

    /** Message sender */
    struct zego_user from_user;

};

/**
 * Barrage message info
 *
 * The received object of the room barrage message, including the message content, message ID, sender, sending time
 */
struct zego_barrage_message_info
{
    /** message content */
    char message[ZEGO_EXPRESS_MAX_MESSAGE_LEN];

    /** message id */
    char message_id[64];

    /** Message send time, UNIX timestamp, in milliseconds. */
    unsigned long long send_time;

    /** Message sender */
    struct zego_user from_user;

};

/**
 */
struct zego_reliable_message
{
    char type[ZEGO_EXPRESS_MAX_COMMON_LEN];

    char content[ZEGO_EXPRESS_MAX_COMMON_LEN];

    struct zego_user from_user;

    unsigned int latest_seq;

    unsigned long long send_time;

};

/**
 */
struct zego_camera_capture_params
{
    int capture_resolution_width;

    int capture_resolution_height;

    int capture_fps;

};

/**
 * Object for video frame fieldeter
 *
 * Including video frame format, width and height, etc.
 */
struct zego_video_frame_param
{
    /** Video frame format */
    enum zego_video_frame_format format;

    /** Number of bytes per line (for example: RGBA only needs to consider strides [0], I420 needs to consider strides [0,1,2]) */
    int strides[4];

    /** Video frame width */
    int width;

    /** Video frame height */
    int height;

    /** Video frame rotation */
    int rotation;

};

/**
 * Object for video encoded frame fieldeter
 *
 * Including video encoded frame format, width and height, etc.
 */
struct zego_video_encoded_frame_param
{
    /** Video encoded frame format */
    enum zego_video_encoded_frame_format format;

    /** Whether it is a keyframe */
    bool is_key_frame;

    /** Video frame width */
    int width;

    /** Video frame height */
    int height;

    /** SEI data */
    const unsigned char* sei_data;

    /** Length of the SEI data */
    unsigned int sei_data_length;

};

/**
 * Parameter object for audio frame
 *
 * Including the sampling rate and channel of the audio frame
 */
struct zego_audio_frame_param
{
    /** Sampling Rate */
    enum zego_audio_sample_rate sample_rate;

    /** Audio channel, default is Mono */
    enum zego_audio_channel channel;

};

/**
 * Audio configuration
 *
 * Configure audio bitrate, audio channel, audio encoding for publishing stream
 */
struct zego_audio_config
{
    /** Audio bitrate in kbps, default is 48 kbps. The settings before and after publishing stream can be effective */
    int bitrate;

    /** Audio channel, default is Mono. The setting only take effect before publishing stream */
    enum zego_audio_channel channel;

    /** codec ID, default is ZegoAudioCodecIDDefault. The setting only take effect before publishing stream */
    enum zego_audio_codec_id codec_id;

};

/**
 * audio mixing data
 */
struct zego_audio_mixing_data
{
    /** Audio PCM data that needs to be mixed into the stream */
    unsigned char* audio_data;

    /** the length of the audio PCM data that needs to be mixed into the stream. If the data length is sufficient, it must be the same as expectedDataLength */
    unsigned int audio_data_length;

    /** Audio data attributes, including sample rate and number of channels. Currently supports 16k 32k 44.1k 48k sampling rate, mono or stereo channel, 16-bit deep PCM data. Developers need to explicitly specify audio data attributes, otherwise mixing will not take effect. */
    struct zego_audio_frame_param param;

    /** SEI data, used to transfer custom data. When audioData is null, SEIData will not be sent */
    unsigned char* sei_data;

    /** SEI data length */
    unsigned int sei_data_length;

};

/**
 * Customize the audio processing configuration object
 *
 * Including custom audio acquisition type, sampling rate, channel number, sampling number and other parameters
 */
struct zego_custom_audio_process_config
{
    /** Sampling rate, the sampling rate of the input data expected by the audio pre-processing module in App. If 0, the default is the SDK internal sampling rate. */
    enum zego_audio_sample_rate sample_rate;

    /** Number of sound channels, the expected number of sound channels for input data of the audio pre-processing module in App. If 0, the default is the number of internal channels in the SDK */
    enum zego_audio_channel channel;

    /** The number of samples required to encode a frame; When encode = false, if samples = 0, the SDK will use the internal sample number, and the SDK will pass the audio data to the external pre-processing module. If the samples! = 0 (the effective value of samples is between [160, 2048]), and the SDK will send audio data to the external preprocessing module that sets the length of sample number. Encode = true, the number of samples for a frame of AAC encoding can be set as (480/512/1024/1960/2048) */
    int samples;

};

/**
 * Record config
 */
struct zego_data_record_config
{
    /** The path to save the recording file, absolute path, need to include the file name, the file name need to specify the suffix, currently only support .mp4 or .flv, if multiple recording for the same path, will overwrite the file with the same name. */
    char file_path[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /** Type of recording media */
    enum zego_data_record_type record_type;

};

/**
 * File recording progress
 */
struct zego_data_record_progress
{
    /** Current recording duration in milliseconds */
    unsigned long long duration;

    /** Current recording file size in byte */
    unsigned long long current_file_size;

};

#endif /* __ZEGO_EXPRESS_DEFINE_H__ */