/**
 * @file tpl_os_hooks.h
 *
 * @section descr File description
 *
 * Trampoline Hooks related macros, functions prototypes and datatypes
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2007
 * Copyright ESEO for function and data structures documentation
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date: 2014-06-02 04:00:49 -0500 (lun. 02 juin 2014) $
 * $Rev: 1529 $
 * $Author: jlb $
 * $URL: https://trampoline.rts-software.org/svn/trunk/os/tpl_os_hooks.h $
 */

#ifndef TPL_OS_HOOKS_H
#define TPL_OS_HOOKS_H

#include "tpl_os_types.h"

#if WITH_MEMORY_PROTECTION == YES
#define SET_RUNNING_TRUSTED   tpl_kern.running_trusted = 1;
#define RESET_RUNNING_TRUSTED tpl_kern.running_trusted = 0;
#else /* WITH_MEMORY_PROTECTION != YES */
#define SET_RUNNING_TRUSTED
#define RESET_RUNNING_TRUSTED
#endif /* WITH_MEMORY_PROTECTION != YES */

/**
 * @def CALL_POST_TASK_HOOK
 *
 * Generates a call to #PostTaskHook only if WITH_POST_TASK_HOOK
 * (or WITH_TASK_HOOK) is defined
 */
#if WITH_POST_TASK_HOOK == YES
#   define CALL_POST_TASK_HOOK()                        \
    if (TPL_KERN_REF(kern).running->state == RUNNING) { \
      SET_RUNNING_TRUSTED                               \
      PostTaskHook();                                   \
      RESET_RUNNING_TRUSTED                             \
    }
#else
#   define CALL_POST_TASK_HOOK()
#endif

/**
 * @def CALL_PRE_TASK_HOOK
 *
 * Generates a call to #PreTaskHook only if WITH_PRE_TASK_HOOK
 * (or WITH_TASK_HOOK) is defined
 */
#if WITH_PRE_TASK_HOOK == YES
#   define CALL_PRE_TASK_HOOK()         \
    SET_RUNNING_TRUSTED \
    PreTaskHook(); \
    RESET_RUNNING_TRUSTED
#else
#   define CALL_PRE_TASK_HOOK()
#endif

/**
 * @def CALL_STARTUP_HOOK
 *
 * Generates a call to #StartupHook only if WITH_STARTUP_HOOK is defined
 */
#if WITH_STARTUP_HOOK == YES
#   define CALL_STARTUP_HOOK()          \
    SET_RUNNING_TRUSTED \
    StartupHook(); \
    RESET_RUNNING_TRUSTED
#else
#   define CALL_STARTUP_HOOK()
#endif

/**
 * @def CALL_OSAPPLICATION_STARTUP_HOOKS
 *
 * Generate a call to the startup hooks of OSApplications
 */
#if WITH_OSAPPLICATION_STARTUP_HOOK == YES
#   define CALL_OSAPPLICATION_STARTUP_HOOKS()   \
    SET_RUNNING_TRUSTED \
    tpl_osapp_startup_hooks(); \
    RESET_RUNNING_TRUSTED
#else
#   define CALL_OSAPPLICATION_STARTUP_HOOKS()
#endif

/**
 * @def CALL_SHUTDOWN_HOOK
 *
 * Generates a call to #ShutdownHook only if WITH_SHUTDOWN_HOOK is defined
 *
 * @param error error code (#StatusType) to send to shutdown hook
 */
#if WITH_SHUTDOWN_HOOK == YES
#   define CALL_SHUTDOWN_HOOK(error)    \
    SET_RUNNING_TRUSTED \
    ShutdownHook(error); \
    RESET_RUNNING_TRUSTED
#else
#   define CALL_SHUTDOWN_HOOK(error)
#endif

/**
 * @def CALL_OSAPPLICATION_SHUTDOWN_HOOKS
 *
 * Generate a call to the startup hooks of OSApplications
 */
#if WITH_OSAPPLICATION_SHUTDOWN_HOOK == YES
#   define CALL_OSAPPLICATION_SHUTDOWN_HOOKS()   \
    SET_RUNNING_TRUSTED \
    tpl_osapp_shutdown_hooks(); \
    RESET_RUNNING_TRUSTED
#else
#   define CALL_OSAPPLICATION_SHUTDOWN_HOOKS()
#endif

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

#if WITH_PRE_TASK_HOOK == YES
/**
 * Prototype of the pre-task hook routine
 */
extern FUNC(void, OS_CODE) PreTaskHook(void);
#endif

#if WITH_POST_TASK_HOOK == YES
/**
 * Prototype of the post-task hook routine
 */
extern FUNC(void, OS_CODE) PostTaskHook(void);
#endif

#if WITH_STARTUP_HOOK == YES
/**
 * Prototype of the startup hook routine
 */
extern FUNC(void, OS_CODE) StartupHook(void);
#endif

#if WITH_SHUTDOWN_HOOK == YES
/**
 * Prototype of the shutdown hook routine
 */
extern FUNC(void, OS_CODE) ShutdownHook(VAR(StatusType, AUTOMATIC) error);
#endif

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

#endif /* TPL_OS_HOOKS_H */

/* End of file tpl_os_hooks.h */
