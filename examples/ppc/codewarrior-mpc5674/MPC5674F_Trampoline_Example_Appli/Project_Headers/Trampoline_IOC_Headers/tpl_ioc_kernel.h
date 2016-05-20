/*
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005+
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * Trampoline AUTOSAR IOC services declaration
 *
 * $Date$ - $Rev$
 * $Author$
 * $URL$
 */
/* MISRA RULE 3.1 VIOLATION: special character is used in comments for svn integration, the code can survive to this ! */

#ifndef __TPL_IOC_KERNEL_H__
#define __TPL_IOC_KERNEL_H__

//#include "Std_Types.h"
#include "tpl_ioc_internal_types.h"
#include "tpl_ioc_queue.h"
#include "tpl_os_error.h"



#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#if (IOC_QUEUED_COUNT > 0)
extern CONSTP2CONST(tpl_ioc_queued_mo, OS_CONST, OS_CONST) tpl_ioc_queued_table[];
#endif

#if (IOC_UNQUEUED_COUNT > 0)
extern CONSTP2CONST(tpl_ioc_unqueued_mo, OS_CONST, OS_CONST) tpl_ioc_unqueued_table[];
#endif

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"




#define OS_START_SEC_CODE
#include "tpl_memmap.h"

#if (IOC_QUEUED_COUNT > 0)

extern FUNC(Std_ReturnType, OS_CODE) tpl_ioc_send_queued_service(
  VAR(tpl_ioc_id, AUTOMATIC) ioc_id,
  P2CONST(tpl_ioc_message, AUTOMATIC, OS_VAR) ioc_data
);

extern FUNC(Std_ReturnType, OS_CODE) tpl_ioc_receive_queued_service(
  VAR(tpl_ioc_id, AUTOMATIC) ioc_id,
  P2CONST(tpl_ioc_message, AUTOMATIC, OS_VAR) ioc_data
);

extern FUNC(StatusType, OS_CODE) tpl_ioc_empty_queue_service(
  VAR(tpl_ioc_id, AUTOMATIC) ioc_id
);

#endif

#if (IOC_UNQUEUED_COUNT > 0)

extern FUNC(Std_ReturnType, OS_CODE) tpl_ioc_send_unqueued_service(
  VAR(tpl_ioc_id, AUTOMATIC) ioc_id,
  P2CONST(tpl_ioc_message, AUTOMATIC, OS_VAR) ioc_data
);

extern FUNC(StatusType, OS_CODE) tpl_ioc_receive_unqueued_service(
  VAR(tpl_ioc_id, AUTOMATIC) ioc_id,
  P2CONST(tpl_ioc_message, AUTOMATIC, OS_VAR) ioc_data
);

extern FUNC(void, OS_CODE) tpl_ioc_init_unqueued(void);

#endif

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"


#endif /* __TPL_IOC_KERNEL_H__ */
