
#ifndef __ZEGOEXPRESSINTERFACE_H__
#define __ZEGOEXPRESSINTERFACE_H__

#include "ZegoExpressDefines.h"
#include "ZegoExpressErrorCode.h"
#include "ZegoExpressEventHandler.h"

namespace ZEGO {
    namespace EXPRESS {

        class IZegoMediaPlayer;


        class IZegoExpressEngine
        {
        protected:

            virtual ~IZegoExpressEngine() {}

        public:

            /**
             * Sets up the event notification callbacks that need to be handled. If the eventHandler is set to [nullptr], all the callbacks set previously will be cleared.
             *
             * Invoke this function will **OVERRIDE** the handler set in [createEngine] or the handler set by the last call to this function.
             *
             * @param eventHandler Event notification callback. Developers should override callback related methods to focus on specific notifications based on their own business scenarios. The main callback methods of SDK are in [IZegoEventHandler].
             */
            virtual void setEventHandler(std::shared_ptr<IZegoEventHandler> eventHandler) = 0;

            /**
             * Uploads logs to the ZEGO server.
             *
             * By default, SDK creates and prints log files in the app's default directory. Each log file defaults to a maximum of 5MB. Three log files are written over and over in a circular fashion. When calling this interface, SDK will auto package and upload the log files to the ZEGO server.
             * Developers can provide a business “feedback” channel in the app. When users feedback problems, they can call this interface to upload the local log information of SDK to help locate user problems.
             * The API is valid for the entire life cycle of the SDK.
             */
            virtual void uploadLog() = 0;

            /**
             * Turns on/off verbose debugging and sets up the log language.
             *
             * The debug switch is set to on and the language is English by default.
             *
             * @param enable Detailed debugging information switch
             * @param language Debugging information language
             */
            virtual void setDebugVerbose(bool enable, ZegoLanguage language) = 0;

            /**
             * Logs in to a room. You must log in to a room before publishing or playing streams.
             *
             * Different users who log in to the same room can get room related notifications in the same room (eg [onRoomUserUpdate], [onRoomStreamUpdate], etc.), and users in one room cannot receive room signaling notifications in another room.
             * Messages sent in one room (eg apis [setStreamExtraInfo], [sendBroadcastMessage], [sendBarrageMessage], [sendCustomCommand], etc.) cannot be received callback ((eg [onRoomStreamExtraInfoUpdate], [onIMRecvBroadcastMessage], [onIMRecvBarrageMessage], [onIMRecvCustomCommand], etc) in other rooms. Currently, SDK does not provide the ability to send messages across rooms. Developers can integrate the SDK of third-party IM to achieve.
             * SDK supports startPlayingStream audio and video streams from different rooms under the same appID, that is, startPlayingStream audio and video streams across rooms. Since ZegoExpressEngine's room related callback notifications are based on the same room, when developers want to startPlayingStream streams across rooms, developers need to maintain related messages and signaling notifications by themselves.
             * If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally. You can get the current connection status of the local room by listening to the [onRoomStateUpdate] callback method, and other users in the same room will receive [onRoomUserUpdate] callback notification.
             * It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
             *
             * @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
             * @param user User object instance, configure userID, userName. Note that the userID needs to be globally unique with the same appID, otherwise the user who logs in later will kick out the user who logged in first.
             */
            virtual void loginRoom(const std::string& roomID, ZegoUser user) = 0;

            /**
             * Logs in to a room with advanced room configurations. You must log in to a room before publishing or playing streams.
             *
             * To prevent the app from being impersonated by a malicious user, you can add authentication before logging in to the room, that is, the [token] parameter in the ZegoRoomConfig object passed in by the [config] parameter.
             * Different users who log in to the same room can get room related notifications in the same room (eg [onRoomUserUpdate], [onRoomStreamUpdate], etc.), and users in one room cannot receive room signaling notifications in another room.
             * Messages sent in one room (eg apis [setStreamExtraInfo], [sendBroadcastMessage], [sendBarrageMessage], [sendCustomCommand], etc.) cannot be received callback ((eg [onRoomStreamExtraInfoUpdate], [onIMRecvBroadcastMessage], [onIMRecvBarrageMessage], [onIMRecvCustomCommand], etc) in other rooms. Currently, SDK does not provide the ability to send messages across rooms. Developers can integrate the SDK of third-party IM to achieve.
             * SDK supports startPlayingStream audio and video streams from different rooms under the same appID, that is, startPlayingStream audio and video streams across rooms. Since ZegoExpressEngine's room related callback notifications are based on the same room, when developers want to startPlayingStream streams across rooms, developers need to maintain related messages and signaling notifications by themselves.
             * If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally. You can get the current connection status of the local room by listening to the [onRoomStateUpdate] callback method, and other users in the same room will receive [onRoomUserUpdate] callback notification.
             * It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
             *
             * @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
             * @param user User object instance, configure userID, userName. Note that the userID needs to be globally unique with the same appID, otherwise the user who logs in later will kick out the user who logged in first.
             * @param config Advanced room configuration
             */
            virtual void loginRoom(const std::string& roomID, ZegoUser user, ZegoRoomConfig config) = 0;

            /**
             * Logs in multi room
             *
             * You must log in the main room with [loginRoom] before invoke this interface to logging in to multi room.
             * Currently supports logging into 1 main room and 1 multi room at the same time.
             * When logging out, you must log out of the multi room before logging out of the main room.
             * User can only publish the stream in the main room, but can play the stream in the main room and multi room at the same time, and can receive the signaling and callback in each room.
             * The advantage of multi room is that you can login another room without leaving the current room, receive signaling and callback from another room, and play streams from another room.
             * To prevent the app from being impersonated by a malicious user, you can add authentication before logging in to the room, that is, the [token] parameter in the ZegoRoomConfig object passed in by the [config] parameter.
             * Different users who log in to the same room can get room related notifications in the same room (eg [onRoomUserUpdate], [onRoomStreamUpdate], etc.), and users in one room cannot receive room signaling notifications in another room.
             * Messages sent in one room (eg apis [setStreamExtraInfo], [sendBroadcastMessage], [sendBarrageMessage], [sendCustomCommand], etc.) cannot be received callback ((eg [onRoomStreamExtraInfoUpdate], [onIMRecvBroadcastMessage], [onIMRecvBarrageMessage], [onIMRecvCustomCommand], etc) in other rooms. Currently, SDK does not provide the ability to send messages across rooms. Developers can integrate the SDK of third-party IM to achieve.
             * SDK supports startPlayingStream audio and video streams from different rooms under the same appID, that is, startPlayingStream audio and video streams across rooms. Since ZegoExpressEngine's room related callback notifications are based on the same room, when developers want to startPlayingStream streams across rooms, developers need to maintain related messages and signaling notifications by themselves.
             * If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally. You can get the current connection status of the local room by listening to the [onRoomStateUpdate] callback method, and other users in the same room will receive [onRoomUserUpdate] callback notification.
             * It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
             *
             * @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
             * @param config Advanced room configuration
             */
            virtual void loginMultiRoom(const std::string& roomID, ZegoRoomConfig* config = nullptr) = 0;

