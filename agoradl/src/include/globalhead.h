#pragma once

#define INFO_LENTH (4096)

typedef struct _RESULT_HANDLER_PARAM
{
	CHAR szCMD[128];
	CHAR	 szInfo[INFO_LENTH];

} RESULT_HANDLER_PARAM, *PRESULT_HANDLER_PARAM, *LPRESULT_HANDLER_PARAM;