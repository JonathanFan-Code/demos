#ifndef __ZEGO_EXPRESS_UTILS_H__
#define __ZEGO_EXPRESS_UTILS_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS

ZEGOEXP_API const char* EXP_CALL zego_express_get_print_debug_info(int module, const char* func_name, zego_error error_code);

ZEGOEXP_API void EXP_CALL zego_express_trigger_on_debug_error(int error_code, const char* func_name, const char* info);

ZEGOEXP_API void EXP_CALL zego_express_show_debug_message_box(zego_language language, zego_error error_code, const char* func_name, const char* error_info);

ZEGOEXP_API void EXP_CALL zego_express_post_windows_message(void* message);

ZEGOEXP_API void EXP_CALL zego_register_recv_windows_message_callback(void* callback, void* user_context);

ZEGOEXP_API void EXP_CALL zego_express_set_platform_language(enum zego_platform_language);

ZEGO_END_DECLS

#endif