            /**
             * Logs out of a room.
             *
             * Exiting the room will stop all publishing and playing streams for user, and then SDK will auto stop local preview UI. After calling this interface, you will receive [onRoomStateUpdate] callback notification successfully exits the room, while other users in the same room will receive the [onRoomUserUpdate] callback notification(On the premise of enabling isUserStatusNotify configuration).
             *
             * @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
             */
            virtual void logoutRoom(const std::string& roomID) = 0;

            /**
             * Set room extra infomation
             *
             * @param roomID Room ID.
             * @param key key of the extra info.
             * @param value value if the extra info.
             * @param callback Callback for setting room extra information
             */
            virtual void setRoomExtraInfo(const std::string& roomID, const std::string& key, const std::string& value, ZegoRoomSetRoomExtraInfoCallback callback) = 0;

            /**
             * Starts publishing a stream (for the specified channel). You can call this API to publish a second stream.
             *
             * This interface allows users to publish their local audio and video streams to the ZEGO real-time audio and video cloud. Other users in the same room can use the streamID to play the audio and video streams for intercommunication.
             * Before you start to publish the stream, you need to join the room first by calling [loginRoom]. Other users in the same room can get the streamID by monitoring the [onRoomStreamUpdate] event callback after the local user publishing stream successfully.
             * In the case of poor network quality, user publish may be interrupted, and the SDK will attempt to reconnect. You can learn about the current state and error information of the stream published by monitoring the [onPublisherStateUpdate] event.
             *
             * @param streamID Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID. If in the same AppID, different users publish each stream and the stream ID is the same, which will cause the user to publish the stream failure. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
             * @param channel Publish stream channel
             */
            virtual void startPublishingStream(const std::string& streamID, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Stops publishing a stream (for the specified channel).
             *
             * This interface allows the user to stop sending local audio and video streams and end the call.
             * If the user has initiated publish flow, this interface must be called to stop the publish of the current stream before publishing the new stream (new streamID), otherwise the new stream publish will return a failure.
             * After stopping streaming, the developer should stop the local preview based on whether the business situation requires it.
             * Use this API to stop publishing stream of aux channel.
             *
             * @param channel Publish stream channel
             */
            virtual void stopPublishingStream(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sets the extra information of the stream being published (for the specified channel).
             *
             * User this interface to set the extra info of the stream, the result will be notified via the [ZegoPublisherSetStreamExtraInfoCallback].
             * The stream extra information is an extra information identifier of the stream ID. Unlike the stream ID, which cannot be modified during the publishing process, the stream extra information can be modified midway through the stream corresponding to the stream ID.
             * Developers can synchronize variable content related to stream IDs based on stream additional information.
             *
             * @param extraInfo Stream extra information, a string of up to 1024 characters.
             * @param callback Set stream extra information execution result notification
             * @param channel Publish stream channel
             */
            virtual void setStreamExtraInfo(const std::string& extraInfo, ZegoPublisherSetStreamExtraInfoCallback callback, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Starts/Updates the local video preview (for the specified channel).
             *
             * The user can see his own local image by calling this interface. The preview function does not require you to log in to the room or publish the stream first. But after exiting the room, SDK internally actively stops previewing by default.
             * Local view and preview modes can be updated by calling this interface again.
             * You can set the mirror mode of the preview by calling the [setVideoMirrorMode] interface. The default preview setting is image mirrored.
             * When this api is called, the audio and video engine module inside SDK will start really, and it will start to try to collect audio and video. In addition to calling this api normally to preview the local screen, developers can also pass [nullptr] to the canvas parameter, in conjunction with ZegoExpressEngine's sound wave function, in order to achieve the purpose of detecting whether the audio equipment is working properly before logging in to the room.
             *
             * @param canvas The view used to display the preview image. If the view is set to nullptr, no preview will be made.
             * @param channel Publish stream channel
             */
            virtual void startPreview(ZegoCanvas* canvas, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Stops the local video preview (for the specified channel).
             *
             * This api can be called to stop previewing when there is no need to see the preview locally.
             *
             * @param channel Publish stream channel
             */
            virtual void stopPreview(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sets up the video configurations (for the specified channel).
             *
             * This api can be used to set the video frame rate, bit rate, video capture resolution, and video encoding output resolution. If you do not call this api, the default resolution is 360p, the bit rate is 600 kbps, and the frame rate is 15 fps.
             * It is necessary to set the relevant video configuration before publishing the stream, and only support the modification of the encoding resolution and the bit rate after publishing the stream.
             * Developers should note that the wide and high resolution of the mobile end is opposite to the wide and high resolution of the PC. For example, in the case of 360p, the resolution of the mobile end is 360x640, and the resolution of the PC end is 640x360.
             *
             * @param config Video configuration, the SDK provides a common setting combination of resolution, frame rate and bit rate, they also can be customized.
             * @param channel Publish stream channel
             */
            virtual void setVideoConfig(ZegoVideoConfig config, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Gets the current video configurations (for the specified channel).
             *
             * This api can be used to get the specified publish channel's current video frame rate, bit rate, video capture resolution, and video encoding output resolution.
             *
             * @param channel Publish stream channel
             * @return Video configuration object
             */
            virtual ZegoVideoConfig getVideoConfig(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sets the video mirroring mode (for the specified channel).
             *
             * This interface can be called to set whether the local preview video and the published video have mirror mode enabled.
             *
             * @param mirrorMode Mirror mode for previewing or publishing the stream
             * @param channel Publish stream channel
             */
            virtual void setVideoMirrorMode(ZegoVideoMirrorMode mirrorMode, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sets the video orientation (for the specified channel).
             *
             * This interface sets the orientation of the video. The captured image is rotated 90, 180 or 270 degrees counterclockwise compared to the forward direction of the phone. After rotation, it is automatically adjusted to match the encoded image resolution.
             *
             * @param orientation Video orientation
             * @param channel Publish stream channel
             */
            virtual void setAppOrientation(ZegoOrientation orientation, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sets up the audio configurations.
             *
             * You can set the combined value of the audio codec, bit rate, and audio channel through this interface. If this interface is not called, the default is standard quality mode. Should be used before publishing.
             * If the preset value cannot meet the developer's scenario, the developer can set the parameters according to the business requirements.
             *
             * @param config Audio config
             */
            virtual void setAudioConfig(ZegoAudioConfig config) = 0;

            /**
             * Gets the current audio configurations.
             *
             * You can get the current audio codec, bit rate, and audio channel through this interface.
             *
             * @return Audio config
             */
            virtual ZegoAudioConfig getAudioConfig() = 0;

            /**
             * Stops or resumes sending the audio part of a stream (for the specified channel).
             *
             * This interface can be called when publishing the stream to publish only the video stream without publishing the audio. The SDK still collects and processes the audio, but does not send the audio data to the network. It can be set before publishing.
             * If you stop sending audio streams, the remote user that play stream of local user publishing stream can receive `Mute` status change notification by monitoring [onRemoteMicStateUpdate] callbacks,
             *
             * @param mute Whether to stop sending audio streams, true means that only the video stream is sent without sending the audio stream, and false means that the audio and video streams are sent simultaneously. The default is false.
             * @param channel Publish stream channel
             */
            virtual void mutePublishStreamAudio(bool mute, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Stops or resumes sending the video part of a stream (for the specified channel).
             *
             * When publishing the stream, this interface can be called to publish only the audio stream without publishing the video stream. The local camera can still work normally, and can normally capture, preview and process the video picture, but does not send the video data to the network. It can be set before publishing.
             * If you stop sending video streams locally, the remote user that play stream of local user publishing stream can receive `Mute` status change notification by monitoring [onRemoteCameraStateUpdate] callbacks,
             *
             * @param mute Whether to stop sending video streams, true means that only the audio stream is sent without sending the video stream, and false means that the audio and video streams are sent at the same time. The default is false.
             * @param channel Publish stream channel
             */
            virtual void mutePublishStreamVideo(bool mute, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Enables or disables traffic control.
             *
             * Traffic control enables SDK to dynamically adjust the bitrate of audio and video streaming according to its own and peer current network environment status.
             * Automatically adapt to the current network environment and fluctuations, so as to ensure the smooth publishing of stream.
             *
             * @param enable Whether to enable traffic control. The default is ture.
             * @param property Adjustable property of traffic control, bitmask format. Should be one or the combinations of [ZegoTrafficControlProperty] enumeration. [AdaptiveFPS] as default.
             */
            virtual void enableTrafficControl(bool enable, int property) = 0;

            /**
             * Sets the minimum video bitrate for traffic control.
             *
             * Set how should SDK send video data when the network conditions are poor and the minimum video bitrate cannot be met.
             * When this api is not called, the SDK will automatically adjust the sent video data frames according to the current network uplink conditions by default.
             *
             * @param bitrate Minimum video bitrate (kbps)
             * @param mode Video sending mode below the minimum bitrate.
             */
            virtual void setMinVideoBitrateForTrafficControl(int bitrate, ZegoTrafficControlMinVideoBitrateMode mode) = 0;

            /**
             * Sets the audio recording volume for stream publishing.
             *
             * This interface is used to set the audio collection volume. The local user can control the volume of the audio stream sent to the far end. It can be set before publishing.
             *
             * @param volume Volume percentage. The range is 0 to 200. Default value is 100.
             */
            virtual void setCaptureVolume(int volume) = 0;

            /**
             * Adds a target CDN URL to which the stream will be relayed from ZEGO's cloud streaming server.
             *
             * You can call this api to publish the audio and video streams that have been published to the ZEGO real-time audio and video cloud to a custom CDN content distribution network that has high latency but supports high concurrent playing stream.
             * Because this called api is essentially a dynamic relay of the audio and video streams published to the ZEGO audio and video cloud to different CDNs, this api needs to be called after the audio and video stream is published to ZEGO real-time cloud successfully.
             * Since ZEGO's audio and video cloud service itself can be configured to support CDN(content distribution networks), this api is mainly used by developers who have CDN content distribution services themselves.
             * You can use ZEGO's CDN audio and video streaming content distribution service at the same time by calling this interface and then use the developer who owns the CDN content distribution service.
             * This interface supports dynamic relay to the CDN content distribution network, so developers can use this api as a disaster recovery solution for CDN content distribution services.
             * When the [enablePublishDirectToCDN] api is set to true to publish the stream straight to the CDN, then calling this interface will have no effect.
             *
             * @param streamID Stream ID
             * @param targetURL CDN relay address, supported address format is rtmp.
             * @param callback The execution result notification of the relay CDN operation, and proceed to the next step according to the execution result.
             */
            virtual void addPublishCdnUrl(const std::string& streamID, const std::string& targetURL, ZegoPublisherUpdateCdnUrlCallback callback) = 0;

            /**
             * Deletes the specified CDN URL, which is used for relaying streams from ZEGO's cloud streaming server to CDN.
             *
             * This api is called when a CDN relayed address has been added and needs to stop propagating the stream to the CDN.
             * This api does not stop publishing audio and video stream to the ZEGO audio and video cloud.
             *
             * @param streamID Stream ID
             * @param targetURL CDN relay address, supported address format rtmp.
             * @param callback Remove CDN relay result notifications
             */
            virtual void removePublishCdnUrl(const std::string& streamID, const std::string& targetURL, ZegoPublisherUpdateCdnUrlCallback callback) = 0;

            /**
             * Whether to publish streams directly from the client to CDN without passing through ZEGO's cloud streaming server (for the specified channel).
             *
             * This api needs to be set before start publishing stream.
             * After calling this api to publish the audio and video stream directly to the CDN, calling [addPublishCdnUrl] and [removePublishCdnUrl] to dynamically repost to the CDN no longer takes effect, because these two API relay or stop the audio and video stream from the ZEGO real-time audio and video cloud If it is published to CDN, if the direct audio and video stream is directly published to the CDN, the audio and video stream cannot be dynamically relay to the CDN through the ZEGO real-time audio and video cloud.
             *
             * @param enable Whether to enable direct publish CDN, true: enable direct publish CDN, false: disable direct publish CDN
             * @param config CDN configuration, if nullptr, use Zego's background default configuration
             * @param channel Publish stream channel
             */
            virtual void enablePublishDirectToCDN(bool enable, ZegoCDNConfig* config, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sets up the stream watermark before stream publishing (for the specified channel).
             *
             * Set before publishing. The layout of the watermark cannot exceed the video encoding resolution of stream.
             *
             * @param watermark The upper left corner of the watermark layout is the origin of the coordinate system, and the area cannot exceed the size set by the encoding resolution. If it is nullptr, the watermark is cancelled.
             * @param isPreviewVisible the watermark is visible on local preview
             * @param channel Publish stream channel
             */
            virtual void setPublishWatermark(ZegoWatermark* watermark, bool isPreviewVisible, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sends Supplemental Enhancement Information (for the specified channel).
             *
             * This interface can synchronize some other additional information while the developer publishes streaming audio and video streaming data while sending streaming media enhancement supplementary information.
             * Generally, for scenarios such as synchronizing music lyrics or precise layout of video canvas, you can choose to use this api.
             * After the anchor sends the SEI, the audience can obtain the SEI content by monitoring the callback of [onPlayerRecvSEI].
             * Since SEI information follows video frames or audio frames, and because of network problems, frames may be dropped, so SEI information may also be dropped. To solve this situation, it should be sent several times within the limited frequency.
             * Limit frequency: Do not exceed 30 times per second.
             * Note: This api is effective only when there is video data published. SEI information will not be sent without publishing video data.
             * The SEI data length is limited to 4096 bytes.
             *
             * @param data SEI data
             * @param dataLength SEI data length
             * @param channel Publish stream channel
             */
            virtual void sendSEI(const unsigned char* data, unsigned int dataLength, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Enables or disables hardware encoding.
             *
             * Whether to use the hardware encoding function when publishing the stream, the GPU is used to encode the stream and to reduce the CPU usage. The setting can take effect before the stream published. If it is set after the stream published, the stream should be stopped first before it takes effect.
             * Because hard-coded support is not particularly good for a few models, SDK uses software encoding by default. If the developer finds that the device is hot when publishing a high-resolution audio and video stream during testing of some models, you can consider calling this interface to enable hard coding.
             *
             * @param enable Whether to enable hardware encoding, true: enable hardware encoding, false: disable hardware encoding
             */
            virtual void enableHardwareEncoder(bool enable) = 0;

            /**
             * Sets the timing of video scaling in the video capture workflow. You can choose to do video scaling right after video capture (the default value) or before encoding.
             *
             * This interface needs to be set before previewing or streaming.
             * The main effect is whether the local preview is affected when the acquisition resolution is different from the encoding resolution.
             *
             * @param mode capture scale mode
             */
            virtual void setCapturePipelineScaleMode(ZegoCapturePipelineScaleMode mode) = 0;

            /**
             * Starts playing a stream from ZEGO's streaming cloud.
             *
             * This interface allows users to play audio and video streams from the ZEGO audio and video cloud.
             * Before starting to play the stream, you need to join the room first, you can get the new streamID in the room by listening to the [onRoomStreamUpdate] event callback.
             * In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event.
             * Playing the stream ID that does not exist, the SDK continues to try to play after executing this interface. After the stream ID is successfully published, the audio and video stream can be actually played.
             * The developer can update the player canvas by calling this interface again (the streamID must be the same).
             *
             * @param streamID Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
             * @param canvas The view used to display the play audio and video stream's image. If the view is set to [nullptr], it will not be displayed.
             */
            virtual void startPlayingStream(const std::string& streamID, ZegoCanvas* canvas) = 0;

            /**
             * Starts playing a stream from ZEGO's streaming cloud or from third-party CDN.
             *
             * This interface allows users to play audio and video streams both from the ZEGO real-time audio and video cloud and from third-party cdn.
             * Before starting to play the stream, you need to join the room first, you can get the new streamID in the room by listening to the [onRoomStreamUpdate] event callback.
             * In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event.
             * Playing the stream ID that does not exist, the SDK continues to try to play after executing this interface. After the stream ID is successfully published, the audio and video stream can be actually played.
             * The developer can update the player canvas by calling this interface again (the streamID must be the same).
             *
             * @param streamID Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
             * @param canvas The view used to display the play audio and video stream's image. If the view is set to [nullptr], it will not be displayed.
             * @param config Advanced player configuration
             */
            virtual void startPlayingStream(const std::string& streamID, ZegoCanvas* canvas, ZegoPlayerConfig config) = 0;

            /**
             * Stops playing a stream.
             *
             * This interface allows the user to stop playing the stream. When stopped, the attributes set for this stream previously, such as [setPlayVolume], [mutePlayStreamAudio], [mutePlayStreamVideo], etc., will be invalid and need to be reset when playing the the stream next time.
             *
             * @param streamID Stream ID
             */
            virtual void stopPlayingStream(const std::string& streamID) = 0;

            /**
             * Sets the stream playback volume.
             *
             * This interface is used to set the playback volume of the stream. Need to be called after calling startPlayingStream.
             * You need to reset after [stopPlayingStream] and [startPlayingStream].
             *
             * @param streamID Stream ID
             * @param volume Volume percentage. The value ranges from 0 to 200, and the default value is 100.
             */
            virtual void setPlayVolume(const std::string& streamID, int volume) = 0;

            /**
             * Stops or resumes playing the audio part of a stream.
             *
             * This api can be used to stop playing/retrieving the audio data of the stream. Need to be called after calling startPlayingStream.
             *
             * @param streamID Stream ID
             * @param mute mute flag, true: mute play stream video, false: resume play stream video
             */
            virtual void mutePlayStreamAudio(const std::string& streamID, bool mute) = 0;

            /**
             * Stops or resumes playing the video part of a stream.
             *
             * This interface can be used to stop playing/retrieving the video data of the stream. Need to be called after calling startPlayingStream.
             * This api is only effective for playing stream from ZEGO real-time audio and video cloud (not ZEGO CDN or third-party CDN).
             *
             * @param streamID Stream ID
             * @param mute mute flag, true: mute play stream video, false: resume play stream video
             */
            virtual void mutePlayStreamVideo(const std::string& streamID, bool mute) = 0;

            /**
             * Enables or disables hardware decoding.
             *
             * Turn on hardware decoding and use hardware to improve decoding efficiency. Need to be called before calling startPlayingStream.
             * Because hard-decoded support is not particularly good for a few models, SDK uses software decoding by default. If the developer finds that the device is hot when playing a high-resolution audio and video stream during testing of some models, you can consider calling this interface to enable hard decoding.
             *
             * @param enable Whether to turn on hardware decoding switch, true: enable hardware decoding, false: disable hardware decoding. The default is false
             */
            virtual void enableHardwareDecoder(bool enable) = 0;

            /**
             * Enables or disables frame order detection.
             *
             * @param enable Whether to turn on frame order detection, true: enable check poc,not support B frames, false: disable check poc, support B frames but the screen may temporary splash. The default is true
             */
            virtual void enableCheckPoc(bool enable) = 0;

            /**
             * Starts a stream mixing task.
             *
             * Due to the performance considerations of the client device, ZegoExpressEngine's mix stream is to start the mixing stream task on the server side of the ZEGO audio and video cloud for mixing stream.
             * After calling this api, SDK initiates a mixing stream request to the ZEGO audio and video cloud. The ZEGO audio and video cloud will find the current publishing stream and perform video layer blending according to the parameters of the mixing stream task requested by ZegoExpressEngine.
             * When you need to update the mixing stream task, that is, the input stream list needs to be updated when the input stream increases or decreases, you can update the field of the [ZegoMixerTask] object inputList and call this api again to pass the same [ZegoMixerTask] object to update the mixing stream task.
             * If an exception occurs when requesting to start the mixing stream task, for example, the most common mix input stream does not exist, it will be given from the callback error code. For specific error codes, please refer to the common error code documentation [https://doc-en.zego.im/en/308.html].
             * If an input stream does not exist in the middle, the mixing stream task will automatically retry playing the input stream for 90 seconds, and will not retry after 90 seconds.
             *
             * @param task Mix stream task object
             * @param callback Start mix stream task result callback notification
             */
            virtual void startMixerTask(ZegoMixerTask task, ZegoMixerStartCallback callback) = 0;

            /**
             * Stops a stream mixing task.
             *
             * Similar to [startMixerTask], after calling this api, SDK initiates a request to end the mixing stream task to the ZEGO audio and video cloud server.
             * If you starts the next mixing stream task without stopping the previous mixing stream task, the previous mixing stream task will not stop automatically. The previous mixing stream task will not be stopped automatically until 90 seconds after the input stream of the previous mixing stream task does not exist.
             * When using the mixing stream function of the ZEGO audio and video cloud service, you should pay attention to the start of the next mixing stream task, and should stop the previous mixing stream task, so as not to cause the anchor has started the next streaming task and mixing with other anchors, and the audience is still playing the output stream of the previous mixing stream task.
             *
             * @param task Mix stream task object
             * @param callback Stop mix stream task result callback notification
             */
            virtual void stopMixerTask(ZegoMixerTask task, ZegoMixerStopCallback callback) = 0;

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
            virtual void muteMicrophone(bool mute) = 0;

            /**
             * Checks whether the microphone is muted.
             *
             * Can be used with [muteMicrophone], determine whether the microphone is muted.
             *
             * @return Whether the microphone is muted; true: the microphone is muted; false: the microphone is enable (not muted)
             */
            virtual bool isMicrophoneMuted() = 0;

            /**
             * Mutes or unmutes the audio output speaker.
             *
             * After mute speaker, all the SDK sounds will not play, including playing stream, mediaplayer, etc. But the SDK will still occupy the output device.
             *
             * @param mute Whether to mute (disable) speaker audio output, true: mute (disable) speaker audio output, false: enable speaker audio output. The default value is false
             */
            virtual void muteSpeaker(bool mute) = 0;

            /**
             * Checks whether the audio output speaker is muted.
             *
             * Can be used with [muteSpeaker], determine whether the speaker audio output is muted.
             *
             * @return Whether the speaker is muted; true: the speaker is muted; false: the speaker is enable (not muted)
             */
            virtual bool isSpeakerMuted() = 0;

            /**
             * Chooses to use the specified audio device.
             *
             * @param deviceType Audio device type
             * @param deviceID ID of a device obtained by getAudioDeviceList
             */
            virtual void useAudioDevice(ZegoAudioDeviceType deviceType, const std::string& deviceID) = 0;

            /**
             * Gets a list of audio devices.
             *
             * @param deviceType Audio device type
             * @return Audo device List
             */
            virtual std::vector<ZegoDeviceInfo> getAudioDeviceList(ZegoAudioDeviceType deviceType) = 0;

            /**
             * Enables or disables the audio capture device.
             *
             * This api is used to control whether to release the audio collection device. When the audio collection device is turned off, the SDK will no longer occupy the audio device. Of course, if the stream is being published at this time, there is no audio data.
             * Occupying the audio capture device and giving up Occupying the audio device is a relatively heavy operation, and the [muteMicrophone] interface is generally recommended.
             *
             * @param enable Whether to enable the audio capture device, true: disable audio capture device, false: enable audio capture device
             */
            virtual void enableAudioCaptureDevice(bool enable) = 0;

            /**
             * Turns on/off the camera (for the specified channel).
             *
             * This interface is used to control whether to start the camera acquisition. After the camera is turned off, video capture will not be performed. At this time, the publish stream will also have no video data.
             * In the case of using a custom video capture function, because the developer has taken over the video data capturing, the SDK is no longer responsible for the video data capturing, this api is no longer valid.
             *
             * @param enable Whether to turn on the camera, true: turn on camera, false: turn off camera
             * @param channel Publishing stream channel
             */
            virtual void enableCamera(bool enable, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Chooses to use the specified video device (for the specified channel).
             *
             * @param deviceID ID of a device obtained by getVideoDeviceList
             * @param channel Publishing stream channel
             */
            virtual void useVideoDevice(const std::string& deviceID, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Gets a list of video devices.
             *
             * @return Video device List
             */
            virtual std::vector<ZegoDeviceInfo> getVideoDeviceList() = 0;

            /**
             * Starts sound level monitoring.
             *
             * After starting monitoring, you can receive local audio sound level via [onCapturedSoundLevelUpdate] callback, and receive remote audio sound level via [onRemoteSoundLevelUpdate] callback.
             * Before entering the room, you can call [startPreview] with this api and combine it with [onCapturedSoundLevelUpdate] callback to determine whether the audio device is working properly.
             * [onCapturedSoundLevelUpdate] and [onRemoteSoundLevelUpdate] callback notification period is 100 ms.
             */
            virtual void startSoundLevelMonitor() = 0;

            /**
             * Stops sound level monitoring.
             *
             * After the monitoring is stopped, the callback of the local/remote audio sound level will be stopped.
             */
            virtual void stopSoundLevelMonitor() = 0;

            /**
             * Starts audio spectrum monitoring.
             *
             * After starting monitoring, you can receive local audio spectrum via [onCapturedAudioSpectrumUpdate] callback, and receive remote audio spectrum via [onRemoteAudioSpectrumUpdate] callback.
             * [onCapturedAudioSpectrumUpdate] and [onRemoteAudioSpectrumUpdate] callback notification period is 100 ms.
             */
            virtual void startAudioSpectrumMonitor() = 0;

            /**
             * Stops audio spectrum monitoring.
             *
             * After the monitoring is stopped, the callback of the local/remote audio spectrum will be stopped.
             */
            virtual void stopAudioSpectrumMonitor() = 0;

            /**
             * Enables or disables headphone monitoring.
             *
             * enable/disable headphone monitor, this setting takes effect when the headset is connected.
             *
             * @param enable Whether to use headphone monitor, true: enable, false: disable
             */
            virtual void enableHeadphoneMonitor(bool enable) = 0;

            /**
             * Sets the headphone monitor volume.
             *
             * set headphone monitor volume, this setting takes effect when the headset is connected.
             *
             * @param volume headphone monitor volume, range from 0 to 100, 80 as default
             */
            virtual void setHeadphoneMonitorVolume(int volume) = 0;

            /**
             * Enables or disables system audio capture.
             *
             * Enable sound card capture to mix sounds played by the system into the push stream, such as sounds played by the browser, sounds played by other software, etc.
             *
             * @param enable Whether to mix system playout
             */
            virtual void enableMixSystemPlayout(bool enable) = 0;

            /**
             * Enables or disables Acoustic Echo Cancellation (AEC).
             *
             * Turning on echo cancellation, the SDK filters the collected audio data to reduce the echo component in the audio.
             * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
             *
             * @param enable Whether to enable echo cancellation, true: enable echo cancellation, false: disable echo cancellation
             */
            virtual void enableAEC(bool enable) = 0;

            /**
             * Sets the Acoustic Echo Cancellation (AEC) mode.
             *
             * Switch different echo cancellation modes to control the extent to which echo data is eliminated.
             * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
             *
             * @param mode Echo cancellation mode
             */
            virtual void setAECMode(ZegoAECMode mode) = 0;

            /**
             * Enables or disables Automatic Gain Control (AGC).
             *
             * When the auto gain is turned on, the sound will be amplified, but it will affect the sound quality to some extent.
             * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
             *
             * @param enable Whether to enable automatic gain control, true: enable AGC, false: disable AGC
             */
            virtual void enableAGC(bool enable) = 0;

            /**
             * Enables or disables Automatic Noise Suppression (ANS).
             *
             * Turning on the noise suppression switch can reduce the noise in the audio data and make the human voice clearer.
             * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
             *
             * @param enable Whether to enable noise suppression, true: enable AGC, false: disable AGC
             */
            virtual void enableANS(bool enable) = 0;

            /**
             * Sets the Automatic Noise Suppression (ANS) mode.
             *
             * Default is medium mode
             * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
             *
             * @param mode Audio Noise Suppression mode
             */
            virtual void setANSMode(ZegoANSMode mode) = 0;

            /**
             * Enables or disables audio mixing.
             *
             * Enable audio mixing, work with setAudioMixingHandler providing the audio data for mixing
             *
             * @param enable Whether to enable audio mixting, true: enable, false: disable
             */
            virtual void enableAudioMixing(bool enable) = 0;

            /**
             * Sets up the audio mixing event handler.
             *
             * @param handler Audio mixing callback handler
             */
            virtual void setAudioMixingHandler(std::shared_ptr<IZegoAudioMixingHandler> handler) = 0;

            /**
             * Stops or resumes playing the mixed audio locally.
             *
             * When stop play audio mixing locally, the audio will not be heard on the mix side (push side) while still be heard on the remote side (pull side).
             *
             * @param mute Whether to mute local audio mixting, true: mute, false: unmute
             */
            virtual void muteLocalAudioMixing(bool mute) = 0;

            /**
             * Sets the audio mixing output volume for either local playback or the stream to published.
             *
             * This API can individually set the mixing volume of local playback or the mixing volume of the push stream
             *
             * @param volume audio mixing volume, range from 0 to 100, 50 as default
             * @param type volume local playback / volume in stream published
             */
            virtual void setAudioMixingVolume(int volume, ZegoVolumeType type) = 0;

            /**
             * Set the sound equalizer (EQ)
             *
             * @param bandIndex The value range is [0, 9], corresponding to 10 frequency bands, and the center frequencies are [31, 62, 125, 250, 500, 1K, 2K, 4K, 8K, 16K] Hz.
             * @param bandGain The value range is [-15, 15]. Default value is 0, if all gain values in all frequency bands are 0, EQ function will be disabled.
             */
            virtual void setAudioEqualizerGain(int bandIndex, float bandGain) = 0;

            /**
             * Sets up the voice changer parameters.
             *
             * sound change effect only works on capture sounds.
             *
             * @param param Voice changer parameters
             */
            virtual void setVoiceChangerParam(ZegoVoiceChangerParam param) = 0;

            /**
             * Sets up the reverberation parameters.
             *
             * Different values set dynamically after a successful publishing will take effect, When any of the parameters is set to 0.0, the reverb is turned off.
             *
             * @param param Reverb parameter
             */
            virtual void setReverbParam(ZegoReverbParam param) = 0;

            /**
             * Enables the virtual stereo feature.
             *
             * Note: You need to set up a dual channel setAudioConfig for the virtual stereo to take effect!
             *
             * @param enable true to turn on the virtual stereo, false to turn off the virtual stereo
             * @param angle angle of the sound source in the virtual stereo, ranging from 0 to 180, with 90 being the front, and 0 and 180 being respectively Corresponds to rightmost and leftmost, usually defaults to 90.
             */
            virtual void enableVirtualStereo(bool enable, int angle) = 0;

            /**
             * Sends a Broadcast Message, which will be delivered to the first 500 users in the room.
             *
             * The total sending frequency limit of [sendBroadcastMessage] and [sendCustomCommand] is 600 times per minute by default.
             * Users of up to the first 500 advanced rooms in the same room can receive it, which is generally used when the number of live broadcast rooms is less than 500.
             *
             * @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
             * @param message Message content, no longer than 256 bytes
             * @param callback Send broadcast message result callback
             */
            virtual void sendBroadcastMessage(const std::string& roomID, const std::string& message, ZegoIMSendBroadcastMessageCallback callback) = 0;

            /**
             * Sends a Barrage Message (bullet screen) to all users in the same room, without guaranteeing the delivery.
             *
             * There is no limit on the number of transmissions, but the server will actively drop messages if it is sent too frequently.
             * It can be received by users with more than 500 people in the same room, but it is not reliable, that is, when there are many users in the room or messages are sent frequently between users, the users who receive the messages may not be able to receive them. Generally used for sending live barrage.
             *
             * @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
             * @param message Message content, no longer than 256 bytes
             * @param callback Send barrage message result callback
             */
            virtual void sendBarrageMessage(const std::string& roomID, const std::string& message, ZegoIMSendBarrageMessageCallback callback) = 0;

            /**
             * Sends a Custom Command to the specified users in the same room.
             *
             * The total sending frequency limit of [sendBroadcastMessage] and [sendCustomCommand] is 600 times per minute by default.
             * The type of point-to-point signaling in the same room is generally used for remote control signaling or message sending between users.
             *
             * @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
             * @param command Custom command content, no longer than 256 bytes
             * @param toUserList The users who will receive the command
             * @param callback Send command result callback
             */
            virtual void sendCustomCommand(const std::string& roomID, const std::string& command, std::vector<ZegoUser> toUserList, ZegoIMSendCustomCommandCallback callback) = 0;

            /**
             * Creates a media player instance.
             *
             * Currently, a maximum of 4 instances can be created, after which it will return nullptr. The more instances of a media player, the greater the performance overhead on the device.
             *
             * @return Media player instance, nullptr will be returned when the maximum number is exceeded.
             */
            virtual IZegoMediaPlayer* createMediaPlayer() = 0;

            /**
             * Destroys a media player instance.
             *
             * @param mediaPlayer The media player instance object to be destroyed
             */
            virtual void destroyMediaPlayer(IZegoMediaPlayer*& mediaPlayer) = 0;

            /**
             * Starts to record locally captured audio or video and directly save the data to a file.
             *
             * Currently only one task can be recorded simultaneously.
             * This API needs to be called after the success of [startPreview] or [startPublishingStream] to be effective.
             * Developers should not [stopPreview] or [stopPublishingStream] during recording, otherwise the SDK will end the current recording task.
             * Developers will receive the [onCapturedDataRecordStateUpdate] and the [onCapturedDataRecordProgressUpdate] callback after start recording.
             *
             * @param config Record config
             * @param channel Publishing stream channel
             */
            virtual void startRecordingCapturedData(ZegoDataRecordConfig config, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Stops recording locally captured audio or video.
             *
             * @param channel Publishing stream channel
             */
            virtual void stopRecordingCapturedData(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sets up the event callback handler for data recording.
             *
             * Implemente the functions of ZegoDataRecordEventHandler to get notified when recode state and process changed
             *
             * @param eventHandler Data record event handler
             */
            virtual void setDataRecordEventHandler(std::shared_ptr<IZegoDataRecordEventHandler> eventHandler) = 0;

            /**
             * Enables or disables custom video rendering.
             *
             * It must be set before the engine starts, that is, before calling [startPreview], [startPublishing], [startPlayingStream]; and the configuration can be modified after the engine is stopped， that is after calling [logoutRoom].
             * When the developer starts custom rendering, by calling [setCustomVideoRenderHandler], you can set to receive local and remote video frame data for custom rendering
             *
             * @param enable enable or disable
             * @param config custom video render config
             */
            virtual void enableCustomVideoRender(bool enable, ZegoCustomVideoRenderConfig* config) = 0;

            /**
             * Sets up the event callback handler for custom video rendering.
             *
             * Custom video render, developers are responsible for rendering video data to UI components. This feature is generally used by developers who use third-party beauty features or use third-party rendering frameworks.
             * When you use the advanced features of ZegoExpressEngine's custom video render, you need to call this api to set a callback object for developers to transfer video data.
             * When you call the start preview [startPreview], start publishing stream [startPublishingStream], or start playing stream [startPlayingStream], the callback method that transfer video data to you will be triggered.
             * You can render video images according to the callback of SDK transfering video data.
             * Custom video rendering can be used with custom video capture.
             *
             * @param handler Custom video render handler
             */
            virtual void setCustomVideoRenderHandler(std::shared_ptr<IZegoCustomVideoRenderHandler> handler) = 0;

            /**
             * Enables or disables custom video capture (for the specified channel).
             *
             * It must be set before the engine starts, that is, before calling [startPreview], [startPublishing]; and the configuration can be modified after the engine is stopped, that is, after calling [logoutRoom].
             * When the developer starts the custom capture, it can be set to receive notification of the start and stop of the custom capture by calling [setCustomVideoCaptureHandler].
             *
             * @param enable enable or disable
             * @param config custom video capture config
             * @param channel publish channel
             */
            virtual void enableCustomVideoCapture(bool enable, ZegoCustomVideoCaptureConfig* config, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sets the event callback handler for custom video capture.
             *
             * Custom video capture, that is, the developer is responsible for collecting video data and sending the collected video data to SDK for video data encoding and publishing to the ZEGO audio and video cloud.This feature is generally used by developers who use third-party beauty features or record game screen living.
             * When you use the advanced features of ZegoExpressEngine's custom video capture, you need to call this api to set SDK to notify that you can start sending video data to ZegoExpressEngine.
             * When you calls startPreview and startPublishingStream, a callback method that notifies you to start sending video data will be triggered. When you stop preview [stopPreview] and stop publishing stream [stopPublishingStream], it will trigger a callback method that notify that you can stop sending video data.
             * Because when using custom video capture, SDK will no longer start the camera to capture video data. You need to collect video data from video sources by yourself.
             * Custom video capture can be used with custom video rendering.
             *
             * @param handler Custom video capture handler
             */
            virtual void setCustomVideoCaptureHandler(std::shared_ptr<IZegoCustomVideoCaptureHandler> handler) = 0;

            /**
             * Sends the video frames (Raw Data) produced by custom video capture to the SDK (for the specified channel).
             *
             * This api need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
             *
             * @param data video frame data
             * @param dataLength video frame data length
             * @param params video frame param
             * @param referenceTimeMillisecond video frame reference time, UNIX timestamp, in milliseconds.
             * @param channel Publishing stream channel
             */
            virtual void sendCustomVideoCaptureRawData(const unsigned char* data, unsigned int dataLength, ZegoVideoFrameParam params, unsigned long long referenceTimeMillisecond, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sends the video frames (Encoded Data) produced by custom video capture to the SDK (for the specified channel).
             *
             * This api need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
             *
             * @param data video frame encoded data
             * @param dataLength video frame data length
             * @param params video frame param
             * @param referenceTimeMillisecond video frame reference time, UNIX timestamp, in milliseconds.
             * @param channel Publishing stream channel
             */
            virtual void sendCustomVideoCaptureEncodedData(const unsigned char* data, unsigned int dataLength, ZegoVideoEncodedFrameParam params, unsigned long long referenceTimeMillisecond, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sets the video fill mode of custom video capture (for the specified channel).
             *
             * @param mode View mode
             * @param channel Publishing stream channel
             */
            virtual void setCustomVideoCaptureFillMode(ZegoViewMode mode, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Enable local capture custom audio processing.
             *
             * When enabled, developers can receive local captured audio frame through [onProcessCapturedAudioData], and can modify the audio data.
             * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
             *
             * @param enable Whether to enable local capture custom audio processing.
             * @param config Custom audio processing configuration.
             */
            virtual void enableCustomAudioCaptureProcessing(bool enable, ZegoCustomAudioProcessConfig* config) = 0;

            /**
             * Enable custom audio processing for remote playing stream.
             *
             * When enabled, developers can receive audio frame from remote playing stream through [onProcessRemoteAudioData], and can modify the audio data.
             * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
             *
             * @param enable Whether to enable custom audio processing for remote playing stream.
             * @param config Custom audio processing configuration.
             */
            virtual void enableCustomAudioRemoteProcessing(bool enable, ZegoCustomAudioProcessConfig* config) = 0;

            /**
             * Set up callback handler for custom audio processing.
             *
             * Developers can modify the processing of audio frame data in the callback.
             *
             * @param handler Callback handler for custom audio processing.
             */
            virtual void setCustomAudioProcessHandler(std::shared_ptr<IZegoCustomAudioProcessHandler> handler) = 0;

            /**
             * Enables the callback for receiving audio data.
             *
             * The callback to the corresponding setting of [setAudioDataHandler] is triggered when this interface is called and at publishing stream state or playing stream state.
             *
             * @param enable Whether to enable audio data callback
             * @param callbackBitMask The callback api bitmask marker for receive audio data, refer to enum [ZegoAudioDataCallbackBitMask], when this param converted to binary, 0x01 for triggering [onCapturedAudioData], 0x10 for triggering [onRemoteAudioData], 0x100 for triggering [onMixedAudioData].The masks can be combined to allow different callbacks to be triggered simultaneously.
             * @param param param of audio frame
             */
            virtual void enableAudioDataCallback(bool enable, unsigned int callbackBitMask, ZegoAudioFrameParam param) = 0;

            /**
             * Sets up the event callback handler for receiving audio data.
             *
             * You can call this api to receive audio data from the SDK when you need to get the audio data of the remote user or get the data collected by the local microphone for other purposes (such as audio-only recording, audio-only third-party monitoring, and audio-only real-time analysis).
             * The set callback needs to be after the call to [enableAudioDataCallback] and in a push or pull stream state for the callback to work.
             * The format of the audio data callback by SDK is pcm. The SDK still controls the collection and playback of the sound device. This function is to copy a piece of data collected or played inside the SDK to the developer for use.
             *
             * @param handler Audio data handler for receive audio data
             */
            virtual void setAudioDataHandler(std::shared_ptr<IZegoAudioDataHandler> handler) = 0;

            /**
             * Enables the custom audio I/O function (for the specified channel).
             *
             * It needs to be invoked before [startPublishingStream], [startPlayingStream] or [startPreview] to take effect.
             *
             * @param enable Whether to enable custom audio IO, default is false
             * @param config Custom audio IO config
             * @param channel Specify the publish channel to enable custom audio IO
             */
            virtual void enableCustomAudioIO(bool enable, ZegoCustomAudioConfig* config, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sends AAC audio data produced by custom audio capture to the SDK (for the specified channel).
             *
             * @param data AAC buffer data
             * @param dataLength The total length of the buffer data
             * @param configLength The length of AAC specific config (Note: The AAC encoded data length is 'encodedLength = dataLength - configLength')
             * @param referenceTimeMillisecond The UNIX timestamp of this AAC audio frame in millisecond.
             * @param param The param of this AAC audio frame
             * @param channel Publish channel for capturing audio frames
             */
            virtual void sendCustomAudioCaptureAACData(unsigned char * data, unsigned int dataLength, unsigned int configLength, unsigned long long referenceTimeMillisecond, ZegoAudioFrameParam param, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Sends PCM audio data produced by custom audio capture to the SDK (for the specified channel).
             *
             * @param data PCM buffer data
             * @param dataLength The total length of the buffer data
             * @param param The param of this PCM audio frame
             * @param channel Publish channel for capturing audio frames
             */
            virtual void sendCustomAudioCapturePCMData(unsigned char * data, unsigned int dataLength, ZegoAudioFrameParam param, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

            /**
             * Fetches PCM audio data of the remote stream for custom audio rendering.
             *
             * It is recommended to use the system framework to periodically invoke this API to drive audio data rendering
             *
             * @param data A block of memory for storing audio PCM data that requires user to manage the memory block's lifecycle, the SDK will copy the audio frame rendering data to this memory block
             * @param dataLength The length of the audio data to be fetch this time (dataLength = duration * sampleRate * channels * 2(16 bit depth i.e. 2 Btye))
             * @param param Specify the parameters of the fetched audio frame
             */
            virtual void fetchCustomAudioRenderPCMData(unsigned char * data, unsigned int dataLength, ZegoAudioFrameParam param) = 0;

            /**
             * Turn on/off audio output to the device
             *
             * This interface is used to control whether the SDK needs to throw audio data to the device.
             *
             * @deprecated This interface is deprecated, please use [muteSpeaker] instead.
             * @param mute Whether to disable audio output to the device, true: disable audio output, false: enable audio output
             */
            virtual void muteAudioOutput(bool mute) = 0;

        };
        /**
         * Zego MediaPlayer
         *
         * Yon can use ZegoMediaPlayer to play media resource files on the local or remote server, and can mix the sound of the media resource files that are played into the publish stream to achieve the effect of background music.
         */
        class IZegoMediaPlayer
        {
        protected:

            virtual ~IZegoMediaPlayer() {}

        public:

            /**
             * Set event callback handler for media player
             *
             * You can change the player UI widget according to the related event callback of the media player
             *
             * @param handler Media player event callback object
             */
            virtual void setEventHandler(std::shared_ptr<IZegoMediaPlayerEventHandler> handler) = 0;

            /**
             * Set video callback handler
             *
             * You can set this callback to throw the video data of the media resource file played by the media player
             *
             * @param handler Video event callback object for media player
             * @param format Video frame format for video data
             */
            virtual void setVideoHandler(std::shared_ptr<IZegoMediaPlayerVideoHandler> handler, ZegoVideoFrameFormat format) = 0;

            /**
             * Set audio callback handler
             *
             * You can set this callback to throw the audio data of the media resource file played by the media player
             *
             * @param handler Audio event callback object for media player
             */
            virtual void setAudioHandler(std::shared_ptr<IZegoMediaPlayerAudioHandler> handler) = 0;

            /**
             * Load media resource
             *
             * Yon can pass the absolute path of the local resource or the URL of the network resource
             *
             * @param path the absolute path of the local resource or the URL of the network resource
             * @param callback Notification of resource loading results
             */
            virtual void loadResource(const std::string& path, ZegoMediaPlayerLoadResourceCallback callback) = 0;

            /**
             * Start playing
             *
             * You need to load resources before playing
             */
            virtual void start() = 0;

            /**
             * Stop playing
             */
            virtual void stop() = 0;

            /**
             * Pause playing
             */
            virtual void pause() = 0;

            /**
             * resume playing
             */
            virtual void resume() = 0;

            /**
             * Set the specified playback progress
             *
             * Unit is millisecond
             *
             * @param millisecond Point in time of specified playback progress
             * @param callback the result notification of set the specified playback progress
             */
            virtual void seekTo(unsigned long long millisecond, ZegoMediaPlayerSeekToCallback callback) = 0;

            /**
             * Whether to repeat playback
             *
             * @param enable repeat playback flag. The default is false.
             */
            virtual void enableRepeat(bool enable) = 0;

            /**
             * Whether to mix the player's sound into the stream being published
             *
             * @param enable Aux audio flag. The default is false.
             */
            virtual void enableAux(bool enable) = 0;

            /**
             * Whether to play locally silently
             *
             * If [enableAux] switch is turned on, there is still sound in the publishing stream. The default is false.
             *
             * @param mute Mute local audio flag, The default is false.
             */
            virtual void muteLocal(bool mute) = 0;

            /**
             * Set the view of the player playing video
             *
             * @param canvas Video rendered canvas object
             */
            virtual void setPlayerCanvas(ZegoCanvas* canvas) = 0;

            /**
             * Set player volume
             *
             * @param volume The range is 0 ~ 100. The default is 50.
             */
            virtual void setVolume(int volume) = 0;

            /**
             * Set playback progress callback interval
             *
             * This interface can control the callback frequency of [onMediaPlayerPlayingProgress]. When the callback interval is set to 0, the callback is stopped. The default callback interval is 1s
             * This callback are not returned exactly at the set callback interval, but rather at the frequency at which the audio or video frames are processed to determine whether the callback is needed to call
             *
             * @param millisecond Interval of playback progress callback in milliseconds
             */
            virtual void setProgressInterval(unsigned long long millisecond) = 0;

            /**
             * Get the current volume
             *
             * The range is 0 ~ 100. The default is 50
             */
            virtual int getVolume() = 0;

            /**
             * Get the total progress of your media resources
             *
             * You should load resource before invoking this API, otherwise the return value is 0
             *
             * @return Unit is millisecond
             */
            virtual unsigned long long getTotalDuration() = 0;

            /**
             * Get current playing progress
             *
             * You should load resource before invoking this API, otherwise the return value is 0
             */
            virtual unsigned long long getCurrentProgress() = 0;

            /**
             * Get the current playback status
             */
            virtual ZegoMediaPlayerState getCurrentState() = 0;

            /**
             * Get media player index
             */
            virtual int getIndex() = 0;

        };


    }
}
#endif // __ZEGOEXPRESSINTERFACE_H__
