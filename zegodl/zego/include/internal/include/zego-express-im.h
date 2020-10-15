
#ifndef __ZEGO_EXPRESS_IM_H__
#define __ZEGO_EXPRESS_IM_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/**
 * Sends a Broadcast Message, which will be delivered to the first 500 users in the room.
 *
 * The total sending frequency limit of [sendBroadcastMessage] and [sendCustomCommand] is 600 times per minute by default.
 * Users of up to the first 500 advanced rooms in the same room can receive it, which is generally used when the number of live broadcast rooms is less than 500.
 *
 * @param room_id Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
 * @param message Message content, no longer than 256 bytes
 */
ZEGOEXP_API zego_seq EXP_CALL zego_express_send_broadcast_message(const char * room_id, const char * message);


/**
 * Sends a Barrage Message (bullet screen) to all users in the same room, without guaranteeing the delivery.
 *
 * There is no limit on the number of transmissions, but the server will actively drop messages if it is sent too frequently.
 * It can be received by users with more than 500 people in the same room, but it is not reliable, that is, when there are many users in the room or messages are sent frequently between users, the users who receive the messages may not be able to receive them. Generally used for sending live barrage.
 *
 * @param room_id Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
 * @param message Message content, no longer than 256 bytes
 */
ZEGOEXP_API zego_seq EXP_CALL zego_express_send_barrage_message(const char * room_id, const char * message);


/**
 * Sends a Custom Command to the specified users in the same room.
 *
 * The total sending frequency limit of [sendBroadcastMessage] and [sendCustomCommand] is 600 times per minute by default.
 * The type of point-to-point signaling in the same room is generally used for remote control signaling or message sending between users.
 *
 * @param room_id Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
 * @param command Custom command content, no longer than 256 bytes
 * @param to_user_list The users who will receive the command
 * @return Sequence of message.
 */
ZEGOEXP_API zego_seq EXP_CALL zego_express_send_custom_command(const char * room_id, const char * command, struct zego_user* to_user_list, unsigned int to_user_count);


/**
 * The callback triggered when Broadcast Messages are received.
 *
 * @param room_id Room ID
 * @param message_list list of received messages.
 * @param message_count List count of received messages.
 * @param user_context Context of user.
 */
typedef void(*zego_on_im_recv_broadcast_message)(const char * room_id, const struct zego_broadcast_message_info* message_list, unsigned int message_count, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_im_recv_broadcast_message_callback(zego_on_im_recv_broadcast_message callback_func, void * user_context);


/**
 * The callback triggered when Barrage Messages are received.
 *
 * @param room_id Room ID
 * @param message_list list of received messages.
 * @param message_count List count of received messages.
 * @param user_context Context of user.
 */
typedef void(*zego_on_im_recv_barrage_message)(const char * room_id, const struct zego_barrage_message_info* message_list, unsigned int message_count, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_im_recv_barrage_message_callback(zego_on_im_recv_barrage_message callback_func, void * user_context);


/**
 * The callback triggered when a Custom Command is received.
 *
 * @param room_id Room ID
 * @param from_user Sender of the command
 * @param command Command content received
 * @param user_context Context of user.
 */
typedef void(*zego_on_im_recv_custom_command)(const char * room_id, struct zego_user from_user, const char * command, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_im_recv_custom_command_callback(zego_on_im_recv_custom_command callback_func, void * user_context);


/**
 * Callback for sending broadcast messages
 *
 * @param room_id Room ID.
 * @param message_id ID of this message
 * @param error_code Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
 * @param seq Sequence of sending broadcast message.
 * @param user_context Context of user.
 */
typedef void(*zego_on_im_send_broadcast_message_result)(const char * room_id, unsigned long long message_id, zego_error error_code, zego_seq seq, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_im_send_broadcast_message_result_callback(zego_on_im_send_broadcast_message_result callback_func, void * user_context);


/**
 * Callback for sending barrage message
 *
 * @param room_id Room ID.
 * @param message_id ID of this message
 * @param error_code Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
 * @param seq Sequence of sending broadcast message.
 * @param user_context Context of user.
 */
typedef void(*zego_on_im_send_barrage_message_result)(const char * room_id, const char * message_id, zego_error error_code, zego_seq seq, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_im_send_barrage_message_result_callback(zego_on_im_send_barrage_message_result callback_func, void * user_context);


/**
 * Callback for sending custom command
 *
 * @param room_id Room ID.
 * @param error_code Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
 * @param seq Sequence of sending broadcast message.
 * @param user_context Context of user.
 */
typedef void(*zego_on_im_send_custom_command_result)(const char * room_id, zego_error error_code, zego_seq seq, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_im_send_custom_command_result_callback(zego_on_im_send_custom_command_result callback_func, void * user_context);



ZEGO_END_DECLS

#endif
