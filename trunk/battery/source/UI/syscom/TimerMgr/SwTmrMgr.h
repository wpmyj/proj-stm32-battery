/***********************************************************************
 *
 * MODULE NAME:  
 * DESCRIPTION:   software timer
 * AUTHOR:     wangxi
 * DATE: 2012/09/09
 *
 ***********************************************************************/
#ifndef __SOFT_TIMER_MGR_H__
#define __SOFT_TIMER_MGR_H__
#include "bits_types.h"

typedef u_int8 SWTMR_NODE_HANDLE;
typedef u_int8 SWTMR_NODE_COUNT;

#define   SWTMR_INVALID_NODE       0

enum {
    SWTMR_MODE_UNUSED   = SWTMR_INVALID_NODE,
    SWTMR_MODE_ONESHOT  = 1<<1,
    SWTMR_MODE_PERIODIC = 1<<2,
};


struct SWTMR_NODE_ITEM {	
    u_int8 flags;
    SWTMR_NODE_HANDLE tmr_id;
    u_int32 timeoutTenths;
    u_int32 timeToExpiry;
    void (*callbackFunc)(void *);
    void *callbackParam;
    struct SWTMR_NODE_ITEM * next;
};

struct SWTMR_INIT_PARAM {
    struct SWTMR_NODE_ITEM *tmrList;
    SWTMR_NODE_COUNT tmrCount;
};

HANDLE SwTmrMgr_Open(struct SWTMR_INIT_PARAM *initParam);
void SwTmrMgr_Close(HANDLE handle);
void SwTmrMgr_Dump(HANDLE handle);


SWTMR_NODE_HANDLE SwTmrMgr_Start(HANDLE handle, u_int32 timeoutTenths, void(*callbackFunc)(void *), void *callbackArg, u_int8 isLoop);
SWTMR_NODE_HANDLE SwTmrMgr_Stop(HANDLE handle, SWTMR_NODE_HANDLE timerHandle);
SWTMR_NODE_HANDLE SwTmrMgr_Change(HANDLE handle, SWTMR_NODE_HANDLE timerHandle, u_int32 timeoutTenths);
SWTMR_NODE_HANDLE SwTmrMgr_Proc(HANDLE handle);


u_int32 SwTmrMgr_ExistSchedule(HANDLE handle);
u_int32 SwTmrMgr_GetCurTickCount(HANDLE handle);

#endif

