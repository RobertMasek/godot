/*************************************************************************/
/*  gd_mono_cache.cpp                                                    */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "gd_mono_cache.h"

#include "core/error/error_macros.h"

namespace GDMonoCache {

ManagedCallbacks managed_callbacks;
bool godot_api_cache_updated = false;

void update_godot_api_cache(const ManagedCallbacks &p_managed_callbacks) {
#define CHECK_CALLBACK_NOT_NULL_IMPL(m_var, m_class, m_method) ERR_FAIL_COND_MSG(m_var == nullptr, \
		"Mono Cache: Managed callback for '" #m_class "_" #m_method "' is null.")

#define CHECK_CALLBACK_NOT_NULL(m_class, m_method) CHECK_CALLBACK_NOT_NULL_IMPL(p_managed_callbacks.m_class##_##m_method, m_class, m_method)

	CHECK_CALLBACK_NOT_NULL(SignalAwaiter, SignalCallback);
	CHECK_CALLBACK_NOT_NULL(DelegateUtils, InvokeWithVariantArgs);
	CHECK_CALLBACK_NOT_NULL(DelegateUtils, DelegateEquals);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, FrameCallback);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, CreateManagedForGodotObjectBinding);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, CreateManagedForGodotObjectScriptInstance);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, GetScriptNativeName);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, SetGodotObjectPtr);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, RaiseEventSignal);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, GetScriptSignalList);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, HasScriptSignal);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, ScriptIsOrInherits);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, AddScriptBridge);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, RemoveScriptBridge);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, UpdateScriptClassInfo);
	CHECK_CALLBACK_NOT_NULL(ScriptManagerBridge, SwapGCHandleForType);
	CHECK_CALLBACK_NOT_NULL(CSharpInstanceBridge, Call);
	CHECK_CALLBACK_NOT_NULL(CSharpInstanceBridge, Set);
	CHECK_CALLBACK_NOT_NULL(CSharpInstanceBridge, Get);
	CHECK_CALLBACK_NOT_NULL(CSharpInstanceBridge, CallDispose);
	CHECK_CALLBACK_NOT_NULL(CSharpInstanceBridge, CallToString);
	CHECK_CALLBACK_NOT_NULL(CSharpInstanceBridge, HasMethodUnknownParams);
	CHECK_CALLBACK_NOT_NULL(GCHandleBridge, FreeGCHandle);
	CHECK_CALLBACK_NOT_NULL(DebuggingUtils, InstallTraceListener);
	CHECK_CALLBACK_NOT_NULL(Dispatcher, InitializeDefaultGodotTaskScheduler);
	CHECK_CALLBACK_NOT_NULL(DisposablesTracker, OnGodotShuttingDown);

	managed_callbacks = p_managed_callbacks;

	godot_api_cache_updated = true;
}
} // namespace GDMonoCache
