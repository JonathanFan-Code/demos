
#ifndef __ZEGOEXPRESSDEFINES_H__
#define __ZEGOEXPRESSDEFINES_H__

#define ZEGO_EXPRESS_VIDEO_SDK 1
#define ZEGO_EXPRESS_AUDIO_SDK 0

#if defined(__APPLE_OS__) || defined(__APPLE__)
#include "TargetConditionals.h"
#endif

#ifdef WIN32
#include <windows.h>
#include <wchar.h>
#include <sstream>
#include <locale>
#include <codecvt>
#define ZegoStrncpy strncpy_s
#endif

#if TARGET_OS_OSX || TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#define ZegoStrncpy strncpy
#endif

#if defined(ANDROID) || defined(LINUX)
#define ZegoStrncpy strncpy
#endif

#ifdef ZEGO_DISABLE_SWTICH_THREAD
#define ZEGO_SWITCH_THREAD_PRE {
#define ZEGO_SWITCH_THREAD_ING }
#else
#ifdef WIN32
#define ZEGO_SWITCH_THREAD_PRE  \
        std::function<void(void)>* pFunc = new std::function<void(void)>;*pFunc = [=](void) {
#define ZEGO_SWITCH_THREAD_ING }; oInternalOriginBridge->postWindowsMessage(pFunc);
#elif TARGET_OS_OSX || TARGET_OS_IPHONE
#define ZEGO_SWITCH_THREAD_PRE dispatch_async(dispatch_get_main_queue(), ^{;
#define ZEGO_SWITCH_THREAD_ING });
#else
#define ZEGO_SWITCH_THREAD_PRE {
#define ZEGO_SWITCH_THREAD_ING }
#endif
#endif

#ifdef __GNUC__
#    define GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#    define GCC_VERSION_AT_LEAST(x,y) 0
#endif

#if GCC_VERSION_AT_LEAST(3,1)
#    define ZEGO_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#    define ZEGO_DEPRECATED __declspec(deprecated)
#else
#    define ZEGO_DEPRECATED
#endif

#define ZEGO_UNUSED_VARIABLE(x) ((void)(x))

#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

namespace ZEGO {
    namespace EXPRESS {

        /** Application scenario */
        enum ZegoScenario
        {
            /** General scenario */
            ZEGO_SCENARIO_GENERAL = 0,

            /** Communication scenario */
            ZEGO_SCENARIO_COMMUNICATION = 1,

            /** Live scenario */
            ZEGO_SCENARIO_LIVE = 2

        };

        /** Language */
        enum ZegoLanguage
        {
            /** English */
            ZEGO_LANGUAGE_ENGLISH = 0,

            /** Chinese */
            ZEGO_LANGUAGE_CHINESE = 1

        };

        /** engine state */
        enum ZegoEngineState
        {
            /** The engine has started */
            ZEGO_ENGINE_STATE_START = 0,

            /** The engine has stoped */
            ZEGO_ENGINE_STATE_STOP = 1

        };

        /** Room state */
        enum ZegoRoomState
        {
            /** Unconnected state, enter this state before logging in and after exiting the room. If there is a steady state abnormality in the process of logging in to the room, such as AppID and AppSign are incorrect, or if the same user name is logged in elsewhere and the local end is KickOut, it will enter this state. */
            ZEGO_ROOM_STATE_DISCONNECTED = 0,

            /** The state that the connection is being requested. It will enter this state after successful execution login room function. The display of the application interface is usually performed using this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting connection status. */
            ZEGO_ROOM_STATE_CONNECTING = 1,

            /** The status that is successfully connected. Entering this status indicates that the login to the room has been successful. The user can receive the callback notification of the user and the stream information in the room. */
            ZEGO_ROOM_STATE_CONNECTED = 2

        };

        /** Publish channel */
        enum ZegoPublishChannel
        {
            /** Main publish channel */
            ZEGO_PUBLISH_CHANNEL_MAIN = 0,

            /** Auxiliary publish channel */
            ZEGO_PUBLISH_CHANNEL_AUX = 1

        };

        /** Video rendering fill mode */
        enum ZegoViewMode
        {
            /** The proportional scaling up, there may be black borders */
            ZEGO_VIEW_MODE_ASPECT_FIT = 0,

            /** The proportional zoom fills the entire View and may be partially cut */
            ZEGO_VIEW_MODE_ASPECT_FILL = 1,

            /** Fill the entire view, the image may be stretched */
            ZEGO_VIEW_MODE_SCALE_TO_FILL = 2

        };

        /** Mirror mode for previewing or playing the  of the stream */
        enum ZegoVideoMirrorMode
        {
            /** The mirror image only for previewing locally. This mode is used by default. */
            ZEGO_VIDEO_MIRROR_MODE_ONLY_PREVIEW_MIRROR = 0,

            /** Both the video previewed locally and the far end playing the stream will see mirror image. */
            ZEGO_VIDEO_MIRROR_MODE_BOTH_MIRROR = 1,

            /** Both the video previewed locally and the far end playing the stream will not see mirror image. */
            ZEGO_VIDEO_MIRROR_MODE_NO_MIRROR = 2,

            /** The mirror image only for far end playing the stream. */
            ZEGO_VIDEO_MIRROR_MODE_ONLY_PUBLISH_MIRROR = 3

        };

        /** Publish stream status */
        enum ZegoPublisherState
        {
            /** The state is not published, and it is in this state before publishing the stream. If a steady-state exception occurs in the publish process, such as AppID and AppSign are incorrect, or if other users are already publishing the stream, there will be a failure and enter this state. */
            ZEGO_PUBLISHER_STATE_NO_PUBLISH = 0,

            /** The state that it is requesting to publish the stream. After the publish stream interface is successfully called, and the application interface is usually displayed using the state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state. */
            ZEGO_PUBLISHER_STATE_PUBLISH_REQUESTING = 1,

            /** The state that the stream is being published, entering the state indicates that the stream has been successfully published, and the user can communicate normally. */
            ZEGO_PUBLISHER_STATE_PUBLISHING = 2

        };

        /** Voice changer preset value */
        enum ZegoVoiceChangerPreset
        {
            /** No Voice changer */
            ZEGO_VOICE_CHANGER_PRESET_NONE = 0,

            /** Male voice becomes child's voice */
            ZEGO_VOICE_CHANGER_PRESET_MEN_TO_CHILD = 1,

            /** male to female voices */
            ZEGO_VOICE_CHANGER_PRESET_MEN_TO_WOMEN = 2,

            /** Female voice becomes child's voice */
            ZEGO_VOICE_CHANGER_PRESET_WOMEN_TO_CHILD = 3,

            /** Female Voice to Male Voice */
            ZEGO_VOICE_CHANGER_PRESET_WOMEN_TO_MEN = 4

        };

        /** Reverberation preset value */
        enum ZegoReverbPreset
        {
            /** No Reverberation */
            ZEGO_REVERB_PRESET_NONE = 0,

            /** Soft Room Mode */
            ZEGO_REVERB_PRESET_SOFT_ROOM = 1,

            /** Large Room Mode */
            ZEGO_REVERB_PRESET_LARGE_ROOM = 2,

            /** Concer Hall Mode */
            ZEGO_REVERB_PRESET_CONCER_HALL = 3,

            /** Valley Mode */
            ZEGO_REVERB_PRESET_VALLEY = 4

        };

        /** Video configuration resolution and bitrate preset enumeration. The preset resolutions are adapted for mobile and desktop. On mobile, height is longer than width, and desktop is the opposite. For example, 1080p is actually 1080(w) x 1920(h) on mobile and 1920(w) x 1080(h) on desktop. */
        enum ZegoVideoConfigPreset
        {
            /** Set the resolution to 320x180, the default is 15 fps, the code rate is 300 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_180P = 0,

            /** Set the resolution to 480x270, the default is 15 fps, the code rate is 400 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_270P = 1,

            /** Set the resolution to 640x360, the default is 15 fps, the code rate is 600 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_360P = 2,

            /** Set the resolution to 960x540, the default is 15 fps, the code rate is 1200 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_540P = 3,

            /** Set the resolution to 1280x720, the default is 15 fps, the code rate is 1500 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_720P = 4,

            /** Set the resolution to 1920x1080, the default is 15 fps, the code rate is 3000 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_1080P = 5

        };

        /** Stream quality level */
        enum ZegoStreamQualityLevel
        {
            /** Excellent */
            ZEGO_STREAM_QUALITY_LEVEL_EXCELLENT = 0,

            /** Good */
            ZEGO_STREAM_QUALITY_LEVEL_GOOD = 1,

            /** Normal */
            ZEGO_STREAM_QUALITY_LEVEL_MEDIUM = 2,

            /** Bad */
            ZEGO_STREAM_QUALITY_LEVEL_BAD = 3,

            /** Failed */
            ZEGO_STREAM_QUALITY_LEVEL_DIE = 4

        };

        /** Audio channel type */
        enum ZegoAudioChannel
        {
            /** Unknown */
            ZEGO_AUDIO_CHANNEL_UNKNOWN = 0,

            /** Mono */
            ZEGO_AUDIO_CHANNEL_MONO = 1,

            /** Stereo */
            ZEGO_AUDIO_CHANNEL_STEREO = 2

        };

        /** Audio Codec ID */
        enum ZegoAudioCodecID
        {
            /** default */
            ZEGO_AUDIO_CODEC_ID_DEFAULT = 0,

            /** Normal */
            ZEGO_AUDIO_CODEC_ID_NORMAL = 1,

            /** Normal2 */
            ZEGO_AUDIO_CODEC_ID_NORMAL2 = 2,

            /** Normal3 */
            ZEGO_AUDIO_CODEC_ID_NORMAL3 = 3,

            /** Low */
            ZEGO_AUDIO_CODEC_ID_LOW = 4,

            /** Low2 */
            ZEGO_AUDIO_CODEC_ID_LOW2 = 5,

            /** Low3 */
            ZEGO_AUDIO_CODEC_ID_LOW3 = 6

        };

        /** Video Codec ID */
        enum ZegoVideoCodecID
        {
            /** default */
            ZEGO_VIDEO_CODEC_ID_DEFAULT = 0,

            /** SVC */
            ZEGO_VIDEO_CODEC_ID_SVC = 1,

            /** VP8 */
            ZEGO_VIDEO_CODEC_ID_VP8 = 2

        };

        /** Video screen rotation direction */
        enum ZegoOrientation
        {
            /** Not rotate */
            ZEGO_ORIENTATION_0 = 0,

            /** Rotate 90 degrees counterclockwise */
            ZEGO_ORIENTATION_90 = 1,

            /** Rotate 180 degrees counterclockwise */
            ZEGO_ORIENTATION_180 = 2,

            /** Rotate 270 degrees counterclockwise */
            ZEGO_ORIENTATION_270 = 3

        };

        /** Player video layer */
        enum ZegoPlayerVideoLayer
        {
            /** The layer to be played depends on the network status */
            ZEGO_PLAYER_VIDEO_LAYER_AUTO = 0,

            /** Play the base layer (small resolution) */
            ZEGO_PLAYER_VIDEO_LAYER_BASE = 1,

            /** Play the extend layer (big resolution) */
            ZEGO_PLAYER_VIDEO_LAYER_BASE_EXTEND = 2

        };

        /** Audio echo cancellation mode */
        enum ZegoAECMode
        {
            /** Aggressive echo cancellation may affect the sound quality slightly, but the echo will be very clean */
            ZEGO_AEC_MODE_AGGRESSIVE = 0,

            /** Moderate echo cancellation, which may slightly affect a little bit of sound, but the residual echo will be less */
            ZEGO_AEC_MODE_MEDIUM = 1,

            /** Comfortable echo cancellation, that is, echo cancellation does not affect the sound quality of the sound, and sometimes there may be a little echo, but it will not affect the normal listening. */
            ZEGO_AEC_MODE_SOFT = 2

        };

        /** Audio Noise Suppression mode */
        enum ZegoANSMode
        {
            /** Soft ANS */
            ZEGO_ANS_MODE_SOFT = 0,

            /** Medium ANS */
            ZEGO_ANS_MODE_MEDIUM = 1,

            /** Aggressive ANS */
            ZEGO_ANS_MODE_AGGRESSIVE = 2

        };

        /** Traffic control property (bitmask enumeration) */
        enum ZegoTrafficControlProperty
        {
            /** Basic */
            ZEGO_TRAFFIC_CONTROL_PROPERTY_BASIC = 0,

            /** Adaptive FPS */
            ZEGO_TRAFFIC_CONTROL_PROPERTY_ADAPTIVE_FPS = 1,

            /** Adaptive resolution */
            ZEGO_TRAFFIC_CONTROL_PROPERTY_ADAPTIVE_RESOLUTION = 1 << 1,

            /** Adaptive Audio bitrate */
            ZEGO_TRAFFIC_CONTROL_PROPERTY_ADAPTIVE_AUDIO_BITRATE = 1 << 2

        };

        /** Video transmission mode when current bitrate is lower than the set minimum bitrate */
        enum ZegoTrafficControlMinVideoBitrateMode
        {
            /** Stop video transmission when current bitrate is lower than the set minimum bitrate */
            ZEGO_TRAFFIC_CONTROL_MIN_VIDEO_BITRATE_MODE_NO_VIDEO = 0,

            /** Video is sent at a very low frequency (no more than 2fps) which is lower than the set minimum bitrate */
            ZEGO_TRAFFIC_CONTROL_MIN_VIDEO_BITRATE_MODE_ULTRA_LOW_FPS = 1

        };

        /** Playing stream status */
        enum ZegoPlayerState
        {
            /** The state of the flow is not played, and it is in this state before the stream is played. If the steady flow anomaly occurs during the playing process, such as AppID and AppSign are incorrect, it will enter this state. */
            ZEGO_PLAYER_STATE_NO_PLAY = 0,

            /** The state that the stream is being requested for playing. After the stream playing interface is successfully called, it will enter the state, and the application interface is usually displayed using this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state. */
            ZEGO_PLAYER_STATE_PLAY_REQUESTING = 1,

            /** The state that the stream is being playing, entering the state indicates that the stream has been successfully played, and the user can communicate normally. */
            ZEGO_PLAYER_STATE_PLAYING = 2

        };

        /** Media event when playing */
        enum ZegoPlayerMediaEvent
        {
            /** Audio stuck event when playing */
            ZEGO_PLAYER_MEDIA_EVENT_AUDIO_BREAK_OCCUR = 0,

            /** Audio stuck event recovery when playing */
            ZEGO_PLAYER_MEDIA_EVENT_AUDIO_BREAK_RESUME = 1,

            /** Video stuck event when playing */
            ZEGO_PLAYER_MEDIA_EVENT_VIDEO_BREAK_OCCUR = 2,

            /** Video stuck event recovery when playing */
            ZEGO_PLAYER_MEDIA_EVENT_VIDEO_BREAK_RESUME = 3

        };

        /** Update type */
        enum ZegoUpdateType
        {
            /** Add */
            ZEGO_UPDATE_TYPE_ADD = 0,

            /** Delete */
            ZEGO_UPDATE_TYPE_DELETE = 1

        };

        /** State of CDN relay */
        enum ZegoStreamRelayCDNState
        {
            /** The state indicates that there is no CDN relay */
            ZEGO_STREAM_RELAY_CDN_STATE_NO_RELAY = 0,

            /** The CDN relay is being requested */
            ZEGO_STREAM_RELAY_CDN_STATE_RELAY_REQUESTING = 1,

            /** Entering this status indicates that the CDN relay has been successful */
            ZEGO_STREAM_RELAY_CDN_STATE_RELAYING = 2

        };

        /** Reason for state of CDN relay changed */
        enum ZegoStreamRelayCDNUpdateReason
        {
            /** No error */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_NONE = 0,

            /** Server error */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_SERVER_ERROR = 1,

            /** Handshake error */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_HANDSHAKE_FAILED = 2,

            /** Access point error */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_ACCESS_POINT_ERROR = 3,

            /** Stream create failure */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_CREATE_STREAM_FAILED = 4,

            /** Bad name */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_BAD_NAME = 5,

            /** CDN server actively disconnected */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_CDN_SERVER_DISCONNECTED = 6,

            /** Active disconnect */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_DISCONNECTED = 7

        };

        /** Remote device status */
        enum ZegoRemoteDeviceState
        {
            /** Device on */
            ZEGO_REMOTE_DEVICE_STATE_OPEN = 0,

            /** General device error */
            ZEGO_REMOTE_DEVICE_STATE_GENERIC_ERROR = 1,

            /** Invalid device ID */
            ZEGO_REMOTE_DEVICE_STATE_INVALID_ID = 2,

            /** No permission */
            ZEGO_REMOTE_DEVICE_STATE_NO_AUTHORIZATION = 3,

            /** Captured frame rate is 0 */
            ZEGO_REMOTE_DEVICE_STATE_ZERO_FPS = 4,

            /** The device is occupied */
            ZEGO_REMOTE_DEVICE_STATE_IN_USE_BY_OTHER = 5,

            /** The device is not plugged in or unplugged */
            ZEGO_REMOTE_DEVICE_STATE_UNPLUGGED = 6,

            /** The system needs to be restarted */
            ZEGO_REMOTE_DEVICE_STATE_REBOOT_REQUIRED = 7,

            /** System media services stop, such as under the iOS platform, when the system detects that the current pressure is huge (such as playing a lot of animation), it is possible to disable all media related services. */
            ZEGO_REMOTE_DEVICE_STATE_SYSTEM_MEDIA_SERVICES_LOST = 8,

            /** Capturing disabled */
            ZEGO_REMOTE_DEVICE_STATE_DISABLE = 9,

            /** The remote device is muted */
            ZEGO_REMOTE_DEVICE_STATE_MUTE = 10,

            /** The device is interrupted, such as a phone call interruption, etc. */
            ZEGO_REMOTE_DEVICE_STATE_INTERRUPTION = 11,

            /** There are multiple apps at the same time in the foreground, such as the iPad app split screen, the system will prohibit all apps from using the camera. */
            ZEGO_REMOTE_DEVICE_STATE_IN_BACKGROUND = 12,

            /** CDN server actively disconnected */
            ZEGO_REMOTE_DEVICE_STATE_MULTI_FOREGROUND_APP = 13,

            /** The system is under high load pressure and may cause abnormal equipment. */
            ZEGO_REMOTE_DEVICE_STATE_BY_SYSTEM_PRESSURE = 14

        };

        /** Audio device type */
        enum ZegoAudioDeviceType
        {
            /** Audio input type */
            ZEGO_AUDIO_DEVICE_TYPE_INPUT = 0,

            /** Audio output type */
            ZEGO_AUDIO_DEVICE_TYPE_OUTPUT = 1

        };

        /** Mix stream content type */
        enum ZegoMixerInputContentType
        {
            /** Mix stream for audio only */
            ZEGO_MIXER_INPUT_CONTENT_TYPE_AUDIO = 0,

            /** Mix stream for both audio and video */
            ZEGO_MIXER_INPUT_CONTENT_TYPE_VIDEO = 1

        };

        /** Capture pipeline scale mode */
        enum ZegoCapturePipelineScaleMode
        {
            /** Zoom immediately after acquisition, default */
            ZEGO_CAPTURE_PIPELINE_SCALE_MODE_PRE = 0,

            /** Scaling while encoding */
            ZEGO_CAPTURE_PIPELINE_SCALE_MODE_POST = 1

        };

        /** Video frame format */
        enum ZegoVideoFrameFormat
        {
            /** Unknown format, will take platform default */
            ZEGO_VIDEO_FRAME_FORMAT_UNKNOWN = 0,

            /** I420 (YUV420Planar) format */
            ZEGO_VIDEO_FRAME_FORMAT_I420 = 1,

            /** NV12 (YUV420SemiPlanar) format */
            ZEGO_VIDEO_FRAME_FORMAT_NV12 = 2,

            /** NV21 (YUV420SemiPlanar) format */
            ZEGO_VIDEO_FRAME_FORMAT_NV21 = 3,

            /** BGRA32 format */
            ZEGO_VIDEO_FRAME_FORMAT_BGRA32 = 4,

            /** RGBA32 format */
            ZEGO_VIDEO_FRAME_FORMAT_RGBA32 = 5,

            /** ARGB32 format */
            ZEGO_VIDEO_FRAME_FORMAT_ARGB32 = 6,

            /** ABGR32 format */
            ZEGO_VIDEO_FRAME_FORMAT_ABGR32 = 7,

            /** I422 (YUV422Planar) format */
            ZEGO_VIDEO_FRAME_FORMAT_I422 = 8

        };

        /** Video encoded frame format */
        enum ZegoVideoEncodedFrameFormat
        {
            /** AVC AVCC format */
            ZEGO_VIDEO_ENCODED_FRAME_FORMAT_AVCC = 0,

            /** AVC Annex-B format */
            ZEGO_VIDEO_ENCODED_FRAME_FORMAT_ANNEXB = 1

        };

        /** Video frame buffer type */
        enum ZegoVideoBufferType
        {
            /** Raw data type video frame */
            ZEGO_VIDEO_BUFFER_TYPE_UNKNOWN = 0,

            /** Raw data type video frame */
            ZEGO_VIDEO_BUFFER_TYPE_RAW_DATA = 1,

            /** Encoded data type video frame */
            ZEGO_VIDEO_BUFFER_TYPE_ENCODED_DATA = 2

        };

        /** Video frame format series */
        enum ZegoVideoFrameFormatSeries
        {
            /** RGB series */
            ZEGO_VIDEO_FRAME_FORMAT_SERIES_RGB = 0,

            /** YUV series */
            ZEGO_VIDEO_FRAME_FORMAT_SERIES_YUV = 1

        };

        /** Video frame flip mode */
        enum ZegoVideoFlipMode
        {
            /** No flip */
            ZEGO_VIDEO_FLIP_MODE_NONE = 0,

            /** X-axis flip */
            ZEGO_VIDEO_FLIP_MODE_X = 1,

            /** Y-axis flip */
            ZEGO_VIDEO_FLIP_MODE_Y = 2,

            /** X-Y-axis flip */
            ZEGO_VIDEO_FLIP_MODE_XY = 3

        };

        /** Customize the audio processing configuration type */
        enum ZegoCustomAudioProcessType
        {
            /** Remote audio processing */
            ZEGO_CUSTOM_AUDIO_PROCESS_TYPE_REMOTE = 0,

            /** Capture audio processing */
            ZEGO_CUSTOM_AUDIO_PROCESS_TYPE_CAPTURE = 1,

            /** Remote audio and capture audio processing */
            ZEGO_CUSTOM_AUDIO_PROCESS_TYPE_CAPTURE_AND_REMOTE = 2

        };

        /** Audio Config Preset */
        enum ZegoAudioConfigPreset
        {
            /** Basic sound quality (16 kbps, Mono, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_BASIC_QUALITY = 0,

            /** Standard sound quality (48 kbps, Mono, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY = 1,

            /** Standard sound quality (56 kbps, Stereo, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY_STEREO = 2,

            /** High sound quality (128 kbps, Mono, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_HIGH_QUALITY = 3,

            /** High sound quality (192 kbps, Stereo, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_HIGH_QUALITY_STEREO = 4

        };

        /** Player state */
        enum ZegoMediaPlayerState
        {
            /** Not playing */
            ZEGO_MEDIA_PLAYER_STATE_NO_PLAY = 0,

            /** Playing */
            ZEGO_MEDIA_PLAYER_STATE_PLAYING = 1,

            /** Pausing */
            ZEGO_MEDIA_PLAYER_STATE_PAUSING = 2,

            /** End of play */
            ZEGO_MEDIA_PLAYER_STATE_PLAY_ENDED = 3

        };

        /** Player network event */
        enum ZegoMediaPlayerNetworkEvent
        {
            /** Network resources are not playing well, and start trying to cache data */
            ZEGO_MEDIA_PLAYER_NETWORK_EVENT_BUFFER_BEGIN = 0,

            /** Network resources can be played smoothly */
            ZEGO_MEDIA_PLAYER_NETWORK_EVENT_BUFFER_ENDED = 1

        };

        /** volume type */
        enum ZegoVolumeType
        {
            /** volume local */
            ZEGO_VOLUME_TYPE_LOCAL = 0,

            /** volume remote */
            ZEGO_VOLUME_TYPE_REMOTE = 1

        };

        /** audio sample rate */
        enum ZegoAudioSampleRate
        {
            /** Unknown */
            ZEGO_AUDIO_SAMPLE_RATE_UNKNOWN = 0,

            /** 8K */
            ZEGO_AUDIO_SAMPLE_RATE_8K = 8000,

            /** 16K */
            ZEGO_AUDIO_SAMPLE_RATE_16K = 16000,

            /** 22.05K */
            ZEGO_AUDIO_SAMPLE_RATE_22K = 22050,

            /** 24K */
            ZEGO_AUDIO_SAMPLE_RATE_24K = 24000,

            /** 32K */
            ZEGO_AUDIO_SAMPLE_RATE_32K = 32000,

            /** 44.1K */
            ZEGO_AUDIO_SAMPLE_RATE_44K = 44100,

            /** 48K */
            ZEGO_AUDIO_SAMPLE_RATE_48K = 48000

        };

        /** Audio capture source type */
        enum ZegoAudioSourceType
        {
            /** Default audio capture source (the main channel uses custom audio capture by default; the aux channel uses the same sound as main channel by default) */
            ZEGO_AUDIO_SOURCE_TYPE_DEFAULT = 0,

            /** Use custom audio capture, refer to [enableCustomAudioIO] */
            ZEGO_AUDIO_SOURCE_TYPE_CUSTOM = 1,

            /** Use media player as audio source, only support aux channel */
            ZEGO_AUDIO_SOURCE_TYPE_MEDIA_PLAYER = 2

        };

        /** Record type */
        enum ZegoDataRecordType
        {
            /** This field indicates that the audio-only SDK records audio by default, and the audio and video SDK records audio and video by default. */
            ZEGO_DATA_RECORD_TYPE_DEFAULT = 0,

            /** only record audio */
            ZEGO_DATA_RECORD_TYPE_ONLY_AUDIO = 1,

            /** only record video, Audio-only SDK is invalid. */
            ZEGO_DATA_RECORD_TYPE_ONLY_VIDEO = 2,

            /** record audio and video, Audio-only SDK will be recorded only audio. */
            ZEGO_DATA_RECORD_TYPE_AUDIO_AND_VIDEO = 3

        };

        /** Record state */
        enum ZegoDataRecordState
        {
            /** Unrecorded state, which is the state when a recording error occurs or before recording starts. */
            ZEGO_DATA_RECORD_STATE_NO_RECORD = 0,

            /** Recording in progress, in this state after successfully call [startCapturedMediaRecord] */
            ZEGO_DATA_RECORD_STATE_RECORDING = 1,

            /** Record successs */
            ZEGO_DATA_RECORD_STATE_SUCCESS = 2

        };

        /** Audio data callback interface enable bitmask enumeration */
        enum ZegoAudioDataCallbackBitMask
        {
            /** The mask bit of this field corresponds to the enable [onCapturedAudioData] callback interface */
            ZEGO_AUDIO_DATA_CALLBACK_BIT_MASK_CAPTURED = 1 << 0,

            /** The mask bit of this field corresponds to the enable [onRemoteAudioData] callback interface */
            ZEGO_AUDIO_DATA_CALLBACK_BIT_MASK_REMOTE = 1 << 1,

            /** The mask bit of this field corresponds to the enable [onMixedAudioData] callback interface */
            ZEGO_AUDIO_DATA_CALLBACK_BIT_MASK_MIXED = 1 << 2

        };

        /**
         * Log config
         *
         * Configure the log file save path and the maximum log file size
         */
        struct ZegoLogConfig
        {
            /** Log file save path */
            std::string logPath;

            /** The maximum log file size (Bytes). The default maximum size is 5MB (5 * 1024 * 1024 Bytes) */
            unsigned long long logSize;

            ZegoLogConfig(){
                logSize = 5 * 1024 * 1024;
            }

        };

        /**
         * Custom video capture configuration
         *
         * Custom video capture, that is, the developer is responsible for collecting video data and sending the collected video data to SDK for video data encoding and publishing to the ZEGO audio and video cloud.This feature is generally used by developers who use third-party beauty features or record game screen living.
         * When you need to use the custom video capture function, you need to set an instance of this class as a parameter to the corresponding parameter of the [ZegoEngineConfig] instance.
         * Because when using custom video capture, SDK will no longer start the camera to capture video data. You need to collect video data from video sources by yourself.
         */
        struct ZegoCustomVideoCaptureConfig
        {
            /** Custom video capture video frame data type */
            ZegoVideoBufferType bufferType;

        };

        /**
         * Custom video render configuration
         *
         * When you need to use the custom video render function, you need to set an instance of this class as a parameter to the corresponding parameter of the [ZegoEngineConfig] instance.
         */
        struct ZegoCustomVideoRenderConfig
        {
            /** Custom video capture video frame data type */
            ZegoVideoBufferType bufferType;

            /** Custom video rendering video frame data format。Useless when set bufferType as [EncodedData] */
            ZegoVideoFrameFormatSeries frameFormatSeries;

            /** Whether the engine also renders while customizing video rendering. The default value is [false]. Useless when set bufferType as [EncodedData] */
            bool enableEngineRender;

        };

        /**
         * Custom audio configuration
         */
        struct ZegoCustomAudioConfig
        {
            /** Audio capture source type */
            ZegoAudioSourceType sourceType;

        };

        /**
         * Advanced engine configuration
         *
         * When you need to use the advanced functions of SDK, such as custom video capture, custom video rendering and other advanced functions, you need to set the instance corresponding to the advanced function configuration to the corresponding field of this type of instance to achieve the purpose of enabling the corresponding advanced functions of ZegoExpressEngine.
         * The configuration of the corresponding advanced functions needs to be set before [createEngine], and it is invalid to set after [createEngine].
         */
        struct ZegoEngineConfig
        {
            /** Log configuration, if not set, use the default configuration */
            ZegoLogConfig* logConfig;

            /** @deprecated This configuration is deprecated after 1.9.0. Please use the ZegoExpressEngine's [enableCustomVideoCapture] method instead */
            ZegoCustomVideoCaptureConfig* customVideoCaptureMainConfig;

            /** @deprecated This configuration is deprecated after 1.9.0. Please use the ZegoExpressEngine's [enableCustomVideoCapture] method instead */
            ZegoCustomVideoCaptureConfig* customVideoCaptureAuxConfig;

            /** @deprecated This configuration is deprecated after 1.9.0. Please use the ZegoExpressEngine's [enableCustomVideoRender] method instead */
            ZegoCustomVideoRenderConfig* customVideoRenderConfig;

            /** Other special function switches, if not set, no other special functions are used by default. Please contact ZEGO technical support before use. */
            std::unordered_map<std::string, std::string> advancedConfig;

            ZegoEngineConfig(){
                logConfig = nullptr;
                customVideoCaptureMainConfig = nullptr;
                customVideoCaptureAuxConfig = nullptr;
                customVideoRenderConfig = nullptr;
            }

        };

        /**
         * Advanced room configuration
         *
         * Configure maximum number of users in the room and authentication token, etc.
         */
        struct ZegoRoomConfig
        {
            /** The maximum number of users in the room, Passing 0 means unlimited, the default is unlimited. */
            unsigned int maxMemberCount;

            /** Whether to enable the user in and out of the room callback notification [onRoomUserUpdate], the default is off. If developers need to use ZEGO Room user notifications, make sure that each user who login sets this flag to true */
            bool isUserStatusNotify;

            /** The token issued by the developer's business server is used to ensure security. The generation rules are detailed in [https://doc.zego.im/CN/565.html](https://doc.zego.im/CN/565.html). Default is empty string, that is, no authentication */
            std::string token;

            ZegoRoomConfig():maxMemberCount(0), isUserStatusNotify(false), token(""){
            }

        };

        /**
         * Video config
         *
         * Configure parameters used for publishing stream, such as bitrate, frame rate, and resolution.
         * Developers should note that the width and height resolution of the mobile and desktop are opposite. For example, 360p, the resolution of the mobile is 360x640, and the desktop is 640x360.
         */
        struct ZegoVideoConfig
        {
            /** Capture resolution width, control the width of camera image acquisition. Only the camera is not started and the custom video capture is not used, the setting is effective */
            int captureWidth;

            /** Capture resolution height, control the height of camera image acquisition. Only the camera is not started and the custom video capture is not used, the setting is effective */
            int captureHeight;

            /** Encode resolution width, control the image width of the encoder when publishing stream. The settings before and after publishing stream can be effective */
            int encodeWidth;

            /** Encode resolution height, control the image height of the encoder when publishing stream. The settings before and after publishing stream can be effective */
            int encodeHeight;

            /** frame rate, control the frame rate of the camera and the frame rate of the encoder. Only the camera is not started, the setting is effective */
            int fps;

            /** Bit rate in kbps. The settings before and after publishing stream can be effective */
            int bitrate;

            /** The codec id to be used, the default value is [default]. Settings only take effect before publishing stream */
            ZegoVideoCodecID codecID;

            ZegoVideoConfig(ZegoVideoConfigPreset preset = ZEGO_VIDEO_CONFIG_PRESET_360P){
            codecID = ZEGO_VIDEO_CODEC_ID_DEFAULT;
            switch (preset) {
            case ZEGO_VIDEO_CONFIG_PRESET_180P:
                captureWidth = 320;
                captureHeight = 180;
                encodeWidth = 320;
                encodeHeight = 180;
                bitrate = 300;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_270P:
                captureWidth = 480;
                captureHeight = 270;
                encodeWidth = 480;
                encodeHeight = 270;
                bitrate = 400;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_360P:
                captureWidth = 640;
                captureHeight = 360;
                encodeWidth = 640;
                encodeHeight = 360;
                bitrate = 600;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_540P:
                captureWidth = 960;
                captureHeight = 540;
                encodeWidth = 960;
                encodeHeight = 540;
                bitrate = 1200;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_720P:
                captureWidth = 1280;
                captureHeight = 720;
                encodeWidth = 1280;
                encodeHeight = 720;
                bitrate = 1500;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_1080P:
                captureWidth = 1920;
                captureHeight = 1080;
                encodeWidth = 1920;
                encodeHeight = 1080;
                bitrate = 3000;
                fps = 15;
                break;
            }
            }

        };

        /**
         * Video config
         *
         * developer can use the built-in presets of the SDK to change the parameters of the voice changer
         */
        struct ZegoVoiceChangerParam
        {
            /** pitch */
            float pitch;

            ZegoVoiceChangerParam(ZegoVoiceChangerPreset preset = ZEGO_VOICE_CHANGER_PRESET_NONE){
                switch(preset) {
                case ZEGO_VOICE_CHANGER_PRESET_MEN_TO_CHILD:
                    pitch = 8.0f;
                    break;
                case ZEGO_VOICE_CHANGER_PRESET_MEN_TO_WOMEN:
                    pitch = 4.0f;
                    break;
                case ZEGO_VOICE_CHANGER_PRESET_WOMEN_TO_CHILD:
                    pitch = 6.0f;
                    break;
                case ZEGO_VOICE_CHANGER_PRESET_WOMEN_TO_MEN:
                    pitch = -3.0f;
                    break;
                default:
                    pitch = 0.0f;
                    break;
                }
            }

        };

        /**
         * Audio reverberation parameters
         *
         * Developers can use the SDK's built-in presets to change the parameters of the reverb.
         */
        struct ZegoReverbParam
        {
            /** Reverb Damping, range [0.0, 2.0], controls the attenuation of the reverb, the higher the damping, the higher the attenuation. */
            float damping;

            /** Dry/wet ratio, the range is greater than or equal to 0.0, to control the ratio between reverberation, direct sound and early reflections; dry part is set to 1 by default; the smaller the dry/wet ratio, the larger the wet ratio, the stronger the reverberation effect. */
            float dryWetRatio;

            /** Echo, in the range [0.0, 0.5], to control the trailing length of the reverb. */
            float reverberance;

            /** Room size, in the range [0.0, 1.0], to control the size of the "room" in which the reverb is generated, the larger the room, the stronger the reverb. */
            float roomSize;

            ZegoReverbParam(ZegoReverbPreset preset = ZEGO_REVERB_PRESET_NONE){
                switch(preset) {
                case ZEGO_REVERB_PRESET_SOFT_ROOM:
                    roomSize = 0.6f;
                    reverberance = 0.03f;
                    damping = 0.25f;
                    dryWetRatio = 2.5f;
                    break;
                case ZEGO_REVERB_PRESET_LARGE_ROOM:
                    roomSize = 0.65f;
                    reverberance = 0.03f;
                    damping = 0.25f;
                    dryWetRatio = 0.94f;
                    break;
                case ZEGO_REVERB_PRESET_CONCER_HALL:
                    roomSize = 0.8f;
                    reverberance = 0.03f;
                    damping = 0.25f;
                    dryWetRatio = 1.1f;
                    break;
                case ZEGO_REVERB_PRESET_VALLEY:
                    roomSize = 0.85f;
                    reverberance = 0.03f;
                    damping = 0.25f;
                    dryWetRatio = 0.92f;
                    break;
                default:
                    roomSize = 0.0f;
                    reverberance = 0.0f;
                    damping = 0.0f;
                    dryWetRatio = 0.0f;
                    break;
                }
            }

        };

        /**
         * User object
         *
         * Configure user ID and username to identify users in the room.
         * Note that the userID must be unique under the same appID, otherwise mutual kicks out will occur.
         * It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
         */
        struct ZegoUser
        {
            /** User ID, a string with a maximum length of 64 bytes or less. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
            std::string userID;

            /** User Name, a string with a maximum length of 256 bytes or less */
            std::string userName;

            ZegoUser(){
            }

            ZegoUser(std::string userID, std::string userName):userID(userID),userName(userName){
            }

        };

        /**
         * Stream object
         *
         * Identify an stream object
         */
        struct ZegoStream
        {
            /** User object instance */
            ZegoUser user;

            /** Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
            std::string streamID;

            /** Stream extra info */
            std::string extraInfo;

        };

        /**
         * Room extra information
         */
        struct ZegoRoomExtraInfo
        {
            /** The key of the room extra information. */
            std::string key;

            /** The value of the room extra information. */
            std::string value;

            /** The user who update the room extra information. */
            ZegoUser updateUser;

            /** Update time of the room extra information, UNIX timestamp, in milliseconds. */
            unsigned long long updateTime;

        };

        /**
         * View related coordinates
         */
        struct ZegoRect
        {
            /** The horizontal offset from the top-left corner */
            int x;

            /** The vertical offset from the top-left corner */
            int y;

            /** The width of the rectangle */
            int width;

            /** The height of the rectangle */
            int height;

            ZegoRect() : x(0), y(0), width(0), height(0){
            }

            ZegoRect(int x, int y, int w, int h) : x(x), y(y), width(w), height(h){
            }

        };

        /**
         * View object
         *
         * Configure view object, view Mode, background color
         */
        struct ZegoCanvas
        {
            /** View object */
            void * view;

            /** View mode, default is ZegoViewModeAspectFit */
            ZegoViewMode viewMode;

            /** Background color, the format is 0xRRGGBB, default is black, which is 0x000000 */
            int backgroundColor;

            ZegoCanvas(void *view=nullptr, ZegoViewMode viewMode=ZEGO_VIEW_MODE_ASPECT_FIT, int backgroundColor=0x000000):view(view),viewMode(viewMode),backgroundColor(backgroundColor){
            }

        };

        /**
         * Published stream quality information
         *
         * Audio and video parameters and network quality, etc.
         */
        struct ZegoPublishStreamQuality
        {
            /** Video capture frame rate. The unit of frame rate is f/s */
            double videoCaptureFPS;

            /** Video encoding frame rate. The unit of frame rate is f/s */
            double videoEncodeFPS;

            /** Video transmission frame rate. The unit of frame rate is f/s */
            double videoSendFPS;

            /** Video bit rate in kbps */
            double videoKBPS;

            /** Audio capture frame rate. The unit of frame rate is f/s */
            double audioCaptureFPS;

            /** Audio transmission frame rate. The unit of frame rate is f/s */
            double audioSendFPS;

            /** Audio bit rate in kbps */
            double audioKBPS;

            /** Local to server delay, in milliseconds */
            int rtt;

            /** Packet loss rate, in percentage, 0.0 ~ 1.0 */
            double packetLostRate;

            /** Published stream quality level */
            ZegoStreamQualityLevel level;

            /** Whether to enable hardware encoding */
            bool isHardwareEncode;

            /** Total number of bytes sent, including audio, video, SEI */
            double totalSendBytes;

            /** Number of audio bytes sent */
            double audioSendBytes;

            /** Number of video bytes sent */
            double videoSendBytes;

        };

        /**
         * CDN config object
         *
         * Includes CDN URL and authentication parameter string
         */
        struct ZegoCDNConfig
        {
            /** CDN URL */
            std::string url;

            /** Auth param of URL */
            std::string authParam;

        };

        /**
         * Relay to CDN info
         *
         * Including the URL of the relaying CDN, relaying state, etc.
         */
        struct ZegoStreamRelayCDNInfo
        {
            /** URL of publishing stream to CDN */
            std::string url;

            /** State of relaying to CDN */
            ZegoStreamRelayCDNState state;

            /** Reason for relay state changed */
            ZegoStreamRelayCDNUpdateReason updateReason;

            /** The timestamp when the state changed, UNIX timestamp, in milliseconds. */
            unsigned long long stateTime;

        };

        /**
         * Advanced player configuration
         *
         * Configure playing stream CDN configuration, video layer
         */
        struct ZegoPlayerConfig
        {
            /** The CDN configuration for playing stream. If set, the stream is play according to the URL instead of the streamID. After that, the streamID is only used as the ID of SDK internal callback. */
            ZegoCDNConfig * cdnConfig;

            /** Set the video layer for playing the stream */
            ZegoPlayerVideoLayer videoLayer;

            ZegoPlayerConfig(): cdnConfig(nullptr), videoLayer(ZEGO_PLAYER_VIDEO_LAYER_AUTO){
            }

        };

        /**
         * Played stream quality information
         *
         * Audio and video parameters and network quality, etc.
         */
        struct ZegoPlayStreamQuality
        {
            /** Video reception frame rate. The unit of frame rate is f/s */
            double videoRecvFPS;

            /** Video decoding frame rate. The unit of frame rate is f/s */
            double videoDecodeFPS;

            /** Video rendering frame rate. The unit of frame rate is f/s */
            double videoRenderFPS;

            /** Video bit rate in kbps */
            double videoKBPS;

            /** Audio reception frame rate. The unit of frame rate is f/s */
            double audioRecvFPS;

            /** Audio decoding frame rate. The unit of frame rate is f/s */
            double audioDecodeFPS;

            /** Audio rendering frame rate. The unit of frame rate is f/s */
            double audioRenderFPS;

            /** Audio bit rate in kbps */
            double audioKBPS;

            /** Server to local delay, in milliseconds */
            int rtt;

            /** Packet loss rate, in percentage, 0.0 ~ 1.0 */
            double packetLostRate;

            /** Delay from peer to peer, in milliseconds */
            int peerToPeerDelay;

            /** Packet loss rate from peer to peer, in percentage, 0.0 ~ 1.0 */
            double peerToPeerPacketLostRate;

            /** Published stream quality level */
            ZegoStreamQualityLevel level;

            /** Delay after the data is received by the local end, in milliseconds */
            int delay;

            /** Whether to enable hardware decoding */
            bool isHardwareDecode;

            /** Total number of bytes received, including audio, video, SEI */
            double totalRecvBytes;

            /** Number of audio bytes received */
            double audioRecvBytes;

            /** Number of video bytes received */
            double videoRecvBytes;

        };

        /**
         * Device Info
         *
         * Including device ID and name
         */
        struct ZegoDeviceInfo
        {
            /** Device ID */
            std::string deviceID;

            /** Device name */
            std::string deviceName;

        };

        /**
         * Mix stream audio configuration
         *
         * Configure video frame rate, bitrate, and resolution for mixer task
         */
        struct ZegoMixerAudioConfig
        {
            /** Audio bitrate in kbps, default is 48 kbps, cannot be modified after starting a mixer task */
            int bitrate;

            /** Audio channel, default is Mono */
            ZegoAudioChannel channel;

            /** codec ID, default is ZegoAudioCodecIDDefault */
            ZegoAudioCodecID codecID;

            ZegoMixerAudioConfig():bitrate(48), channel(ZEGO_AUDIO_CHANNEL_MONO), codecID(ZEGO_AUDIO_CODEC_ID_DEFAULT){
            }

            ZegoMixerAudioConfig(int bitrate, ZegoAudioChannel channel, ZegoAudioCodecID codecID): bitrate(bitrate), channel(channel), codecID(codecID){
            }

        };

        /**
         * Mix stream video config object
         *
         * Configure video frame rate, bitrate, and resolution for mixer task
         */
        struct ZegoMixerVideoConfig
        {
            /** Video resolution width */
            int width;

            /** Video resolution height */
            int height;

            /** Video FPS, cannot be modified after starting a mixer task */
            int fps;

            /** Video bitrate in kbps */
            int bitrate;

            ZegoMixerVideoConfig(): width(640), height(360), fps(15), bitrate(600){
            }

            ZegoMixerVideoConfig(int width, int height, int fps, int bitrate): width(width), height(height), fps(fps), bitrate(bitrate){
            }

        };

        /**
         * Mixer input
         *
         * Configure the mix stream input stream ID, type, and the layout
         */
        struct ZegoMixerInput
        {
            /** Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
            std::string streamID;

            /** Mix stream content type */
            ZegoMixerInputContentType contentType;

            /** Stream layout */
            ZegoRect layout;

            /** If enable soundLevel in mix stream task, an unique soundLevelID is need for every stream */
            unsigned int soundLevelID;

            ZegoMixerInput() : contentType(ZEGO_MIXER_INPUT_CONTENT_TYPE_VIDEO), soundLevelID(0){
            }

            ZegoMixerInput(std::string streamID, ZegoMixerInputContentType contentType, ZegoRect layout, unsigned int soundLevelID): streamID(streamID), contentType(contentType), layout(layout), soundLevelID(soundLevelID){
            }

        };

        /**
         * Mixer output object
         *
         * Configure mix stream output target URL or stream ID
         */
        struct ZegoMixerOutput
        {
            /** Mix stream output target, URL or stream ID, if set to be URL format, only RTMP URL surpported, for example rtmp://xxxxxxxx */
            std::string target;

            ZegoMixerOutput(){
            }

            ZegoMixerOutput(std::string target) :target(target){
            }

        };

        /**
         * Watermark object
         *
         * Configure a watermark image URL and the layout of the watermark in the screen
         */
        struct ZegoWatermark
        {
            /** Watermark image URL, only png or jpg format surpport. */
            std::string imageURL;

            /** Watermark image layout */
            ZegoRect layout;

            ZegoWatermark(){
            }

            ZegoWatermark(std::string imageURL, ZegoRect layout) :imageURL(imageURL), layout(layout){
            }

        };

        /**
         * Mix stream task object
         *
         * This class is the configuration class of the mixing stream task. When a mixing stream task is requested to the ZEGO audio and video cloud, the configuration of the mixing task is required.
         * This class describes the detailed configuration information of this mixed task.
         */
        struct ZegoMixerTask
        {
            /** The task ID of the task */
            std::string taskID;

            /** The audio config of the task */
            ZegoMixerAudioConfig audioConfig;

            /** The audio config of the task */
            ZegoMixerVideoConfig videoConfig;

            /** The input list of the task */
            std::vector<ZegoMixerInput> inputList;

            /** The output list of the task */
            std::vector<ZegoMixerOutput> outputList;

            /** The watermark of the task */
            ZegoWatermark* watermark;

            /** The background image URL of the task */
            std::string backgroundImageURL;

            /** Enable or disable sound level callback for the task. If enabled, then the remote player can get the soundLevel of every stream in the inputlist by [onMixerSoundLevelUpdate] callback. */
            bool enableSoundLevel;

            ZegoMixerTask(std::string taskID=""): taskID(taskID), watermark(nullptr){
            }

        };

        /**
         * Broadcast message info
         *
         * The received object of the room broadcast message, including the message content, message ID, sender, sending time
         */
        struct ZegoBroadcastMessageInfo
        {
            /** message content */
            std::string message;

            /** message id */
            unsigned long long messageID;

            /** Message send time, UNIX timestamp, in milliseconds. */
            unsigned long long sendTime;

            /** Message sender */
            ZegoUser fromUser;

        };

        /**
         * Barrage message info
         *
         * The received object of the room barrage message, including the message content, message ID, sender, sending time
         */
        struct ZegoBarrageMessageInfo
        {
            /** message content */
            std::string message;

            /** message id */
            std::string messageID;

            /** Message send time, UNIX timestamp, in milliseconds. */
            unsigned long long sendTime;

            /** Message sender */
            ZegoUser fromUser;

        };

        /**
         * Object for video frame fieldeter
         *
         * Including video frame format, width and height, etc.
         */
        struct ZegoVideoFrameParam
        {
            /** Video frame format */
            ZegoVideoFrameFormat format;

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
        struct ZegoVideoEncodedFrameParam
        {
            /** Video encoded frame format */
            ZegoVideoEncodedFrameFormat format;

            /** Whether it is a keyframe */
            bool isKeyFrame;

            /** Video frame width */
            int width;

            /** Video frame height */
            int height;

            /** SEI data */
            const unsigned char* SEIData;

            /** Length of the SEI data */
            unsigned int SEIDataLength;

        };

        /**
         * Parameter object for audio frame
         *
         * Including the sampling rate and channel of the audio frame
         */
        struct ZegoAudioFrameParam
        {
            /** Sampling Rate */
            ZegoAudioSampleRate sampleRate;

            /** Audio channel, default is Mono */
            ZegoAudioChannel channel;

        };

        /**
         * Audio configuration
         *
         * Configure audio bitrate, audio channel, audio encoding for publishing stream
         */
        struct ZegoAudioConfig
        {
            /** Audio bitrate in kbps, default is 48 kbps. The settings before and after publishing stream can be effective */
            int bitrate;

            /** Audio channel, default is Mono. The setting only take effect before publishing stream */
            ZegoAudioChannel channel;

            /** codec ID, default is ZegoAudioCodecIDDefault. The setting only take effect before publishing stream */
            ZegoAudioCodecID codecID;

            ZegoAudioConfig(ZegoAudioConfigPreset preset = ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY){
                codecID = ZEGO_AUDIO_CODEC_ID_DEFAULT;
                switch (preset) {
                case ZEGO_AUDIO_CONFIG_PRESET_BASIC_QUALITY:
                    bitrate = 16;
                    channel = ZEGO_AUDIO_CHANNEL_MONO;
                    break;
                case ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY:
                    bitrate = 48;
                    channel = ZEGO_AUDIO_CHANNEL_MONO;
                    break;
                case ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY_STEREO:
                    bitrate = 56;
                    channel = ZEGO_AUDIO_CHANNEL_STEREO;
                    break;
                case ZEGO_AUDIO_CONFIG_PRESET_HIGH_QUALITY:
                    bitrate = 128;
                    channel = ZEGO_AUDIO_CHANNEL_MONO;
                    break;
                case ZEGO_AUDIO_CONFIG_PRESET_HIGH_QUALITY_STEREO:
                    bitrate = 192;
                    channel = ZEGO_AUDIO_CHANNEL_STEREO;
                    break;
                }
            }

        };

        /**
         * audio mixing data
         */
        struct ZegoAudioMixingData
        {
            /** Audio PCM data that needs to be mixed into the stream */
            unsigned char* audioData;

            /** the length of the audio PCM data that needs to be mixed into the stream. If this is no enough data left to mix as audioDataLength, then you can set audioDataLength = 0. */
            unsigned int audioDataLength;

            /** Audio data attributes, including sample rate and number of channels. Currently supports 16k 32k 44.1k 48k sampling rate, mono or stereo channel, 16-bit deep PCM data. Developers need to explicitly specify audio data attributes, otherwise mixing will not take effect. */
            ZegoAudioFrameParam param;

            /** SEI data, used to transfer custom data. When audioData is null, SEIData will not be sent */
            unsigned char* SEIData;

            /** SEI data length */
            unsigned int SEIDataLength;

        };

        /**
         * Customize the audio processing configuration object
         *
         * Including custom audio acquisition type, sampling rate, channel number, sampling number and other parameters
         */
        struct ZegoCustomAudioProcessConfig
        {
            /** Sampling rate, the sampling rate of the input data expected by the audio pre-processing module in App. If 0, the default is the SDK internal sampling rate. */
            ZegoAudioSampleRate sampleRate;

            /** Number of sound channels, the expected number of sound channels for input data of the audio pre-processing module in App. If 0, the default is the number of internal channels in the SDK */
            ZegoAudioChannel channel;

            /** The number of samples required to encode a frame; When encode = false, if samples = 0, the SDK will use the internal sample number, and the SDK will pass the audio data to the external pre-processing module. If the samples! = 0 (the effective value of samples is between [160, 2048]), and the SDK will send audio data to the external preprocessing module that sets the length of sample number. Encode = true, the number of samples for a frame of AAC encoding can be set as (480/512/1024/1960/2048) */
            int samples;

        };

        /**
         * Record config
         */
        struct ZegoDataRecordConfig
        {
            /** The path to save the recording file, absolute path, need to include the file name, the file name need to specify the suffix, currently only support .mp4 or .flv, if multiple recording for the same path, will overwrite the file with the same name. */
            std::string filePath;

            /** Type of recording media */
            ZegoDataRecordType recordType;

        };

        /**
         * File recording progress
         */
        struct ZegoDataRecordProgress
        {
            /** Current recording duration in milliseconds */
            unsigned long long duration;

            /** Current recording file size in byte */
            unsigned long long currentFileSize;

        };

        /**
         * Callback for asynchronous destruction completion
         *
         * In general, developers do not need to listen to this callback.
         */
        using ZegoDestroyCompletionCallback = std::function<void ()>;


        /**
         * Callback for setting room extra information
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         */
        using ZegoRoomSetRoomExtraInfoCallback = std::function<void (int errorCode)>;


        /**
         * Callback for setting stream extra information
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         */
        using ZegoPublisherSetStreamExtraInfoCallback = std::function<void (int errorCode)>;


        /**
         * Callback for add/remove CDN URL
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         */
        using ZegoPublisherUpdateCdnUrlCallback = std::function<void (int errorCode)>;


        /**
         * Results of starting a mixer task
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         * @param extendedData Extended Information
         */
        using ZegoMixerStartCallback = std::function<void (int errorCode, std::string extendedData)>;


        /**
         * Results of stoping a mixer task
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         */
        using ZegoMixerStopCallback = std::function<void (int errorCode)>;


        /**
         * Callback for sending broadcast messages
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         * @param messageID ID of this message
         */
        using ZegoIMSendBroadcastMessageCallback = std::function<void (int errorCode, unsigned long long messageID)>;


        /**
         * Callback for sending barrage message
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         * @param messageID ID of this message
         */
        using ZegoIMSendBarrageMessageCallback = std::function<void (int errorCode, std::string messageID)>;


        /**
         * Callback for sending custom command
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         */
        using ZegoIMSendCustomCommandCallback = std::function<void (int errorCode)>;


        /**
         * Callback for media player loads resources
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         */
        using ZegoMediaPlayerLoadResourceCallback = std::function<void (int errorCode)>;


        /**
         * Callback for media player seek to playback progress
         *
         * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
         */
        using ZegoMediaPlayerSeekToCallback = std::function<void (int errorCode)>;



        using ZegoAudioSpectrum = std::vector<float>;
        using ZegoView = void*;

    }
}

#endif /* __ZEGOEXPRESSDEFINES_H__ */
