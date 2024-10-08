/*
 * Copyright (c) 2017, 2019, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#include "precompiled.hpp"
#include "gc/z/zAttachedArray.inline.hpp"
#include "gc/z/zLock.inline.hpp"
#include "gc/z/zNMethodData.hpp"
#include "memory/allocation.hpp"
#include "runtime/atomic.hpp"
#include "utilities/align.hpp"
#include "utilities/debug.hpp"
#include "utilities/growableArray.hpp"

ZNMethodDataOops *ZNMethodDataOops::create(const GrowableArray<oop *> &immediates, bool has_non_immediates) {
    return ::new(AttachedArray::alloc(immediates.length())) ZNMethodDataOops(immediates, has_non_immediates);
}

void ZNMethodDataOops::destroy(ZNMethodDataOops *oops) {
    AttachedArray::free(oops);
}

ZNMethodDataOops::ZNMethodDataOops(const GrowableArray<oop *> &immediates, bool has_non_immediates) :
        _immediates(immediates.length()),
        _has_non_immediates(has_non_immediates) {
    // Save all immediate oops
    for (size_t i = 0; i < immediates_count(); i++) {
        immediates_begin()[i] = immediates.at(int(i));
    }
}

size_t ZNMethodDataOops::immediates_count() const {
    return _immediates.length();
}

oop **ZNMethodDataOops::immediates_begin() const {
    return _immediates(this);
}

oop **ZNMethodDataOops::immediates_end() const {
    return immediates_begin() + immediates_count();
}

bool ZNMethodDataOops::has_non_immediates() const {
    return _has_non_immediates;
}

ZNMethodData::ZNMethodData() :
        _lock(),
        _oops(NULL) {}

ZNMethodData::~ZNMethodData() {
    ZNMethodDataOops::destroy(_oops);
}

ZReentrantLock *ZNMethodData::lock() {
    return &_lock;
}

ZNMethodDataOops *ZNMethodData::oops() const {
    return Atomic::load_acquire(&_oops);
}

ZNMethodDataOops *ZNMethodData::swap_oops(ZNMethodDataOops *new_oops) {
    ZLocker <ZReentrantLock> locker(&_lock);
    ZNMethodDataOops *const old_oops = _oops;
    _oops = new_oops;
    return old_oops;
}
